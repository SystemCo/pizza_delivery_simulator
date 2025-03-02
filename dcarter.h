#ifndef _DCARTER_H_
#define _DCARTER_H_
#include "fonts.h"
#include "image.h"
// Simple text display wrapper used for the credits page
void show_david(Rect* r);

// Rendering and physics for the title screen
struct Animation {
    float delta_x;
    float delta_y;
    float delta_angle;
    int   flipped;
};
void title_moto_physics(int frame, Animation animations[5]);
void title_physics();
void title_render();

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

class Entity : public Image { // Wrapper around image that stores important display info
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
    // No inputs, just jumps based on gl's resolution state.
    void jump_edges();
    //
    // Runs 500 frames of entity animation. 
    // Incrementing the frame number is the job of the calling context.
    // Section count allows for arbitrarily complex animations.
    //
    // If section count == 5, 
    // then the animation runs 5 stages of 100 frames each.
    // This function is not safe.
    // It is the job of the calling context to ensure 
    // that index does not go out of bounds.
    // Ex: Animation animations[3]; 
    // my_entity.animate_500_frames(499, animations, 4); 
    // will produce out of bounds error.
    //
    void animate_500_frames(int frame, Animation animations[],
                                                    int section_count);
    void render(); 
};

// Models the main playable character
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

// Mouse clickable buttons. These are intended to be a parent class.
// Each real button will inherent from this, 
// and implement its own On_Click method.
class Button {
private:
        char text[100];
        char color[3] { (char)255, 0, (char)255 }; // bytes, not characters
        void write_text(); // Button text color is always black for now
public:
        float pos[2];
        int  dims[2];
        // All that needs to be called to render. Writes text internally.
        void render();
        Button();
        Button(int x_pos, int y_pos);
        // The sea of setup
        void set_pos(float x, float y)  {  pos[0]   = x;  pos[1]   = y; }
        void set_dims(int  x, int   y)  { dims[0]   = x; dims[1]   = y; }
        void set_color(char r, char g, char b) 
        {
            color[0] = r; color[1] = g; color [2] = b;
        }
        void set_text(const char new_text[]);
        int is_inside(int x, int y); // AABB
        // 
        // Nothing burger. Meant to be mutated by child classes.
        void click(int x, int y);
};

#endif //_DCARTER_H_
