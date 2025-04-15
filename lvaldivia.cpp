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

            if (roundAttempts > 0) 
            {
                roundAttempts--;
                timesUp = true;
                timesUpTimer = 2.0f;
            }

        }

    }
}
void TimerBar::resetTimer()
{
    deliverytime = 15.0f;
    timesUp = false;
}

void TimerBar::update()
{ //updates frame based on the time
    int maxFrames = rows * cols;
    float frameRatio = (((maxTime - deliverytime) / maxTime) * maxFrames);
    // float frameRatio = ((1- deliveryTime) / maxTime) * (maxFrames-1) + 1;

    int frameR = static_cast<int>(frameRatio);

    if (frameR < 1) {
        frameR = 0;
    } else if (frameR > maxFrames) {
        frameR = maxFrames - 1;
    } else {
        frameR = frameR;
    }

    this->frame = frameR;

    /*   
         cout << " deliveryTime=" << deliverytime 
         << ", maxTime=" << maxTime 
         << ", frameRatio=" << frameRatio 
         << ", frame=" << frameR <<endl;

*/
}

void TimerBar::timeRender()
{ //remder the time sprite 
  //cout << "Rendering sprite frame " << this->frame << " of " << rows*cols << endl;
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
//=================================================
//Created list for Timers
//=================================================

TimerList::TimerList()
{
    tail = NULL;
    head = NULL;
}
void TimerList::Deallocate()
{
    timerNode* t = head;
    while( t != NULL)
    {
        timerNode* nn = t->next;
        delete t;
        t = nn;

    }

}
TimerList::~TimerList()
{
    Deallocate();
    head = NULL;
    tail = NULL;
}
timerNode* TimerList::create(TimerBar* Timer)
{
    timerNode* newnode;
    try
    {
        newnode = new timerNode;
        newnode->timer = Timer;
        newnode->prev = NULL;
        newnode->next = NULL;
    }
    catch (bad_alloc &e)
    {
        newnode = NULL;
    }
    return newnode;
}


void TimerList::addTimer(TimerBar* timer)
{

    timerNode* newnode = create(timer);
    if (newnode == NULL) {
        cout << "failed to create node" << endl;
    }

    if (head != NULL)
    {
        newnode->next = head;
        head->prev = newnode;
        head = newnode;
    }
    else
    {
        head = newnode;
        tail = newnode;
    }
    cout << "Node created" << endl;


}

void TimerList::removeTimer(TimerBar* timer)
{

    timerNode* t = head;

    if(head->timer == timer)
    {
        t = head;
        head = head->next;
        head->prev = NULL;

        if (head == NULL) {
            tail = NULL;
        }
        delete t->timer;
        delete t;
        return;

    }
    //traverse to delete node 
    timerNode* c = head;
    while (c->next != NULL) {
        if (c->next->timer == timer) {
            timerNode* t = c->next;
            c->next = t->next;

            if (t == tail) {
                tail = c;
            }
            delete t->timer;
            delete t; 
            return;
        }
        c = c->next;
    }


}
void TimerList::initAll()
{
    timerNode* t = head;
    while ( t != NULL)
    {
        if (t->timer != NULL)
        {
            cout << "initializing" << endl;
            t->timer->init_gl();
        }
        t = t->next;
    }
}
void TimerList::timerAll(float dT)
{
    timerNode* t = head;
    while (t != NULL) {
        if ( t->timer != NULL) {
            t->timer->Timer(dT);
        }
        t = t->next;
    }
}
void TimerList::updateAll()
{
    timerNode* t = head;
    while ( t != NULL) {
        if (t->timer != NULL) {
            t ->timer->update();
        }
        t = t-> next;
    }
}
void TimerList::renderAll() 
{
    timerNode* t = head;
    while (t != NULL)
    {
        if (t->timer != NULL)
        { //attempting rendering
          //cout << "rendering" << endl;
            t->timer->timeRender();

        }
        t = t->next;

    }
}

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
// 04/06/2024
// White box showing,initialization is the problem?
//==================================
//Attempts
//==================================







//==================================
//Time left in a Day
//================================== 




