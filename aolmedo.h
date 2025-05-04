// Author: Avelina Olmedo
// Date: 02/28/2025

#ifndef AOLMEDO_H
#define AOLMEDO_H
#include "fonts.h"
#include "image.h"
#include "dcarter.h"


// Macros for background indexing
#define SPLASH_BG 0
#define MENU_BG 1
#define GAME_BG 2
#define NUM_BACKGROUNDS 3



// Function declarations
void show_avelina(Rect *r);
void init_backgrounds();

// "Home" pizza menu
void render_menu_screen();
void handle_menu_click(int x, int y, bool is_press);

// “How to play” screen
void render_instructions_screen();
void handle_instructions_click(int x, int y, bool is_press);

// “Settings” screen
void render_settings_screen();
void handle_settings_click(int x, int y, bool is_press);

void render_title_screen();
void handle_title_input(int x, int y, bool is_press);

void aolmedo_title_physics();



// Global array of background images
extern Image* backgrounds[NUM_BACKGROUNDS];



// Title exit button class
class Title_Exit_Button : public Button {
    //private:
    
        //char text[100] = "Exit title";
    public:
        Title_Exit_Button();
        void click(int x, int y);
        
};


// Start Game button for main menu
class StartGame_Button : public Button {
    //private:
        //char text[100] = "Start Game";
    public:
        StartGame_Button();
        void click(int x, int y);
        
};


#endif // AOLMEDO_H

