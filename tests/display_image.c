#include     <stdio.h>
#include     <stdlib.h>
#include     <string.h>
#include     <X11/Xlib.h>

// modified from https://github.com/QMonkey/Xlib-demo/blob/master/src/display_image.c

XImage *CreateTrueColorImage(Display *display, Visual *visual, unsigned char *image, int width, int height)
{
    int i, j;
    unsigned char *image32=(unsigned char *)malloc(width*height*4);
    unsigned char *p=image32;
    for(i=0; i<width; i++)
    {
        for(j=0; j<height; j++)
        {
            if((i<width/2)&&(j<height/2))
            {
                *p++=rand()%256; // blue
                *p++=rand()%256; // green
                *p++=rand()%256; // red
            }
            else
            {
                *p++=i%256; // blue
                *p++=j%256; // green
                if(i<width/2)
                    *p++=i%256; // red
                else if(j<height/2)
                    *p++=j%256; // red
                else
                    *p++=(256-j)%256; // red
            }
            p++;
        }
    }
    return XCreateImage(display, visual, DefaultDepth(display,DefaultScreen(display)), ZPixmap, 0, image32, width, height, 32, 0);
}

void processEvent(Display *display, Window window, XImage *ximage, int width, int height)
{
    static char *tir="This is red";
    static char *tig="This is green";
    static char *tib="This is blue";
    XEvent ev;
    XNextEvent(display, &ev);
    switch(ev.type)
    {
        case Expose:
            XPutImage(display, window, DefaultGC(display, 0), ximage, 0, 0, 0, 0, width, height);
            XSetForeground(display, DefaultGC(display, 0), 0x00ff0000); // red
            XDrawString(display, window, DefaultGC(display, 0), 32,     32,     tir, strlen(tir));
            XDrawString(display, window, DefaultGC(display, 0), 32+width/2, 32,     tir, strlen(tir));
            XDrawString(display, window, DefaultGC(display, 0), 32+width/2, 32+height/2, tir, strlen(tir));
            XDrawString(display, window, DefaultGC(display, 0), 32,     32+height/2, tir, strlen(tir));
            XSetForeground(display, DefaultGC(display, 0), 0x0000ff00); // green
            XDrawString(display, window, DefaultGC(display, 0), 32,     52,     tig, strlen(tig));
            XDrawString(display, window, DefaultGC(display, 0), 32+width/2, 52,     tig, strlen(tig));
            XDrawString(display, window, DefaultGC(display, 0), 32+width/2, 52+height/2, tig, strlen(tig));
            XDrawString(display, window, DefaultGC(display, 0), 32,     52+height/2, tig, strlen(tig));
            XSetForeground(display, DefaultGC(display, 0), 0x000000ff); // blue
            XDrawString(display, window, DefaultGC(display, 0), 32,     72,     tib, strlen(tib));
            XDrawString(display, window, DefaultGC(display, 0), 32+width/2, 72,     tib, strlen(tib));
            XDrawString(display, window, DefaultGC(display, 0), 32+width/2, 72+height/2, tib, strlen(tib));
            XDrawString(display, window, DefaultGC(display, 0), 32,     72+height/2, tib, strlen(tib));
            break;
        case ButtonPress:
            exit(0);
    }
}

int main(int argc, char **argv)
{
    XImage *ximage;
    int width=320, height=320;
    Display *display=XOpenDisplay(NULL);
    Visual *visual=DefaultVisual(display, 0);
    //Window window=XCreateSimpleWindow(display, RootWindow(display, 0), 0, 0, width, height, 1, 0, 0);
    Window window=XCreateWindow(display, RootWindow(display, 0), 0, 0, width, height, 5, CopyFromParent, CopyFromParent, CopyFromParent, 0, NULL);
    if(visual->class!=TrueColor)
    {
        fprintf(stderr, "Cannot handle non true color visual ...\n");
        exit(1);
    }

    ximage=CreateTrueColorImage(display, visual, 0, width, height);
    XSelectInput(display, window, ButtonPressMask|ExposureMask);
    XMapWindow(display, window);
    while(1)
    {
        processEvent(display, window, ximage, width, height);
    }
}