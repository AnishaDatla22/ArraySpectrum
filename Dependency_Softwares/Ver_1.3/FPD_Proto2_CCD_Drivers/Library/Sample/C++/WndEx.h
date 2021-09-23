// WndEx.h: CWndEx
//
//////////////////////////////////////////////////////////////////////////////
#pragma once

//#include "DCamLIBApp.h"

//============================================================================
// CWndEx 
//============================================================================
class CWndEx : public CWnd
{
	//DECLARE_DYNAMIC(CWndEx)

public:
	CWndEx();
	virtual ~CWndEx();
	
	afx_msg void  OnShowWindow();

protected:
	DECLARE_MESSAGE_MAP()

protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};


