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
    void show(float, int, int, float);    
};


#endif // _IMAGE_H
