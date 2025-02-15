#include "headers.h"

extern Global gl;
void show_david(Rect* r)
{
    ggprint8b(r, 16, 0x00ff00ff, "David - The Sweaty One");
}


void init_opengl_bike()
{
    glGenTextures(1, &gl.bikeTexture);
    int w = gl.bike_img->width;
    int h = gl.bike_img->height;
    //
    glBindTexture(GL_TEXTURE_2D, gl.bikeTexture);
    //
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
            GL_RGB, GL_UNSIGNED_BYTE, gl.bike_img->data);
}

