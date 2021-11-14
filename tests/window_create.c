#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    Display *d;
    Window w;
    XEvent e;
    const char *msg = "Hello, World!";
    int s;

    d = XOpenDisplay(NULL);
    if (d == NULL) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    s = DefaultScreen(d);
    //w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 100, 100, 1,
    //                        BlackPixel(d, s), WhitePixel(d, s));
    w = XCreateWindow(d, DefaultRootWindow(d), 10, 10,
                      100, 100, 1, CopyFromParent, CopyFromParent, CopyFromParent, 0, NULL);
    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapWindow(d, w);

    while (1) {
        XNextEvent(d, &e);
        if (e.type == Expose) {
            XSetForeground(d, DefaultGC(d, s), 255);
            XFillRectangle(d, w, DefaultGC(d, s), 20, 20, 10, 10);
            XFillRectangle(d, w, DefaultGC(d, s), 30, 30, 10, 10);
            XFillRectangle(d, w, DefaultGC(d, s), 40, 40, 10, 10);
            XDrawString(d, w, DefaultGC(d, s), 10, 50, msg, strlen(msg));
            XDrawString(d, w, DefaultGC(d, s), 20, 60, msg, strlen(msg));
        }
        if (e.type == KeyPress)
            break;
    }

    XCloseDisplay(d);
    return 0;
}