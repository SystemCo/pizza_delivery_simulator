#include "headers.h"
#include <iostream>
#include <cmath>
#define PI 3.141592653589793
#define TO_RAD(x) ((x+90) / 360.0f) * PI * 2.0
#define SPEED 4

/** This is the global variable for the whole project. Declared in asteroids.cpp */
extern Global gl;

void show_david(Rect* r)
{
    ggprint8b(r, 16, 0x00ff00ff, "David - The Sweaty One");
}

void Image::show(float wid, int pos_x, int pos_y, float angle, int flipped)
{
    Image* img = this;
    float height = wid * img->height/img->width;
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslatef(pos_x, pos_y, 0.0f);

    glBindTexture(GL_TEXTURE_2D, img->texture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);

    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    
    glBegin(GL_QUADS);
    if (flipped) {
        glTexCoord2i(0, 1); glVertex2i(-wid,-height);
        glTexCoord2i(0, 0); glVertex2i(-wid, height);
        glTexCoord2i(1, 0); glVertex2i( wid, height);
        glTexCoord2i(1, 1); glVertex2i( wid,-height);
    } else {
        //glTexCoord2f(1.0f, 1.0f); glVertex2i(-wid,-height);
        glTexCoord2i(1, 1); glVertex2i(-wid,-height);
        glTexCoord2i(1, 0); glVertex2i(-wid, height);
        glTexCoord2i(0, 0); glVertex2i( wid, height);
        glTexCoord2i(0, 1); glVertex2i( wid,-height);
    }
    glEnd();
    glPopMatrix();
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

Entity::Entity(int pos_x, int pos_y, float scale, float angle, const char infile[])
{
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->scale = scale;
    this->angle = angle;
    img = new Image(infile);
    img->init_gl();
}
Entity::Entity(const char infile[])
{
    pos_x = 0;
    pos_y = 0;
    scale = 50.0f;
    angle - 0;
    img = new Image(infile);
    img->init_gl();
}
void Entity::render(int flipped)
{
    img->show(scale, pos_x, pos_y, angle, flipped);
}
void Entity::render()
{
    img->show(scale, pos_x, pos_y, angle);
}

Motorcycle::Motorcycle()
{
    pic = new Entity(250, 250, 30.0, 0.0, "./images/motorcycle.gif");
    fflush(stdout);
/*
    pos_x = 250;
    pos_y = 250;
    angle = 0;
    img = new Image("./images/motorcycle.gif");
*/
    pedal = Neutral;

    //setup_opengl(this.img);
    // you can't set up opengl anywhere but main.
    // opengl setup uses weird implicit global variables that go out of scope
    // unless specifically initialized within the main initialization function.
}

void Motorcycle::render()
{
    pic->render();
    //img->show(30.0f, pos_x, pos_y, angle);
}
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
       pic->angle += 1.5f;
       break;
    case Right:
       pic->angle -= 1.5f;
       break;
    }
    pic->angle = fmod(pic->angle, 360.0);
    float rad = TO_RAD(pic->angle);
    pic->pos_x = pic->pos_x + vel * SPEED * std::cos(rad);
    pic->pos_y = pic->pos_y + vel * SPEED * std::sin(rad);
    if (pic->pos_x < 0)
        pic->pos_x = gl.xres;
    if (pic->pos_x > gl.xres)
        pic->pos_x = 0;
    if (pic->pos_y < 0)
        pic->pos_y = gl.yres;
    if (pic->pos_y > gl.yres)
        pic->pos_y = 0;
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

