#ifndef _DCARTER_H_
#define _DCARTER_H_
#include "fonts.h"
#include "shared.h"
void show_david(Rect* r);
void init_opengl_bike();
void render_bike();
enum Pedal { Forward, Neutral, Backward };
enum Turn  { Left, Straight, Right };

class Image { // from the rainforest framework
public:
    int width, height;
    unsigned char *data;
    GLuint texture;

    ~Image() { delete [] data; }
    Image(const char *fname);
    void init_gl();
    
};

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
        Percent velocity;
        Pedal pedal;
        Turn turn;
    public:
        Image *img;
        Motorcycle();

        void set_pedal(Pedal);
        void set_turn(Turn);
        void move();
        void render();
};

#endif //_DCARTER_H_
