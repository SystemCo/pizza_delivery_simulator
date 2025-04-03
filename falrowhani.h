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
void drawPauseMenu();
void title_physics();
void initGame();
void physicsforCollision();
void title(Rect &r);
//bool checkCollision(Motorcycle& moto);


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
    int width;
    int height;
    float pos[2];
    float prev[2];
    float vel[2];
    float force[2];
    float color[3];
    char text[100];

     void render() {
        glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //cahnge to .01 

    glColor4f(color[0], color[1], color[2], 0.01f); // 40% opacity

    glBegin(GL_QUADS);
    glVertex2f(pos[0], pos[1]);
    glVertex2f(pos[0] + width, pos[1]);
    glVertex2f(pos[0] + width, pos[1] + height);
    glVertex2f(pos[0], pos[1] + height);
    glEnd();

    glDisable(GL_BLEND); 
}

    // Default Constructor
    Box() {
        width = 200;
        height = 275;
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
};


#endif
