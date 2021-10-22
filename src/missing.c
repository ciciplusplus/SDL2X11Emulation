#include "X11/Xlibint.h"
#include "X11/Xresource.h"
#include "X11/Xutil.h"
#include <stdio.h>

Window XGetSelectionOwner( register Display *dpy, Atom selection) { printf("CALL XGetSelectionOwner\n"); }

Status XInternAtoms ( Display *dpy, char **names, int count, Bool onlyIfExists, Atom *atoms_return) { printf("CALL XInternAtoms\n"); }

void XSetTextProperty ( Display *dpy, Window w, XTextProperty *tp, Atom property) { printf("CALL XSetTextProperty\n"); }

void XSetWMName ( Display *dpy, Window w, XTextProperty *tp) { printf("CALL XSetWMName\n"); }

void XSetWMIconName ( Display *dpy, Window w, XTextProperty *tp) { printf("CALL XSetWMIconName\n"); }

int XClearWindow ( Display* dpy, Window w) { return XClearArea(dpy, w, 0, 0, 0, 0, False); }

int XClearArea ( register Display *dpy, Window w, int x, int y, unsigned int width, unsigned int height, Bool exposures) { printf("CALL XClearArea\n");  return -1; }

long XMaxRequestSize(Display *dpy) { printf("CALL XMaxRequestSize\n");  return -1; }

int XDisplayKeycodes( Display *dpy, int *min_keycode_return, int *max_keycode_return) { printf("CALL XDisplayKeycodes\n");  return -1; }

long XExtendedMaxRequestSize(Display *dpy) { printf("CALL XExtendedMaxRequestSize\n");  return -1; }

Status XAllocColorCells( register Display *dpy, Colormap cmap, Bool contig, unsigned long *masks, /* LISTofCARD32 */ /* RETURN */ unsigned int nplanes, /* CARD16 */ unsigned long *pixels, /* LISTofCARD32 */ /* RETURN */ unsigned int ncolors) /* CARD16 */ { printf("CALL XAllocColorCells\n"); }

int XQueryColor( register Display *dpy, Colormap cmap, XColor *def) /* RETURN */ { printf("CALL XQueryColor\n");  return -1; }

int XSetBackground ( register Display *dpy, GC gc, unsigned long background) /* CARD32 */ { printf("CALL XSetBackground\n");  return -1; }

void XLockDisplay( register Display* dpy) { printf("CALL XLockDisplay\n"); }

void XUnlockDisplay( register Display* dpy) { printf("CALL XUnlockDisplay\n"); }

Bool XCheckTypedWindowEvent ( register Display *dpy, Window w, /* Selected window. */ int type, /* Selected event type. */ register XEvent *event) /* XEvent to be filled in. */ { printf("CALL XCheckTypedWindowEvent\n");  return False; }

int XSetFunction ( register Display *dpy, GC gc, int function) { printf("CALL XSetFunction\n");  return -1; }

int XSetArcMode ( register Display *dpy, register GC gc, int arc_mode) { printf("CALL XSetArcMode\n");  return -1; }

int XSetFillStyle ( register Display *dpy, register GC gc, int fill_style) { printf("CALL XSetFillStyle\n");  return -1; }

int XSetGraphicsExposures ( register Display *dpy, register GC gc, Bool graphics_exposures) { printf("CALL XSetGraphicsExposures\n");  return -1; }

int XSetSubwindowMode ( register Display *dpy, register GC gc, int subwindow_mode) { printf("CALL XSetSubwindowMode\n");  return -1; }

int XSetScreenSaver( register Display *dpy, int timeout, int interval, int prefer_blank, int allow_exp) { printf("CALL XSetScreenSaver\n");  return -1; }

Cursor XCreateFontCursor( Display *dpy, unsigned int which) { printf("CALL XCreateFontCursor\n"); }

int XVendorRelease(Display *dpy) { printf("CALL XVendorRelease\n");  return -1; }

void XUnsetICFocus(XIC ic) { printf("CALL XUnsetICFocus\n"); }

int XmbLookupString(XIC ic, XKeyEvent *ev, char *buffer, int nbytes, KeySym *keysym, Status *status) { printf("CALL XmbLookupString\n");  return -1; }

Bool XSupportsLocale(void) { printf("CALL XSupportsLocale\n");  return False; }

int XmbTextPropertyToTextList( Display *dpy, const XTextProperty *text_prop, char ***list_ret, int *count_ret) { printf("CALL XmbTextPropertyToTextList\n");  return -1; }

int XmbTextListToTextProperty( Display *dpy, char **list, int count, XICCEncodingStyle style, XTextProperty *text_prop) { printf("CALL XmbTextListToTextProperty\n");  return -1; }

Bool XRegisterIMInstantiateCallback( Display *display, XrmDatabase rdb, char *res_name, char *res_class, XIDProc callback, XPointer client_data) { printf("CALL XRegisterIMInstantiateCallback\n");  return False; }

Bool XUnregisterIMInstantiateCallback( Display *display, XrmDatabase rdb, char *res_name, char *res_class, XIDProc callback, XPointer client_data) { printf("CALL XUnregisterIMInstantiateCallback\n");  return False; }

int XSetClipRectangles ( register Display *dpy, GC gc, int clip_x_origin, int clip_y_origin, XRectangle *rectangles, int n, int ordering) { printf("CALL XSetClipRectangles\n");  return -1; }

int XSaveContext( Display *display, register XID rid, register XContext context, _Xconst char* data) { printf("CALL XSaveContext\n");  return -1; }

int XFindContext(Display *display, XID rid, XContext context, XPointer *data) { printf("CALL XFindContext\n");  return -1; }

int XDeleteContext(Display *display, XID rid, XContext context) { printf("CALL XDeleteContext\n");  return -1; }

int XGetScreenSaver( register Display *dpy, /* the following are return only vars */ int *timeout, int *interval, int *prefer_blanking, int *allow_exp) /*boolean */ { printf("CALL XGetScreenSaver\n");  return -1; }

Status XGetAtomNames ( Display *dpy, Atom *atoms, int count, char **names_return) { printf("CALL XGetAtomNames\n"); }

Bool XQueryExtension( register Display *dpy, _Xconst char *name, int *major_opcode, /* RETURN */ int *first_event, /* RETURN */ int *first_error) /* RETURN */ { printf("CALL XQueryExtension\n");  return False; }

Bool XkbSetDetectableAutoRepeat(Display *dpy, Bool detectable, Bool *supported) { printf("CALL XkbSetDetectableAutoRepeat\n");  return False; }

Bool XkbUseExtension(Display *dpy, int *major_rtrn, int *minor_rtrn) { printf("CALL XkbUseExtension\n");  return False; }

int XkbTranslateKeySym(Display *dpy, KeySym *sym_rtrn, unsigned int mods, char *buffer, int nbytes, int *extra_rtrn) { printf("CALL XkbTranslateKeySym\n");  return -1; }

int XDrawPoint( register Display *dpy, Drawable d, GC gc, int x, int y) /* INT16 */ { printf("CALL XDrawPoint\n");  return -1; }

int XStoreColor( register Display *dpy, Colormap cmap, XColor *def) { printf("CALL XStoreColor\n");  return -1; }

int XWindowEvent ( register Display *dpy, Window w, /* Selected window. */ long mask, /* Selected event mask. */ register XEvent *event) /* XEvent to be filled in. */ { printf("CALL XWindowEvent\n");  return -1; }

XrmQuark XrmUniqueQuark(void) { printf("CALL XrmUniqueQuark\n"); }

void XSetWMProperties ( Display *dpy, Window w, /* window to decorate */ XTextProperty *windowName, /* name of application */ XTextProperty *iconName, /* name string for icon */ char **argv, /* command line */ int argc, /* size of command line */ XSizeHints *sizeHints, /* size hints for window in its normal state */ XWMHints *wmHints, /* miscellaneous window manager hints */ XClassHint *classHints) /* resource name and class */ { printf("CALL XSetWMProperties\n"); }

Status XInitThreads(void) { printf("CALL XInitThreads\n"); }

XPixmapFormatValues *XListPixmapFormats (
    Display *dpy,
    int *count)	/* RETURN */
{ printf("CALL XListPixmapFormats\n"); }

KeySym
XkbKeycodeToKeysym(Display *dpy,
#if NeedWidePrototypes
                   unsigned int kc,
#else
                   KeyCode kc,
#endif
                   int group,
                   int level)
{ printf("CALL XkbKeycodeToKeysym\n"); }

Bool XCheckIfEvent (
	register Display *dpy,
	register XEvent *event,		/* XEvent to be filled in. */
	Bool (*predicate)(
			  Display*			/* display */,
			  XEvent*			/* event */,
			  char*				/* arg */
			  ),		/* function to call */
	char *arg)
{ printf("CALL XCheckIfEvent\n");  return False; }

KeySym *
XGetKeyboardMapping (Display *dpy,
#if NeedWidePrototypes
			     unsigned int first_keycode,
#else
			     KeyCode first_keycode,
#endif
			     int count,
			     int *keysyms_per_keycode)
{ printf("CALL XGetKeyboardMapping\n"); }

char *XServerVendor(Display *dpy) { printf("CALL XServerVendor\n"); }

XWMHints *XAllocWMHints (void)
{
    printf("CALL XAllocWMHints\n");
}

char *
XDisplayName(
    _Xconst char *display)
{ printf("CALL XDisplayName\n"); }

char *
XSetIMValues(XIM im, ...)
{ printf("CALL XSetIMValues\n"); }

Display *
XDisplayOfIM(XIM im)
{ printf("CALL XDisplayOfIM\n"); }

char *
XLocaleOfIM(XIM im)
{ printf("CALL XLocaleOfIM\n"); }

char *
XmbResetIC(XIC ic)
{ printf("CALL XmbResetIC\n"); }