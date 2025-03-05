#ifndef _IMAGE_H
#define _IMAGE_H
#include <GL/glx.h>

class Image { // from the rainforest framework
private:
    unsigned char* colorToAlpha(unsigned char color[3]);
    unsigned char color[3];
    int color_to_alpha = false;
public:
    int width, height;
    unsigned char *data;
    GLuint texture;

    ~Image() { delete [] data; }
    Image(const char *fname);
    Image(const char *fname, unsigned char color[3]);
    void init_gl();
    unsigned char* buildAlphaData();
    void show(float wid, int pos_x, int pos_y, float angle, int flipped);
    // Overload not flipped by default
    void show(float wid, int pos_x, int pos_y, float angle);
};

#endif // _IMAGE_H
