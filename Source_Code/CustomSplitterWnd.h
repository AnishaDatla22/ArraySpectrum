#pragma once


// CCustomSplitterWnd

class CCustomSplitterWnd : public CSplitterWnd
{
	DECLARE_DYNAMIC(CCustomSplitterWnd)

public:
	CCustomSplitterWnd();
	virtual ~CCustomSplitterWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(CWnd* pParentWnd, int nMaxRows, int nMaxCols, SIZE sizeMin, CCreateContext* pContext, DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | SPLS_DYNAMIC_SPLIT, UINT nID = AFX_IDW_PANE_FIRST);
	BOOL CreateStatic(CWnd* pParentWnd, int nRows, int nCols, DWORD dwStyle= WS_CHILD | WS_VISIBLE, UINT nID = AFX_IDW_PANE_FIRST);
};


