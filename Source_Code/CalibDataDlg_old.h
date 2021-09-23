#pragma once
#include "afxcmn.h"


// CCalibDataDlg dialog

class CCalibDataDlg : public CDialog
{
	DECLARE_DYNAMIC(CCalibDataDlg)

public:
	CCalibDataDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCalibDataDlg();

// Dialog Data
	enum { IDD = IDD_CALIBDATADLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_nPixelNo;
	float m_fWLNo;
	CListCtrl m_listCalibEntries;
	afx_msg void OnBnClickedButtonRemove();
	afx_msg void OnBnClickedButtonAdd();
	virtual BOOL OnInitDialog();
	// if bSave is TRUE, The Calibration settings are saved to a INI file otherwise they will be rerieved from the 
	void SerializeCalibData(bool bSave);
	afx_msg void OnBnClickedOk();
	// Polynomial A Coefficeint
	float m_fA;
	// Polynomial B Coefficeint
	float m_fB;
	// Polynomial C Coefficeint
	float m_fC;
	// Polynomial D Coefficeint
	float m_fD;
};
