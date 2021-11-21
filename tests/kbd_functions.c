#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
    Display *display;

    /* open connection with the server */
    display = XOpenDisplay(NULL);
    if (display == NULL)
    {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    int min_keycode, max_keycode, keysyms_per_keycode;
    KeySym *keymap;
    XDisplayKeycodes(display, &min_keycode, &max_keycode);

    printf("min keycode %d, max keycode %d\n", min_keycode, max_keycode);

    keymap = XGetKeyboardMapping(display, min_keycode, max_keycode - min_keycode + 1, &keysyms_per_keycode);

    for (int i = min_keycode; i <= max_keycode; i++)
    {
        for (int j = 0; j < keysyms_per_keycode; j++)
        {
            KeySym ks = keymap[j];
            if (ks != NoSymbol) {
                printf("keycode %d offset %d keysym %s\n", i, j, XKeysymToString(ks));
                assert(ks == XStringToKeysym(XKeysymToString(ks)));
            }
        }
        keymap += keysyms_per_keycode;
    }

    /* close connection to server */
    XCloseDisplay(display);

    return 0;
}