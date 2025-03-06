// dcarter.cpp
// Personal file of David Carter
// Contains important implementation for:
//      Image,
//      Entity,
//      Motorcycle,
//      Button
// Classes
//
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

//Non-Class function prototypes
int resolution_scale(int width, int height);
int resolution_scale(Image* img);
void show_david(Rect* r);

void show_david(Rect* r)
{
    ggprint8b(r, 16, 0xf3ab00, "David - The Sweaty One");
}

// ***************** Image Method Implementations ***********************
// Overload of Image::show, that sets flipped to 0 by default
void Image::show(float wid, int pos_x, int pos_y, float angle)
{
    this->show(wid, pos_x, pos_y, angle, 0);
}

Image::Image(const char *fname, unsigned char alphaColor[3]) : Image(fname)
{
    for (int i = 0; i<3; i++)
        this->alphaColor[i] = alphaColor[i];
}

unsigned char* Image::colorToAlpha(unsigned char color[3])
{
    unsigned char *newdata, *ptr;
    unsigned char *data = (unsigned char *)this->data;
    newdata = (unsigned char *)malloc(this->width * this->height * 4);
    ptr = newdata;
    for (int i=0; i<this->width * this->height * 3; i+=3) {
        const int a = ptr[0] = data[0];
        const int b = ptr[1] = data[1];
        const int c = ptr[2] = data[2];
        const int r_delta = color[0] > a ? color[0] - a : a - color[0];
        const int g_delta = color[1] > b ? color[1] - b : b - color[1];
        const int b_delta = color[2] > c ? color[2] - c : c - color[2];
        ptr[3] = (r_delta + g_delta + b_delta)/3;
        ptr = &ptr[4];
        data = &data[3];
    }
    return newdata;
}

unsigned char* Image::blackToAlpha()
{
    //Add 4th component to an RGB stream...
    //RGBA
    //When you do this, OpenGL is able to use the A component to determine
    //transparency information.
    //It is used in this application to erase parts of a texture-map from view.
    //Edited by David Carter, hoping to improve:
    //
    //This is an optimized equivalent to colorToAlpha(black)
    //ppm file format has no alpha channel. Alpha pixels are converted to black
    //
    unsigned char *newdata;
    unsigned char *data = (unsigned char *)this->data;
    newdata = (unsigned char *)malloc(this->width * this->height * 4);
    for (int i=0; i<this->width * this->height; i++) {
        const int a = newdata[i*4+0] = data[i*3+0];
        const int b = newdata[i*4+1] = data[i*3+1];
        const int c = newdata[i*4+2] = data[i*3+2];
        //-----------------------------------------------
        //Original approach:
        //newdata[3] = (newdata[0] + newdata[1] + newdata[2])/3
        //Max approach:
        //newdata[3] = MAX(a, b, c);
        //Chris Smith approach:
        //newdata[3] = (a|b|c);
        //
        // All approaches represent "The blacker it is, the lower the alpha" 
        //
        // Similarly, all will return 0, only when pixel is perfect black
        //
        // Chris Smith's is the most efficient
        // and is perfectly sufficient when paired with
        // glAlphaFunc(GL_GREATER, 0.0f);
        // since this only checks for full transparency => full black
        //
        //-----------------------------------------------
        newdata[i*4+3] = (a|b|c);
    }
    return newdata;
}

// *********************** Percent methods ***********************
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
Entity::Entity(float pos_x, float pos_y, float scale, float angle,
        const char infile[], unsigned char color[3]) 
        : Image(infile, color)
{
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->scale = scale;
    this->angle = angle;
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

#define MOTO_SIZE 25
// Calling Entity's constructor sets all shared variables 
// and calls Image's constructor.
Motorcycle::Motorcycle() :
    Entity(250, 250, MOTO_SIZE, 0.0, "./images/Moto_bod.jpg")
    // main entity default colorToAlpha white because jpg
{
    // Everything but pedal can be left default or set by Entity constructor
    turn_sharpness = 2.5;
    pedal = Neutral;
}

// Go straight when not pressing buttons or when pressing L & R buttons
void Motorcycle::set_turn()
{
    if ( this->left && !this->right)
        this->turning = Left;
    else if ( this->right && !this->left)
        this->turning = Right;
    else
        this->turning = Straight;
}

void Motorcycle::move()
{
    // Maybe this should go in the header file?
    const float acceleration = 0.1;
    const float turn_acc = 0.3;
    const float vel = velocity.get();
    const float dir = turn_dir.get();
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
    const float straighter_dir = dir > 0 ? dir - turn_acc : dir + turn_acc;
    const bool snap = dir*dir < turn_acc*turn_acc;
    const float straightened_dir = snap ? 0 : straighter_dir;
    switch (turning) {
    case Straight:
        turn_dir.set(straightened_dir);
        break;
    case Left:
        turn_dir.set(dir + turn_acc);
        break;
    case Right:
        turn_dir.set(dir - turn_acc);
        break;
    }
    angle += turn_sharpness*turn_dir.get()*vel;
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

void Motorcycle::render()
{
    const float head_angle = 10 * turn_sharpness * turn_dir.get();
    Image* img = this;
    const float height = scale * img->height/img->width;
    glBindTexture(GL_TEXTURE_2D, img->texture);
    glColor4ub(255,255,255,255);
    glPushMatrix();
        glTranslatef(pos_x, pos_y, 0.0f);
        glEnable(GL_ALPHA_TEST);
        const float whiteness_cutoff = 0.4f;
        glAlphaFunc(GL_GREATER, whiteness_cutoff);
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
        //render the body
        glBegin(GL_QUADS);
        // no flipped for now
            glTexCoord2i(0, 1); glVertex2i(-scale,-height);
            glTexCoord2i(0, 0); glVertex2i(-scale, height);
            glTexCoord2i(1, 0); glVertex2i( scale, height);
            glTexCoord2i(1, 1); glVertex2i( scale,-height);
        glEnd();
        const float head_height = scale * head.height/head.width;
        glBindTexture(GL_TEXTURE_2D, head.texture);
        // render the head
        glPushMatrix();
            // translation after rotation effectively changes the pivot point
            const float pivot_offset = head_height / 1.3;
            glTranslatef(0.0f, height*0.9-pivot_offset, 0.0f);
            glRotatef(head_angle, 0.0f, 0.0f, 1.0f);
            glTranslatef(0.0f, pivot_offset, 0.0f);
            glBegin(GL_QUADS);
                glTexCoord2i(0, 1); glVertex2i(-scale,-head_height);
                glTexCoord2i(0, 0); glVertex2i(-scale, head_height);
                glTexCoord2i(1, 0); glVertex2i( scale, head_height);
                glTexCoord2i(1, 1); glVertex2i( scale,-head_height);
            glEnd();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
    glDisable(GL_ALPHA_TEST);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Motorcycle::init_gl()
{
    Image::init_gl();
    head.init_gl();
}

// *********** Resolution Utilities ***********************
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
    //glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    const int wid = resolution_scale(&gl.background);
    gl.background.show(wid, gl.xres/2, gl.yres/2, 0.0f);
    gl.moto_side->render();
    gl.dummy_button.render();
}

// ***************** Mouse clickable Buttons *************************
//

Button::Button(float x, float y)
{
    this->set_text("Loren Ipsum");
    this->set_color(255, 255, 0);
    this->set_pos(x, y);
    this->set_dims(100, 50);
}

Button::Button() : Button(200, 200)
{
}

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
        glColor4ub(color[0], color[1], color[2], 255);
        glTranslatef(pos[0], pos[1], 0.0f);
        glBegin(GL_QUADS);
            const int width = dims[0];
            const int height = dims[1];
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

