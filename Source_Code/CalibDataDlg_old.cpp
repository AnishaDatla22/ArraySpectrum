// CalibDataDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ArraySpectrum.h"
#include "CalibDataDlg.h"
#include <stdlib.h>
#include <stdio.h>

// CCalibDataDlg dialog

IMPLEMENT_DYNAMIC(CCalibDataDlg, CDialog)

CCalibDataDlg::CCalibDataDlg(CWnd* pParent /*=NULL*/)
: CDialog(CCalibDataDlg::IDD, pParent)
, m_nPixelNo(0)
, m_fWLNo(0)
, m_fA(0)
, m_fB(0)
, m_fC(0)
, m_fD(0)
{

}

CCalibDataDlg::~CCalibDataDlg()
{
}

void CCalibDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PIXEL_NO, m_nPixelNo);
	DDX_Text(pDX, IDC_EDIT_WL, m_fWLNo);
	DDX_Control(pDX, IDC_LIST_CALIB_ENTRIES, m_listCalibEntries);
	DDX_Text(pDX, IDC_STATIC_COEFF_A, m_fA);
	DDX_Text(pDX, IDC_STATIC_COEFF_B, m_fB);
	DDX_Text(pDX, IDC_STATIC_COEFF_C, m_fC);
	DDX_Text(pDX, IDC_STATIC_COEFF_D, m_fD);
}


BEGIN_MESSAGE_MAP(CCalibDataDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, &CCalibDataDlg::OnBnClickedButtonRemove)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CCalibDataDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDOK, &CCalibDataDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CCalibDataDlg message handlers

void CCalibDataDlg::OnBnClickedButtonRemove()
{
	// TODO: Add your control notification handler code here
	POSITION pos =m_listCalibEntries.GetFirstSelectedItemPosition();
	if(pos==NULL)
		return;
	int nIndex=m_listCalibEntries.GetNextSelectedItem(pos);
	if(nIndex>=0)
		m_listCalibEntries.DeleteItem(nIndex);

}

void CCalibDataDlg::OnBnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if(m_nPixelNo >=0 && m_fWLNo >=0)
	{
		CString str1,str2;
		str1.Format(_T("%4d"),m_nPixelNo);
		str2.Format(_T("%.2f"),m_fWLNo);
		m_listCalibEntries.InsertItem(0,str1);
		m_listCalibEntries.SetItemText(0,1,str2);

	}

}

BOOL CCalibDataDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	m_listCalibEntries.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	//m_listCalibEntries.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, m_listCalibEntries.SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE) | LVS_EX_FULLROWSELECT);
	m_listCalibEntries.InsertColumn(0,_T("Pixel No"),LVCFMT_CENTER,130);
	m_listCalibEntries.InsertColumn(1,_T("WaveLength (nm)"),LVCFMT_CENTER,130);
	//m_listCalibEntries.SetColumnWidth(0,150);
	//m_listCalibEntries.SetColumnWidth(1,150);
	
	SerializeCalibData(FALSE);
	UpdateData(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

// if bSave is TRUE, The Calibration settings are saved to a INI file otherwise they will be rerieved from the 
void CCalibDataDlg::SerializeCalibData(bool bSave)
{

	if(bSave)
	{
		//Cleanup Calib_Config.INI

		BOOL bRes=CreateDirectory(_T("C:\\ELICO"),NULL);
		CreateDirectory(_T("C:\\ELICO\\ArraySpectrum"),NULL);
		FILE * pf= _wfopen(_T("Calib_Config.ini"),_T("w"));
		fclose(pf);
		int nCount=m_listCalibEntries.GetItemCount();
		CString str;
		for(int i=0;i<nCount;i++)
		{
			str+=m_listCalibEntries.GetItemText(i,0);
			str+=_T(",");
			str+=m_listCalibEntries.GetItemText(i,1);
			str+=_T("#");
		}
		WritePrivateProfileString(_T("Calib"),_T("PIXEL_WL_MAP"),str,_T("C:\\ELICO\\ArraySpectrum\\Calib_Config.ini"));
		str.Format(_T("%.5f"),m_fA);
		WritePrivateProfileString(_T("Calib"),_T("a"),str,_T("C:\\ELICO\\ArraySpectrum\\Calib_Config.ini"));

		str.Format(_T("%.5f"),m_fB);
		WritePrivateProfileString(_T("Calib"),_T("b"),str,_T("C:\\ELICO\\ArraySpectrum\\Calib_Config.ini"));


		str.Format(_T("%.5f"),m_fC);
		WritePrivateProfileString(_T("Calib"),_T("c"),str,_T("C:\\ELICO\\ArraySpectrum\\Calib_Config.ini"));

		str.Format(_T("%.5f"),m_fD);
		WritePrivateProfileString(_T("Calib"),_T("d"),str,_T("C:\\ELICO\\ArraySpectrum\\Calib_Config.ini"));

	}
	else
	{
		TCHAR buff[5000];
		GetPrivateProfileString(_T("Calib"),_T("PIXEL_WL_MAP"),_T(""),buff,5000,_T("C:\\ELICO\\ArraySpectrum\\Calib_Config.ini"));
		CString str=buff;
		if(str.IsEmpty())
			return;
		else
		{
			int i=0;
			TCHAR * pstrTok=NULL;
			while(1)
			{
				if(i==0)
				  pstrTok=_tcstok(buff,_T("#"));
				else
					pstrTok=_tcstok(NULL,_T("#"));
				if(pstrTok==NULL)
					break;
                i++;
				CString s=pstrTok;
				int i=s.Find(_T(","));
				CString s1=s.Left(i);
				s1.Trim();
				CString s2= s.Right(s.GetLength()-i-1);
				s2.Trim();
				m_listCalibEntries.InsertItem(0,s1);
				m_listCalibEntries.SetItemText(0,1,s2);


			}
			GetPrivateProfileString(_T("Calib"),_T("a"),_T("0.0"),buff,5000,_T("C:\\ELICO\\ArraySpectrum\\Calib_Config.ini"));
			m_fA=_wtof(buff);
			
			GetPrivateProfileString(_T("Calib"),_T("b"),_T("0.0"),buff,5000,_T("C:\\ELICO\\ArraySpectrum\\Calib_Config.ini"));
			m_fB=_wtof(buff);
			
			GetPrivateProfileString(_T("Calib"),_T("c"),_T("0.0"),buff,5000,_T("C:\\ELICO\\ArraySpectrum\\Calib_Config.ini"));
			m_fC=_wtof(buff);
			
			GetPrivateProfileString(_T("Calib"),_T("c"),_T("0.0"),buff,5000,_T("C:\\ELICO\\ArraySpectrum\\Calib_Config.ini"));
			m_fD=_wtof(buff);

		}
	}
}

void CCalibDataDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	UpdateData();
	SerializeCalibData(TRUE);
	OnOK();
}
