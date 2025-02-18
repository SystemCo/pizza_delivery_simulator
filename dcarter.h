#ifndef _DCARTER_H_
#define _DCARTER_H_
#include "fonts.h"
#include "shared.h"
#include "image.h"
void show_david(Rect* r);
void init_opengl_bike();
void render_bike();
enum Pedal { Forward, Neutral, Backward };
enum Turn  { Left, Straight, Right };

void show_image(float wid, int pos_x, int pos_y, float angle, Image* img);

class Percent { // float from -1 to 1
    private:
        float val;
    public:
        Percent(float);
        Percent();
        void set(float);
        float get();
};

class Motorcycle {
    private:
        float pos_x;
        float pos_y;
        float angle;
        bool left;
        bool right;
        Percent velocity;
        Pedal pedal;
        Turn turn;
        void set_turn();
    public:
        Image *img;
        Motorcycle();

        void set_pedal(Pedal);
        void move();
        void render();
        void set_left();
        void unleft();
        void set_right();
        void unright();
};

#endif //_DCARTER_H_
