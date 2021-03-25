#include "stdafx.h"
#include "MyPen.h"


MyPen::MyPen() {}

MyPen::MyPen(int x1, int y1)
	:MyLine(x1, y1, x1, y1)
{
	CPoint p(x1, y1);
	pArr.push_back(p);
	style = 5;
}

MyPen::MyPen(int x1, int y1, int thin, COLORREF color)
	:MyLine(x1, y1, x1, y1, thin, color)
{
	CPoint p(x1, y1);
	pArr.push_back(p);
	style = 5;
}

CPoint MyPen::lastP()
{
	return pArr[pArr.size() - 1];
}

void MyPen::Build(CPoint cur)
{
	pArr.push_back(cur);
}

void MyPen::Draw(CDC *dc)
{
	CPen myPen(PS_SOLID, isThin ? 1 : 4, bgColor);
	for (int i = 1; i < pArr.size(); i++)
	{
		dc->SelectObject(myPen);
		dc->MoveTo(pArr[i - 1]);
		dc->LineTo(pArr[i]);
	}
}

bool MyPen::isEx(CPoint p) { return 0; }
