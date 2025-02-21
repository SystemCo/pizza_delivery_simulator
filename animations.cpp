#include "headers.h"
#define MAX(x, y) (x > y)*x + (y > x)*y

/** 
 *  This is the global variable for the whole project.
 *  Declared in asteroids.cpp
 */
extern Global gl;

void title_moto_physics(int frame)
{
    float* pos_x = &gl.moto_side->pos_x;
    float* pos_y = &gl.moto_side->pos_y;
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
    while (*pos_x < 0)
        *pos_x += gl.xres;
    while (*pos_x > gl.xres)
        *pos_x -= gl.xres;
    while (*pos_y < 0)
        *pos_y += gl.xres;
    while (*pos_y > gl.yres)
        *pos_y -= gl.yres;
}

void title_physics()
{
    static int frame = 0; 
    title_moto_physics(frame);

    frame += 1;
    frame %= 500;
}

void title_render()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    int wid = resolution_scale(&gl.background);
    gl.background.show(wid, gl.xres/2, gl.yres/2, 0.0f);
    int flipped = false;
    gl.moto_side->render();
}

