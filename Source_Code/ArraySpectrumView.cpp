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

// ArraySpectrumView.cpp : implementation of the CArraySpectrumView class
//

#include "stdafx.h"
#include "ArraySpectrum.h"

#include "ArraySpectrumDoc.h"
#include "ArraySpectrumView.h"
#include "constants.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CArraySpectrumView

IMPLEMENT_DYNCREATE(CArraySpectrumView, CBasePlotView)

BEGIN_MESSAGE_MAP(CArraySpectrumView, CBasePlotView)
	// Standard printing commands
	/*ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CArraySpectrumView::OnFilePrintPreview)
	
	ON_WM_SIZE()
	ON_WM_DESTROY()*/
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CArraySpectrumView construction/destruction

CArraySpectrumView::CArraySpectrumView()
{
	// TODO: add construction code here
	//m_pChartCtrl=NULL;
	
	m_strPlotTilte=_T("Pixel Plot");
	m_strXAxisTitle=_T("Pixels");
#ifdef _SA165
	m_strYAxisTitle=_T("Voltage(mv)");
#else
	m_strYAxisTitle=_T("ADU");
#endif
	m_nYMax=2000; //def Y Max
	//Fill X indices (i.e the Pixel Numbers to be marked on X-Axis)
	m_bufXDataPoints= new double[MAX_PIXEL_DATA_COUNT_PER_LINE];
	for(int i=0;i<MAX_PIXEL_DATA_COUNT_PER_LINE;i++)
		m_bufXDataPoints[i]=i;

}

CArraySpectrumView::~CArraySpectrumView()
{
   delete [] m_bufXDataPoints;
}


// CArraySpectrumView drawing

void CArraySpectrumView::OnDraw(CDC* pDC)
{
	CArraySpectrumDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

}


// CArraySpectrumView printing


void CArraySpectrumView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CArraySpectrumView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CArraySpectrumView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CArraySpectrumView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CArraySpectrumView diagnostics

#ifdef _DEBUG
void CArraySpectrumView::AssertValid() const
{
	CView::AssertValid();
}

void CArraySpectrumView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CArraySpectrumDoc* CArraySpectrumView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CArraySpectrumDoc)));
	return (CArraySpectrumDoc*)m_pDocument;
}
#endif //_DEBUG


// CArraySpectrumView message handlers

int CArraySpectrumView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBasePlotView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
    return 0;
}


void CArraySpectrumView::OnUpdate(CView* pSender, LPARAM lHint, CObject*pHint)
{
	// TODO: Add your specialized code here and/or call the base class
	CArraySpectrumDoc* pDoc= (CArraySpectrumDoc*)GetDocument();
   
	BOOL bUpdateExistingSeries=lHint; //If true, don ot Add series, only update the existing seriees
	
	ClearGraph();
	
	//If no Pixel Data is Available, Do not do any thing
	if(pDoc->m_objCapturePixelBuff.ISEmpty()==FALSE)
	{   	
		BeginWaitCursor(); // display the hourglass cursor
		int nLineCount = pDoc->m_objCapturePixelBuff.m_nLineCount;
		int nSeriesCount = m_TChartPtr->GetSeriesCount();
		int i;
		for(i=0;i<nLineCount;i++)
		{
			double bufYData[MAX_PIXEL_DATA_COUNT_PER_LINE];
			for(int j=0;j<MAX_PIXEL_DATA_COUNT_PER_LINE;j++)
				bufYData[j]=pDoc->m_objCapturePixelBuff.m_pPixelLines[i][j];
			CString strTitle;
			strTitle.Format(_T("Line %2d"),i+1);
			if(bUpdateExistingSeries && nSeriesCount>0)
                UpdateSeries(i,m_bufXDataPoints,bufYData,MAX_PIXEL_DATA_COUNT_PER_LINE, PIXEL_LINE_COLOR);
			else
			    AddSeries(m_bufXDataPoints, bufYData, MAX_PIXEL_DATA_COUNT_PER_LINE, PIXEL_LINE_COLOR,strTitle);
		}
		
		if(pDoc->m_objCapturePixelBuff.m_bShowAvg)
		{
			double bufYData[MAX_PIXEL_DATA_COUNT_PER_LINE];
			for(int j=0;j<MAX_PIXEL_DATA_COUNT_PER_LINE;j++)
				bufYData[j]=pDoc->m_objCapturePixelBuff.m_pBufAvgPixelData[j];
			CString strTitle;
			strTitle.Format(_T("AVG"));
			if(bUpdateExistingSeries && nSeriesCount>0) 
                UpdateSeries(i,m_bufXDataPoints,bufYData,MAX_PIXEL_DATA_COUNT_PER_LINE,AVG_PIXEL_LINE_COLOR);
			else
			    AddSeries(m_bufXDataPoints,bufYData,MAX_PIXEL_DATA_COUNT_PER_LINE,AVG_PIXEL_LINE_COLOR, strTitle);

		}
		if(pDoc->m_objCapturePixelBuff.m_bShowSD && nLineCount >1)
		{
			double bufYData[MAX_PIXEL_DATA_COUNT_PER_LINE];
			for(int j=0;j<MAX_PIXEL_DATA_COUNT_PER_LINE;j++)
				bufYData[j]=pDoc->m_objCapturePixelBuff.m_pBufSDPixelData[j];
			CString strTitle;
			strTitle.Format(_T("SD"));
			if(bUpdateExistingSeries && nSeriesCount>0) 
                UpdateSeries(i+1,m_bufXDataPoints,bufYData,MAX_PIXEL_DATA_COUNT_PER_LINE,SD_PIXEL_LINE_COLOR);
			else
			    AddSeries(m_bufXDataPoints,bufYData,MAX_PIXEL_DATA_COUNT_PER_LINE,SD_PIXEL_LINE_COLOR, strTitle);

		}
		if(pDoc->m_objCapturePixelBuff.m_bShowRSD && nLineCount >1)
		{
			double bufYData[MAX_PIXEL_DATA_COUNT_PER_LINE];
			for(int j=0;j<MAX_PIXEL_DATA_COUNT_PER_LINE;j++)
				bufYData[j]=pDoc->m_objCapturePixelBuff.m_pBufRSDPixelData[j];
			CString strTitle;
			strTitle.Format(_T("RSD"));
			if(bUpdateExistingSeries && nSeriesCount>0) 
                UpdateSeries(i+2,m_bufXDataPoints,bufYData,MAX_PIXEL_DATA_COUNT_PER_LINE,RSD_PIXEL_LINE_COLOR);
			else
			    AddSeries(m_bufXDataPoints,bufYData,MAX_PIXEL_DATA_COUNT_PER_LINE,RSD_PIXEL_LINE_COLOR, strTitle);

		}
		EndWaitCursor(); // remove the hourglass cursor
		//m_objGraphCtrl.Invalidate(TRUE);
		//<--1.3 call the baseplotview
		CBasePlotView::OnUpdate(pSender,lHint,pHint);
	}
}

