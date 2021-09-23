#pragma once


// CDataView view

#include "SpreadSheet.h"

class CDataView : public CView
{
	DECLARE_DYNCREATE(CDataView)

protected:
	CDataView();           // protected constructor used by dynamic creation
	virtual ~CDataView();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
int m_nRowIndex;
	
protected:
	CSpreadSheet m_objDataGrid;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// Initialize Data Grid
	BOOL InitDataGrid(void);
	// Set the Header Row with Column Titles
	void SetHeaderRow(CStringArray & strColNames);
	// Add A Row with the given Values
	void AddRow(CStringArray &strColValues);
	// Update the Existing Row with the given Col Values
	void UpdateRow(int nRowNo, CStringArray & strColValues);
	// Clear Entire Data Grid
	void ClearAll(void);
protected:
	CString m_strRowsData;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//Set the Whole Row/Col Text at once
   void CDataView::ClipDataToGrid();
};


