#include "X11/Xlibint.h"
#include "X11/xcms/Xcmsint.h"
#include "X11/Xresource.h"
#include "X11/Xutil.h"
#include "X11/Xatom.h"
#include "X11/Xlocale.h"
#include <stdio.h>
#include "util.h"

Window XGetSelectionOwner( register Display *dpy, Atom selection) { LOG("CALL XGetSelectionOwner\n"); return dpy->screens[0].root; }

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

long XMaxRequestSize(Display *dpy) { LOG("CALL XMaxRequestSize\n");  return 0; }

int XDisplayKeycodes(Display *dpy, int *min_keycode_return, int *max_keycode_return) {
	*min_keycode_return = dpy->min_keycode;
    *max_keycode_return = dpy->max_keycode;
    return 1;
}

long XExtendedMaxRequestSize(Display *dpy) { LOG("CALL XExtendedMaxRequestSize\n");  return 0; }

Status XAllocColorCells( register Display *dpy, Colormap cmap, Bool contig, unsigned long *masks, /* LISTofCARD32 */ /* RETURN */ unsigned int nplanes, /* CARD16 */ unsigned long *pixels, /* LISTofCARD32 */ /* RETURN */ unsigned int ncolors) /* CARD16 */ { LOG("CALL XAllocColorCells\n"); }

int XQueryColor( register Display *dpy, Colormap cmap, XColor *def) /* RETURN */ { LOG("CALL XQueryColor\n");  return 0; }

void XLockDisplay( register Display* dpy) { LockDisplay(dpy); }

void XUnlockDisplay( register Display* dpy) { UnlockDisplay(dpy); }

int XSetArcMode ( register Display *dpy, register GC gc, int arc_mode) { LOG("CALL XSetArcMode\n");  return 0; }

int XSetFillStyle ( register Display *dpy, register GC gc, int fill_style) { LOG("CALL XSetFillStyle\n");  return 0; }

int XSetScreenSaver( register Display *dpy, int timeout, int interval, int prefer_blank, int allow_exp) { LOG("CALL XSetScreenSaver\n");  return 0; }

Cursor XCreateFontCursor( Display *dpy, unsigned int which) { LOG("CALL XCreateFontCursor\n"); }

void XUnsetICFocus(XIC ic) { LOG("CALL XUnsetICFocus\n"); }

int XmbLookupString(XIC ic, XKeyEvent *ev, char *buffer, int nbytes, KeySym *keysym, Status *status) { LOG("CALL XmbLookupString\n");  return 0; }

Bool XSupportsLocale(void) { LOG("CALL XSupportsLocale\n");  return False; }

int XmbTextPropertyToTextList( Display *dpy, const XTextProperty *text_prop, char ***list_ret, int *count_ret) { LOG("CALL XmbTextPropertyToTextList\n");  return 0; }

int XmbTextListToTextProperty( Display *dpy, char **list, int count, XICCEncodingStyle style, XTextProperty *text_prop) { LOG("CALL XmbTextListToTextProperty\n");  return 1; }

Bool XRegisterIMInstantiateCallback( Display *display, XrmDatabase rdb, char *res_name, char *res_class, XIDProc callback, XPointer client_data) { LOG("CALL XRegisterIMInstantiateCallback\n");  return False; }

Bool XUnregisterIMInstantiateCallback( Display *display, XrmDatabase rdb, char *res_name, char *res_class, XIDProc callback, XPointer client_data) { LOG("CALL XUnregisterIMInstantiateCallback\n");  return False; }

int XSetClipRectangles ( register Display *dpy, GC gc, int clip_x_origin, int clip_y_origin, XRectangle *rectangles, int n, int ordering) { LOG("CALL XSetClipRectangles\n");  return 0; }

int XGetScreenSaver( register Display *dpy, /* the following are return only vars */ int *timeout, int *interval, int *prefer_blanking, int *allow_exp) /*boolean */ { LOG("CALL XGetScreenSaver\n");  return 0; }

 XExtCodes *XInitExtension (
     Display *dpy,
     _Xconst char *name)
 {
     LOG("CALL XInitExtension %s\n", name);

     XExtCodes codes;    /* temp. place for extension information. */
     register _XExtension *ext;/* need a place to build it all */
     if (!XQueryExtension(dpy, name,
         &codes.major_opcode, &codes.first_event,
         &codes.first_error)) return (NULL);

     LockDisplay (dpy);
     if (! (ext = Xcalloc (1, sizeof (_XExtension))) ||
         ! (ext->name = strdup(name))) {
         Xfree(ext);
         UnlockDisplay(dpy);
         return (XExtCodes *) NULL;
     }
     codes.extension = dpy->ext_number++;
     ext->codes = codes;

     /* chain it onto the display list */
     ext->next = dpy->ext_procs;
     dpy->ext_procs = ext;
     UnlockDisplay (dpy);

     return (&ext->codes);       /* tell him which extension */
 }

XExtCodes *XAddExtension (Display *dpy)
{
    register _XExtension *ext;

    LockDisplay (dpy);
    if (! (ext = Xcalloc (1, sizeof (_XExtension)))) {
        UnlockDisplay(dpy);
        return (XExtCodes *) NULL;
    }
    ext->codes.extension = dpy->ext_number++;

    /* chain it onto the display list */
    ext->next = dpy->ext_procs;
    dpy->ext_procs = ext;
    UnlockDisplay (dpy);

    return (&ext->codes);		/* tell him which extension */
}

Bool XQueryExtension( register Display *dpy, _Xconst char *name, int *major_opcode, /* RETURN */ int *first_event, /* RETURN */ int *first_error) /* RETURN */ {
    LOG("CALL XQueryExtension %s\n", name);
    if (strcmp(name, "GLX") == 0) {
        *major_opcode = 1;
        *first_event = 0;
        *first_error = 0;
        return True;
    }
    return False;
}

Bool XkbSetDetectableAutoRepeat(Display *dpy, Bool detectable, Bool *supported) { LOG("CALL XkbSetDetectableAutoRepeat\n");  return False; }

Bool XkbUseExtension(Display *dpy, int *major_rtrn, int *minor_rtrn) { LOG("CALL XkbUseExtension\n");  return False; }

int XkbTranslateKeySym(Display *dpy, KeySym *sym_rtrn, unsigned int mods, char *buffer, int nbytes, int *extra_rtrn) { LOG("CALL XkbTranslateKeySym\n");  return 0; }

int XDrawPoint( register Display *dpy, Drawable d, GC gc, int x, int y) /* INT16 */ { LOG("CALL XDrawPoint\n");  return 0; }

int XDrawPoints( register Display *dpy, Drawable d, GC gc, XPoint *points, int n_points, int mode) /* CoordMode */ { printf("CALL XDrawPoints\n");  return 0; }

int XStoreColor( register Display *dpy, Colormap cmap, XColor *def) { LOG("CALL XStoreColor\n");  return 0; }

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

XWMHints *XAllocWMHints (void)
{
    return Xcalloc (1, sizeof (XWMHints));
}

char *XDisplayName(_Xconst char* display) {
    char *d;
    if ( display != (char *)NULL && *display != '\0' )
        return( (char *)display );
    if ( (d = getenv( "DISPLAY" )) != (char *)NULL )
        return( d );
    return( (char *) "" );
}

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

int XWarpPointer( register Display *dpy, Window src_win, Window dest_win, int src_x, int src_y, unsigned int src_width, unsigned int src_height, int dest_x, int dest_y) { LOG("CALL XWarpPointer\n");  return 0; }

int XDrawLine ( register Display *dpy, Drawable d, GC gc, int x1, int y1, int x2, int y2) { LOG("CALL XDrawLine\n");  return 0; }

int XGrabPointer( register Display *dpy, Window grab_window, Bool owner_events, unsigned int event_mask, /* CARD16 */ int pointer_mode, int keyboard_mode, Window confine_to, Cursor curs, Time time) { LOG("CALL XGrabPointer\n");  return 0; }

Bool XQueryPointer( register Display *dpy, Window w, Window *root, Window *child, int *root_x, int *root_y, int *win_x, int *win_y, unsigned int *mask) { LOG("CALL XQueryPointer\n");  return False; }

int XResetScreenSaver(register Display *dpy) { LOG("CALL XResetScreenSaver\n");  return 0; }

int XUngrabPointer( register Display *dpy, Time time) { LOG("CALL XUngrabPointer\n");  return 0; }

int XPending(Display *dpy)
{
    return XEventsQueued(dpy, QueuedAfterFlush);
}

int XUnloadFont( register Display *dpy, Font font) { printf("CALL XUnloadFont\n");  return 0; }

int XDrawImageString( register Display *dpy, Drawable d, GC gc, int x, int y, _Xconst char *string, int length) { printf("CALL XDrawImageString\n");  return 0; }

Bool XCheckMaskEvent ( register Display *dpy, long mask, /* Selected event mask. */ register XEvent *event) /* XEvent to be filled in. */ { printf("CALL XCheckMaskEvent\n");  return False; }

int XSetState( register Display *dpy, GC gc, unsigned long foreground, unsigned long background, int function, unsigned long planemask) { printf("CALL XSetState\n");  return 0; }

int XMapSubwindows( register Display *dpy, Window win) { printf("CALL XMapSubwindows\n");  return 0; }

int XDrawSegments ( register Display *dpy, Drawable d, GC gc, XSegment *segments, int nsegments) { printf("CALL XDrawSegments\n");  return 0; }

int XGetErrorText( register Display *dpy, register int code, char *buffer, int nbytes) { printf("CALL XGetErrorText\n");  return 0; }

int XRestackWindows ( register Display *dpy, register Window *windows, int n) { printf("CALL XRestackWindows\n");  return 0; }

int XAutoRepeatOn (register Display *dpy) { printf("CALL XAutoRepeatOn\n");  return 0; }

int XAutoRepeatOff (register Display *dpy) { printf("CALL XAutoRepeatOff\n");  return 0; }

Status XQueryBestCursor( register Display *dpy, Drawable drawable, unsigned int width, unsigned int height, unsigned int *ret_width, unsigned int *ret_height) { printf("CALL XQueryBestCursor\n");  return 0; }

int XRotateWindowProperties( register Display *dpy, Window w, Atom *properties, register int nprops, int npositions) { printf("CALL XRotateWindowProperties\n");  return 0; }

int XChangeKeyboardMapping ( register Display *dpy, int first_keycode, int keysyms_per_keycode, KeySym *keysyms, int nkeycodes) { printf("CALL XChangeKeyboardMapping\n");  return 0; }

int XCirculateSubwindowsUp( register Display *dpy, Window w) { printf("CALL XCirculateSubwindowsUp\n");  return 0; }

int XCirculateSubwindows( register Display *dpy, Window w, int direction) { printf("CALL XCirculateSubwindows\n");  return 0; }

int XInstallColormap( register Display *dpy, Colormap cmap) { printf("CALL XInstallColormap\n");  return 0; }

Status XAllocColorPlanes( register Display *dpy, Colormap cmap, Bool contig, unsigned long *pixels, /* LISTofCARD32 */ /* RETURN */ int ncolors, int nreds, int ngreens, int nblues, unsigned long *rmask, unsigned long *gmask, unsigned long *bmask) /* CARD32 */ /* RETURN */ { printf("CALL XAllocColorPlanes\n");  return 0; }

XIOErrorHandler XSetIOErrorHandler(XIOErrorHandler handler) { printf("CALL XSetIOErrorHandler\n");  return NULL; }

int XLowerWindow( Display *dpy, Window w) { printf("CALL XLowerWindow\n");  return 0; }

int XGetPointerControl( register Display *dpy, /* the following are return only vars */ int *accel_numer, int *accel_denom, int *threshold) { printf("CALL XGetPointerControl\n");  return 0; }

int XGetKeyboardControl ( register Display *dpy, register XKeyboardState *state) { printf("CALL XGetKeyboardControl\n");  return 0; }

int XSetTile ( register Display *dpy, GC gc, Pixmap tile) { printf("CALL XSetTile\n");  return 0; }

int XCirculateSubwindowsDown( register Display *dpy, Window w) { printf("CALL XCirculateSubwindowsDown\n");  return 0; }

int XUndefineCursor ( register Display *dpy, Window w) { printf("CALL XUndefineCursor\n");  return 0; }

int XUnmapSubwindows( register Display *dpy, Window win) { printf("CALL XUnmapSubwindows\n");  return 0; }

int XBitmapUnit(Display *dpy) { printf("CALL XBitmapUnit\n");  return 0; }

int XBitmapBitOrder(Display *dpy) { printf("CALL XBitmapBitOrder\n");  return 0; }

int XBitmapPad(Display *dpy) { printf("CALL XBitmapPad\n");  return 0; }

int XImageByteOrder(Display *dpy) { printf("CALL XImageByteOrder\n");  return 0; }

Window XRootWindowOfScreen(Screen *s) { printf("CALL XRootWindowOfScreen\n");  return 0; }

unsigned long XBlackPixelOfScreen(Screen *s) { printf("CALL XBlackPixelOfScreen\n");  return 0; }

unsigned long XWhitePixelOfScreen(Screen *s) { printf("CALL XWhitePixelOfScreen\n");  return 0; }

Colormap XDefaultColormapOfScreen(Screen *s) { printf("CALL XDefaultColormapOfScreen\n");  return 0; }

int XDefaultDepthOfScreen(Screen *s) { printf("CALL XDefaultDepthOfScreen\n");  return 0; }

GC XDefaultGCOfScreen(Screen *s) { printf("CALL XDefaultGCOfScreen\n");  return NULL; }

int XWidthOfScreen(Screen *s) { printf("CALL XWidthOfScreen\n");  return 0; }

int XHeightOfScreen(Screen *s) { printf("CALL XHeightOfScreen\n");  return 0; }

int XWidthMMOfScreen(Screen *s) { printf("CALL XWidthMMOfScreen\n");  return 0; }

int XHeightMMOfScreen(Screen *s) { printf("CALL XHeightMMOfScreen\n");  return 0; }

int XPlanesOfScreen(Screen *s) { printf("CALL XPlanesOfScreen\n");  return 0; }

int XCellsOfScreen(Screen *s) { printf("CALL XCellsOfScreen\n");  return 0; }

int XMinCmapsOfScreen(Screen *s) { printf("CALL XMinCmapsOfScreen\n");  return 0; }

int XMaxCmapsOfScreen(Screen *s) { printf("CALL XMaxCmapsOfScreen\n");  return 0; }

Bool XDoesSaveUnders(Screen *s) { printf("CALL XDoesSaveUnders\n");  return False; }

int XDoesBackingStore(Screen *s) { printf("CALL XDoesBackingStore\n");  return 0; }

int XScreenNumberOfScreen (register Screen *scr) { printf("CALL XScreenNumberOfScreen\n");  return 0; }

int XSetCloseDownMode( register Display *dpy, int mode) { printf("CALL XSetCloseDownMode\n");  return 0; }

XcmsCCC
XcmsCreateCCC(
        Display *dpy,
        int screenNumber,
        Visual *visual,
        XcmsColor *clientWhitePt,
        XcmsCompressionProc gamutCompProc,
        XPointer gamutCompClientData,
        XcmsWhiteAdjustProc whitePtAdjProc,
        XPointer whitePtAdjClientData)
/*
 *	DESCRIPTION
 *		Given a Display, Screen, Visual, etc., this routine creates
 *		an appropriate Color Conversion Context.
 *
 *	RETURNS
 *		Returns NULL if failed; otherwise address of the newly
 *		created XcmsCCC.
 *
 */
{ printf("CALL XcmsCreateCCC\n");  return NULL; }

Status XcmsRGBiToRGB( XcmsCCC ccc, XcmsColor *pXcmsColors_in_out,/* pointer to XcmsColors to convert */ unsigned int nColors, /* Number of colors */ Bool *pCompressed) /* pointer to a bit array */ /* * DESCRIPTION * Converts color specifications in an array of XcmsColor * structures from RGBi format to RGB format. * * RETURNS * XcmsFailure if failed, * XcmsSuccess if succeeded without gamut compression. * XcmsSuccessWithCompression if succeeded with gamut * compression. */ { printf("CALL XcmsRGBiToRGB\n");  return 0; }

Status XcmsCIELuvToCIEuvY( XcmsCCC ccc, XcmsColor *pLuv_WhitePt, XcmsColor *pColors_in_out, unsigned int nColors) /* * DESCRIPTION * Converts color specifications in an array of XcmsColor * structures from CIELuv format to CIEuvY format. * * RETURNS * XcmsFailure if failed, * XcmsSuccess if succeeded. * */ { printf("CALL XcmsCIELuvToCIEuvY\n");  return 0; }

int XRecolorCursor( register Display *dpy, Cursor cursor, XColor *foreground, XColor *background) { printf("CALL XRecolorCursor\n");  return 0; }

int XSubtractRegion( Region regM, Region regS, register Region regD) { printf("CALL XSubtractRegion\n");  return 0; }

int XChangeActivePointerGrab( register Display *dpy, unsigned int event_mask, /* CARD16 */ Cursor curs, Time time) { printf("CALL XChangeActivePointerGrab\n");  return 0; }

Status XQueryBestSize( register Display *dpy, int class, Drawable drawable, unsigned int width, unsigned int height, unsigned int *ret_width, unsigned int *ret_height) { printf("CALL XQueryBestSize\n");  return 0; }

void XFlushGC( Display *dpy, GC gc) { printf("CALL XFlushGC\n"); }

Status XQueryBestTile( register Display *dpy, Drawable drawable, unsigned int width, unsigned int height, unsigned int *ret_width, unsigned int *ret_height) { printf("CALL XQueryBestTile\n");  return 0; }

int XChangePointerControl( register Display *dpy, Bool do_acc, Bool do_thresh, int acc_numerator, int acc_denominator, int threshold) { printf("CALL XChangePointerControl\n");  return 0; }

int XDrawArcs( register Display *dpy, Drawable d, GC gc, XArc *arcs, int n_arcs) { printf("CALL XDrawArcs\n");  return 0; }

int XQueryTextExtents ( register Display *dpy, Font fid, register _Xconst char *string, register int nchars, int *dir, int *font_ascent, int *font_descent, register XCharStruct *overall) { printf("CALL XQueryTextExtents\n");  return 0; }

int XChangeKeyboardControl( register Display *dpy, unsigned long mask, XKeyboardControl *value_list) { printf("CALL XChangeKeyboardControl\n");  return 0; }

Colormap XCopyColormapAndFree( register Display *dpy, Colormap src_cmap) { printf("CALL XCopyColormapAndFree\n");  return 0; }

int XDestroySubwindows( register Display *dpy, Window win) { printf("CALL XDestroySubwindows\n");  return 0; }

int XRemoveHost ( register Display *dpy, XHostAddress *host) { printf("CALL XRemoveHost\n");  return 0; }

int XRemoveHosts ( register Display *dpy, XHostAddress *hosts, int n) { printf("CALL XRemoveHosts\n");  return 0; }

int XChangeSaveSet( register Display *dpy, Window win, int mode) { printf("CALL XChangeSaveSet\n");  return 0; }

int XAddToSaveSet( register Display *dpy, Window win) { printf("CALL XAddToSaveSet\n");  return 0; }

int XSetFillRule ( register Display *dpy, register GC gc, int fill_rule) { printf("CALL XSetFillRule\n");  return 0; }

Status XQueryBestStipple( register Display *dpy, Drawable drawable, unsigned int width, unsigned int height, unsigned int *ret_width, unsigned int *ret_height) { printf("CALL XQueryBestStipple\n");  return 0; }

int XKillClient( register Display *dpy, XID resource) { printf("CALL XKillClient\n");  return 0; }

long XEventMaskOfScreen(Screen *s) { printf("CALL XEventMaskOfScreen\n");  return 0; }

int XDestroyImage( XImage *ximage) { printf("CALL XDestroyImage\n");  return 0; }

int XDrawImageString16( register Display *dpy, Drawable d, GC gc, int x, int y, _Xconst XChar2b *string, int length) { printf("CALL XDrawImageString16\n");  return 0; }

Pixmap XCreatePixmapFromBitmapData( Display *display, Drawable d, char *data, unsigned int width, unsigned int height, unsigned long fg, unsigned long bg, unsigned int depth) { printf("CALL XCreatePixmapFromBitmapData\n");  return 0; }

int XActivateScreenSaver(register Display *dpy) { printf("CALL XActivateScreenSaver\n");  return 0; }

int XDrawText16( register Display *dpy, Drawable d, GC gc, int x, int y, XTextItem16 *items, int nitems) { printf("CALL XDrawText16\n");  return 0; }

int XEnableAccessControl(register Display *dpy) { printf("CALL XEnableAccessControl\n");  return 0; }

int XSetAccessControl( register Display *dpy, int mode) { printf("CALL XSetAccessControl\n");  return 0; }

Status XcmsConvertColors( XcmsCCC ccc, XcmsColor *pColors_in_out, unsigned int nColors, XcmsColorFormat targetFormat, Bool *pCompressed) /* * DESCRIPTION * Convert XcmsColor structures to another format * * RETURNS * XcmsFailure if failed, * XcmsSuccess if succeeded without gamut compression, * XcmsSuccessWithCompression if succeeded with gamut * compression. * */ { printf("CALL XcmsConvertColors\n");  return 0; }

Status XcmsTekHVCToCIEuvY( XcmsCCC ccc, XcmsColor *pHVC_WhitePt, XcmsColor *pColors_in_out, unsigned int nColors) /* * DESCRIPTION * Transforms an array of TekHVC color specifications, given * their associated white point, to CIECIEuvY.color * specifications. * * RETURNS * XcmsFailure if failed, XcmsSuccess otherwise. * */ { printf("CALL XcmsTekHVCToCIEuvY\n");  return 0; }

XcmsWhiteAdjustProc XcmsSetWhiteAdjustProc( XcmsCCC ccc, XcmsWhiteAdjustProc white_adjust_proc, XPointer client_data ) /* * DESCRIPTION * Set the specified CCC's white_adjust function and client data. * * RETURNS * Returns the old white_adjust function. * */ { printf("CALL XcmsSetWhiteAdjustProc\n");  return NULL; }

Status XcmsRGBToRGBi( XcmsCCC ccc, XcmsColor *pXcmsColors_in_out,/* pointer to XcmsColors to convert */ unsigned int nColors, /* Number of colors */ Bool *pCompressed) /* pointer to a bit array */ /* * DESCRIPTION * Converts color specifications in an array of XcmsColor * structures from RGB format to RGBi format. * * RETURNS * XcmsFailure if failed, * XcmsSuccess if succeeded. */ { printf("CALL XcmsRGBToRGBi\n");  return 0; }

int XcmsScreenNumberOfCCC( XcmsCCC ccc) /* * DESCRIPTION * Queries the screen number of the specified CCC. * * RETURNS * screen number. * */ { printf("CALL XcmsScreenNumberOfCCC\n");  return 0; }

int XStoreNamedColor( register Display *dpy, Colormap cmap, _Xconst char *name, /* STRING8 */ unsigned long pixel, /* CARD32 */ int flags) /* DoRed, DoGreen, DoBlue */ { printf("CALL XStoreNamedColor\n");  return 0; }

int XUnionRectWithRegion( register XRectangle *rect, Region source, Region dest) { printf("CALL XUnionRectWithRegion\n");  return 0; }

int XTextExtents16 ( XFontStruct *fs, _Xconst XChar2b *string, int nchars, int *dir, /* RETURN font information */ int *font_ascent, /* RETURN font information */ int *font_descent, /* RETURN font information */ register XCharStruct *overall) /* RETURN character information */ { printf("CALL XTextExtents16\n");  return 0; }

int XDrawText( register Display *dpy, Drawable d, GC gc, int x, int y, XTextItem *items, int nitems) { printf("CALL XDrawText\n");  return 0; }

int XTextExtents ( XFontStruct *fs, _Xconst char *string, int nchars, int *dir, /* RETURN font information */ int *font_ascent, /* RETURN font information */ int *font_descent, /* RETURN font information */ register XCharStruct *overall) /* RETURN character information */ { printf("CALL XTextExtents\n");  return 0; }

int XStoreColors( register Display *dpy, Colormap cmap, XColor *defs, int ncolors) { printf("CALL XStoreColors\n");  return 0; }

int XQueryTextExtents16 ( register Display *dpy, Font fid, _Xconst XChar2b *string, register int nchars, int *dir, int *font_ascent, int *font_descent, register XCharStruct *overall) { printf("CALL XQueryTextExtents16\n");  return 0; }

int XSetStipple ( register Display *dpy, GC gc, Pixmap stipple) { printf("CALL XSetStipple\n");  return 0; }

int XGrabButton( register Display *dpy, unsigned int button, /* CARD8 */ unsigned int modifiers, /* CARD16 */ Window grab_window, Bool owner_events, unsigned int event_mask, /* CARD16 */ int pointer_mode, int keyboard_mode, Window confine_to, Cursor curs) { printf("CALL XGrabButton\n");  return 0; }

int XUngrabButton( register Display *dpy, unsigned int button, /* CARD8 */ unsigned int modifiers, /* CARD16 */ Window grab_window) { printf("CALL XUngrabButton\n");  return 0; }

int XQueryKeymap( register Display *dpy, char keys[32]) { printf("CALL XQueryKeymap\n");  return 0; }

int XDrawRectangles( register Display *dpy, Drawable d, GC gc, XRectangle *rects, int n_rects) { printf("CALL XDrawRectangles\n");  return 0; }

unsigned long XDisplayMotionBufferSize(Display *dpy) { printf("CALL XDisplayMotionBufferSize\n");  return 0; }

int XSetPointerMapping ( register Display *dpy, _Xconst unsigned char *map, int nmaps) { printf("CALL XSetPointerMapping\n");  return 0; }

int XFillArcs( register Display *dpy, Drawable d, GC gc, XArc *arcs, int n_arcs) { printf("CALL XFillArcs\n");  return 0; }

int XAddHost ( register Display *dpy, XHostAddress *host) { printf("CALL XAddHost\n");  return 0; }

int XAddHosts ( register Display *dpy, XHostAddress *hosts, int n) { printf("CALL XAddHosts\n");  return 0; }

int XMaskEvent ( register Display *dpy, long mask, /* Selected event mask. */ register XEvent *event) /* XEvent to be filled in. */ { printf("CALL XMaskEvent\n");  return 0; }

int XSetModifierMapping( register Display *dpy, register XModifierKeymap *modifier_map) { printf("CALL XSetModifierMapping\n");  return 0; }

int XRemoveFromSaveSet ( register Display *dpy, Window win) { printf("CALL XRemoveFromSaveSet\n");  return 0; }

int XAllowEvents( register Display *dpy, int mode, Time time) { printf("CALL XAllowEvents\n");  return 0; }

int XUninstallColormap( register Display *dpy, Colormap cmap) { printf("CALL XUninstallColormap\n");  return 0; }

int XForceScreenSaver( register Display *dpy, int mode) { printf("CALL XForceScreenSaver\n");  return 0; }

int XPeekEvent ( register Display *dpy, register XEvent *event) { printf("CALL XPeekEvent\n");  return 0; }

int XGrabKey( register Display *dpy, int key, unsigned int modifiers, Window grab_window, Bool owner_events, int pointer_mode, int keyboard_mode) { printf("CALL XGrabKey\n");  return 0; }

int XDisableAccessControl(register Display *dpy) { printf("CALL XDisableAccessControl\n");  return 0; }

Status XcmsCIEXYZToRGBi( XcmsCCC ccc, XcmsColor *pXcmsColors_in_out,/* pointer to XcmsColors to convert */ unsigned int nColors, /* Number of colors */ Bool *pCompressed) /* pointer to an array of Bool */ /* * DESCRIPTION * Converts color specifications in an array of XcmsColor * structures from RGB format to RGBi format. * * RETURNS * XcmsFailure if failed, * XcmsSuccess if succeeded without gamut compression. * XcmsSuccessWithCompression if succeeded with gamut * compression. */ { printf("CALL XcmsCIEXYZToRGBi\n");  return 0; }

int XGetPointerMapping ( register Display *dpy, unsigned char *map, /* RETURN */ int nmaps) { printf("CALL XGetPointerMapping\n");  return 0; }

Bool XContextDependentDrawing(XFontSet font_set) { printf("CALL XContextDependentDrawing\n");  return False; }

void XrmInitialize(void) { printf("CALL XrmInitialize\n"); }

Status XGetTextProperty ( Display *display, Window window, XTextProperty *tp, Atom property) { printf("CALL XGetTextProperty\n");  return 0; }

int XUngrabKey( register Display *dpy, int key, unsigned int modifiers, Window grab_window) { printf("CALL XUngrabKey\n");  return 0; }

void XwcDrawText( Display *dpy, Drawable d, GC gc, int x, int y, XwcTextItem *text_items, int nitems) { printf("CALL XwcDrawText\n"); }

void XwcDrawString( Display *dpy, Drawable d, XFontSet font_set, GC gc, int x, int y, _Xconst wchar_t *text, int text_len) { printf("CALL XwcDrawString\n"); }

void XwcDrawImageString( Display *dpy, Drawable d, XFontSet font_set, GC gc, int x, int y, _Xconst wchar_t *text, int text_len) { printf("CALL XwcDrawImageString\n"); }

void XmbDrawText( Display *dpy, Drawable d, GC gc, int x, int y, XmbTextItem *text_items, int nitems) { printf("CALL XmbDrawText\n"); }

void XmbDrawString( Display *dpy, Drawable d, XFontSet font_set, GC gc, int x, int y, _Xconst char *text, int text_len) { printf("CALL XmbDrawString\n"); }

void XmbDrawImageString( Display *dpy, Drawable d, XFontSet font_set, GC gc, int x, int y, _Xconst char *text, int text_len) { printf("CALL XmbDrawImageString\n"); }

int XmbTextEscapement( XFontSet font_set, _Xconst char *text, int text_len) { printf("CALL XmbTextEscapement\n");  return 0; }

XIM XIMOfIC(XIC ic) { printf("CALL XIMOfIC\n");  return NULL; }

int XwcLookupString(XIC ic, XKeyEvent *ev, wchar_t *buffer, int nchars, KeySym *keysym, Status *status) { printf("CALL XwcLookupString\n");  return 0; }

int XwcTextPropertyToTextList( Display *dpy, const XTextProperty *text_prop, wchar_t ***list_ret, int *count_ret) { printf("CALL XwcTextPropertyToTextList\n");  return 0; }

int XwcTextListToTextProperty( Display *dpy, wchar_t **list, int count, XICCEncodingStyle style, XTextProperty *text_prop) { printf("CALL XwcTextListToTextProperty\n");  return 0; }

Status XcmsRGBiToCIEXYZ( XcmsCCC ccc, XcmsColor *pXcmsColors_in_out,/* pointer to XcmsColors to convert */ unsigned int nColors, /* Number of colors */ Bool *pCompressed) /* pointer to a bit array */ /* * DESCRIPTION * Converts color specifications in an array of XcmsColor * structures from RGBi format to CIEXYZ format. * * RETURNS * XcmsFailure if failed, * XcmsSuccess if succeeded. */ { printf("CALL XcmsRGBiToCIEXYZ\n");  return 0; }

int XFontsOfFontSet( XFontSet font_set, XFontStruct ***font_struct_list, char ***font_name_list) { printf("CALL XFontsOfFontSet\n");  return 0; }

Region XPolygonRegion( XPoint *Pts, /* the pts */ int Count, /* number of pts */ int rule) /* winding rule */ { printf("CALL XPolygonRegion\n");  return NULL; }

XrmDatabase XrmGetDatabase( Display *display) { printf("CALL XrmGetDatabase\n");  return NULL; }

void XrmStringToQuarkList( register _Xconst char *name, register XrmQuarkList quarks) /* RETURN */ { printf("CALL XrmStringToQuarkList\n"); }

void XrmStringToBindingQuarkList( register _Xconst char *name, register XrmBindingList bindings, /* RETURN */ register XrmQuarkList quarks) /* RETURN */ { printf("CALL XrmStringToBindingQuarkList\n"); }

void XrmPutResource( XrmDatabase *pdb, _Xconst char *specifier, _Xconst char *type, XrmValuePtr value) { printf("CALL XrmPutResource\n"); }

void XrmPutLineResource( XrmDatabase *pdb, _Xconst char*line) { printf("CALL XrmPutLineResource\n"); }

Status XrmCombineFileDatabase( _Xconst char *filename, XrmDatabase *target, Bool override) { printf("CALL XrmCombineFileDatabase\n");  return 0; }

// from Xrm.c
static XrmQuark XrmQString, XrmQANY;
typedef	Bool (*DBEnumProc)(
        XrmDatabase*	/* db */,
        XrmBindingList	/* bindings */,
        XrmQuarkList	/* quarks */,
        XrmRepresentation*	/* type */,
        XrmValue*		/* value */,
        XPointer		/* closure */
);

Bool XrmEnumerateDatabase( XrmDatabase db, XrmNameList names, XrmClassList classes, int mode, DBEnumProc proc, XPointer closure) { printf("CALL XrmEnumerateDatabase\n");  return False; }

Bool XrmQGetSearchResource( XrmSearchList searchList, register XrmName name, register XrmClass class, XrmRepresentation *pType, /* RETURN */ XrmValue *pValue) /* RETURN */ { printf("CALL XrmQGetSearchResource\n");  return False; }

Bool XrmGetResource(XrmDatabase db, _Xconst char *name_str, _Xconst char *class_str, XrmString *pType_str, XrmValuePtr pValue) { printf("CALL XrmGetResource\n");  return False; }

void XrmDestroyDatabase( XrmDatabase db) { printf("CALL XrmDestroyDatabase\n"); }

Status XFetchName ( register Display *dpy, Window w, char **name) { printf("CALL XFetchName\n");  return 0; }

Status XGetIconName ( register Display *dpy, Window w, char **icon_name) { printf("CALL XGetIconName\n");  return 0; }

int XStoreBuffer ( register Display *dpy, _Xconst char *bytes, int nbytes, register int buffer) { printf("CALL XStoreBuffer\n");  return 0; }

int XRebindKeysym ( Display *dpy, KeySym keysym, KeySym *mlist, int nm, /* number of modifiers in mlist */ _Xconst unsigned char *str, int nbytes) { printf("CALL XRebindKeysym\n");  return 0; }

int XSetIconSizes ( Display *dpy, Window w, /* typically, root */ XIconSize *list, int count) /* number of items on the list */ { printf("CALL XSetIconSizes\n");  return 0; }

int XWMGeometry ( Display *dpy, /* user's display connection */ int screen, /* screen on which to do computation */ _Xconst char *user_geom, /* user provided geometry spec */ _Xconst char *def_geom, /* default geometry spec for window */ unsigned int bwidth, /* border width */ XSizeHints *hints, /* usually WM_NORMAL_HINTS */ int *x_return, /* location of window */ int *y_return, /* location of window */ int *width_return, /* size of window */ int *height_return, /* size of window */ int *gravity_return) /* gravity of window */ { printf("CALL XWMGeometry\n");  return 0; }

Status XGetIconSizes ( Display *dpy, Window w, /* typically, root */ XIconSize **size_list, /* RETURN */ int *count) /* RETURN number of items on the list */ { printf("CALL XGetIconSizes\n");  return 0; }

Status XGetCommand ( Display *dpy, Window w, char ***argvp, int *argcp) { printf("CALL XGetCommand\n");  return 0; }

Status XGetTransientForHint( Display *dpy, Window w, Window *propWindow) { printf("CALL XGetTransientForHint\n");  return 0; }

Status XGetClassHint( Display *dpy, Window w, XClassHint *classhint) /* RETURN */ { printf("CALL XGetClassHint\n");  return 0; }

void XwcFreeStringList( wchar_t **list) { printf("CALL XwcFreeStringList\n"); }

void XSetRGBColormaps ( Display *dpy, Window w, XStandardColormap *cmaps, int count, Atom property) /* XA_RGB_BEST_MAP, etc. */ { printf("CALL XSetRGBColormaps\n"); }

Status XGetWMProtocols ( Display *dpy, Window w, Atom **protocols, int *countReturn) { printf("CALL XGetWMProtocols\n");  return 0; }

int XWriteBitmapFile( Display *display, _Xconst char *filename, Pixmap bitmap, unsigned int width, unsigned int height, int x_hot, int y_hot) { printf("CALL XWriteBitmapFile\n");  return 0; }

int XClipBox( Region r, XRectangle *rect) { printf("CALL XClipBox\n");  return 0; }

int XDestroyRegion( Region r) { printf("CALL XDestroyRegion\n");  return 0; }

int XShrinkRegion( Region r, int dx, int dy) { printf("CALL XShrinkRegion\n");  return 0; }

int XEmptyRegion( Region r) { printf("CALL XEmptyRegion\n");  return 0; }

int XRectInRegion( register Region region, int rx, int ry, unsigned int rwidth, unsigned int rheight) { printf("CALL XRectInRegion\n");  return 0; }

Status XGetWMSizeHints ( Display *dpy, Window w, XSizeHints *hints, long *supplied, Atom property) { printf("CALL XGetWMSizeHints\n");  return 0; }

Status XGetWMNormalHints ( Display *dpy, Window w, XSizeHints *hints, long *supplied) { printf("CALL XGetWMNormalHints\n");  return 0; }

int XReadBitmapFile ( Display *display, Drawable d, _Xconst char *filename, unsigned int *width, /* RETURNED */ unsigned int *height, /* RETURNED */ Pixmap *pixmap, /* RETURNED */ int *x_hot, /* RETURNED */ int *y_hot) /* RETURNED */ { printf("CALL XReadBitmapFile\n");  return 0; }

Status XTextPropertyToStringList ( XTextProperty *tp, char ***list_return, int *count_return) { printf("CALL XTextPropertyToStringList\n");  return 0; }

Status XGetRGBColormaps ( Display *dpy, Window w, XStandardColormap **stdcmap, /* RETURN */ int *count, /* RETURN */ Atom property) /* XA_RGB_BEST_MAP, etc. */ { printf("CALL XGetRGBColormaps\n");  return 0; }

void XrmCombineDatabase( XrmDatabase from, XrmDatabase *into, Bool override) { printf("CALL XrmCombineDatabase\n"); }

void XrmQPutStringResource( XrmDatabase *pdb, XrmBindingList bindings, XrmQuarkList quarks, _Xconst char *str) { printf("CALL XrmQPutStringResource\n"); }

void XrmPutStringResource( XrmDatabase *pdb, _Xconst char*specifier, _Xconst char*str) { printf("CALL XrmPutStringResource\n"); }

XrmDatabase XrmGetStringDatabase( _Xconst char *data) { printf("CALL XrmGetStringDatabase\n");  return NULL; }

XrmDatabase XrmGetFileDatabase( _Xconst char *filename) { printf("CALL XrmGetFileDatabase\n");  return NULL; }

void XrmPutFileDatabase( XrmDatabase db, _Xconst char *fileName) { printf("CALL XrmPutFileDatabase\n"); }

Bool XrmQGetSearchList( XrmDatabase db, XrmNameList names, XrmClassList classes, XrmSearchList searchList, /* RETURN */ int listLength) { printf("CALL XrmQGetSearchList\n");  return False; }

int XStoreBytes ( register Display *dpy, _Xconst char *bytes, int nbytes) { printf("CALL XStoreBytes\n");  return 0; }

Status XGetWMName ( Display *dpy, Window w, XTextProperty *tp) { printf("CALL XGetWMName\n");  return 0; }

Status XGetWMIconName ( Display *dpy, Window w, XTextProperty *tp) { printf("CALL XGetWMIconName\n");  return 0; }

Status XGetWMClientMachine ( Display *dpy, Window w, XTextProperty *tp) { printf("CALL XGetWMClientMachine\n");  return 0; }

Region XCreateRegion(void) { printf("CALL XCreateRegion\n");  return NULL; }

int XSetRegion( Display *dpy, GC gc, register Region r) { printf("CALL XSetRegion\n");  return 0; }

int XIntersectRegion( Region reg1, Region reg2, /* source regions */ register Region newReg) /* destination Region */ { printf("CALL XIntersectRegion\n");  return 0; }

int XXorRegion(Region sra, Region srb, Region dr) { printf("CALL XXorRegion\n");  return 0; }

int XEqualRegion(Region r1, Region r2) { printf("CALL XEqualRegion\n");  return 0; }

void XrmSetDatabase( Display *display, XrmDatabase database) { printf("CALL XrmSetDatabase\n"); }

void XrmMergeDatabases( XrmDatabase from, XrmDatabase *into) { printf("CALL XrmMergeDatabases\n"); }

void XrmQPutResource( XrmDatabase *pdb, XrmBindingList bindings, XrmQuarkList quarks, XrmRepresentation type, XrmValuePtr value) { printf("CALL XrmQPutResource\n"); }

Bool XrmQGetResource( XrmDatabase db, XrmNameList names, XrmClassList classes, XrmRepresentation *pType, /* RETURN */ XrmValuePtr pValue) /* RETURN */ { printf("CALL XrmQGetResource\n");  return False; }

int XOffsetRegion( register Region pRegion, register int x, register int y) { printf("CALL XOffsetRegion\n");  return 0; }

int XUnionRegion( Region reg1, Region reg2, /* source regions */ Region newReg) /* destination Region */ { printf("CALL XUnionRegion\n");  return 0; }

int XPointInRegion( Region pRegion, int x, int y) { printf("CALL XPointInRegion\n");  return 0; }

Atom *XListProperties( register Display *dpy, Window window, int *n_props) /* RETURN */ { printf("CALL XListProperties\n");  return NULL; }

char *XScreenResourceString(Screen *screen) { printf("CALL XScreenResourceString\n");  return NULL; }

XImage *XGetSubImage( register Display *dpy, Drawable d, int x, int y, unsigned int width, unsigned int height, unsigned long plane_mask, int format, /* either XYPixmap or ZPixmap */ XImage *dest_image, int dest_x, int dest_y) { printf("CALL XGetSubImage\n");  return NULL; }

char *XFetchBuffer ( register Display *dpy, int *nbytes, register int buffer) { printf("CALL XFetchBuffer\n");  return NULL; }

char *XFetchBytes ( register Display *dpy, int *nbytes) { printf("CALL XFetchBytes\n");  return NULL; }

char *XResourceManagerString(Display *dpy) { printf("CALL XResourceManagerString\n");  return NULL; }

Colormap *XListInstalledColormaps( register Display *dpy, Window win, int *n) /* RETURN */ { printf("CALL XListInstalledColormaps\n");  return 0; }

XWMHints *XGetWMHints ( Display *dpy, Window w) { printf("CALL XGetWMHints\n");  return NULL; }

XTimeCoord *XGetMotionEvents( register Display *dpy, Window w, Time start, Time stop, int *nEvents) /* RETURN */ { printf("CALL XGetMotionEvents\n");  return NULL; }

XStandardColormap *XAllocStandardColormap (void) { printf("CALL XAllocStandardColormap\n");  return NULL; }

XIconSize *XAllocIconSize (void) { printf("CALL XAllocIconSize\n");  return NULL; }

static int _XSyncFunction(register Display *dpy)
{
    XSync(dpy,0);
    return 0;
}

int (*XSynchronize(Display *dpy, int onoff))(Display *)
{
    int (*temp)(Display *);
    int (*func)(Display *) = NULL;

    if (onoff)
        func = _XSyncFunction;

    LockDisplay(dpy);
    if (dpy->flags & XlibDisplayPrivSync) {
        temp = dpy->savedsynchandler;
        dpy->savedsynchandler = func;
    } else {
        temp = dpy->synchandler;
        dpy->synchandler = func;
    }
    UnlockDisplay(dpy);
    return (temp);
}

int (*XSetAfterFunction(
        Display *dpy,
        int (*func)(
                Display*
        )
))(Display *)
{
    int (*temp)(Display *);

    LockDisplay(dpy);
    if (dpy->flags & XlibDisplayPrivSync) {
        temp = dpy->savedsynchandler;
        dpy->savedsynchandler = func;
    } else {
        temp = dpy->synchandler;
        dpy->synchandler = func;
    }
    UnlockDisplay(dpy);
    return (temp);
}

int XGetErrorDatabaseText( Display *dpy, register _Xconst char *name, register _Xconst char *type, _Xconst char *defaultp, char *buffer, int nbytes) { printf("CALL XGetErrorDatabaseText\n");  return 0; }

Status XcmsQueryBlack( XcmsCCC ccc, XcmsColorFormat target_format, XcmsColor *pColor_ret) { printf("CALL XcmsQueryBlack\n");  return 0; }

XcmsCCC XcmsDefaultCCC( Display *dpy, int screenNumber) { printf("CALL XcmsDefaultCCC\n");  return NULL; }

void XcmsFreeCCC(XcmsCCC ccc) { printf("CALL XcmsFreeCCC\n"); }

Status XcmsTekHVCQueryMinV ( XcmsCCC ccc, XcmsFloat hue, XcmsFloat chroma, XcmsColor *pColor_return) { printf("CALL XcmsTekHVCQueryMinV\n");  return 0; }

Status XcmsAllocColor( Display *dpy, Colormap colormap, XcmsColor *pXcmsColor_in_out, XcmsColorFormat result_format) { printf("CALL XcmsAllocColor\n");  return 0; }

XcmsColorFormat XcmsFormatOfPrefix(char *prefix) { printf("CALL XcmsFormatOfPrefix\n");  return 0; }

Status XcmsQueryBlue( XcmsCCC ccc, XcmsColorFormat target_format, XcmsColor *pColor_ret) { printf("CALL XcmsQueryBlue\n");  return 0; }

Status XcmsCIELabQueryMaxLC ( XcmsCCC ccc, XcmsFloat hue_angle, XcmsColor *pColor_return) { printf("CALL XcmsCIELabQueryMaxLC\n");  return 0; }

Status XcmsTekHVCQueryMaxV( XcmsCCC ccc, XcmsFloat hue, XcmsFloat chroma, XcmsColor *pColor_return) { printf("CALL XcmsTekHVCQueryMaxV\n");  return 0; }

Status XcmsQueryWhite( XcmsCCC ccc, XcmsColorFormat target_format, XcmsColor *pColor_ret) { printf("CALL XcmsQueryWhite\n");  return 0; }

Status XcmsCIELabToCIEXYZ( XcmsCCC ccc, XcmsColor *pLab_WhitePt, XcmsColor *pColors_in_out, unsigned int nColors) { printf("CALL XcmsCIELabToCIEXYZ\n");  return 0; }

Status XcmsSetWhitePoint( XcmsCCC ccc, XcmsColor *pColor) { printf("CALL XcmsSetWhitePoint\n");  return 0; }

Status XcmsCIELuvQueryMaxC( XcmsCCC ccc, XcmsFloat hue_angle, XcmsFloat L_star, XcmsColor *pColor_return) { printf("CALL XcmsCIELuvQueryMaxC\n");  return 0; }

Status XcmsCIELuvQueryMaxL( XcmsCCC ccc, XcmsFloat hue_angle, XcmsFloat chroma, XcmsColor *pColor_return) { printf("CALL XcmsCIELuvQueryMaxL\n");  return 0; }

Status XcmsTekHVCQueryMaxVSamples( XcmsCCC ccc, XcmsFloat hue, XcmsColor *pColor_in_out, unsigned int nSamples) { printf("CALL XcmsTekHVCQueryMaxVSamples\n");  return 0; }

Status XcmsAddColorSpace(XcmsColorSpace *pCS) { printf("CALL XcmsAddColorSpace\n");  return 0; }

Status XcmsQueryColors( Display *dpy, Colormap colormap, XcmsColor *pXcmsColors_in_out, unsigned int nColors, XcmsColorFormat result_format) { printf("CALL XcmsQueryColors\n");  return 0; }

Status XcmsTekHVCQueryMaxC( XcmsCCC ccc, XcmsFloat hue, XcmsFloat value, XcmsColor *pColor_return) { printf("CALL XcmsTekHVCQueryMaxC\n");  return 0; }

Status XcmsCIELuvQueryMinL( XcmsCCC ccc, XcmsFloat hue_angle, XcmsFloat chroma, XcmsColor *pColor_return) { printf("CALL XcmsCIELuvQueryMinL\n");  return 0; }

XcmsCCC XcmsCCCOfColormap( Display *dpy, Colormap cmap) { printf("CALL XcmsCCCOfColormap\n");  return NULL; }

Status XcmsQueryColor( Display *dpy, Colormap colormap, XcmsColor *pXcmsColor_in_out, XcmsColorFormat result_format) { printf("CALL XcmsQueryColor\n");  return 0; }

Status XcmsCIELuvQueryMaxLC ( XcmsCCC ccc, XcmsFloat hue_angle, XcmsColor *pColor_return) { printf("CALL XcmsCIELuvQueryMaxLC\n");  return 0; }

Status XcmsAllocNamedColor ( Display *dpy, Colormap cmap, _Xconst char *colorname, XcmsColor *pColor_scrn_return, XcmsColor *pColor_exact_return, XcmsColorFormat result_format) { printf("CALL XcmsAllocNamedColor\n");  return 0; }

void XmbSetWMProperties ( Display *dpy, Window w, _Xconst char *windowName, _Xconst char *iconName, char **argv, int argc, XSizeHints *sizeHints, XWMHints *wmHints, XClassHint *classHints) { printf("CALL XmbSetWMProperties\n"); }

Status XcmsQueryGreen( XcmsCCC ccc, XcmsColorFormat target_format, XcmsColor *pColor_ret) { printf("CALL XcmsQueryGreen\n");  return 0; }

Status XcmsStoreColors( Display *dpy, Colormap colormap, XcmsColor *pColors_in, unsigned int nColors, Bool *pCompressed) { printf("CALL XcmsStoreColors\n");  return 0; }

Status XcmsLookupColor ( Display *dpy, Colormap cmap, _Xconst char *colorname, XcmsColor *pColor_exact_return, XcmsColor *pColor_scrn_return, XcmsColorFormat result_format) { printf("CALL XcmsLookupColor\n");  return 0; }

Status XcmsTekHVCQueryMaxVC ( XcmsCCC ccc, XcmsFloat hue, XcmsColor *pColor_return) { printf("CALL XcmsTekHVCQueryMaxVC\n");  return 0; }

Status XcmsStoreColor( Display *dpy, Colormap colormap, XcmsColor *pColor_in) { printf("CALL XcmsStoreColor\n");  return 0; }

Status XcmsCIELabQueryMaxC( XcmsCCC ccc, XcmsFloat hue_angle, XcmsFloat L_star, XcmsColor *pColor_return) { printf("CALL XcmsCIELabQueryMaxC\n");  return 0; }

Status XcmsQueryRed( XcmsCCC ccc, XcmsColorFormat target_format, XcmsColor *pColor_ret) { printf("CALL XcmsQueryRed\n");  return 0; }

Status XcmsAddFunctionSet(XcmsFunctionSet *pNewFS) { printf("CALL XcmsAddFunctionSet\n");  return 0; }

Status XcmsCIELuvWhiteShiftColors( XcmsCCC ccc, XcmsColor *pWhitePtFrom, XcmsColor *pWhitePtTo, XcmsColorFormat destSpecFmt, XcmsColor *pColors_in_out, unsigned int nColors, Bool *pCompressed) { printf("CALL XcmsCIELuvWhiteShiftColors\n");  return 0; }

Status XcmsCIELabQueryMaxL( XcmsCCC ccc, XcmsFloat hue_angle, XcmsFloat chroma, XcmsColor *pColor_return) { printf("CALL XcmsCIELabQueryMaxL\n");  return 0; }

Status XcmsCIELabQueryMinL( XcmsCCC ccc, XcmsFloat hue_angle, XcmsFloat chroma, XcmsColor *pColor_return) { printf("CALL XcmsCIELabQueryMinL\n");  return 0; }

Status XcmsCIEXYZToCIEuvY( XcmsCCC ccc, XcmsColor *puvY_WhitePt, XcmsColor *pColors_in_out, unsigned int nColors) { printf("CALL XcmsCIEXYZToCIEuvY\n");  return 0; }

void XrmParseCommand( XrmDatabase *pdb, register XrmOptionDescList options, int num_options, _Xconst char *prefix, int *argc, char **argv) { printf("CALL XrmParseCommand\n"); }

int XRotateBuffers ( register Display *dpy, int rotate) { printf("CALL XRotateBuffers\n");  return 0; }

Status XcmsCIELabWhiteShiftColors( XcmsCCC ccc, XcmsColor *pWhitePtFrom, XcmsColor *pWhitePtTo, XcmsColorFormat destSpecFmt, XcmsColor *pColors_in_out, unsigned int nColors, Bool *pCompressed) { printf("CALL XcmsCIELabWhiteShiftColors\n");  return 0; }

Status XcmsCIEXYZToCIELab( XcmsCCC ccc, XcmsColor *pLab_WhitePt, XcmsColor *pColors_in_out, unsigned int nColors) { printf("CALL XcmsCIEXYZToCIELab\n");  return 0; }

Status XcmsTekHVCWhiteShiftColors( XcmsCCC ccc, XcmsColor *pWhitePtFrom, XcmsColor *pWhitePtTo, XcmsColorFormat destSpecFmt, XcmsColor *pColors_in_out, unsigned int nColors, Bool *pCompressed) { printf("CALL XcmsTekHVCWhiteShiftColors\n");  return 0; }

Status XcmsCIEuvYToCIEXYZ( XcmsCCC ccc, XcmsColor *puvY_WhitePt, XcmsColor *pColors_in_out, unsigned int nColors) { printf("CALL XcmsCIEuvYToCIEXYZ\n");  return 0; }

Status XcmsCIEXYZToCIExyY( XcmsCCC ccc, XcmsColor *pxyY_WhitePt, XcmsColor *pColors_in_out, unsigned int nColors) { printf("CALL XcmsCIEXYZToCIExyY\n");  return 0; }

const char *XrmLocaleOfDatabase( XrmDatabase db) { printf("CALL XrmLocaleOfDatabase\n");  return NULL; }

char *XGetDefault( Display *dpy, char _Xconst *prog, register _Xconst char *name) { printf("CALL XGetDefault\n");  return NULL; }

XModifierKeymap *XNewModifiermap(int keyspermodifier) { printf("CALL XNewModifiermap\n");  return NULL; }

wchar_t *XwcResetIC(XIC ic) { printf("CALL XwcResetIC\n");  return NULL; }

const char *XDefaultString(void) { printf("CALL XDefaultString\n");  return NULL; }

char *XcmsPrefixOfFormat( XcmsColorFormat id) { printf("CALL XcmsPrefixOfFormat\n");  return NULL; }

Display *XcmsDisplayOfCCC( XcmsCCC ccc) { printf("CALL XcmsDisplayOfCCC\n");  return NULL; }

Visual *XcmsVisualOfCCC( XcmsCCC ccc) { printf("CALL XcmsVisualOfCCC\n");  return NULL; }

XcmsColor *XcmsScreenWhitePointOfCCC( XcmsCCC ccc) { printf("CALL XcmsScreenWhitePointOfCCC\n");  return NULL; }

XcmsColor *XcmsClientWhitePointOfCCC( XcmsCCC ccc) { printf("CALL XcmsClientWhitePointOfCCC\n");  return NULL; }

char *XBaseFontNameListOfFontSet(XFontSet font_set) { printf("CALL XBaseFontNameListOfFontSet\n");  return NULL; }

char *XLocaleOfFontSet(XFontSet font_set) { printf("CALL XLocaleOfFontSet\n");  return NULL; }

XFontSetExtents *XExtentsOfFontSet(XFontSet font_set) { printf("CALL XExtentsOfFontSet\n");  return NULL; }

int XwcTextEscapement( XFontSet font_set, _Xconst wchar_t *text, int text_len) { printf("CALL XwcTextEscapement\n");  return 0; }

int XwcTextExtents( XFontSet font_set, _Xconst wchar_t *text, int text_len, XRectangle *overall_ink_extents, XRectangle *overall_logical_extents) { printf("CALL XwcTextExtents\n");  return 0; }

Status XwcTextPerCharExtents( XFontSet font_set, _Xconst wchar_t *text, int text_len, XRectangle *ink_extents_buffer, XRectangle *logical_extents_buffer, int buffer_size, int *num_chars, XRectangle *max_ink_extents, XRectangle *max_logical_extents) { printf("CALL XwcTextPerCharExtents\n");  return 0; }

int XmbTextExtents( XFontSet font_set, _Xconst char *text, int text_len, XRectangle *overall_ink_extents, XRectangle *overall_logical_extents) { printf("CALL XmbTextExtents\n");  return 0; }

Status XmbTextPerCharExtents( XFontSet font_set, _Xconst char *text, int text_len, XRectangle *ink_extents_buffer, XRectangle *logical_extents_buffer, int buffer_size, int *num_chars, XRectangle *max_ink_extents, XRectangle *max_logical_extents) { printf("CALL XmbTextPerCharExtents\n");  return 0; }

Status XcmsCIEuvYToCIELuv( XcmsCCC ccc, XcmsColor *pLuv_WhitePt, XcmsColor *pColors_in_out, unsigned int nColors) { printf("CALL XcmsCIEuvYToCIELuv\n");  return 0; }

Status XcmsCIExyYToCIEXYZ( XcmsCCC ccc, XcmsColor *pxyY_WhitePt, XcmsColor *pColors_in_out, unsigned int nColors) { printf("CALL XcmsCIExyYToCIEXYZ\n");  return 0; }

XcmsColorSpace	XcmsCIELabColorSpace = {};
XcmsColorSpace	XcmsCIEXYZColorSpace = {};

int
XIfEvent (
        register Display *dpy,
        register XEvent *event,
        Bool (*predicate)(
                Display*			/* display */,
                XEvent*			/* event */,
                char*				/* arg */
        ),		/* function to call */
        char *arg)
{ return 0; }

int
XPeekIfEvent (
        register Display *dpy,
        register XEvent *event,
        Bool (*predicate)(
                Display*			/* display */,
                XEvent*			/* event */,
                char*				/* arg */
        ),
        char *arg)
{ return 0; }

XModifierKeymap *
XInsertModifiermapEntry(XModifierKeymap *map,
                        KeyCode keycode,
                        int modifier)
{ return NULL; }

XModifierKeymap *
XDeleteModifiermapEntry(XModifierKeymap *map,
                        KeyCode keycode,
                        int modifier)
{ return NULL; }

char **XListFontsWithInfo(
        register Display *dpy,
        _Xconst char *pattern,  /* null-terminated */
        int maxNames,
        int *actualCount,	/* RETURN */
        XFontStruct **info)	/* RETURN */
{ return NULL; }

