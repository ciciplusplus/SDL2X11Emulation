// from https://stackoverflow.com/a/17056616

//g++ test.cc -lX11
#include<iostream>
#include<unistd.h>
#include<X11/Xlib.h>
#include<X11/Xutil.h>

Display *display;


class Metallica{
private:
    Window window;


public:
    int i;
    Metallica(int j, XContext *context){
        i=j;
        this->window = XCreateSimpleWindow(display,DefaultRootWindow(display),100,100,100,100,0,0,0);
        XSelectInput(display, this->window, ExposureMask|ButtonReleaseMask|KeyReleaseMask);
        XMapWindow(display,this->window);
        XSaveContext(display, this->window, *context, XPointer(this));
    };
    void MasterOfPuppet(){
        std::cout << i++ << std::endl;
    };
    void FadeToBlack(){
        std::cout << "ok" << std::endl;
    };
};

int main(){
    XContext Metallica_context;
    XPointer *XPointerToOneMetallicaObject;
    XEvent e;
    int DoNotStop=1;

    display = XOpenDisplay(0);

    Metallica OneMetallicaObject(2,&Metallica_context);
    Metallica *SandMan;

    while(DoNotStop){
        XNextEvent(display, &e);
        switch(e.type){
            case Expose : XFlush(display); break;
            case KeyRelease : XFindContext(display,e.xany.window,Metallica_context,XPointerToOneMetallicaObject);
                SandMan = (Metallica*)(*XPointerToOneMetallicaObject);
                SandMan->MasterOfPuppet();
                if (SandMan->i > 4) DoNotStop=0;
                break;
            //case KeyRelease    : DoNotStop=0; break;
        }
    }

    return 0;
}