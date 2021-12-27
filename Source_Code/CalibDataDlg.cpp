// CalibDataDlg.cpp : implementation file
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include "ArraySpectrum.h"
#include "CalibDataDlg.h"
#include "CubicSplineInterpolation.h"
#include "quadraticfit.h"
#include "ArraySpectrumDoc.h"
#include <cmath>

// CCalibDataDlg dialog

IMPLEMENT_DYNAMIC(CCalibDataDlg, CDialog)

CCalibDataDlg::CCalibDataDlg(CWnd* pParent /*=NULL*/)
: CDialog(CCalibDataDlg::IDD, pParent)
, m_nPixelNo(0)
, m_fWLNo(0)
, m_dblA(0)
, m_dblB(0)
, m_dblC(0)
, m_dblD(0)
/* m_fA(0)
, m_fB(0)
, m_fC(0)
, m_fD(0)*/
{
	m_pDoc = NULL;
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
	/*DDX_Text(pDX, IDC_STATIC_COEFF_A, m_fA);
	DDX_Text(pDX, IDC_STATIC_COEFF_B, m_fB);
	DDX_Text(pDX, IDC_STATIC_COEFF_C, m_fC);
	DDX_Text(pDX, IDC_STATIC_COEFF_D, m_fD);*/
	
	DDX_Text(pDX, IDC_STATIC_COEFF_A, m_dblA);
	DDX_Text(pDX, IDC_STATIC_COEFF_B, m_dblB);
	DDX_Text(pDX, IDC_STATIC_COEFF_C, m_dblC);
	DDX_Text(pDX, IDC_STATIC_COEFF_D, m_dblD);
}


BEGIN_MESSAGE_MAP(CCalibDataDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, &CCalibDataDlg::OnBnClickedButtonRemove)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CCalibDataDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDOK, &CCalibDataDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_CALCULATE, &CCalibDataDlg::OnBnClickedButtonCalculate)
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
	// Set WS_EX_LAYERED on this window 
	SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);

	// Make this window 70% alpha
	SetLayeredWindowAttributes(0, (255 * 90) / 100, LWA_ALPHA);

	m_listCalibEntries.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	//m_listCalibEntries.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, m_listCalibEntries.SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE) | LVS_EX_FULLROWSELECT);
	m_listCalibEntries.InsertColumn(0,_T("Pixel No"),LVCFMT_CENTER,120);
	m_listCalibEntries.InsertColumn(1,_T("WaveLength (nm)"),LVCFMT_CENTER,120);
	/*m_listCalibEntries.SetColumnWidth(0,150);
	m_listCalibEntries.SetColumnWidth(1,150);*/
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

		
		int nCount=m_listCalibEntries.GetItemCount();
		CString str;
		for(int i=0;i<nCount;i++)
		{
			str+=m_listCalibEntries.GetItemText(i,0);
			str+=_T(",");
			str+=m_listCalibEntries.GetItemText(i,1);
			str+=_T("#");
		}
		AfxGetApp()->WriteProfileString(_T("Calib"),_T("PIXEL_WL_MAP"),str);
		
		
		
		AfxGetApp()->WriteProfileBinary(_T("Calib"),_T("a"),(BYTE*)&m_dblA,sizeof(double));
		AfxGetApp()->WriteProfileBinary(_T("Calib"),_T("b"),(BYTE*)&m_dblB,sizeof(double));
		AfxGetApp()->WriteProfileBinary(_T("Calib"),_T("c"),(BYTE*)&m_dblC,sizeof(double));
		AfxGetApp()->WriteProfileBinary(_T("Calib"),_T("d"),(BYTE*)&m_dblD,sizeof(double));

	}
	else
	{
		
		CString str=AfxGetApp()->GetProfileString(_T("Calib"),_T("PIXEL_WL_MAP"),_T(""));
		if(str.IsEmpty())

			return;
		else
		{
			int i=0;
			TCHAR * pstrTok=NULL;
			while(1)
			{
				if(i==0)
				  pstrTok=_tcstok((wchar_t*)(LPCTSTR)str,_T("#"));
				else
					pstrTok=_tcstok(NULL,_T("#"));
				if(pstrTok==NULL)
					break;
                i++;
				CString s=pstrTok;
				int i=s.Find(_T(","));
				CString s1=s.Left(i);
				CString s2= s.Right(s.GetLength()-i-1);
				s1.Trim();
				s2.Trim();
				m_listCalibEntries.InsertItem(0,s1);
				m_listCalibEntries.SetItemText(0,1,s2);


			}
			double * a;//= &m_dblA;
			double * b;//= &m_dblB;
			double * c;//= &m_dblC;
			double * d;//= &m_dblD;
            UINT len=sizeof(double);
			AfxGetApp()->GetProfileBinary(_T("Calib"),_T("a"),(LPBYTE*)&a,&len);
            len=sizeof(double);
			AfxGetApp()->GetProfileBinary(_T("Calib"),_T("b"),(LPBYTE*)&b,&len);
			len=sizeof(double);
			AfxGetApp()->GetProfileBinary(_T("Calib"),_T("c"),(LPBYTE*)&c,&len);
			len=sizeof(double);
			AfxGetApp()->GetProfileBinary(_T("Calib"),_T("d"),(LPBYTE*)&d,&len);

			m_dblA=*a;
			m_dblB=*b;
			m_dblC=*c;
			m_dblD=*d;
			UpdateData(FALSE);

		}
	}


	//if(bSave)
	//{
	//	//Cleanup Calib_Config.INI

	//	BOOL bRes=CreateDirectory(_T("C:\\ELICO"),NULL);
	//	CreateDirectory(_T("C:\\ELICO\\ArraySpectrum"),NULL);
	//	FILE * pf= _wfopen(_T("Calib_Config.ini"),_T("w"));
	//	fclose(pf);
	//	int nCount=m_listCalibEntries.GetItemCount();
	//	CString str;
	//	for(int i=0;i<nCount;i++)
	//	{
	//		str+=m_listCalibEntries.GetItemText(i,0);
	//		str+=_T(",");
	//		str+=m_listCalibEntries.GetItemText(i,1);
	//		str+=_T("#");
	//	}
	//	WritePrivateProfileString(_T("Calib"),_T("PIXEL_WL_MAP"),str,_T("C:\\ELICO\\ArraySpectrum\\Calib_Config.ini"));
	//	//str.Format(_T("%.3f"),m_fA);
	//	str.Format(_T("%.25lf"),m_dblA);
	//	WritePrivateProfileString(_T("Calib"),_T("a"),str,_T("C:\\ELICO\\ArraySpectrum\\Calib_Config.ini"));

	//	//str.Format(_T("%.3f"),m_fB);
	//	str.Format(_T("%.25lf"),m_dblB);
	//	WritePrivateProfileString(_T("Calib"),_T("b"),str,_T("C:\\ELICO\\ArraySpectrum\\Calib_Config.ini"));


	//	//str.Format(_T("%.3f"),m_fC);
	//	str.Format(_T("%.25lf"),m_dblC);
	//	WritePrivateProfileString(_T("Calib"),_T("c"),str,_T("C:\\ELICO\\ArraySpectrum\\Calib_Config.ini"));

	//	//str.Format(_T("%.3f"),m_fD);
	//	str.Format(_T("%.25lf"),m_dblD);
	//	WritePrivateProfileString(_T("Calib"),_T("d"),str,_T("C:\\ELICO\\ArraySpectrum\\Calib_Config.ini"));

	//}
	//else
	//{
	//	TCHAR buff[5000];
	//	GetPrivateProfileString(_T("Calib"),_T("PIXEL_WL_MAP"),_T(""),buff,5000,_T("C:\\ELICO\\ArraySpectrum\\Calib_Config.ini"));
	//	CString str=buff;
	//	if(str.IsEmpty())
	//		return;
	//	else
	//	{
	//		int i=0;
	//		TCHAR * pstrTok=NULL;
	//		while(1)
	//		{
	//			if(i==0)
	//			  pstrTok=_tcstok(buff,_T("#"));
	//			else
	//				pstrTok=_tcstok(NULL,_T("#"));
	//			if(pstrTok==NULL)
	//				break;
 //               i++;
	//			CString s=pstrTok;
	//			int i=s.Find(_T(","));
	//			CString s1=s.Left(i);
	//			CString s2= s.Right(s.GetLength()-i-1);
	//			s1.Trim();
	//			s2.Trim();
	//			m_listCalibEntries.InsertItem(0,s1);
	//			m_listCalibEntries.SetItemText(0,1,s2);


	//		}
	//		GetPrivateProfileString(_T("Calib"),_T("a"),_T("0.0"),buff,5000,_T("C:\\ELICO\\ArraySpectrum\\Calib_Config.ini"));
	//		//m_fA=_wtof(buff);
	//		m_dblA=_tcstod(buff,NULL);
	//		
	//		GetPrivateProfileString(_T("Calib"),_T("b"),_T("0.0"),buff,5000,_T("C:\\ELICO\\ArraySpectrum\\Calib_Config.ini"));
	//		//m_fB=_wtof(buff);
	//		m_dblB=_tcstod(buff,NULL);
	//		
	//		GetPrivateProfileString(_T("Calib"),_T("c"),_T("0.0"),buff,5000,_T("C:\\ELICO\\ArraySpectrum\\Calib_Config.ini"));
	//		//m_fC=_wtof(buff);
	//		m_dblC=_tcstod(buff,NULL);
	//		
	//		GetPrivateProfileString(_T("Calib"),_T("d"),_T("0.0"),buff,5000,_T("C:\\ELICO\\ArraySpectrum\\Calib_Config.ini"));
	//		//m_fD=_wtof(buff);
	//		m_dblD=_tcstod(buff,NULL);

	//	}
	//}
}

void CCalibDataDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	UpdateData();
	SerializeCalibData(TRUE);

	for(int i=0;i<MAX_PIXEL_DATA_COUNT_PER_LINE;i++)
	{

        double x=i;
		double x2=x*x;
		double afact=m_dblA*x2;
		double bfact=m_dblB*x;
		double cfact=m_dblC;

		m_pDoc->m_bufWLDataPoints[i]=afact+bfact+cfact;
		//Convert WL to Raman Shift
		m_pDoc->m_bufRSDataPoints[i] = ((1 / 785) - (1 / m_pDoc->m_bufWLDataPoints[i])) * pow(10, 7);
	}

	DestroyWindow();
}

void CCalibDataDlg::OnBnClickedButtonCalculate()
{
	// TODO: Add your control notification handler code here
	int nCount=0;
	double* ptrdblPixelPts=NULL;
	double* ptrdblWavelengthPts=NULL;
	//double A0,A1,A2,A3;

	nCount=m_listCalibEntries.GetItemCount();
	if(nCount<6)
	{
		AfxMessageBox(_T("Please enter atleast Six Pair of Values"));
		return;
	}
	else
	{
		ptrdblPixelPts=new double[nCount];
		ptrdblWavelengthPts=new double[nCount];
	
		CString strTemp;
		double d;

		for(int nIndex=0;nIndex<m_listCalibEntries.GetItemCount();nIndex++)
		{
			strTemp=m_listCalibEntries.GetItemText(nIndex,0);//Pixel Number
			_stscanf(strTemp,_T("%lf.2"),&d);

			ptrdblPixelPts[nIndex]=d;

			strTemp=m_listCalibEntries.GetItemText(nIndex,1);//Wavelength
			_stscanf(strTemp,_T("%lf.2"),&d);
			ptrdblWavelengthPts[nIndex]=d;   
 		}

		//CCubicSplineInterpolation objCubicSplineInterpolation;
		///////objCubicSplineInterpolation.fncFindCubicPloynomial(nCount,ptrdblPixelPts,ptrdblWavelengthPts,A0,A1,A2,A3);
		
		//objCubicSplineInterpolation.fncFindCubicPloynomial(nCount,ptrdblPixelPts,ptrdblWavelengthPts,m_dblA,m_dblB,m_dblC,m_dblD);
		//BOOL bRes;
		//objCubicSplineInterpolation.FindQuadraticFitCoefficients(nCount,ptrdblPixelPts,ptrdblWavelengthPts, &m_dblA,&m_dblB,&m_dblC,&bRes);
		CQuadraticFit quadFit;
        for(int nIndex=0;nIndex<m_listCalibEntries.GetItemCount();nIndex++)
		{
		  quadFit.AddPoints(ptrdblPixelPts[nIndex],ptrdblWavelengthPts[nIndex]);
		}
		m_dblA=quadFit.aTerm();
		
		m_dblB=quadFit.bTerm();
		
		m_dblC=quadFit.cTerm();
		
		m_dblD=0;
		
		//m_fA=A0;
		//m_fB=A1;
		//m_fC=A2;
		//m_fD=A3;
   
		if(ptrdblPixelPts!=NULL)
		{	
			delete[] ptrdblPixelPts;
			ptrdblPixelPts=NULL;
		}
	
		if(ptrdblWavelengthPts!=NULL)
		{
			delete[] ptrdblWavelengthPts;
			ptrdblWavelengthPts=NULL;
		}
		UpdateData(FALSE);
	}
}

void CCalibDataDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	DestroyWindow();
}
