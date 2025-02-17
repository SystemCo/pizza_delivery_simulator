#include "headers.h"
#include <iostream>
#include <cmath>
#define PI 3.141592653589793
#define TO_RAD(x) ((x+90) / 360.0f) * PI * 2.0
#define SPEED 4

extern Global gl;

void show_david(Rect* r)
{
    ggprint8b(r, 16, 0x00ff00ff, "David - The Sweaty One");
}

void show_image(float wid, int pos_x, int pos_y, float angle, Image* img)
{
    //printf("hello world");
    float height = wid * img->height/img->width;
    glColor3f(1.0, 1.0, 1.0);
    //glColor3f(0, 0, 0);
    glPushMatrix();
    glTranslatef(pos_x, pos_y, 0.0f);

    glBindTexture(GL_TEXTURE_2D, img->texture);
   // glBindTexture(GL_TEXTURE_2D, g.silhouetteTexture);
   // glEnable(GL_ALPHA_TEST);
   // glAlphaFunc(GL_GREATER, 0.0f);
   // glColor4ub(255,255,255,255);

    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 1.0f); glVertex2i(-wid,-height);
        glTexCoord2f(1.0f, 0.0f); glVertex2i(-wid, height);
        glTexCoord2f(0.0f, 0.0f); glVertex2i( wid, height);
        glTexCoord2f(0.0f, 1.0f); glVertex2i( wid,-height);
    glEnd();
    glPopMatrix();
}

void Image::init_gl()
{
    glGenTextures(1, &texture);
    int w = width;
    int h = height;
    glBindTexture(GL_TEXTURE_2D, texture);
    //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
            GL_RGB, GL_UNSIGNED_BYTE, data);
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

Motorcycle::Motorcycle()
{
    pos_x = 250;
    pos_y = 250;
    angle = 0;
    pedal = Neutral;
    img = new Image("./images/motorcycle.png");

    //setup_opengl(this);
}

void Motorcycle::render()
{
    show_image(30.0f, pos_x, pos_y, angle, img);
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
       angle += 1.5f;
       break;
    case Right:
       angle -= 1.5f;
       break;
    }
    angle = fmod(angle, 360.0);
    float rad = TO_RAD(angle);
    pos_x = pos_x + vel * SPEED * std::cos(rad);
    pos_y = pos_y + vel * SPEED * std::sin(rad);

    if (pos_x < 0)
        pos_x = gl.xres;
    if (pos_x > gl.xres)
        pos_x = 0;

    if (pos_y < 0)
        pos_y = gl.yres;
    if (pos_y > gl.yres)
        pos_y = 0;


}

