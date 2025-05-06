#ifndef _SHARED_H_
#define _SHARED_H_

//#include <X11/Xlib.h>
//#include <X11/keysym.h>
//#include <GL/glx.h>
#include "dcarter.h"
#include "aolmedo.h"
#include "falrowhani.h"
#include "lvaldivia.h"
#include "fandrade.h"
class TimerBar;
class TimerList;
enum ScreenState { Title, Home, Instructions, Settings, Pause, Credits, Playing, GameOver };

class Global { // Originally from Asteroids framework  
        unsigned char white[3] {255, 255, 255};
    unsigned char blue[3] {0, 0, 255};
    unsigned char black[3] {0, 0, 0};
    unsigned char red[3] {255, 0, 0};
    public:
    int volume;
    int current_background;
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
    Box box11; 
    Box box12; 
    Box box13; 
    Box box14; 
    Box box15; 
    Box box16;
    Box box17; 

    //float deliveryLocations[10][2]; //index can be changed depending of delievery locations
    int numActiveDelieries;
    //bool activeDeliveries[3];
    
    TimerList* timerList;   
    bool gameOver = false;
    int gameAttempts = 3; 
    static const int maxActiveDeliveries = 3; //no more than three active
    static const int maxDeliveryLocations = 6;
    int timerLocation[maxDeliveryLocations]; //to know what timer corresponds to which location
    int activeDeliveries = 0; // to keep count
    bool activeDeliveryLocations[maxDeliveryLocations];
    float deliveryLocations[maxDeliveryLocations][2];
    float deliveryDeltaTime = 0.0f;
    float nextDelivery = 0.0f; 

    float gameTime;
    float remainingTime;
    TimerBar* mainTime;
    
    int mouse_cursor_on;
    int credits;
    int show_bike;
    Motorcycle bike;
    Entity* moto_side;
    Title_Exit_Button title_button;
    StartGame_Button  start_button;
    Game_Button pause_button;
    Restart_Button restart;  
    //Image background {"./images/Background2.png"};
    Image background {"./images/map1.png"};
    Image show {"./images/game2.jpg"};
    //   Image show {"./images/Web_Photo_Editor.jpg"};
    // Image show {"./images/Web_Photo_Editor.jpg"};
    //Image show {"./images/game2.jpg"};
    /*
       Line_Follower car1 {
       200, 200, 40.0, 0.0, 
       "images/Car1_sprite.png", red, 1, 8
       };
       */
    Entity attempts[3] = {
        {930, 690,25.0f, 0.0f, "./images/pizza.png", black, 1, 1},
        {880, 690, 25.0f, 0.0f, "./images/pizza.png", black, 1, 1},
        {830, 690, 25.0f, 0.0f, "./images/pizza.png", black, 1, 1}
    };

    Sprite explosion = {"./images/exp44.png", black, 4, 4};
    Position expl_pos = {-10, -10};

     //Entity attempts { 
    //  580, 440,10.0f , 0.0f, "./images/pizza.png", black, 1, 1
    // };

    ScreenState screen;
    //TODO: 
    // implement switch statements in main func as well as other funcs
    // using screen state enum
    MoneySystem money;
    Global();
    ~Global();
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
