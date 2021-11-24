/* key.c */

/* mapping keycode-keysym */

// from https://www.u-picardie.fr/ferment/xwindow/key.htm

#include <stdio.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

GC      gc;
Display *display;
int     screen;
Window  win, root;
unsigned long white_pixel, black_pixel;
int nbre_keysym, i, minkc, maxkc, nbrekc;

main() {
    display = XOpenDisplay ("");
    XDisplayKeycodes (display, &minkc, &maxkc);
    nbrekc = maxkc - minkc + 1 ;
    printf("%d keycodes de %d a %d\n", nbrekc, minkc, maxkc);
    XGetKeyboardMapping(display, minkc, nbrekc, &nbre_keysym);
    printf("nombre maximal de keysyms par keycode : %d\n", nbre_keysym);
    screen = DefaultScreen (display);
    gc = DefaultGC (display, screen);
    root = RootWindow (display, screen);
    white_pixel = WhitePixel (display, screen);
    black_pixel = BlackPixel (display, screen);
    win = XCreateSimpleWindow (display, root, 0, 0,
                               200, 50, 2, black_pixel, white_pixel);
    XSelectInput (display, win, ExposureMask | ButtonPressMask | KeyPressMask);
    XStoreName (display, win, "key");
    XMapRaised (display, win);

    for (;;) {
        XEvent ev;
        KeySym touche, keysym;
        char caractere[10], modifiers[40];
        int nbre;

        XNextEvent (display, &ev);
        switch (ev.type) {
            case Expose :
                XDrawString (display, win, gc, 10, 10,
                             "Enfoncez une touche du clavier", 30);
                XDrawString (display, win, gc, 10, 25,
                             "avec touches modifiers ou sans", 30);
                break;
//            case ButtonPress :
//                exit(0);
            case KeyPress :
                nbre = XLookupString(&ev, caractere, 10, &touche, 0);
                caractere[nbre] = '\0';
                printf("Le keycode est %d (0x%x), le keysym est %d (0x%x)\n",
                       ev.xkey.keycode, ev.xkey.keycode,
                       XKeysymToString(touche), touche);
                if (nbre == 0)
                    printf("La chaine ascii correspondante est vide\n");
                else
                    printf("La chaine ascii obtenue est %s\n", caractere);
                modifiers[0] = '\0';
                if (ev.xkey.state & ShiftMask)
                    strcat(modifiers, "Shift ");
                if (ev.xkey.state & LockMask)
                    strcat(modifiers, "Lock ");
                if (ev.xkey.state & ControlMask)
                    strcat(modifiers, "Control ");
                if (ev.xkey.state & Mod1Mask)
                    strcat(modifiers, "Mod1 ");
                if (ev.xkey.state & Mod2Mask)
                    strcat(modifiers, "Mod2 ");
                if (ev.xkey.state & Mod3Mask)
                    printf("Aucun modifier actif\n");
                else
                    printf("Modifiers actifs %s\n", modifiers);
                printf("Les keysyms associes : ");
                for (i = 0; i <nbre_keysym ; ++i) {
                    if ((keysym = XKeycodeToKeysym(display, ev.xkey.keycode, i))
                        == NoSymbol)
                        printf("NoSymbol ");
                    else
                        printf("%s ", XKeysymToString(keysym));
                }
                printf("\n\n");
                break;
            default :
                break;
        }
    }
}