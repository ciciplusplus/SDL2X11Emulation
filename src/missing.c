#include "X11/Xlibint.h"
#include "X11/Xresource.h"
#include "X11/Xutil.h"
#include "X11/Xatom.h"
#include "X11/Xlocale.h"
#include <stdio.h>
#include "util.h"

Window XGetSelectionOwner( register Display *dpy, Atom selection) { LOG("CALL XGetSelectionOwner\n"); }

void XSetTextProperty (
        Display *dpy,
        Window w,
        XTextProperty *tp,
        Atom property)
{
    XChangeProperty (dpy, w, property, tp->encoding, tp->format,
                     PropModeReplace, tp->value, tp->nitems);
}

void XSetWMName (
        Display *dpy,
        Window w,
        XTextProperty *tp)
{
    XSetTextProperty (dpy, w, tp, XA_WM_NAME);
}

void XSetWMIconName (
        Display *dpy,
        Window w,
        XTextProperty *tp)
{
    XSetTextProperty (dpy, w, tp, XA_WM_ICON_NAME);
}

int XClearWindow ( Display* dpy, Window w) { return XClearArea(dpy, w, 0, 0, 0, 0, False); }

int XClearArea ( register Display *dpy, Window w, int x, int y, unsigned int width, unsigned int height, Bool exposures) { LOG("CALL XClearArea\n");  return -1; }

long XMaxRequestSize(Display *dpy) { LOG("CALL XMaxRequestSize\n");  return -1; }

int XDisplayKeycodes(Display *dpy, int *min_keycode_return, int *max_keycode_return) {
	*min_keycode_return = dpy->min_keycode;
    *max_keycode_return = dpy->max_keycode;
    return 1;
}

long XExtendedMaxRequestSize(Display *dpy) { LOG("CALL XExtendedMaxRequestSize\n");  return -1; }

Status XAllocColorCells( register Display *dpy, Colormap cmap, Bool contig, unsigned long *masks, /* LISTofCARD32 */ /* RETURN */ unsigned int nplanes, /* CARD16 */ unsigned long *pixels, /* LISTofCARD32 */ /* RETURN */ unsigned int ncolors) /* CARD16 */ { LOG("CALL XAllocColorCells\n"); }

int XQueryColor( register Display *dpy, Colormap cmap, XColor *def) /* RETURN */ { LOG("CALL XQueryColor\n");  return -1; }

void XLockDisplay( register Display* dpy) { LOG("CALL XLockDisplay\n"); }

void XUnlockDisplay( register Display* dpy) { LOG("CALL XUnlockDisplay\n"); }

Bool XCheckTypedWindowEvent ( register Display *dpy, Window w, /* Selected window. */ int type, /* Selected event type. */ register XEvent *event) /* XEvent to be filled in. */ { /* LOG("CALL XCheckTypedWindowEvent\n"); */  return False; }

int XSetFunction ( register Display *dpy, GC gc, int function) { LOG("CALL XSetFunction\n");  return -1; }

int XSetArcMode ( register Display *dpy, register GC gc, int arc_mode) { LOG("CALL XSetArcMode\n");  return -1; }

int XSetFillStyle ( register Display *dpy, register GC gc, int fill_style) { LOG("CALL XSetFillStyle\n");  return -1; }

int XSetScreenSaver( register Display *dpy, int timeout, int interval, int prefer_blank, int allow_exp) { LOG("CALL XSetScreenSaver\n");  return -1; }

Cursor XCreateFontCursor( Display *dpy, unsigned int which) { LOG("CALL XCreateFontCursor\n"); }

int XVendorRelease(Display *dpy) { return (VendorRelease(dpy)); }

void XUnsetICFocus(XIC ic) { LOG("CALL XUnsetICFocus\n"); }

int XmbLookupString(XIC ic, XKeyEvent *ev, char *buffer, int nbytes, KeySym *keysym, Status *status) { LOG("CALL XmbLookupString\n");  return -1; }

Bool XSupportsLocale(void) { LOG("CALL XSupportsLocale\n");  return False; }

int XmbTextPropertyToTextList( Display *dpy, const XTextProperty *text_prop, char ***list_ret, int *count_ret) { LOG("CALL XmbTextPropertyToTextList\n");  return -1; }

int XmbTextListToTextProperty( Display *dpy, char **list, int count, XICCEncodingStyle style, XTextProperty *text_prop) { LOG("CALL XmbTextListToTextProperty\n");  return -1; }

Bool XRegisterIMInstantiateCallback( Display *display, XrmDatabase rdb, char *res_name, char *res_class, XIDProc callback, XPointer client_data) { LOG("CALL XRegisterIMInstantiateCallback\n");  return False; }

Bool XUnregisterIMInstantiateCallback( Display *display, XrmDatabase rdb, char *res_name, char *res_class, XIDProc callback, XPointer client_data) { LOG("CALL XUnregisterIMInstantiateCallback\n");  return False; }

int XSetClipRectangles ( register Display *dpy, GC gc, int clip_x_origin, int clip_y_origin, XRectangle *rectangles, int n, int ordering) { LOG("CALL XSetClipRectangles\n");  return -1; }

//int XSaveContext( Display *display, register XID rid, register XContext context, _Xconst char* data) { LOG("CALL XSaveContext\n");  return -1; }

//int XFindContext(Display *display, XID rid, XContext context, XPointer *data) { LOG("CALL XFindContext\n");  return -1; }

//int XDeleteContext(Display *display, XID rid, XContext context) { LOG("CALL XDeleteContext\n");  return -1; }

int XGetScreenSaver( register Display *dpy, /* the following are return only vars */ int *timeout, int *interval, int *prefer_blanking, int *allow_exp) /*boolean */ { LOG("CALL XGetScreenSaver\n");  return -1; }

Bool XQueryExtension( register Display *dpy, _Xconst char *name, int *major_opcode, /* RETURN */ int *first_event, /* RETURN */ int *first_error) /* RETURN */ { LOG("CALL XQueryExtension\n");  return False; }

Bool XkbSetDetectableAutoRepeat(Display *dpy, Bool detectable, Bool *supported) { LOG("CALL XkbSetDetectableAutoRepeat\n");  return False; }

Bool XkbUseExtension(Display *dpy, int *major_rtrn, int *minor_rtrn) { LOG("CALL XkbUseExtension\n");  return False; }

int XkbTranslateKeySym(Display *dpy, KeySym *sym_rtrn, unsigned int mods, char *buffer, int nbytes, int *extra_rtrn) { LOG("CALL XkbTranslateKeySym\n");  return -1; }

int XDrawPoint( register Display *dpy, Drawable d, GC gc, int x, int y) /* INT16 */ { LOG("CALL XDrawPoint\n");  return -1; }

int XStoreColor( register Display *dpy, Colormap cmap, XColor *def) { LOG("CALL XStoreColor\n");  return -1; }

int XWindowEvent ( register Display *dpy, Window w, /* Selected window. */ long mask, /* Selected event mask. */ register XEvent *event) /* XEvent to be filled in. */ { LOG("CALL XWindowEvent\n");  return -1; }

XrmQuark XrmUniqueQuark(void) { LOG("CALL XrmUniqueQuark\n"); }

/* Make sure this produces the same string as DefineLocal/DefineSelf in xdm.
 * Otherwise, Xau will not be able to find your cookies in the Xauthority file.
 *
 * Note: POSIX says that the ``nodename'' member of utsname does _not_ have
 *       to have sufficient information for interfacing to the network,
 *       and so, you may be better off using gethostname (if it exists).
 */

#if (defined(_POSIX_SOURCE) && !defined(AIXV3) && !defined(__QNX__)) || defined(hpux) || defined(SVR4)
#define NEED_UTSNAME
#include <sys/utsname.h>
#else
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#endif

/*
 * _XGetHostname - similar to gethostname but allows special processing.
 */
int _XGetHostname (
        char *buf,
        int maxlen)
{
    int len;

#ifdef NEED_UTSNAME
    struct utsname name;

    if (maxlen <= 0 || buf == NULL)
        return 0;

    uname (&name);
    len = (int) strlen (name.nodename);
    if (len >= maxlen) len = maxlen - 1;
    strncpy (buf, name.nodename, (size_t) len);
    buf[len] = '\0';
#else
    if (maxlen <= 0 || buf == NULL)
	return 0;

    buf[0] = '\0';
    (void) gethostname (buf, maxlen);
    buf [maxlen - 1] = '\0';
    len = (int) strlen(buf);
#endif /* NEED_UTSNAME */
    return len;
}

/*
 * XSetWMProperties sets the following properties:
 *	WM_NAME		  type: TEXT		format: varies?
 *	WM_ICON_NAME	  type: TEXT		format: varies?
 *	WM_HINTS	  type: WM_HINTS	format: 32
 *	WM_COMMAND	  type: TEXT		format: varies?
 *	WM_CLIENT_MACHINE type: TEXT		format: varies?
 *	WM_NORMAL_HINTS	  type: WM_SIZE_HINTS 	format: 32
 *	WM_CLASS	  type: STRING/STRING	format: 8
  *	WM_LOCALE_NAME	  type: STRING		format: 8
 */

void XSetWMProperties (
        Display *dpy,
        Window w,			/* window to decorate */
        XTextProperty *windowName,	/* name of application */
        XTextProperty *iconName,	/* name string for icon */
        char **argv,		/* command line */
        int argc,			/* size of command line */
        XSizeHints *sizeHints,	/* size hints for window in its normal state */
        XWMHints *wmHints,		/* miscellaneous window manager hints */
        XClassHint *classHints)	/* resource name and class */
{
    XTextProperty textprop;
    char hostName[256];
    int len = _XGetHostname (hostName, sizeof hostName);
    char *locale;

    /* set names of window and icon */
    if (windowName) XSetWMName (dpy, w, windowName);
    if (iconName) XSetWMIconName (dpy, w, iconName);

    /* set the command if given */
    if (argv) {
        /*
         * for UNIX and other operating systems which use nul-terminated
         * arrays of STRINGs.
         */
        XSetCommand (dpy, w, argv, argc);
    }

    /* set the name of the machine on which this application is running */
    textprop.value = (unsigned char *) hostName;
    textprop.encoding = XA_STRING;
    textprop.format = 8;
    textprop.nitems = (unsigned long) len;
    XSetWMClientMachine (dpy, w, &textprop);

    /* set hints about how geometry and window manager interaction */
    if (sizeHints) XSetWMNormalHints (dpy, w, sizeHints);
    if (wmHints) XSetWMHints (dpy, w, wmHints);
    if (classHints) {
        XClassHint tmp;

        if (!classHints->res_name) {
            tmp.res_name = getenv ("RESOURCE_NAME");
            if (!tmp.res_name && argv && argv[0]) {
                /*
                 * UNIX uses /dir/subdir/.../basename; other operating
                 * systems will have to change this.
                 */
                char *cp = strrchr (argv[0], '/');
#ifdef __UNIXOS2__
                char *os2_cp = strrchr (argv[0],'\\');
		char *dot_cp = strrchr (argv[0],'.');
		if (os2_cp && (os2_cp > cp)) {
		    if(dot_cp && (dot_cp > os2_cp)) *dot_cp = '\0';
		    cp=os2_cp;
		}
#endif
                tmp.res_name = (cp ? cp + 1 : argv[0]);
            }
            tmp.res_class = classHints->res_class;
            classHints = &tmp;
        }
        XSetClassHint (dpy, w, classHints);
    }

    locale = setlocale(LC_CTYPE, (char *)NULL);
    if (locale)
        XChangeProperty (dpy, w, XInternAtom(dpy, "WM_LOCALE_NAME", False),
                         XA_STRING, 8, PropModeReplace,
                         (unsigned char *)locale, (int) strlen(locale));
}

//Status XInitThreads(void) { LOG("CALL XInitThreads\n"); }

XPixmapFormatValues *XListPixmapFormats( Display *dpy, int *count) {
    XPixmapFormatValues *formats = malloc(sizeof(XPixmapFormatValues));
    formats->depth = 32;
    formats->bits_per_pixel = 32;
    formats->scanline_pad = 32;
    *count = 1;
    return formats;
}

KeySym
XkbKeycodeToKeysym(Display *dpy,
#if NeedWidePrototypes
                   unsigned int kc,
#else
                   KeyCode kc,
#endif
                   int group,
                   int level)
{ LOG("CALL XkbKeycodeToKeysym\n"); }

Bool XCheckIfEvent (
	register Display *dpy,
	register XEvent *event,		/* XEvent to be filled in. */
	Bool (*predicate)(
			  Display*			/* display */,
			  XEvent*			/* event */,
			  char*				/* arg */
			  ),		/* function to call */
	char *arg)
{ /* LOG("CALL XCheckIfEvent\n"); */ return False; }

char *XServerVendor(Display *dpy) { return (ServerVendor(dpy)); }

XWMHints *XAllocWMHints (void)
{
    return Xcalloc (1, sizeof (XWMHints));
}

char *
XDisplayName(
    _Xconst char *display)
{ LOG("CALL XDisplayName\n"); }

char *
XSetIMValues(XIM im, ...)
{ LOG("CALL XSetIMValues\n"); }

Display *
XDisplayOfIM(XIM im)
{ LOG("CALL XDisplayOfIM\n"); }

char *
XLocaleOfIM(XIM im)
{ LOG("CALL XLocaleOfIM\n"); }

char *
XmbResetIC(XIC ic)
{ LOG("CALL XmbResetIC\n"); }

int XWarpPointer( register Display *dpy, Window src_win, Window dest_win, int src_x, int src_y, unsigned int src_width, unsigned int src_height, int dest_x, int dest_y) { LOG("CALL XWarpPointer\n");  return -1; }

int XDrawLine ( register Display *dpy, Drawable d, GC gc, int x1, int y1, int x2, int y2) { LOG("CALL XDrawLine\n");  return -1; }

int XGrabPointer( register Display *dpy, Window grab_window, Bool owner_events, unsigned int event_mask, /* CARD16 */ int pointer_mode, int keyboard_mode, Window confine_to, Cursor curs, Time time) { LOG("CALL XGrabPointer\n");  return -1; }

Bool XQueryPointer( register Display *dpy, Window w, Window *root, Window *child, int *root_x, int *root_y, int *win_x, int *win_y, unsigned int *mask) { LOG("CALL XQueryPointer\n");  return False; }

int XResetScreenSaver(register Display *dpy) { LOG("CALL XResetScreenSaver\n");  return -1; }

int XUngrabPointer( register Display *dpy, Time time) { LOG("CALL XUngrabPointer\n");  return -1; }
