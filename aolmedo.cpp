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
    set_text("WELCOME TO THE PIZZA DELIVERY SIMULATOR!");
    /*set_color(0,200,200);
    set_pos(300,300);
    set_dims(200,50);
    */
    set_color(255,100,0);
    set_pos(gl.xres/2 + 100, gl.yres/2 + 200);
    set_dims(400,70);
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
    //set_pos(gl.xres/2, gl.yres/2 - 100);
    //set_dims(250,80);
    set_color(255,180,0);
    set_pos(gl.xres/2, gl.yres/2 + 150);
    set_dims(300,80);
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

    /* hover-fade on the Start button
    if (gl.start_button.darken)
        gl.start_button.set_color(255,100,0);
    else
        gl.start_button.set_color(255,128,0);
    */
}

void render_title_screen() {
    glClear(GL_COLOR_BUFFER_BIT);
    backgrounds[SPLASH_BG]
      ->show(gl.scale, gl.xres/2, gl.yres/2, 0.0f);
    gl.moto_side->render();

    Rect r;
    r.bot  = gl.yres - 20;
    r.left = 10;
    ggprint8b(&r, 16, 0xffec407a, "Pizza Delivery Simulator");

    gl.title_button.render();
    //gl.start_button.render();
}

void handle_title_input(int x, int y, bool is_press) {
    if (!is_press) return;
    gl.title_button.click(x,y);
    //gl.start_button.click(x,y);
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
    
    // Center 80% of the screen width for x-bounds
    const int center_width = gl.xres * 0.8;
    const int left_boundary = (gl.xres - center_width) / 2;
    const int right_boundary = left_boundary + center_width;
    
    // "Start game" button area - roughly 1/4 down from the top of usable space
    // These y-values must be adjusted based on where items appear in the actual image
    //const int start_top = (int)(gl.yres * 0.65);

    // "Start game" button area - widened vertical range
    const int start_top = (int)(gl.yres * 0.75);      // Increased from 0.70
    const int start_bottom = (int)(gl.yres * 0.50);   // Decreased from 0.55
    
    // "How to play" button area - roughly middle of the screen
   //const int howto_top = (int)(gl.yres * 0.5);
    //const int howto_bottom = (int)(gl.yres * 0.4);

    // "How to play" button area - widened vertical range
    const int howto_top = (int)(gl.yres * 0.55);      // Increased from 0.50
    const int howto_bottom = (int)(gl.yres * 0.30);   // Decreased from 0.35
    
    // "Settings" button area - roughly 3/4 down the usable space
   // const int settings_top = (int)(gl.yres * 0.35);
   // const int settings_bottom = (int)(gl.yres * 0.25);
    
    // Print all boundaries for debugging
   // printf("Boundaries: left=%d, right=%d\n", left_boundary, right_boundary);
   // printf("Start game: bottom=%d, top=%d\n", start_bottom, start_top);
   // printf("How to play: bottom=%d, top=%d\n", howto_bottom, howto_top);
   // printf("Settings: bottom=%d, top=%d\n", settings_bottom, settings_top);
   
   // "Settings" button area - widened vertical range
   const int settings_top = (int)(gl.yres * 0.35);   // Increased from 0.30
   const int settings_bottom = (int)(gl.yres * 0.10); // Decreased from 0.15


    // "Start game" button area
    if (x >= left_boundary && x <= right_boundary && 
        y >= start_bottom && y <= start_top) {
            printf("Starting game... changing screen to Playing\n");
        gl.screen = Playing;
        gameState = PLAYING;  // Also set the gameState to ensure proper game rendering
        gl.remainingTime = gl.gameTime;  // Reset game timer when starting a new game
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
   // else {
   //     printf("Click not in any menu area\n");
   // }
    // Print current screen after handling the click
    //printf("Current screen after click: %d\n", gl.screen);
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

     /* Add a title at the top
     Rect r;
     r.bot = gl.yres - 30;
     r.left = gl.xres/2 - 100;
     ggprint8b(&r, 24, 0xffec407a, "PIZZA DELIVERY MENU");
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
      //->show(gl.scale, gl.xres/2, gl.yres/2, 0.0f);
      ->show(gl.scale * 0.8, gl.xres/2, gl.yres/2, 0.0f);

      // Draw a semi-transparent black rectangle for the popup
      int popup_width = 650;
      int popup_height = 450;
      int popup_x = gl.xres/2 - popup_width/2;
      int popup_y = gl.yres/2 - popup_height/2;
      
      // Draw semi-transparent background
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(0.0f, 0.0f, 0.0f, 0.9f);  // Black with 90% opacity
      glBegin(GL_QUADS);
      glVertex2i(popup_x, popup_y);
      glVertex2i(popup_x + popup_width, popup_y);
      glVertex2i(popup_x + popup_width, popup_y + popup_height);
      glVertex2i(popup_x, popup_y + popup_height);
      glEnd();
      glDisable(GL_BLEND);
      
      // Draw border
      glColor3f(1.0f, 0.5f, 0.0f);  // Orange border
      glBegin(GL_LINE_LOOP);
      glVertex2i(popup_x, popup_y);
      glVertex2i(popup_x + popup_width, popup_y);
      glVertex2i(popup_x + popup_width, popup_y + popup_height);
      glVertex2i(popup_x, popup_y + popup_height);
      glEnd();
  
      // Draw title
    Rect r;
   
   /* r.bot  = gl.yres - 100;
    r.left = 50;
    ggprint8b(&r, 24, 0xffffff00,
      "HOW TO PLAY:\n"
      "- Arrow keys to steer\n"
      "- Space to drop pizza\n"
      "- Deliver as many as you can!");

    // Hint
    ggprint8b(&r, 24, 0xff0000ff,
      "\n(click anywhere to return)");
      */
      r.bot = popup_y + popup_height - 80;
      r.left = popup_x + popup_width/2 - 110;
      ggprint16(&r, 48, 0xffffcc00, "HOW TO PLAY");
      
     // Draw instructions - repositioned more centrally
     int text_left = popup_x + 120;  // Move text further right
     r.bot = popup_y + popup_height - 160;
     r.left = text_left;
    ggprint8b(&r, 26, 0xffffffff,
        "- Use ARROW KEYS to control your delivery motorcycle");
      r.bot -= 50;
      r.left = text_left;
      ggprint8b(&r, 26, 0xffffffff,
        "- Press SPACEBAR to drop a pizza at a delivery location");
      r.bot -= 50;
      r.left = text_left;
      ggprint8b(&r, 26, 0xffffffff,
        "- Deliver pizzas within the time limit to earn money");
      r.bot -= 50;
      r.left = text_left;
      ggprint8b(&r, 26, 0xffffffff,
        "- Avoid obstacles and other vehicles on the road");
      r.bot -= 50;
      r.left = text_left;
      ggprint8b(&r, 26, 0xffffffff,
        "- Press ESC to pause the game");
  
      // Draw return instruction 
      r.bot = popup_y + 70;
      r.left = popup_x + popup_width/2 - 140;
      ggprint8b(&r, 28, 0xffff6600, "Press ESC to return to menu");

}

// Simple volume control
void handle_settings_click(int x, int y, bool is_press) {
  
    if (!is_press) return;
    // Debug output
    //printf("Settings screen click: x=%d, y=%d - returning to menu\n", x, y);
    //gl.screen = Home;

printf("Settings screen click: x=%d, y=%d\n", x, y);
    
    // Define the popup dimensions (match the instructions popup)
    int popup_width = 600;
    int popup_height = 400;
    int popup_x = gl.xres/2 - popup_width/2;
    int popup_y = gl.yres/2 - popup_height/2;
    
    // Define the volume buttons
    int btn_width = 60;
    int btn_height = 60;
    int vol_up_x = popup_x + popup_width - 240;
    int vol_up_y = popup_y + popup_height/2 - 50;
    int vol_down_x = popup_x + 180;
    int vol_down_y = popup_y + popup_height/2 - 50;
    
    // Check for volume up button click
    if (x >= vol_up_x && x <= vol_up_x + btn_width && 
        y >= vol_up_y - btn_height && y <= vol_up_y) {
        // Increase volume by 10%
        gl.volume = (gl.volume + 10 > 100) ? 100 : gl.volume + 10;
        printf("Volume increased to %d%%\n", gl.volume);
    }
    // Check for volume down button click
    else if (x >= vol_down_x && x <= vol_down_x + btn_width && 
             y >= vol_down_y - btn_height && y <= vol_down_y) {
        // Decrease volume by 10%
        gl.volume = (gl.volume - 10 < 0) ? 0 : gl.volume - 10;
        printf("Volume decreased to %d%%\n", gl.volume);
    }
    // Check for close button click (anywhere outside the popup)
    else if (x < popup_x || x > popup_x + popup_width || 
             y < popup_y || y > popup_y + popup_height) {
        gl.screen = Home;
    }
}

void render_settings_screen() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw same menu BG
    backgrounds[MENU_BG]
    ->show(gl.scale * 0.8, gl.xres/2, gl.yres/2, 0.0f);

    // Draw a semi-transparent black rectangle for the popup
    int popup_width = 600;
    int popup_height = 400;
    int popup_x = gl.xres/2 - popup_width/2;
    int popup_y = gl.yres/2 - popup_height/2;
    
    // Draw semi-transparent background
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.9f);  // Black with 90% opacity
    glBegin(GL_QUADS);
    glVertex2i(popup_x, popup_y);
    glVertex2i(popup_x + popup_width, popup_y);
    glVertex2i(popup_x + popup_width, popup_y + popup_height);
    glVertex2i(popup_x, popup_y + popup_height);
    glEnd();
    glDisable(GL_BLEND);
    
    // Draw border
    glColor3f(1.0f, 0.5f, 0.0f);  // Orange border
    glBegin(GL_LINE_LOOP);
    glVertex2i(popup_x, popup_y);
    glVertex2i(popup_x + popup_width, popup_y);
    glVertex2i(popup_x + popup_width, popup_y + popup_height);
    glVertex2i(popup_x, popup_y + popup_height);
    glEnd();

    // Draw title

   /* Rect r;
    r.bot  = gl.yres -  80;
    r.left = 50;
    ggprint8b(&r, 24, 0xffffff00,
      "SETTINGS:\n"
      "- Volume: %d%%\n"
      "- (click to return)", gl.volume);
      */
      Rect r;
      r.bot = popup_y + popup_height - 70;
      r.left = popup_x + popup_width/2 - 80; // Center the title
      ggprint16(&r, 42, 0xffffcc00, "SETTINGS");
      
      // Draw volume setting - centered
    r.bot = popup_y + popup_height/2 + 30;
    r.left = popup_x + popup_width/2 - 80;
    ggprint16(&r, 36, 0xffffffff, "Volume: %d%%", gl.volume);
      
      // Draw volume control buttons
      int btn_width = 60;
      int btn_height = 60;
      
      // Volume down button (-)
      int vol_down_x = popup_x + 180;
      int vol_down_y = popup_y + popup_height/2 - 50;
      glColor3f(0.8f, 0.3f, 0.0f);
      glBegin(GL_QUADS);
      glVertex2i(vol_down_x, vol_down_y - btn_height);
      glVertex2i(vol_down_x + btn_width, vol_down_y - btn_height);
      glVertex2i(vol_down_x + btn_width, vol_down_y);
      glVertex2i(vol_down_x, vol_down_y);
      glEnd();
      
      // Volume up button (+)
      int vol_up_x = popup_x + popup_width - 240;
      int vol_up_y = popup_y + popup_height/2 - 50;
      glBegin(GL_QUADS);
      glVertex2i(vol_up_x, vol_up_y - btn_height);
      glVertex2i(vol_up_x + btn_width, vol_up_y - btn_height);
      glVertex2i(vol_up_x + btn_width, vol_up_y);
      glVertex2i(vol_up_x, vol_up_y);
      glEnd();
    
      // Draw - and + symbols
    r.bot = vol_down_y - btn_height/2 - 10;
    r.left = vol_down_x + btn_width/2 - 8;
    ggprint16(&r, 40, 0xffffffff, "-");
    
    r.bot = vol_up_y - btn_height/2 - 10;
    r.left = vol_up_x + btn_width/2 - 8;
    ggprint16(&r, 40, 0xffffffff, "+");
    
    // Volume bar
    int bar_width = vol_up_x - vol_down_x - btn_width;
    int bar_height = 30;
    int bar_x = vol_down_x + btn_width;
    int bar_y = vol_down_y - btn_height/2 - bar_height/2;
    
    // Draw volume bar background
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    glVertex2i(bar_x, bar_y);
    glVertex2i(bar_x + bar_width, bar_y);
    glVertex2i(bar_x + bar_width, bar_y + bar_height);
    glVertex2i(bar_x, bar_y + bar_height);
    glEnd();
    
    // Draw volume level
    int level_width = (bar_width * gl.volume) / 100;
    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2i(bar_x, bar_y);
    glVertex2i(bar_x + level_width, bar_y);
    glVertex2i(bar_x + level_width, bar_y + bar_height);
    glVertex2i(bar_x, bar_y + bar_height);
    glEnd();
    
    // Draw return instruction
    r.bot = popup_y + 60;
    r.left = popup_x + popup_width/2 - 120;
    ggprint8b(&r, 24, 0xffff6600, "Press ESC to return to menu");

}

// Add this new function to handle hover effects on menu items
void handle_menu_hover(int x, int y) {
    // Use the same boundaries as in the click handler
    // Center 80% of the screen width for x-bounds
    const int center_width = gl.xres * 0.8;
    const int left_boundary = (gl.xres - center_width) / 2;
    const int right_boundary = left_boundary + center_width;
    
    // "Start game" button area
    const int start_top = (int)(gl.yres * 0.75);
    const int start_bottom = (int)(gl.yres * 0.50);
    
    // "How to play" button area
    const int howto_top = (int)(gl.yres * 0.55);
    const int howto_bottom = (int)(gl.yres * 0.30);
    
    // "Settings" button area
    const int settings_top = (int)(gl.yres * 0.35);
    const int settings_bottom = (int)(gl.yres * 0.10);

    // Reset hover state
    gl.start_button.darken = false;
    
     // Check if cursor is in any menu area
    if (x >= left_boundary && x <= right_boundary) {
        if (y >= start_bottom && y <= start_top) {
            // Hovering over Start Game
            // Debug - uncomment to track hovering
            // printf("Hovering over Start Game\n");

            // Hover over "Start Game"
            gl.start_button.darken = true;
            
            // Visual feedback for hover (can be expanded)
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor4f(1.0f, 0.5f, 0.0f, 0.3f);  // Orange with transparency
            glBegin(GL_QUADS);
            glVertex2i(left_boundary, start_bottom);
            glVertex2i(right_boundary, start_bottom);
            glVertex2i(right_boundary, start_top);
            glVertex2i(left_boundary, start_top);
            glEnd();
            glDisable(GL_BLEND);
        }
        else if (y >= howto_bottom && y <= howto_top) {
            // Hovering over How to Play
            // Debug - uncomment to track hovering
            // printf("Hovering over How to Play\n");

             // Hover over "How to Play"
             glEnable(GL_BLEND);
             glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
             glColor4f(1.0f, 0.5f, 0.0f, 0.3f);  // Orange with transparency
             glBegin(GL_QUADS);
             glVertex2i(left_boundary, howto_bottom);
             glVertex2i(right_boundary, howto_bottom);
             glVertex2i(right_boundary, howto_top);
             glVertex2i(left_boundary, howto_top);
             glEnd();
             glDisable(GL_BLEND);
        }
        else if (y >= settings_bottom && y <= settings_top) {
            // Hovering over Settings
            // Debug - uncomment to track hovering
            // printf("Hovering over Settings\n");

             // Hover over "Settings"
             glEnable(GL_BLEND);
             glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
             glColor4f(1.0f, 0.5f, 0.0f, 0.3f);  // Orange with transparency
             glBegin(GL_QUADS);
             glVertex2i(left_boundary, settings_bottom);
             glVertex2i(right_boundary, settings_bottom);
             glVertex2i(right_boundary, settings_top);
             glVertex2i(left_boundary, settings_top);
             glEnd();
             glDisable(GL_BLEND);
        }
    }
}
