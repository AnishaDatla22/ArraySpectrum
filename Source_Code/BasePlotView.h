#pragma once

#include "ArraySpectrumDoc.h"
#import "Dependencies/TeeChart8.ocx" no_namespace rename("LoadImage","TcLoadImage")rename("TextOut","TcTextOut")
//#include "TChart.h"
#include "EsdAdvancedGraphControl.h"
#import "EsdAdvancedGraphControl.tlb" no_namespace

// CBasePlotView view

class CBasePlotView : public CView
{
	DECLARE_DYNCREATE(CBasePlotView)
   

// Attributes
public:
	CArraySpectrumDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
	void InitializeGraphCtrl();
public:
	CBasePlotView();
	virtual ~CBasePlotView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int m_nSeriesIndex;
public:
   
	ITChart *  m_TChartPtr;
	ILegend* m_LegendPtr;
	//CTChart m_objGraphCtrl;
	CDEsdAdvancedGraphControl m_objGraphCtrl;
	
	BOOL m_bShowLegends;
	CString m_strPlotTilte;
	CString m_strXAxisTitle;
	CString m_strYAxisTitle;
	int m_nYMax;
	int m_nXMax;
	double * m_bufXDataPoints;//[MAX_PIXEL_DATA_COUNT_PER_LINE];
	///
	int m_nPeakGraphID;
	///
	//stEventInfo *m_ptrEvents;
	///
	LONG m_lngPeakCount;
	///
	double* m_ptrdblHeight;
	///
	double* m_ptrdblWidth;
	///
	double* m_ptrdblArea;
	///
	long* m_ptrlngStart;
	///
	long* m_ptrlngMax;
	///
	long* m_ptrlngEnd;
	///
	double m_dblheightReject;
	///
	bool m_bShowPeaks;

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();

public:
	// Clear All Series in the Graph
	void ClearGraph(void);
	
	// Add a new Series with the given X and Y Point buffers
	void AddSeries(double * pBufXPoints, double * pBufYPoints, long nPointCount,COLORREF color,CString strSeriesTitle);
	
	// Delete a Given indexed series
	void DeleteSeries(void);
	
	// Show a Given indexed Series in Highlighted Color
	void HighLightSeries(int nSeriesIndex);
	// Update the Series data with the given SeriesID
	void UpdateSeries(long nSeriesID, double* pBufXData, double* pBufYData, long nPointCount,COLORREF rgbColor);

	void OnTChartMouseMove(long Shift, long X, long Y);
	
	void OnZoom();
protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject*pHint);

public:
	void fncCleanPeakInformation();

	void fncGetPeakInformation(int nGraphIndex);
	
	void SetPeakGraphID(int nGraphID);
	///
	void CalculateCompoundArea();
	///
	void ShowPeaks();
	///
	LRESULT OnCalcualteArea(WPARAM wp,LPARAM lp);

	DECLARE_EVENTSINK_MAP()

};

#ifndef _DEBUG  // debug version in ArraySpectrumView.cpp
inline CArraySpectrumDoc* CBasePlotView::GetDocument() const
   { return reinterpret_cast<CArraySpectrumDoc*>(m_pDocument); }
#endif


