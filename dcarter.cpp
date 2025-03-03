// Personal file of David Carter
// Third
// Contains important implementation for:
//      Image,
//      Entity,
//      Motorcycle
// Classes
//
//#include "headers.h"
#include "shared.h"
#include "dcarter.h"

#include <iostream>
#include <cmath>
#include <cstring>

#define PI 3.141592653589793
#define TO_RAD(x) ((x+90) / 360.0f) * PI * 2.0 // from asteroids framework
#define SPEED 4 // Moto Linear Speed

/* 
 **  This is the global variable for the whole project. 
 **  Declared in asteroids.cpp
 */
extern Global gl;
//nothing

//Non-Class function prototypes
int resolution_scale(int width, int height);
int resolution_scale(Image* img);
void show_david(Rect* r);

void show_david(Rect* r)
{
    ggprint8b(r, 16, 0xf3ab00, "David - The Sweaty One");
}

void Image::show(float wid, int pos_x, int pos_y, float angle)
{
    this->show(wid, pos_x, pos_y, angle, 0);
}

Percent::Percent()
{
    this->val = 0;
}

Percent::Percent(float val)
{
    this->val = val;
}

void Percent::set(float val)
{
    this->val = val;
    if (val > 1)
        this->val = 1;
    if (val < -1)
        this->val = -1;
}

float Percent::get()
{
    return this->val;
}

Entity::Entity(float pos_x, float pos_y, float scale, 
        float angle, const char infile[]) : Image(infile)
{
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->scale = scale;
    this->angle = angle;
    //init_gl();
}
Entity::Entity(const char infile[]) : Image(infile)
{
    pos_x = 0;
    pos_y = 0;
    scale = 50.0f;
    angle = 0;
    //init_gl();
}
void Entity::render()
{
    this->show(scale, pos_x, pos_y, angle, flipped);
}

#define MOTO_SIZE 75
// Calling Entity's constructor sets all shared variables 
// and calls Image's constructor.
Motorcycle::Motorcycle() : 
    Entity(250, 250, MOTO_SIZE, 0.0, "./images/motorcycle.gif")
{
    // Everything but pedal can be left default or set by Entity constructor
    pedal = Neutral;
}

// The sea of boilerplate. It's just to make other functions less verbose. 
void Motorcycle::set_pedal(Pedal pedal)
{
    this->pedal = pedal;
}
void Motorcycle::set_left()
{
    this->left = true;
}
void Motorcycle::unleft()
{
    this->left = false;
}
void Motorcycle::set_right()
{
    this->right = true;
}
void Motorcycle::unright()
{
    this->right = false;
}

// Go straight when not pressing buttons or when pressing L & R buttons
void Motorcycle::set_turn()
{
    if ( this->left && !this->right)
        this->turn = Left;
    else if ( this->right && !this->left)
        this->turn = Right;
    else
        this->turn = Straight;
}

void Motorcycle::move()
{
    // Maybe this should go in the header file?
    const float turn_speed = 2.0f;
    const float acceleration = 0.1;
    const float vel = velocity.get();
    switch (pedal) { // Per linux
    case Forward:
        velocity.set(vel + acceleration);
        break;
    case Neutral:
        velocity.set(vel*0.99);
        break;
    case Backward:
        velocity.set(vel - acceleration);
        break;
    }
    this->set_turn();
    switch (turn) {
    case Straight:
        break;
    case Left:
        angle += turn_speed;
        break;
    case Right:
        angle -= turn_speed;
        break;
    }
    while (angle < 0)
        angle += 360;
    while (angle > 0)
        angle -= 360; // no integer overflows
    const float rad = TO_RAD(angle);
    const float delta_x = vel * SPEED * std::cos(rad);
    pos_x += delta_x;
    const float delta_y = vel * SPEED * std::sin(rad);
    pos_y += delta_y;
    // Motorcycle jumps on edge. May be changed later. 
    if (pos_x < 0) // Wish I could make this a switch statement...
        pos_x = gl.xres;
    if (pos_x > gl.xres)
        pos_x = 0;
    if (pos_y < 0)
        pos_y = gl.yres;
    if (pos_y > gl.yres)
        pos_y = 0;
}

int resolution_scale(int width, int height)
{
    float img_proportion = width / height;
    float resolution_proportion = gl.xres / gl.yres;
    int output = 0;
    if (resolution_proportion > img_proportion) {
        output = img_proportion * gl.xres/2;
    } else {
        output = img_proportion * gl.yres;
    }
    return output;
}

int resolution_scale(Image* img)
{
    return resolution_scale(img->width, img->height);
}

// *********** Animation for Title sceen *******************
// This setup may be used for animations more generally.
// For now, the particulars of the animation and images are hard coded.
// ********************************************************
void Entity::jump_edges()
{
    while (pos_x < 0)
        pos_x += gl.xres;
    while (pos_x > gl.xres)
        pos_x -= gl.xres;
    while (pos_y < 0)
        pos_y += gl.xres;
    while (pos_y > gl.yres)
        pos_y -= gl.yres;
}

void Entity::animate(int frame, Animation animations[],
                                    int section_count, int total_frames)
{
    const int frame_num = total_frames / section_count;
    for (int i = 0; i < section_count; i++) {
        if (frame >= i*frame_num && frame < (i+1)*frame_num) {
            pos_x  += animations[i].delta_x;
            pos_y  += animations[i].delta_y;
            angle  += animations[i].delta_angle;
            flipped = animations[i].flipped;
        }
    }
    
    // Always jump edges. May not want to do this in the full animation
    this->jump_edges();
}
void title_moto_physics(int frame, Animation animations[5])
{
    const int total_frames = 500;
    const int section_count = 5;
    gl.moto_side->animate(frame, animations, section_count, total_frames);
}


void title_render()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    const int wid = resolution_scale(&gl.background);
    gl.background.show(wid, gl.xres/2, gl.yres/2, 0.0f);
    //int flipped = false;
    gl.moto_side->render();
}

// ***************** Mouse clickable Buttons *************************
//

void Button::write_text()
{
    Rect r;
    const int text_height = 5;
    const int color = 0x000000;
    r.bot = pos[1] - text_height;
    r.left = pos[0];
    ggprint8b(&r, 16, color, text);
}

// All that needs to be called to render. Writes text as well.
void Button::render()
{
    glPushMatrix();
    glColor3ub(color[0], color[1], color[2]);
    glTranslatef(pos[0], pos[1], 0.0f);
    glBegin(GL_QUADS);
    const int width = pos[0];
    const int height = pos[1];
    glVertex2f(-width, -height);
    glVertex2f(-width,  height);
    glVertex2f( width,  height);
    glVertex2f( width, -height);
    glEnd();
    glPopMatrix();
    write_text();
}

int Button::is_inside(int x, int y)
{
return   y <= (pos[1] + dims[1]) &&
         y >= (pos[1] - dims[1]) &&
         x <= (pos[0] + dims[0]) &&
         x >= (pos[0] - dims[0]);
}

void Button::set_text(const char new_text[])
{
    strcpy(text, new_text);
}
void Button::click(int x, int y)
{
    if (is_inside(x, y))
        printf("click!\n");
}

// ****************** Contributions to shared ***********************

