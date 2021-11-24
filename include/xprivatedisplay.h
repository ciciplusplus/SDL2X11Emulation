#include <X11/Xlib.h>
#include <X11/Xproto.h>		/* to declare xEvent */
#include <X11/XlibConf.h>	/* for configured options like XTHREADS */

typedef struct _MyXDisplay
{
    XExtData *ext_data;	/* hook for extension to hang data */
    struct _XFreeFuncs *free_funcs; /* internal free functions */
    int fd;			/* Network socket. */
    int conn_checker;         /* ugly thing used by _XEventsQueued */
    int proto_major_version;/* maj. version of server's X protocol */
    int proto_minor_version;/* minor version of server's X protocol */
    char *vendor;		/* vendor of the server hardware */
    XID resource_base;	/* resource ID base */
    XID resource_mask;	/* resource ID mask bits */
    XID resource_id;	/* allocator current ID */
    int resource_shift;	/* allocator shift to correct bits */
    XID (*resource_alloc)(	/* allocator function */
            struct _XDisplay*
    );
    int byte_order;		/* screen byte order, LSBFirst, MSBFirst */
    int bitmap_unit;	/* padding and data requirements */
    int bitmap_pad;		/* padding requirements on bitmaps */
    int bitmap_bit_order;	/* LeastSignificant or MostSignificant */
    int nformats;		/* number of pixmap formats in list */
    ScreenFormat *pixmap_format;	/* pixmap format list */
    int vnumber;		/* Xlib's X protocol version number. */
    int release;		/* release of the server */
    struct _XSQEvent *head, *tail;	/* Input event queue. */
    int qlen;		/* Length of input event queue */
    unsigned long last_request_read; /* seq number of last event read */
    unsigned long request;	/* sequence number of last request. */
    char *last_req;		/* beginning of last request, or dummy */
    char *buffer;		/* Output buffer starting address. */
    char *bufptr;		/* Output buffer index pointer. */
    char *bufmax;		/* Output buffer maximum+1 address. */
    unsigned max_request_size; /* maximum number 32 bit words in request*/
    struct _XrmHashBucketRec *db;
    int (*synchandler)(	/* Synchronization handler */
            struct _XDisplay*
    );
    char *display_name;	/* "host:display" string used on this connect*/
    int default_screen;	/* default screen for operations */
    int nscreens;		/* number of screens on this server*/
    Screen *screens;	/* pointer to list of screens */
    unsigned long motion_buffer;	/* size of motion buffer */
    volatile unsigned long flags;	   /* internal connection flags */
    int min_keycode;	/* minimum defined keycode */
    int max_keycode;	/* maximum defined keycode */
    KeySym *keysyms;	/* This server's keysyms */
    XModifierKeymap *modifiermap;	/* This server's modifier keymap */
    int keysyms_per_keycode;/* number of rows */
    char *xdefaults;	/* contents of defaults from server */
    char *scratch_buffer;	/* place to hang scratch buffer */
    unsigned long scratch_length;	/* length of scratch buffer */
    int ext_number;		/* extension number on this display */
    struct _XExten *ext_procs; /* extensions initialized on this display */
    /*
     * the following can be fixed size, as the protocol defines how
     * much address space is available.
     * While this could be done using the extension vector, there
     * may be MANY events processed, so a search through the extension
     * list to find the right procedure for each event might be
     * expensive if many extensions are being used.
     */
    Bool (*event_vec[128])(	/* vector for wire to event */
            Display *	/* dpy */,
            XEvent *	/* re */,
            xEvent *	/* event */
    );
    Status (*wire_vec[128])( /* vector for event to wire */
            Display *	/* dpy */,
            XEvent *	/* re */,
            xEvent *	/* event */
    );
    KeySym lock_meaning;	   /* for XLookupString */
    struct _XLockInfo *lock;   /* multi-thread state, display lock */
    struct _XInternalAsync *async_handlers; /* for internal async */
    unsigned long bigreq_size; /* max size of big requests */
    struct _XLockPtrs *lock_fns; /* pointers to threads functions */
    void (*idlist_alloc)(	   /* XID list allocator function */
            Display *	/* dpy */,
            XID *		/* ids */,
            int		/* count */
    );
    /* things above this line should not move, for binary compatibility */
    struct _XKeytrans *key_bindings; /* for XLookupString */
    Font cursor_font;	   /* for XCreateFontCursor */
    struct _XDisplayAtoms *atoms; /* for XInternAtom */
    unsigned int mode_switch;  /* keyboard group modifiers */
    unsigned int num_lock;  /* keyboard numlock modifiers */
    struct _XContextDB *context_db; /* context database */
    Bool (**error_vec)(	/* vector for wire to error */
            Display     *	/* display */,
            XErrorEvent *	/* he */,
            xError      *	/* we */
    );
    /*
     * Xcms information
     */
    struct {
        XPointer defaultCCCs;  /* pointer to an array of default XcmsCCC */
        XPointer clientCmaps;  /* pointer to linked list of XcmsCmapRec */
        XPointer perVisualIntensityMaps;
        /* linked list of XcmsIntensityMap */
    } cms;
    struct _XIMFilter *im_filters;
    struct _XSQEvent *qfree; /* unallocated event queue elements */
    unsigned long next_event_serial_num; /* inserted into next queue elt */
    struct _XExten *flushes; /* Flush hooks */
    struct _XConnectionInfo *im_fd_info; /* _XRegisterInternalConnection */
    int im_fd_length;	/* number of im_fd_info */
    struct _XConnWatchInfo *conn_watchers; /* XAddConnectionWatch */
    int watcher_count;	/* number of conn_watchers */
    XPointer filedes;	/* struct pollfd cache for _XWaitForReadable */
    int (*savedsynchandler)( /* user synchandler when Xlib usurps */
            Display *	/* dpy */
    );
    XID resource_max;	/* allocator max ID */
    int xcmisc_opcode;	/* major opcode for XC-MISC */
    struct _XkbInfoRec *xkb_info; /* XKB info */
    struct _XtransConnInfo *trans_conn; /* transport connection object */
    struct _X11XCBPrivate *xcb; /* XCB glue private data */

    /* Generic event cookie handling */
    unsigned int next_cookie; /* next event cookie */
    /* vector for wire to generic event, index is (extension - 128) */
    Bool (*generic_event_vec[128])(
            Display *	/* dpy */,
            XGenericEventCookie *	/* Xlib event */,
            xEvent *	/* wire event */);
    /* vector for event copy, index is (extension - 128) */
    Bool (*generic_event_copy_vec[128])(
            Display *	/* dpy */,
            XGenericEventCookie *	/* in */,
            XGenericEventCookie *   /* out*/);
    void *cookiejar;  /* cookie events returned but not claimed */
} _MyXDisplay;

/*
 * Note that some machines do not return a valid pointer for malloc(0), in
 * which case we provide an alternate under the control of the
 * define MALLOC_0_RETURNS_NULL.  This is necessary because some
 * Xlib code expects malloc(0) to return a valid pointer to storage.
 */
#if defined(MALLOC_0_RETURNS_NULL) || defined(__clang_analyzer__)

# define Xmalloc(size) malloc(((size) == 0 ? 1 : (size)))
# define Xrealloc(ptr, size) realloc((ptr), ((size) == 0 ? 1 : (size)))
# define Xcalloc(nelem, elsize) calloc(((nelem) == 0 ? 1 : (nelem)), (elsize))

#else

# define Xmalloc(size) malloc((size))
# define Xrealloc(ptr, size) realloc((ptr), (size))
# define Xcalloc(nelem, elsize) calloc((nelem), (elsize))

#endif

typedef void (*FreeFuncType) (
        Display*	/* display */
);

typedef int (*FreeModmapType) (
        XModifierKeymap*	/* modmap */
);

/*
 * This structure is private to the library.
 */
typedef struct _XFreeFuncs {
    FreeFuncType atoms;		/* _XFreeAtomTable */
    FreeModmapType modifiermap;	/* XFreeModifiermap */
    FreeFuncType key_bindings;	/* _XFreeKeyBindings */
    FreeFuncType context_db;	/* _XFreeContextDB */
    FreeFuncType defaultCCCs;	/* _XcmsFreeDefaultCCCs */
    FreeFuncType clientCmaps;	/* _XcmsFreeClientCmaps */
    FreeFuncType intensityMaps;	/* _XcmsFreeIntensityMaps */
    FreeFuncType im_filters;	/* _XFreeIMFilters */
    FreeFuncType xkb;		/* _XkbFreeInfo */
} _XFreeFuncRec;
