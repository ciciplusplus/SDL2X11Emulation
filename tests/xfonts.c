/*
xfonts.c
*/

#include <X11/Xlib.h>
#include <stdio.h>

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
    }

//    if ( num_fonts < 4 ) {
//        fprintf (stderr,"Not enough fonts found!!!\n");
//        return -1;
//    }

    /* get rid of the font name list */
    XFreeFontNames (fontlist);

    return 0;
}