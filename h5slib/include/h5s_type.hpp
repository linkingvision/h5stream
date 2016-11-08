#ifndef __H5S_TPYE_HH__
#define __H5S_TPYE_HH__

#include <string.h>
#include <vector>
#include <iostream>

#if defined(_WIN32)
#if defined(H5S_EXPORTS)
#define H5S_LIBRARY_API __declspec(dllexport)
#else
#define H5S_LIBRARY_API __declspec(dllimport)
#endif
#else
#define H5S_LIBRARY_API
#endif



#endif 

