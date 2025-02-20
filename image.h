#ifndef _IMAGE_H
#define _IMAGE_H

class Image { // from the rainforest framework
public:
    int width, height;
    unsigned char *data;
    GLuint texture;

    ~Image() { delete [] data; }
    Image(const char *fname);
    void init_gl();
    unsigned char* buildAlphaData();
    void show(float wid, int pos_x, int pos_y, float angle);
    void show(float wid, int pos_x, int pos_y, float angle, int flipped);
    // Overload not flipped by default
};


#endif // _IMAGE_H
