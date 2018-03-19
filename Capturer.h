#ifndef CAPTURER_H
#define CAPTURER_H

#include "stdafx.h"

struct Rectangle {
    Rectangle(int x, int y, int width, int height): 
        x(x), y(y),
        width(width),
        height(height) {
    }
    int x;
    int y;
    int width;
    int height;
};

class Capturer {
public:
    Capturer(Rectangle area);
    Capturer(int x, int y, int width, int height);
    virtual ~Capturer();
    cv::Mat getFastScreenshot();
private:
    Display* display_ptr;
    Window root;
    XImage* ximg_ptr;
    XShmSegmentInfo shminfo;
    Rectangle region_ro_capture;
    bool image_created;
    
    void init();
};

#endif /* CAPTURER_H */

