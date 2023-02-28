#pragma once
//#include "common.h"

#include <iostream>
#include<string>

#ifdef DLL_EXPORTS
#define DLL_DECLSPEC __declspec(dllexport)
#else
#define DLL_DECLSPEC __declspec(dllimport)
#endif

//#include "../OpenCV_App/common.h"
#include "../OpenCV_App/shape.h"

class DLL_DECLSPEC Circle:public Shape
{
public:
	Circle();
	~Circle();
	void ShowShapeInfo();

protected:
private:
};

extern "C"
{
	DLL_DECLSPEC Shape* lib_Circle_Create();
	DLL_DECLSPEC void lib_Circle_Release(Shape* obj);
} 