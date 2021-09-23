// BasePlotView.cpp : implementation file
//

#include "stdafx.h"
#include "ArraySpectrum.h"
#include "BasePlotView.h"
#include "constants.h"
#include "MainFrm.h"
#include "CompoundSettings.h"
#include <math.h>

// CBasePlotView

IMPLEMENT_DYNCREATE(CBasePlotView, CView)


BEGIN_MESSAGE_MAP(CBasePlotView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CBasePlotView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_MESSAGE(WM_CALCULATE_AREA, &CBasePlotView::OnCalcualteArea)
END_MESSAGE_MAP()


BEGIN_EVENTSINK_MAP(CBasePlotView,CView)

	//ON_EVENT(CBasePlotView, ID_GRAPH_CTRL, 20 /* OnMouseMove */, OnTChartMouseMove, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CBasePlotView,ID_GRAPH_CTRL,26,OnZoom,VTS_NONE)

END_EVENTSINK_MAP()

// CBasePlotView construction/destruction

CBasePlotView::CBasePlotView()
{
	// TODO: add construction code here
	//m_pChartCtrl=NULL;
	m_TChartPtr=NULL;
	m_LegendPtr=NULL;
	m_bShowLegends=TRUE;
	m_strPlotTilte=_T(" Plot");
	m_strXAxisTitle=_T("X-Axis");
	m_strYAxisTitle=_T("Y-Axis");
	m_nYMax=2000; //def Y Max
	m_nXMax=MAX_PIXEL_DATA_COUNT_PER_LINE;
	m_ptrdblHeight = NULL;
	m_ptrdblWidth = NULL;
	m_ptrdblArea = NULL;
	m_ptrlngStart = NULL;
	m_ptrlngMax = NULL;
	m_ptrlngEnd = NULL;
	//m_ptrEvents = NULL;
	m_nPeakGraphID = 0;
	m_lngPeakCount = 0;
	m_dblheightReject = 100;
	m_bShowPeaks = false;
}

CBasePlotView::~CBasePlotView()
{
	m_TChartPtr->RemoveAllSeries();
	//m_objGraphCtrl.ClearCustomText();
	fncCleanPeakInformation();
	/*if(m_ptrEvents != NULL)
	{
		delete[] m_ptrEvents;
		m_ptrEvents = NULL;
	}*/
	m_lngPeakCount = 0;
	m_nPeakGraphID = 0;
	m_bShowPeaks = FALSE;
}

BOOL CBasePlotView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CBasePlotView drawing

void CBasePlotView::OnDraw(CDC* pDC)
{
	CArraySpectrumDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

}


// CBasePlotView printing


void CBasePlotView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CBasePlotView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBasePlotView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBasePlotView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CBasePlotView diagnostics

#ifdef _DEBUG
void CBasePlotView::AssertValid() const
{
	CView::AssertValid();
}

void CBasePlotView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CArraySpectrumDoc* CBasePlotView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CArraySpectrumDoc)));
	return (CArraySpectrumDoc*)m_pDocument;
}
#endif //_DEBUG


// CBasePlotView message handlers

int CBasePlotView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	if(!m_objGraphCtrl.CreateControl(m_objGraphCtrl.GetClsid(),_T(""),WS_VISIBLE | WS_CHILD,
		CRect(0,0,0,0),this,ID_GRAPH_CTRL))	
	{
		AfxMessageBox(_T("Graph Control Creation Failed"));
		return -1 ;
	}
	m_objGraphCtrl.BringWindowToTop();

	InitializeGraphCtrl();


	return 0;  // return TRUE  unless you set the focus to a control

}

void CBasePlotView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	if(m_objGraphCtrl.GetSafeHwnd())
		m_objGraphCtrl.MoveWindow(0,0,cx,cy);
	// TODO: Add your message handler code here
}

void CBasePlotView::OnDestroy()
{
	if(m_TChartPtr)
		m_TChartPtr->Release();

	if(m_LegendPtr)
		m_LegendPtr->Release();

	if(m_objGraphCtrl.m_hWnd != NULL)
	{
		m_objGraphCtrl.ShowWindow(SW_HIDE);
		m_objGraphCtrl.DestroyWindow();
	}

	CView::OnDestroy();

	// TODO: Add your message handler code here
}

void CBasePlotView::InitializeGraphCtrl()
{
	IUnknown *p=m_objGraphCtrl.GetControlUnknown();

	p->QueryInterface(__uuidof(ITChart),(void**)&m_TChartPtr);
	//p->Release();

	//No 3D look
	m_TChartPtr->Aspect->put_View3D(FALSE);

	//Clear All Series- Just for good sake
	m_TChartPtr->RemoveAllSeries();

	if(m_bShowLegends)
	{
		//Get Legends object set the style to show the Legend Table
		m_TChartPtr->get_Legend(&m_LegendPtr);
		m_LegendPtr->put_LegendStyle(ELegendStyle::lsSeries);
	}

	//Set the Title Of the Plot Area Header
	m_TChartPtr->GetHeader()->Font->put_Size(14);
	m_TChartPtr->GetHeader()->Font->put_Bold(VARIANT_TRUE);
	m_TChartPtr->GetHeader()->Font->put_Color(PLOT_TITLE_COLOR);
	m_TChartPtr->GetHeader()->put_Caption(_bstr_t(m_strPlotTilte));

	//Set Axis Titles and default ranges
	m_TChartPtr->GetAxis()->GetLeft()->GetTitle()->Font->put_Size(12);
	m_TChartPtr->GetAxis()->GetLeft()->GetTitle()->Font->put_Bold(VARIANT_TRUE);
	m_TChartPtr->GetAxis()->GetLeft()->GetTitle()->Font->put_Color(AXIS_TITLE_COLOR);

	m_TChartPtr->GetAxis()->GetLeft()->GetTitle()->Caption= m_strYAxisTitle.AllocSysString();
	m_TChartPtr->GetAxis()->GetLeft()->GetLabels()->GetFont()->put_Color(SCALE_LABELS_COLOR);

	m_TChartPtr->GetAxis()->GetBottom()->GetTitle()->Font->put_Size(12);
	m_TChartPtr->GetAxis()->GetBottom()->GetTitle()->Font->put_Bold(VARIANT_TRUE);
	m_TChartPtr->GetAxis()->GetBottom()->GetTitle()->Font->put_Color(AXIS_TITLE_COLOR);
	m_TChartPtr->GetAxis()->GetBottom()->GetTitle()->Caption=m_strXAxisTitle.AllocSysString();

	m_TChartPtr->GetAxis()->GetBottom()->GetLabels()->GetFont()->put_Color(SCALE_LABELS_COLOR);

	//m_TChartPtr->GetAxis()->GetLeft()->SetMinMax(0,m_nYMax);
	//m_TChartPtr->GetAxis()->GetBottom()->SetMinMax(0,m_nXMax);
	m_TChartPtr->GetAxis()->GetLeft()->PutAutomaticMaximum(VARIANT_TRUE);// Automatic=TRUE;
	m_TChartPtr->GetAxis()->GetBottom()->PutAutomaticMaximum(VARIANT_TRUE);
	m_TChartPtr->GetAxis()->GetLeft()->PutAutomaticMinimum(VARIANT_TRUE);
	m_TChartPtr->GetAxis()->GetBottom()->PutAutomaticMinimum(VARIANT_TRUE);

	//Set the default Axes Scale Lables Mark intervals
	m_TChartPtr->GetAxis()->GetBottom()->Increment=1;// m_TChartPtr->GetAxis()->GetBottom()->GetMaximum()/20.0;
	m_TChartPtr->GetAxis()->GetLeft()->Increment =1;//m_TChartPtr->GetAxis()->GetLeft()->GetMaximum()/10.0;

	//	ITeePoint2D ptrPoint2D;
	//	m_TChartPtr->get_Cursor();
	//	m_TChartPtr->get_MousePosition(&ptrPoint2D);
	//	m_TChartPtr->Tools->Add(
}


// Clear All Series in the Graph
void CBasePlotView::ClearGraph(void)
{
	m_objGraphCtrl.ClearCustomText();
	m_TChartPtr->RemoveAllSeries();
	//m_objGraphCtrl.ClearCustomText();

	fncCleanPeakInformation();
	/*if(m_ptrEvents != NULL)
	{
		delete[] m_ptrEvents;
		m_ptrEvents = NULL;
	}*/
	m_lngPeakCount = 0;
	m_nPeakGraphID = 0;
}

// Add a new Series with the given X and Y Point buffers
void CBasePlotView::AddSeries(double * pBufXPoints, double * pBufYPoints, long nPointCount,COLORREF Color,CString strSeriesTitle)
{
	//Add the Line Series (whose serisID=0)
	//long seriesID=m_TChartPtr->AddSeries(ESeriesClass::scLine);
	long seriesID;
	seriesID=m_objGraphCtrl.AddGraph(strSeriesTitle,Color);

	//For Area Chart
	//m_nSeriesIndex=m_TChartPtr->AddSeries(ESeriesClass::scArea);
	//m_TChartPtr->Series(m_nSeriesIndex)->asArea->AreaPen->put_Visible(VARIANT_FALSE);

	m_TChartPtr->Series(seriesID)->put_Color(Color);
	//m_TChartPtr->Series(seriesID)->asArea->AreaPen->put_Visible(VARIANT_FALSE);
	m_TChartPtr->Series(seriesID)->PutVerticalAxis(EVerticalAxis::aLeftAxis);
	m_TChartPtr->Series(seriesID)->put_Title(strSeriesTitle.AllocSysString());
	if(m_bShowLegends)
		m_TChartPtr->Series(seriesID)->put_ShowInLegend(VARIANT_TRUE);

	for(int i=0;i<nPointCount;i++)
	{
		//m_TChartPtr->Series(seriesID)->AddXY(pBufXPoints[i],i+1,_T(""),Color);
		m_TChartPtr->Series(seriesID)->AddXY(pBufXPoints[i],pBufYPoints[i],_T(""),Color);

	}
	/*if(m_TChartPtr->GetSeriesCount()==1)
	m_objGraphCtrl.put_CrossWire(TRUE);
	else
	m_objGraphCtrl.put_CrossWire(FALSE);*/

}



// Delete a Given indexed series
void CBasePlotView::DeleteSeries(void)
{
}



// Show a Given indexed Series in Highlighted Color
void CBasePlotView::HighLightSeries(int nSeriesIndex)
{
}

// Update the Series data with the given SeriesID
void CBasePlotView::UpdateSeries(long nSeriesID, double* pBufXData, double* pBufYData, long nPointCount,COLORREF rgbColor)
{

	m_TChartPtr->Series(nSeriesID)->Clear();

	for(int i=0;i<nPointCount;i++)
	{
		//m_TChartPtr->Series(seriesID)->AddXY(pBufXPoints[i],i+1,_T(""),Color);
		m_TChartPtr->Series(nSeriesID)->AddXY(pBufXData[i],pBufYData[i],_T(""),rgbColor);
	}
}
void CBasePlotView::OnTChartMouseMove(long Shift, long X, long Y)
{
	TRACE(_T("in mouse move event X=%d, Y=%d\n"),X,Y);
}

void CBasePlotView::OnZoom()
{
	m_TChartPtr->GetAxis()->GetLeft()->Increment=1;
	m_TChartPtr->GetAxis()->GetBottom()->Increment=1;
}

void CBasePlotView::OnUpdate(CView* pSender, LPARAM lHint, CObject*pHint)
{
	//int nSeriesCount = m_TChartPtr->GetSeriesCount();
	//for(int nSeriesIndex = 0; nSeriesIndex < nSeriesCount; nSeriesIndex++)
	//{
	//m_objGraphCtrl.ShowPeaks(0, 1);
	//m_objGraphCtrl.SetShowDataAtPeak(TRUE);
	//long lngID = 0;
	//short nPeaKLevel = 1;
	//m_objGraphCtrl.ShowPeaks(lngID,nPeaKLevel);

	//lngCount = m_objGraphCtrl.GetGraphPeaksCount(0);
	//m_objGraphCtrl.StartOnlinePeakDetection();

	//<--Testing--
	//	m_objGraphCtrl.GetStartnEndptMarkingColor();
	
	
	//OnCalcualteArea(0,0);
	
	
	//}
}

void CBasePlotView::fncCleanPeakInformation()
{
	if(m_ptrdblHeight != NULL)
	{
		delete[] m_ptrdblHeight;
		m_ptrdblHeight = NULL;
	}
	if(m_ptrdblWidth != NULL)
	{
		delete[] m_ptrdblWidth;
		m_ptrdblWidth = NULL;
	}
	if(m_ptrdblArea != NULL)
	{
		delete[] m_ptrdblArea;
		m_ptrdblArea = NULL;
	}
	if(m_ptrlngStart != NULL)
	{
		delete[] m_ptrlngStart;
		m_ptrlngStart = NULL;
	}
	if(m_ptrlngMax != NULL)
	{
		delete[] m_ptrlngMax;
		m_ptrlngMax = NULL;
	}
	if(m_ptrlngEnd != NULL)
	{
		delete[] m_ptrlngEnd;
		m_ptrlngEnd = NULL;
	}
}

void CBasePlotView::fncGetPeakInformation(int nGraphIndex)
{
	m_nPeakGraphID = nGraphIndex;
	m_lngPeakCount = m_objGraphCtrl.GetGraphPeaksCount(nGraphIndex);

	VARIANT vdblHt,vdblWd,vdblArea;
	VARIANT vnPeakStartIndex,vnPeakMaxIndex,vnPeakEndIndex;
	vdblHt.vt	=	VT_ARRAY|VT_R8;
	vdblWd.vt	=	VT_ARRAY|VT_R8;
	vdblArea.vt	=	VT_ARRAY|VT_R8;
	vnPeakStartIndex.vt	=	VT_ARRAY|VT_I4;
	vnPeakMaxIndex.vt	=	VT_ARRAY|VT_I4;
	vnPeakEndIndex.vt	=	VT_ARRAY|VT_I4;
	//m_GraphCtrl.GetPeakInfo(0,dblHt,dblWd,dblArea,nPeakStartIndex,nPeakMaxIndex,nPeakEndIndex); //19/11
	m_objGraphCtrl.GetPeakInfo(0,&vdblHt,&vdblWd,&vdblArea,&vnPeakStartIndex,&vnPeakMaxIndex,&vnPeakEndIndex);

	// Retrieve Peak Info values from Safe Arrays
	long lBound,uBound;
	SafeArrayGetLBound(vdblArea.parray,1,&lBound);
	SafeArrayGetUBound(vdblArea.parray,1,&uBound);
	uBound	=uBound-lBound;
	/*double dblHt[uBound+1],dblWd[uBound+1],dblArea[uBound+1];
	long nPeakStartIndex[uBound+1],nPeakMaxIndex[uBound+1],nPeakEndIndex[uBound+1];*/


	m_ptrdblHeight = new double[uBound+1];
	m_ptrdblWidth = new double[uBound+1];
	m_ptrdblArea = new double[uBound+1];

	m_ptrlngStart = new long[uBound+1];
	m_ptrlngMax = new long[uBound+1];
	m_ptrlngEnd = new long[uBound+1];

	long lng=0;
	for(long cnt=lBound;cnt<=uBound;cnt++)
	{
		SafeArrayGetElement(vdblHt.parray,&cnt,&m_ptrdblHeight[lng]);
		SafeArrayGetElement(vdblWd.parray,&cnt,&m_ptrdblWidth[lng]);
		SafeArrayGetElement(vdblArea.parray,&cnt,&m_ptrdblArea[lng]);
		SafeArrayGetElement(vnPeakStartIndex.parray,&cnt,&m_ptrlngStart[lng]);
		SafeArrayGetElement(vnPeakMaxIndex.parray,&cnt,&m_ptrlngMax[lng]);
		SafeArrayGetElement(vnPeakEndIndex.parray,&cnt,&m_ptrlngEnd[lng]);
		lng++;
	}

	// Destroy the Safe Array Elements ////////////////////////////
	SafeArrayDestroy(vdblHt.parray);
	SafeArrayDestroy(vdblWd.parray);
	SafeArrayDestroy(vdblArea.parray);
	SafeArrayDestroy(vnPeakStartIndex.parray);
	SafeArrayDestroy(vnPeakMaxIndex.parray);
	SafeArrayDestroy(vnPeakEndIndex.parray);
}

void CBasePlotView::SetPeakGraphID(int nGraphID)
{
	m_nPeakGraphID = nGraphID;
}

void CBasePlotView::CalculateCompoundArea()
{
	//m_objGraphCtrl.ClearCustomText();
	CArraySpectrumDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc == NULL)
		return;
	if(pDoc->m_objCapturePixelBuff.ISEmpty() == FALSE)
	{
		double* ptrdblYvals = NULL;
		double bufYData[MAX_PIXEL_DATA_COUNT_PER_LINE];

		int nLineCount = pDoc->m_objCapturePixelBuff.m_nLineCount;
		if( (nLineCount > 1 )  && (pDoc->m_objCapturePixelBuff.m_bShowAvg ==  TRUE))
		{
			ptrdblYvals = pDoc->m_objCapturePixelBuff.m_pBufAvgPixelData;
			m_nPeakGraphID = nLineCount;
		}
		else if( nLineCount == 1)
		{
			for(int j=0;j<MAX_PIXEL_DATA_COUNT_PER_LINE;j++)
				bufYData[j]=pDoc->m_objCapturePixelBuff.m_pPixelLines[0][j];
			//ptrdblYvals = pDoc->m_objCapturePixelBuff.m_pBuffPixelData;
			ptrdblYvals = bufYData;
			m_nPeakGraphID = 0;
		}
		else if((nLineCount > 1) && (pDoc->m_objCapturePixelBuff.m_bShowAvg ==  FALSE))
		{
			for(int j=0;j<MAX_PIXEL_DATA_COUNT_PER_LINE;j++)
				bufYData[j]=pDoc->m_objCapturePixelBuff.m_pPixelLines[0][j];
			//ptrdblYvals = pDoc->m_objCapturePixelBuff.m_pBuffPixelData;
			ptrdblYvals = bufYData;
			m_nPeakGraphID = 0;
		}
		//if(nLineCount == 1)
		//{
		//	ptrdblYvals = (double*)m_pDoc->m_objCapturePixelBuff.GetLinePixelBuf(0);
		//}
		//else if(nLineCount > 1)
		//{
		//}
		//ptrdblYvals = theApp.m_bufWLDataPoints;

		for(int nCompIndex = 0; nCompIndex < NO_OF_COMPOUNDS ; nCompIndex++)
		{
			CCompoundSettings objSCompoundSettings = pDoc->m_objSettings.m_arrobjCompoundSettings[nCompIndex];
			//Find the nearest point for the given peak wavelength
			bool bFound = false;
			int nLowerWLIndex = -1;
			double dblPeakWLLower = objSCompoundSettings.m_dlPeakWL - objSCompoundSettings.m_dlPeakWLTOLLimit;
			//double dblPeakWLLower = 600 - 100;

			pDoc->FindNeareastIndex(pDoc->m_bufWLDataPoints,MAX_PIXEL_DATA_COUNT_PER_LINE,dblPeakWLLower,&bFound,&nLowerWLIndex);

			int nUpperWLIndex = -1;
			double dblPeakWLUpper = objSCompoundSettings.m_dlPeakWL + objSCompoundSettings.m_dlPeakWLTOLLimit;
			//double dblPeakWLUpper = 600 + 100;

			pDoc->FindNeareastIndex(pDoc->m_bufWLDataPoints,MAX_PIXEL_DATA_COUNT_PER_LINE,dblPeakWLUpper,&bFound,&nUpperWLIndex);

			double dblTempArea = 0.0;
			int nSeriesCount = m_TChartPtr->GetSeriesCount();
			if(nSeriesCount > 0)
			{
				//m_objGraphCtrl.FindArea(0,pDoc->m_bufWLDataPoints[nLowerWLIndex],ptrdblYvals[nLowerWLIndex],pDoc->m_bufWLDataPoints[nUpperWLIndex],ptrdblYvals[nUpperWLIndex],nLowerWLIndex,nUpperWLIndex,&dblTempArea);
				m_objGraphCtrl.GetArea(m_nPeakGraphID,pDoc->m_bufWLDataPoints[nLowerWLIndex],ptrdblYvals[nLowerWLIndex],pDoc->m_bufWLDataPoints[nUpperWLIndex],ptrdblYvals[nUpperWLIndex],nLowerWLIndex,nUpperWLIndex,&dblTempArea);
				//--Testing-->
				if(objSCompoundSettings.m_strCompoundName.CompareNoCase(SULPHUR_COMPOUND) == 0)
				{
					dblTempArea = sqrt(dblTempArea);
				}
				pDoc->m_arrdblCompoundPeakArea[nCompIndex] = dblTempArea;
				double dblXVal;
				double dblYValReten;
				CString strName;
				BSTR bstr;
				int nPeakWLIndex = -1;
				pDoc->FindNeareastIndex(pDoc->m_bufWLDataPoints,MAX_PIXEL_DATA_COUNT_PER_LINE,objSCompoundSettings.m_dlPeakWL,&bFound,&nPeakWLIndex);

				m_objGraphCtrl.GetGraphDataAt(m_nPeakGraphID,nPeakWLIndex,&dblXVal,&dblYValReten);
				//strName.Format(_T("%.3lf,%.3lf"),dblXVal,dblYValReten);
				//strName.Format(_T("%.3lf"),dblYValReten);
				strName.Format(_T("%.2lf"),dblTempArea);
				bstr=strName.AllocSysString();
				m_objGraphCtrl.DisplayTextAt(m_nPeakGraphID,bstr,dblXVal,dblYValReten);
			}
		}
	}
}

void CBasePlotView::ShowPeaks()
{
	m_objGraphCtrl.put_PeakMinHeight(m_dblheightReject);

	m_objGraphCtrl.StartOfflinePeakDetection();

	fncGetPeakInformation(m_nPeakGraphID);//basic peak detection 

	if(m_lngPeakCount > 0)
	{
		//Fill the event info
		//if(m_ptrEvents != NULL)
		//{
		//	delete[] m_ptrEvents;
		//	m_ptrEvents = NULL;
		//}
		//m_ptrEvents = new stEventInfo[m_lngPeakCount];

		//for(int nPeakIndex = 0; nPeakIndex < m_lngPeakCount; nPeakIndex++)
		//{
		//	m_ptrEvents[nPeakIndex].dwEventCode = 3;//Valley to Valley

		//	m_ptrEvents[nPeakIndex].dblStartTime = m_ptrlngStart[nPeakIndex];
		//	m_ptrEvents[nPeakIndex].dblEndTimeOrValue = m_ptrlngEnd[nPeakIndex];
		//}

		//m_objGraphCtrl.DoGraphReprocess((BYTE*)m_ptrEvents,m_lngPeakCount);
		//fncGetPeakInformation(m_nPeakGraphID);//valley to valley peak detection

		double dblXVal;
		double dblYValReten;
		CString strName;
		BSTR bstr;

		for(int i = 0; i < m_lngPeakCount; i++)
		{
			m_objGraphCtrl.GetGraphDataAt(m_nPeakGraphID,m_ptrlngMax[i],&dblXVal,&dblYValReten);
			//strName.Format(_T("%.3lf,%.3lf"),dblXVal,dblYValReten);
			//strName.Format(_T("%.3lf"),dblYValReten);
			strName.Format(_T("%.3lf"),m_ptrdblArea[i]);
			bstr=strName.AllocSysString();
			//m_objGraphCtrl.DisplayTextAt(0,bstr,dblXVal,dblYValReten);
		}

	}
	//<--write the peak information on to the Trace output
}


LRESULT CBasePlotView::OnCalcualteArea(WPARAM wp,LPARAM lp)
{
	CalculateCompoundArea();
	return S_OK;
}