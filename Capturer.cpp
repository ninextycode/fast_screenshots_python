#include "Capturer.h"


Capturer::Capturer(int x, int y, int width, int height): 
    region_ro_capture(x, y, width, height) {
    init();
}

Capturer::Capturer(Rectangle area): region_ro_capture(area) {
    init();
}

void Capturer::init() {
    display_ptr = XOpenDisplay(NULL);
    root = DefaultRootWindow(display_ptr);
    XWindowAttributes window_attributes;
    XGetWindowAttributes(display_ptr, root, &window_attributes);
    Screen* screen = window_attributes.screen;

    ximg_ptr = XShmCreateImage(display_ptr,
            DefaultVisualOfScreen(screen),
            DefaultDepthOfScreen(screen),
            ZPixmap, NULL, &shminfo,
            region_ro_capture.width, region_ro_capture.height);

    shminfo.shmid = shmget(IPC_PRIVATE,
            ximg_ptr->bytes_per_line * ximg_ptr->height, IPC_CREAT|0777);
    shminfo.shmaddr = ximg_ptr->data = (char*)shmat(shminfo.shmid, 0, 0);
    shminfo.readOnly = False;
    if(shminfo.shmid < 0)
        puts("Capturer: Fatal shminfo error!");
    Status s1 = XShmAttach(display_ptr, &shminfo);
    printf("Capturer: XShmAttach() %s\n", s1 ? "success!" : "failure!");

    this->image_created = false;
}

Capturer::~Capturer() {
    if(image_created) {
        XDestroyImage(ximg_ptr);
    }
    XShmDetach(display_ptr, &shminfo);
    shmdt(shminfo.shmaddr);
    XCloseDisplay(display_ptr);
    puts("Capturer: Exit success!");
}

cv::Mat Capturer::getFastScreenshot() {
    if(!image_created) {
        image_created=true;
    }
    XShmGetImage(display_ptr, root, ximg_ptr, 
            region_ro_capture.x, region_ro_capture.y, 0x00ffffff);
    cv::Mat img = cv::Mat(region_ro_capture.height, region_ro_capture.width, 
            CV_8UC4, ximg_ptr->data);
    // cv::cvtColor(img, img, CV_BGRA2BGR);
    return img;    
}

