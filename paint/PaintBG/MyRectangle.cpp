#include "stdafx.h"
#include "MyRectangle.h"


MyRectangle::MyRectangle() {}

MyRectangle::MyRectangle(int a1, int b1, int a2, int b2)
	:Shapes(a1, b1, a2, b2)
{
	style = 0;
}

MyRectangle::MyRectangle(int a1, int b1, int a2, int b2, int fill, int thin, COLORREF color)
	: Shapes(a1, b1, a2, b2, fill, thin, color)
{
	style = 0;
}

void MyRectangle::Draw(CDC *dc)
{
	CBrush myBrush;
	CPen myPen(PS_SOLID, isThin ? 1 : 4, bgColor);
	dc->SelectObject(&myPen);
	if (isFill)
		myBrush.CreateSolidBrush(bgColor); //if fill checkbox is marked
	else
		myBrush.CreateSolidBrush(RGB(240, 240, 240)); //if not, create the window color
	dc->SelectObject(myBrush);
	dc->Rectangle(x1, y1, x2, y2); //draws rectangle with the extra parameters (color,boldness)
}

//if the shape exists
bool MyRectangle::isEx(CPoint p)
{
	int minX = getMinX(), maxX = getMaxX(), minY = getMinY(), maxY = getMaxY();
	if (!(p.x < minX || p.x > maxX || p.y < minY || p.y > maxY))
		return 1;
	return 0;
}
