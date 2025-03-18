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

void drawPauseMenu();

enum GameState {
    PLAYING,
    PAUSED,
    MENU
};

// Global variable to track current game state
//GameState gameState = PLAYING;

//extern GameState gameState;
GameState gameState = PLAYING;

Global::Global() 
{
    xres = 640;
    yres = 480;
    //screen = Playing;
    screen = Title;
    memset(keys, 0, 65536);
    credits = true;
    show_bike = true;

    // mouse value 1 = true = mouse is a regular mouse.
    mouse_cursor_on = 1;
    moto_side = new Entity("images/moto_side.gif");
    scale = resolution_scale(&background);
    gameState = PLAYING;
    car1.set_points(new Position[6] {
            {200, 200}, 
            {300, 300},
            {400, 200},
            {500, 300},
            {100, 100},
            {100, 500},
    }, 6);
}

Global gl;

class Ship {
    public:
        Vec pos;
        Vec dir;
        Vec vel;
        Vec acc;
        float angle;
        float color[3];
    public:
        Ship() {
            pos[0] = (Flt)(gl.xres/2);
            pos[1] = (Flt)(gl.yres/2);
            pos[2] = 0.0f;
            VecZero(dir);
            VecZero(vel);
            VecZero(acc);
            angle = 0.0;
            color[0] = color[1] = color[2] = 1.0;
        }
};

class Bullet {
    public:
        Vec pos;
        Vec vel;
        float color[3];
        struct timespec time;
    public:
        Bullet() { }
};

class Asteroid {
    public:
        Vec pos;
        Vec vel;
        int nverts;
        Flt radius;
        Vec vert[8];
        float angle;
        float rotate;
        float color[3];
        struct Asteroid *prev;
        struct Asteroid *next;
    public:
        Asteroid() {
            prev = NULL;
            next = NULL;
        }
};

class Game {
    public:
        Ship ship;
        Asteroid *ahead;
        Bullet *barr;
        int nasteroids;
        int nbullets;
        struct timespec bulletTimer;
        struct timespec mouseThrustTimer;
        bool mouseThrustOn;
    public:
        void Build_Asteroid()
        {

            Asteroid *a = new Asteroid;
            a->nverts = 8;
            a->radius = rnd()*80.0 + 40.0;
            Flt r2 = a->radius / 2.0;
            Flt angle = 0.0f;
            Flt inc = (PI * 2.0) / (Flt)a->nverts;
            for (int i=0; i<a->nverts; i++) {
                a->vert[i][0] = sin(angle) * (r2 + rnd() * a->radius);
                a->vert[i][1] = cos(angle) * (r2 + rnd() * a->radius);
                angle += inc;
            }
            a->pos[0] = (Flt)(rand() % gl.xres);
            a->pos[1] = (Flt)(rand() % gl.yres);
            a->pos[2] = 0.0f;
            a->angle = 0.0;
            a->rotate = rnd() * 4.0 - 2.0;
            a->color[0] = 0.8;
            a->color[1] = 0.8;
            a->color[2] = 0.7;
            a->vel[0] = (Flt)(rnd()*2.0-1.0);
            a->vel[1] = (Flt)(rnd()*2.0-1.0);
            //std::cout << "asteroid" << std::endl;
            //add to front of linked list
            a->next = ahead;
            if (ahead != NULL)
                ahead->prev = a;
            ahead = a;
            ++nasteroids;
        }
        Game() {
            ahead = NULL;
            barr = new Bullet[MAX_BULLETS];
            nasteroids = 0;
            nbullets = 0;
            mouseThrustOn = false;
            //build 10 asteroids...
            for (int j=0; j<10; j++) {
                Build_Asteroid();
            }
            clock_gettime(CLOCK_REALTIME, &bulletTimer);
        }
        ~Game() {
            delete [] barr;
        }
} g;

X11_wrapper x11(gl.xres, gl.yres);
// ---> for fullscreen x11(0, 0);

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
    logOpen();
    init_opengl();
#ifdef USE_OPENAL_SOUND
    init_openal();
    
    // Create buffer to hold sound information
    ALuint alBuffer = alutCreateBufferFromFile("./wav/737engine.wav");
    
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
    int done=0;
    //Game_System pstats;
    while (!done) {
        while (x11.getXPending()) {
            XEvent e = x11.getXNextEvent();
            x11.check_resize(&e);
            check_mouse(&e);
            done = check_keys(&e);
        }
      /*  auto currenttime = std::chrono::steady_clock::now();
        std::chrono::duration<float> elaspedtime = currenttime - lasttime;
        float deltaTime = elaspedtime.count();
        lasttime = currenttime;

        pstats.Timer(deltaTime);
        */
        clock_gettime(CLOCK_REALTIME, &timeCurrent);
        timeSpan = timeDiff(&timeStart, &timeCurrent);
        timeCopy(&timeStart, &timeCurrent);
        // if gl.screen state is paused, don't do physics
        physicsCountdown += timeSpan;
        switch (gl.screen) {
        case Title:
            while (physicsCountdown >= physicsRate) {
               //coommenting this out 
        //       title_physics();
                physicsCountdown -= physicsRate;
            }
            title_render();
            break;
        case Home:
        case Pause:
        case Credits:
        case Playing:
            while (physicsCountdown >= physicsRate) {
                physics();
                physicsCountdown -= physicsRate;
            }
            render();
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
    //cleanup_openal();
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
    gl.car1.init_gl();
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
            gl.title_button.click(e->xbutton.x, true_y);
        }
        if (e->xbutton.button==3) {
            //Right button is down
        }
    }
    //keys[XK_Up] = 0;
    if (savex != e->xbutton.x || savey != e->xbutton.y) {
        // the mouse moved
        int xdiff = savex - e->xbutton.x;
        int ydiff = savey - e->xbutton.y;
        savex = e->xbutton.x;
        savey = e->xbutton.y;
        if (++ct < 10)
            return;
        //std::cout << "savex: " << savex << std::endl << std::flush;
        //std::cout << "e->xbutton.x: " << e->xbutton.x << std::endl <<
        //std::flush;
        //
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
            //if escape 
            case XK_Escape:
                if (gameState == PLAYING) {
                    gameState = PAUSED;  // Pause the game
                } else if (gameState == PAUSED) {
                    gameState = PLAYING;  // Resume the game
                }
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
    /*
    extern GameState gameState;
    //added this 
    //
       if (e->type == KeyPress) {
        switch (key) {
            case XK_Escape:
                // Toggle between PLAYING and PAUSED
                if (gameState == PLAYING) {
                    gameState = PAUSED;
                } else {
                    gameState = PLAYING;
                }
                return 1;
        }
    }
*/
 //   return 0;
//}
    //if (e->type == KeyPress) {
    // we return if not keypress or keyrelease and return if it is keyrelease
    // so this if guard is not strictly needed.
    //
    (void)shift; // I don't understand what this line does.
                 //
                 // if any button is pushed, exit the title menu. 
                 // Currently would break pause and credits
    gl.screen = Playing;
    switch (key) {
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
       // case XK_Escape:
                        // TODO: Pause
            // set gl.screen to pause state
          if (gameState == PLAYING) {
                gameState = PAUSED;
         } else if (gameState == PAUSED) {
                gameState = PLAYING;
          }
           return 1;
     //modified code 
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
    }
    return 0;
}


void physics()
{
    gl.car1.update_frame();
    gl.car1.physics();
    gl.bike.move();
}

void title_render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    gl.background.show(gl.scale, gl.xres/2, gl.yres/2, 0.0f);
//added this to show intro image 
    gl.show.show(gl.scale, gl.xres/2 , gl.yres/2 +2, 0.0f);
    gl.moto_side->render();
    //printf("%f, %f\n", gl.moto_side->pos.x, gl.moto_side->pos.y);
    gl.title_button.render();
}

void render()
{
    Rect r;
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    gl.background.show(gl.scale, gl.xres/2, gl.yres/2, 0.0f);
    gl.show.show(gl.scale, gl.xres/2, gl.yres/2 +2, 0.0f);
    r.bot = gl.yres - 20;
    r.left = 10;
    r.center = 0;
    ggprint8b(&r, 16, 0x00ff0000, "3350 - Asteroids");
       if (gameState == PAUSED) {
        // Draw pause menu
        drawPauseMenu();
    } else {

    ggprint8b(&r, 16, 0x00ffff00, "n bullets: %i", g.nbullets);
    ggprint8b(&r, 16, 0x00ffff00, "n asteroids: %i", g.nasteroids);
    ggprint8b(&r, 16, 0x00ff00ff, "Press C for credits");
    if (gl.credits) {
        show_avelina(&r);
        show_david(&r);
        show_fenoon(&r);
        show_francisco(&r);
        show_lesslie(&r);
    }
    if (gl.show_bike)
        gl.bike.render();
    gl.title_button.render();
    gl.car1.render();
    //added this here
     if (gameState == PAUSED) {
        drawPauseMenu();
    }
}
}

///adding a draw puase menu 
void drawPauseMenu() {
    Rect r;
    
    glColor4f(0.0, 0.0, 0.0, 1.0);// transparency
    glBegin(GL_QUADS);
        glVertex2f(-1, -1);
        glVertex2f(1, -1);
        glVertex2f(1, 1);
        glVertex2f(-1, 1);
    glEnd();

    // Display menu options
    r.bot = gl.yres / 2 + 40;
    r.left = gl.xres / 2 - 80;
    r.center = 1;
    
    glColor3f(1.0, 1.0, 1.0); 
    ggprint8b(&r, 16, 0xFFFFFF00, "Game Paused: Press Esc to continue");
    r.bot -= 30;
}

