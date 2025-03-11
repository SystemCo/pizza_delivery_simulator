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

// ***************** Non-Class functions **********************************
// ************************************************************************
//
// for credits
void show_david(Rect* r)
{
    ggprint8b(r, 16, 0xf3ab00, "David - The Sweaty One");
}

// **************** Convenient Math funcs *****************
float abs_diff(float a, float b)
{
    return a > b ? a - b : b - a;
}

float approach(float follower, float leader, float rate)
{
    if (abs_diff(follower, leader) <= rate)
        return leader;
    else
        return follower > leader ? follower - rate : follower + rate;
}

// *********** Resolution Utilities ***********************
int resolution_scale(int width, int height)
{
    const float img_proportion = (float)width / (float)height;
    const float resolution_proportion = (float)gl.xres / (float)gl.yres;
    const bool  crop_height = resolution_proportion > img_proportion;
    const bool  crop_width  = !crop_height;
    float output = 0;
    
    if (crop_height)
        output = img_proportion * gl.yres / 2;
    if (crop_width)
        output = gl.xres / 2;
    return output;
}
int resolution_scale(Image* img)
{
    return resolution_scale(img->width, img->height);
}

// *********** Animation for Title sceen ******************
// void Entity::jump_edges();
// void Entity::animate();
void title_moto_physics(int frame, Animation animations[5])
{
    const int total_frames = 500;
    const int section_count = 5;
    gl.moto_side->animate(frame, animations, section_count, total_frames);
}
void title_render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    const int wid = resolution_scale(&gl.background);
    gl.background.show(wid, gl.xres/2, gl.yres/2, 0.0f);
    gl.moto_side->render();
    gl.dummy_button.render();
}

// ********** OpenGL Wrapper Functions ********************
void draw_rect(float wid, float height)
{
    glBegin(GL_QUADS);
        glTexCoord2i(0, 1); glVertex2i(-wid,-height);
        glTexCoord2i(0, 0); glVertex2i(-wid, height);
        glTexCoord2i(1, 0); glVertex2i( wid, height);
        glTexCoord2i(1, 1); glVertex2i( wid,-height);
    glEnd();
}

void pivotedRotate(float pivot_x_point, float pivot_y_point, float angle)
{
    glTranslatef(pivot_x_point, pivot_y_point, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-pivot_x_point, -pivot_y_point, 0.0f);
}

// ***************** Image Method Implementations ***********************
// **********************************************************************
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
    unsigned char *newdata;
    unsigned char *data = (unsigned char *)this->data;
    newdata = (unsigned char *)malloc(width * height * 4);
    for (int i=0; i < width * height; i++) {
        const int r = newdata[ i*4 + 0] = data[ i*3 + 0];
        const int g = newdata[ i*4 + 1] = data[ i*3 + 1];
        const int b = newdata[ i*4 + 2] = data[ i*3 + 2];
        const int r_delta = abs_diff(color[0], r);
        const int g_delta = abs_diff(color[1], g);
        const int b_delta = abs_diff(color[2], b);
        newdata[i*4 + 3] = (r_delta + g_delta + b_delta)/3;
    }
    return newdata;
}

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
//-----------------------------------------------
unsigned char* Image::blackToAlpha()
{
    //Add 4th component to an RGB stream...
    //RGBA
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
        newdata[i*4+3] = (a|b|c);
    }
    return newdata;
}

// ****************** Percent Method Implementations ************
// **************************************************************
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

// ****************** Entity Method Implementations *************
// **************************************************************
Entity::Entity(float pos_x, float pos_y, float scale, 
        float angle, const char infile[]) : Image(infile)
{
    pos = {pos_x, pos_y};
    this->scale = scale;
    this->angle = angle;
}
Entity::Entity(float pos_x, float pos_y, float scale, float angle,
        const char infile[], unsigned char color[3]) 
        : Image(infile, color)
{
    pos = {pos_x, pos_y};
    this->scale = scale;
    this->angle = angle;
}
Entity::Entity(const char infile[]) : Image(infile)
{
    pos = {0, 0};
    scale = 50.0f;
    angle = 0;
}

void Entity::render()
{
    this->show(scale, pos.x, pos.y, angle, flipped);
}

void Entity::jump_edges()
{
    const int wid = gl.scale*2;
    const int height = 2*gl.scale * gl.background.height / gl.background.width;
    const int left_edge = (gl.xres - wid)/2;
    const int right_edge = left_edge + wid;
    const int bottom_edge = (gl.yres - height)/2;
    const int top_edge = bottom_edge + height;

    for (int i = 0; i < 10; i++) {
        if (pos.x < left_edge)
            pos.x += wid;
        else if (pos.x > right_edge)
            pos.x -= wid;
        else if (pos.y < bottom_edge)
            pos.y += height;
        else if (pos.y > top_edge)
            pos.y -= height;
        else
            break;
    }
}

void Entity::animate(int frame, Animation animations[],
                                    int section_count, int total_frames)
{
    const int frame_num = total_frames / section_count;
    for (int i = 0; i < section_count; i++) {
        if (frame >= i*frame_num && frame < (i+1)*frame_num) {
            pos.x  += animations[i].delta_x;
            pos.y  += animations[i].delta_y;
            angle  += animations[i].delta_angle;
            flipped = animations[i].flipped;
        }
    }
    
    // Always jump edges. May not want to do this in the full animation
    this->jump_edges();
}

// ****************** Motorcycle Method Implementations ********************
// *************************************************************************
#define MOTO_SIZE 25

Motorcycle::Motorcycle() :
    // main entity default colorToAlpha white because jpg
    Entity(250, 250, MOTO_SIZE, 0.0, "./images/Moto_bod.jpg")
{
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
    const float turn_rate = 0.6;
    const float vel = velocity.get();

    // Pedal acclarates
    switch (pedal) {
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

    // Arrow keys change the turn direction
    float goal_dir = 0;
    this->set_turn();
    switch (turning) {
    case Straight:
        goal_dir = 0;
        break;
    case Left:
        goal_dir = turn_sharpness;
        break;
    case Right:
        goal_dir = -1*turn_sharpness;
        break;
    }
    direction = approach(direction, goal_dir, turn_rate);

    // Moto drives in a circle regaurdless of speed
    angle += direction * vel / scale * 25;
    while (angle < 0)
        angle += 360;
    while (angle > 0)
        angle -= 360;

    // Update position
    const float rad = TO_RAD(angle);
    const float delta_x = vel * SPEED * std::cos(rad);
    const float delta_y = vel * SPEED * std::sin(rad);
    pos.x += delta_x;
    pos.y += delta_y;
    jump_edges();
}

void Motorcycle::render()
{
    const float head_angle = 10 * direction;
    const float height = scale * this->height/width;
    const float whiteness_cutoff = 0.4f;
    const float head_height = scale * head.height/head.width;
    const float pivot_y = -head_height / 1.3;

    glColor4ub(255,255,255,255);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, whiteness_cutoff);

    // render body
    glBindTexture(GL_TEXTURE_2D, texture);
    glPushMatrix();
        glTranslatef(pos.x, pos.y, 0.0f);
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
        draw_rect(scale, height);

        // render head
        glBindTexture(GL_TEXTURE_2D, head.texture);
        glPushMatrix();
            glTranslatef(0.0f, height*0.9, 0.0f);
            pivotedRotate(0.0f, pivot_y, head_angle);
            draw_rect(scale, head_height);
        glPopMatrix();
    glPopMatrix();

    // cleanup
    glDisable(GL_ALPHA_TEST);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Motorcycle::init_gl()
{
    Image::init_gl();
    head.init_gl();
}

// ***************** Button Method Implementations *******************
// *******************************************************************
Button::Button(float x, float y)
{
    this->set_text("Loren Ipsum");
    this->set_color(255, 255, 0);
    pos = {x , y};
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
    r.bot = pos.y - text_height;
    r.left = pos.x;
    ggprint8b(&r, 16, color, text);
}

void Button::render()
{
    glColor4ub(color[0], color[1], color[2], 255);
    glPushMatrix();
        glTranslatef(pos.x, pos.y, 0.0f);
        draw_rect(dims[0], dims[1]);
    glPopMatrix();

    write_text();
}

int Button::is_inside(int x, int y)
{
return   y <= (pos.y + dims[1]) &&
         y >= (pos.y - dims[1]) &&
         x <= (pos.x + dims[0]) &&
         x >= (pos.x - dims[0]);
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

