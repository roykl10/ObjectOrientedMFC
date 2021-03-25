
// PaintBGDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PaintBG.h"
#include "PaintBGDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////
// CPaintBGDlg dialog

CPaintBGDlg::CPaintBGDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPaintBGDlg::IDD, pParent)
	, isFill(FALSE), isThin(FALSE)
{
	shapeType=RECTANGLE;
	curColor=RGB(0,0,0);
	isPressed=false;
	index=iMax=0;

	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

CPaintBGDlg::~CPaintBGDlg()
{
	int size=myShapes.size();
	for(int i=0;i<size;i++)
		myShapes.erase(myShapes.begin());
}

void CPaintBGDlg::ClearScreen() 
{
	myShapes.clear(); //vector method
	moves.delAll(); //UndoRedo type object - deletes undo,redo stacks
	undo.EnableWindow(0);
	redoPic.EnableWindow(0);
	Invalidate();
}

void CPaintBGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Check(pDX, IDC_CHECK1, isFill);
	DDX_Check(pDX, IDC_CHECK2, isThin);
	DDX_Control(pDX, IDC_BUTTON1, RecPic);
	DDX_Control(pDX, IDC_BUTTON2, ElipPic);
	DDX_Control(pDX, IDC_BUTTON3, TraPic);
	DDX_Control(pDX, IDC_BUTTON4, TrapPic);
	DDX_Control(pDX, IDC_BUTTON5, LinePic);
	DDX_Control(pDX, IDC_BUTTON6, PenPic);
	DDX_Control(pDX, IDC_BUTTON7, MovePic);
	DDX_Control(pDX, IDC_BUTTON8, FillPic);
	DDX_Control(pDX, IDC_BUTTON9, ColorPic);
	DDX_Control(pDX, IDC_BUTTON10, redoPic);
	DDX_Control(pDX, IDC_BUTTON11, undo);
}

BEGIN_MESSAGE_MAP(CPaintBGDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	
	ON_BN_CLICKED(IDC_BUTTON1, &CPaintBGDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPaintBGDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CPaintBGDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CPaintBGDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CPaintBGDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CPaintBGDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CPaintBGDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CPaintBGDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_CHECK1, &CPaintBGDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CPaintBGDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_NEW, &CPaintBGDlg::OnBnClickedNew)
	ON_BN_CLICKED(IDC_BUTTON10, &CPaintBGDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CPaintBGDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON9, &CPaintBGDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_SAVE, &CPaintBGDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_LOAD, &CPaintBGDlg::OnBnClickedLoad)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////
// CPaintBGDlg message handlers

BOOL CPaintBGDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		//BOOL bNameValid;
		CString strAboutMenu;
		//bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		//ASSERT(bNameValid);
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// loading bmp imgs to btns values
	RecPic.SetBitmap(LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP1)));
	ElipPic.SetBitmap(LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP2)));
	TraPic.SetBitmap(LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP3)));
	TrapPic.SetBitmap(LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP4)));
	LinePic.SetBitmap(LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP5)));
	PenPic.SetBitmap(LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP6)));
	MovePic.SetBitmap(LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP7)));
	FillPic.SetBitmap(LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP8)));
	ColorPic.SetBitmap(LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP9)));
	redoPic.SetBitmap(LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP10)));
	undo.SetBitmap(LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP11)));
	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPaintBGDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPaintBGDlg::OnPaint()
{
	int curIndex = myShapes.size();
	CPaintDC dc (this);
	for(int i=0; i<curIndex; i++)
		myShapes[i]->Draw(&dc);
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPaintBGDlg::OnQueryDragIcon()
{
	//return <HCURSOR>(m_hIcon);
	return static_cast<HCURSOR>(m_hIcon);
}


int ExIndex = -1; // !!!!!

void CPaintBGDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int curIndex = myShapes.size();
	endP=startP=point;
	isPressed=true;
	switch(shapeType) //enum type
	{
	case PEN:
		myShapes.push_back(new MyPen(startP.x,startP.y,isThin,curColor));
		moves.move(new MyPen(startP.x,startP.y,isThin,curColor));//pushes to undo-stack
		break;
	
	case CHANGE_COLOR:
		{
			for (int i=0; i<curIndex; i++)
			if(myShapes[i]->isEx(point)) //if shape exist
			{
				myShapes[i]->SetColor(curColor); //changes its color
				Invalidate();
			}
			CClientDC dc(this);
			COLORREF c=curColor;
		}
		break;

	case MOVE_OBJECT:
		for (int i=0; i<curIndex; i++)
			if(myShapes[i]->isEx(point))
			{
				ExIndex = i;
			}
		break;
	}
	if (curIndex < myShapes.size())//if created new shape, cant redo it, only undo.
		redoPic.EnableWindow(0);

	CDialog::OnLButtonDown(nFlags, point);
}

void CPaintBGDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if(isPressed)
	{
		int curIndex = myShapes.size();
		CClientDC dc(this);
		CBrush myBrush,*oldBrush;
		if (isFill)
		{
			myBrush.CreateSolidBrush(curColor);		// fill figure color
			oldBrush=dc.SelectObject( &myBrush );
		}
		dc.SetROP2(R2_NOTXORPEN);

		CPen myPen1(PS_SOLID, isThin?1:4, curColor);		// outside line figure color
		CPen *oldPen;
		oldPen=dc.SelectObject( &myPen1 ); 

		switch(shapeType)
		{
		case RECTANGLE:
			dc.Rectangle(startP.x, startP.y,endP.x, endP.y);//while moving creating temporary shape untill mouse-up
			endP=point;
			dc.Rectangle(startP.x, startP.y,endP.x, endP.y);
			undo.EnableWindow(1);
			break;
		case ELLIPSE:
			dc.Ellipse(startP.x, startP.y,endP.x, endP.y);
			endP=point;
			dc.Ellipse(startP.x, startP.y,endP.x, endP.y);
			undo.EnableWindow(1);
			break;
		case TRIANGLE:
			dc.MoveTo(startP.x,endP.y);
			dc.LineTo(endP.x,endP.y);
			dc.LineTo((startP.x + endP.x)/2,startP.y);
			dc.LineTo(startP.x,endP.y);
			endP=point;
			dc.MoveTo(startP.x,endP.y);
			dc.LineTo(endP.x,endP.y);
			dc.LineTo((startP.x + endP.x)/2,startP.y);
			dc.LineTo(startP.x,endP.y);
			undo.EnableWindow(1);
			break;
		case TRAPEZE:
			dc.MoveTo(startP.x,endP.y);
			dc.LineTo(endP.x,endP.y);
			dc.LineTo((endP.x-startP.x)*3/4+startP.x,startP.y);
			dc.LineTo((endP.x-startP.x)*1/4+startP.x,startP.y);
			dc.LineTo(startP.x,endP.y);
			endP=point;
			dc.MoveTo(startP.x,endP.y);
			dc.LineTo(endP.x,endP.y);
			dc.LineTo((endP.x-startP.x)*3/4+startP.x,startP.y);
			dc.LineTo((endP.x-startP.x)*1/4+startP.x,startP.y);
			dc.LineTo(startP.x,endP.y);
			undo.EnableWindow(1);
			break;
		case LINE:
			dc.MoveTo(startP.x,startP.y);
			dc.LineTo(endP.x,endP.y);
			endP=point;
			dc.MoveTo(startP.x,startP.y);
			dc.LineTo(endP.x,endP.y);
			undo.EnableWindow(1);
			break;
		case PEN:
			myShapes[curIndex-1]->Build(point);
			dc.MoveTo(myShapes[curIndex-1]->lastP());
			dc.LineTo(endP.x,endP.y);
			endP=point;
			dc.MoveTo(myShapes[curIndex-1]->lastP());
			dc.LineTo(endP.x,endP.y);
			undo.EnableWindow(1);
			break;

		case MOVE_OBJECT: //repaints object while and after moving them
			if (ExIndex != -1)
			{
				//x1,x2,y1,y2 public members of Shapes.h
				myShapes[ExIndex]->Draw(&dc);
				myShapes[ExIndex]->x2 += endP.x - myShapes[ExIndex]->x1;
				myShapes[ExIndex]->y2 += endP.y - myShapes[ExIndex]->y1;
				myShapes[ExIndex]->x1 = endP.x;
				myShapes[ExIndex]->y1 = endP.y;
				endP=point;
				myShapes[ExIndex]->Draw(&dc);
			}
			break;
		}

	}
	CDialog::OnMouseMove(nFlags, point);
}

void CPaintBGDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	int curIndex = myShapes.size();
	if(isPressed)
	{
		endP=point;
		isPressed=false;
		if (endP != startP) //if shape was even created
		{
			switch(shapeType) //enum type SHAPES
			{
			case RECTANGLE:
				myShapes.push_back(new MyRectangle(startP.x,startP.y,endP.x,endP.y,isFill,isThin,curColor));
				moves.move(new MyRectangle(startP.x,startP.y,endP.x,endP.y,isFill,isThin,curColor));//move -> pushes to undo-stack
				Invalidate();
				break;
			case ELLIPSE:
				myShapes.push_back(new MyEllipse(startP.x,startP.y,endP.x,endP.y,isFill,isThin,curColor));
				moves.move(new MyEllipse(startP.x,startP.y,endP.x,endP.y,isFill,isThin,curColor));
				Invalidate();
				break;
			case TRIANGLE:
				myShapes.push_back(new MyTriangle(startP.x,startP.y,endP.x,endP.y,isFill,isThin,curColor));
				moves.move(new MyTriangle(startP.x,startP.y,endP.x,endP.y,isFill,isThin,curColor));
				Invalidate();
				break;
			case TRAPEZE:
				myShapes.push_back(new MyTrapeze(startP.x,startP.y,endP.x,endP.y,isFill,isThin,curColor));
				moves.move(new MyTrapeze(startP.x,startP.y,endP.x,endP.y,isFill,isThin,curColor));
				Invalidate();
				break;
			case LINE:
				myShapes.push_back(new MyLine(startP.x,startP.y,endP.x,endP.y,isThin,curColor));
				moves.move(new MyLine(startP.x,startP.y,endP.x,endP.y,isThin,curColor));
				Invalidate();
				break;
			case PEN:
				
				Invalidate();
				break;
			case MOVE_OBJECT:
				if (ExIndex != -1)
				{
					ExIndex = -1;
					Invalidate();
				}
				break;
			}
		}
		if (curIndex < myShapes.size())
			redoPic.EnableWindow(0);
	}

	CDialog::OnLButtonUp(nFlags, point);
}

void CPaintBGDlg::OnBnClickedButton1() //rectangle
{
	shapeType=RECTANGLE;
}

void CPaintBGDlg::OnBnClickedButton2() //ellipse
{
	shapeType=ELLIPSE;
}

void CPaintBGDlg::OnBnClickedButton3() //triangle
{
	shapeType=TRIANGLE;
}

void CPaintBGDlg::OnBnClickedButton4() //trapeze
{
	shapeType=TRAPEZE;
}

void CPaintBGDlg::OnBnClickedButton5() //line
{
	shapeType=LINE;
}

void CPaintBGDlg::OnBnClickedButton6() //pen
{
	shapeType=PEN;
}

void CPaintBGDlg::OnBnClickedButton7() //move
{
	shapeType=MOVE_OBJECT;
}

void CPaintBGDlg::OnBnClickedButton8() //choose color
{
	shapeType=CHANGE_COLOR;
}


void CPaintBGDlg::OnBnClickedCheck1() //fill checkbox
{
	UpdateData(true); //must in checkbox
}


void CPaintBGDlg::OnBnClickedCheck2() //thin checkbox
{
	UpdateData(true); //must in checkbox
}

void CPaintBGDlg::OnBnClickedNew() //clear window
{
	this->ClearScreen();
}

void CPaintBGDlg::OnBnClickedButton10() //redo
{
	myShapes = moves.Redo();
	undo.EnableWindow(1);
	Invalidate();
}

void CPaintBGDlg::OnBnClickedButton11() //undo
{
	myShapes = moves.Undo();
	if(myShapes.empty())
		undo.EnableWindow(0);
	redoPic.EnableWindow(1);
	Invalidate();
}


void CPaintBGDlg::OnBnClickedButton9() //color
{
	CColorDialog dlg; 
	if (dlg.DoModal() == IDOK) 
		curColor = dlg.GetColor();
}

void CPaintBGDlg::OnBnClickedSave()   //outputs to file (save)
{
	CFile file(_T("SavedShapes.$$"), CFile::modeWrite);
	CArchive ar (&file, CArchive::store);
	int ct=myShapes.size(); // logical size of array
	ar<<ct; //saves size to beginning of file

	//saves values of each shape to file
	for(int i=0;i<ct;i++)
	{
		ar << myShapes[i]->style;
		ar << myShapes[i]->isFill;
		ar << myShapes[i]->isThin;
		ar << myShapes[i]->bgColor;
		ar << myShapes[i]->x1;
		ar << myShapes[i]->y1;
		ar << myShapes[i]->x2;
		ar << myShapes[i]->y2;
	}
	ar.Close();
	file.Close();
	//dont forget to close
}

void CPaintBGDlg::OnBnClickedLoad()  //serialize - input from file (load)
{
	CFile file(_T("SavedShapes.$$"), CFile::modeRead);
	CArchive ar (&file, CArchive::load);
	myShapes.clear(); //deleting previous shapes in vector
	index = iMax = 0; //reseting index's
	int ct;
	CPen p;
	COLORREF color;
	ar>>ct; //gets the size from beginning of file
	int x1,x2,y1,y2,Fill,Thin,style; //new parameters to copy values into

	for (int i=0; i < ct ; i++)
	{
		//paramaters of each object saved before
		ar >> style;
		ar >> Fill;
		ar >> Thin;
		ar >> color;
		ar >> x1;
		ar >> y1;
		ar >> x2;
		ar >> y2;

		switch(style) //creating new object based on style and giving the parameters from file input
		{
		case 0:
			myShapes.push_back( new MyRectangle(x1,y1,x2,y2,Fill,Thin,color) );
			break;
		case 1:
			myShapes.push_back( new MyEllipse(x1,y1,x2,y2,Fill,Thin,color) ); 
			break;
		case 2:
			myShapes.push_back( new MyTriangle(x1,y1,x2,y2,Fill,Thin,color) ); 
			break;
		case 3:
			myShapes.push_back( new MyTrapeze(x1,y1,x2,y2,Fill,Thin,color) ); 
			break;
		case 4:
			myShapes.push_back( new MyLine(x1,y1,x2,y2,Thin,color) ); 
			break;
		case 5:
			myShapes.push_back( new MyPen(x1,y1,Thin,color) ); 
			break;
			index++;
		}
	}
	ar.Close();
	file.Close();
	Invalidate();
	//dont forget to close
}

