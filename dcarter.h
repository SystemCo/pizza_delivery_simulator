#ifndef _DCARTER_H_
#define _DCARTER_H_
#include "fonts.h"
#include "image.h"
// Simple text display wrapper used for the credits page
void show_david(Rect* r);
// Rendering and physics for the title screen
void title_render();
void title_physics();
//
// get the minimum scale for an image that will completely fill a given resolution     
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

class Entity : public Image {
    public:
    float pos_x;
    float pos_y;
    int flipped;
    float scale;
    float angle;
    Entity(float pos_x, float pos_y, float scale, float angle, 
            const char infile[]);
    //
                                 // Overload just for brevity.
                                 // Values always need updated in practice.
    Entity(const char infile[]);
    void render(); 
};

class Motorcycle : public Entity {
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
        //Entity* pic;
    public:
        Motorcycle();

        void set_pedal(Pedal pedal);
        void move();
        //void render();
        void set_left();
        void unleft();
        void set_right();
        void unright();
        //void init_gl();
};

#endif //_DCARTER_H_
