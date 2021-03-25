#include "stdafx.h"
#include "MyLine.h"

MyLine::MyLine() {}

MyLine::MyLine(int a1, int b1, int a2, int b2)
	:Shapes(a1, b1, a2, b2)
{
	style = 4;
}

MyLine::MyLine(int a1, int b1, int a2, int b2, int thin, COLORREF color)
	: Shapes(a1, b1, a2, b2, 0, thin, color)
{
	style = 4;
}

void MyLine::Draw(CDC *dc)
{
	CPen myPen(PS_SOLID, isThin ? 1 : 4, bgColor);
	dc->SelectObject(&myPen);
	dc->MoveTo(x1, y1);
	dc->LineTo(x2, y2);
}

bool MyLine::isEx(CPoint p)
{
	int yy = y1 - y2, xx = x1 - x2;
	int minX = getMinX(), maxX = getMaxX(), minY = getMinY(), maxY = getMaxY(); //Shapes methods
	double m = (double)yy / (double)xx;
	if ((p.y - y1 - m * (p.x - x1)) > -7 && (p.y - y1 - m * (p.x - x1) < 7) && (!(p.x < minX || p.x > maxX || p.y < minY || p.y > maxY)))
		return 1;
	return 0;
}