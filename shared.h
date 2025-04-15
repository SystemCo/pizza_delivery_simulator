#ifndef _SHARED_H_
#define _SHARED_H_

//#include <X11/Xlib.h>
//#include <X11/keysym.h>
//#include <GL/glx.h>
#include "dcarter.h"
#include "aolmedo.h"
#include "falrowhani.h"
#include "lvaldivia.h"
enum ScreenState { Title, Home, Pause, Credits, Playing };

class Global { // Originally from Asteroids framework  
    unsigned char white[3] {255, 255, 255};
    unsigned char blue[3] {0, 0, 255};
    unsigned char black[3] {0, 0, 0};
    unsigned char red[3] {255, 0, 0};
    public:
    int xres, yres, scale;
    unsigned char black2[3] {0, 0, 0};
    char keys[65536];
    Box box;
    Box box2; 
    Box box3; 
    Box box4; 
    Box box5; 
    Box box6; 
    Box box7; 
    Box box8;
    Box box9;
    Box box10;  
    int mouse_cursor_on;
    int credits;
    int show_bike;
    Motorcycle bike;
    Entity* moto_side;
    Title_Exit_Button title_button;
    Game_Button pause_button;
    Restart_Button restart;  
    //Image background {"./images/Background2.png"};
    Image background {"./images/map1.png"};
    Image show {"./images/game2.jpg"};
    //   Image show {"./images/Web_Photo_Editor.jpg"};
    // Image show {"./images/Web_Photo_Editor.jpg"};
    //Image show {"./images/game2.jpg"};
    //TimerBar timerbar = {320,240, 100.0f, 0.0f, "./images/TimeBar.png",black, 1, 12};
    Line_Follower car1 {
        200, 200, 40.0, 0.0, 
            "images/Car1_sprite.png", red, 1, 8
    };
    Entity attempts[3] = {
    {1360, 850,20.0f, 0.0f, "./images/pizza.png", black, 1, 1},
    {1320, 850, 20.0f, 0.0f, "./images/pizza.png", black, 1, 1},
    {1280, 850, 20.0f, 0.0f, "./images/pizza.png", black, 1, 1}
};
    //Entity attempts { 
      //  580, 440,10.0f , 0.0f, "./images/pizza.png", black, 1, 1
   // };
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
