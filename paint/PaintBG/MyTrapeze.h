#pragma once
#include "Shapes.h"
#include "MyRectangle.h"

class MyTrapeze :public MyRectangle {
public:
	MyTrapeze();

	MyTrapeze(int a1, int b1, int a2, int b2);

	MyTrapeze(int a1, int b1, int a2, int b2, int fill, int thin, COLORREF color);

	void Draw(CDC *dc) override;

	bool isEx(CPoint p) override;
};