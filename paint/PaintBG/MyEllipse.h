#pragma once
#include "Shapes.h"

class MyEllipse :public Shapes {
public:
	MyEllipse();

	MyEllipse(int a1, int b1, int a2, int b2);

	MyEllipse(int a1, int b1, int a2, int b2, int fill, int thin, COLORREF color);

	void Draw(CDC *dc);

	bool isEx(CPoint p);
};

