#pragma once


// CWLSpectrumView view


#include "baseplotview.h"

class CWLSpectrumView : public CBasePlotView
{
	DECLARE_DYNCREATE(CWLSpectrumView)

protected:
	//CWLSpectrumView();           // protected constructor used by dynamic creation
	virtual ~CWLSpectrumView();

public:
	CWLSpectrumView();
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
	void OnUpdate(CView* pSender, LPARAM lHint, CObject*pHint);
};


