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

unsigned char red[3] {255,0,0};
const Intersections map1Intersections {
    .left      = 180,
    .right     = 675,
    .top       = 550,
    .bottom    = 250,
    .off_left  = -100,
    .off_right = 1500,
    .off_top   = 1000,
};

/* 
 **  This is the global variable for the whole project. 
 **  Declared in asteroids.cpp
 */

Line_Follower cars[10];
extern Global gl;

// ***************** Variables That May Be Called Externally *************
//


// ***************** Non-Class functions **********************************
// ************************************************************************
//
// for credits

void show_david(Rect* r)
{
    ggprint8b(r, 16, 0xf3ab00, "David - The Sweaty One");
}

extern double timeDiff(struct timespec *start, struct timespec *end);
extern void timeCopy(struct timespec *dest, struct timespec *source);
void show_fps(Rect* r)
{
    const int show_delay = 30;
    static int call_times = 0;
    static struct timespec timeStart, timeCurrent;
    static double timeSpan;
    char buffer[30];
    call_times += 1;
    if (call_times < show_delay) {
        sprintf(buffer, "fps: %3.0f", show_delay / timeSpan);
        ggprint8b(r, 16, 0xf3ab00, buffer);
        return;
    }
    call_times = 0;
    clock_gettime(CLOCK_REALTIME, &timeCurrent);
    timeSpan = timeDiff(&timeStart, &timeCurrent);
    sprintf(buffer, "fps: %3.0f", show_delay / timeSpan);
    ggprint8b(r, 16, 0xf3ab00, buffer);
    timeCopy(&timeStart, &timeCurrent);
}

void initCars()
{
    const Intersections ints = map1Intersections;

    cars[0].set_points(new Position[6] {
            {ints.off_left, ints.top},
            {ints.left, ints.top},
            {ints.right, ints.top},
            {ints.right, ints.bottom},
            {ints.left, ints.bottom},
            {ints.off_left, ints.bottom},
        });
    cars[1].set_points(new Position[6] {
            {ints.right, ints.off_top},
            {ints.right, ints.bottom},
            {ints.left, ints.bottom},
            {ints.left, ints.top},
            {ints.right, ints.top},
            {ints.off_right, ints.top},
        });
    cars[2].set_points(new Position[6] {
            {ints.off_left, ints.top},
            {ints.left, ints.top},
            {ints.right, ints.top},
            {ints.left, ints.top},
            {ints.left, ints.bottom},
            {ints.off_left, ints.bottom},
        });
    cars[3].set_points(new Position[6] {
            {ints.off_right, ints.bottom},
            {ints.left, ints.bottom},
            {ints.right, ints.bottom},
            {ints.left, ints.bottom},
            {ints.right, ints.bottom},
            {ints.off_left, ints.bottom},
        });

    for (int i = 2; i < 10; i++)
        cars[4].set_points(new Position[6] {
            {ints.left, ints.off_top},
            {ints.left, ints.top},
            {ints.left, ints.bottom},
            {ints.right, ints.bottom},
            {ints.right, ints.top},
            {ints.right, ints.off_top},
        });
    for (int i = 0; i < 10; i++) {
        cars[i].quickSnap();
    }
}

void handle_car_crash()
{
if (gl.expl_pos.x > -1) {
        gl.explosion.update_frame();
        if (gl.explosion.frame == 0) {
            gl.expl_pos.x = -10;
        }
    } else {
        for (int i = 0; i < 5; i++) {
            if (gl.bike.collides(cars[i])) {
                gl.expl_pos.x = gl.bike.pos.x;
                gl.expl_pos.y = gl.bike.pos.y;
                gl.explosion.frame = 1;
                gl.explosion.delay = 2; 
                // explosion takes 2 * (16 / 60) = 1/2 second
            }
        }
        if (gl.expl_pos.x > -1) {
            deductMoney(gl.money, 5.0f);
            gl.bike.velocity.set(0.0f);
        }
    }
}

// **************** Convenient Math funcs *****************
template <typename T>
T abs_diff(T a, T b)
{
    return a > b ? a - b : b - a;
}

template <typename T>
T approach(T follower, T leader, T rate)
{
    if (abs_diff<T>(follower, leader) <= rate)
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
        const unsigned char r = newdata[ i*4 + 0] = data[ i*3 + 0];
        const unsigned char g = newdata[ i*4 + 1] = data[ i*3 + 1];
        const unsigned char b = newdata[ i*4 + 2] = data[ i*3 + 2];
        const unsigned char r_delta = abs_diff(color[0], r);
        const unsigned char g_delta = abs_diff(color[1], g);
        const unsigned char b_delta = abs_diff(color[2], b);
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

// ***************** Sprite Method Implementations ***********************
// *********************************************************************
Sprite::Sprite(const char *fname, unsigned char alphaColor[3], 
        int rows, int cols)
        : Image(fname, alphaColor)
{
    this->rows = rows;
    this->cols = cols;
    this->delay = 4;
    this->frame = 0;
}

Sprite::Sprite(const char *fname, int rows, int cols) : Image(fname)
{
    this->rows  = rows;
    this->cols  = cols;
    this->delay = 4;
    this->frame = 0;
}
void Sprite::update_frame()
{
    if (delay_counter > delay) {
        const int total_frames = rows * cols;
        frame += 1;
        frame %= total_frames;
        delay_counter = 0;
    } else {
        delay_counter += 1;
    }
}

//void draw_rect_sect(

void Sprite::render(float scale, Position pos, float angle)
{
    const int   wid       = scale;
    const int   height    = scale * (this->height / rows) / (width / cols);
    const int   frame_row = frame / cols; // trunkated by design
    const int   frame_col = frame % cols;
    const float delta_x   = 1.0f / (float)cols;
    const float delta_y   = 1.0f / (float)rows;
    //const float left      = (float)(frame_col - 1) / (float)cols;
    const float left      = (float)(frame_col) / (float)cols;
    const float right     = left + delta_x;
    //const float bottom    = (float) (frame_row - 1) / (float)rows;
    const float bottom    = (float) (frame_row) / (float)rows;
    const float top       = bottom + delta_y;

    glColor4ub(255,255,255,255);
    glBindTexture(GL_TEXTURE_2D, texture);

    glPushMatrix();
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, alpha_cutoff.get());
        glTranslatef(pos.x, pos.y, 0.0f);
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
        glBegin(GL_QUADS);
           glTexCoord2f( left,    top);  glVertex2i(-wid, -height);
           glTexCoord2f( left, bottom);  glVertex2i(-wid, +height);
           glTexCoord2f(right, bottom);  glVertex2i(+wid, +height);
           glTexCoord2f(right,    top);  glVertex2i(+wid, -height);
        glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Sprite::render(float scale, Position pos)
{
    render(scale, pos, 0.0f);
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
        float angle, const char infile[], unsigned char alphaColor[3],
        int rows, int cols) :
    Sprite(infile, alphaColor, rows, cols)
{
    pos = {pos_x, pos_y};
    this->scale = scale;
    this->angle = angle;
}
Entity::Entity(float pos_x, float pos_y, float scale, float angle,
        const char infile[], unsigned char alphaColor[3]) 
        : Entity(pos_x, pos_y, scale, angle, infile, alphaColor, 1, 1)
{}

Entity::Entity(float pos_x, float pos_y, float scale, 
        float angle, const char infile[]) : Sprite(infile, 1, 1)
{
    pos = {pos_x, pos_y};
    this->scale = scale;
    this->angle = angle;
}
Entity::Entity(const char infile[]) : Entity(200.0, 200.0, 100.0f, 0.0f, infile)
{}

void Entity::render()
{
    this->Sprite::render(scale, pos, angle);
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

// ****************** Line_Follower Method Implementations ******
// **************************************************************
Line_Follower::Line_Follower(float pos_x, float pos_y, float scale, 
        float angle, const char infile[], unsigned char alphaColor[3],
        int rows, int cols) :
    Entity(pos_x, pos_y, scale, angle, infile, alphaColor, rows, cols)
{
}


Line_Follower::Line_Follower() :
    Entity(30, 30, 40.0, 0, "images/Car1_sprite.png", red, 1, 8)
{}

void Line_Follower::set_points(Position points[10])
{
    line_on = 0;

    for (int i = 0; i < point_count; i++)
        lines[i] = points[i];
}

// returns true if snapped to point
bool Line_Follower::approach(Position point)
{
    const float delta_x = point.x - pos.x;
    const float delta_y = point.y - pos.y;
    const float abs_diff_pos = sqrt( 
            delta_x * delta_x + 
            delta_y * delta_y
    );
    if (abs_diff_pos <= speed * 3) {
        pos.x = point.x;
        pos.y = point.y;
        return true;
    }
    const double angle = atan2f( delta_y, delta_x);
    pos.x += speed * cos(angle);
    pos.y += speed * sin(angle);
    this->angle = angle / PI / 2.0 * 360.0;
    return false;
}

void Line_Follower::physics()
{
    //std::cout << lines[line_on].x << ", " << lines[line_on].y << std::endl;
    const bool snapped = this->approach(lines[line_on]);
    if(snapped) {
        line_on += 1;
        line_on %= point_count;
    }
    fflush(stdout);
}

void Line_Follower::quickSnap()
{
    pos.x = lines[line_on].x;
    pos.y = lines[line_on].y;
}

// ****************** Motorcycle Method Implementations ********************
// *************************************************************************
#define MOTO_SIZE 17

Motorcycle::Motorcycle() :
    // main entity default colorToAlpha white because jpg
    Entity(250, 250, MOTO_SIZE, 0.0, "./images/Moto_bod.jpg")
{
    turn_sharpness = 2.5;
    pedal = Neutral;
    alpha_cutoff.set(0.4f);

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
        if (crash_dir < 1)
            velocity.set(vel + acceleration);
        break;
    case Neutral:
        velocity.set(vel*0.99);
        break;
    case Backward:
        if (crash_dir > -1)
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
    direction = approach<float>(direction, goal_dir, turn_rate);

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
    const float head_height = scale * head.height/head.width;
    const float pivot_y = -head_height / 1.3;

    glColor4ub(255,255,255,255);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, alpha_cutoff.get());

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

bool Motorcycle::collides(Line_Follower &obstacle)
{
    const int obstacleWidth  = obstacle.scale;
    const int obstacleHeight = obstacle.scale * (obstacle.height / rows) /
                                                (width / cols);
    const float leftBound  = obstacle.pos.x - obstacleWidth;
    const float rightBound = obstacle.pos.x + obstacleWidth;
    const float topBound   = obstacle.pos.y + obstacleHeight;
    const float lowerBound = obstacle.pos.y - obstacleHeight;

    if ((pos.x >= leftBound && pos.x <= rightBound &&
        pos.y >= lowerBound && pos.y <= topBound))
        return true;
    else
        return false;
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
    unsigned char greyer[3] {
        approach<unsigned char>(color[0], 0, 20),
        approach<unsigned char>(color[1], 0, 20),
        approach<unsigned char>(color[2], 0, 20)
    };
    if (darken)
        glColor4ub(greyer[0], greyer[1], greyer[2], 255);
    else
        glColor4ub(color[0], color[1], color[2], 255);
    glPushMatrix();
        glTranslatef(pos.x, pos.y, 0.0f);
        draw_rect(dims[0], dims[1]);
    glPopMatrix();

    write_text();
}

bool Button::is_inside(int x, int y)
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

