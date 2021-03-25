#include "stdafx.h"
#include "MyTrapeze.h"


MyTrapeze::MyTrapeze() {}

MyTrapeze::MyTrapeze(int a1, int b1, int a2, int b2)
	:MyRectangle(a1, b1, a2, b2)
{
	style = 3;
}

MyTrapeze::MyTrapeze(int a1, int b1, int a2, int b2, int fill, int thin, COLORREF color)
	: MyRectangle(a1, b1, a2, b2, fill, thin, color)
{
	style = 3;
}

void MyTrapeze::Draw(CDC *dc)
{
	CPoint pt[4];
	pt[0].SetPoint(x1, y2);
	pt[1].SetPoint(x2, y2);
	pt[2].SetPoint((x2 - x1) * 3 / 4 + x1, y1);
	pt[3].SetPoint((x2 - x1) * 1 / 4 + x1, y1);

	CBrush myBrush;
	CPen myPen(PS_SOLID, isThin ? 1 : 4, bgColor);
	dc->SelectObject(&myPen);
	if (isFill)
		myBrush.CreateSolidBrush(bgColor);
	else
		myBrush.CreateSolidBrush(RGB(240, 240, 240));
	dc->SelectObject(myBrush);
	dc->Polygon(pt, 4);				 //getting points makigng polygon 
}

bool MyTrapeze::isEx(CPoint p)
{
	int minX = getMinX(), maxX = getMaxX(), minY = getMinY(), maxY = getMaxY();
	if (!(p.x < minX || p.x > maxX || p.y < minY || p.y > maxY))
		return 1;
	return 0;
}