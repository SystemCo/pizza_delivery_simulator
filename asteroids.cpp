//
//program: asteroids.cpp
//author:  Gordon Griesel
//date:    2014 - 2025
//mod spring 2015: added constructors
//This program is a game starting point for a 3350 project.
//
//
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <ctime>
#include <cmath>
//#include <X11/Xutil.h>
//#include <GL/gl.h>
//#include <GL/glu.h>

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>

#include "headers.h"

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

Global::Global() {
    xres = 640;
    yres = 480;
    //screen = Playing;
    screen = Title;
    memset(keys, 0, 65536);
    credits = 0;
    show_bike = 0;

    // mouse value 1 = true = mouse is a regular mouse.
    mouse_cursor_on = 1;
    moto_side = new Entity("images/moto_side.gif");
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
    srand(time(NULL));
    clock_gettime(CLOCK_REALTIME, &timePause);
    clock_gettime(CLOCK_REALTIME, &timeStart);
    x11.set_mouse_position(200, 200);
    x11.show_mouse_cursor(gl.mouse_cursor_on);
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
        while (physicsCountdown >= physicsRate) {
            switch (gl.screen) {
                case Title:
                    title_physics();
                    break;
                default:
                    physics();
            }
            physicsCountdown -= physicsRate;
        }
        switch (gl.screen) {
            case Title:
                title_render();
                break;
            default:
                render();
        }
        x11.swapBuffers();
    }
    cleanup_fonts();
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
    glClearColor(0.0, 0.0, 0.0, 1.0);
    //Do this to allow fonts
    glEnable(GL_TEXTURE_2D);
    initialize_fonts();
    gl.bike.init_gl();
    gl.background.init_gl();
    gl.moto_side->img->init_gl();
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
    //std::cout << "m" << std::endl << std::flush;
    if (e->type == ButtonRelease) {
        return;
    }
    if (e->type == ButtonPress) {
        if (e->xbutton.button==1) {
            //Left button is down
            //a little time between each bullet
            struct timespec bt;
            clock_gettime(CLOCK_REALTIME, &bt);
            double ts = timeDiff(&g.bulletTimer, &bt);
            if (ts > 0.1) {
                timeCopy(&g.bulletTimer, &bt);
                //shoot a bullet...
                if (g.nbullets < MAX_BULLETS) {
                    Bullet *b = &g.barr[g.nbullets];
                    timeCopy(&b->time, &bt);
                    b->pos[0] = g.ship.pos[0];
                    b->pos[1] = g.ship.pos[1];
                    b->vel[0] = g.ship.vel[0];
                    b->vel[1] = g.ship.vel[1];
                    //convert ship angle to radians
                    Flt rad = ((g.ship.angle+90.0) / 360.0f) * PI * 2.0;
                    //convert angle to a vector
                    Flt xdir = cos(rad);
                    Flt ydir = sin(rad);
                    b->pos[0] += xdir*20.0f;
                    b->pos[1] += ydir*20.0f;
                    b->vel[0] += xdir*6.0f + rnd()*0.1;
                    b->vel[1] += ydir*6.0f + rnd()*0.1;
                    b->color[0] = 1.0f;
                    b->color[1] = 1.0f;
                    b->color[2] = 1.0f;
                    ++g.nbullets;
                }
            }
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
            //std::cout << "xdiff: " << xdiff << std::endl << std::flush;
            g.ship.angle += 0.05f * (float)xdiff;
            if (g.ship.angle >= 360.0f)
                g.ship.angle -= 360.0f;
        }
        else if (xdiff < 0) {
            //std::cout << "xdiff: " << xdiff << std::endl << std::flush;
            g.ship.angle += 0.05f * (float)xdiff;
            if (g.ship.angle < 0.0f)
                g.ship.angle += 360.0f;
        }
        if (ydiff > 0) {
            //apply thrust
            //convert ship angle to radians
            Flt rad = ((g.ship.angle+90.0) / 360.0f) * PI * 2.0;
            //convert angle to a vector
            Flt xdir = cos(rad);
            Flt ydir = sin(rad);
            g.ship.vel[0] += xdir * (float)ydiff * 0.01f;
            g.ship.vel[1] += ydir * (float)ydiff * 0.01f;
            Flt speed = sqrt(g.ship.vel[0]*g.ship.vel[0]+
                    g.ship.vel[1]*g.ship.vel[1]);
            if (speed > 10.0f) {
                speed = 10.0f;
                normalize2d(g.ship.vel);
                g.ship.vel[0] *= speed;
                g.ship.vel[1] *= speed;
            }
            g.mouseThrustOn = true;
            clock_gettime(CLOCK_REALTIME, &g.mouseThrustTimer);
        }
        x11.set_mouse_position(200,200);
        savex = 200;
        savey = 200;
    }
}

int check_keys(XEvent *e)
{
    //static int shift=0;
    if (e->type != KeyRelease && e->type != KeyPress) {
        //not a keyboard event
        return 0;
    }
    int key = (XLookupKeysym(&e->xkey, 0) & 0x0000ffff);
    //Log("key: %i\n", key);
    if (e->type == KeyRelease) {
        //gl.keys[key] = 0;
        //if (key == XK_Shift_L || key == XK_Shift_R)
            //shift = 0;
        switch (key) {
            case XK_Left:
                gl.bike.unleft();
                break;
            case XK_Right:
                gl.bike.unright();
                break;
            case XK_Up:
                gl.bike.set_pedal(Neutral);
                break;
            case XK_Down:
                gl.bike.set_pedal(Neutral);
                break;
        }
        return 0;
    }
    if (e->type == KeyPress) {
        //gl.keys[key]=1;
        if (key == XK_Shift_L || key == XK_Shift_R) {
            //shift = 1;
            //return 0;
        }
    }
    //(void)shift;
    // if any button is pushed, exit the title menu. 
    // Currently would break pause and credits
    gl.screen = Playing;
    switch (key) {
        case XK_Escape:
            // TODO: Pause
            // set gl.screen to pause state
            return 1;
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
            gl.bike.set_left();
            break;
        case XK_Right:
            gl.bike.set_right();
            break;
        case XK_Down:
            gl.bike.set_pedal(Backward);
            break;
        case XK_Up:
            gl.bike.set_pedal(Forward);
        case XK_equal:
            break;
        case XK_minus:
            break;
    }
    return 0;
}
void physics()
{

    gl.bike.move();
}

void render()
{
    Rect r;
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    int wid = resolution_scale(&gl.background);
    gl.background.show(wid, gl.xres/2, gl.yres/2, 0.0f);
    r.bot = gl.yres - 20;
    r.left = 10;
    r.center = 0;
    ggprint8b(&r, 16, 0x00ff0000, "3350 - Asteroids");
    ggprint8b(&r, 16, 0x00ffff00, "n bullets: %i", g.nbullets);
    ggprint8b(&r, 16, 0x00ffff00, "n asteroids: %i", g.nasteroids);
    ggprint8b(&r, 16, 0x00ff00ff, "Press C for credits");
    if (gl.credits) {
        show_david(&r);
        //show_francisco();
    }

    if (gl.show_bike)
        gl.bike.render();
}
