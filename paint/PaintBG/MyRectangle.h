#pragma once
#include "Shapes.h"

class MyRectangle :public Shapes {
public:
	MyRectangle();

	MyRectangle(int a1, int b1, int a2, int b2);

	MyRectangle(int a1, int b1, int a2, int b2, int fill, int thin, COLORREF color);

	void Draw(CDC *dc);

	bool isEx(CPoint p);
};