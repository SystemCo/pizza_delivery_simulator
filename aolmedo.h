// Author: Avelina Olmedo
// Date: 02/28/2025

#ifndef AOLMEDO_H
#define AOLMEDO_H
#include "fonts.h"

void show_avelina(Rect *r);



class Title_Exit_Button : public Button {
    private:
        char text[100] = "Exit title";
    public:
        void click(int x, int y);
        Title_Exit_Button();
};



#endif // AOLMEDO_H

