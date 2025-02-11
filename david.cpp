// Author: David Carter
// Purpose: My personal contributions to the project
// Date: Spring 2025

enum Pedal { Forward, Neutral, Backward };

struct motorcycle {
    int x;
    int y;
    int rotation;
    Pedal pedal;

};

double accelerate(double velocity, int forward)
{
    return velocity + forward;
}

