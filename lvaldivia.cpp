//Lesslie Valdivia
//
#include "lvaldivia.h"
#include <new>
#include <iostream>
#include <chrono> 
using namespace std;
//void timer(float t);
extern Global gl;

void attemptsRender(Rect* r);

void show_lesslie(Rect* r)
{
    ggprint8b(r, 16, 0xFFFF0000, "Lesslie");

}
int roundAttempts = 3;
bool timesUp = false;
float timesUpTimer = 0.0f;
//void show_lesslie(Rect* r);

void attemptsRender(Rect* r) 
{
    //extern Global gl;

    for (int i = 0; i < roundAttempts; i++)
    gl.attempts[i].render();


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

        if  (deliverytime <= 0 && !timesUp) {
            deliverytime = 0;
            timesUp = true;
            removalNeeded = true;
            if (roundAttempts > 0) 
            {
                roundAttempts--;
                timesUpTimer = 2.0f;
            }

        }

    }
}

bool TimerBar::getRemovalNeeded() { return removalNeeded; }

void TimerBar::resetTimer()
{
    deliverytime = 15.0f;
    timesUp = false;
}

void TimerBar::update()
{ //updates frame based on the time
    int maxFrames = rows * cols;
    float frameRatio = (((maxTime - deliverytime) / maxTime) * maxFrames);

    int frameR = static_cast<int>(frameRatio);

    if (frameR < 0) {
        frameR = 0;
    } else if (frameR > maxFrames) {
        frameR = maxFrames - 1;
    } else {
        frameR = frameR;
    }

    this->frame = frameR;

       
        // cout << " deliveryTime=" << deliverytime 
        // << ", maxTime=" << maxTime 
         //<< ", frameRatio=" << frameRatio 
         //<< ", frame=" << frameR <<endl;


}

void TimerBar::timeRender()
{ //remder the time sprite 
  //cout << "Rendering sprite frame " << this->frame << " of " << rows*cols << endl;
  
   //doesn't work?  
  // this->render();
    
     const int   wid       = scale;
    const int   height    = scale * (this->height / rows) / (width / cols);
    const int   frame_row = frame / cols; // trunkated by design
    const int   frame_col = frame % cols;
    const float delta_x   = 1.0f / (float)cols;
    const float delta_y   = 1.0f / (float)rows;
    const float left      = (float)(frame_col - 1) / (float)cols;
    const float right     = left + delta_x;
    const float bottom    = (float) (frame_row - 1) / (float)rows;
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
//=================================================
//Created list for Timers
//=================================================

//queue like structure
TimerList::TimerList()
{
    count = 0;
}

TimerList::~TimerList()
{
for (int i = 0; i < count; i++) {
         if (timers[i] != NULL) {
             delete timers[i];
             timers[i] = NULL;
         }
     }
     count = 0;
 
}

bool TimerList::addTimer(float x, float y, float scale, float angle, const char* infile, unsigned char alphaColor[3], int rows, int cols)
{
cout << "creating timer" << endl;
 if (count >= maxTimers)
         return false;
 
     timers[count] = new TimerBar(x, y, scale, angle, infile, alphaColor, rows, cols);
     timers[count]->init_gl();
     count++;
cout << "done creatinf" << endl;
     return true;

}

void TimerList::removeTimer(int index)
{

 if (index >= 0) {
         if (index < count) {
             delete timers[index];
 
 
             for (int i = index; i < count - 1; i++) {
                 timers[i] = timers[i - 1];
             }
 
             timers[count - 1] = NULL;
             count--;
         }
 
 
     }

}

void TimerList::removeExpiredTimers()
{
    for (int i =0; i < count; i++) {
        if (timers[i] != NULL && timers[i]->getRemovalNeeded()) {
            removeTimer(i);
            i--;
        }
    }
}
/*void TimerList::initAll()
{
    cout << " testing" << endl;
for (int i = 0; i < count; i++) {
         cout << "initializing" << endl;
         timers[i]->init_gl();
     }
}
*/
void TimerList::timerAll(float dT)
{
for (int i = 0; i < count; i++) {
         if (timers[i] != NULL)
             timers[i]->Timer(dT);
     }
}
void TimerList::updateAll()
{
for (int i = 0; i < count; i++) {
         if (timers[i] != NULL)
             timers[i]->update();
     }
}
void TimerList::renderAll() 
{
for (int i = 0; i < count; i++) {
         if (timers[i] != NULL)
             timers[i]->timeRender();
     }
}
/*
void TimerList::renderTimer(TimerBar* timer)
{
    timerNode* t = head;
    while (t != NULL)
    {
        if (t->timer == timer)
        {
            t->timer->timeRender();
            return;
        }
        t = t->next;
    }
}
*/
// 04/06/2024
// White box showing,initialization is the problem?
//==================================
//Attempts
//==================================







//==================================
//Time left in a Day
//================================== 




