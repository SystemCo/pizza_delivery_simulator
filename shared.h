#ifndef _SHARED_H_
#define _SHARED_H_

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>

class Image { // from the rainforest framework
public:
    int width, height;
    unsigned char *data;
    ~Image() { delete [] data; }
    Image(const char *fname);
    
};

class Global {
public:
	int xres, yres;
	char keys[65536];
	int mouse_cursor_on;
        int credits;
        int show_bike;
        Image* bike_img;
        GLuint bikeTexture;
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
