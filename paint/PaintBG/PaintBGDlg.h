
/* 
Assigned by
Idan Rokach - 318853694
Roy Kliger - 315963880
*/

// PaintBGDlg.h : header file
//
#if !defined(AFX_PaintBGDlg_H__D02F91E6_1066_4AA4_AE0B_1D16C986AE2C__INCLUDED_)
#define AFX_PaintBGDlg_H__D02F91E6_1066_4AA4_AE0B_1D16C986AE2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "afxwin.h"
#include <vector>
#include "Shapes.h"
#include "MyRectangle.h"
#include "MyEllipse.h"
#include "MyTriangle.h"
#include "MyTrapeze.h"
#include "MyLine.h"
#include "MyPen.h"
#include "UndoRedo.h"

using namespace std;

// CPaintBGDlg dialog
class CPaintBGDlg : public CDialogEx
{
// Construction
public:
	CPaintBGDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PAINTBG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	enum SHAPES{RECTANGLE,ELLIPSE,TRIANGLE,TRAPEZE,LINE,PEN,MOVE_OBJECT,CHANGE_COLOR};

	vector <Shapes*> myShapes; //array of shapes

	void ClearScreen();
	~CPaintBGDlg();

private:
	//using for PaintBGDlg.cpp
	SHAPES shapeType; //enum type
    COLORREF curColor;
	int index, iMax;
	UndoRedo moves;
	bool isPressed;
	CPoint startP;
	CPoint endP;

public:
	//btn values
	CButton RecPic;
	CButton ElipPic;
	CButton TraPic;
	CButton TrapPic;
	CButton LinePic;
	CButton PenPic;
	CButton MovePic;
	CButton FillPic;
	CButton ColorPic;
	CButton redoPic; //redo
	CButton undo; //undo
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedNew();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();
	BOOL isFill;
	BOOL isThin;
};

#endif