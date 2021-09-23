// WLSpectrumView.cpp : implementation file
//

#include "stdafx.h"
#include "ArraySpectrum.h"
#include "WLSpectrumView.h"
#include "constants.h"
#include "MainFrm.h"
// CWLSpectrumView

IMPLEMENT_DYNCREATE(CWLSpectrumView, CBasePlotView)

CWLSpectrumView::CWLSpectrumView()
{
    m_strPlotTilte=_T("WaveLength Plot");
	m_strXAxisTitle=_T("WaveLength (nm)");
#ifdef _SA165
	m_strYAxisTitle=_T("Voltage(mv)");
#else
	m_strYAxisTitle=_T("ADU");
#endif
	m_nYMax=2000; //def Y Max
	/*
	CArraySpectrumApp *pApp=(CArraySpectrumApp*)AfxGetApp();
	//fill the x-data points (WL) mapped to pixels based on Polynomial Co-Efficeints
	//m_bufXDataPoints= pApp->ConvertPixelNumbersToWL();
	m_bufXDataPoints= pApp->m_bufWLDataPoints;
	*/
	/*CArraySpectrumDoc* pDoc = NULL;
	pDoc = (CArraySpectrumDoc*)(GetDocument());
	if(pDoc != NULL)
		m_bufXDataPoints = pDoc->m_bufWLDataPoints;*/
}

CWLSpectrumView::~CWLSpectrumView()
{
}

BEGIN_MESSAGE_MAP(CWLSpectrumView, CBasePlotView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CWLSpectrumView drawing

void CWLSpectrumView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CWLSpectrumView diagnostics

#ifdef _DEBUG
void CWLSpectrumView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CWLSpectrumView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CWLSpectrumView message handlers

int CWLSpectrumView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBasePlotView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}

void CWLSpectrumView::OnUpdate(CView* pSender, LPARAM lHint, CObject*pHint)
{
	// TODO: Add your specialized code here and/or call the base class
	CArraySpectrumDoc* pDoc = (CArraySpectrumDoc*)GetDocument();
   
	BOOL bUpdateExistingSeries=lHint; //If true, don ot Add series, only update the existing seriees
	
	ClearGraph();
	
	//If no Pixel Data is Available, Do not do any thing
	if(pDoc->m_objCapturePixelBuff.ISEmpty()==FALSE)
	{   			
		int nLineCount=pDoc->m_objCapturePixelBuff.m_nLineCount;
		int nSeriesCount=m_TChartPtr->GetSeriesCount();
		int i;
		for(i=0;i<nLineCount;i++)
		{
			double bufYData[MAX_PIXEL_DATA_COUNT_PER_LINE];
			for(int j=0;j<MAX_PIXEL_DATA_COUNT_PER_LINE;j++)
				bufYData[j]=pDoc->m_objCapturePixelBuff.m_pPixelLines[i][j];
			CString strTitle;
			strTitle.Format(_T("Line %2d"),i+1);
			if(bUpdateExistingSeries && nSeriesCount>0)
                UpdateSeries(i,pDoc->m_bufWLDataPoints,bufYData,MAX_PIXEL_DATA_COUNT_PER_LINE, PIXEL_LINE_COLOR);
			else
			    AddSeries(pDoc->m_bufWLDataPoints, bufYData, MAX_PIXEL_DATA_COUNT_PER_LINE, PIXEL_LINE_COLOR,strTitle);
		}
		
		if(pDoc->m_objCapturePixelBuff.m_bShowAvg)
		{
			double bufYData[MAX_PIXEL_DATA_COUNT_PER_LINE];
			for(int j=0;j<MAX_PIXEL_DATA_COUNT_PER_LINE;j++)
				bufYData[j]=pDoc->m_objCapturePixelBuff.m_pBufAvgPixelData[j];
			CString strTitle;
			strTitle.Format(_T("AVG"));
			if(bUpdateExistingSeries && nSeriesCount>0) 
                UpdateSeries(i,pDoc->m_bufWLDataPoints,bufYData,MAX_PIXEL_DATA_COUNT_PER_LINE,AVG_PIXEL_LINE_COLOR);
			else
			    AddSeries(pDoc->m_bufWLDataPoints,bufYData,MAX_PIXEL_DATA_COUNT_PER_LINE,AVG_PIXEL_LINE_COLOR, strTitle);
		}

		if(pDoc->m_objCapturePixelBuff.m_bShowSD && nLineCount >1)
		{
			double bufYData[MAX_PIXEL_DATA_COUNT_PER_LINE];
			for(int j=0;j<MAX_PIXEL_DATA_COUNT_PER_LINE;j++)
				bufYData[j]=pDoc->m_objCapturePixelBuff.m_pBufSDPixelData[j];
			CString strTitle;
			strTitle.Format(_T("SD"));
			if(bUpdateExistingSeries && nSeriesCount>0) 
                UpdateSeries(i+1,pDoc->m_bufWLDataPoints,bufYData,MAX_PIXEL_DATA_COUNT_PER_LINE,SD_PIXEL_LINE_COLOR);
			else
			    AddSeries(pDoc->m_bufWLDataPoints,bufYData,MAX_PIXEL_DATA_COUNT_PER_LINE,SD_PIXEL_LINE_COLOR, strTitle);

		}
		if(pDoc->m_objCapturePixelBuff.m_bShowRSD && nLineCount >1)
		{
			double bufYData[MAX_PIXEL_DATA_COUNT_PER_LINE];
			for(int j=0;j<MAX_PIXEL_DATA_COUNT_PER_LINE;j++)
				bufYData[j]=pDoc->m_objCapturePixelBuff.m_pBufRSDPixelData[j];
			CString strTitle;
			strTitle.Format(_T("RSD"));
			if(bUpdateExistingSeries && nSeriesCount>0) 
                UpdateSeries(i+2,pDoc->m_bufWLDataPoints,bufYData,MAX_PIXEL_DATA_COUNT_PER_LINE,RSD_PIXEL_LINE_COLOR);
			else
			    AddSeries(pDoc->m_bufWLDataPoints,bufYData,MAX_PIXEL_DATA_COUNT_PER_LINE,RSD_PIXEL_LINE_COLOR, strTitle);
		}
		//call baseplotview OnUpdate 
		CMainFrame* pFrame=(CMainFrame*)AfxGetMainWnd();
		if(pFrame != NULL)
		{
			//if(pFrame->m_PresentationMode == CMainFrame::WAVELENGTH_MODE)
			//{
				CalculateCompoundArea();
				pFrame->UpdateSettingsDlg();

				if(m_bShowPeaks == TRUE)
				{
					ShowPeaks();
				}
			//}
		}
		m_objGraphCtrl.Invalidate();

		CBasePlotView::OnUpdate(pSender,lHint,pHint);
	}
}
