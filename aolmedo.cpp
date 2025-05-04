// Author: Avelina Olmedo
// Date: 02/28/2025
/***********************************************************************************/
#include "shared.h"
#include "aolmedo.h"

#include <cstdio>

extern Global gl;

// Background image file paths
const char* background_files[NUM_BACKGROUNDS] = {
    "./images/game2.jpg",   // Menu background
    "./images/map1.png"              // Game background
};

// Global array of background images
Image* backgrounds[NUM_BACKGROUNDS] = {nullptr};

void show_avelina(Rect* r);
void init_backgrounds();

// Initialize all background images
void init_backgrounds()
{
    for (int i = 0; i < NUM_BACKGROUNDS; i++) {
        backgrounds[i] = new Image(background_files[i]);
        backgrounds[i]->init_gl();
    }
}

void show_avelina(Rect* r)
{
    ggprint8b(r, 16, 0xffec407a, "Lina");
}

// Title Exit Button implementation
Title_Exit_Button::Title_Exit_Button() : Button(200, 200)
{
    this->set_text("Welcome to the Pizza Delivery Simulator!");
    this->set_color(0, 200, 200);
    this->set_pos(300, 300);
    this->set_dims(200, 50);
}

void Title_Exit_Button::click(int x, int y)
{
    if (is_inside(x, y))
        gl.screen = Home;
}

// Start Game Button implementation
StartGame_Button::StartGame_Button() : Button(200, 400)
{
    this->set_text("Start Game");
    this->set_color(255, 128, 0);  // Orange color for pizza theme
    this->set_pos(gl.xres/2, gl.yres/2 - 100);
    this->set_dims(250, 80);
}

void StartGame_Button::click(int x, int y)
{
    if (is_inside(x, y))
        gl.screen = Playing;
}

// Title screen physics function
void aolmedo_title_physics() 
{
    // Animate title screen elements if needed
    static float moto_offset = 0.0f;
    moto_offset += 0.5f;
    if (moto_offset > 360.0f) {
        moto_offset = 0.0f;
    }

    // Make the motorcycle move in a small circle or pattern
    float radius = 30.0f;
    float centerX = gl.xres/2 - 200;
    float centerY = gl.yres/2 + 100;

    float angle = moto_offset * (3.14159f / 180.0f);
    gl.moto_side->pos.x = centerX + radius * cos(angle);
    gl.moto_side->pos.y = centerY + radius * sin(angle);

    // Update start button animation if needed
    if (gl.start_button.darken) {
        gl.start_button.set_color(255, 100, 0); // Darker orange when hovered
    } else {
        gl.start_button.set_color(255, 128, 0); // Normal orange
    }
}
