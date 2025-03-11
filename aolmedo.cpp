// Author: Avelina Olmedo
// Date: 02/28/2025
/***********************************************************************************/
#include "shared.h"
#include "aolmedo.h"

#include <cstdio>

extern Global gl;

void show_avelina(Rect* r);


void show_avelina(Rect* r)
{
    ggprint8b(r, 16, 0xffec407a, "Lina");
}


Title_Exit_Button::Title_Exit_Button() : Button(200, 200)
 {
     this->set_text("Welcome to the Pizza Delivery Simulator!");
     this->set_color(0, 200, 200);
     this->set_pos(300, 300);
     this->set_dims(200, 50);
 }

 void Title_Exit_Button::click(int x, int y)
 {
     if (is_inside(x, y))
         gl.screen = Home;
 }

