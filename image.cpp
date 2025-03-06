//#include "headers.h"
#include "image.h"
#include "shared.h"
#include <cstring>
//#include <cstdio>
#include <iostream>
#include <unistd.h>
//#include <stdlib.h>

//#include <string.h>
//#include <cstdlib>

#define SAFE_LINE_READ(line, count, pointer) \
    if ( fgets(line, count, pointer) == NULL)\
        std::cout << "error reading line " << line << " of image file\n"
// Semicolon must be used during implementation of this macro
// Writen this way follow style

// =============================================================
// Extracted or taken whole from rainforest framework by David.
// Rainforest start:
Image::Image(const char *fname)
{ // From the rainforest framework
    if (fname[0] == '\0')
        return;
    printf("fname **%s**\n", fname);
    // ========================================================
    // Uses CLI MagickConvert to get PPM
    char name[40];
    strcpy(name, fname);
    const int slen = strlen(name);
    const int ppmFlag = strncmp(name+(slen-4), ".ppm", 4) == 0;
    is_jpg = strncmp(name+(slen-4), ".jpg", 4) == 0;
    const unsigned char clr_byte = is_jpg ? 255 : 0;
    for (int i=0; i<3; i++)
        alphaColor[i] = clr_byte;
    //jpg == white, everything else == black
    char ppmname[80];
    if (ppmFlag) {
        strcpy(ppmname, name);
    } else {
        name[slen-4] = '\0';
        sprintf(ppmname,"%s.ppm", name);
        char convert_command[100];
        //system("convert eball.jpg eball.ppm");
        sprintf(convert_command, "convert %s %s", fname, ppmname);
        if( system(convert_command) )
            std::cout << "Magick Convert failed\n";
    }
    FILE *fpi = fopen(ppmname, "r");
    if (fpi) {
        char line[200];
        //First two lines of ppm must be trashed
        SAFE_LINE_READ(line, 200, fpi);
        SAFE_LINE_READ(line, 200, fpi);
        //skip comments and blank lines
        while (line[0] == '#' || strlen(line) < 2)
            SAFE_LINE_READ(line, 200, fpi);
        //Width and Height extracted according to ppm encoding
        sscanf(line, "%i %i", &width, &height);
        SAFE_LINE_READ(line, 200, fpi);
        //get pixel data
        const int n = width * height * 3;
        data = new unsigned char[n];
        for (int i=0; i<n; i++)
            data[i] = fgetc(fpi);
        //printf("%s", data);
        fclose(fpi);
    } else {
        printf("ERROR opening image: %s\n",ppmname);
        exit(0);
    }
    // Delete the temporary ppm file, but only if we used convert to make it
    if (!ppmFlag)
        unlink(ppmname);
} 

void Image::show(float wid, int pos_x, int pos_y, float angle, int flipped)
{
    Image* img = this;
    const float height = wid * img->height/img->width;
    glBindTexture(GL_TEXTURE_2D, img->texture);
    glColor4f(0.0, 0.0, 0.0, 0.0);
    glPushMatrix(); // Pushmatrix indented because subequent commands
                    // Are implemented on the topmost stack as determined
                    // By glPush and glPop
        glTranslatef(pos_x, pos_y, 0.0f);
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.0f);
        glColor4ub(255,255,255,255);
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
        glBegin(GL_QUADS);
        if (flipped) {
            glTexCoord2i(1, 1); glVertex2i(-wid,-height);
            glTexCoord2i(1, 0); glVertex2i(-wid, height);
            glTexCoord2i(0, 0); glVertex2i( wid, height);
            glTexCoord2i(0, 1); glVertex2i( wid,-height);
        } else {
            //glTexCoord2f(1.0f, 1.0f); glVertex2i(-wid,-height);
            glTexCoord2i(0, 1); glVertex2i(-wid,-height);
            glTexCoord2i(0, 0); glVertex2i(-wid, height);
            glTexCoord2i(1, 0); glVertex2i( wid, height);
            glTexCoord2i(1, 1); glVertex2i( wid,-height);
        }
        glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0); // Unbinds texture
}

void Image::init_gl()
{
    glGenTextures(1, &texture);
    const int w = width;
    const int h = height;
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *silhouetteData;
    bool is_black = !(alphaColor[0]||alphaColor[1]||alphaColor[2]);
    if (is_black)
        silhouetteData = this->blackToAlpha();
    else
        silhouetteData = this->colorToAlpha(alphaColor);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);
    free(silhouetteData);
}

// rainforest end

// =============================================================
// Asteroids framework start
extern Global gl;
X11_wrapper::X11_wrapper(int w, int h)
{
    GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
    //GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, None };
    XSetWindowAttributes swa;
    setup_screen_res(gl.xres, gl.yres);
    dpy = XOpenDisplay(NULL);
    if (dpy == NULL) {
        std::cout << "\n\tcannot connect to X server" << std::endl;
        exit(EXIT_FAILURE);
    }
    const Window root = DefaultRootWindow(dpy);
    XWindowAttributes getWinAttr;
    XGetWindowAttributes(dpy, root, &getWinAttr);
    int fullscreen = 0;
    gl.xres = w;
    gl.yres = h;
    if (!w && !h) {
        //Go to fullscreen.
        gl.xres = getWinAttr.width;
        gl.yres = getWinAttr.height;
        //When window is fullscreen, there is no client window
        //so keystrokes are linked to the root window.
        XGrabKeyboard(dpy, root, False,
                GrabModeAsync, GrabModeAsync, CurrentTime);
        fullscreen=1;
    }
    XVisualInfo *vi = glXChooseVisual(dpy, 0, att);
    if (vi == NULL) {
        std::cout << "\n\tno appropriate visual found\n" << std::endl;
        exit(EXIT_FAILURE);
    } 
    const Colormap cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
    swa.colormap = cmap;
    swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
        PointerMotionMask | MotionNotify | ButtonPress | ButtonRelease |
        StructureNotifyMask | SubstructureNotifyMask;
    unsigned int winops = CWBorderPixel|CWColormap|CWEventMask;
    if (fullscreen) {
        winops |= CWOverrideRedirect;
        swa.override_redirect = True;
    }
    win = XCreateWindow(dpy, root, 0, 0, gl.xres, gl.yres, 0,
            vi->depth, InputOutput, vi->visual, winops, &swa);
    //win = XCreateWindow(dpy, root, 0, 0, gl.xres, gl.yres, 0,
    //vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
    set_title();
    glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
    glXMakeCurrent(dpy, win, glc);
    show_mouse_cursor(0);
}

X11_wrapper::~X11_wrapper()
{
    XDestroyWindow(dpy, win);
    XCloseDisplay(dpy);
}

void X11_wrapper::set_title()
{
    //Set the window title bar.
    XMapWindow(dpy, win);
#ifdef SLEEP_TEST
    XStoreName(dpy, win, "Sleep test");
#elif defined GENERIC_TEST
    XStoreName(dpy, win, "Generic Test");
#else
    XStoreName(dpy, win, "Pizza Delivery SUPREME!");
#endif
}

void X11_wrapper::check_resize(XEvent *e)
{
    //The ConfigureNotify is sent by the
    //server if the window is resized.
    if (e->type != ConfigureNotify)
        return;
    const XConfigureEvent xce = e->xconfigure;
    if (xce.width != gl.xres || xce.height != gl.yres) {
        //Window size did change.
        reshape_window(xce.width, xce.height);
    }
}

void X11_wrapper::reshape_window(int width, int height)
{
    //window has been resized.
    setup_screen_res(width, height);
    glViewport(0, 0, (GLint)width, (GLint)height);
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    glMatrixMode(GL_MODELVIEW); glLoadIdentity();
    glOrtho(0, gl.xres, 0, gl.yres, -1, 1);
    set_title();
}

void X11_wrapper::setup_screen_res(const int w, const int h)
{
    gl.xres = w;
    gl.yres = h;
}

void X11_wrapper::swapBuffers()
{
    glXSwapBuffers(dpy, win);
}

bool X11_wrapper::getXPending()
{
    return XPending(dpy);
}

XEvent X11_wrapper::getXNextEvent()
{
    XEvent e;
    XNextEvent(dpy, &e);
    return e;
}

void X11_wrapper::set_mouse_position(int x, int y)
{
    XWarpPointer(dpy, None, win, 0, 0, 0, 0, x, y);
}

void X11_wrapper::show_mouse_cursor(const int onoff)
{
    printf("show_mouse_cursor(%i)\n", onoff); fflush(stdout);
    if (onoff) {
        //this removes our own blank cursor.
        XUndefineCursor(dpy, win);
        return;
    }
    //vars to make blank cursor
    Pixmap blank;
    XColor dummy;
    char data[1] = {0};
    Cursor cursor;
    //make a blank cursor
    blank = XCreateBitmapFromData (dpy, win, data, 1, 1);
    if (blank == None)
        std::cout << "error: out of memory." << std::endl;
    cursor = XCreatePixmapCursor(dpy, blank, blank, &dummy, &dummy, 0, 0);
    XFreePixmap(dpy, blank);
    //this makes the cursor. then set it using this function
    XDefineCursor(dpy, win, cursor);
    //after you do not need the cursor anymore use this function.
    //it will undo the last change done by XDefineCursor
    //(thus do only use ONCE XDefineCursor and then XUndefineCursor):
}

// =============================================================
// Asteroids framework end

