#include "stdafx.h"
#include "MyEllipse.h"

MyEllipse::MyEllipse() {}

MyEllipse::MyEllipse(int a1, int b1, int a2, int b2)
	:Shapes(a1, b1, a2, b2)
{
	style = 1;
}

MyEllipse::MyEllipse(int a1, int b1, int a2, int b2, int fill, int thin, COLORREF color)
	: Shapes(a1, b1, a2, b2, fill, thin, color)
{
	style = 1;
}

void MyEllipse::Draw(CDC *dc)
{
	CBrush myBrush;
	CPen myPen(PS_SOLID, isThin ? 1 : 4, bgColor);
	dc->SelectObject(&myPen);
	if (isFill)
		myBrush.CreateSolidBrush(bgColor);
	else
		myBrush.CreateSolidBrush(RGB(240, 240, 240));
	dc->SelectObject(myBrush);
	dc->Ellipse(x1, y1, x2, y2);
}

bool MyEllipse::isEx(CPoint p)
{
	if (p.x > x1 && p.x < x2 && p.y > y1 && p.y < y2)
		return 1;
	return 0;
}