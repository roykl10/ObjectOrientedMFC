#pragma once
#include "afxwin.h"
#include <vector>
using namespace std;

class Shapes :public CObject {
public:
	COLORREF bgColor;

	int isFill, isThin;
	int x1, y1, x2, y2, style;         //style will contain the Enum of the shape

	Shapes(); //default constructor

	Shapes(int a1, int b1, int a2, int b2); //extanded ctor

	Shapes(int a1, int b1, int a2, int b2, int fill, int thin, int color); //more extanded ctor

	void SetColor(COLORREF newColor);

	virtual int getMinX()
	{
		if (x1 < x2)
			return x1;
		return x2;
	}

	virtual int getMaxX()
	{
		if (x1 < x2)
			return x2;
		return x1;
	}

	virtual int getMinY()
	{
		if (y1 < y2)
			return y1;
		return y2;
	}

	virtual int getMaxY()
	{
		if (y1 < y2)
			return y2;
		return y1;
	}

	virtual void Build(CPoint cur) {}

	virtual CPoint lastP()
	{
		CPoint p(0, 0);
		return p;
	}

	virtual void Draw(CDC *dc) = 0;

	virtual bool isEx(CPoint p) = 0;

	virtual ~Shapes(void);
};
