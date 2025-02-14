#ifndef _SHARED_H_
#define _SHARED_H_
class Image { // from the Bigfoot framework
public:
    int width, height;
    unsigned char *data;
    ~Image() { delete [] data; }
    Image(const char *fname);
    
};
#endif //_SHARED_H_
