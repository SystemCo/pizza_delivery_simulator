// Author: Avelina Olmedo
// Date: 02/28/2025

#ifndef AOLMEDO_H
#define AOLMEDO_H
#include "fonts.h"
#include "image.h"

// Macros for background indexing
#define MENU_BG 0
#define GAME_BG 1
#define NUM_BACKGROUNDS 2


// Function declarations
void show_avelina(Rect *r);
void init_backgrounds();
void aolmedo_title_physics();

// Global array of background images
extern Image* backgrounds[NUM_BACKGROUNDS];



// Title exit button class
class Title_Exit_Button : public Button {
    private:
        char text[100] = "Exit title";
    public:
        void click(int x, int y);
        Title_Exit_Button();
};


// Start Game button for main menu
class StartGame_Button : public Button {
    private:
        char text[100] = "Start Game";
    public:
        void click(int x, int y);
        StartGame_Button();
};


#endif // AOLMEDO_H

