#include "stdafx.h"
#include "Shapes.h"

Shapes::Shapes(void) {}

Shapes::Shapes(int a1, int b1, int a2, int b2)
{
	x1 = a1;
	x2 = a2;
	y1 = b1;
	y2 = b2;
	isFill = 0;
	bgColor = RGB(0, 0, 0);
}

Shapes::Shapes(int a1, int b1, int a2, int b2, int fill, int thin, int color)
{
	x1 = a1;
	x2 = a2;
	y1 = b1;
	y2 = b2;
	isFill = fill;
	isThin = thin;
	bgColor = color;
}

void Shapes::SetColor(COLORREF newColor)
{
	bgColor = newColor;
}

Shapes::~Shapes(void) {}


