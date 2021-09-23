#pragma once

#include "PropertiesPaneDlg.h"
// CPropertiesPaneView view

class CPropertiesPaneView : public CView
{
	DECLARE_DYNCREATE(CPropertiesPaneView)

public:
	CPropertiesPaneView();           // protected constructor used by dynamic creation
	virtual ~CPropertiesPaneView();
public:
	//CPropertiesPaneDlg m_PropertiesPaneDlg;
public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


