// PropertiesPaneView.cpp : implementation file
//

#include "stdafx.h"
#include "ArraySpectrum.h"
#include "PropertiesPaneView.h"


// CPropertiesPaneView

IMPLEMENT_DYNCREATE(CPropertiesPaneView, CView)

CPropertiesPaneView::CPropertiesPaneView()
{

}

CPropertiesPaneView::~CPropertiesPaneView()
{
}

BEGIN_MESSAGE_MAP(CPropertiesPaneView, CView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CPropertiesPaneView drawing

void CPropertiesPaneView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CPropertiesPaneView diagnostics

#ifdef _DEBUG
void CPropertiesPaneView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPropertiesPaneView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPropertiesPaneView message handlers

int CPropertiesPaneView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	
	//m_PropertiesPaneDlg.Create(_T("Dialog"),this);

	return 0;
}
