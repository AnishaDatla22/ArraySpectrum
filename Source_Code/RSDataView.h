#pragma once

#include "dataview.h"
#include "capturepixels.h"
// CRSDataView view


class CRSDataView : public CDataView
{
	DECLARE_DYNCREATE(CRSDataView)

protected:
	CRSDataView();           // protected constructor used by dynamic creation
	virtual ~CRSDataView();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
	//This is the array used to refer RS numbers converted from Pixel numbers
	   // double *m_bufXDataPoints;//[MAX_PIXEL_DATA_COUNT_PER_LINE];
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
};


#pragma once
