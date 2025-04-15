#ifndef _LVALDIVIA_H_
#define _LVALDIVIA_H_

#include "fonts.h"
//#include "image.h"
//#include "dcarter.h"
#include "shared.h"

//extern Global gl;

extern int roundAttempts;
extern bool timesUp;
extern float  timesUpTimer;
void show_lesslie(Rect* r);

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
        /*void renderTimer() {
          timerbar.timeRender();
          }i
          */
        //void renderTimer(Position pos, float scale) {
        //void timerbar.timeRender(pos, scale);



};
struct timerNode 
{
    TimerBar* timer;
    timerNode *next;
    timerNode *prev;
};
class TimerList
{
    protected: 
        timerNode *head;
        timerNode *tail;
    public:
        TimerList();
        void Deallocate();
        ~TimerList();
        timerNode *create(TimerBar* Timer);
        void timerAll( float dt);
        void updateAll();
       void addTimer(TimerBar* timer);
       void initAll();
       void removeTimer(TimerBar* Timer);
       void renderTimer(TimerBar* timer);
       void renderAll();

};
#endif

//add a counter that calls the physics counter, instead of real time
