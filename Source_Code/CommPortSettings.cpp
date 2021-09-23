// CommPortSettings.cpp : implementation file
//

#include "stdafx.h"
#include "ArraySpectrum.h"
#include "CommPortSettings.h"


// CCommPortSettings dialog

IMPLEMENT_DYNAMIC(CCommPortSettings, CDialog)

CCommPortSettings::CCommPortSettings(CWnd* pParent /*=NULL*/)
	: CDialog(CCommPortSettings::IDD, pParent)
{
	
}

CCommPortSettings::~CCommPortSettings()
{
	
}

void CCommPortSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PORT_NAMES, m_cmbPortNames);
}

BEGIN_MESSAGE_MAP(CCommPortSettings, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CCommPortSettings::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CCommPortSettings::OnBnClickedOk)
END_MESSAGE_MAP()


// CCommPortSettings message handlers

BOOL CCommPortSettings::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	if(fncEnumeratePorts() == FALSE)
	{
		OnBnClickedCancel();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CCommPortSettings::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void CCommPortSettings::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//get the selected port name
	int nSelectedIndex = m_cmbPortNames.GetCurSel();
	if(nSelectedIndex >= 0)
		m_cmbPortNames.GetLBText(nSelectedIndex,m_strSelectedCommPortName);
	else
		m_strSelectedCommPortName = _T("");	

	OnOK();
}

CString CCommPortSettings::GetSelectedCommPortName()
{
	return m_strSelectedCommPortName;
}

BOOL CCommPortSettings::fncEnumeratePorts()
{
	//Up to 255 COMM ports are supported so we iterate through all of them seeing
	//if we can get the default configuration
	//changed on 17/1/2012 by arun 
	if (m_cmbPortNames.GetCount() > 0)
			m_cmbPortNames.ResetContent();
	
	CString strPort;
	int nTotalComPorts = 0;
	for (UINT i = 1; i< 100; i++)
	{
		//Form the Raw device name
		strPort.Format(_T("COM%d"), i);

		COMMCONFIG cc;
		DWORD dwSize = sizeof(COMMCONFIG);	
		if (GetDefaultCommConfig(strPort, &cc, &dwSize))
		{
			m_cmbPortNames.InsertString(nTotalComPorts++, strPort);
		}
	}
	if (nTotalComPorts == 0)
	{
		AfxMessageBox(_T("No Ports are available in the Computer"));
		return FALSE;
	}
	else
		m_cmbPortNames.SetCurSel(0);

	return TRUE;
}