#ifndef _DCARTER_H_
#define _DCARTER_H_
#include "fonts.h"
void show_david(Rect* r);
void init_opengl_bike();
void render_bike();
enum Pedal { Forward, Neutral, Backward };
enum Turn  { Left, Straight, Right };

// From Bigfoot Framework

class Percent { // float from -1 to 1
    private:
        float val;
    public:
        Percent(float);
        void set(float);
        float get();
};

class Motorcycle {
    private:
        int pos_x;
        int pos_y;
        int rotation;
        Percent velocity;
        Pedal pedal;
        Turn turn;
    public:
        Motorcycle();

        void set_pedal(Pedal);
        void set_turn(Turn);
        void move();
        void render();
};

#endif //_DCARTER_H_
