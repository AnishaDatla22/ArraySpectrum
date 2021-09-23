#pragma once


// CPropertiesPaneDlg dialog
#include "resource.h"

class CPropertiesPaneDlg : public CDialog
{
	DECLARE_DYNAMIC(CPropertiesPaneDlg)

public:
	CPropertiesPaneDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPropertiesPaneDlg();

// Dialog Data
	enum { IDD = IDD_PROPERTIESPANEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	
	// The Integration Time  (m.Sec) used to set to the Data Acquisition H/W
	int m_nExposureTime;
	// The Gain factor to be set
	int m_nGain;
	// The parameter set to the  Data Acquisistion ardware to set the number of Lines to be scanned. 
	int m_nLineCount;
	afx_msg void OnBnClickedButtonApply();
	BOOL m_bShowAverage;
	BOOL m_bShowRSD;
	virtual BOOL OnInitDialog();
	void InitProperties();
	// Pixel Offset
	int m_nOffSet;
	// TRUE, if SD vakue is to be shown in the data grid
	BOOL m_bShowSD;
};
