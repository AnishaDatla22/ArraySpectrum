// SettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ArraySpectrum.h"
#include "SettingsDlg.h"

#include "ArraySpectrumDoc.h"
#include "FlameSettings.h"
//class CFlameSettings;
#include "MainFrm.h"
#include <math.h>

// CSettingsDlg dialog



IMPLEMENT_DYNAMIC(CSettingsDlg, CDialog)

CSettingsDlg::CSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingsDlg::IDD, pParent)
	, m_dblFlamePeakWL(0)
	, m_dblFlamePeakTOLLimits(0)
	, m_dblFlamePeakTHOLD(0)
	, m_dblSPeakWL(0)
	, m_dblSPeakWLTolLimit(0)
	, m_dblSLevel1THLD(0)
	, m_dblSLevel1ThldTolLimit(0)
	, m_dblSLevel2THLD(0)
	, m_dblSLevel2ThldTolLimit(0)
	, m_dblSLevel3THLD(0)
	, m_dblSLevel3ThldTolLimit(0)
	, m_dblSLevel4THLD(0)
	, m_dblSLevel4ThldTolLimit(0)
	, m_dblSLevel5THLD(0)
	, m_dblSLevel5ThldTolLimit(0)
{
  //m_pParent = NULL;
	m_pDoc = NULL;
	//m_arrnCompoundLevelIndicators.RemoveAll();
	//m_arrCompoundEnergyAtPeakWL.RemoveAll();
	m_bShowCompoundSettings = false;
	m_bShowFlameSettings = false;
	m_fntCompoundName.CreateFont(
		20,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,				   // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("Tahoma"));

	m_rectCollapsedSettings = CRect(0,0,365,400);
	m_rectExpandedSettings = CRect(0,0,550,465);
}

CSettingsDlg::~CSettingsDlg()
{
}

void CSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_FLAMMABLE_ON_OFF, m_btnFlameOnOFF);
	DDX_Control(pDX, IDC_BTN_FLAMMABLE_SETTINGS, m_btnFlameSettings);
	DDX_Control(pDX, IDC_EDIT_FLAME_PEAK_WL, m_edtFlamePeakWL);
	DDX_Control(pDX, IDC_EDIT_FLAME_PEAK_WL_TOL_LIMITS, m_edtPeakWLTOLLimit);
	DDX_Control(pDX, IDC_EDIT_FLAME_THRESHOLD, m_edtFlameTHOLD);
	DDX_Text(pDX, IDC_EDIT_FLAME_PEAK_WL, m_dblFlamePeakWL);
	DDX_Text(pDX, IDC_EDIT_FLAME_PEAK_WL_TOL_LIMITS, m_dblFlamePeakTOLLimits);
	DDX_Text(pDX, IDC_EDIT_FLAME_THRESHOLD, m_dblFlamePeakTHOLD);
	DDX_Text(pDX, IDC_EDIT_S_PEAK_WL, m_dblSPeakWL);
	DDX_Text(pDX, IDC_EDIT_S_PEAK_WL_TOL_LIMIT, m_dblSPeakWLTolLimit);
	DDX_Text(pDX, IDC_EDIT_S_LEVEL_1_THLD, m_dblSLevel1THLD);
	DDX_Text(pDX, IDC_EDIT_S_LEVEL_1_THLD_TOL_LIMIT, m_dblSLevel1ThldTolLimit);
	DDX_Text(pDX, IDC_EDIT_S_LEVEL_2_THLD, m_dblSLevel2THLD);
	DDX_Text(pDX, IDC_EDIT_S_LEVEL_2_THLD_TOL_LIMIT, m_dblSLevel2ThldTolLimit);
	DDX_Text(pDX, IDC_EDIT_S_LEVEL_3_THLD, m_dblSLevel3THLD);
	DDX_Text(pDX, IDC_EDIT_S_LEVEL_3_THLD_TOL_LIMIT, m_dblSLevel3ThldTolLimit);
	DDX_Text(pDX, IDC_EDIT_S_LEVEL_4_THLD, m_dblSLevel4THLD);
	DDX_Text(pDX, IDC_EDIT_S_LEVEL_4_THLD_TOL_LIMIT, m_dblSLevel4ThldTolLimit);
	DDX_Text(pDX, IDC_EDIT_S_LEVEL_5_THLD, m_dblSLevel5THLD);
	DDX_Text(pDX, IDC_EDIT_S_LEVEL_5_THLD_TOL_LIMIT, m_dblSLevel5ThldTolLimit);

	DDX_Control(pDX, IDC_COMBO_COMPOUND_NAMES_COL, m_cmbCompoundNames);
	DDX_Control(pDX, IDC_SEL_COMPOUND_NAME, m_staticSelCompoundName);
	DDX_Control(pDX, IDC_S_LEVEL_INDICATOR, m_staticSLevelIndicator);
	DDX_Control(pDX, IDC_P_LEVEL_INDICATOR2, m_staticPLevelIndicator);
	DDX_Control(pDX, IDC_AS_LEVEL_INDICATOR3, m_staticASLevelIndicator);
	DDX_Control(pDX, IDC_HNO_LEVEL_INDICATOR4, m_staticHNOLevelIndicator);

	DDX_Control(pDX, IDC_S_LEVEL_LABLE, m_staticSLevelLable);
	DDX_Control(pDX, IDC_STATIC_P_LEVEL_LABLE, m_staticPLevelLable);
	DDX_Control(pDX, IDC_STATIC_AS_LEVEL_LABLE, m_saticASLevelLable);
	DDX_Control(pDX, IDC_STATIC_HNO_LEVEL_LABLE, m_staticHNOLevelLable);
}


BEGIN_MESSAGE_MAP(CSettingsDlg, CDialog)
	ON_WM_CLOSE()
	//ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_FLAMMABLE_SETTINGS, &CSettingsDlg::OnBnClickedBtnFlammableSettings)
	ON_BN_CLICKED(IDC_BTN_APPLY, &CSettingsDlg::OnBnClickedBtnApply)
	ON_CBN_SELCHANGE(IDC_COMBO_COMPOUND_NAMES_COL, &CSettingsDlg::OnCbnSelchangeComboCompoundNamesCol)
	ON_BN_CLICKED(IDOK, &CSettingsDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_COMPOUND_SETTINGS, &CSettingsDlg::OnBnClickedBtnCompoundSettings)
	ON_STN_CLICKED(IDC_S_LEVEL_INDICATOR, &CSettingsDlg::OnStnClickedSLevelIndicator)
	ON_STN_CLICKED(IDC_STATIC_P_LEVEL_LABLE, &CSettingsDlg::OnStnClickedStaticPLevelLable)
	ON_BN_CLICKED(IDC_BTN_FLAME_APPLY, &CSettingsDlg::OnBnClickedBtnFlameApply)
	ON_MESSAGE(WM_APPLY_SETTINGS,&CSettingsDlg::OnApplySettings)
END_MESSAGE_MAP()


// CSettingsDlg message handlers

void CSettingsDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	// If the user attempts to close the dialog box, we will instead hide it
	ShowWindow(FALSE);
	
	if(m_pDoc != NULL)
		m_pDoc->SerializeSettingsData(TRUE);

	CDialog::OnClose();
}

void CSettingsDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages

}

BOOL CSettingsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	if(m_staticSLevelLable.m_hWnd != NULL)
		m_staticSLevelLable.SetFont(&m_fntCompoundName);
	if(m_staticPLevelLable.m_hWnd != NULL)
		m_staticPLevelLable.SetFont(&m_fntCompoundName);
	if(m_saticASLevelLable.m_hWnd != NULL)
		m_saticASLevelLable.SetFont(&m_fntCompoundName);
	if(m_staticHNOLevelLable.m_hWnd != NULL)
		m_staticHNOLevelLable.SetFont(&m_fntCompoundName);

	// get the rect for the parent
	CRect rectClient;
	GetClientRect(rectClient);

	// flags to ensure SetWindowPos only moves and resizes
	/*UINT flags = SWP_NOSENDCHANGING |SWP_NOACTIVATE | SWP_NOZORDER;
	::SetWindowPos(NULL,HWND_TOP, 0, 0,
		100, 100, SWP_NOSIZE);*/
	//MoveWindow(0,0,400,400);
	CRect rectWindow;
	GetWindowRect(rectWindow);
	MoveWindow(rectWindow.left,rectWindow.top, m_rectCollapsedSettings.Width(),m_rectCollapsedSettings.Height());
	// TODO:  Add extra initialization here
	//ApplyDocDataIntoCtrls();
	
	//ApplyStatesToDlgCtrls();

	m_btnFlameOnOFF.LoadBmp(IDB_BMP_FLAME_ON,IDB_BMP_FLAME_OFF,1);
	m_btnFlameOnOFF.SetCaptionAlignment(0);
	
	//PostMessage(WM_APPLY_SETTINGS,0,0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSettingsDlg::ApplyDocDataIntoCtrls()
{
	if(m_pDoc != NULL)
	{
		//Get the FlameSettings
		CFlameSettings obj = ((CArraySpectrumDoc*)m_pDoc)->m_objSettings.m_objFlameSettings;
		m_dblFlamePeakWL = obj.m_dlPeakWL;
	
		m_dblFlamePeakTOLLimits = obj.m_dlPeakWLTOLLimit;
	
		m_dblFlamePeakTHOLD = obj.m_dblPeakTHLD;
		
		//
		//ApplyFlameSettings();

		//Remvoe all compound names
		m_cmbCompoundNames.ResetContent();

		//Add compound names into the combo
		//int nSizeCompoundNames = ((CArraySpectrumDoc*)m_pDoc)->m_objSettings.m_arrobjCompoundSettings.GetCount();
		for(int nIndex = 0; nIndex < NO_OF_COMPOUNDS; nIndex++)
		{
			CCompoundSettings objCompSettings = ((CArraySpectrumDoc*)m_pDoc)->m_objSettings.m_arrobjCompoundSettings[nIndex];//S compound settings

			m_cmbCompoundNames.AddString(objCompSettings.m_strCompoundName);
		}
		//m_cmbCompoundNames.SetCurSel(0);

		//Set the cur selected compound as zero index
		int nSelIndex = 0;
		m_cmbCompoundNames.SetCurSel(nSelIndex);
		CString strSelCompoundName;
		m_cmbCompoundNames.GetLBText(nSelIndex, strSelCompoundName);
		m_staticSelCompoundName.SetWindowText(strSelCompoundName);
		//Fill the compound setting data
		FillCompoundSettingsCtrl(nSelIndex);
        
		//if(m_arrnCompoundLevelIndicators.GetCount() != 4)
		//	m_arrnCompoundLevelIndicators.SetSize(4);	
			
		//if(m_arrCompoundEnergyAtPeakWL.GetCount() != 4)
		//	m_arrCompoundEnergyAtPeakWL.SetSize(4);

		//for(int nIndex = 0; nIndex < NO_OF_COMPOUNDS; nIndex++)
		//{
		//	m_arrnCompoundLevelIndicators[nIndex] = 0;
		//	m_arrCompoundEnergyAtPeakWL[nIndex]=0;
		//}
		//UpdateCompoundLevelIndicators();
		//Update the data into the dialog controls
		UpdateData(FALSE);
	}
}


void CSettingsDlg::ApplyFlameSettings()
{
	//Get the data from the dialog controls
	UpdateData(true);
	if(m_pDoc == NULL)
		return;

	//Get the current sample ADU/mV value at the provided flame peak wavelength
	//theApp.FindNeareastIndex(m_pDoc->
	if(m_pDoc->m_objCapturePixelBuff.ISEmpty()==FALSE)
	{   
		int nLineCount = m_pDoc->m_objCapturePixelBuff.m_nLineCount;
		int i = 0;
		//Get the Y Values
		//TODO: need to take the average value of Y
		double* ptrdblYvals = NULL;
		//if(nLineCount == 1)
		//{
		//	ptrdblYvals = (double*)m_pDoc->m_objCapturePixelBuff.GetLinePixelBuf(0);
		//}
		//else if(nLineCount > 1)
		//{
			ptrdblYvals = m_pDoc->m_objCapturePixelBuff.m_pBufAvgPixelData;
		//}
		//ptrdblYvals = theApp.m_bufWLDataPoints;
		
		//Find the nearest point for the given peak wavelength
		bool bFound = false;
		int nLowerWLIndex = -1;
		double dblPeakWLLower = m_pDoc->m_objSettings.m_objFlameSettings.m_dlPeakWL - m_pDoc->m_objSettings.m_objFlameSettings.m_dlPeakWLTOLLimit;
		
		m_pDoc->FindNeareastIndex(m_pDoc->m_bufWLDataPoints,MAX_PIXEL_DATA_COUNT_PER_LINE,dblPeakWLLower,&bFound,&nLowerWLIndex);

		int nUpperWLIndex = -1;
		double dblPeakWLUpper = m_pDoc->m_objSettings.m_objFlameSettings.m_dlPeakWL + m_pDoc->m_objSettings.m_objFlameSettings.m_dlPeakWLTOLLimit;
		
		m_pDoc->FindNeareastIndex(m_pDoc->m_bufWLDataPoints,MAX_PIXEL_DATA_COUNT_PER_LINE,dblPeakWLUpper,&bFound,&nUpperWLIndex);

		int nBandWidthSize = 0;
		nBandWidthSize = ((nUpperWLIndex +1) - (nLowerWLIndex -1)) + 1;
		double* ptrdblTempXVals = new double[nBandWidthSize];
		double* ptrdblTempYVals = new double[nBandWidthSize];
		int nStartIndex = (nLowerWLIndex - 1);
		for(int nIndex = 0; nIndex < nBandWidthSize; nIndex++)
		{
			ptrdblTempXVals[nIndex] = m_pDoc->m_bufWLDataPoints[nStartIndex];
			ptrdblTempYVals[nIndex] = ptrdblYvals[nStartIndex];
			nStartIndex++;
		}
			
		double dblLowPkWLInterpolateVal = 0;
		double dblPkWLInterpolateVal = 0;
		double dblUpPkWLInterpolateVal = 0;
		if( bFound == false)
		{
			//get the y value by interpolating the above nearest points
			//TODO: need to handle if the nearest index is a lower bound and upper bound index in the array
			double dblSlope = 0;
			double dblIntercept =0;

			theApp.GetLinearCoefficient(ptrdblTempXVals,ptrdblTempYVals,0,nBandWidthSize,&dblSlope,&dblIntercept);
			
			//ADU/mV value at lower peak wl  
			dblLowPkWLInterpolateVal = (dblSlope)*(dblPeakWLLower) + dblIntercept;
			
			//ADU/mv value at peak wl
			dblPkWLInterpolateVal = (dblSlope)*(m_pDoc->m_objSettings.m_objFlameSettings.m_dlPeakWL) + dblIntercept;

			//ADU/mV value at upper peak wl
			dblUpPkWLInterpolateVal = (dblSlope)*(dblPeakWLUpper) + dblIntercept;
		}
		else
		{
			//TODO:
		}
		
		//Check whether the ADC/mV value at the specific peak wavelength exceeded the Threshold value
		m_bFlameON = false;
		if( (dblLowPkWLInterpolateVal > m_pDoc->m_objSettings.m_objFlameSettings.m_dblPeakTHLD) || 
			(dblPkWLInterpolateVal > m_pDoc->m_objSettings.m_objFlameSettings.m_dblPeakTHLD) ||  
			(dblUpPkWLInterpolateVal > m_pDoc->m_objSettings.m_objFlameSettings.m_dblPeakTHLD) 
			)
		{
			m_bFlameON = true;
		}
		UpdateFlameIndicator();
		
		if(ptrdblTempXVals != NULL)
		{
			delete[] ptrdblTempXVals;
			ptrdblTempXVals = NULL;
		}
		if(ptrdblTempYVals != NULL)
		{
			delete[] ptrdblTempYVals;
			ptrdblTempYVals = NULL;
		}
	}
}

void CSettingsDlg::ApplyStatesToDlgCtrls()
{
	
	UpdateFlameIndicator();

	//S Compound Level
	//m_nSLevelIndicator = m_nSEnergyLevel;

	UpdateCompoundLevelIndicators();

}

void CSettingsDlg::ApplyCtrlsDataIntoDoc()
{
	if(m_pDoc != NULL)
	{
		//Update the data from dialog controls into local variables
		UpdateData(TRUE);
		
		//Update the FlameSettings doc with current settings
		CFlameSettings obj;
		obj.m_dlPeakWL = m_dblFlamePeakWL;
	
		obj.m_dlPeakWLTOLLimit = m_dblFlamePeakTOLLimits;
	
		obj.m_dblPeakTHLD = m_dblFlamePeakTHOLD;

		((CArraySpectrumDoc*)m_pDoc)->m_objSettings.m_objFlameSettings = obj;

		//Update the S Compound Setttings doc with current settings		
		CCompoundSettings objSCompSettings;
		CString strCurCompoundName;
		m_staticSelCompoundName.GetWindowText(strCurCompoundName);

		objSCompSettings.m_strCompoundName = strCurCompoundName; 

		objSCompSettings.m_dlPeakWL = m_dblSPeakWL;

		objSCompSettings.m_dlPeakWLTOLLimit = m_dblSPeakWLTolLimit;

		//if(objSCompSettings.m_arrPKEnergyLevels.GetCount() != 5)
		//	objSCompSettings.m_arrPKEnergyLevels.SetSize(5);
		//objSCompSettings.m_arrPKEnergyLevelsLimits.SetSize(5);
		
		objSCompSettings.m_arrPKEnergyLevels[0] = m_dblSLevel1THLD;

		//objSCompSettings.m_arrPKEnergyLevelsLimits.SetAt(0,m_dblSLevel1ThldTolLimit);

		objSCompSettings.m_arrPKEnergyLevels[1] = m_dblSLevel2THLD;

		//objSCompSettings.m_arrPKEnergyLevelsLimits.SetAt(1,m_dblSLevel2ThldTolLimit);
		
		objSCompSettings.m_arrPKEnergyLevels[2] =m_dblSLevel3THLD;

		//objSCompSettings.m_arrPKEnergyLevelsLimits.SetAt(2,m_dblSLevel3ThldTolLimit);

		objSCompSettings.m_arrPKEnergyLevels[3] = m_dblSLevel4THLD;

		//objSCompSettings.m_arrPKEnergyLevelsLimits.SetAt(3,m_dblSLevel4ThldTolLimit);

		objSCompSettings.m_arrPKEnergyLevels[4] = m_dblSLevel5THLD;

		//objSCompSettings.m_arrPKEnergyLevelsLimits.SetAt(4,m_dblSLevel5ThldTolLimit);
		//if(((CArraySpectrumDoc*)m_pDoc)->m_objSettings.m_arrobjCompoundSettings.GetCount() != 4)
	    //	((CArraySpectrumDoc*)m_pDoc)->m_objSettings.m_arrobjCompoundSettings.SetSize(4);

		
		//int nCount = ((CArraySpectrumDoc*)m_pDoc)->m_objSettings.m_arrobjCompoundSettings.GetCount();
		CString strTempCompoundName;
		CCompoundSettings objTemp;
		int nPrevSelIndex = -1;
		for(int nIndex = 0; nIndex < NO_OF_COMPOUNDS; nIndex++)
		{
			objTemp = ((CArraySpectrumDoc*)m_pDoc)->m_objSettings.m_arrobjCompoundSettings[nIndex];
			strTempCompoundName = objTemp.m_strCompoundName;
			if(strTempCompoundName.CompareNoCase(strCurCompoundName) == 0)
			{
				nPrevSelIndex = nIndex;
				break;
			}
		}
		if(nPrevSelIndex != -1)
			((CArraySpectrumDoc*)m_pDoc)->m_objSettings.m_arrobjCompoundSettings[nPrevSelIndex] = objSCompSettings;
	}
}

void CSettingsDlg::ApplyCompoundSettings()
{
	//Get the current sample ADU/mV value at the provided flame peak wavelength
	//theApp.FindNeareastIndex(m_pDoc->
	CMainFrame* pWnd=NULL;
	pWnd=(CMainFrame*)GetParent();
	if((m_pDoc->m_objCapturePixelBuff.ISEmpty()==FALSE) && (pWnd->m_PresentationMode==CMainFrame::VIEW_MODE::WAVELENGTH_MODE))
	{
		//Get the Y Values(ADU data)
		//TODO: need to take the average value of Y
		double* ptrdblYvals = NULL;
		//if(m_pDoc->m_objCapturePixelBuff.m_nLineCount == 1)
		//	ptrdblYvals = (double*)m_pDoc->m_objCapturePixelBuff.GetLinePixelBuf(0);
		//else
			ptrdblYvals = m_pDoc->m_objCapturePixelBuff.m_pBufAvgPixelData;
		//ptrdblYvals = m_pDoc->m_objCapturePixelBuff.m_pBufAvgPixelData;

		//Find the nearest point for the given peak wavelength
		bool bFound = false;
		int nLowerWLIndex = -1;
		for(int nCompIndex = 0; nCompIndex < NO_OF_COMPOUNDS ; nCompIndex++)
		{
			CCompoundSettings objSCompoundSettings = m_pDoc->m_objSettings.m_arrobjCompoundSettings[nCompIndex];
			double dblPeakWLLower = objSCompoundSettings.m_dlPeakWL - objSCompoundSettings.m_dlPeakWLTOLLimit;

			m_pDoc->FindNeareastIndex(m_pDoc->m_bufWLDataPoints,MAX_PIXEL_DATA_COUNT_PER_LINE,dblPeakWLLower,&bFound,&nLowerWLIndex);

			int nUpperWLIndex = -1;
			double dblPeakWLUpper = objSCompoundSettings.m_dlPeakWL + objSCompoundSettings.m_dlPeakWLTOLLimit;

			m_pDoc->FindNeareastIndex(m_pDoc->m_bufWLDataPoints,MAX_PIXEL_DATA_COUNT_PER_LINE,dblPeakWLUpper,&bFound,&nUpperWLIndex);

			int nBandWidthSize = 0;
			nBandWidthSize = ((nUpperWLIndex +1) - (nLowerWLIndex -1)) + 1;
			double* ptrdblTempXVals = new double[nBandWidthSize];
			double* ptrdblTempYVals = new double[nBandWidthSize];
			int nStartIndex = (nLowerWLIndex - 1);
			for(int nIndex = 0; nIndex < nBandWidthSize; nIndex++)
			{
				ptrdblTempXVals[nIndex] = m_pDoc->m_bufWLDataPoints[nStartIndex];
				ptrdblTempYVals[nIndex] = ptrdblYvals[nStartIndex];
				nStartIndex++;
			}

			double dblPkWLInterpolateVal = 0;
			if( bFound == false)
			{
				//get the y value by interpolating using above points
				double dblSlope = 0;
				double dblIntercept = 0;

				theApp.GetLinearCoefficient(ptrdblTempXVals,ptrdblTempYVals,0,nBandWidthSize,&dblSlope,&dblIntercept);

				//ADU/mv value at peak wl
				dblPkWLInterpolateVal = (dblSlope)*(objSCompoundSettings.m_dlPeakWL) + dblIntercept;
				m_arrCompoundEnergyAtPeakWL[nCompIndex] = dblPkWLInterpolateVal;
				////is it above level 1?
				//if( (dblPkWLInterpolateVal > (objSCompoundSettings.m_dblPeakTHLD - objSCompoundSettings.m_dblPeakTHLDTOLLimit) ) ||
				//	(dblPkWLInterpolateVal > (objSCompoundSettings.m_dblPeakTHLD) ) ||
				//	(dblPkWLInterpolateVal > (objSCompoundSettings.m_dblPeakTHLD + objSCompoundSettings.m_dblPeakTHLDTOLLimit) )
				//	)
				//{
				//	m_nSEnergyLevel = 1;//Yellow
				//}

				for(int nIndex = 0; nIndex < NO_OF_ENERGY_LEVELS; nIndex++)
				{
					//if( (dblPkWLInterpolateVal > (objSCompoundSettings.m_arrPKEnergyLevels.GetAt(nIndex) - objSCompoundSettings.m_arrPKEnergyLevelsLimits.GetAt(nIndex)) ) ||
					//	(dblPkWLInterpolateVal > (objSCompoundSettings.m_arrPKEnergyLevels.GetAt(nIndex)) ) ||
					//	(dblPkWLInterpolateVal > (objSCompoundSettings.m_arrPKEnergyLevels.GetAt(nIndex) - objSCompoundSettings.m_arrPKEnergyLevelsLimits.GetAt(nIndex)) )
					if( dblPkWLInterpolateVal > (objSCompoundSettings.m_arrPKEnergyLevels[nIndex]))
					{
						//m_nSEnergyLevel = nIndex + 1;//from Level1 it is Yellow and from Level2 it is Red
						m_arrnCompoundLevelIndicators[nCompIndex] = (nIndex+1);
						//break;
					}
				}
			}
			else
			{
				//TODO:
			}

			if(ptrdblTempXVals != NULL)
			{
				delete[] ptrdblTempXVals;
				ptrdblTempXVals = NULL;
			}
			if(ptrdblTempYVals != NULL)
			{
				delete[] ptrdblTempYVals;
				ptrdblTempYVals = NULL;
			}
		}
	}
}
void CSettingsDlg::OnBnClickedBtnFlammableSettings()
{
	// TODO: Add your control notification handler code here
	CMainFrame* pWnd=NULL;
	pWnd=(CMainFrame*)GetParent();
	if((pWnd != NULL) && (pWnd->m_hWnd != NULL))
	{
		if(pWnd->m_bStartCapturing == TRUE)
			return;
	}
	if(m_bShowFlameSettings == false)
	{
		GetDlgItem(IDC_BTN_FLAMMABLE_SETTINGS)->SetWindowText(_T("Hide Settings"));
		m_bShowFlameSettings = true;
	}
	else if(m_bShowFlameSettings == true)
	{
		GetDlgItem(IDC_BTN_FLAMMABLE_SETTINGS)->SetWindowText(_T("Show Settings"));
		m_bShowFlameSettings = false;
	}
	ShowOrHideFlameSettings(m_bShowFlameSettings);
}

void CSettingsDlg::OnBnClickedBtnApply()
{
	// TODO: Add your control notification handler code here
	ApplyCtrlsDataIntoDoc();
	//if(m_pDoc != NULL)
	//	m_pDoc->UpdateAllViews(NULL);
	
	//WM_CALCULATE_AREA
	CMainFrame* pWnd=NULL;
	pWnd=(CMainFrame*)GetParent();
	if((pWnd != NULL) && (pWnd->m_hWnd != NULL))
	{
		pWnd->CalculateArea();
	}

	ApplyFlameSettings();
	//ApplyCompoundSettings();
	
	ApplyStatesToDlgCtrls();
	Invalidate();
}


void CSettingsDlg::OnCbnSelchangeComboCompoundNamesCol()
{
	// TODO: Add your control notification handler code here
	//Fill the selected compound respective data into the dlg ctrls
	int nCurSelIndex = -1;
	nCurSelIndex = m_cmbCompoundNames.GetCurSel();
	if(nCurSelIndex != -1)
	{
		////save the current settings into the document
		////get the current compound name
		//CString strCurCompoundName;
		//m_staticSelCompoundName.GetWindowText(strCurCompoundName);
		//int nCount = ((CArraySpectrumDoc*)m_pDoc)->m_objSettings.m_arrobjCompoundSettings.GetCount();
		//CString strTempCompoundName;
		//CCompoundSettings objTemp;
		//int nPrevSelIndex = -1;
		//for(int nIndex = 0; nIndex < nCount; nIndex++)
		//{
		//	objTemp = ((CArraySpectrumDoc*)m_pDoc)->m_objSettings.m_arrobjCompoundSettings.GetAt(nIndex);
		//	strTempCompoundName = objTemp.m_strCompoundName;
		//	if(strTempCompoundName.CompareNoCase(strCurCompoundName) == 0)
		//	{
		//		nPrevSelIndex = nIndex;
		//		break;
		//	}
		//}
		//if(nPrevSelIndex != -1)
		//	UpdateCompoundSettingIntoDoc(nPrevSelIndex);

		CString strSelCompoundName;
		m_cmbCompoundNames.GetLBText(nCurSelIndex, strSelCompoundName);
		m_staticSelCompoundName.SetWindowText(strSelCompoundName);
		FillCompoundSettingsCtrl(nCurSelIndex);
		UpdateData(FALSE);
	}
}

void CSettingsDlg::FillCompoundSettingsCtrl(int nSelIndex)
{
	//Get S Compound Settings
	CCompoundSettings objCompSettings = ((CArraySpectrumDoc*)m_pDoc)->m_objSettings.m_arrobjCompoundSettings[nSelIndex];//S compound settings

	m_staticSelCompoundName.SetWindowText(objCompSettings.m_strCompoundName);

	m_dblSPeakWL = objCompSettings.m_dlPeakWL;

	m_dblSPeakWLTolLimit = objCompSettings.m_dlPeakWLTOLLimit;

	//if(objCompSettings.m_arrPKEnergyLevels.GetCount() != 5)
	//{
	//	objCompSettings.m_arrPKEnergyLevels.SetSize(5);
	//}

	//if(objCompSettings.m_arrPKEnergyLevels.GetCount() > 0 && objCompSettings.m_arrPKEnergyLevelsLimits.GetCount() > 0)
	//if(objCompSettings.m_arrPKEnergyLevels.GetCount() > 0)
	//{
		m_dblSLevel1THLD = objCompSettings.m_arrPKEnergyLevels[0];

		//m_dblSLevel1ThldTolLimit = objCompSettings.m_arrPKEnergyLevelsLimits.GetAt(0);

		m_dblSLevel2THLD = objCompSettings.m_arrPKEnergyLevels[1];

		//m_dblSLevel2ThldTolLimit = objCompSettings.m_arrPKEnergyLevelsLimits.GetAt(1);

		m_dblSLevel3THLD = objCompSettings.m_arrPKEnergyLevels[2];

		//m_dblSLevel3ThldTolLimit = objCompSettings.m_arrPKEnergyLevelsLimits.GetAt(2);

		m_dblSLevel4THLD = objCompSettings.m_arrPKEnergyLevels[3];

		//m_dblSLevel4ThldTolLimit = objCompSettings.m_arrPKEnergyLevelsLimits.GetAt(3);

		m_dblSLevel5THLD = objCompSettings.m_arrPKEnergyLevels[4];

		//m_dblSLevel5ThldTolLimit = objCompSettings.m_arrPKEnergyLevelsLimits.GetAt(4);
	//}
	//Update the data into the dialog controls
	//UpdateData(FALSE);
}

void CSettingsDlg::UpdateCompoundLevelIndicators()
{
	/*CString strTemp;
	strTemp.Format(_T("%d"), m_arrnCompoundLevelIndicators.GetAt(0));
	m_staticSLevelIndicator.SetWindowText(strTemp);
	strTemp.Format(_T("%d"), m_arrnCompoundLevelIndicators.GetAt(1));
	m_staticPLevelIndicator.SetWindowText(strTemp);
	strTemp.Format(_T("%d"), m_arrnCompoundLevelIndicators.GetAt(2));
	m_staticASLevelIndicator.SetWindowText(strTemp);
	strTemp.Format(_T("%d"), m_arrnCompoundLevelIndicators.GetAt(3));
	m_staticHNOLevelIndicator.SetWindowText(strTemp);*/
	//Get S Compound Settings
	CCompoundSettings objCompSettings;
	int nLevel; 
	
	if(m_pDoc == NULL)
		return;

	for(int j = 0; j < NO_OF_COMPOUNDS; j++)
	{
		m_arrnCompoundLevelIndicators[j] = 0;
	}

	//<--Testing
	//CString strPeakVals,strTemp;
	//for(int i = 0; i < NO_OF_COMPOUNDS; i++)
	//{
	//	strTemp.Format(_T("%.2lf,"),((CArraySpectrumDoc*)m_pDoc)->m_arrdblCompoundPeakArea[i]);
	//	strPeakVals += strTemp; 
	//}
	//GetDlgItem(IDC_STATIC_PEAK_VALS)->SetWindowText(strPeakVals);
	//<--Testing

    //Apply square root on Sulphur Peak Energy value
	/*for(int nCompIndex = 0; nCompIndex < NO_OF_COMPOUNDS; nCompIndex++)
	{
		objCompSettings = ((CArraySpectrumDoc*)m_pDoc)->m_objSettings.m_arrobjCompoundSettings[nCompIndex];
		if(objCompSettings.m_strCompoundName.CompareNoCase(SULPHUR_COMPOUND) == 0)
		{
			double dblPeakArea = ((CArraySpectrumDoc*)m_pDoc)->m_arrdblCompoundPeakArea[nCompIndex];
			dblPeakArea = sqrt(dblPeakArea);
			((CArraySpectrumDoc*)m_pDoc)->m_arrdblCompoundPeakArea[nCompIndex] = dblPeakArea;
			break;
		}
	}*/

	for(int nCompIndex = 0; nCompIndex < NO_OF_COMPOUNDS; nCompIndex++)
	{
		objCompSettings = ((CArraySpectrumDoc*)m_pDoc)->m_objSettings.m_arrobjCompoundSettings[nCompIndex];
		for(int nIndex = 0; nIndex < NO_OF_ENERGY_LEVELS; nIndex++)
		{
			//if( (dblPkWLInterpolateVal > (objSCompoundSettings.m_arrPKEnergyLevels.GetAt(nIndex) - objSCompoundSettings.m_arrPKEnergyLevelsLimits.GetAt(nIndex)) ) ||
			//	(dblPkWLInterpolateVal > (objSCompoundSettings.m_arrPKEnergyLevels.GetAt(nIndex)) ) ||
			//	(dblPkWLInterpolateVal > (objSCompoundSettings.m_arrPKEnergyLevels.GetAt(nIndex) - objSCompoundSettings.m_arrPKEnergyLevelsLimits.GetAt(nIndex)) )
			if( ((CArraySpectrumDoc*)m_pDoc)->m_arrdblCompoundPeakArea[nCompIndex] > (objCompSettings.m_arrPKEnergyLevels[nIndex]))
			{
				//m_nSEnergyLevel = nIndex + 1;//from Level1 it is Yellow and from Level2 it is Red
				m_arrnCompoundLevelIndicators[nCompIndex] = (nIndex+1);
				//break;
			}
		}
	}

	for(int nIndex = 0; nIndex < NO_OF_COMPOUNDS; nIndex++)
	{
		objCompSettings = ((CArraySpectrumDoc*)m_pDoc)->m_objSettings.m_arrobjCompoundSettings[nIndex];
		nLevel = m_arrnCompoundLevelIndicators[nIndex];
		if(nIndex == 0)
		{
			m_staticSLevelIndicator.SetMinMaxEnergyVals(objCompSettings.m_arrPKEnergyLevels[0],objCompSettings.m_arrPKEnergyLevels[(NO_OF_ENERGY_LEVELS-1)]);
			//m_staticSLevelIndicator.SetBaseEnergyVal(objCompSettings.m_arrPKEnergyLevels[1]);
			//if(nLevel > 0)
			//{
				//m_staticSLevelIndicator.SetCurEnergyVal(m_arrCompoundEnergyAtPeakWL[nIndex]);
				//m_staticSLevelIndicator.SetCurEnergyVal(((CArraySpectrumDoc*)m_pDoc)->m_arrdblCompoundPeakArea[nIndex]);
				m_staticSLevelIndicator.SetCurEnergyLevel(nLevel);
			//}
		}
		else if(nIndex == 1)
		{
			m_staticPLevelIndicator.SetMinMaxEnergyVals(objCompSettings.m_arrPKEnergyLevels[0],objCompSettings.m_arrPKEnergyLevels[(NO_OF_ENERGY_LEVELS-1)]);
			//m_staticPLevelIndicator.SetBaseEnergyVal(objCompSettings.m_arrPKEnergyLevels[1]);
			//if(nLevel > 0)
			//{
				//m_staticPLevelIndicator.SetCurEnergyVal(m_arrCompoundEnergyAtPeakWL[nIndex]);
				//m_staticPLevelIndicator.SetCurEnergyVal(((CArraySpectrumDoc*)m_pDoc)->m_arrdblCompoundPeakArea[nIndex]);
				m_staticPLevelIndicator.SetCurEnergyLevel(nLevel);
			//}
		}
		else if(nIndex ==2)
		{
			m_staticASLevelIndicator.SetMinMaxEnergyVals(objCompSettings.m_arrPKEnergyLevels[0],objCompSettings.m_arrPKEnergyLevels[(NO_OF_ENERGY_LEVELS-1)]);
			//m_staticASLevelIndicator.SetBaseEnergyVal(objCompSettings.m_arrPKEnergyLevels[1]);
			//if(nLevel > 0)
			//{
				//m_staticASLevelIndicator.SetCurEnergyVal(m_arrCompoundEnergyAtPeakWL[nIndex]);
				//m_staticASLevelIndicator.SetCurEnergyVal(((CArraySpectrumDoc*)m_pDoc)->m_arrdblCompoundPeakArea[nIndex]);
				m_staticASLevelIndicator.SetCurEnergyLevel(nLevel);
			//}
		}
		else if(nIndex == 3)
		{
			m_staticHNOLevelIndicator.SetMinMaxEnergyVals(objCompSettings.m_arrPKEnergyLevels[0],objCompSettings.m_arrPKEnergyLevels[(NO_OF_ENERGY_LEVELS-1)]);
			//m_staticHNOLevelIndicator.SetBaseEnergyVal(objCompSettings.m_arrPKEnergyLevels[1]);
			//if(nLevel > 0)
			//{
				//m_staticHNOLevelIndicator.SetCurEnergyVal(m_arrCompoundEnergyAtPeakWL[nIndex]);
				//m_staticHNOLevelIndicator.SetCurEnergyVal(((CArraySpectrumDoc*)m_pDoc)->m_arrdblCompoundPeakArea[nIndex]);
				m_staticHNOLevelIndicator.SetCurEnergyLevel(nLevel);
			//}
		}
	}
	
	///*objCompSettings = ((CArraySpectrumDoc*)m_pDoc)->m_objSettings.m_arrobjCompoundSettings[1];
	//nLevel = m_arrnCompoundLevelIndicators[1];
	//m_staticPLevelIndicator.SetMinMaxEnergyVals(objCompSettings.m_arrPKEnergyLevels[0],objCompSettings.m_arrPKEnergyLevels[(NO_OF_ENERGY_LEVELS-1)]);
	//m_staticPLevelIndicator.SetBaseEnergyVal(objCompSettings.m_arrPKEnergyLevels[1]);
	//if(nLevel > 0)
	//	m_staticPLevelIndicator.SetCurEnergyVal(m_arrCompoundEnergyAtPeakWL[1]);
	//
	//objCompSettings = ((CArraySpectrumDoc*)m_pDoc)->m_objSettings.m_arrobjCompoundSettings[2];
	//nLevel = m_arrnCompoundLevelIndicators[2];
	//m_staticASLevelIndicator.SetMinMaxEnergyVals(objCompSettings.m_arrPKEnergyLevels[0],objCompSettings.m_arrPKEnergyLevels[(NO_OF_ENERGY_LEVELS-1)]);
	//m_staticASLevelIndicator.SetBaseEnergyVal(objCompSettings.m_arrPKEnergyLevels[1]);
	//if(nLevel > 0)
	//	m_staticASLevelIndicator.SetCurEnergyVal(m_arrCompoundEnergyAtPeakWL[2]);
	//
	//objCompSettings = ((CArraySpectrumDoc*)m_pDoc)->m_objSettings.m_arrobjCompoundSettings[3];
	//nLevel = m_arrnCompoundLevelIndicators[3];
	//m_staticHNOLevelIndicator.SetMinMaxEnergyVals(objCompSettings.m_arrPKEnergyLevels[0],objCompSettings.m_arrPKEnergyLevels[(NO_OF_ENERGY_LEVELS-1)]);
	//m_staticHNOLevelIndicator.SetBaseEnergyVal(objCompSettings.m_arrPKEnergyLevels[1]);
	//if(nLevel > 0)
	//	m_staticHNOLevelIndicator.SetCurEnergyVal(m_arrCompoundEnergyAtPeakWL[3]);
	//*/
}

void CSettingsDlg::SerializeSettingsData(bool bSave)
{
	// if bSave is TRUE, The Calibration settings are saved to a INI file otherwise they will be rerieved from the 
	if(bSave)
	{
		//Cleanup Calib_Config.INI
		CSettings objTempSettings = ((CArraySpectrumDoc*)m_pDoc)->m_objSettings;
		//FlameSettings
		CString str;
		str.Format(_T("%lf,%lf,%lf"),objTempSettings.m_objFlameSettings.m_dlPeakWL,objTempSettings.m_objFlameSettings.m_dlPeakWLTOLLimit,objTempSettings.m_objFlameSettings.m_dblPeakTHLD);
		
		AfxGetApp()->WriteProfileString(_T("Settings"),_T("FlameSettings"),str);

		CCompoundSettings obj;
		//Compound Size
		CString strCompound;
	
		int nCount = NO_OF_COMPOUNDS;
		str.Format(_T("%d"),nCount);
		AfxGetApp()->WriteProfileString(_T("Settings"),_T("CompoundSize"),str);

		//Compound Names
		for(int nIndex = 0; nIndex < nCount; nIndex++)
		{
			obj = objTempSettings.m_arrobjCompoundSettings[nIndex];
			if(nIndex = nCount)
				str = str + (obj.m_strCompoundName);
			else
				str = str +( obj.m_strCompoundName + _T(","));
		}
		AfxGetApp()->WriteProfileString(_T("Settings"),_T("CompoundNames"),str);
		
		
		//Compound Settings
		
		for(int nIndex = 0; nIndex < nCount; nIndex++)
		{
			obj = objTempSettings.m_arrobjCompoundSettings[nIndex];
			strCompound = obj.m_strCompoundName;
			strCompound += _T("Settings");
			str.Format(_T("%lf,%lf"),obj.m_dlPeakWL,obj.m_dlPeakWLTOLLimit);
			CString strEnergyLevels;
			for(int nLevelIndex = 0; nLevelIndex < NO_OF_ENERGY_LEVELS; nLevelIndex++)
			{
				CString strTemp;
				strTemp.Format(_T(",%lf"), obj.m_arrPKEnergyLevels[nLevelIndex] );
				strEnergyLevels += strTemp;
			}
			str = str + strEnergyLevels;
			int nLen = str.GetLength() + 1;
			LPBYTE pByte = new BYTE[nLen];
			memcpy(pByte, (VOID*)LPCTSTR(str), nLen-1);
			AfxGetApp()->WriteProfileBinary(_T("Settings"),strCompound,pByte,nLen);
			delete[] pByte;
			pByte = NULL;
		}
	}
	else
	{
		CSettings objTempSettings;
		int i=0;
		TCHAR *next_token = NULL;
		TCHAR *pstrTok=NULL;
		CStringArray arrStrTokenizedData;
		CFlameSettings obj;
			
		//Flame Settings
		CString str=AfxGetApp()->GetProfileString(_T("Settings"),_T("FlameSettings"));
		if(str.IsEmpty()!= TRUE)
		{
			while(1)
			{
				if(i == 0)
					pstrTok = _tcstok_s((wchar_t*)(LPCTSTR)str,_T(","),&next_token);
				else
					pstrTok = _tcstok_s(NULL,_T(","),&next_token);
				if(pstrTok==NULL)
					break;
				str = pstrTok;
				arrStrTokenizedData.Add(str);
			}
			if((arrStrTokenizedData.GetCount() > 0) && (arrStrTokenizedData.GetCount() == 3))
			{
				obj.m_dlPeakWL = _tcstod(arrStrTokenizedData.GetAt(0),NULL);
				obj.m_dlPeakWLTOLLimit = _tcstod(arrStrTokenizedData.GetAt(1),NULL);
				obj.m_dblPeakTHLD = _tcstod(arrStrTokenizedData.GetAt(2),NULL);
			}
		}
		objTempSettings.m_objFlameSettings = obj;

		//Compound count
		int nCount = 0;
		str = AfxGetApp()->GetProfileString(_T("Settings"),_T("CompoundSize"));
		nCount = _tcstol(str,NULL,10);
		
		//Compound Names
		str = AfxGetApp()->GetProfileString(_T("Settings"),_T("CompoundNames"));
		CStringArray arrStrCompoundNames;
		if(str.IsEmpty()!= TRUE)
		{
			while(1)
			{
				if(i == 0)
					pstrTok = _tcstok_s((wchar_t*)(LPCTSTR)str,_T(","),&next_token);
				else
					pstrTok = _tcstok_s(NULL,_T(","),&next_token);
				if(pstrTok==NULL)
					break;
				str = pstrTok;
				arrStrCompoundNames.Add(str);
			}
		}

		//Compound Settings
		CCompoundSettings arrCompoundSettings[NO_OF_COMPOUNDS];
		CString strCompound;
		for(int nIndex = 0; nIndex <  nCount; nIndex++)
		{
			strCompound = arrStrCompoundNames.GetAt(nIndex);
			strCompound += _T("Settings");
			CString str = AfxGetApp()->GetProfileString(_T("Settings"),strCompound);
			arrStrTokenizedData.RemoveAll();
			arrStrTokenizedData.FreeExtra();
			if(str.IsEmpty() != TRUE)
			{
				while(1)
				{
					if(i == 0)
						pstrTok = _tcstok_s((wchar_t*)(LPCTSTR)str,_T(","),&next_token);
					else
						pstrTok = _tcstok_s(NULL,_T(","),&next_token);
					if(pstrTok == NULL)
						break;
					str = pstrTok;
					arrStrTokenizedData.Add(str);
				}
			}
			if((arrStrTokenizedData.GetCount() > 0) && (arrStrTokenizedData.GetCount() == NO_OF_COMPOUNDS))
			{
				int i = 0;
				CCompoundSettings obj;
				//obj.m_arrPKEnergyLevels.SetSize(5);
				//obj.m_arrPKEnergyLevelsLimits.SetSize(5);
				obj.m_strCompoundName = arrStrCompoundNames.GetAt(nIndex);
				obj.m_dlPeakWL = _tcstod(arrStrTokenizedData.GetAt(i++),NULL);
				obj.m_dlPeakWLTOLLimit = _tcstod(arrStrTokenizedData.GetAt(i++),NULL);
				for(int nLevelIndex = 0; nLevelIndex < NO_OF_ENERGY_LEVELS; nLevelIndex++)
				{
					//obj.m_arrPKEnergyLevels.SetAt(nLevelIndex, _tcstod(arrStrTokenizedData.GetAt(i++),NULL));
					//obj.m_arrPKEnergyLevelsLimits.SetAt(nLevelIndex, _tcstod(arrStrTokenizedData.GetAt(i++),NULL));
					obj.m_arrPKEnergyLevels[nLevelIndex] = _tcstod(arrStrTokenizedData.GetAt(i++),NULL);
					//obj.m_arrPKEnergyLevelsLimits[nLevelIndex] = _tcstod(arrStrTokenizedData.GetAt(i++),NULL);
				}
				//arrCompoundSettings[nIndex] = obj;
				objTempSettings.m_arrobjCompoundSettings[nIndex] = obj;
			}
						
		}
		//objTempSettings.m_arrobjCompoundSettings = arrCompoundSettings;
		((CArraySpectrumDoc*)m_pDoc)->m_objSettings = objTempSettings;
	}
}

void CSettingsDlg::UpdateCompoundSettingIntoDoc(int nSelIndex)
{
	UpdateData(TRUE);

	//Get S Compound Settings
	CCompoundSettings objCompSettings = ((CArraySpectrumDoc*)m_pDoc)->m_objSettings.m_arrobjCompoundSettings[nSelIndex];//S compound settings

	CString strCompoundName;
	m_staticSelCompoundName.GetWindowText(strCompoundName);

	objCompSettings.m_strCompoundName = strCompoundName;


	objCompSettings.m_dlPeakWL = m_dblSPeakWL;

	objCompSettings.m_dlPeakWLTOLLimit = m_dblSPeakWLTolLimit;
	//if(objCompSettings.m_arrPKEnergyLevels.GetCount() != 5)
	//	objCompSettings.m_arrPKEnergyLevels.SetSize(5);

	objCompSettings.m_arrPKEnergyLevels[0] = m_dblSLevel1THLD;

	//objCompSettings.m_arrPKEnergyLevelsLimits.SetAt(0,m_dblSLevel1ThldTolLimit);

	objCompSettings.m_arrPKEnergyLevels[1] = m_dblSLevel2THLD;

	//objCompSettings.m_arrPKEnergyLevelsLimits.SetAt(1,m_dblSLevel2ThldTolLimit);

	objCompSettings.m_arrPKEnergyLevels[2] = m_dblSLevel3THLD;

	//objCompSettings.m_arrPKEnergyLevelsLimits.SetAt(2,m_dblSLevel3ThldTolLimit);

	objCompSettings.m_arrPKEnergyLevels[3] = m_dblSLevel4THLD;

	//objCompSettings.m_arrPKEnergyLevelsLimits.SetAt(3,m_dblSLevel4ThldTolLimit);

	objCompSettings.m_arrPKEnergyLevels[4] = m_dblSLevel5THLD;

	//objCompSettings.m_arrPKEnergyLevelsLimits.SetAt(4,m_dblSLevel5ThldTolLimit);

	((CArraySpectrumDoc*)m_pDoc)->m_objSettings.m_arrobjCompoundSettings[nSelIndex] = objCompSettings;
}


void CSettingsDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	
	if(m_pDoc != NULL)
		m_pDoc->SerializeSettingsData(TRUE);

	OnOK();
}


void CSettingsDlg::ShowOrHideFlameSettings(bool bShow)
{
	GetDlgItem(IDC_PEAK_WL_LABEL)->ShowWindow(bShow);
	GetDlgItem(IDC_STATIC_FALME_WL_TOL_LIMIT)->ShowWindow(bShow);
	GetDlgItem(IDC_STATIC_FLAME_THOLD)->ShowWindow(bShow);
	m_edtFlamePeakWL.ShowWindow(bShow);
	m_edtPeakWLTOLLimit.ShowWindow(bShow);
	m_edtFlameTHOLD.ShowWindow(bShow);
	GetDlgItem(IDC_STATIC_WAVELENGTH_UNITS)->ShowWindow(bShow);
	GetDlgItem(IDC_STATIC_WAVELENGTH_UNITS2)->ShowWindow(bShow);
	GetDlgItem(IDC_THRESHOLD_UNITS)->ShowWindow(bShow);
	GetDlgItem(IDC_BTN_FLAME_APPLY)->ShowWindow(bShow);
}

void CSettingsDlg::ShowOrHideCompoundSettings(bool bShow)
{
	GetDlgItem(IDC_SELECT_COMPOUND_LABEL)->ShowWindow(bShow);
	m_cmbCompoundNames.ShowWindow(bShow);
	GetDlgItem(IDC_STATIC_S_PEAK_WL)->ShowWindow(bShow);
	GetDlgItem(IDC_STATIC_S_PEAK_WL_TOL_LIMIT)->ShowWindow(bShow);
	GetDlgItem(IDC_S_LEVEL1_THLD_LABEL)->ShowWindow(bShow);
	GetDlgItem(IDC_S_LEVEL2_THLD_LABEL)->ShowWindow(bShow);
	GetDlgItem(IDC_S_LEVEL_3_THLD_LABEL)->ShowWindow(bShow);
	GetDlgItem(IDC_S_LEVEL_4_THLD_LABEL)->ShowWindow(bShow);
	GetDlgItem(IDC_S_LEVEL_5_THLD)->ShowWindow(bShow);
	GetDlgItem(IDC_COMPOUND_LABEL)->ShowWindow(bShow);
	m_staticSelCompoundName.ShowWindow(bShow);
	GetDlgItem(IDC_STATIC_WAVELENGTH_UNITS3)->ShowWindow(bShow);
	GetDlgItem(IDC_STATIC_WAVELENGTH_UNITS4)->ShowWindow(bShow);
	GetDlgItem(IDC_THRESHOLD_UNITS2)->ShowWindow(bShow);
	GetDlgItem(IDC_THRESHOLD_UNITS4)->ShowWindow(bShow);
	GetDlgItem(IDC_THRESHOLD_UNITS6)->ShowWindow(bShow);
	GetDlgItem(IDC_THRESHOLD_UNITS8)->ShowWindow(bShow);
	GetDlgItem(IDC_THRESHOLD_UNITS11)->ShowWindow(bShow);
	GetDlgItem(IDC_EDIT_S_PEAK_WL)->ShowWindow(bShow);
	GetDlgItem(IDC_EDIT_S_PEAK_WL_TOL_LIMIT)->ShowWindow(bShow);
	GetDlgItem(IDC_EDIT_S_LEVEL_1_THLD)->ShowWindow(bShow);
	GetDlgItem(IDC_EDIT_S_LEVEL_2_THLD)->ShowWindow(bShow);
	GetDlgItem(IDC_EDIT_S_LEVEL_3_THLD)->ShowWindow(bShow);
	GetDlgItem(IDC_EDIT_S_LEVEL_4_THLD)->ShowWindow(bShow);
	GetDlgItem(IDC_EDIT_S_LEVEL_5_THLD)->ShowWindow(bShow);
	GetDlgItem(IDC_BTN_APPLY)->ShowWindow(bShow);
}

void CSettingsDlg::OnBnClickedBtnCompoundSettings()
{
	CMainFrame* pWnd=NULL;
	pWnd=(CMainFrame*)GetParent();
	if((pWnd != NULL) && (pWnd->m_hWnd != NULL))
	{
		if(pWnd->m_bStartCapturing == TRUE)
			return;
	}
	// TODO: Add your control notification handler code here
	if(m_bShowCompoundSettings == false)
	{
		GetDlgItem(IDC_BTN_COMPOUND_SETTINGS)->SetWindowText(_T("Hide Settings"));
		m_bShowCompoundSettings = true;
		CRect rectWindow;
		GetWindowRect(rectWindow);
		MoveWindow(rectWindow.left,rectWindow.top, m_rectExpandedSettings.Width(),m_rectExpandedSettings.Height());
		//MoveWindow(&);
	}
	else if(m_bShowCompoundSettings == true)
	{
		GetDlgItem(IDC_BTN_COMPOUND_SETTINGS)->SetWindowText(_T("Show Settings"));
		m_bShowCompoundSettings = false;
		CRect rectWindow;
		GetWindowRect(rectWindow);
		MoveWindow(rectWindow.left,rectWindow.top, m_rectCollapsedSettings.Width(),m_rectCollapsedSettings.Height());
		//MoveWindow(&m_rectCollapsedSettings);
	}
	ShowOrHideCompoundSettings(m_bShowCompoundSettings);
}

void CSettingsDlg::OnStnClickedSLevelIndicator()
{
	// TODO: Add your control notification handler code here
}

void CSettingsDlg::OnStnClickedStaticPLevelLable()
{
	// TODO: Add your control notification handler code here
}

void CSettingsDlg::UpdateSettings()
{
//	OnBnClickedBtnApply();
	//ApplyFlameSettings();
	//ApplyCompoundSettings();
	
	ApplyStatesToDlgCtrls();
	Invalidate();
}

void CSettingsDlg::UpdateFlameIndicator()
{
	//As per Energy received at the peak wavelength we indicate Flame is ON/OFF 
	if(m_bFlameON == true)
	{
		//m_btnFlameOnOFF.SetWindowText(_T("ON"));
		//m_btnFlameOnOFF.EnableWindow(TRUE);
		m_btnFlameOnOFF.ToggleBmp(IDB_BMP_FLAME_ON);
	}
	else
	{
		//m_btnFlameOnOFF.SetWindowText(_T("OFF"));
		//m_btnFlameOnOFF.EnableWindow(FALSE);	
		m_btnFlameOnOFF.ToggleBmp(IDB_BMP_FLAME_OFF);
	}
}
void CSettingsDlg::OnBnClickedBtnFlameApply()
{
	// TODO: Add your control notification handler code here
	ApplyCtrlsDataIntoDoc();
	//if(m_pDoc != NULL)
	//	m_pDoc->UpdateAllViews(NULL);
	CMainFrame* pWnd=NULL;
	pWnd=(CMainFrame*)GetParent();
	if((pWnd != NULL) && (pWnd->m_hWnd != NULL))
	{
		pWnd->CalculateArea();
	}

	ApplyFlameSettings();
	ApplyStatesToDlgCtrls();
	Invalidate();
}

LRESULT CSettingsDlg::OnApplySettings(WPARAM wp , LPARAM lp)
{
	ApplyDocDataIntoCtrls();
	ApplyFlameSettings();
	ApplyStatesToDlgCtrls();
	Invalidate();
	return S_OK;
}