#ifndef _DCARTER_H_
#define _DCARTER_H_
#include "fonts.h"
#include "image.h"
//include "shared.h"




class Box;
// Simple text display wrapper used for the credits page
void show_david(Rect* r);

// Functions based on how often func is called
void show_fps(Rect* r);

// Define the path for all cars
void initCars();

// Rendering and physics for the title screen
struct Animation {
    float delta_x;
    float delta_y;
    float delta_angle;
    float delta_scale;
    int   flipped;
};

struct Position {
    float x;
    float y;
};

struct AABB {
    Position pos;
    float wid;
    float height;
};

struct Intersections {
    float left;
    float right;
    float top;
    float bottom;
    float off_left;
    float off_right;
    float off_top;
};

// Entity::animate() wrapper
void title_moto_physics(int frame, Animation animations[5]);
void title_physics();
void title_render();

// get the minimum scale for an image that will completely fill a given resolution     
int  resolution_scale(int width, int height);
int  resolution_scale(Image* img);

// Draws rectangle on the current gl stack frame, with current color and texture
// Position and angle must be set using glTranslate on the current stack frame
void draw_rect(float width, float height);

// Rotates a gl stack frame about a given pivot point
void pivotedRotate(float pivot_point_x, float pivot_point_y, float angle);  

enum Pedal { Forward, Neutral, Backward };
enum Turn  { Left, Straight, Right };

class Percent { // float from -1 to 1
private:
    float val;
public:
    Percent(float val);
    Percent();
    void set(float val);
    float get();
};

class Sprite : public Image {
private:
    int delay_counter = 0;
public:
    int frame;
    int delay;
    int rows;
    int cols;
    //Percent alpha_cutoff = 0.0f;
    Percent alpha_cutoff;
    void render(float scale, Position pos, float angle);
    void render(float scale, Position pos);
    void update_frame();
    Sprite(const char *fname, unsigned char alphaColor[3], int rows, int cols);
    Sprite(const char *fname, int rows, int cols);
};

class Entity : public Sprite { // Wrapper around image that stores important display info
public:
    Position pos;
    int flipped;
    float scale;
    float angle;
    Entity(float pos_x, float pos_y, float scale, float angle, 
            const char infile[]);
    Entity(float pos_x, float pos_y, float scale, float angle, 
            const char infile[], unsigned char color[3]);
    Entity(float pos_x, float pos_y, float scale, float angle, 
            const char infile[], unsigned char color[3], int rows, int cols);
    Entity(const char infile[]);
    // No inputs, just jumps based on gl's resolution state.
    void jump_edges();
    //
    // Incrementing the frame number is the job of the calling context.
    // Section count allows for arbitrarily complex animations.
    //
    // If section count == 5, and totale_frames == 500
    // then the animation runs 5 stages of 100 frames each.
    // This function is not safe.
    // section_count must be equal to the length of the animation array.
    // It is the job of the calling context to ensure 
    // that index does not go out of bounds.
    //
    // Ex: Animation animations[3]; 
    // my_entity.animate(499, animations, 4, 500); 
    // will produce out of bounds error.
    //
    // Ex correct call:
    // Aniation animations[3];
    // *initialize animations*
    // Entity my_entity("image.png");
    // my_entity.animate(10, animations, 3, 500);
    void animate(int frame, Animation animations[],
                                    int section_count, int total_frames);
    void follow_lines(Position* line_points, int point_count, float speed);
    void render(); 
};

class Line_Follower : public Entity { // Only allowed to follow lines
    private:
        const int point_count = 6;
        Position lines[6]; // Need to know size at compile time?
        int line_on;
        bool approach(Position point);
    public:
        float speed = 2.0;
        Line_Follower(float pos_x, float pos_y, float scale, float angle, 
            const char infile[], unsigned char color[3], int rows, int cols);
        Line_Follower();
        void set_points(Position* points);
        void physics();
        void quickSnap();
};
extern Line_Follower cars[10];

struct RectStruct;
// Models the main playable character
class Motorcycle : public Entity {
    private:
        Percent velocity;
        //Percent turn_dir;
        float direction = 0;
        int crash_dir = 0; // -1 for backward, 1 for forward
        Turn turning;
        Image head {"./images/Moto_head.jpg"}; // white alphaColor
        void set_turn();
    public:
        bool right;
        bool left;
        float turn_sharpness;
        Pedal pedal;
        Motorcycle();
        //Vec2 prevPos;
        Position prevPos;
        float vel[2];
        float force[2];
        void move();
        void render();
        void init_gl();
        void crash();
        bool collides_with_box(const Box& box);
    };

// Mouse clickable buttons. These are intended to be a parent class.
// Each real button will inherent from this, 
// and implement its own On_Click method.
class Button {
private:
        char text[100];
        unsigned char color[3] { 255, 0, 255 }; // bytes, not characters
        void write_text(); // Button text color is always black for now
public:
        Position pos;
        int  dims[2];
        bool darken = false;
        // All that needs to be called to render. Writes text internally.
        void render();
        Button();
        Button(float x_pos, float y_pos);
        
         float motoWidth;
         float motoHeight;
        // The sea of setup
        void set_pos(float x, float y)  {  pos.x  = x;   pos.y = y; }
        void set_dims(int  x, int   y)  { dims[0] = x; dims[1] = y; }
        void set_color(char r, char g, char b) 
        {
            color[0] = r; color[1] = g; color [2] = b;
        }
        void set_text(const char new_text[]);
        bool is_inside(int x, int y); // AABB
        // 
        // Nothing burger. Meant to be mutated by child classes.
        void click(int x, int y);
        void onHardCollision();
};


// class Title_Exit_Button : public Button {
// private:
//     char text[100] = "Exit title";
// public:
//     void click(int x, int y);
//     Title_Exit_Button();
// };



// class Pause_Button : public Button {
//     void click(int x, int y);
//     Pause_Button(int x, int y, const char text[]);
// }
// void Pause_Button::click(int x, int y)
// {
//     // Your implementation here
// }

#endif //_DCARTER_H_
