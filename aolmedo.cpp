// Author: Avelina Olmedo
// Date: 02/28/2025
/***********************************************************************************/
#include "shared.h"
#include "aolmedo.h"
#include "falrowhani.h"
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
    if (is_inside(x,y)) {
        printf("Title clicked - navigating to Home menu\n");
        gl.screen = Home;
    }
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
    if (is_inside(x,y)) {
        printf("Start button clicked - navigating to menu\n");
        gl.screen = Home;
    }
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

    Rect r;
r.bot  = gl.yres - 20;
r.left = 10;


title(r);  

    ggprint8b(&r, 16, 0xffec407a, "Pizza Delivery Simulator");

    gl.title_button.render();
    gl.start_button.render();
}

void handle_title_input(int x, int y, bool is_press) {
    if (!is_press) return;
    gl.title_button.click(x,y);
    gl.start_button.click(x,y);
}

void handle_menu_click(int x, int y, bool is_press) {
    if (!is_press) return;
    
    // Debug output to show click coordinates
    //printf("Menu click: x=%d, y=%d\n", x, y);

     // Enhanced debug output to show click coordinates and current state
     printf("Menu click: x=%d, y=%d, gl.screen=%d\n", x, y, gl.screen);
    
    // Define precise rectangular areas for each menu item
    // X coordinates range from approximately 1/3 to 2/3 of screen width
    //const int left_boundary = gl.xres / 3;
   //const int right_boundary = (gl.xres * 2) / 3;

    // Check the coordinates visually against the menu image
    // The values below should be tuned based on the actual image layout
    
    // Center 60% of the screen width for x-bounds
    const int center_width = gl.xres * 0.6;
    const int left_boundary = (gl.xres - center_width) / 2;
    const int right_boundary = left_boundary + center_width;
    
    // "Start game" button area - roughly 1/4 down from the top of usable space
    // These y-values must be adjusted based on where items appear in the actual image
    const int start_top = (int)(gl.yres * 0.65);
    const int start_bottom = (int)(gl.yres * 0.55);
    
    // "How to play" button area - roughly middle of the screen
    const int howto_top = (int)(gl.yres * 0.5);
    const int howto_bottom = (int)(gl.yres * 0.4);
    
    // "Settings" button area - roughly 3/4 down the usable space
    const int settings_top = (int)(gl.yres * 0.35);
    const int settings_bottom = (int)(gl.yres * 0.25);
    
    // Print all boundaries for debugging
    printf("Boundaries: left=%d, right=%d\n", left_boundary, right_boundary);
    printf("Start game: bottom=%d, top=%d\n", start_bottom, start_top);
    printf("How to play: bottom=%d, top=%d\n", howto_bottom, howto_top);
    printf("Settings: bottom=%d, top=%d\n", settings_bottom, settings_top);
    
    // "Start game" button area
    if (x >= left_boundary && x <= right_boundary && 
        y >= start_bottom && y <= start_top) {
            printf("Starting game... changing screen to Playing\n");
        gl.screen = Playing;
    }
    // "How to play" button area
    else if (x >= left_boundary && x <= right_boundary && 
        y >= howto_bottom && y <= howto_top) {
            printf("Opening instructions... changing screen to Instructions\n");
        gl.screen = Instructions;
    }
    // "Settings" button area
    else if (x >= left_boundary && x <= right_boundary && 
        y >= settings_bottom && y <= settings_top) {
            printf("Opening settings... changing screen to Settings\n");
        gl.screen = Settings;
    }
    else {
        printf("Click not in any menu area\n");
    }
    // Print current screen after handling the click
    printf("Current screen after click: %d\n", gl.screen);
}

void render_menu_screen() {
    // clear
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Calculate appropriate scaling to fit the screen
    float img_scale = gl.scale * 0.8; // Reduce scale by 20% to make it smaller
    
    // draw the pizza menu properly scaled to fit the screen
    backgrounds[MENU_BG]
      ->show(img_scale, gl.xres/2, gl.yres/2, 0.0f);
      
    // Debug - show clickable regions (uncomment to visualize click areas)
    /*
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    int left = gl.xres/3;
    int right = (gl.xres*2)/3;
    int top = gl.yres/2 + 120;
    int bottom = gl.yres/2 + 60;
    glVertex2f(left, bottom);
    glVertex2f(right, bottom);
    glVertex2f(right, top);
    glVertex2f(left, top);
    glEnd();
    */
}

void handle_instructions_click(int x, int y, bool is_press) {
    if (!is_press) return;
    // Debug output
    printf("Instructions screen click: x=%d, y=%d - returning to menu\n", x, y);
    // anywhere you click, go back to menu:
    gl.screen = Home;
}

void render_instructions_screen() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Dim background
    backgrounds[MENU_BG]
      ->show(gl.scale, gl.xres/2, gl.yres/2, 0.0f);

    // Draw a centered text block
    Rect r;
    r.bot  = gl.yres - 100;
    r.left = 50;
    ggprint8b(&r, 24, 0xffffff00,
      "HOW TO PLAY:\n"
      "- Arrow keys to steer\n"
      "- Space to drop pizza\n"
      "- Deliver as many as you can!");

    // Hint
    ggprint8b(&r, 24, 0xff0000ff,
      "\n(click anywhere to return)");
}

// Simple volume control
void handle_settings_click(int x, int y, bool is_press) {
    if (!is_press) return;
    // Debug output
    printf("Settings screen click: x=%d, y=%d - returning to menu\n", x, y);
    gl.screen = Home;
}

void render_settings_screen() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw same menu BG
    backgrounds[MENU_BG]
      ->show(gl.scale, gl.xres/2, gl.yres/2, 0.0f);

    Rect r;
    r.bot  = gl.yres -  80;
    r.left = 50;
    ggprint8b(&r, 24, 0xffffff00,
      "SETTINGS:\n"
      "- Volume: %d%%\n"
      "- (click to return)", gl.volume);
}

// Add this new function to handle hover effects on menu items
void handle_menu_hover(int x, int y) {
    // Use the same boundaries as in the click handler
    // Center 60% of the screen width for x-bounds
    const int center_width = gl.xres * 0.6;
    const int left_boundary = (gl.xres - center_width) / 2;
    const int right_boundary = left_boundary + center_width;
    
    // "Start game" button area
    const int start_top = (int)(gl.yres * 0.65);
    const int start_bottom = (int)(gl.yres * 0.55);
    
    // "How to play" button area
    const int howto_top = (int)(gl.yres * 0.5);
    const int howto_bottom = (int)(gl.yres * 0.4);
    
    // "Settings" button area
    const int settings_top = (int)(gl.yres * 0.35);
    const int settings_bottom = (int)(gl.yres * 0.25);
    
    // Check if mouse is over any menu item
    if (x >= left_boundary && x <= right_boundary) {
        if (y >= start_bottom && y <= start_top) {
            // Hovering over Start Game
            // Debug - uncomment to track hovering
            // printf("Hovering over Start Game\n");
        }
        else if (y >= howto_bottom && y <= howto_top) {
            // Hovering over How to Play
            // Debug - uncomment to track hovering
            // printf("Hovering over How to Play\n");
        }
        else if (y >= settings_bottom && y <= settings_top) {
            // Hovering over Settings
            // Debug - uncomment to track hovering
            // printf("Hovering over Settings\n");
        }
    }
}
