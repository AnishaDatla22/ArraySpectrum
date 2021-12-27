// RSSpectrumView.cpp : implementation file
//

#include "stdafx.h"
#include "ArraySpectrum.h"
#include "RSSpectrumView.h"
#include "constants.h"
#include "MainFrm.h"
// CRSSpectrumView

IMPLEMENT_DYNCREATE(CRSSpectrumView, CBasePlotView)

CRSSpectrumView::CRSSpectrumView()
{
	m_strPlotTilte = _T("RamanShift Plot");
	m_strXAxisTitle = _T("Raman Shift (nm)");
#ifdef _SA165
	m_strYAxisTitle = _T("Voltage(mv)");
#else
	m_strYAxisTitle = _T("ADU");
#endif
	m_nYMax = 2000; //def Y Max
}

CRSSpectrumView::~CRSSpectrumView()
{
}

BEGIN_MESSAGE_MAP(CRSSpectrumView, CBasePlotView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CRSSpectrumView drawing

void CRSSpectrumView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CRSSpectrumView diagnostics

#ifdef _DEBUG
void CRSSpectrumView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CRSSpectrumView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CRSSpectrumView message handlers

int CRSSpectrumView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBasePlotView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}

void CRSSpectrumView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CArraySpectrumDoc* pDoc = (CArraySpectrumDoc*)GetDocument();

	BOOL bUpdateExistingSeries = lHint; //If true, don not Add series, only update the existing series

	ClearGraph();

	//If no Pixel Data is Available, Do not do any thing
	if (pDoc->m_objCapturePixelBuff.ISEmpty() == FALSE)
	{
		int nLineCount = pDoc->m_objCapturePixelBuff.m_nLineCount;
		int nSeriesCount = m_TChartPtr->GetSeriesCount();
		int i;
		for (i = 0; i < nLineCount; i++)
		{
			double bufYData[MAX_PIXEL_DATA_COUNT_PER_LINE];
			for (int j = 0; j < MAX_PIXEL_DATA_COUNT_PER_LINE; j++)
				bufYData[j] = pDoc->m_objCapturePixelBuff.m_pPixelLines[i][j];
			CString strTitle;
			strTitle.Format(_T("Line %2d"), i + 1);
			if (bUpdateExistingSeries && nSeriesCount > 0)
				UpdateSeries(i, pDoc->m_bufRSDataPoints, bufYData, MAX_PIXEL_DATA_COUNT_PER_LINE, PIXEL_LINE_COLOR);
			else
				AddSeries(pDoc->m_bufRSDataPoints, bufYData, MAX_PIXEL_DATA_COUNT_PER_LINE, PIXEL_LINE_COLOR, strTitle);
		}

		if (pDoc->m_objCapturePixelBuff.m_bShowAvg)
		{
			double bufYData[MAX_PIXEL_DATA_COUNT_PER_LINE];
			for (int j = 0; j < MAX_PIXEL_DATA_COUNT_PER_LINE; j++)
				bufYData[j] = pDoc->m_objCapturePixelBuff.m_pBufAvgPixelData[j];
			CString strTitle;
			strTitle.Format(_T("AVG"));
			if (bUpdateExistingSeries && nSeriesCount > 0)
				UpdateSeries(i, pDoc->m_bufRSDataPoints, bufYData, MAX_PIXEL_DATA_COUNT_PER_LINE, AVG_PIXEL_LINE_COLOR);
			else
				AddSeries(pDoc->m_bufRSDataPoints, bufYData, MAX_PIXEL_DATA_COUNT_PER_LINE, AVG_PIXEL_LINE_COLOR, strTitle);
		}

		if (pDoc->m_objCapturePixelBuff.m_bShowSD && nLineCount > 1)
		{
			double bufYData[MAX_PIXEL_DATA_COUNT_PER_LINE];
			for (int j = 0; j < MAX_PIXEL_DATA_COUNT_PER_LINE; j++)
				bufYData[j] = pDoc->m_objCapturePixelBuff.m_pBufSDPixelData[j];
			CString strTitle;
			strTitle.Format(_T("SD"));
			if (bUpdateExistingSeries && nSeriesCount > 0)
				UpdateSeries(i + 1, pDoc->m_bufRSDataPoints, bufYData, MAX_PIXEL_DATA_COUNT_PER_LINE, SD_PIXEL_LINE_COLOR);
			else
				AddSeries(pDoc->m_bufRSDataPoints, bufYData, MAX_PIXEL_DATA_COUNT_PER_LINE, SD_PIXEL_LINE_COLOR, strTitle);

		}
		if (pDoc->m_objCapturePixelBuff.m_bShowRSD && nLineCount > 1)
		{
			double bufYData[MAX_PIXEL_DATA_COUNT_PER_LINE];
			for (int j = 0; j < MAX_PIXEL_DATA_COUNT_PER_LINE; j++)
				bufYData[j] = pDoc->m_objCapturePixelBuff.m_pBufRSDPixelData[j];
			CString strTitle;
			strTitle.Format(_T("RSD"));
			if (bUpdateExistingSeries && nSeriesCount > 0)
				UpdateSeries(i + 2, pDoc->m_bufRSDataPoints, bufYData, MAX_PIXEL_DATA_COUNT_PER_LINE, RSD_PIXEL_LINE_COLOR);
			else
				AddSeries(pDoc->m_bufRSDataPoints, bufYData, MAX_PIXEL_DATA_COUNT_PER_LINE, RSD_PIXEL_LINE_COLOR, strTitle);
		}
		//call baseplotview OnUpdate 
		CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
		if (pFrame != NULL)
		{
			//if(pFrame->m_PresentationMode == CMainFrame::WAVELENGTH_MODE)
			//{
			CalculateCompoundArea();
			pFrame->UpdateSettingsDlg();

			if (m_bShowPeaks == TRUE)
			{
				ShowPeaks();
			}
			//}
		}
		m_objGraphCtrl.Invalidate();

		CBasePlotView::OnUpdate(pSender, lHint, pHint);
	}
}
