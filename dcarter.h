#ifndef _DCARTER_H_
#define _DCARTER_H_
#include "fonts.h"
#include "shared.h"
#include "image.h"
void show_david(Rect* r);
void init_opengl_bike();
void title_render();
void title_physics();
int  resolution_scale(int width, int height);
int  resolution_scale(Image* img);
enum Pedal { Forward, Neutral, Backward };
enum Turn  { Left, Straight, Right };

//void show_image(float wid, int pos_x, int pos_y, float angle, Image* img);

class Percent { // float from -1 to 1
    private:
        float val;
    public:
        Percent(float val);
        Percent();
        void set(float val);
        float get();
};

class Entity {
    public:
    int pos_x;
    int pos_y;
    int flipped;
    float scale;
    float angle;
    Image *img;
    Entity(int pos_x, int pos_y, float scale, float angle, 
            const char infile[]);//
                                 // Overload just for brevity.
                                 // Values always need updated in practice.
    Entity(const char infile[]);
    void render(); 
};

class Motorcycle {
    private:
/*
        float pos_x;
        float pos_y;
        float angle;
*/
        bool left;
        bool right;
        Percent velocity;
        Pedal pedal;
        Turn turn;
        void set_turn();
    public:
        Entity* pic;
        /*
        Image *img;
        */
        Motorcycle();

        void set_pedal(Pedal pedal);
        void move();
        void render();
        void set_left();
        void unleft();
        void set_right();
        void unright();
};

#endif //_DCARTER_H_
