// Author: Avelina Olmedo
// Date: 02/28/2025
/***********************************************************************************/
#include "shared.h"
#include "aolmedo.h"
#include <cstdio>
#include <GL/gl.h>
#include <cmath>

extern Global gl;

// Background image file paths
const char* background_files[NUM_BACKGROUNDS] = {
    "./images/game2.jpg",   // SPLASH_BG
    "./images/pizza-delivery-menu.png",  // MENU_BG
    "./images/map1.png"              // GAME_BG
};

// Global array of background images

Image* backgrounds[NUM_BACKGROUNDS] = {nullptr};


// Initialize all background images
void init_backgrounds()
{
    for (int i = 0; i < NUM_BACKGROUNDS; i++) {
        backgrounds[i] = new Image(background_files[i]);
        backgrounds[i]->init_gl();
    }
}

void show_avelina(Rect* r) {
    ggprint8b(r, 16, 0xffec407a, "Lina");
}

Title_Exit_Button::Title_Exit_Button()
  : Button(200,200)
{
    set_text("Welcome to the Pizza Delivery Simulator!");
    set_color(0,200,200);
    set_pos(300,300);
    set_dims(200,50);
}
void Title_Exit_Button::click(int x, int y) {
    if (is_inside(x,y)) gl.screen = Home;
}

StartGame_Button::StartGame_Button()
  : Button(200,400)
{
    set_text("Start Game");
    set_color(255,128,0);
    set_pos(gl.xres/2, gl.yres/2 - 100);
    set_dims(250,80);
}
void StartGame_Button::click(int x, int y) {
    if (is_inside(x,y)) gl.screen = Playing;
}

void aolmedo_title_physics() {
    static float moto_offset = 0.0f;
    moto_offset += 0.5f;
    if (moto_offset > 360.0f) moto_offset = 0.0f;

    float radius = 30.0f;
    float cx = gl.xres/2 - 200, cy = gl.yres/2 + 100;
    float ang = moto_offset * (3.14159f/180.0f);
    gl.moto_side->pos.x = cx + radius * cos(ang);
    gl.moto_side->pos.y = cy + radius * sin(ang);

    // hover-fade on the Start button
    if (gl.start_button.darken)
        gl.start_button.set_color(255,100,0);
    else
        gl.start_button.set_color(255,128,0);
}

void render_title_screen() {
    glClear(GL_COLOR_BUFFER_BIT);
    backgrounds[SPLASH_BG]
      ->show(gl.scale, gl.xres/2, gl.yres/2, 0.0f);
    gl.moto_side->render();

    Rect r = { .bot = gl.yres - 20, .left = 10 };
    ggprint8b(&r, 16, 0xffec407a, "Pizza Delivery Simulator");

    gl.title_button.render();
    gl.start_button.render();
}

void handle_title_input(int x, int y, bool is_press) {
    if (!is_press) return;
    gl.title_button.click(x,y);
    gl.start_button.click(x,y);
}

void render_menu_screen() {
    // clear
    glClear(GL_COLOR_BUFFER_BIT);
    // draw the pizza menu full-screen
    backgrounds[MENU_BG]
      ->show(gl.scale, gl.xres/2, gl.yres/2, 0.0f);
}

void handle_menu_click(int x, int y, bool is_press) {
    if (!is_press) return;
    // just one button for now: if they click roughly in the “Start game” region…
    // you may want to fine-tune these bounds to match the pixels in your image!
    const int left   = gl.xres/2 - 100;
    const int right  = gl.xres/2 + 100;
    const int top    = gl.yres/2 +  20;  // adjust based on your art
    const int bottom = gl.yres/2 -  20;
    if (x >= left && x <= right &&
        y >= bottom && y <= top) {
      gl.screen = Playing;
    }
    
}


