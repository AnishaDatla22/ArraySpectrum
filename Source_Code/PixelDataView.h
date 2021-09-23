#pragma once
#include "dataview.h"

// CPixelDataView view

class CPixelDataView : public CDataView
{
	DECLARE_DYNCREATE(CPixelDataView)

protected:
	CPixelDataView();           // protected constructor used by dynamic creation
	virtual ~CPixelDataView();
	void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
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


