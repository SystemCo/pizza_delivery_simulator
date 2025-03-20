#ifndef _LVALDIVIA_H_
#define _LVALDIVIA_H_

#include "fonts.h"
#include "shared.h"
#include "image.h"

void show_lesslie(Rect* r);

class TimerBar : public Entity
{
    public:
        int frame = 0;
        //TimerBar(const char* fname, int rows, int cols);
        TimerBar(float x, float y, float scale, float angle,const char* fname, unsigned char alphaColor[3], int rows, int cols);
        //TimerBar(float pos_x, float pos_y, float scale, float angle,const char* fname, int rows, int cols);
        void update(float deliveryTime, float maxTime);
        void timeRender();
        //void timeRender(Position pos, float scale)
        //int strikes = 3;
        //float money;
        float deliverytime = 15.0f; 
        bool timesup = false;
        bool deliverMade = false;
        void Timer(float t);
        void resetTimer();
        /*void renderTimer() {
          timerbar.timeRender();
          }i
          */
        //void renderTimer(Position pos, float scale) {
        //void timerbar.timeRender(pos, scale);



};
#endif
//add a counter that calls the physics counter, instead of real time
