//
//program: asteroids.cpp
//author:  Gordon Griesel
//date:    2014 - 2025
//mod spring 2015: added constructors
//This program is a game starting point for a 3350 project.
//
//
//#include <cstdlib>
//#include <unistd.h>
//#include <ctime>

#include <iostream> // Adds a lot of preprocessor time
#include <cstring>
#include <cmath>    // Adds a lot of preprocessor time
#include <chrono>
//#include <X11/Xutil.h>
//#include <GL/gl.h>
//#include <GL/glu.h>

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#ifdef USE_OPENAL_SOUND
#include <AL/alut.h>
#endif //USE_OPENAL_SOUND

//#include "headers.h"
#include "dcarter.h"
#include "shared.h"
#include "log.h"
#include "lvaldivia.h"
#include "aolmedo.h"
#include "fandrade.h"
#include "falrowhani.h"

//defined types
typedef float Flt;
typedef float Vec[3];
typedef Flt   Matrix[4][4];

//macros
#define rnd() (((Flt)rand())/(Flt)RAND_MAX)
#define random(a) (rand()%a)
#define VecZero(v) (v)[0]=0.0,(v)[1]=0.0,(v)[2]=0.0
#define MakeVector(x, y, z, v) (v)[0]=(x),(v)[1]=(y),(v)[2]=(z)
#define VecCopy(a,b) (b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2]
#define VecDot(a,b)  ((a)[0]*(b)[0]+(a)[1]*(b)[1]+(a)[2]*(b)[2])
#define VecSub(a,b,c) (c)[0]=(a)[0]-(b)[0]; \
                             (c)[1]=(a)[1]-(b)[1]; \
(c)[2]=(a)[2]-(b)[2]
//constants
const float timeslice = 1.0f;
const float gravity = -0.2f;
#define PI 3.141592653589793
#define ALPHA 1
const int MAX_BULLETS = 11;
const Flt MINIMUM_ASTEROID_SIZE = 60.0;

//-----------------------------------------------------------------------------
//Setup timers
const double physicsRate = 1.0 / 60.0;
const double oobillion = 1.0 / 1e9;
extern struct timespec timeStart, timeCurrent;
extern struct timespec timePause;
extern double physicsCountdown;
extern double timeSpan;
extern double timeDiff(struct timespec *start, struct timespec *end);
extern void timeCopy(struct timespec *dest, struct timespec *source);

//-----------------------------------------------------------------------------

const int carCount = 5;
void drawPauseMenu();
void physicsforCollision();
void title(Rect &r);
//void textMoveRight();
Game_Button pauseButton;
/*enum GameState {
  PLAYING,
  PAUSED,
  MENU
  };
  */
//extern GameState gameState; 

// Global variable to track current game state
//GameState gameState = PLAYING;

//extern GameState gameState;
GameState gameState = PLAYING;

//*/
//Box box(100, 50);
Global::Global() 
{
    timerList = new TimerList();
    xres = 960;
    yres = 720;
    //xres = 640;
    //yres = 480;
    //    Box box(100, 50);
    //screen = Playing;
    screen = Title;
    volume = 100;
    memset(keys, 0, 65536);
    credits = true;
    show_bike = true;

    gameTime = 150.0f;
    remainingTime = gameTime;
    mainTime = new TimerBar(125, 680, 100, 0, "./images/gameTime.png", black2, 1, 24);
    mainTime->maxTime = gameTime;
    mainTime->deliverytime = remainingTime;

    // mouse value 1 = true = mouse is a regular mouse.
    mouse_cursor_on = 1;
    moto_side = new Entity("images/moto_side.gif");
    scale = resolution_scale(&background);
    gameState = PLAYING;

    // Initialize the current background to the menu background
    current_background = MENU_BG;
    //gl.current_background = MENU_BG;
}
Global::~Global()
{
    delete timerList;
    // Clean up the background images
    for (int i = 0; i < NUM_BACKGROUNDS; i++) {
        if (backgrounds[i] != nullptr) {
            delete backgrounds[i];
            backgrounds[i] = nullptr;
        }
    }
    delete mainTime;
}

Global gl;
X11_wrapper x11(960, 720);
// 0, 0 for fullscreen
TimerList timerList;

//function prototypes
void init_opengl(void);
void check_mouse(XEvent *e);
int check_keys(XEvent *e);
void physics();
void render();
//==========================================================================
// M A I N
//==========================================================================
int main()
{
    printf("Entered main");
    logOpen();
    // std::cout << "about to create timerbar" << std::endl;
    //std::cout << "timer bar created" << std::endl;
    init_opengl();
    // physicsforCollision();
#ifdef USE_OPENAL_SOUND
    init_openal();

    // Create buffer to hold sound information
    system("ffmpeg -i ./audio/music/intro_theme.mp3 ./audio/music/intro_theme.wav");
    ALuint alBuffer = alutCreateBufferFromFile("./audio/music/intro_theme.wav");

    // Create sound source and store buffer in it
    ALuint alSource;
    alGenSources(1, &alSource);
    alSourcei(alSource, AL_BUFFER, alBuffer);

    // Set volume and pitch to normal
    alSourcef(alSource, AL_GAIN, 1.0f);
    alSourcef(alSource, AL_PITCH, 1.0f);
    alSourcei(alSource, AL_LOOPING, AL_TRUE);
    if (alGetError() != AL_NO_ERROR) {
        printf("ERROR: setting source\n");
    }

    alSourcePlay(alSource);
#endif //USE_OPENAL_SOUND
    srand(time(NULL));
    clock_gettime(CLOCK_REALTIME, &timePause);
    clock_gettime(CLOCK_REALTIME, &timeStart);
    //auto lasttime = std::chrono::steady_clock::now();
    x11.set_mouse_position(200, 200);
    x11.show_mouse_cursor(gl.mouse_cursor_on);
    initCars();




    // Debugging money system
    /*
       std::cout << gl.money.getTotalMoney() << std::endl;
       std::cout << gl.money.getRevenue() << std::endl;
       gl.money.increaseRevenue(10.00);
       std::cout << gl.money.getRevenue() << std::endl;
       gl.money.cashInRevenue();
       std::cout << gl.money.getTotalMoney() << std::endl;
       */
    // End of debugging
    int done=0;
    while (!done) {
        while (x11.getXPending()) {
            XEvent e = x11.getXNextEvent();
            x11.check_resize(&e);
            check_mouse(&e);
            done = check_keys(&e);
        }
        clock_gettime(CLOCK_REALTIME, &timeCurrent);
        timeSpan = timeDiff(&timeStart, &timeCurrent);
        timeCopy(&timeStart, &timeCurrent);
        // if gl.screen state is paused, don't do physics
        physicsCountdown += timeSpan;
        switch (gl.screen) {
            case Title:
                while (physicsCountdown >= physicsRate) {
                    //coommenting this out 
                    aolmedo_title_physics();
                    //  title_physics();
                    physicsCountdown -= physicsRate;
                }
                render_title_screen();
                break;

            case Home:
                render_menu_screen();
                break;

            case Instructions:
                render_instructions_screen();
                break;

            case Settings:
                render_settings_screen();
                break;

            case Pause:
            case Credits:
            case Playing:
                while (physicsCountdown >= physicsRate) {
                    //physics();
                    manageDeliveries(physicsRate); 
                    manageGame(physicsRate); //for the main timer
                    physics();
                    physicsCountdown -= physicsRate;
                }
                if(gl.gameOver == true) {
                    gl.screen = GameOver;
                }
                else {
                    render();
                }
                break;
            case GameOver:
                drawGameOver();
                break;
        }
        x11.swapBuffers();
#ifdef SLEEP_TEST
        // usleep documentation garuntees usleep to sleep for 
        // AT LEAST as long as called. It may sleep longer.
        // For reference: time system command, user time vs system vs total time.
        // Experimentally, this doesn't seem to actually help anything...
        const int Second = 1000000; // usleep is in microseconds
        const int FPS = 30;
        usleep(Second / FPS);
#endif //SLEEP_TEST
    }
    cleanup_fonts();
#ifdef USE_OPENAL_SOUND
    cleanup_openal(&alSource, &alBuffer);
    system("rm ./wav/intro_theme.wav");
#endif //USE_OPENAL_SOUND
    logClose();
    return 0;
}

void init_opengl(void)
{
    //OpenGL initialization
    glViewport(0, 0, gl.xres, gl.yres);
    //Initialize matrices
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    glMatrixMode(GL_MODELVIEW); glLoadIdentity();
    //This sets 2D mode (no perspective)
    glOrtho(0, gl.xres, 0, gl.yres, -1, 1);
    //
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_FOG);
    glDisable(GL_CULL_FACE);
    //
    //Clear the screen to black
    //glClearColor(0.0, 0.0, 0.0, 1.0);
    //Do this to allow fonts
    glEnable(GL_TEXTURE_2D);
    initialize_fonts();
    gl.bike.init_gl();
    gl.background.init_gl();
    //called intro image here 
    gl.show.init_gl();
    gl.moto_side->init_gl();
    cars[0].init_gl();
    //timerList.initAll();
    cars[1].init_gl();
    //gl.attempts.init_gl();
    for (int i = 0; i < 3; i++) {
        gl.attempts[i].init_gl();
    }
    initGame();
    initDeliveryLocations();

    // Initialize the background array
    init_backgrounds();
    gl.mainTime->init_gl();
    // gl.box.pos[0] = 100.0f;
    //gl.box.pos[1] = 100.0f;
    //add timerbar
    //gl.timerbar.init_gl();
    //gl.timerList.initALL();
}

void normalize2d(Vec v)
{
    Flt len = v[0]*v[0] + v[1]*v[1];
    if (len == 0.0f) {
        v[0] = 1.0;
        v[1] = 0.0;
        return;
    }
    len = 1.0f / sqrt(len);
    v[0] *= len;
    v[1] *= len;
}

void check_mouse(XEvent *e)
{
    //Did the mouse move?
    //Was a mouse button clicked?
    static int savex = 0;
    static int savey = 0;
    //
    static int ct=0;
    const int true_y = gl.yres - e->xbutton.y;

    if (e->type == ButtonRelease) {
        return;
    }
    if (e->type == ButtonPress) {
        if (e->xbutton.button==1) { // Left button
                                    // Handle different screens with appropriate click handlers
            printf("Button press - current screen: %d\n", gl.screen);

            switch (gl.screen) {
                case Title:
                    printf("Processing Title screen click\n");
                    gl.title_button.click(e->xbutton.x, true_y);
                    gl.start_button.click(e->xbutton.x, true_y);
                    break;
                case Home:
                    printf("Processing Home/Menu screen click\n");
                    handle_menu_click(e->xbutton.x, true_y, true);
                    break;
                case Instructions:
                    printf("Processing Instructions screen click\n");
                    handle_instructions_click(e->xbutton.x, true_y, true);
                    break;
                case Settings:
                    printf("Processing Settings screen click\n");
                    handle_settings_click(e->xbutton.x, true_y, true);
                    break;
                default:
                    printf("Unhandled screen in click handler: %d\n", gl.screen);
                    break;
            }
            printf("After processing - x: %d, y: %d\n", e->xbutton.x, true_y);
        }
        if (e->xbutton.button==3) {
            //Right button is down
        }
        if (gameState == PAUSED) {
            gl.pause_button.click(e->xbutton.x, true_y);
        }

        if (gameState == PAUSED) {
            gl.restart.click(e->xbutton.x, true_y);
        }
    }
    //keys[XK_Up] = 0;
    if (savex != e->xbutton.x || savey != e->xbutton.y) {
        // the mouse moved
        int xdiff = savex - e->xbutton.x;
        int ydiff = savey - e->xbutton.y;
        savex = e->xbutton.x;
        savey = e->xbutton.y;
        //std::cout << savex << ", " << savey << std::endl;
        if (++ct < 10)
            return;
        //std::cout << "savex: " << savex << std::endl << std::flush;
        //std::cout << "e->xbutton.x: " << e->xbutton.x << std::endl <<
        //std::flush;
        //std::cout << "savey: " << savey << std::endl << std::flush;
        //std::cout << "e->xbutton.y: " << e->xbutton.y << std::endl <<
        //std::flush;
        //
        // Handle hover effects based on current screen
        switch (gl.screen) {
            //title(r);
            case Title:
                // Check if mouse is inside the start button (for hover effect)
                if (gl.start_button.is_inside(e->xbutton.x, true_y)) {
                    gl.start_button.darken = true;
                }
                else {
                    gl.start_button.darken = false;
                }

                // Check if mouse is inside the title button (for hover effect)
                if (gl.title_button.is_inside(e->xbutton.x, true_y)) {
                    gl.title_button.darken = true;
                }
                else {
                    gl.title_button.darken = false;
                }
                break;

            case Home:
                // Call the hover handler for menu items
                handle_menu_hover(e->xbutton.x, true_y);
                break;

            default:
                break;
        }
        // If mouse cursor is on, it does not control the ship.
        // It's a regular mouse.
        if (gl.mouse_cursor_on)
            return;
        //printf("mouse move "); fflush(stdout);
        if (xdiff > 0) {
        }
        else if (xdiff < 0) {
        }
        if (ydiff > 0) {
        }
        x11.set_mouse_position(200,200);
        savex = 200;
        savey = 200;
    }
}

int check_keys(XEvent *e)
{
    static int shift=false; // shift variable is used to distinguish capitals
                            // i.e. a vs A uses shift && a.
                            // Currently not being used in this code base.

    if (e->type != KeyRelease && e->type != KeyPress) {
        //not a keyboard event
        return 0;
    }
    int key = (XLookupKeysym(&e->xkey, 0) & 0x0000ffff);
    //Log("key: %i\n", key);
    if (e->type == KeyRelease) {
        switch (key) {
            case XK_Escape:
                break;
            case XK_a:
                gl.bike.turn_sharpness = 2.5;
                break;
            case XK_s:
                gl.bike.scale = 25;
                break;
            case XK_Shift_L:
            case XK_Shift_R:
                shift = false;
                break;
            case XK_Left:
                gl.bike.left = false;
                break;
            case XK_Right:
                gl.bike.right = false;
                break;
            case XK_Up:
                gl.bike.pedal = Neutral;
                break;
            case XK_Down:
                gl.bike.pedal = Neutral;
                break;
        }
        return 0;
    }
    (void)shift; // I don't understand what this line does.
                 //
                 // if any button is pushed, exit the title menu. 
                 // Currently would break pause and credits
    if (e->type == KeyPress) {
        //gl.screen = Playing;
        printf("Key press - current screen: %d\n", gl.screen);
        switch (key) {
            case XK_F4:
                return 1;
            case XK_a:
                gl.bike.turn_sharpness = 5.0;
                break;
            case XK_s:
                gl.bike.scale = 10;
                break;
            case XK_Shift_L:
            case XK_Shift_R:
                shift = true;
                break;
            case XK_Escape:
                /*if (gameState == PLAYING) {
                  gameState = PAUSED;
                  } else if (gameState == PAUSED) {
                  gameState = PLAYING;
                  }
                  */
                if (gl.screen == Title || gl.screen == Home || 
                        gl.screen == Instructions || gl.screen == Settings) {
                    // In menus, ESC goes back to main menu
                    printf("ESC pressed in menu - returning to home\n");
                    gl.screen = Home;
                } 
                else if (gameState == PLAYING) {
                    gameState = PAUSED;
                } 
                else if (gameState == PAUSED) {
                    gameState = PLAYING;
                }
                break;
            case XK_m:
                gl.mouse_cursor_on = !gl.mouse_cursor_on;
                x11.show_mouse_cursor(gl.mouse_cursor_on);
                break;
            case XK_c:
                gl.credits = !gl.credits;
                break;
            case XK_b:
                gl.show_bike = !gl.show_bike;
                break;
            case XK_Left:
                gl.bike.left = true;
                break;
            case XK_Right:
                gl.bike.right = true;
                break;
            case XK_Down:
                gl.bike.pedal = Backward;
                break;
            case XK_Up:
                gl.bike.pedal = Forward;
            case XK_equal:
                break;
            case XK_minus:
                break;
            case XK_x:
                if (gl.screen == GameOver) { 
                    return 1;
                }

        }
    }


    return 0;
    /*
    //
    // if any button is pushed, exit the title menu. 
    // Currently would break pause and credits
    if (e->type == KeyPress) {
    if (gl.screen != GameOver) {
    gl.screen = Playing;
    }
    switch (key) {
    case XK_F4:
    return 1;
    case XK_a:
    gl.bike.turn_sharpness = 5.0;
    break;
    case XK_s:
    gl.bike.scale = 10;
    break;
    case XK_Shift_L:
    case XK_Shift_R:
    shift = true;
    break;
    case XK_Escape:
    if (gameState == PLAYING) {
    gameState = PAUSED;
    } else if (gameState == PAUSED) {
    gameState = PLAYING;
    }
    break;
    case XK_m:
    gl.mouse_cursor_on = !gl.mouse_cursor_on;
    x11.show_mouse_cursor(gl.mouse_cursor_on);
    break;
    case XK_c:
    gl.credits = !gl.credits;
    break;
    case XK_b:
    gl.show_bike = !gl.show_bike;
    break;
    case XK_Left:
    gl.bike.left = true;
    break;
    case XK_Right:
    gl.bike.right = true;
    break;
    case XK_Down:
    gl.bike.pedal = Backward;
    break;
    case XK_Up:
    gl.bike.pedal = Forward;
    case XK_equal:
    break;
    case XK_minus:
    break;
    case XK_x:
    if (gl.screen == GameOver) { 
    return 1;
    }
    break;
    }
    }
    return 0;
    */
}


void physics()
{
    cars[0].update_frame();
    cars[1].update_frame();
    cars[0].physics();
    cars[1].physics();
    physicsforCollision();
    deliveryDetection();
    gl.bike.move();
    gl.mainTime->update();
}

/*void title_render()
  {
  glClear(GL_COLOR_BUFFER_BIT);

// This line below caused both images to appear at once during the title screen
//gl.background.show(gl.scale, gl.xres/2, gl.yres/2, 0.0f);

//added this to show intro image 
//    gl.show.show(gl.scale, gl.xres/2 , gl.yres/2 +2, 0.0f);


// Use the proper background from the array
backgrounds[MENU_BG]->show(gl.scale, gl.xres/2, gl.yres/2, 0.0f);

// Show the motorcycle side image
gl.moto_side->render();
//printf("%f, %f\n", gl.moto_side->pos.x, gl.moto_side->pos.y);
// Setup text rectangle
Rect r;  // Rect object for text positioning
r.bot = gl.yres - 20;  // Set the bottom of the text near the bottom of the screen
r.left = 10; 
//title(r);
//gl.title_button.render();
//title(r);
//physicsforCollision();

// Display game title text
ggprint8b(&r, 16, 0xffec407a, "Pizza Delivery Simulator");

// Render start game button
gl.start_button.render();
}
*/
void render()
{
    Rect r;
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    //gl.background.show(gl.scale, gl.xres/2, gl.yres/2, 0.0f);
    //physicsforCollision();

    // This line below rendered the intro image during the playing state
    //gl.show.show(gl.scale, gl.xres/2, gl.yres/2 +2, 0.0f);

    // Use the game background from the background array when playing
    backgrounds[GAME_BG]->show(gl.scale, gl.xres/2, gl.yres/2, 0.0f);




    r.bot = gl.yres - 20;

    /* Debugging..*/
    //timerbar.timeRender();
    gl.box.render();
    gl.box2.render();
    gl.box3.render();
    gl.box4.render();
    gl.box5.render();
    gl.box6.render();
    gl.box7.render();
    gl.box8.render();
    gl.box9.render();
    gl.box10.render();
    gl.box11.render();
    gl.box12.render();
    gl.box13.render();
    gl.box14.render();
    gl.box15.render();
    gl.box16.render();
    myRender(); 
    r.left = 10;
    r.center = 0;
    //ggprint8b(&r, 16, 0x00ff0000, "3350 - Asteroids");


    show_fps(&r);
    gl.timerList->renderAll();
    gl.mainTime->timeRender();
    //     if (gl.box.checkCollision(gl.bike)) {
    // Stop the motorcycle or reverse its direction
    //      gl.bike.velocity = 0; // Or apply any other collision response
    //  }

    //   box.render();   
    if (gameState == PAUSED) {
        // Draw pause menu
        drawPauseMenu();
    } else {
        /* ggprint8b(&r, 16, 0x00ff00ff, "Press C for credits");
           if (gl.credits) {
           show_avelina(&r);
           show_david(&r);
           show_fenoon(&r);
           show_francisco(&r);
           show_lesslie(&r);

           } */
        if (gl.show_bike)
            gl.bike.render();
        printScoreNTime();
        //  physicsforCollision();
        // Commented this so title button would disappear during playing state
        //gl.title_button.render();
        cars[0].render();
        cars[1].render();
        //printf("%f\n", cars[0].pos.x);
        attemptsRender(&r);
        //  gl.box.render();
        //added this here
        //  if (gameState == PAUSED) {
        //     drawPauseMenu();
        // }
        // }
        //   if (gameState == PAUSED) {
        //     drawPauseMenu();
        //}
}
}

