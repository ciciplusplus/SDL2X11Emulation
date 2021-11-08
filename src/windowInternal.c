//
// Created by Sebastian on 08.10.2016.
//
#include "windowInternal.h"
#include "drawing.h"
#include "events.h"
#include "display.h"

Window SCREEN_WINDOW = None;

void initWindowStruct(WindowStruct* windowStruct, int x, int y, unsigned int width, unsigned int height,
                      Visual* visual, Colormap colormap, Bool inputOnly,
                      unsigned long backgroundColor, Pixmap backgroundPixmap) {
    windowStruct->parent = None;
    initArray(&windowStruct->children, 0);
    windowStruct->x = x;
    windowStruct->y = y;
    windowStruct->w = width;
    windowStruct->h = height;
    windowStruct->inputOnly = inputOnly;
    windowStruct->colormap = colormap;
    windowStruct->visual = visual;
    windowStruct->sdlTexture = NULL;
    windowStruct->sdlWindow = NULL;
    windowStruct->sdlRenderer = NULL;
    windowStruct->backgroundColor = backgroundColor;
    windowStruct->background = backgroundPixmap;
    windowStruct->colormapWindowsCount = -1;
    windowStruct->colormapWindows = NULL;
    initArray(&windowStruct->properties, 0);
    windowStruct->windowName = NULL;
    windowStruct->icon = NULL;
    windowStruct->borderWidth = 0;
    windowStruct->depth = 0;
    windowStruct->mapState = UnMapped;
    windowStruct->eventMask = NoEventMask;
    windowStruct->overrideRedirect = False;
#ifdef DEBUG_WINDOWS
    windowStruct->debugId = ((unsigned long) rand() << 16) | rand();
#endif /* DEBUG_WINDOWS */
}

/* Screen window handles */

Bool initScreenWindow(Display* display) {
    if (SCREEN_WINDOW == None) {
        SCREEN_WINDOW = ALLOC_XID();
        if (SCREEN_WINDOW == None) {
            LOG("Out of memory: Failed to allocate SCREEN_WINDOW in initScreenWindow!\n");
            return False;
        }
        SET_XID_TYPE(SCREEN_WINDOW, WINDOW);
        WindowStruct* window = malloc(sizeof(WindowStruct));
        if (window == NULL) {
            FREE_XID(SCREEN_WINDOW);
            SCREEN_WINDOW = None;
            LOG("Out of memory: Failed to allocate SCREEN_WINDOW in initScreenWindow!\n");
            return False;
        }
        initWindowStruct(window, 0, 0, GET_DISPLAY(display)->screens[0].width, GET_DISPLAY(display)->screens[0].height,
                         NULL, None, False, 0, None);
        SET_XID_VALUE(SCREEN_WINDOW, window);
//        window->sdlWindow = SDL_CreateWindow("Internal", SDL_WINDOWPOS_UNDEFINED,
//                                             SDL_WINDOWPOS_UNDEFINED, 1, 1,
//                                             SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL);
//        if (window->sdlWindow == NULL) {
//            fprintf(stderr, "Creating the main internal window failed: %s\n", SDL_GetError());
//            free(SCREEN_WINDOW);
//            SCREEN_WINDOW = NULL;
//            return False;
//        }
//        window->sdlRenderer = SDL_CreateRenderer(window->sdlWindow, -1, SDL_RENDERER_TARGETTEXTURE);
        SDL_Surface* sdlSurface = SDL_CreateRGBSurface(0, 1, 1, SDL_SURFACE_DEPTH, DEFAULT_RED_MASK,
                                                       DEFAULT_GREEN_MASK, DEFAULT_BLUE_MASK,
                                                       DEFAULT_ALPHA_MASK);
        window->sdlRenderer = SDL_CreateSoftwareRenderer(sdlSurface);
        if (window->sdlRenderer == NULL) {
            LOG("Creating the main renderer failed: %s\n", SDL_GetError());
            SDL_DestroyWindow(window->sdlWindow);
            window->sdlWindow = NULL;
            FREE_XID(SCREEN_WINDOW);
            SCREEN_WINDOW = None;
            return False;
        }
        window->mapState = Mapped;
    }
    return True;
}

void destroyScreenWindow(Display* display) {
    if (SCREEN_WINDOW != None) {
        size_t i;
        Window* children = GET_CHILDREN(SCREEN_WINDOW);
        WindowStruct* windowStruct = GET_WINDOW_STRUCT(SCREEN_WINDOW);
        for (i = 0; i < windowStruct->children.length; i++) {
            destroyWindow(display, children[i], False);
        }
        SDL_DestroyRenderer(windowStruct->sdlRenderer);
        windowStruct->sdlRenderer = NULL;
        SDL_DestroyWindow(windowStruct->sdlWindow);
        freeArray(&windowStruct->children);
        free(windowStruct);
        FREE_XID(SCREEN_WINDOW);
        SCREEN_WINDOW = None;
    }
}

WindowSdlIdMapper* mappingListStart = NULL;

WindowSdlIdMapper* getWindowSdlIdMapperStructFromId(Uint32 sdlWindowId) {
    WindowSdlIdMapper* mapper;
    for (mapper = mappingListStart; mapper != NULL; mapper = mapper->next) {
        if (mapper->sdlWindowId == sdlWindowId) { return mapper; }
    }
    return NULL;
}

void deleteWindowMapping(Window window) {
    WindowSdlIdMapper* mapper = mappingListStart;
    if (mapper == NULL) {
        return;
    } else if (mapper->window == window) {
        mappingListStart = mapper->next;
        free(mapper);
        return;
    }
    for (; mapper->next != NULL; mapper = mapper->next) {
        if (mapper->next->window == window) {
            WindowSdlIdMapper* nextMapper = mapper->next;
            mapper->next = nextMapper->next;
            free(nextMapper);
            return;
        }
    }
}

void registerWindowMapping(Window window, Uint32 sdlWindowId) {
    WindowSdlIdMapper* mapper = getWindowSdlIdMapperStructFromId(sdlWindowId);
    if (mapper == NULL) {
        mapper = malloc(sizeof(WindowSdlIdMapper));
        if (mapper == NULL) {
            LOG("Failed to allocate mapping object to map xWindow to SDL window ID!\n");
            return;
        }
        mapper->next = mappingListStart;
        mappingListStart = mapper;
        mapper->sdlWindowId = sdlWindowId;
    }
    mapper->window = window;
}

Window getWindowFromId(Uint32 sdlWindowId) {
    WindowSdlIdMapper* mapper = getWindowSdlIdMapperStructFromId(sdlWindowId);
    LOG("Got window %lu for id %u\n", mapper == NULL ? None : mapper->window, sdlWindowId);
    return mapper == NULL ? None : mapper->window;
}

Window getContainingWindow(Window window, int x, int y) {
    int i, child_x, child_y, child_w, child_h;
    Window* children = GET_CHILDREN(window);
    for (i = GET_WINDOW_STRUCT(window)->children.length - 1; i >= 0 ; i--) {
        GET_WINDOW_POS(children[i], child_x, child_y);
        GET_WINDOW_DIMS(children[i], child_w, child_h);
        if (x >= child_x && x <= child_x + child_w && y >= child_y && y <= child_y + child_h) {
            return getContainingWindow(children[i], x - child_x, y - child_y);
        }
    }
    return window;
}

void removeChildFromParent(Window child) {
    if (child == SCREEN_WINDOW) { return; }
    Window parent = GET_PARENT(child);
    if (parent != None) {
        ssize_t childIndex = findInArray(&GET_WINDOW_STRUCT(parent)->children, (void *) child);
        if (childIndex != -1) {
            removeArray(&GET_WINDOW_STRUCT(parent)->children, (size_t) childIndex, True);
        }
    }
}

void destroyWindow(Display* display, Window window, Bool freeParentData) {
    size_t i;
    WindowStruct* windowStruct = GET_WINDOW_STRUCT(window);
    WARN_UNIMPLEMENTED;
    // if (windowStruct->mapState == Mapped) {
    //     XUnmapWindow(display, window);
    // }
    Window* children = GET_CHILDREN(window);
    for (i = 0; i < windowStruct->children.length; i++) {
        destroyWindow(display, children[i], False);
    }
    freeArray(&windowStruct->children);
    XFreeColormap(display, GET_COLORMAP(window));
    for (i = 0; i < windowStruct->properties.length; i++) {
        free(windowStruct->properties.array[i]);
    }
    freeArray(&windowStruct->properties);
    if (windowStruct->background != None) {
        XFreePixmap(display, windowStruct->background);
    }
    if (windowStruct->windowName != NULL) {
        free(windowStruct->windowName);
    }
    if (windowStruct->icon != NULL) {
        SDL_FreeSurface(windowStruct->icon);
    }
    if (windowStruct->sdlRenderer != NULL) {
        SDL_DestroyRenderer(windowStruct->sdlRenderer);
    }
    if (windowStruct->sdlTexture != NULL) {
        SDL_DestroyTexture(windowStruct->sdlTexture);
    }
    if (windowStruct->sdlWindow != NULL) {
        SDL_DestroyWindow(windowStruct->sdlWindow);
    }
    deleteWindowMapping(window);
    postEvent(display, window, DestroyNotify);
    if (freeParentData) {
        removeChildFromParent(window);
    }
    free(windowStruct);
    FREE_XID(window);
}

Bool addChildToWindow(Window parent, Window child) { // TODO: Check for duplicates?
    if (insertArray(&GET_WINDOW_STRUCT(parent)->children, (void *) child)) {
        GET_WINDOW_STRUCT(child)->parent = parent;
        return True;
    }
    return False;
}

Bool isParent(Window window1, Window window2) {
    Window parent = GET_PARENT(window2);
    while (parent != None) {
        if (parent == window1) {
            return True;
        }
        parent = GET_PARENT(parent);
    }
    return False;
}

WindowProperty* findProperty(Array* properties, Atom property, size_t* index) {
    size_t i;
    WindowProperty** windowProperties = (WindowProperty **) properties->array;
    for (i = 0; i < properties->length; i++) {
        if (windowProperties[i]->property == property) {
            if (index != NULL) *index = i;
            return windowProperties[i];
        }
    }
    return NULL;
}

void resizeWindowTexture(Window window) {
    WindowStruct* windowStruct = GET_WINDOW_STRUCT(window);
    if (windowStruct->sdlTexture != NULL) {
        SDL_Texture* oldTexture = windowStruct->sdlTexture;
        SDL_Rect destRect;
        destRect.x = 0;
        destRect.y = 0;
        SDL_QueryTexture(oldTexture, NULL, NULL, &destRect.w, &destRect.h);
        windowStruct->sdlTexture = NULL;
        SDL_Renderer* windowRenderer;
        GET_RENDERER(window, windowRenderer);
        SDL_RenderCopy(windowRenderer, oldTexture, NULL, &destRect);
        SDL_DestroyTexture(oldTexture);
    }
}

Bool mergeWindowDrawables(Window parent, Window child) {
    WindowStruct* childWindowStruct = GET_WINDOW_STRUCT(child);
    if (childWindowStruct->sdlTexture == NULL) { return True; }
    SDL_Renderer* parentRenderer = getWindowRenderer(parent);
    if (childWindowStruct->sdlRenderer != NULL) {
        SDL_RenderPresent(childWindowStruct->sdlRenderer);
    }
    SDL_Rect destRect;
    GET_WINDOW_POS(child, destRect.x, destRect.y);
    GET_WINDOW_DIMS(child, destRect.w, destRect.h);
    if (SDL_RenderCopy(parentRenderer, childWindowStruct->sdlTexture, NULL, &destRect) != 0) {
        return False;
    }
    SDL_DestroyTexture(childWindowStruct->sdlTexture);
    childWindowStruct->sdlTexture = NULL;
    if (childWindowStruct->sdlRenderer != NULL) {
        SDL_DestroyRenderer(childWindowStruct->sdlRenderer);
        childWindowStruct->sdlRenderer = NULL;
    }
    return True;
}

void mapRequestedChildren(Display* display, Window window) {
    Window* children = GET_CHILDREN(window);
    size_t i;
    for (i = 0; i < GET_WINDOW_STRUCT(window)->children.length; i++) {
        if (children[i] != None && GET_WINDOW_STRUCT(children[i])->mapState == MapRequested) {
            if (!mergeWindowDrawables(window, children[i])) {
                LOG("Failed to merge the window drawables in %s\n", __func__);
                return;
            }
            GET_WINDOW_STRUCT(children[i])->mapState = Mapped;
            postEvent(display, children[i], MapNotify);
            mapRequestedChildren(display, children[i]);
        }
    }
}

Bool configureWindow(Display* display, Window window, unsigned long value_mask, XWindowChanges* values) {
    if (window == SCREEN_WINDOW) return True;
    Bool hasChanged = False;
    WindowStruct* windowStruct = GET_WINDOW_STRUCT(window);
    if (!windowStruct->overrideRedirect && HAS_EVENT_MASK(GET_PARENT(window), SubstructureRedirectMask)) {
        return postEvent(display, window, ConfigureRequest, value_mask, values);
    }
    Bool isMappedTopLevelWindow = IS_MAPPED_TOP_LEVEL_WINDOW(window);
    int oldX, oldY, oldWidth, oldHeight;
    GET_WINDOW_POS(window, oldX, oldY);
    GET_WINDOW_DIMS(window, oldWidth, oldHeight);
    if (HAS_VALUE(value_mask, CWX) || HAS_VALUE(value_mask, CWY)) { 
        int x = oldX, y = oldY;
        if (HAS_VALUE(value_mask, CWX)) {
            x = values->x;
        }
        if (HAS_VALUE(value_mask, CWY)) {
            y = values->y;
        }
        if (isMappedTopLevelWindow) {
            SDL_SetWindowPosition(windowStruct->sdlWindow, x, y);
            SDL_GetWindowPosition(windowStruct->sdlWindow, &windowStruct->x, &windowStruct->y);
        } else {
            windowStruct->x = x;
            windowStruct->y = y;
        }
        if (oldX != windowStruct->x || oldY != windowStruct->y) {
            hasChanged = True;
        }
    }
    if (HAS_VALUE(value_mask, CWWidth) || HAS_VALUE(value_mask, CWHeight)) {
        int width = oldWidth, height = oldHeight;
        if (HAS_VALUE(value_mask, CWWidth)) {
            width = values->width;
            if (width <= 0) {
                handleError(0, display, None, 0, BadValue, 0);
                return False;
            }
        }
        if (HAS_VALUE(value_mask, CWHeight)) {
            height = values->height;
            if (height <= 0) {
                handleError(0, display, None, 0, BadValue, 0);
                return False;
            }
        }
        printWindowsHierarchy();
        LOG("Resizing window %lu to (%ux%u)\n", window, width, height);
        if (isMappedTopLevelWindow) {
            SDL_SetWindowSize(windowStruct->sdlWindow, width, height);
            int wOut, hOut;
            SDL_GetWindowSize(windowStruct->sdlWindow, &wOut, &hOut);
            windowStruct->w = (unsigned int) wOut;
            windowStruct->h = (unsigned int) hOut;
        } else {
            windowStruct->w = (unsigned int) width;
            windowStruct->h = (unsigned int) height;
        }
        if (oldWidth != windowStruct->w || oldHeight != windowStruct->h) {
            resizeWindowTexture(window);
            hasChanged = True;
        }
    }
    if (!hasChanged) return True;
    if (!postEvent(display, window, ConfigureNotify)) {
        return False;
    }
    if (windowStruct->mapState != UnMapped && (oldX != windowStruct->x || oldY != windowStruct->y
        || oldWidth != windowStruct->w || oldHeight != windowStruct->h)) {
        SDL_Rect exposedRect;  // TODO: Handle whe window shrinks or moves, update parent
        if (oldX != windowStruct->x || oldY != windowStruct->y) {
            exposedRect.x = 0;
            exposedRect.y = 0;
            exposedRect.w = windowStruct->w;
            exposedRect.h = windowStruct->h;
        } else {
            exposedRect.x = 0;
            exposedRect.y = 0;
            exposedRect.w = windowStruct->w;
            exposedRect.h = windowStruct->h;// TODO Calculate exposed rect
        }
        postExposeEvent(display, window, &exposedRect, 1);
    }
    return True;
    // TODO: Implement re-stacking: https://tronche.com/gui/x/xlib/window/configure.html#XWindowChanges
}
