// PropertiesPane.cpp : implementation file
//

#include "stdafx.h"
#include "ArraySpectrum.h"
#include "PropertiesPane.h"


// CPropertiesPane

IMPLEMENT_DYNAMIC(CPropertiesPane, CDockablePane)

CPropertiesPane::CPropertiesPane()
{

}

CPropertiesPane::~CPropertiesPane()
{
}


BEGIN_MESSAGE_MAP(CPropertiesPane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CPropertiesPane message handlers




int CPropertiesPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	
	if(!m_PropertiesPaneDlg.Create(IDD_PROPERTIESPANEDLG,this))
	{
      AfxMessageBox(_T("Properties Screen creation failed"));
	}
	

	
	return 0;
}

void CPropertiesPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
    
	// TODO: Add your message handler code here
	m_PropertiesPaneDlg.MoveWindow(0,0,cx,cy);

}
