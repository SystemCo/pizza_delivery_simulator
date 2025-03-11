#ifndef _SHARED_H_
#define _SHARED_H_

//#include <X11/Xlib.h>
//#include <X11/keysym.h>
//#include <GL/glx.h>
#include "dcarter.h"
#include "aolmedo.h"

enum ScreenState { Title, Home, Pause, Credits, Playing };
class Global { // Originally from Asteroids framework  
public:
	int xres, yres, scale;
	char keys[65536];
	int mouse_cursor_on;
        int credits;
        int show_bike;
        Motorcycle bike;
        Entity* moto_side;
        Title_Exit_Button title_button;
        //Image background {"./images/Background2.png"};
        Image background {"./images/map1.png"};
        Image show {"./images/game2.jpg"};
        ScreenState screen;
        //TODO: 
        // implement switch statements in main func as well as other funcs
        // using screen state enum
	Global();
};

class X11_wrapper { // from Asteroids framework
private:
	Display *dpy;
	Window win;
	GLXContext glc;
public:
	X11_wrapper() { }
	X11_wrapper(int w, int h);
        ~X11_wrapper();
        void set_title();
        void check_resize(XEvent *e);
        void reshape_window(int width, int height);
        void setup_screen_res(const int w, const int h);
        void swapBuffers();
        bool getXPending();
        XEvent getXNextEvent();
        void set_mouse_position(int x, int y);
        void show_mouse_cursor(const int onoff);
};

#endif //_SHARED_H_
