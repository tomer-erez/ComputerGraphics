// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "CGWork.h"

#include "MainFrm.h"
#include "Scene.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	ON_COMMAND(ID_OPTIONS_OBJECTCOLOR, &CMainFrame::OnObjectColor)

	ON_COMMAND(ID_OPTIONS_BACKGROUNDCOLOR, &CMainFrame::OnBackgroundColor)
	ON_COMMAND(ID_FOGEFFECTS_COLOR, &CMainFrame::OnFogColor)

	ON_COMMAND(ID_OPTIONS_VERTEXNORMALSCOLOR, &CMainFrame::OnVertexNormalsColor)
	ON_COMMAND(ID_OPTIONS_POLYGONNORMALSCOLOR, &CMainFrame::OnPolygonNormalsColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here

}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
			sizeof(indicators) / sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers



// Return by Reference the status bar. This is used so that ChildView can place 
// text at will.
CStatusBar& CMainFrame::getStatusBar() {
	return m_wndStatusBar;
}



void CMainFrame::OnObjectColor()
{
	CCGWorkApp* pApp = (CCGWorkApp*)AfxGetApp();
	// Create a color dialog with default options
	COLORREF initialColor = pApp->Object_color;
	CColorDialog colorDlg(initialColor);

	// Display the dialog and handle the user's choice
	if (colorDlg.DoModal() == IDOK)
	{
		// Get the selected color
		COLORREF selectedColor = colorDlg.GetColor();

		// Use the selected color (e.g., store it, apply it, etc.)
		pApp->Object_color = selectedColor;

	}
}


void CMainFrame::OnFogColor()
{
	CCGWorkApp* pApp = (CCGWorkApp*)AfxGetApp();
	COLORREF initialColor = pApp->fog_color;
	CColorDialog colorDlg(initialColor);

	// Display the dialog and handle the user's choice
	if (colorDlg.DoModal() == IDOK)
	{
		// Get the selected color
		COLORREF selectedColor = colorDlg.GetColor();

		// Use the selected color (e.g., store it, apply it, etc.)

		pApp->fog_color = selectedColor;

	}
}

void CMainFrame::OnBackgroundColor()
{
	CCGWorkApp* pApp = (CCGWorkApp*)AfxGetApp();
	COLORREF initialColor = pApp->Background_color;
	CColorDialog colorDlg(initialColor);

	// Display the dialog and handle the user's choice
	if (colorDlg.DoModal() == IDOK)
	{
		// Get the selected color
		COLORREF selectedColor = colorDlg.GetColor();

		// Use the selected color (e.g., store it, apply it, etc.)

		pApp->Background_color = selectedColor;

	}
}

void CMainFrame::OnVertexNormalsColor()
{
	CCGWorkApp* pApp = (CCGWorkApp*)AfxGetApp();
	COLORREF initialColor = pApp->vertex_normals_color;
	CColorDialog colorDlg(initialColor);

	// Display the dialog and handle the user's choice
	if (colorDlg.DoModal() == IDOK)
	{
		// Get the selected color
		COLORREF selectedColor = colorDlg.GetColor();

		// Use the selected color (e.g., store it, apply it, etc.)

		pApp->vertex_normals_color = selectedColor;

	}
}

void CMainFrame::OnPolygonNormalsColor()
{
	CCGWorkApp* pApp = (CCGWorkApp*)AfxGetApp();
	COLORREF initialColor = pApp->poly_normals_color;
	CColorDialog colorDlg(initialColor);

	// Display the dialog and handle the user's choice
	if (colorDlg.DoModal() == IDOK)
	{
		// Get the selected color
		COLORREF selectedColor = colorDlg.GetColor();

		// Use the selected color (e.g., store it, apply it, etc.)

		pApp->poly_normals_color = selectedColor;

	}
}