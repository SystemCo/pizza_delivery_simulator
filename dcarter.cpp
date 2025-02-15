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
    pedal = Pedal::Neutral;
    turn = Turn::Straight;
    img = new Image("./images/motorcycle.png");

    //setup_opengl(this);
}

void Motorcycle::render()
{
    float wid = 60.0f;
    glColor3f(1.0, 1.0, 1.0); // white?
    //glColor4f(1.0, 1.0, 1.0, 1.0); // white?
    glPushMatrix();
    glTranslatef(pos_x, pos_y, 0.0f);

    glBindTexture(GL_TEXTURE_2D, img->texture);
    //glBindTexture(GL_TEXTURE_2D, gl.new_bike.id);
    
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    
    glBegin(GL_QUADS);

   // glVertex2f(-wid,-wid);
   // glVertex2f(-wid, wid);
   // glVertex2f( wid, wid);
   // glVertex2f( wid,-wid);

    glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid,-wid);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
    glTexCoord2f(1.0f, 0.0f); glVertex2i( wid, wid);
    glTexCoord2f(1.0f, 1.0f); glVertex2i( wid,-wid);

    // left ?
    //    glTexCoord2f(1.0f, 1.0f); glVertex2i(-wid,-wid);
    //    glTexCoord2f(1.0f, 0.0f); glVertex2i(-wid, wid);
    //    glTexCoord2f(0.0f, 0.0f); glVertex2i( wid, wid);
    //    glTexCoord2f(0.0f, 1.0f); glVertex2i( wid,-wid);
    glEnd();
    glPopMatrix();
}
void Motorcycle::set_pedal(Pedal pedal)
{
    this->pedal = pedal;
}
void Motorcycle::set_turn(Turn turn)
{
    this->turn = turn;
}
void Motorcycle::move()
{
    float vel = velocity.get();
    switch (pedal) {
        case Pedal::Forward:
            velocity.set(vel+0.1);
            break;
        case Pedal::Neutral:
            velocity.set(vel*0.99);
            break;
        case Pedal::Backward:
            velocity.set(vel-0.1);
            break;
    }
    switch (turn) {
    case Turn::Straight:
       break;
    case Turn::Left:
       angle += 1.5f;
       break;
    case Turn::Right:
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

