//Name:Fenoon Alrowhani

//Work includes: 

//Pause Menu Buttons and strucure 
//Check for collisons
//Main page animations



//#include "GL.h"
#include "dcarter.h"
#include "fandrade.h"
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
void myRender();
void deliveryDetection();
//GameState gameState = PLAYING;
MoneySystem money; 

//function prototypes 
//void title_moto_physics(int frame, Animation animation[3]);
void show_fenoon(Rect*r);

using namespace std;         
using namespace std::chrono;  

//pop up messages 

int show_warning = 0;
int warning_timer = 0;







void show_fenoon(Rect*r)
{
    ggprint8b(r, 16, 0x00FFFF, "Fenoon");
}

Game_Button::Game_Button() : Button(200, 200) 
{
    this->set_text("Resume");       // Set the button's text
    this->set_color(252, 136,3);    // Set the button's color (RGB)
    this->set_pos(400, 400);         // Set the position of the button
    this->set_dims(100, 50);         // Set the dimensions of the button
}

void Game_Button::click(int x, int y)
 {
    if (this->is_inside(x, y)) { // Check if the click is inside the button
        //std::cout << "Resume Button Clicked!" << std::endl;
        gameState = PLAYING; // Change game state to PLAYING
    }
}
Restart_Button::Restart_Button() : Button(200, 200) 
{
    this->set_text("Restart");       // Set the button's text
    this->set_color(252, 136, 3);    // Set the button's color (RGB)
    this->set_pos(400, 200);         // Set the position of the button
    this->set_dims(100, 50);         // Set the dimensions of the button
}

//void Restart_Button::on_click() {
//    reset_game();  // Call reset function
//}

void reset_game() 
{
    std::cout << " Reset!" << std::endl;
    // gl.show=Image {"./images/game2.jpg"};
    gl.show = Image {"./images/game2.jpg"};
    // glutPostRedisplay();
    // renderScene();
}

//void Restart_Button::on_click() { 
//    reset_game();  // Call reset function
//}

void Restart_Button::click(int x, int y) 
{
    if (this->is_inside(x, y)) { // Check if the click is inside the button
       // std::cout << "RgjfkngnkdkButton Clicked!" << std::endl;
        //  Image show {"./images/game2.jpg"};
        reset_game();
    }
}
void drawPauseMenu() 
{
    Rect r;

    glColor4f(0.0, 0.0, 0.0, 1.0);// transparency
    glBegin(GL_QUADS);
    glVertex2f(-1, -1);
    glVertex2f(1, -1);
    glVertex2f(1, 1);
    glVertex2f(-1, 1);
    glEnd();

    
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


/*void title(Rect &r) 
{
    const char* sentence = "Pizza Delivery Simulator";

    r.bot = gl.yres - 20;

    // Iterate through each character in the sentence and print it with a delay
    for (int i = 0; sentence[i] != '\0'; i++) {
        ggprint8b(&r, 16, 0xFFFFFF00, "%c", sentence[i]);
        usleep(200000);  // Sleep for 0.2 seconds between characters
        r.left += 16;  // Move the text position to the right 
    }
}
*/
void title(Rect &r) 
{
    static int frame = 0;
    const char* sentence = "Pizza Delivery Simulator";
    int letters_to_show = frame / 80;

    r.bot = 400;
    r.left = 500 - ((int)strlen(sentence) * 9);

    char buffer[64] = {0};
    strncpy(buffer, sentence, letters_to_show);
    ggprint8b(&r, 62, 0xFFFFFF00, "%s", buffer);

    if (letters_to_show < (int)strlen(sentence)) {
        frame++;
    }
}




//collision positions defined 

void initGame()
 {
    gl.box.pos[0] = 5.0f;
    gl.box.pos[1] = 325.0f;

    gl.box2.width = 110;
    gl.box2.height = 80;

    gl.box2.pos[0] = 2.0f; 
    gl.box2.pos[1] = 575.0f;

    gl.box3.width = 110;
    gl.box3.height = 120;

    gl.box3.pos[0] = 2.0f; 
    gl.box3.pos[1] = 55.0f;

    gl.box4.width = 370.0;
    gl.box4.height = 90;

    gl.box4.pos[0] = 235.0f; 
    gl.box4.pos[1] = 565.0f;

    gl.box5.width = 380;
    gl.box5.height = 175;

    gl.box5.pos[0] = 235.0f; 
    gl.box5.pos[1] = 300.0f;

    gl.box6.width = 375;
    gl.box6.height = 20;

    gl.box6.pos[0] = 235.0f; 
    gl.box6.pos[1] = 160.0f;

    gl.box7.width = 110;
    gl.box7.height = 110;

    gl.box7.pos[0] = 365.0f; 
    gl.box7.pos[1] = 65.0f;

    gl.box8.width = 400;
    gl.box8.height = 95;

    gl.box8.pos[0] = 725.0f; 
    gl.box8.pos[1] = 555.0f;

    gl.box9.width = 230;
    gl.box9.height = 175;

    gl.box9.pos[0] = 725.0f; 
    gl.box9.pos[1] = 300.0f;

    gl.box10.width = 210;
    gl.box10.height = 100;

    gl.box10.pos[0] = 735.0f; 
    gl.box10.pos[1] = 55.0f;

    //delivery place postions starts here:///
    
   
    gl.box11.color[0] = 0.0f;
    gl.box11.color[1] = 0.0f;
    gl.box11.color[2] = 1.0f;


    gl.box12.color[0] = 0.0f;
    gl.box12.color[1] = 0.0f;
    gl.box12.color[2] = 1.0f;

    
    gl.box13.color[0] = 0.0f;
    gl.box13.color[1] = 0.0f;
    gl.box13.color[2] = 1.0f;


    gl.box14.color[0] = 0.0f;
    gl.box14.color[1] = 0.0f;
    gl.box14.color[2] = 1.0f;


    gl.box15.color[0] = 0.0f;
    gl.box15.color[1] = 0.0f;
    gl.box15.color[2] = 1.0f;

    
    gl.box16.color[0] = 0.0f;
    gl.box16.color[1] = 0.0f;
    gl.box16.color[2] = 1.0f;


    gl.box11.width = 55;
    gl.box11.height = 20;

    gl.box11.pos[0] =  382.0f; 
    gl.box11.pos[1] = 470.0f;


    gl.box12.width = 55;
    gl.box12.height = 20;

    gl.box12.pos[0] =  457.0f; 
    gl.box12.pos[1] = 470.0f;


    gl.box13.width = 55;
    gl.box13.height = 20;

    gl.box13.pos[0] =  520.0f; 
    gl.box13.pos[1] = 470.0f;


    gl.box14.width = 85;
    gl.box14.height = 30;

    gl.box14.pos[0] =  382.0f; 
    gl.box14.pos[1] = 150.0f;

    gl.box15.width = 85;
    gl.box15.height = 20;

    gl.box15.pos[0] =  750.0f; 
    gl.box15.pos[1] = 150.0f;

    gl.box16.width = 85;
    gl.box16.height = 20;

    gl.box16.pos[0] =  890.0f; 
    gl.box16.pos[1] = 150.0f;
    

}
void deductMoney(MoneySystem &money, float amount) {
    float current = money.getTotalMoney();
    float newTotal = current - amount;
    if (newTotal < 0.0f)
        newTotal = 0.0f;
    
    money.increaseRevenue(newTotal - current);
    money.cashInRevenue();
}

void addMoney(MoneySystem &money, float amount) {
    money.increaseRevenue(amount);
    money.cashInRevenue();
}


void physicsforCollision() 
{
    Motorcycle& moto = gl.bike;
    Box& box = gl.box;

    bool crashed =false; 

    static bool was_colliding = false;

    float motoX = moto.pos.x;
    float motoY = moto.pos.y;

    float boxLeft   = box.pos[0];
    float boxRight  = box.pos[0] + box.width;
    float boxBottom = box.pos[1];
    float boxTop    = box.pos[1] + box.height;

    // Point-based AABB collision
    if ((motoX >= boxLeft && motoX <= boxRight &&
        motoY >= boxBottom && motoY <= boxTop)&& !was_colliding) {
       // std::cout << "Collision detected!\n";
        show_warning = 1;
        warning_timer = 100;

        gl.bike.crash();
        crashed=true; 
        deductMoney(money, 5.0f);
  
  }
  else { 
    //ig gl .baike crash is no called 
    //crash direction is set to 0 
    crashed=false; 
    if (!crashed) { 
        gl.bike.crash_dir =0;
    }


  }
    if (gl.bike.pos.x >= gl.box2.pos[0] &&
        gl.bike.pos.x <= gl.box2.pos[0] + gl.box2.width &&
        gl.bike.pos.y >= gl.box2.pos[1] &&
        gl.bike.pos.y <= gl.box2.pos[1] + gl.box2.height) {
        
        //std::cout << "Collision with box 2!\n";
        show_warning = 1;
        warning_timer = 100;
        //gl.bike.velocity = 0.0;

        gl.bike.crash();
        crashed=true; 
        deductMoney(money, 5.0f);

        
    }
    else { 
        //ig gl .baike crash is no called 
        //crash direction is set to 0 
        crashed=false; 
        if (!crashed) { 
            gl.bike.crash_dir =0;
        }
    
    
      }
    if (gl.bike.pos.x >= gl.box3.pos[0] &&
        gl.bike.pos.x <= gl.box3.pos[0] + gl.box3.width &&
        gl.bike.pos.y >= gl.box3.pos[1] &&
        gl.bike.pos.y <= gl.box3.pos[1] + gl.box3.height) {
       // std::cout << "Collision with box 3!\n";
        show_warning = 1;
        warning_timer = 100;
       // gl.bike.velocity = 0.0;

       gl.bike.crash();
       crashed=true; 
       deductMoney(money, 5.0f);

       
    }
    else { 
        
        crashed=false; 
        if (!crashed) { 
            gl.bike.crash_dir =0;
        }
    
    
      }
    
    if (gl.bike.pos.x >= gl.box4.pos[0] &&
        gl.bike.pos.x <= gl.box4.pos[0] + gl.box4.width &&
        gl.bike.pos.y >= gl.box4.pos[1] &&
        gl.bike.pos.y <= gl.box4.pos[1] + gl.box4.height) {
       // std::cout << "Collision with box 4!\n";
        show_warning = 1;
        warning_timer = 100;
        

        gl.bike.crash();
        crashed=true; 
        deductMoney(money, 5.0f);

        }
        else { 
        
            crashed=false; 
            if (!crashed) { 
                gl.bike.crash_dir =0;
            }
        
        
          }

    
    if (gl.bike.pos.x >= gl.box5.pos[0] &&
        gl.bike.pos.x <= gl.box5.pos[0] + gl.box5.width &&
        gl.bike.pos.y >= gl.box5.pos[1] &&
        gl.bike.pos.y <= gl.box5.pos[1] + gl.box5.height) {
        //std::cout << "Collision with box 5!\n";
        show_warning = 1;
        warning_timer = 100;

        gl.bike.crash();
        crashed=true; 
        deductMoney(money, 5.0f);



    }
    else { 
        
        crashed=false; 
        if (!crashed) { 
            gl.bike.crash_dir =0;
        }
    
    
      }
    
    if (gl.bike.pos.x >= gl.box6.pos[0] &&
        gl.bike.pos.x <= gl.box6.pos[0] + gl.box6.width &&
        gl.bike.pos.y >= gl.box6.pos[1] &&
        gl.bike.pos.y <= gl.box6.pos[1] + gl.box6.height) {
       // std::cout << "Collision with box 6!\n";
        show_warning = 1;
        warning_timer = 100;

     gl.bike.crash();
     crashed=true; 
     deductMoney(money, 5.0f);


    }
    else { 
        
        crashed=false; 
        if (!crashed) { 
            gl.bike.crash_dir =0;
        }
    
    
      }
    
    if (gl.bike.pos.x >= gl.box7.pos[0] &&
        gl.bike.pos.x <= gl.box7.pos[0] + gl.box7.width &&
        gl.bike.pos.y >= gl.box7.pos[1] &&
        gl.bike.pos.y <= gl.box7.pos[1] + gl.box7.height) {
       // std::cout << "Collision with box 7!\n";
        show_warning = 1;
        warning_timer = 100;

    gl.bike.crash();
    crashed=true; 
    deductMoney(money, 5.0f);
    

    }
    else { 
        
        crashed=false; 
        if (!crashed) { 
            gl.bike.crash_dir =0;
        }
    
    
      }
    
    if (gl.bike.pos.x >= gl.box8.pos[0] &&
        gl.bike.pos.x <= gl.box8.pos[0] + gl.box8.width &&
        gl.bike.pos.y >= gl.box8.pos[1] &&
        gl.bike.pos.y <= gl.box8.pos[1] + gl.box8.height) {
        //std::cout << "Collision with box 8!\n";
        show_warning = 1;
        warning_timer = 100;

        gl.bike.crash();
        crashed=true; 
        deductMoney(money, 5.0f);
    
    }
    else { 
        
        crashed=false; 
        if (!crashed) { 
            gl.bike.crash_dir =0;
        }
    
    
      }
    
    if (gl.bike.pos.x >= gl.box9.pos[0] &&
        gl.bike.pos.x <= gl.box9.pos[0] + gl.box9.width &&
        gl.bike.pos.y >= gl.box9.pos[1] &&
        gl.bike.pos.y <= gl.box9.pos[1] + gl.box9.height) {
        //std::cout << "Collision with box 9!\n";
        show_warning = 1;
        warning_timer = 100;

        gl.bike.crash();
        crashed=true; 
        deductMoney(money, 5.0f);


    
    }
    else { 
        
        crashed=false; 
        if (!crashed) { 
        
            gl.bike.crash_dir =0;
        }
    
    
      }
    
    if (gl.bike.pos.x >= gl.box10.pos[0] &&
        gl.bike.pos.x <= gl.box10.pos[0] + gl.box10.width &&
        gl.bike.pos.y >= gl.box10.pos[1] &&
        gl.bike.pos.y <= gl.box10.pos[1] + gl.box10.height) {
        //std::cout << "Collision with box 10!\n";
        show_warning = 1;
        warning_timer = 100;

        gl.bike.crash();
        crashed=true; 
        deductMoney(money, 5.0f);
     
    }
    else { 
        
        crashed=false; 
        if (!crashed) { 
            gl.bike.crash_dir =0;
        }
    
    
      }

    //delivery places collision starts here: 

    
}   

void deliveryDetection() 
{
    float motoX = gl.bike.pos.x;
    float motoY = gl.bike.pos.y;

    if (motoX >= gl.box11.pos[0] &&
        motoX <= gl.box11.pos[0] + gl.box11.width &&
        motoY >= gl.box11.pos[1] &&
        motoY <= gl.box11.pos[1] + gl.box11.height) {
       // std::cout << "Delivery at box11!\n";
       addMoney(money, 10.0f);

    }

    if (motoX >= gl.box12.pos[0] &&
        motoX <= gl.box12.pos[0] + gl.box12.width &&
        motoY >= gl.box12.pos[1] &&
        motoY <= gl.box12.pos[1] + gl.box12.height) {
        //std::cout << "Delivery at box12!\n";
        addMoney(money, 10.0f);

    }

    if (motoX >= gl.box13.pos[0] &&
        motoX <= gl.box13.pos[0] + gl.box13.width &&
        motoY >= gl.box13.pos[1] &&
        motoY <= gl.box13.pos[1] + gl.box13.height) {
        std::cout << "Delivery at box13!\n";
        addMoney(money, 10.0f);

    }

    if (motoX >= gl.box14.pos[0] &&
        motoX <= gl.box14.pos[0] + gl.box14.width &&
        motoY >= gl.box14.pos[1] &&
        motoY <= gl.box14.pos[1] + gl.box14.height) {
       // std::cout << "Delivery at box14!\n";
        addMoney(money, 10.0f);

    }

    if (motoX >= gl.box15.pos[0] &&
        motoX <= gl.box15.pos[0] + gl.box15.width &&
        motoY >= gl.box15.pos[1] &&
        motoY <= gl.box15.pos[1] + gl.box15.height) {
        //std::cout << "Delivery at box15!\n";
        addMoney(money, 10.0f);

    }


    if (motoX >= gl.box16.pos[0] &&
        motoX <= gl.box16.pos[0] + gl.box16.width &&
        motoY >= gl.box16.pos[1] &&
        motoY <= gl.box16.pos[1] + gl.box16.height) {
       // std::cout << "Delivery at box16!\n";
       addMoney(money, 10.0f);

    }
}



void myRender()
{
    Rect r; 

    gl.box.render();
    gl.box2.render();
    gl.box3.render();
    gl.box4.render();
    gl.box5.render();
    gl.box6.render();
    gl.box7.render();
    gl.box8.render();
    gl.box9.render();
    gl.box10.render();
    gl.box11.render();
    gl.box12.render();
    gl.box13.render();
    gl.box14.render();
    gl.box15.render();
    gl.box16.render();


    if (show_warning) {
        glPushMatrix();
        glLoadIdentity();
        glColor3f(0.0f, 0.0f, 0.0f); // Black color
        glBegin(GL_QUADS);
            glVertex2f(gl.xres/2 - 100, gl.yres/2 + 20);
            glVertex2f(gl.xres/2 + 100, gl.yres/2 + 20);
            glVertex2f(gl.xres/2 + 100, gl.yres/2 - 20);
            glVertex2f(gl.xres/2 - 100, gl.yres/2 - 20);
        glEnd();
        glPopMatrix();

        r.left = gl.xres/2 - 50;
        r.bot = gl.yres/2;
        r.center = 0;
        ggprint16(&r, 1000, 0xffff00ff, "WATCH OUT!");
    }

    if (warning_timer > 0) {
        warning_timer--;
        if (warning_timer == 0) {
            show_warning = 0;
        }
    }
}

void Motorcycle::crash() { 


    if (crash_dir == 0) {
        velocity.set(0.0);
    }


    if (velocity.get() > 0) {
        crash_dir = 1;  // Moving "forward"
    } else {
        crash_dir = -1; // Moving "backward"
    }

   
//if (!physicsforCollision()) {
  
//}


}
//crashdir -1 or 1; 

    //cal g.bike.crash(); 


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
