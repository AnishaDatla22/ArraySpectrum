#pragma once


// CRSSpectrumView view


#include "baseplotview.h"

class CRSSpectrumView : public CBasePlotView
{
	DECLARE_DYNCREATE(CRSSpectrumView)

protected:
	//CRSSpectrumView();           // protected constructor used by dynamic creation
	virtual ~CRSSpectrumView();

public:
	CRSSpectrumView();
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
	void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
};


#pragma once
