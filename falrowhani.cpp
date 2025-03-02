//Name:Fenoon
//lab4
//working on animation
//
//original code from Dcarter 
//modified by me 
//
#include "dcarter.h"

// I added this prototype to my header file -- David
//void title_moto_physics(int frame, Animation animation[5]);


void title_physics()
{
    static int frame = 0;
    Animation  animations[5];
    animations[0] = {5, 0, 0, 0};
    animations[1] = {5, 0, 1, 0};
    for (int i = 0; i<5; i++)
        animations[i] = {1, 1, 0, 0};
    title_moto_physics(frame, animations);

    frame += 1;
    frame %= 500;
}
