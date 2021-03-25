#pragma once
#include "MyLine.h"

class MyPen :public MyLine {
public:
	MyPen();

	MyPen(int x1, int y1);

	MyPen(int x1, int y1, int thin, COLORREF color);

	CPoint lastP();

	void Build(CPoint cur);		//pushing points to vector<CPoint> pArr

	void Draw(CDC *dc);

	bool isEx(CPoint p);

protected:
	vector <CPoint> pArr;
};