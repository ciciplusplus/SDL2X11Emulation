/*
xfonts.c
*/

#include <X11/Xlib.h>
#include <stdio.h>
#include <assert.h>

int main()
{
    Display *dpy;                /* structure describing X session*/
    int num_fonts;               /* number of fonts X server found */
    char **fontlist;             /* array of strings
                                  (available font names) */

    /* get the connection to X */
    /* Normally, the default display is unix:0 */
    dpy = XOpenDisplay ("unix:0");

    //XSetFontPath(dpy, NULL, 0);

    /* Get the names of all fonts that might be Helvetica fonts */
    /* (have "helv" appearing in their font name) */
    fontlist = XListFonts (dpy, "*", 1000, &num_fonts);

    /* other useful X font subroutines are:
     * XListFonts
     * XListFontsWithInfo
     * XFreeFontNames
     * XFreeFontInfo
     * XSetFontPath
     * XGetFontPath
     * XFreeFontPath
     */

    /* We have decided, by some criteria, to use the fifth
     * available Helvetica font (assuming that at least five
     * Helvetica fonts are found). We will give it an id of 433.
     */

    printf("Found fonts %d\n", num_fonts);

    for (int i = 0; i < num_fonts; ++i) {
        printf("%d: %s\n", i, fontlist[i]);

        XFontStruct *xfs = XLoadQueryFont(dpy, fontlist[i]);
        XFontStruct *xfsToo = XQueryFont(dpy, xfs->fid);

        assert(xfs->n_properties == xfsToo->n_properties);
        assert(xfs->min_char_or_byte2 == xfsToo->min_char_or_byte2);
        assert(xfs->max_char_or_byte2 == xfsToo->max_char_or_byte2);
    }

//    if ( num_fonts < 4 ) {
//        fprintf (stderr,"Not enough fonts found!!!\n");
//        return -1;
//    }

    /* get rid of the font name list */
    XFreeFontNames (fontlist);

    return 0;
}