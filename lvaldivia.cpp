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

        update(deliverytime, 15.0f);
    }
}
void TimerBar::resetTimer()
{
    deliverytime = 15.0f;
    timesup = false;
}

void TimerBar::update(float deliveryTime, float maxTime)
{ //updates frame based on the time
    int maxFrames = rows * cols;
    float frameRatio = (((maxTime - deliveryTime) / maxTime) * maxFrames);
    // float frameRatio = ((1- deliveryTime) / maxTime) * (maxFrames-1) + 1;
    //cout << "Delivery TIme: " << deliveryTime << endl;

    int frameR = static_cast<int>(frameRatio);

    if (frameR < 1) {
        frameR = 0;
    } else if (frameR > maxFrames) {
        frameR = maxFrames - 1;
    } else {
        frameR = frameR;
    }

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
    this->render();
}
