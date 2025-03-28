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
#include <stdio.h> 
//#include <graphics.h> 
//#include <dos.h> 
#include <thread>
#include <chrono>
#include <cstring>
extern Global gl; 


void drawPauseMenu();
void Game_Button();
//GameState gameState = PLAYING;

//function prototypes 
//void title_moto_physics(int frame, Animation animation[3]);
void show_fenoon(Rect*r);

using namespace std;          // To avoid using 'std::' every time
using namespace std::chrono;  // For time-related functions


void show_fenoon(Rect*r)
{
    ggprint8b(r, 16, 0x00FFFF, "Fenoon");
}

Game_Button::Game_Button() : Button(200, 200) {
    this->set_text("Resume");       // Set the button's text
    this->set_color(252, 136,3);    // Set the button's color (RGB)
    this->set_pos(200, 300);         // Set the position of the button
    this->set_dims(200, 50);         // Set the dimensions of the button
}

void Game_Button::click(int x, int y) {
    if (this->is_inside(x, y)) { // Check if the click is inside the button
        std::cout << "Resume Button Clicked!" << std::endl;
        gameState = PLAYING; // Change game state to PLAYING
    }
}

/*
this->set_on_click([]() {
        resume_game(); // Call the function to resume the game
    });
}

void resume_game() {
    // Logic to resume the game
    isGamePaused = false; // Assuming you have a boolean flag for pause state
}
*/

/*typedef struct my_rect {
    int left, right, top, bot, centerx, centery;
} MyRect;

typedef struct my_button {
    MyRects mor r;
    char text[32];
    int over;
    int down;
    int click;
    float color[3];
    float dcolor[3];
    unsigned int text_color;
} MyButton;
*/
/*
typedef struct t_button {
    Rect r;
    char text[32];
    int over;
    int down;
    int click;
    float color[3];
    float dcolor[3];
    unsigned int text_color;
} Button;
*/
/*Button pausebutton[2];
int nbuttons = 2;
int paused = 0;

void createButtons() {
    pausebutton[0] = (Button){{100, 100, 200, 150, 150, 125}, "Button 1", 0, 0, 0, {0.6f, 0.6f, 0.6f}, {0.3f, 0.3f, 0.3f}, 0xFFFFFF};
    pausebutton[1] = (Button){{300, 100, 400, 150, 350, 125}, "Resume", 0, 0, 0, {0.6f, 0.6f, 0.6f}, {0.3f, 0.3f, 0.3f}, 0xFFFFFF};
}

void drawButtons() {
    for (int i = 0; i < 2; i++) {
        Button *b = &pausebutton[i];
        if (b->over) {
            glColor3f(1.0f, 0.0f, 0.0f);
            glLineWidth(2);
            glBegin(GL_LINE_LOOP);
                glVertex2i(b->r.left-2,  b->r.bot-2);
                glVertex2i(b->r.left-2,  b->r.top+2);
                glVertex2i(b->r.right+2, b->r.top+2);
                glVertex2i(b->r.right+2, b->r.bot-2);
                glVertex2i(b->r.left-2,  b->r.bot-2);
            glEnd();
            glLineWidth(1);
        }
        glColor3fv(b->down ? b->dcolor : b->color);
        glBegin(GL_QUADS);
            glVertex2i(b->r.left,  b->r.bot);
            glVertex2i(b->r.left,  b->r.top);
            glVertex2i(b->r.right, b->r.top);
            glVertex2i(b->r.right, b->r.bot);
        glEnd();
    }
}

void checkButtonHover(int x, int y) {
    for (int i = 0; i < 2; i++) {
        pausebutton[i].over = (x >= pausebutton[i].r.left && x <= pausebutton[i].r.right && y >= pausebutton[i].r.bot && y <= pausebutton[i].r.top);
    }
}

void handleMouseClick(int x, int y, int buttonPressed) {
    for (int i = 0; i < 2; i++) {
        if (pausebutton[i].over) {
            pausebutton[i].down = (buttonPressed == 1);
            if (strcmp(pausebutton[i].text, "Resume") == 0) {
                paused = 0; // Unpause the game
            }
            break;
        }
    }
}*/

/*namespace textAnimation {

    void textMoveRight() {
        string text = "Hello, world!";
        int position = 0;

        while (position < 50) {
            cout << "\033[2J\033[1;1H";  // Clear the screen
            cout << string(position, ' ') << text << flush;  // Move text
            this_thread::sleep_for(milliseconds(100));  // Delay
            position++;  // Move the text to the right
        }
    }

}*/
/*
void textAnimation()
{ 
    int gdriver =DETECT, gmode; 

    initgraph(&gdriver, &gmode, "jk"); 


    while (!kbhit()) 
    { 
        delay(70); 
        settextstyle(3,0,7); 
        cleardevice(); 
        outtextxy(50,250, "R'); 
            delay(200); 
        
        cleardevice(); 
        outtextxy(50, 250, "r" ); 
        setcolor(YELLOW); 
        outtextxy(100, 250, "t"); 
        setcolor(BLUE); 
        outtextxy(150, 250, "s"); 
        delay(600); 
    }*/
/*
Game_Button::Game_Button() : Button(200, 200)
 {
     this->set_text("hellor!");
     this->set_color(0, 200, 200);
     this->set_pos(300, 300);
     this->set_dims(200, 50);
 }*/ 
/*
void Game_Button::draw() {
    glColor3ub(this->r, this->g, this->b); // Set button color
    glBegin(GL_QUADS);
    glVertex2i(this->x, this->y);
    glVertex2i(this->x + this->width, this->y);
    glVertex2i(this->x + this->width, this->y + this->height);
    glVertex2i(this->x, this->y + this->height);
    glEnd();

    // Draw button text
    Rect r;
    r.bot = this->y + (this->height / 2) - 8;
    r.left = this->x + (this->width / 2) - 20;
    ggprint8b(&r, 16, 0xFFFFFF00, this->text.c_str());
}*/
/*
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


*/
extern Global gl; 

void title_moto_physics(int frame, Animation animation[5]);

void title_physics()
{
    static int frame = 0;
 Animation  animations[3];
    animations[0] = {2, 0, 0, 0};
    animations[1] = {2, 5, 25, 0};
    animations[2] = {2, 0, 0, 0};

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
