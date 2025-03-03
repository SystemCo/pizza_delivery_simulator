//Name:Fenoon
//lab4
//working on animation
//
//original code from Dcarter 
//modified by me 
//
#include "dcarter.h"
#include <iostream>
#include "falrowhani.h"

//function prototypes 
void title_moto_physics(int frame, Animation animation[3]);
void show_fenoon(Rect*r);

void show_fenoon(Rect*r)
{
    ggprint8b(r, 16, 0x00FFFF, "Fenoon");
}


// I added this prototype to my header file -- David
//void title_moto_physics(int frame, Animation animation[5]);

void title_physics()
{
    static int frame = 0;
 Animation  animations[3];
    animations[0] = {2, 0, 0, 0};
    animations[1] = {2, 5, 25, 0};
    animations[2] = {2, 0, 0, 0};

    title_moto_physics(frame, animations);

    frame += 1;
    frame %= 500;

}


/*
void title_physics()
{
    static int frame = 0;
    Animation  animations[5];
    animations[0] = {5, 0, 0, 0};
    animations[1] = {2, 5, 30, 0};
    animations[2] = {5, 0, 0, 0};
    for (int i = 0; i<5; i++)
        animations[i] = {1, 1, 0, 0};
    title_moto_physics(frame, animations);

    frame += 1;
    frame %= 500;
}*/
