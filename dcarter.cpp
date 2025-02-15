#include "headers.h"
#include <iostream>

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
    //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
            GL_RGB, GL_UNSIGNED_BYTE, gl.bike_img->data);
}

void render_bike()
{
    float wid = 60.0f;
    //glColor3f(1.0, 1.0, 1.0); // white?
    glColor4f(1.0, 1.0, 1.0, 1.0); // white?
    glPushMatrix();
    glTranslatef((float)(gl.xres/2), (float)(gl.yres/2), 0.0f);

    glBindTexture(GL_TEXTURE_2D, gl.bikeTexture);
    //glBindTexture(GL_TEXTURE_2D, gl.new_bike.id);
    
    //glRotatef(g.bike.angle, 0.0f, 0.0f, 1.0f);
    
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

