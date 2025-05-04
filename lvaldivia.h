#ifndef _LVALDIVIA_H_
#define _LVALDIVIA_H_

#include "fonts.h"
//#include "image.h"
//#include "dcarter.h"
#include "shared.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

//extern Global gl;

//extern int roundAttempts;

void show_lesslie(Rect* r);
void manageDeliveries(float dT);

void attemptsRender(Rect* r);



class TimerBar : public Entity
{
    public:
       int frame = 0;
        //TimerBar(const char* fname, int rows, int cols);
        TimerBar(float x, float y, float scale, float angle,const char* fname, unsigned char alphaColor[3], int rows, int cols);
        //TimerBar(float pos_x, float pos_y, float scale, float angle,const char* fname, int rows, int cols);
        // void update(float deliveryTime, float maxTime);
        void update();
        void timeRender();
        //void timeRender(Position pos, float scale)
        //int strikes = 3;
        //float money;
        float deliverytime = 15.0f;
        float maxTime = 15.0f; 
        //bool timesup = false;
        bool deliverMade = false;
        //int frameR = 0;
        void Timer(float t);
        void resetTimer();
        bool removalNeeded = false;
        bool getRemovalNeeded();



};
class TimerList
{
    public:
         static const int maxTimers = 6;
        TimerBar* timers[maxTimers];
        int count;
        TimerList();
        ~TimerList();
        void timerAll( float dt);
        void updateAll();
       bool addTimer(float x, float y, float scale, float angle, const char* infile, unsigned char alphaColor[3], int rows, int cols);
       //void initAll();
       void removeTimer(int index);
void removeExpiredTimers();
       //void renderTimer(TimerBar* timer);
       void renderAll();

};

void initDeliveryLocations();
void activateRandomDeliveries();
void manageGame(float dT);
void drawGameOver();
void printScoreNTime();
#endif

//add a counter that calls the physics counter, instead of real time
