// DataView.cpp : implementation file
//

#include "stdafx.h"
#include "ArraySpectrum.h"
#include "DataView.h"
#include "ArraySpectrumDoc.h"

// CDataView
#define IDC_SPREADSHEET 12341

IMPLEMENT_DYNCREATE(CDataView, CView)

CDataView::CDataView()
{
	m_nRowIndex=1; //leave the top row 
}

CDataView::~CDataView()
{
}

BEGIN_MESSAGE_MAP(CDataView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDataView drawing

void CDataView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CDataView diagnostics

#ifdef _DEBUG
void CDataView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CDataView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDataView message handlers

int CDataView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	InitDataGrid();


	return 0;
}

// Initialize Data Grid
BOOL CDataView::InitDataGrid(void)
{
	WCHAR pwchLicenseKey[] =
	{
		0x0043,	0x006F,	0x0070,	0x0079,	0x0072,	0x0069,	
		0x0067,	0x0068,	0x0074,	0x0020,	0x0028,	0x0063,	
		0x0029,	0x0020,	0x0031,	0x0039,	0x0039,	0x0035,	
		0x0020,	0x0046,	0x0061,	0x0072,	0x0050,	0x006F,	
		0x0069,	0x006E,	0x0074
	} ;

	BSTR bstrLicense = ::SysAllocStringLen(pwchLicenseKey,sizeof(pwchLicenseKey)/sizeof(WCHAR)) ;	

	CLSID clsID ;
	HRESULT hr= CLSIDFromProgID(OLESTR("FPUSpreadADO.fpSpread.5"), &clsID) ;

	if(FAILED(hr))
	{
		AfxMessageBox(_T("Data Grid Control is not Registered.."));
		::SysFreeString(bstrLicense) ;
		return FALSE ;
	}

	CRect rcRect;
	GetClientRect(&rcRect);

	if(!m_objDataGrid.CreateControl(clsID,NULL,WS_VISIBLE | WS_CHILD,
		rcRect,this,IDC_SPREADSHEET,NULL,FALSE,bstrLicense))
	{
		AfxMessageBox(_T("Failed to create Data Grid"));
		::SysFreeString(bstrLicense) ;//TTP# 771 Measurement Slowdown 
		return FALSE ;
	};

	::SysFreeString(bstrLicense) ;

	//m_objDataGrid.SetUserResize(3) ; // 3 means allow the user to resize
	//m_objDataGrid.SetTypeHAlign(1); // 1 is for right alignment
	//m_objDataGrid.SetAllowMultiBlocks(FALSE);


	m_objDataGrid.BringWindowToTop();
	m_objDataGrid.SetTypeHAlign(2); //center align
	//m_objDataGrid.SetAutoSize(TRUE);
	m_objDataGrid.SetUserResize(1);
	m_objDataGrid.SetGrayAreaBackColor(0x00AAC6C4);
    
	m_objDataGrid.SetAutoClipboard(TRUE);
	m_objDataGrid.SetClipboardOptions(15); 
	
	
	m_objDataGrid.SetColHeaderRows(1);
	//m_objDataGrid.SetRowHeaderCols(1);
	m_objDataGrid.SetRowHeadersShow(FALSE);
	m_objDataGrid.SetColHeadersShow(TRUE);
	m_objDataGrid.SetProtect(FALSE);
    m_objDataGrid.SetScrollBarExtMode(TRUE); 

    m_objDataGrid.SetRow(m_nRowIndex);
	m_objDataGrid.SetCol(-1);
	//m_objDataGrid.SetShadowColor(0x00990000);
	//m_objDataGrid.SetShadowDark(0x00600000);



	/*
	//m_objDataGrid.SetMaxRows(1);
	//m_objDataGrid.SetMaxCols(10);
	m_objDataGrid.SetCol(-1);
	m_objDataGrid.SetRow(0);
	// Turn off the raised three-dimensional appearance
	m_objDataGrid.SetTypeTextShadow(FALSE);
	// Set the lowered three-dimensional appearance
	m_objDataGrid.SetTypeTextShadowIn(TRUE);

	// Set the background color
	// blue, RGB(0, 0, 255)
	m_objDataGrid.SetShadowColor(0x00990000);
	// Set the shadow border color
	// dark blue, RGB(0, 0, 128)
	m_objDataGrid.SetShadowDark(0x00600000);
	// Set the text color
	// yellow, RGB(255, 255, 0)
	m_objDataGrid.SetShadowText(0x0000FFFF); 
	m_objDataGrid.SetFontBold(TRUE);

	*/
	ClearAll();
	return TRUE;
}

// Set the Header Row with Column Titles
void CDataView::SetHeaderRow(CStringArray & strColNames)
{
	AddRow(strColNames);
	m_objDataGrid.SetMaxCols(strColNames.GetCount());

}

// Add A Row with the given Values
void CDataView::AddRow(CStringArray & strColValues)
{
	for(int nIndex=0;nIndex<strColValues.GetCount();nIndex++)
	{
		m_strRowsData+=strColValues.GetAt(nIndex);
		m_strRowsData+=_T("\t");
	}
    m_strRowsData+=_T("\r\n");

	/////
	/*m_objDataGrid.SetRow(m_nRowIndex);

	int nColCount=strColValues.GetCount();
	m_objDataGrid.SetMaxCols(nColCount);

	m_objDataGrid.SetCol(1);
	m_objDataGrid.SetCol2(-1);
	m_objDataGrid.SetRow2(-1);
	m_objDataGrid.SetClip(strRowData);*/


	/////

	/*
	for(int i=1;i<=nColCount;i++)
	{
		m_objDataGrid.SetCol(i);
		m_objDataGrid.SetCellType(5);//non editable
		if(m_nRowIndex==1)
		{
			//m_objDataGrid.SetShadowColor(0x00990000);
			// Set the shadow border color
			// dark blue, RGB(0, 0, 128)
			//m_objDataGrid.SetShadowDark(0x00600000);
			//m_objDataGrid.SetFontBold(TRUE);
			m_objDataGrid.SetBackColor(RGB(200,200,200));

		}
		m_objDataGrid.SetBackColor(RGB(255,255,255));
		m_objDataGrid.SetText(strColValues[i-1]);
	}
	*/
	m_nRowIndex++;
	//m_objDataGrid.SetActiveCell(1,m_nRowIndex);
}
//Set the Whole Row/Col Text at once
void CDataView::ClipDataToGrid()
{
	m_objDataGrid.SetRow(0);
	m_objDataGrid.SetCol(1);
	m_objDataGrid.SetCol2(-1);
	m_objDataGrid.SetRow2(-1);
	m_objDataGrid.SetClip(m_strRowsData);
}
// Update the Existing Row with the given Col Values
void CDataView::UpdateRow(int nRowNo, CStringArray & strColValues)
{
	m_objDataGrid.SetRow(nRowNo);
	int nColCount=strColValues.GetCount();
	for(int i=0;i<nColCount;i++)
	{
		//<--commented fo 1.2
		//m_objDataGrid.SetCol(i);
		//m_objDataGrid.SetCellType(3);//non editable
		//<--commented fo 1.2

		//<--Added for 1.2
		//m_objDataGrid.SetCol(i);//1.3
		m_objDataGrid.SetCol(i+1);//1.3
		m_objDataGrid.SetCellType(5);//non editable
		//<--Added for 1.2

		if(m_nRowIndex==0)
			m_objDataGrid.SetFontBold(TRUE);
		m_objDataGrid.SetText(strColValues[i]);
	}
} 

// Clear Entire Data Grid
void CDataView::ClearAll(void)
{
	m_strRowsData=_T("");
	m_objDataGrid.DeleteRows(0,m_nRowIndex);
	m_objDataGrid.SetMaxRows(0);
	m_objDataGrid.SetMaxCols(0);
	m_nRowIndex=0;
}


void CDataView::OnSize(UINT nType,int cx,int cy)
{
	CView::OnSize(nType,cx,cy);
	//Fit the Grid Control with respect to client window
	if(m_objDataGrid.GetSafeHwnd())
	{
		m_objDataGrid.MoveWindow(0,0,cx,cy);
	}
}