#pragma once

#include "dataview.h"
#include "capturepixels.h"
// CWLDataView view


class CWLDataView : public CDataView
{
	DECLARE_DYNCREATE(CWLDataView)

protected:
	CWLDataView();           // protected constructor used by dynamic creation
	virtual ~CWLDataView();
 
public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
//This is the array used to refer WL numbers converted from Pixel numbers
   // double *m_bufXDataPoints;//[MAX_PIXEL_DATA_COUNT_PER_LINE];
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
};


