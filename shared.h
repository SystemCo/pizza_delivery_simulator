#ifndef _SHARED_H_
#define _SHARED_H_

//#include <X11/Xlib.h>
//#include <X11/keysym.h>
//#include <GL/glx.h>
#include "dcarter.h"
#include "aolmedo.h"
#include "lvaldivia.h"
enum ScreenState { Title, Home, Pause, Credits, Playing };
/*
 * class TimerBar : public Entity
{
    public:
        int frame = 0;
        //TimerBar(const char* fname, int rows, int cols);
        TimerBar(float x, float y, float scale, float angle,const char* fname, unsigned char alphaColor[3    ], int rows, int cols);
        //TimerBar(float pos_x, float pos_y, float scale, float angle,const char* fname, int rows, int co    ls);
        void update(float deliveryTime, float maxTime);
        void timeRender();
        //void timeRender(Position pos, float scale)
        //int strikes = 3;
        //float money;
        float deliverytime = 15.0f;
        bool timesup = false;
        bool deliverMade = false;
        void Timer(float t);
        void resetTimer();
        void renderTimer() {
          timerbar.timeRender();
          }i
          
        //void renderTimer(Position pos, float scale) {
        //void timerbar.timeRender(pos, scale);



};
*/
class Global { // Originally from Asteroids framework  
    unsigned char white[3] {255, 255, 255};
    unsigned char blue[3] {0, 0, 255};
    unsigned char black[3] {0, 0, 0};
    unsigned char red[3] {255, 0, 0};
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
    //TimerBar timerbar {"./images/TimeBar.png", 1, 12};
    TimerBar timerbar = {320,240, 100.0f, 0.0f, "./images/TimeBar.png",black, 1, 12}; 
    Line_Follower car1 {
        200, 200, 40.0, 0.0, 
            "images/Car1_sprite.png", red, 1, 8
    };
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
