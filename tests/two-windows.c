#include <X11/Xlib.h>
#include <stdlib.h>

static void create_x_window(Display *display, Window *win, int width, int height, unsigned long background)
{
    int screen_num = DefaultScreen(display);
    //unsigned long background = WhitePixel(display, screen_num);
    unsigned long border = BlackPixel(display, screen_num);
    *win = XCreateSimpleWindow(display, DefaultRootWindow(display), /* display, parent */
                               0,0, /* x, y */
                               width, height, /* width, height */
                               2, border, /* border width & colour */
                               background); /* background colour */
    XSelectInput(display, *win, ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask);
    XMapWindow(display, *win);

}

int main(void) {
    XInitThreads(); // prevent threaded XIO errors
    Display *local_display = XOpenDisplay(":0.0");

    Window self_win, remote_win;
    XEvent self_event, remote_event;

    int s = DefaultScreen(local_display);
    GC gc = DefaultGC(local_display, s);

    create_x_window(local_display, &remote_win, 320,240, rand());
    //XSetForeground(local_display, gc, 255);
    //XFillRectangle(local_display, remote_win, gc, 20, 20, 10, 10);
    //while(XPending(local_display)) { XNextEvent(local_display, &remote_event); };

    create_x_window(local_display, &self_win, 160, 120, rand());
    //while(XPending(local_display)) { XNextEvent(local_display, &self_event); };

    //XFlush(local_display);

    //while (1) { XFlush(local_display); }

    XEvent e;
    while (1) {
        XNextEvent(local_display, &e);
        if (e.type == Expose) {
            XSetForeground(local_display, gc, 255);
            XFillRectangle(local_display, remote_win, gc, 20, 20, 10, 10);
            XFillRectangle(local_display, self_win, gc, 30, 30, 10, 10);
            XFlush(local_display);
        }
        if (e.type == KeyPress)
            break;
    }

    XCloseDisplay(local_display);
    return 0;
}