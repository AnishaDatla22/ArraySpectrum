// CustomSplitterWnd.cpp : implementation file
//

#include "stdafx.h"
#include "ArraySpectrum.h"
#include "CustomSplitterWnd.h"


// CCustomSplitterWnd

IMPLEMENT_DYNAMIC(CCustomSplitterWnd, CSplitterWnd)

CCustomSplitterWnd::CCustomSplitterWnd()
{

}

CCustomSplitterWnd::~CCustomSplitterWnd()
{
}



BEGIN_MESSAGE_MAP(CCustomSplitterWnd, CSplitterWnd)
END_MESSAGE_MAP()



// CCustomSplitterWnd message handlers



BOOL CCustomSplitterWnd::Create(CWnd* pParentWnd, int nMaxRows, int nMaxCols, SIZE sizeMin, CCreateContext* pContext, DWORD dwStyle , UINT nID)
{
	// TODO: Add your specialized code here and/or call the base class

	//The following Protected members of the CSplitterWnd must be initialized as below before creating 
	//the splitter again using the same splitterWnd Object.
    m_nRows=0;
	m_nCols=0;
	if(m_pColInfo)
		delete m_pColInfo;
	if(m_pRowInfo)
		delete m_pRowInfo;
	m_pColInfo=NULL;
	m_pRowInfo=NULL;
	////
	return CSplitterWnd::Create(pParentWnd, nMaxRows, nMaxCols, sizeMin, pContext, dwStyle, nID);
}

BOOL CCustomSplitterWnd::CreateStatic(CWnd* pParentWnd, int nRows, int nCols, DWORD dwStyle,UINT nID)
{
	// TODO: Add your specialized code here and/or call the base class
	//The following Protected members of the CSplitterWnd must be initialized as below before creating 
	//the splitter again using the same splitterWnd Object.
    m_nRows=0;
	m_nCols=0;
	if(m_pColInfo)
		delete m_pColInfo;
	if(m_pRowInfo)
		delete m_pRowInfo;
	m_pColInfo=NULL;
	m_pRowInfo=NULL;
	return CSplitterWnd::CreateStatic(pParentWnd, nRows, nCols, dwStyle, nID);
}
