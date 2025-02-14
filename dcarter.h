
enum Pedal { Forward, Neutral, Backward };
enum Turn  { Left, Neutral, Right };

class Motorcycle {
pub:
    int pos_x;
    int pos_y;
    int rotation;
    float velocity; // from -1 to 1
    Pedal pedal;
    Turn turn;
    Motorcycle();
    
    void set_pedal(Pedal);
    void set_turn(Turn);
    void move();
    void render();
};


