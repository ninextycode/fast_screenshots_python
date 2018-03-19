#ifndef STDAFX_H
#define STDAFX_H

#include <numpy/numpyconfig.h>
#ifdef NPY_1_7_API_VERSION
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#define NPE_PY_ARRAY_OBJECT PyArrayObject
#else
#define NPE_PY_ARRAY_OBJECT PyObject
#endif
        
#include <opencv2/opencv.hpp> 
#include <numpy/arrayobject.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <X11/extensions/XShm.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python.hpp>
#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/foreach.hpp>

#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include <map>
#include <list>
#include <exception>
#include <Python.h>


        
#endif /* STDAFX_H */

