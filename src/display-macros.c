#include "X11/Xlib.h"

unsigned long XBlackPixel(
        Display *display,
        int screen_number
) { return BlackPixel(display, screen_number); }

unsigned long XWhitePixel(
        Display *display,
        int screen_number
) { return WhitePixel(display, screen_number); }

int XConnectionNumber(
        Display *display
) { return ConnectionNumber(display); }

Colormap XDefaultColormap(
        Display *display,
        int screen_number
) { return DefaultColormap(display, screen_number); }

int XDefaultDepth(
        Display *display,
        int screen_number
) { return DefaultDepth(display, screen_number); }

GC XDefaultGC(
        Display *display,
        int screen_number
) { return DefaultGC(display, screen_number); }

Window XDefaultRootWindow(
        Display *display
) { return DefaultRootWindow(display); }

Screen *XDefaultScreenOfDisplay(
        Display *display
) { return DefaultScreenOfDisplay(display); }

int XDefaultScreen(
        Display *display
) { return DefaultScreen(display); }

Visual *XDefaultVisual(
        Display *display,
        int screen_number
) { return DefaultVisual(display, screen_number); }

int XDisplayCells(
        Display *display,
        int screen_number
) { return DisplayCells(display, screen_number); }

int XDisplayPlanes(
        Display *display,
        int screen_number
) { return DisplayPlanes(display, screen_number); }

char *XDisplayString(
        Display *display
) { return DisplayString(display); }

unsigned long XLastKnownRequestProcessed(
        Display *display
) { return LastKnownRequestProcessed(display); }

unsigned long XNextRequest(
        Display *display
) { return NextRequest(display); }

int XProtocolVersion(
        Display *display
) { return ProtocolVersion(display); }

int XProtocolRevision(
        Display *display
) { return ProtocolRevision(display); }

int XQLength(
        Display *display
) { return QLength(display); }

Window XRootWindow(
        Display *display,
        int screen_number
) { return RootWindow(display, screen_number); }

int XScreenCount(
        Display *display
) { return ScreenCount(display); }

char *XServerVendor(
        Display *display
) { return ServerVendor(display); }

int XVendorRelease(
        Display *display
) { return VendorRelease(display); }

