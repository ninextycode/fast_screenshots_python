#include "stdafx.h"
#include "Capturer.h"
#include "numpy_opencv_converter/np_opencv_converter.hpp"

using namespace boost::python;
BOOST_PYTHON_MODULE(capturer) {
    fs::python::init_and_export_converters();
    class_<Rectangle>("Rectangle", init<int, int, int, int>(args("x", "y", "width", "height")))
        .def_readwrite("x", &Rectangle::x)
        .def_readwrite("y", &Rectangle::y)
        .def_readwrite("width", &Rectangle::width)
        .def_readwrite("height", &Rectangle::height);
    
    class_<Capturer>("Capturer", no_init)
        .def(init<Rectangle>(args("rectangle")))
        .def(init<int, int, int, int>(args("x", "y", "width", "height")))
        .def("get_fast_screenshot", &Capturer::getFastScreenshot);
    
}

int main(){
    Rectangle area(100, 100, 100, 100);
    
    Capturer capturer(100, 100, 100, 100);
    cv::Mat img;

    for(int i; ; i++){
        img = capturer.getFastScreenshot();

        cv::imshow("img", img);
        int key = cv::waitKey(1);
        if (key == 27)
            break;
    }

  
    cv::waitKey(0);
}