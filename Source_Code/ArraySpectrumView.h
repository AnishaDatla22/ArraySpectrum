// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// ArraySpectrumView.h : interface of the CArraySpectrumView class
//


#pragma once

#include "ArraySpectrumDoc.h"

#include "TChart.h"
#include "baseplotview.h"


class CArraySpectrumView : public CBasePlotView
{
protected: // create from serialization only
	//CArraySpectrumView();
	DECLARE_DYNCREATE(CArraySpectrumView)

// Attributes
public:
	CArraySpectrumView();
	CArraySpectrumDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);


public:
	virtual ~CArraySpectrumView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

;
// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
public:
	
};

#ifndef _DEBUG  // debug version in ArraySpectrumView.cpp
inline CArraySpectrumDoc* CArraySpectrumView::GetDocument() const
   { return reinterpret_cast<CArraySpectrumDoc*>(m_pDocument); }
#endif

