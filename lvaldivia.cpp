//Lesslie Valdivia
//
#include "lvaldivia.h"
#include <iostream>
#include <chrono> 
using namespace std;
//void timer(float t);
extern Global gl;
extern TimerList timerList;

void manageDeliveries(float dT);
void initDeliveryLocations();
void manageGame(float dT);
void drawGameOver();
void printScoreNTime();
void checkDelivery(int locIndex);
void addMoney(MoneySystem &money, float amount);
void checkDelivery(int locIndex)
{
    for(int i = 0; i < gl.timerList->count; i++) {
       if (gl.timerLocation[i] == locIndex && gl.activeDeliveryLocations[locIndex]) {
           cout << "delivery completed" << endl;
           addMoney(gl.money, 10.0f);
           gl.timerList->removeTimer(i);
       }
    }

}
void printScoreNTime()
{
    Rect r;

    r.bot = 680;
    r.left = gl.xres/2 - 70;
    r.center = 0;
    gl.money.cashInRevenue();
    //int score = (int)gl.money.getTotalMoney();
    ggprint16(&r, 100, 0xFFCC5C, "SCORE: %i", (int)gl.money.getTotalMoney());


    Rect r2;

    r2.bot = 695;
    r2.left = 80;
    r2.center = 0;

    ggprint16(&r2, 100, 0xFFCC5C, "TIME");
}

void drawGameOver()
{
    gl.background.show(gl.scale, gl.xres/2, gl.yres/2, 0.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.1f, 0.14f, 0.34f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(0,0);
    glVertex2f(0, gl.xres);
    glVertex2f(gl.xres, gl.yres);
    glVertex2f(gl.xres, 0);
    glEnd();


    int boxW = gl.xres * 0.8f;
    int boxH = gl.yres * 0.6f;
    int boxL = (gl.xres - boxW) /2;
    int boxT = (gl.yres - boxH) / 2;


    glColor3f(0.1f, 0.14f, 0.34f);
    glBegin(GL_QUADS);
    glVertex2f(boxL, boxT);
    glVertex2f(boxL, boxT + boxH);
    glVertex2f(boxL + boxW, boxT + boxH);
    glVertex2f(boxL + boxW, boxT);
    glEnd();

    Rect r;
    r.bot = boxT + boxH - 50;
    r.left = gl.xres/2;

    ggprint16(&r, 1000, 0xFF6B6B, "GAME OVER");

    int box2W = boxW * 0.8;
    int box2H = 60;
    int box2L = boxL + (boxW - box2W)/2;
    int box2T = boxT + boxH - 120;

    glColor3f(0.06f, 0.09f, 0.16f);
    glBegin(GL_QUADS);
    glVertex2f(box2L + 2, box2T + 2);
    glVertex2f(box2L + 2, box2T + box2H - 2);
    glVertex2f(box2L + box2W - 2, box2T + box2H - 2);
    glVertex2f(box2L + box2W - 2, box2T +2);
    glEnd();

    r.bot = box2T + box2H/2;
    r.left = gl.xres / 2;
    ggprint16(&r, 1000, 0x6AAA64, "SCORE: %i", (int)gl.money.getTotalMoney()); //add the money total;

    r.bot = boxT + 290;
    r.left = gl.xres / 2;
    ggprint16(&r, 1000, 0x62B1FF, "THANKS FOR PLAYING!");

    r.bot = boxT + 250;
    r.left = gl.xres / 2;
    ggprint16(&r, 1000, 0xD6C1FF, "CREDITS: ");

    r.bot = boxT + 230;
    r.left = gl.xres / 2;
    show_avelina(&r);

    r.bot = boxT + 210;
    r.left = gl.xres / 2;
    show_david(&r);

    r.bot = boxT + 190;
    r.left = gl.xres / 2;
    show_fenoon(&r);

    r.bot = boxT + 160;
    r.left = gl.xres / 2;
    show_francisco(&r);

    r.bot = boxT + 140;
    r.left = gl.xres / 2;
    
    r.bot = boxT + 120;
    r.left = gl.xres / 2;
    show_lesslie(&r);

    /*show_lesslie(&r);
      show_avelina(&r);
      show_david(&r);
      show_fenoon(&r);
      show_francisco(&r);
      show_lesslie(&r);*/

    r.bot = boxT + 40;
    r.left = gl.xres / 2;
    ggprint16(&r, 1000,  0xFFCC5C, "PRESS X TO EXIT GAME");

    glDisable(GL_BLEND);
}   
//======================================
//Random Delivery System
//======================================

void initDeliveryLocations()
{

    //test locations
    /*gl.deliveryLocations[0][0] = 277.0f + 70;
    gl.deliveryLocations[0][1] = 533.0f + 70;

    gl.deliveryLocations[1][0] = 13.0f + 70;
    gl.deliveryLocations[1][1] = 279.0f + 70;

    gl.deliveryLocations[2][0] = 504.0f + 70;
    gl.deliveryLocations[2][1] = 533.0f + 70;
    */
    
   gl.deliveryLocations[0][0] = gl.box11.pos[0] + gl.box11.width;
    gl.deliveryLocations[0][1] = gl.box11.pos[1] + gl.box11.height;

    gl.deliveryLocations[1][0] = gl.box12.pos[0] + gl.box12.width;
    gl.deliveryLocations[1][1] = gl.box12.pos[1] + gl.box12.height;


    gl.deliveryLocations[2][0] = gl.box13.pos[0] + gl.box13.width;
    gl.deliveryLocations[2][1] = gl.box13.pos[1] + gl.box13.height;

    gl.deliveryLocations[3][0] = gl.box14.pos[0] + gl.box14.width;
    gl.deliveryLocations[3][1] = gl.box14.pos[1] + gl.box14.height;

    gl.deliveryLocations[4][0] = gl.box15.pos[0] + gl.box15.width;
    gl.deliveryLocations[4][1] = gl.box15.pos[1] + gl.box15.height;


    gl.deliveryLocations[5][0] = gl.box16.pos[0] + gl.box16.width;
    gl.deliveryLocations[5][1] = gl.box16.pos[1] + gl.box16.height; 
    for (int i = 0; i < gl.maxDeliveryLocations ; i++) {
        gl.activeDeliveryLocations[i] = false;
    }

    for (int i = 0; i < gl.maxDeliveryLocations; i++) {
        cout << "location " << i << ": " << gl.deliveryLocations[i][0] << ", "<< gl.deliveryLocations[i][1] << endl;
    }
    gl.activeDeliveries = 0;
}

void activateRandomDeliveries()
{
    //cout << "called" << endl;
    if (gl.activeDeliveries >= gl.maxActiveDeliveries)
        return;

    int index = rand() % gl.maxDeliveryLocations;
    bool found = false;
    for (int i = 0; i < gl.maxDeliveryLocations; i++) {
        if(!gl.activeDeliveryLocations[index]) {
            found = true;
            break;
        }
        index = (index + 1) % gl.maxDeliveryLocations; // try the next location
    }

    // activate the location
    if (found) {
        gl.activeDeliveryLocations[index] = true;

        float pos_x = gl.deliveryLocations[index][0] - 40;
        float pos_y = gl.deliveryLocations[index][1] - 40;

        // cout << pos_x << ", " << pos_y << endl;
        // store the current timer count before adding a new timer
        int timerIndex = gl.timerList->count;

        //add a timer for this delivery
        if (gl.timerList->addTimer(pos_x, pos_y, 90, 0.0f, "./images/TimeBar.png", gl.black2, 1, 12)) {
            // map timer to the delivery location
            gl.timerLocation[timerIndex] = index;
            gl.activeDeliveries++;
            cout << "created timer " << timerIndex << " for location " << index << endl;
        } 
        else {
            cout << "failed" << endl;
            gl.activeDeliveryLocations[index] = false;
        }
    }
}

void manageDeliveries(float dT)
{
    // Only manage deliveries if we're actually playing the game
    //if (gl.screen != Playing) return;

    gl.timerList->timerAll(dT);
    gl.timerList->updateAll();
    //gl.timerList->renderAll();
    gl.timerList->removeExpiredTimers();

    gl.deliveryDeltaTime += dT;

    //activates a new delivery between 5 to 10 seconds
    if (gl.activeDeliveries < gl.maxActiveDeliveries && gl.deliveryDeltaTime >= gl.nextDelivery) {

        activateRandomDeliveries();

        gl.deliveryDeltaTime = 0.0f;

        gl.nextDelivery = 5.0f + (rand() % 11);
    }
}

void manageGame(float dT)
{ //the main game time
  //manageDeliveries(dT);

  // Only manage game time if we're actually playing the game
  //if (gl.screen != Playing) return;

    gl.remainingTime = gl.remainingTime - dT;
    if (gl.remainingTime <= 0 ) {
        gl.remainingTime = 0;
        gl.gameOver = true;
    }
    gl.mainTime->deliverytime = gl.remainingTime;
    gl.mainTime->update();

    gl.money.cashInRevenue();

}

void attemptsRender(Rect* r);

void show_lesslie(Rect* r)
{
    ggprint8b(r, 16, 0xFFFF0000, "Lesslie");

}
//void show_lesslie(Rect* r);

void attemptsRender(Rect* r) 
{
    for (int i = 0; i < gl.gameAttempts; i++)
        gl.attempts[i].render();
}
TimerBar::TimerBar(float pos_x, float pos_y, float scale, float angle, const char* infile, unsigned char alphaColor[3], int rows, int cols) : Entity(pos_x, pos_y, scale, angle, infile, alphaColor, rows, cols) 
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
        if  (deliverytime <= 0) {
            deliverytime = 0;
            removalNeeded = true;
           if(!gl.gameOver) { 
            if (gl.gameAttempts > 0) 
            {
                gl.gameAttempts--;
             
            if ( gl.gameAttempts == 0) {
                gl.gameOver = true;
                cout << "GAME OVER!" << endl;
            }

        }
        }

    }
}
}
//bool TimerBar::getRemovalNeeded() { return removalNeeded; }
/*
void TimerBar::resetTimer()
{
    deliverytime = 15.0f;
    timesUp = false;
}
*/
void TimerBar::update()
{ //updates frame based on the time
    int maxFrames = rows * cols;
    float frameRatio = (((maxTime - deliverytime) / maxTime) * maxFrames);

    int frameR = (int)(frameRatio);

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

TimerList::TimerList()
{

    for (int i = 0; i < maxTimers; i++) {
        timers[i] = NULL;
    }
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
    //cout << "creating timer" << endl;
    if (count >= maxTimers)
        return false;

    timers[count] = new TimerBar(x, y, scale, angle, infile, alphaColor, rows, cols);
    timers[count]->init_gl();
    count++;
    //cout << "done creatinf" << endl;
    return true;

}

void TimerList::removeTimer(int index)
{

    if (index >= 0) {
        if (index < count) {
            int locationIndex = gl.timerLocation[index];
            gl.activeDeliveryLocations[locationIndex] = false;
            gl.activeDeliveries--;
           
            delete timers[index];


            for (int i = index; i < count - 1; i++) {
                gl.timerLocation[i] = gl.timerLocation[i + 1];
            }
            for (int i = index; i < count - 1; i++) {
                timers[i] = timers[i + 1];
            }

            timers[count - 1] = NULL;
            gl.timerLocation[count - 1] = -1;
            count--;
        }


    }

}

void TimerList::removeExpiredTimers()
{
    for (int i =0; i < count; i++) {
        if (timers[i] != NULL) {
            if (timers[i]->removalNeeded) {
                removeTimer(i);
                i--;
            }
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



