#include "stdafx.h"
#include "MyTriangle.h"


MyTriangle::MyTriangle()
{
}

MyTriangle::MyTriangle(int a1, int b1, int a2, int b2)
	:Shapes(a1, b1, a2, b2)
{
	style = 2;
}

MyTriangle::MyTriangle(int a1, int b1, int a2, int b2, int fill, int thin, COLORREF color)
	:Shapes(a1, b1, a2, b2, fill, thin, color)
{
	style = 2;
}

void MyTriangle::Draw(CDC *dc)
{
	CPoint pt[3];
	pt[0].SetPoint(x1, y2);
	pt[1].SetPoint(x2, y2);
	pt[2].SetPoint((x1 + x2) / 2, y1);

	CBrush myBrush;
	CPen myPen(PS_SOLID, isThin ? 1 : 4, bgColor);
	dc->SelectObject(&myPen);
	if (isFill)
		myBrush.CreateSolidBrush(bgColor);
	else
		myBrush.CreateSolidBrush(RGB(240, 240, 240));
	dc->SelectObject(myBrush);
	dc->Polygon(pt, 3);
}

bool MyTriangle::isEx(CPoint p)
{
	int minX = getMinX(), maxX = getMaxX(), minY = getMinY(), maxY = getMaxY();
	if (!(p.x < minX || p.x > maxX || p.y < minY || p.y > maxY))
		return 1;
	return 0;
}
