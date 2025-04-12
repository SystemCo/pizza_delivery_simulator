//Name:Fenoon Alrowhani

//Work includes: 

//Pause Menu Buttons and strucure 
//Check for collisons
//Main page animations



//#include "GL.h"
#include "dcarter.h"
#include <iostream>
#include "falrowhani.h"
#include "shared.h" 
#include <stdio.h> 
//#include <graphics.h> 
//#include <dos.h> 
#include <thread>
#include <chrono>
#include <cstring>
#include <algorithm>
#include <GL/glut.h>
#include <unistd.h>
#include <cmath>

extern Global gl; 
#define GRAVITY 9.8f 



//function protypes
void drawPauseMenu();
void Game_Button();
void Restart_Button();
void initGame();
void physicsforCollision();
void know();
//GameState gameState = PLAYING;

//function prototypes 
//void title_moto_physics(int frame, Animation animation[3]);
void show_fenoon(Rect*r);

using namespace std;         
using namespace std::chrono;  



void show_fenoon(Rect*r)
{
    ggprint8b(r, 16, 0x00FFFF, "Fenoon");
}

Game_Button::Game_Button() : Button(200, 200) {
    this->set_text("Resume");       // Set the button's text
    this->set_color(252, 136,3);    // Set the button's color (RGB)
    this->set_pos(200, 400);         // Set the position of the button
    this->set_dims(100, 50);         // Set the dimensions of the button
}

void Game_Button::click(int x, int y) {
    if (this->is_inside(x, y)) { // Check if the click is inside the button
        std::cout << "Resume Button Clicked!" << std::endl;
        gameState = PLAYING; // Change game state to PLAYING
    }
}
Restart_Button::Restart_Button() : Button(200, 200) {
    this->set_text("Restart");       // Set the button's text
    this->set_color(252, 136, 3);    // Set the button's color (RGB)
    this->set_pos(200, 200);         // Set the position of the button
    this->set_dims(100, 50);         // Set the dimensions of the button
}

//void Restart_Button::on_click() {
//    reset_game();  // Call reset function
//}

void reset_game() {
    std::cout << " Reset!" << std::endl;
    // gl.show=Image {"./images/game2.jpg"};
    gl.show = Image {"./images/game2.jpg"};
    // glutPostRedisplay();
    // renderScene();
}

//void Restart_Button::on_click() { 
//    reset_game();  // Call reset function
//}

void Restart_Button::click(int x, int y) {
    if (this->is_inside(x, y)) { // Check if the click is inside the button
        std::cout << "RgjfkngnkdkButton Clicked!" << std::endl;
        //  Image show {"./images/game2.jpg"};
        reset_game();
    }
}
void drawPauseMenu() {
    Rect r;

    glColor4f(0.0, 0.0, 0.0, 1.0);// transparency
    glBegin(GL_QUADS);
    glVertex2f(-1, -1);
    glVertex2f(1, -1);
    glVertex2f(1, 1);
    glVertex2f(-1, 1);
    glEnd();

    // Display menu options
    r.bot = gl.yres / 2 + 40;
    r.left = gl.xres / 2 - 80;
    r.center = 1;

    glColor3f(1.0, 1.0, 1.0); 
  //  void Game_Button();
  //  ggprint8b(&r, 16, 0xFFFFFF00, "Game Paused: Press Esc to continue");
    r.bot -= 30;
    gl.pause_button.render();
    gl.restart.render();
}
extern Global gl; 

void title_moto_physics(int frame, Animation animation[5]);

//extern Global gl; 


// motorcyle animation for entry in game 
//original function from Dcarter 
//modified by Fenoon: me 


void title_physics()
{
    static int frame = 0;
 Animation  animations[3];
    animations[0] = {2, 0, 0, 0};
    animations[1] = {2, 5, 25, 0};
    animations[2] = {0, 5, 0, 0};

   // title_moto_physics(frame, animations);
    
    const int totalFrames = 500; 
    const int section_count = 3;     

    // calling animate function direcly 
    gl.moto_side->animate(frame, animations, section_count, totalFrames);
    frame += 1;
    frame %= totalFrames;

}

//currently not working 


void title(Rect &r) {
    const char* sentence = "Pizza Delivery Simulator";

    r.bot = gl.yres - 20;

    // Iterate through each character in the sentence and print it with a delay
    for (int i = 0; sentence[i] != '\0'; i++) {
        ggprint8b(&r, 16, 0xFFFFFF00, "%c", sentence[i]);
        usleep(200000);  // Sleep for 0.2 seconds between characters
        r.left += 16;  // Move the text position to the right 
    }
}
//collision positions defined 

void initGame() {
    gl.box.pos[0] = 20.0f;
    gl.box.pos[1] = 350.0f;

    gl.box2.width = 200;
    gl.box2.height = 175;

    gl.box2.pos[0] = 20.0f; 
    gl.box2.pos[1] = 700.0f;

    gl.box3.width = 175;
    gl.box3.height = 175;

    gl.box3.pos[0] = 20.0f; 
    gl.box3.pos[1] = 5.0f;

    gl.box4.width = 575;
    gl.box4.height = 175;

    gl.box4.pos[0] = 345.0f; 
    gl.box4.pos[1] = 700.0f;

    gl.box5.width = 575;
    gl.box5.height = 280;

    gl.box5.pos[0] = 345.0f; 
    gl.box5.pos[1] = 350.0f;

    gl.box6.width = 575;
    gl.box6.height = 25;

    gl.box6.pos[0] = 345.0f; 
    gl.box6.pos[1] = 150.0f;

    gl.box7.width = 185;
    gl.box7.height = 165;

    gl.box7.pos[0] = 550.0f; 
    gl.box7.pos[1] = 10.0f;

    gl.box8.width = 400;
    gl.box8.height = 175;

    gl.box8.pos[0] = 1050.0f; 
    gl.box8.pos[1] = 700.0f;

    gl.box9.width = 400;
    gl.box9.height = 300;

    gl.box9.pos[0] = 1050.0f; 
    gl.box9.pos[1] = 325.0f;

    gl.box10.width = 375;
    gl.box10.height = 175;

    gl.box10.pos[0] = 1050.0f; 
    gl.box10.pos[1] = 5.0f;

    //gl.box3.pos[0] = 500.0f; 
    //gl.box3.pos[1] = 150.0f;

}

//checking for collison through all positons defined 


void physicsforCollision() {
    Motorcycle& moto = gl.bike;
    Box& box = gl.box;

    float motoX = moto.pos.x;
    float motoY = moto.pos.y;

    float boxLeft   = box.pos[0];
    float boxRight  = box.pos[0] + box.width;
    float boxBottom = box.pos[1];
    float boxTop    = box.pos[1] + box.height;

    // Point-based AABB collision
    if (motoX >= boxLeft && motoX <= boxRight &&
        motoY >= boxBottom && motoY <= boxTop) {
        std::cout << "Collision detected!\n";
    }

    if (gl.bike.pos.x >= gl.box2.pos[0] &&
        gl.bike.pos.x <= gl.box2.pos[0] + gl.box2.width &&
        gl.bike.pos.y >= gl.box2.pos[1] &&
        gl.bike.pos.y <= gl.box2.pos[1] + gl.box2.height) {
        
        std::cout << "Collision with box 2!\n";
    }
    if (gl.bike.pos.x >= gl.box3.pos[0] &&
        gl.bike.pos.x <= gl.box3.pos[0] + gl.box3.width &&
        gl.bike.pos.y >= gl.box3.pos[1] &&
        gl.bike.pos.y <= gl.box3.pos[1] + gl.box3.height) {
        std::cout << "Collision with box 3!\n";
    }
    
    if (gl.bike.pos.x >= gl.box4.pos[0] &&
        gl.bike.pos.x <= gl.box4.pos[0] + gl.box4.width &&
        gl.bike.pos.y >= gl.box4.pos[1] &&
        gl.bike.pos.y <= gl.box4.pos[1] + gl.box4.height) {
        std::cout << "Collision with box 4!\n";
    }
    
    if (gl.bike.pos.x >= gl.box5.pos[0] &&
        gl.bike.pos.x <= gl.box5.pos[0] + gl.box5.width &&
        gl.bike.pos.y >= gl.box5.pos[1] &&
        gl.bike.pos.y <= gl.box5.pos[1] + gl.box5.height) {
        std::cout << "Collision with box 5!\n";
    }
    
    if (gl.bike.pos.x >= gl.box6.pos[0] &&
        gl.bike.pos.x <= gl.box6.pos[0] + gl.box6.width &&
        gl.bike.pos.y >= gl.box6.pos[1] &&
        gl.bike.pos.y <= gl.box6.pos[1] + gl.box6.height) {
        std::cout << "Collision with box 6!\n";
    }
    
    if (gl.bike.pos.x >= gl.box7.pos[0] &&
        gl.bike.pos.x <= gl.box7.pos[0] + gl.box7.width &&
        gl.bike.pos.y >= gl.box7.pos[1] &&
        gl.bike.pos.y <= gl.box7.pos[1] + gl.box7.height) {
        std::cout << "Collision with box 7!\n";
    }
    
    if (gl.bike.pos.x >= gl.box8.pos[0] &&
        gl.bike.pos.x <= gl.box8.pos[0] + gl.box8.width &&
        gl.bike.pos.y >= gl.box8.pos[1] &&
        gl.bike.pos.y <= gl.box8.pos[1] + gl.box8.height) {
        std::cout << "Collision with box 8!\n";
    }
    
    if (gl.bike.pos.x >= gl.box9.pos[0] &&
        gl.bike.pos.x <= gl.box9.pos[0] + gl.box9.width &&
        gl.bike.pos.y >= gl.box9.pos[1] &&
        gl.bike.pos.y <= gl.box9.pos[1] + gl.box9.height) {
        std::cout << "Collision with box 9!\n";
    }
    
    if (gl.bike.pos.x >= gl.box10.pos[0] &&
        gl.bike.pos.x <= gl.box10.pos[0] + gl.box10.width &&
        gl.bike.pos.y >= gl.box10.pos[1] &&
        gl.bike.pos.y <= gl.box10.pos[1] + gl.box10.height) {
        std::cout << "Collision with box 10!\n";
    }
    
}   

/*
void title_physics()
{
    static int frame = 0;
    Animation  animations[5];
    animations[0] = {5, 0, 0, 0};
    animations[1] = {2, 5, 30, 0};
    animations[2] = {5, 0, 0, 0};
    for (int i = 0; i<5; i++)
        animations[i] = {1, 1, 0, 0};
    title_moto_physics(frame, animations);

    frame += 1;
    frame %= 500;
}*/
