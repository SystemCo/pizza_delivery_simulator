//Name:Fenoon
//lab4
//working on animation
//
//original code from Dcarter 
//modified by me 
//
//#include "GL.h"
#include "dcarter.h"
#include <iostream>
#include "falrowhani.h"
#include "shared.h" 
//#include "global.h"

extern Global gl; 


void drawPauseMenu();

//GameState gameState = PLAYING;

//function prototypes 
//void title_moto_physics(int frame, Animation animation[3]);
void show_fenoon(Rect*r);

void show_fenoon(Rect*r)
{
    ggprint8b(r, 16, 0x00FFFF, "Fenoon");
}

void drawPauseMenu() {
    Rect r;
        
    // Semi-transparent black overlay
    glColor4f(0.0, 0.0, 0.0, 0.5); // Black with 50% transparency
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
    
    glColor3f(1.0, 1.0, 1.0); // White text
    ggprint8b(&r, 16, 0xFFFFFF00, "Game Paused: Press Esc to continue");
    r.bot -= 30;
}


//extern Global gl; 

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

/*
class Box {

    public:
        int width;
        int height;
        float pos[2];
        float prev[2];
        float vel[2];
        float force[2];
        float color [3];
        char text[100];
        Box () {
            width = 100;
            height = 50;
            //adding this to add more boxes
            //  pos[0] = x;
            // pos[1] = y;
            //         pos[0] = pos[1] = 0.0f;
            //will declare laterso it can be in the middle
            vel[0]= vel[1]= 0.0f;
            // color [0] = rnd();
            color [0] = .3f;
            color [1] = .7f;
            color [2] = .3f;

        }
        Box (int w, int h) {
          Box();
          width =w;
          height=h;
          }
        Box(int w, int h) {
            width = w;
            height = h;
            //pos[0] = x;
            // pos[1] = y;
            vel[0] = vel[1] = 0.0f;
            color[0] = 0.3f;
            color[1] = 0.7f;
            color[2] = 0.3f;
        }
};
//Box box;
Box particle (4,4);
Box particles [MAX_PARTICLES];
int n =0;
Box box[NUM_BOXES];
*/

//class mainMenu{ 
//global: 
 //   int button; 
   // int text; 
//private: 



//}

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
