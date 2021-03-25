#pragma once
#include "Shapes.h"

class MyLine :public Shapes {
public:
	MyLine();

	MyLine(int a1, int b1, int a2, int b2);

	MyLine(int a1, int b1, int a2, int b2, int thin, COLORREF color);

	void Draw(CDC *dc);

	bool isEx(CPoint p);
};