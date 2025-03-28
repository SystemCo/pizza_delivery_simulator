//Lesslie Valdivia
//
#include "lvaldivia.h"
#include <iostream>
#include <chrono> 
using namespace std;
//void timer(float t);
void show_lesslie(Rect* r);
//void deltaTime();

/*class Glass_System {
  public:
//int strikes = 3;
//float money;

};
*/
//  TO DO03/23/2025
//FIX the update_frame fuction.
void show_lesslie(Rect* r)
{
    ggprint8b(r, 16, 0xFFFF0000, "Lesslie");

}

TimerBar::TimerBar(float pos_x, float pos_y, float scale, float angle, const char* infile, unsigned char alphaColor[3], int rows, int cols) : Entity(pos_x, pos_y, scale, angle, infile, alphaColor, rows, cols) 
                                                                                                                                              //TimerBar::TimerBar(float pos_x, float pos_y, float scale, float angle, const char* fname, int rows, int cols) : Entity(pos_x, pos_y, scale, angle, fname)
{
    this->rows = rows;
    this->cols = cols;
    this->frame = 0;
    cout << "TimerBar texture ID: " << texture << endl; 

}

void TimerBar::Timer(float t) 
{ 

    if (deliverytime > 0)
    {
        deliverytime = deliverytime - t;

        /*if (deliveryMade) 
         * resetTimer();
         */

        if  (deliverytime <= 0 && !timesup) {
            deliverytime = 0;
            timesup = true;
        }

        //update();
        //update(deliverytime, 15.0f);
    }
}
void TimerBar::resetTimer()
{
    deliverytime = 15.0f;
    timesup = false;
}

void TimerBar::update()
{ //updates frame based on the timef
    float frameR;  
    int maxFrames = rows * cols;
    float frameRatio = (((maxTime - deliverytime) / maxTime) * maxFrames);
    // float frameRatio = ((1- deliveryTime) / maxTime) * (maxFrames-1) + 1;
    //cout << "Delivery TIme: " << deliveryTime << endl;

    frameR = static_cast<int>(frameRatio);

    if (frameR < 1) {
        frameR = 0;
    } else if (frameR > maxFrames) {
        frameR = maxFrames - 1;
    } else {
        frameR = frameR;
    }

   // frame = frameR;
    this->frame = frameR;
    /* ///debugging
       cout << " deliveryTime=" << deliveryTime 
       << ", maxTime=" << maxTime 
       << ", frameRatio=" << frameRatio 
       << ", frame=" << frameR <<endl;

*/
}

void TimerBar::timeRender()
{ //remder the time sprite 
    cout << "Rendering sprite frame " << this->frame << " of " << rows*cols << endl;
    //this->frame = frameR;  
    this->render();
    
    /*
    int width = scale / 2;
    int height = scale;
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, texture);
    //
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, alpha_cutoff.get());
    glColor4ub(255,255,255,255);

    int ix = frame / cols;
    int iy = frame % cols;

    float fx = (float)iy / (float)cols;
    float fy = (float)ix / (float)rows;
    float deltaX = 1.0f / (float)cols;
    float deltaY = 1.0f / (float)rows;

    glBegin(GL_QUADS);

    glTexCoord2f(fx, fy+deltaY); glVertex2i(-width, -height);
    glTexCoord2f(fx, fy);             glVertex2i(-width, height);
    glTexCoord2f(fx + deltaX, fy);    glVertex2i(width, height);
    glTexCoord2f(fx + deltaX,fy+deltaY); glVertex2i(width, -height);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
       
      */
}
