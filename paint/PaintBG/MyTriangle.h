#pragma once
#include "Shapes.h"

class MyTriangle :public Shapes {
public:
	MyTriangle();

	MyTriangle(int a1, int b1, int a2, int b2);

	MyTriangle(int a1, int b1, int a2, int b2, int fill, int thin, COLORREF color);

	void Draw(CDC *dc);

	bool isEx(CPoint p);
};

