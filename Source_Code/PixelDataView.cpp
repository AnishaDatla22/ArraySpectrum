// PixelDataView.cpp : implementation file
//

#include "stdafx.h"
#include "ArraySpectrum.h"
#include "PixelDataView.h"
#include "arraySpectrumDoc.h"
#include "constants.h"
#include "MainFrm.h"

// CPixelDataView

IMPLEMENT_DYNCREATE(CPixelDataView, CDataView)

CPixelDataView::CPixelDataView()
{

}

CPixelDataView::~CPixelDataView()
{
}

BEGIN_MESSAGE_MAP(CPixelDataView, CDataView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CPixelDataView drawing

void CPixelDataView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CPixelDataView diagnostics

#ifdef _DEBUG
void CPixelDataView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPixelDataView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPixelDataView message handlers
void CPixelDataView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	// TODO: Add your specialized code here and/or call the base class

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	if(pFrame != NULL)
	{
		if(pFrame->m_bShowViewData == false)
			return;
	}

	CArraySpectrumDoc* pDoc= (CArraySpectrumDoc*)GetDocument();

	BOOL bUpdateExistingRows=lHint; //If true, do not Add Rows, only update the existing Rows
	
	ClearAll();
	//If no Pixel Data is Available, Do not do anything
	if(pDoc->m_objCapturePixelBuff.ISEmpty()==FALSE)
	{   	
		BeginWaitCursor(); // display the hourglass cursor
		int nLineCount=pDoc->m_objCapturePixelBuff.m_nLineCount;
		int nRowNo=0;
		int nColCount=0;
		CStringArray strColValues;
		CString str;
		m_objDataGrid.SetMaxRows(MAX_PIXEL_DATA_COUNT_PER_LINE+1);
		//Prepare HeaderRow
		strColValues.Add(_T("Px.No"));
		if(pDoc->m_objCapturePixelBuff.m_bShowAvg)
		{
			strColValues.Add(_T("Avg."));
		}
		if(pDoc->m_objCapturePixelBuff.m_bShowSD && nLineCount >1 )
		{		
			strColValues.Add(_T("SD"));

		}
		if(pDoc->m_objCapturePixelBuff.m_bShowRSD && nLineCount >1)
		{		
			strColValues.Add(_T("RSD"));

		}
		for(int h=0;h<nLineCount;h++)
		{
			str.Format(_T("L %d"),h+1);
			strColValues.Add(str);

		}
		this->SetHeaderRow(strColValues);

		nRowNo++;
		//////////////////////////
		//Prepare Data Rows
		for(int d=0;d<MAX_PIXEL_DATA_COUNT_PER_LINE;d++)
		{
			strColValues.RemoveAll();
			str.Format(_T("%d"),d);//nRowNo-1);
			strColValues.Add(str);

			if(pDoc->m_objCapturePixelBuff.m_bShowAvg)
			{
				str.Format(_T("%.3f"),pDoc->m_objCapturePixelBuff.m_pBufAvgPixelData[d]);
				strColValues.Add(str);
			}
			if(pDoc->m_objCapturePixelBuff.m_bShowSD && nLineCount >1)
			{
				str.Format(_T("%.3f"),pDoc->m_objCapturePixelBuff.m_pBufSDPixelData[d]);
				strColValues.Add(str);
			}			
			if(pDoc->m_objCapturePixelBuff.m_bShowRSD && nLineCount >1)
			{
				str.Format(_T("%.3f"),pDoc->m_objCapturePixelBuff.m_pBufRSDPixelData[d]);
				strColValues.Add(str);
			}	
			for(int l=0;l<nLineCount;l++)
			{
#ifdef _SA165
		str.Format(_T("%.3f"),(double)pDoc->m_objCapturePixelBuff.m_pPixelLines[l][d]);
#else
		str.Format(_T("%.3f"),(double)pDoc->m_objCapturePixelBuff.m_pPixelLines[l][d]);
#endif
				strColValues.Add(str);
			}
			if(bUpdateExistingRows)
			{
				UpdateRow(nRowNo,strColValues);
			}
			else
				AddRow(strColValues);
			nRowNo++;

		}
		//Set the Whole Row/Col Text at once
		ClipDataToGrid();
		EndWaitCursor(); // remove the hourglass cursor
	}
}
int CPixelDataView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDataView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}
