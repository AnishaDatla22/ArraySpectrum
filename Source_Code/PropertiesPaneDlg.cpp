// PropertiesPaneDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ArraySpectrum.h"
#include "PropertiesPaneDlg.h"
#include "mainfrm.h"
#include "arrayspectrumdoc.h"

// CPropertiesPaneDlg dialog

IMPLEMENT_DYNAMIC(CPropertiesPaneDlg, CDialog)

CPropertiesPaneDlg::CPropertiesPaneDlg(CWnd* pParent /*=NULL*/)
: CDialog(CPropertiesPaneDlg::IDD, pParent)

//, m_nExposureTime(100)
, m_nExposureTime(DEFAULT_EXPOSURE_TIME)
, m_nGain(1)
, m_nLineCount(1)
, m_bShowAverage(TRUE)
, m_bShowRSD(FALSE)
, m_nOffSet(10)
, m_bShowSD(FALSE)
{
	
}

CPropertiesPaneDlg::~CPropertiesPaneDlg()
{
}

void CPropertiesPaneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_EXPOSURE_TIME, m_nExposureTime);
	DDX_Text(pDX, IDC_EDIT_GAIN, m_nGain);
	DDX_Text(pDX, IDC_EDIT_LINE_COUNT, m_nLineCount);
	DDX_Check(pDX, IDC_CHECK_AVERAGE, m_bShowAverage);
	DDX_Check(pDX, IDC_CHECK_RSD, m_bShowRSD);
	DDX_Text(pDX, IDC_EDIT_OFFSET, m_nOffSet);
	DDX_Check(pDX, IDC_CHECK_SD, m_bShowSD);
	DDV_MinMaxInt(pDX, m_nExposureTime, 1, 5000);
	DDV_MinMaxInt(pDX, m_nGain, 1, 10);
	DDV_MinMaxInt(pDX, m_nLineCount, 1, 100);
}


BEGIN_MESSAGE_MAP(CPropertiesPaneDlg, CDialog)

	ON_BN_CLICKED(IDC_BUTTON_APPLY, &CPropertiesPaneDlg::OnBnClickedButtonApply)
END_MESSAGE_MAP()


// CPropertiesPaneDlg message handlers


void CPropertiesPaneDlg::OnBnClickedButtonApply()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CMainFrame * pFrame=(CMainFrame*)AfxGetMainWnd();

	CArraySpectrumDoc* pDoc= (CArraySpectrumDoc*)(pFrame->GetActiveDocument());

	pDoc->m_objCapturePixelBuff.m_nGain=m_nGain;
	pDoc->m_objCapturePixelBuff.m_nExposureTime=m_nExposureTime;
	pDoc->m_objCapturePixelBuff.m_nLineCount=m_nLineCount;
	pDoc->m_objCapturePixelBuff.m_nOffset=m_nOffSet;
	if(m_nLineCount>1)
	{
		pDoc->m_objCapturePixelBuff.m_bShowAvg=m_bShowAverage;
		pDoc->m_objCapturePixelBuff.m_bShowRSD=m_bShowRSD;
		pDoc->m_objCapturePixelBuff.m_bShowSD=m_bShowSD;
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHECK_RSD))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHECK_SD))->SetCheck(FALSE);
		pDoc->m_objCapturePixelBuff.m_bShowRSD=FALSE;
		pDoc->m_objCapturePixelBuff.m_bShowSD=FALSE;
	}
	//Apply the Capture Properties to the Device
	pDoc->ApplyCaptureProperties();
}

BOOL CPropertiesPaneDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here



	/*((CButton*)GetDlgItem(IDC_CHECK_AVERAGE))->SetCheck(TRUE);
	GetDlgItem(IDC_CHECK_AVERAGE)->EnableWindow(FALSE);
	*/

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CPropertiesPaneDlg::InitProperties()
{
	CArraySpectrumDoc* pDoc= (CArraySpectrumDoc*)(((CMainFrame*)AfxGetMainWnd())->GetActiveDocument());

	m_bShowAverage=pDoc->m_objCapturePixelBuff.m_bShowAvg;
	m_bShowSD=pDoc->m_objCapturePixelBuff.m_bShowSD;
	m_bShowRSD=pDoc->m_objCapturePixelBuff.m_bShowRSD;
	m_nExposureTime=pDoc->m_objCapturePixelBuff.m_nExposureTime;
	m_nLineCount=pDoc->m_objCapturePixelBuff.m_nLineCount;
	m_nGain=pDoc->m_objCapturePixelBuff.m_nGain;
	m_nOffSet=pDoc->m_objCapturePixelBuff.m_nOffset;
	UpdateData(FALSE);

}