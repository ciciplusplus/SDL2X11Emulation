#include <math.h>
#define XLIB_ILLEGAL_ACCESS
#include "xprivatedisplay.h"
#include "X11/Xutil.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "window.h"
#include "errors.h"
#include "events.h"
#include "colors.h"
#include "drawing.h"
#include "display.h"
#include "atoms.h"
#include "visual.h"
#include "font.h"
#include <X11/X.h>
#include <X11/Xutil.h>
#include <limits.h>

// src/OpenDis.c
#include "X11/locking.h"
int  (*_XInitDisplayLock_fn)(Display *dpy) = NULL;
void (*_XFreeDisplayLock_fn)(Display *dpy) = NULL;

#define InitDisplayLock(d)	(_XInitDisplayLock_fn ? (*_XInitDisplayLock_fn)(d) : Success)
#define FreeDisplayLock(d)	if (_XFreeDisplayLock_fn) (*_XFreeDisplayLock_fn)(d)

// void __attribute__((constructor)) _init() {
//     setenv("DISPLAY", ":0", 0);
// }

int numDisplaysOpen = 0;
// TODO: or SDL_GetCurrentVideoDriver
static char* vendor = "SDL " TO_STRING(SDL_MAJOR_VERSION) "." TO_STRING(SDL_MINOR_VERSION)
                      "."  TO_STRING(SDL_PATCHLEVEL);
static const int releaseVersion = 1;

int XCloseDisplay(Display* display) {
    // https://tronche.com/gui/x/xlib/display/XCloseDisplay.html
    if (numDisplaysOpen == 1) {
        freeAtomStorage();
        freeFontStorage();
        TTF_Quit();
        SDL_Quit();
        destroyScreenWindow(display);
        freeVisuals();
    }
    if (numDisplaysOpen > 0) {
        numDisplaysOpen--;
    }
    if (GET_DISPLAY(display)->nscreens > 0) {
        free(GET_DISPLAY(display)->screens);
    }
    free(display);
    return 0;
}

Display* XOpenDisplay(_Xconst char* display_name) {
    setenv("DISPLAY", ":0", 0);

    // https://tronche.com/gui/x/xlib/display/opening.html
    _MyXDisplay* display = malloc(sizeof(_MyXDisplay));
    if (display == NULL) {
        LOG("Out of memory: Failed to allocate memory for Display struct in XOpenDisplay!");
        return NULL;
    }
    if (!SDL_WasInit(SDL_INIT_VIDEO)) {
        SDL_SetMainReady();
        if (SDL_Init(SDL_INIT_VIDEO) == -1) {
            LOG("Failed to initialize SDL: %s\n", SDL_GetError());
            free(display);
            return NULL;
        }
//        SDL_SetHintWithPriority("SDL_HINT_ANDROID_SEPARATE_MOUSE_AND_TOUCH", "0", SDL_HINT_OVERRIDE);
    }
    if (!TTF_WasInit()) {
        if (TTF_Init() == -1) {
            LOG("Failed to initialize SDL_TTF: %s\n", TTF_GetError());
            free(display);
            return NULL;
        }
    }
    if (numDisplaysOpen == 0) {
         if (!(initVisuals() && initFontStorage())) {
             free(display);
             return NULL;
         }
    }
    numDisplaysOpen++;

    display->keysyms		= (KeySym *) NULL;
    display->modifiermap	= NULL;
    display->lock_meaning	= NoSymbol;
    display->keysyms_per_keycode = 0;
    display->xdefaults		= (char *)NULL;
    display->scratch_length	= 0L;
    display->scratch_buffer	= NULL;
    display->key_bindings	= NULL;
    display->ext_procs		= NULL;
    display->ext_data		= (XExtData *)NULL;
    display->ext_number 	= 0;
//    display->event_vec[X_Error] = _XUnknownWireEvent;
//    display->event_vec[X_Reply] = _XUnknownWireEvent;
//    display->wire_vec[X_Error]  = _XUnknownNativeEvent;
//    display->wire_vec[X_Reply]  = _XUnknownNativeEvent;
//    for (int i = KeyPress; i < LASTEvent; i++) {
//        display->event_vec[i] 	= _XWireToEvent;
//        display->wire_vec[i] 	= NULL;
//    }
//    for (int i = LASTEvent; i < 128; i++) {
//        display->event_vec[i] 	= _XUnknownWireEvent;
//        display->wire_vec[i] 	= _XUnknownNativeEvent;
//    }
    display->resource_id	= 0;
    display->db 		= (struct _XrmHashBucketRec *)NULL;
    display->cursor_font	= None;
    display->flags		= 0;
    display->async_handlers	= NULL;
    display->screens		= NULL;
    display->vendor		= NULL;
    display->buffer		= NULL;
    display->atoms		= NULL;
    display->error_vec		= NULL;
    display->context_db		= NULL;
    display->free_funcs		= NULL;
    display->pixmap_format	= NULL;
    display->cms.clientCmaps	= NULL;
    display->cms.defaultCCCs	= NULL;
    display->cms.perVisualIntensityMaps = NULL;
    display->im_filters		= NULL;
    display->bigreq_size	= 0;
    display->lock		= NULL;
    display->lock_fns		= NULL;
    display->qfree		= NULL;
    display->next_event_serial_num = 1;
    display->im_fd_info		= NULL;
    display->im_fd_length	= 0;
    display->conn_watchers	= NULL;
    display->watcher_count	= 0;
    display->filedes		= NULL;
    display->flushes		= NULL;
    display->xcmisc_opcode	= 0;
    display->xkb_info		= NULL;
    
    display->qlen = 0;
    int eventFd = initEventPipe(display);
    if (eventFd < 0) {
        display->nscreens = 0;
        XCloseDisplay(display);
        return NULL;
    }
    display->fd = eventFd;
    display->proto_major_version = X_PROTOCOL;
    display->proto_minor_version = X_PROTOCOL_REVISION;
    display->vendor = vendor;
    display->release = releaseVersion;
    display->request = X_NoOperation;
    display->min_keycode = 8;
    display->max_keycode = 255;
    display->display_name = (char*) display_name;
    display->byte_order = SDL_BYTEORDER == SDL_BIG_ENDIAN ? MSBFirst : LSBFirst;
    display->default_screen = 0; // TODO: Investigate here, see SDL_GetCurrentVideoDisplay();
    display->nscreens = SDL_GetNumVideoDisplays();
    if (display->nscreens < 0) {
        LOG("Failed to get the number of screens: %s\n", SDL_GetError());
        XCloseDisplay(display);
        return NULL;
    }
    display->screens = malloc(sizeof(Screen) * display->nscreens);
    if (display->screens == NULL) {
        LOG("Failed to get the number of screens: %s\n", SDL_GetError());
        XCloseDisplay(display);
        return NULL;
    }

    /* Initialize the display lock */
    if (InitDisplayLock(display) != 0) {
        LOG("Failed to InitDisplayLock\n");
        return NULL;
    }

    if ((display->free_funcs = Xcalloc(1, sizeof(_XFreeFuncRec))) == NULL) {
        //OutOfMemory (dpy);
        LOG("OutOfMemory free_funcs\n");
        return NULL;
    }

    int screenIndex;
    for (screenIndex = 0; screenIndex < display->nscreens; screenIndex++) {
        Screen* screen = &display->screens[screenIndex];
        SDL_DisplayMode displayMode;
        if (SDL_GetDesktopDisplayMode(screenIndex, &displayMode) != 0) {
            XCloseDisplay(display);
            LOG("Failed to get the display mode in XOpenDisplay: %s\n", SDL_GetError());
            return NULL;
        }
        screen->display = display;
        screen->width   = displayMode.w;
        screen->height  = displayMode.h;
        #if SDL_VERSION_ATLEAST(2, 0, 4)
        // Calculate the values in millimeters
        float h_dpi, v_dpi;
        if (SDL_GetDisplayDPI(screenIndex, NULL, &h_dpi, &v_dpi) != 0) {
            LOG("Warning: SDL_GetDisplayDPI failed, "
                            "using pixel values for mm values: %s\n", SDL_GetError());
            screen->mwidth  = displayMode.w;
            screen->mheight = displayMode.h;
        } else {
            screen->mwidth  = (int) roundf((displayMode.w * 25.4f) / v_dpi);
            screen->mheight = (int) roundf((displayMode.h * 25.4f) / h_dpi);
        }
        #else
        screen->mwidth  = displayMode.w;
        screen->mheight = displayMode.h;
        #endif
        screen->root = SCREEN_WINDOW;
        screen->root_visual = getDefaultVisual(screenIndex);
        // TODO: Need real values here (use from visual)
        screen->root_depth = 32;
        screen->white_pixel = 0xFFFFFFFF;
        screen->black_pixel = 0x000000FF;
        screen->cmap = REAL_COLOR_COLORMAP;
    }
    if (SCREEN_WINDOW == None) {
        if (initScreenWindow(display) != True) {
            LOG("XOpenDisplay: Initializing the screen window failed!\n");
            XCloseDisplay(display);
            return NULL;
        }
        for (screenIndex = 0; screenIndex < display->nscreens; screenIndex++) {
            display->screens[screenIndex].root = SCREEN_WINDOW;

            // FIXME: what is correct way to init default gc?
            display->screens[screenIndex].default_gc = XCreateGC(display, RootWindow(display, 0), 0, 0);
        }
    }
//     GET_WINDOW_STRUCT(SCREEN_WINDOW)->sdlWindow = SDL_CreateWindow(NULL, 0, 0, 320, 240, SDL_WINDOW_SHOWN);
//     if (GET_WINDOW_STRUCT(SCREEN_WINDOW)->sdlWindow == NULL) {
//         LOG("XOpenDisplay: Initializing the SDL screen window failed: %s!\n", SDL_GetError());
//         XCloseDisplay(display);
//         return NULL;
//     }
//     GET_WINDOW_STRUCT(SCREEN_WINDOW)->sdlRenderer = SDL_CreateRenderer(GET_WINDOW_STRUCT(SCREEN_WINDOW)->sdlWindow , -1, SDL_RENDERER_SOFTWARE);
//     if (GET_WINDOW_STRUCT(SCREEN_WINDOW)->sdlRenderer == NULL) {
//         LOG("XOpenDisplay: Initializing SDL renderer failed!\n");
//         XCloseDisplay(display);
//         return NULL;
//     }
    if (numDisplaysOpen == 1) {
        // Init the font search path
        XSetFontPath(display, NULL, 0);
    }
    return display;
}

int XBell(Display* display, int percent) {
    // https://tronche.com/gui/x/xlib/input/XBell.html
    SET_X_SERVER_REQUEST(display, X_Bell);
    if (-100 > percent || 100 < percent) {
        handleError(0, display, None, 0, BadValue, 0);
    } else {
        // TODO: Should it be implemented with audio or haptic feedback?
        printf("\a");
        fflush(stdout);
    }
    return 1;
}

int XSync(Display *display, Bool discard) {
    // https://tronche.com/gui/x/xlib/event-handling/XSync.html
    //WARN_UNIMPLEMENTED;
    drawWindowDataToScreen();
    return 1;
}

int XConvertSelection(Display* display, Atom selection, Atom target, Atom property,
                       Window requestor, Time time) {
    // https://tronche.com/gui/x/xlib/window-information/XConvertSelection.html
    // http://www.man-online.org/page/3-XConvertSelection/
    SET_X_SERVER_REQUEST(display, X_ConvertSelection);
    //WARN_UNIMPLEMENTED;
    return 1;
}

int XSetSelectionOwner(Display *display, Atom selection, Window owner, Time time) {
    // https://tronche.com/gui/x/xlib/window-information/XSetSelectionOwner.html
    SET_X_SERVER_REQUEST(display, X_SetSelectionOwner);
    WARN_UNIMPLEMENTED;
    return 1;
}

int XNoOp(Display *display) {
    // https://tronche.com/gui/x/xlib/display/XNoOp.html
    SET_X_SERVER_REQUEST(display, X_NoOperation);
    return 1;
}

int XGrabServer(Display *display) {
    // https://tronche.com/gui/x/xlib/window-and-session-manager/XGrabServer.html
    SET_X_SERVER_REQUEST(display, X_GrabServer);
    WARN_UNIMPLEMENTED;
    return 1;
}

int XUngrabServer(Display *display) {
    // https://tronche.com/gui/x/xlib/window-and-session-manager/XUngrabServer.html
    SET_X_SERVER_REQUEST(display, X_UngrabServer);
    WARN_UNIMPLEMENTED;
    return 1;
} 

XHostAddress* XListHosts(Display *display, int *nhosts_return, Bool *state_return) {
    // https://tronche.com/gui/x/xlib/window-and-session-manager/controlling-host-access/XListHosts.html
    SET_X_SERVER_REQUEST(display, X_ListHosts);
    const static char* LOCAL_HOST = "127.0.0.1";
    *state_return = True;
    XHostAddress* host = malloc(sizeof(XHostAddress));
    if (host == NULL) {
        *nhosts_return = 0;
        return NULL;
    }
    *nhosts_return = 1;
    host->address = (char *) LOCAL_HOST;
    host->length = strlen(LOCAL_HOST);
    host->family = FamilyInternet;
    return host;
}

#define BOOL long
#define SIGNEDINT long
#define UNSIGNEDINT unsigned long
#define RESOURCEID unsigned long

/* this structure may be extended, but do not change the order */
typedef struct {
    UNSIGNEDINT flags;
    BOOL input;				/* need to convert */
    SIGNEDINT initialState;		/* need to cvt */
    RESOURCEID iconPixmap;
    RESOURCEID iconWindow;
    SIGNEDINT  iconX;			/* need to cvt */
    SIGNEDINT  iconY;			/* need to cvt */
    RESOURCEID iconMask;
    UNSIGNEDINT windowGroup;
} xPropWMHints;
#define NumPropWMHintsElements 9 /* number of elements in this structure */

#undef BOOL
#undef SIGNEDINT
#undef UNSIGNEDINT
#undef RESOURCEID

int
XSetWMHints (
        Display *dpy,
        Window w,
        XWMHints *wmhints)
{
    xPropWMHints prop;
    memset(&prop, 0, sizeof(prop));
    prop.flags = wmhints->flags;
    if (wmhints->flags & InputHint)
        prop.input = (wmhints->input == True ? 1 : 0);
    if (wmhints->flags & StateHint)
        prop.initialState = wmhints->initial_state;
    if (wmhints->flags & IconPixmapHint)
        prop.iconPixmap = wmhints->icon_pixmap;
    if (wmhints->flags & IconWindowHint)
        prop.iconWindow = wmhints->icon_window;
    if (wmhints->flags & IconPositionHint) {
        prop.iconX = wmhints->icon_x;
        prop.iconY = wmhints->icon_y;
    }
    if (wmhints->flags & IconMaskHint)
        prop.iconMask = wmhints->icon_mask;
    if (wmhints->flags & WindowGroupHint)
        prop.windowGroup = wmhints->window_group;
    return XChangeProperty (dpy, w, XA_WM_HINTS, XA_WM_HINTS, 32,
                            PropModeReplace, (unsigned char *) &prop,
                            NumPropWMHintsElements);
}

int XSetCommand(Display *display, Window w, char **argv, int argc) {
    // https://tronche.com/gui/x/xlib/ICC/client-to-session-manager/XSetCommand.html
    WARN_UNIMPLEMENTED;
    return 1;
}

#define BOOL long
#define SIGNEDINT long
#define UNSIGNEDINT unsigned long
#define RESOURCEID unsigned long

/* this structure may be extended, but do not change the order */
typedef struct {
    UNSIGNEDINT flags;
    SIGNEDINT x, y, width, height;	/* need to cvt; only for pre-ICCCM */
    SIGNEDINT minWidth, minHeight;	/* need to cvt */
    SIGNEDINT maxWidth, maxHeight;	/* need to cvt */
    SIGNEDINT widthInc, heightInc;	/* need to cvt */
    SIGNEDINT minAspectX, minAspectY;	/* need to cvt */
    SIGNEDINT maxAspectX, maxAspectY;	/* need to cvt */
    SIGNEDINT baseWidth,baseHeight;	/* need to cvt; ICCCM version 1 */
    SIGNEDINT winGravity;		/* need to cvt; ICCCM version 1 */
} xPropSizeHints;
#define OldNumPropSizeElements 15	/* pre-ICCCM */
#define NumPropSizeElements 18		/* ICCCM version 1 */

#undef BOOL
#undef SIGNEDINT
#undef UNSIGNEDINT
#undef RESOURCEID

void XSetWMSizeHints (
        Display *dpy,
        Window w,
        XSizeHints *hints,
        Atom prop)
{
    xPropSizeHints data;

    memset(&data, 0, sizeof(data));
    data.flags = (hints->flags &
                  (USPosition|USSize|PPosition|PSize|PMinSize|PMaxSize|
                   PResizeInc|PAspect|PBaseSize|PWinGravity));

    /*
     * The x, y, width, and height fields are obsolete; but, applications
     * that want to work with old window managers might set them.
     */
    if (hints->flags & (USPosition|PPosition)) {
        data.x = hints->x;
        data.y = hints->y;
    }
    if (hints->flags & (USSize|PSize)) {
        data.width = hints->width;
        data.height = hints->height;
    }

    if (hints->flags & PMinSize) {
        data.minWidth = hints->min_width;
        data.minHeight = hints->min_height;
    }
    if (hints->flags & PMaxSize) {
        data.maxWidth  = hints->max_width;
        data.maxHeight = hints->max_height;
    }
    if (hints->flags & PResizeInc) {
        data.widthInc = hints->width_inc;
        data.heightInc = hints->height_inc;
    }
    if (hints->flags & PAspect) {
        data.minAspectX = hints->min_aspect.x;
        data.minAspectY = hints->min_aspect.y;
        data.maxAspectX = hints->max_aspect.x;
        data.maxAspectY = hints->max_aspect.y;
    }
    if (hints->flags & PBaseSize) {
        data.baseWidth = hints->base_width;
        data.baseHeight = hints->base_height;
    }
    if (hints->flags & PWinGravity) {
        data.winGravity = hints->win_gravity;
    }

    XChangeProperty (dpy, w, prop, XA_WM_SIZE_HINTS, 32,
                     PropModeReplace, (unsigned char *) &data,
                     NumPropSizeElements);
}


void XSetWMNormalHints (
        Display *dpy,
        Window w,
        XSizeHints *hints)
{
    XSetWMSizeHints (dpy, w, hints, XA_WM_NORMAL_HINTS);
}

int XSetClassHint(Display *display, Window w, XClassHint *class_hints) {
    // https://tronche.com/gui/x/xlib/ICC/client-to-window-manager/XSetClassHint.html
    WARN_UNIMPLEMENTED;
    return 1;
}

Status XStringListToTextProperty(char **list, int count, XTextProperty *text_prop_return) {
    // https://tronche.com/gui/x/xlib/ICC/client-to-window-manager/XStringListToTextProperty.html
    size_t i;
    text_prop_return->format = 8; // STRING
    text_prop_return->encoding = XA_STRING;
    text_prop_return->nitems = 1;
    for (i = 0; i < count; i++) {
        text_prop_return->nitems += strlen(list[i]);
    }
    text_prop_return->value = malloc(sizeof(char) * text_prop_return->nitems);
    if (text_prop_return->value == NULL) {
        text_prop_return->nitems = 0;
        return 0;
    }
    text_prop_return->value[0] = '\0';
    for (i = 0; i < count; i++) {
        strcat((char *) text_prop_return->value, list[i]);
    }
    return 1;
}

void XSetWMClientMachine (
        Display *dpy,
        Window w,
        XTextProperty *tp)
{
    XSetTextProperty (dpy, w, tp, XA_WM_CLIENT_MACHINE);
}

#define safestrlen(s) ((s) ? strlen(s) : 0)

int
XSetSizeHints(		/* old routine */
        Display *dpy,
        Window w,
        XSizeHints *hints,
        Atom property)
{
    xPropSizeHints prop;
    memset(&prop, 0, sizeof(prop));
    prop.flags = (hints->flags & (USPosition|USSize|PAllHints));
    if (hints->flags & (USPosition|PPosition)) {
        prop.x = hints->x;
        prop.y = hints->y;
    }
    if (hints->flags & (USSize|PSize)) {
        prop.width = hints->width;
        prop.height = hints->height;
    }
    if (hints->flags & PMinSize) {
        prop.minWidth = hints->min_width;
        prop.minHeight = hints->min_height;
    }
    if (hints->flags & PMaxSize) {
        prop.maxWidth  = hints->max_width;
        prop.maxHeight = hints->max_height;
    }
    if (hints->flags & PResizeInc) {
        prop.widthInc = hints->width_inc;
        prop.heightInc = hints->height_inc;
    }
    if (hints->flags & PAspect) {
        prop.minAspectX = hints->min_aspect.x;
        prop.minAspectY = hints->min_aspect.y;
        prop.maxAspectX = hints->max_aspect.x;
        prop.maxAspectY = hints->max_aspect.y;
    }
    return XChangeProperty (dpy, w, property, XA_WM_SIZE_HINTS, 32,
                            PropModeReplace, (unsigned char *) &prop,
                            OldNumPropSizeElements);
}

/*
 * XSetNormalHints sets the property
 *	WM_NORMAL_HINTS 	type: WM_SIZE_HINTS format: 32
 */

int
XSetNormalHints (			/* old routine */
        Display *dpy,
        Window w,
        XSizeHints *hints)
{
    return XSetSizeHints (dpy, w, hints, XA_WM_NORMAL_HINTS);
}

/*
 * XSetStandardProperties sets the following properties:
 *	WM_NAME		  type: STRING		format: 8
 *	WM_ICON_NAME	  type: STRING		format: 8
 *	WM_HINTS	  type: WM_HINTS	format: 32
 *	WM_COMMAND	  type: STRING
 *	WM_NORMAL_HINTS	  type: WM_SIZE_HINTS 	format: 32
 */

int
XSetStandardProperties (
        Display *dpy,
        Window w,		/* window to decorate */
        _Xconst char *name,	/* name of application */
        _Xconst char *icon_string,/* name string for icon */
        Pixmap icon_pixmap,	/* pixmap to use as icon, or None */
        char **argv,		/* command to be used to restart application */
        int argc,		/* count of arguments */
        XSizeHints *hints)	/* size hints for window in its normal state */
{
    XWMHints phints;
    phints.flags = 0;

    if (name != NULL) XStoreName (dpy, w, name);

    if (safestrlen(icon_string) >= USHRT_MAX)
        return 1;
    if (icon_string != NULL) {
        XChangeProperty (dpy, w, XA_WM_ICON_NAME, XA_STRING, 8,
                         PropModeReplace,
                         (_Xconst unsigned char *)icon_string,
                         (int)safestrlen(icon_string));
    }

    if (icon_pixmap != None) {
        phints.icon_pixmap = icon_pixmap;
        phints.flags |= IconPixmapHint;
    }
    if (argv != NULL) XSetCommand(dpy, w, argv, argc);

    if (hints != NULL) XSetNormalHints(dpy, w, hints);

    if (phints.flags != 0) XSetWMHints(dpy, w, &phints);

    return 1;
}