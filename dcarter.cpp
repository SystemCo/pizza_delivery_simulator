#include "headers.h"
#include <iostream>
#include <cmath>
#define PI 3.141592653589793
#define TO_RAD(x) ((x+90) / 360.0f) * PI * 2.0 // from asteroids framework
#define SPEED 4

/** This is the global variable for the whole project. Declared in asteroids.cpp */
extern Global gl;

void show_david(Rect* r)
{
    ggprint8b(r, 16, 0x00ff00ff, "David - The Sweaty One");
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

Entity::Entity(float pos_x, float pos_y, float scale, float angle, const char infile[]) : Image(infile)
{
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->scale = scale;
    this->angle = angle;
    init_gl();
}
Entity::Entity(const char infile[]) : Image(infile)
{
    pos_x = 0;
    pos_y = 0;
    scale = 50.0f;
    angle = 0;
    init_gl();
}
void Entity::render()
{
    this->show(scale, pos_x, pos_y, angle, flipped);
}

Motorcycle::Motorcycle() : Entity(250, 250, 30.0, 0.0, "./images/motorcycle.gif")
{
    //fflush(stdout);
    pedal = Neutral;

    //setup_opengl(this.img);
    // you can't set up opengl anywhere but main.
    // opengl setup uses weird implicit global variables that go out of scope
    // unless specifically initialized within the main initialization function.
}

//void Motorcycle::render()
//{
    //render();
//}
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
    float turn_speed = 2.0f;
    float vel = velocity.get();
    switch (pedal) {
        case Forward:
            velocity.set(vel+0.1);
            break;
        case Neutral:
            velocity.set(vel*0.99);
            break;
        case Backward:
            velocity.set(vel-0.1);
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
        angle -= 360;
    float rad = TO_RAD(angle);
    float delta_x = vel * SPEED * std::cos(rad);
    pos_x += delta_x;
    float delta_y = vel * SPEED * std::sin(rad);
    pos_y += delta_y;
    if (pos_x < 0)
        pos_x = gl.xres;
    if (pos_x > gl.xres)
        pos_x = 0;
    if (pos_y < 0)
        pos_y = gl.yres;
    if (pos_y > gl.yres)
        pos_y = 0;
}

//void Motorcycle::init_gl()
//{
    //init_gl();
//}

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

// ****************** Contributions to shared ***********************
// I set up the title_moto_physics animation framework as seen below.
// The animation itself was a group effort (I hope)
// Including it here becuase I'm particularly proud 
// of it's readablity and format  
/**
void title_moto_physics(int frame)
{
    int* pos_x = &gl.moto_side->pos_x;
    int* pos_y = &gl.moto_side->pos_y;
    int* flipped = &gl.moto_side->flipped;
    float* angle = &gl.moto_side->angle;
    // Deviation from style. 
    // I feel it's appropriate given the repeat code,
    // to help emphasize the important elements of the code block.
    if       (frame < 100) {
                                *pos_x  += 10;
                                *pos_y  += 10;
                                *angle  += 0;
                                *flipped = false;
    }else if (frame < 200) {
                                *pos_x  += -10;
                                *pos_y  += 0;
                                *angle  += 0;
                                *flipped = true;
    }else if (frame < 300) {
                                *pos_x  += 5;
                                *pos_y  += 0;
                                *angle  += 0;
                                *flipped = false;
    }else if (frame < 400) {
                                *pos_x  += 0;
                                *pos_y  += 0;
                                *angle  += 0.1;
                                *flipped = *flipped;
    }else if (frame < 500) {
                                *pos_x  +=  -3;
                                *pos_y  +=  4;
                                *angle  +=  0;
                                *flipped = false;
    }
    // Always jump edges. May not want to do this in the full animation
    if (*pos_x < 0)
        *pos_x += gl.xres;
    *pos_x %= gl.xres;
    if (*pos_y < 0)
        *pos_y += gl.xres;
    *pos_y %= gl.yres;
}
*/


