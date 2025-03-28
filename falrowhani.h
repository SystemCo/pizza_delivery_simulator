#ifndef _FENOON_H_
#define _FENOON_H_
//#ifndef GL_H
//#define GL_H


#include "fonts.h"
#include <GL/glx.h>
//extern GL gl; 

//extern GameState gameState; 
enum GameState {
    PLAYING,
    PAUSED,
    MENU
};

extern GameState gameState;

void show_fenoon(Rect*r);

class Game_Button : public Button {
    private:
        char text[100] = "Exit title";
    public:
        void click(int x, int y);
        Game_Button();
        void draw();
};

class Restart_Button : public Button {
public:
    Restart_Button();
    void on_click();
    void click(int x, int y);
     void draw();
};
class Box {
public:
    int width, height;
    float pos[2], color[3];

    Box(int w, int h) {
        width = w;
        height = h;
        pos[0] = 100.0f;  // Example position
        pos[1] = 100.0f;
        color[0] = 0.3f;
        color[1] = 0.7f;
        color[2] = 0.3f;
    }

    // Render method to draw the box using OpenGL
    void render() {
        glColor3f(color[0], color[1], color[2]);  // Set the color

        glBegin(GL_QUADS);  // Draw a rectangle (box)
            glVertex2f(pos[0], pos[1]);
            glVertex2f(pos[0] + width, pos[1]);
            glVertex2f(pos[0] + width, pos[1] + height);
            glVertex2f(pos[0], pos[1] + height);
        glEnd();
    }
};
/*
class Box {
public:
    int width;
    int height;
    float pos[2];
    float prev[2];
    float vel[2];
    float force[2];
    float color[3];
    char text[100];

    // Default Constructor
    Box() {
        width = 100;
        height = 50;
        vel[0] = vel[1] = 0.0f;
        color[0] = 0.3f;
        color[1] = 0.7f;
        color[2] = 0.3f;
    }

    // Parameterized Constructor
    Box(int w, int h) {
        width = w;
        height = h;
        vel[0] = vel[1] = 0.0f;
        color[0] = 0.3f;
        color[1] = 0.7f;
        color[2] = 0.3f;
    }
};*/
#endif
