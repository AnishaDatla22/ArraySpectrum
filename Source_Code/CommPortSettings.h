#pragma once
#include "afxwin.h"


// CCommPortSettings dialog

class CCommPortSettings : public CDialog
{
	DECLARE_DYNAMIC(CCommPortSettings)

public:
	CCommPortSettings(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCommPortSettings();

// Dialog Data
	enum { IDD = IDD_COMMPORTSETTINGS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cmbPortNames;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();

private:
	//the selected port name is assigned into this variable
	CString m_strSelectedCommPortName;

public:
	//this function is used to enumerate the avialable comm ports in a computer and adds into the combobox
	BOOL fncEnumeratePorts();
	
	//user selected comm port name is returned
	CString GetSelectedCommPortName();

};
