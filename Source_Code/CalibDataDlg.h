#pragma once
#include "afxcmn.h"

#include "ArraySpectrumDoc.h"

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
	///
	int m_nPixelNo;
	///
	double m_fWLNo;
	///
	CListCtrl m_listCalibEntries;
	
	// Polynomial A Coefficeint
	double m_dblA;
	// Polynomial B Coefficeint
	double m_dblB;
	// Polynomial C Coefficeint
	double m_dblC;
	// Polynomial D Coefficeint
	double m_dblD;
	///
	CArraySpectrumDoc* m_pDoc;

protected:
	virtual void OnCancel();
public:
	///
	afx_msg void OnBnClickedButtonRemove();
	///
	afx_msg void OnBnClickedButtonAdd();
	///
	virtual BOOL OnInitDialog();
	// if bSave is TRUE, The Calibration settings are saved to a INI file otherwise they will be rerieved from the 
	void SerializeCalibData(bool bSave);
	///
	afx_msg void OnBnClickedOk();
	///
	afx_msg void OnBnClickedButtonCalculate();

};
