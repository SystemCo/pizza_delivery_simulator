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
#endif
