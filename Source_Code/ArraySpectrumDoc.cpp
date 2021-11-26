// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// ArraySpectrumDoc.cpp : implementation of the CArraySpectrumDoc class
//

#include "stdafx.h"
#include "ArraySpectrum.h"

#include "ArraySpectrumDoc.h"

#include "mainfrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CArraySpectrumDoc

IMPLEMENT_DYNCREATE(CArraySpectrumDoc, CDocument)

BEGIN_MESSAGE_MAP(CArraySpectrumDoc, CDocument)

END_MESSAGE_MAP()


// CArraySpectrumDoc construction/destruction

CArraySpectrumDoc::CArraySpectrumDoc()
{
	// TODO: add one-time construction code here

//Retrieve Polynomial Co-eff
	//RetrievePolyCoEfficients();
	ConvertPixelNumbersToWL();
	//Set the size
	//if(m_objSettings.m_arrobjCompoundSettings.GetCount() != 4)
	//	m_objSettings.m_arrobjCompoundSettings.SetSize(4);
	
	/*CCompoundSettings obj = m_objSettings.m_arrobjCompoundSettings[0];
	obj.m_strCompoundName = _T("S");
	m_objSettings.m_arrobjCompoundSettings[0]=obj;
	
	obj = m_objSettings.m_arrobjCompoundSettings.GetAt(1);
	obj.m_strCompoundName = _T("P");
	m_objSettings.m_arrobjCompoundSettings.SetAt(1,obj);

	obj = m_objSettings.m_arrobjCompoundSettings.GetAt(2);
	obj.m_strCompoundName = _T("As");
	m_objSettings.m_arrobjCompoundSettings.SetAt(2,obj);
	
	obj = m_objSettings.m_arrobjCompoundSettings.GetAt(3);
	obj.m_strCompoundName = _T("HNO");
	m_objSettings.m_arrobjCompoundSettings.SetAt(3,obj);*/

	//Retrive Settings
	TCHAR buff[1000];
	GetPrivateProfileString(_T("Application Settings"),_T("FirstTimeExecution"),_T("0"),buff,1000,theApp.m_strConfigIniPath);
	int nFirstTimeExecution = _tcstol(buff,NULL,10);
	if(nFirstTimeExecution == 1)
	{
		SerializeSettingsData(FALSE);
	}
	else if(nFirstTimeExecution == 0)
	{
		m_objSettings.m_objFlameSettings.m_dlPeakWL = 305;
		m_objSettings.m_objFlameSettings.m_dlPeakWLTOLLimit = 5;
		m_objSettings.m_objFlameSettings.m_dblPeakTHLD = 400;

		//m_objSettings.m_arrobjCompoundSettings[0].m_strCompoundName = _T("S");
		m_objSettings.m_arrobjCompoundSettings[0].m_strCompoundName = SULPHUR_COMPOUND;
		m_objSettings.m_arrobjCompoundSettings[0].m_dlPeakWL = 405;
		m_objSettings.m_arrobjCompoundSettings[0].m_dlPeakWLTOLLimit = 5;
		m_objSettings.m_arrobjCompoundSettings[0].m_arrPKEnergyLevels[0] = 400;
		m_objSettings.m_arrobjCompoundSettings[0].m_arrPKEnergyLevels[1] = 800;
		m_objSettings.m_arrobjCompoundSettings[0].m_arrPKEnergyLevels[2] = 1000;
		m_objSettings.m_arrobjCompoundSettings[0].m_arrPKEnergyLevels[3] = 2500;
		m_objSettings.m_arrobjCompoundSettings[0].m_arrPKEnergyLevels[4] = 4000;


		//m_objSettings.m_arrobjCompoundSettings[1].m_strCompoundName = _T("P");
		m_objSettings.m_arrobjCompoundSettings[1].m_strCompoundName = PHOSPHORUS_COMPOUND;
		m_objSettings.m_arrobjCompoundSettings[1].m_dlPeakWL = 526;
		m_objSettings.m_arrobjCompoundSettings[1].m_dlPeakWLTOLLimit = 5;
		m_objSettings.m_arrobjCompoundSettings[1].m_arrPKEnergyLevels[0] = 50;
		m_objSettings.m_arrobjCompoundSettings[1].m_arrPKEnergyLevels[1] = 80;
		m_objSettings.m_arrobjCompoundSettings[1].m_arrPKEnergyLevels[2] = 120;
		m_objSettings.m_arrobjCompoundSettings[1].m_arrPKEnergyLevels[3] = 250;
		m_objSettings.m_arrobjCompoundSettings[1].m_arrPKEnergyLevels[4] = 600;


		//m_objSettings.m_arrobjCompoundSettings[2].m_strCompoundName = _T("As");
		m_objSettings.m_arrobjCompoundSettings[2].m_strCompoundName = ARSENIC_COMPOUND;
		m_objSettings.m_arrobjCompoundSettings[2].m_dlPeakWL = 500;
		m_objSettings.m_arrobjCompoundSettings[2].m_dlPeakWLTOLLimit = 5;
		m_objSettings.m_arrobjCompoundSettings[2].m_arrPKEnergyLevels[0] = 50;
		m_objSettings.m_arrobjCompoundSettings[2].m_arrPKEnergyLevels[1] = 80;
		m_objSettings.m_arrobjCompoundSettings[2].m_arrPKEnergyLevels[2] = 120;
		m_objSettings.m_arrobjCompoundSettings[2].m_arrPKEnergyLevels[3] = 250;
		m_objSettings.m_arrobjCompoundSettings[2].m_arrPKEnergyLevels[4] = 600;

		//m_objSettings.m_arrobjCompoundSettings[3].m_strCompoundName = _T("HNO");
		m_objSettings.m_arrobjCompoundSettings[3].m_strCompoundName = NITROXYL_COMPOUND;
		m_objSettings.m_arrobjCompoundSettings[3].m_dlPeakWL = 689;
		m_objSettings.m_arrobjCompoundSettings[3].m_dlPeakWLTOLLimit = 5;
		m_objSettings.m_arrobjCompoundSettings[3].m_arrPKEnergyLevels[0] = 50;
		m_objSettings.m_arrobjCompoundSettings[3].m_arrPKEnergyLevels[1] = 80;
		m_objSettings.m_arrobjCompoundSettings[3].m_arrPKEnergyLevels[2] = 90;
		m_objSettings.m_arrobjCompoundSettings[3].m_arrPKEnergyLevels[3] = 100;
		m_objSettings.m_arrobjCompoundSettings[3].m_arrPKEnergyLevels[4] = 150;

		//set firstimeexecution to 1 in the config ini file
		CString str;
		str = _T("1");
		WritePrivateProfileString(_T("Application Settings"),_T("FirstTimeExecution"),str,theApp.m_strConfigIniPath);
	}
	
	//
	for(int nIndex = 0; nIndex < NO_OF_COMPOUNDS; nIndex++)
	{
		m_arrdblCompoundPeakArea[nIndex] = 0;
	}
}

CArraySpectrumDoc::~CArraySpectrumDoc()
{
}

BOOL CArraySpectrumDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here(SDI documents will reuse this document)


	return TRUE;
}




// CArraySpectrumDoc serialization

void CArraySpectrumDoc::Serialize(CArchive& ar)
{
	m_objCapturePixelBuff.Serialize(ar);
	if (ar.IsStoring())
	{
		// TODO: add storing code here

	}
	else
	{
		// TODO: add loading code here

	}
}


// CArraySpectrumDoc diagnostics

#ifdef _DEBUG
void CArraySpectrumDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CArraySpectrumDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// This method is used to Start/Stop,the Capturing of Spectrum continuously (based on the Integration time). If the Capturing is Started, the "Capture Start" button is toggled to "Stop".

void CArraySpectrumDoc::StartCapture(void)
{
	m_objCapturePixelBuff.StartCapture();
}

// Apply the Capture Properties to the Data Acquisition h/w. This method should be called before the "Capturing" or "Snap Shot" of the Spectrum (Pixels) is invoked 
void CArraySpectrumDoc::ApplyCaptureProperties(void)
{

}

// //Acquires a single snap shot frame data from the device
BOOL CArraySpectrumDoc::AcquireSnapShotData(void)
{
	
	m_objCapturePixelBuff.CaptureSnapShot();

	return TRUE;
}

// //Stop Continuous Capturing of Frames from CCD
void CArraySpectrumDoc::StopCapture(void)
{
	m_objCapturePixelBuff.StopCapture();
}

// Updaate the Propery Pane with property values respective to the opened Job and if bEnable is FALSE, disable the Property pane. 
void CArraySpectrumDoc::UpdatePropertiesPane(bool bEnable)
{
	CMainFrame* pFrame=(CMainFrame*)AfxGetMainWnd();
	if(pFrame)
	{
		if(pFrame->m_wndPropertiesPane.m_hWnd)
		{
			CPropertiesPaneDlg *pdlg=&(pFrame->m_wndPropertiesPane.m_PropertiesPaneDlg);
			if(pdlg->m_hWnd != NULL)
			{
				pdlg->m_bShowAverage=m_objCapturePixelBuff.m_bShowAvg;

				pdlg->m_nExposureTime=m_objCapturePixelBuff.m_nExposureTime;
				pdlg->m_nLineCount=m_objCapturePixelBuff.m_nLineCount;
				if(pdlg->m_nLineCount==1)
				{
					pdlg->m_bShowSD=m_objCapturePixelBuff.m_bShowSD=FALSE;
					pdlg->m_bShowRSD=m_objCapturePixelBuff.m_bShowRSD=FALSE;
				}
				else
				{
					pdlg->m_bShowSD=m_objCapturePixelBuff.m_bShowSD;
					pdlg->m_bShowRSD=m_objCapturePixelBuff.m_bShowRSD;
				}
				pdlg->m_nGain=m_objCapturePixelBuff.m_nGain;
				pdlg->m_nOffSet=m_objCapturePixelBuff.m_nOffset;
				pdlg->UpdateData(FALSE);
				pdlg->EnableWindow(bEnable);
			}
		}

	}
}

BOOL CArraySpectrumDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  Add your specialized creation code here
	UpdatePropertiesPane(FALSE);
	

	return TRUE;
}

BOOL CArraySpectrumDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDocument::OnSaveDocument(lpszPathName);
}

void CArraySpectrumDoc::DeleteContents()
{
	// TODO: Add your specialized code here and/or call the base class
	//clean the Captured pixel Data Buf
	m_objCapturePixelBuff.ClearPixelBuffer();
	
	//<--Ver 1.4
	//UpdatePropertiesPane(TRUE);
	//--Ver 1.4-->

	CDocument::DeleteContents();
}


//check sum calculation
//Checksum use:Instrument checks value of check sum to conform command send by Application
//To calculate check sum for scan array
BYTE CArraySpectrumDoc::fncCalcChecksum(BYTE* ptrchksumcontents,int nlenofbytearr)
{
	short nchecksum=0;
	if(ptrchksumcontents!=NULL)
	{
		for(int i=0;i<nlenofbytearr;i++)
		{
			short k=short(ptrchksumcontents[i]);
			nchecksum=k+nchecksum;
		}
		nchecksum=nchecksum % 256;
		//two's Compliment calculation
		nchecksum=~nchecksum+1;
	}
	return BYTE(nchecksum);
}

//for getting absorbance value by clubbing msb and lsb value sent by instrument
unsigned short CArraySpectrumDoc::fncGetADCValue(BYTE* bhibyte,BYTE* blowbyte)
{
	unsigned short nAbs=0;
#ifdef _NoBYTEREVERSAL
	char Temp1[10]={0};

	char Temp2[10]={0};

	if(*bhibyte!=NULL||*blowbyte!=NULL)
	{
		sprintf(Temp1,"%x",*bhibyte);
		sprintf(Temp2,"%x",*blowbyte);
		if(strlen(Temp2)<2)
		{
			//if lower byte is having nothing 
			//insert two zero's
			if(strlen(Temp2)==0)
			{
				Temp2[0]='0';
				Temp2[1]='0';
			}
			//it is observed if ADC is "470D" instrument is sending '47' in msb and '0D' in lsb
			//when i am reading it using sprintf i am getting reading as 'D' into the buffer
			//to avoid this i am inserting zero in first pos of the buffer and 'D' into next pos in Buffer.
			if(strlen(Temp2)==1)
			{
				BYTE k=Temp2[0];
				Temp2[0]='0';
				Temp2[1]=k;
			}
		}
		strcat(Temp1,Temp2);

		char *k=NULL;
		nAbs=(unsigned short)strtol(Temp1,&k,16);
	}

#endif

#ifdef _WITHBYTEREVERSAL
	BYTE k[5]={0};
	k[0]=*blowbyte;
	k[1]=*bhibyte;
	unsigned short *temp=(unsigned short*)k;
	nAbs=*temp;
#endif
	return nAbs;
}

//Function: For calculating Absorbance and transmittance and Energy value.
//double CArraySpectrumDoc::fncCalAbsorTransmittanceorEnergy(double dblRefval,double dblSmpval,SCANTYPE entype)
double CArraySpectrumDoc::fncCalEnergy(double dblRefval,double dblSmpval)
{
	//Energy calculation
	double dblEnergy;
	/*if(entype==SCAN_ENERGY)
	{*/
	dblEnergy=(dblRefval/65535.0)*5.0;
	dblEnergy*=1000.0;
	/*}*/
	return dblEnergy/*wcstod(theApp._DoubletoString(dblEnergy),NULL)*/;

	//////	///Absorbance calculation
	//////	if(entype==SCAN_ABSORBANCE)
	//////	{
	//////		double dblAbsval=0.0;
	//////
	//////		if(dblSmpval<=0)
	//////		{
	//////			dblAbsval=2.5;
	//////		}
	//////		else if(dblRefval<=0)
	//////		{
	//////			dblAbsval=-2.5;
	//////		}
	//////		else
	//////		{
	//////			dblAbsval=-(log(dblSmpval/dblRefval))/log(10);
	//////		}
	//////		return dblAbsval/*wcstod(theApp._DoubletoString(dblAbsval),NULL)*/;
	//////	}
	//////	//Transmittance Calculation
	//////	if(entype==SCAN_TRANSMITANCE)
	//////	{
	//////		double dblTransmitanceval;
	//////
	//////		if(dblSmpval<=0)
	//////		{
	//////			dblTransmitanceval=0;
	//////		}
	//////		else if(dblRefval<=0)
	//////		{
	//////			dblTransmitanceval=100;
	//////		}
	//////		else
	//////		{
	//////			//percentage of transmittance.
	//////			dblTransmitanceval=(dblSmpval/dblRefval)*100;
	//////		}
	//////#ifdef _DEBUG
	//////		char ch[100]={0};
	//////		sprintf(ch,"%Transmitance: %lf\n",dblTransmitanceval);
	//////		WriteLog(ch);
	//////#endif
	//////		return dblTransmitanceval/* wcstod(theApp._DoubletoString(dblTransmitanceval),NULL)*/;
	//////	}
}

unsigned short* CArraySpectrumDoc::fncSetData(BYTE *RawScanData,LONG lngLength)
{
	int count = 0;
	unsigned short* shD2RefOpen= new unsigned short[MAX_PIXEL_DATA_COUNT_PER_LINE]; 
	for(int i=0;i<lngLength;i=i+2)
	{
		shD2RefOpen[count++] = fncGetADCValue(&RawScanData[i],&RawScanData[i+1]);
	}
	return shD2RefOpen;
}


// Retrieve the Polynomial Co-efficients from the Calibration config INI file required for mapping Pixel to WL
void CArraySpectrumDoc::RetrievePolyCoEfficients(void)
{
	/*TCHAR buff[1000];
	GetPrivateProfileString(_T("Calib"),_T("a"),_T("0.0"),buff,1000,_T("C:\\ELICO\\ArraySpectrum\\Calib_Config.ini"));

	m_dblCoeffA=_tcstod(buff,NULL);

	GetPrivateProfileString(_T("Calib"),_T("b"),_T("0.0"),buff,1000,_T("C:\\ELICO\\ArraySpectrum\\Calib_Config.ini"));

	m_dblCoeffB=_tcstod(buff,NULL);

	GetPrivateProfileString(_T("Calib"),_T("c"),_T("0.0"),buff,1000,_T("C:\\ELICO\\ArraySpectrum\\Calib_Config.ini"));

	m_dblCoeffC=_tcstod(buff,NULL);

	GetPrivateProfileString(_T("Calib"),_T("d"),_T("0.0"),buff,1000,_T("C:\\ELICO\\ArraySpectrum\\Calib_Config.ini"));

	m_dblCoeffD=_tcstod(buff,NULL);*/

	double * a;//= &m_dblCoeffA;
	double *b;//= &m_dblCoeffB;
	double * c;//= &m_dblCoeffC;
	double * d;//= &m_dblCoeffD;
	BOOL bRes;
	UINT len=sizeof(double);
	bRes=AfxGetApp()->GetProfileBinary(_T("Calib"),_T("a"),(LPBYTE*)&a,&len);

	len=sizeof(double);
	bRes=AfxGetApp()->GetProfileBinary(_T("Calib"),_T("b"),(LPBYTE*)&b,&len);

	len=sizeof(double);
	bRes=AfxGetApp()->GetProfileBinary(_T("Calib"),_T("c"),(LPBYTE*)&c,&len);


	len=sizeof(double);
	bRes=AfxGetApp()->GetProfileBinary(_T("Calib"),_T("d"),(LPBYTE*)&d,&len);

	if(bRes)
	{
		m_dblCoeffA=*a;
		m_dblCoeffB=*b;
		m_dblCoeffC=*c;
		m_dblCoeffD=*d;
	}
	else
	{
		m_dblCoeffA=0;
		m_dblCoeffB=0;
		m_dblCoeffC=0;
		m_dblCoeffD=0;
	}


}
//Convert the Pixel Numbers to WL numbers based on the Polynomial co-efficients obtained in Calibration.
//Returns the buffer containing the converted WaveLength numbers
double * CArraySpectrumDoc::ConvertPixelNumbersToWL()
{  
   
	//Retrivel the poly co-effs afresh
	RetrievePolyCoEfficients();
  /*
	m_dblCoeffA=0.0000007126881654;
	m_dblCoeffB=-0.0028039202439154;
	m_dblCoeffC=4.5710879813549700;
	m_dblCoeffD=-2291.6059457956800;*/

	for(int i=0;i<MAX_PIXEL_DATA_COUNT_PER_LINE;i++)
	{
		/*double x=i;
		double x3=x*x*x;
		double x2=x*x;
		double afact=m_dblCoeffA*x3;
		double bfact=m_dblCoeffB*x2;
		double cfact=m_dblCoeffC*x;
		m_bufWLDataPoints[i]=afact+bfact+cfact+m_dblCoeffD;*/

        double x=i;
		double x2=x*x;
		double afact=m_dblCoeffA*x2;
		double bfact=m_dblCoeffB*x;
		double cfact=m_dblCoeffC;
		m_bufWLDataPoints[i]=afact+bfact+cfact;
	}
   return m_bufWLDataPoints;
}


void CArraySpectrumDoc::SerializeSettingsData(bool bSave)
{
	// if bSave is TRUE, The Calibration settings are saved to a INI file otherwise they will be rerieved from the 
	if(bSave)
	{
		//Cleanup Calib_Config.INI
		CSettings objTempSettings = m_objSettings;
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
		str = _T("");
		for(int nIndex = 0; nIndex < nCount; nIndex++)
		{
			obj = objTempSettings.m_arrobjCompoundSettings[nIndex];
			if(nIndex == (nCount-1))
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
				//strTemp.Format(_T(",%lf,%lf"), obj.m_arrPKEnergyLevels.GetAt(nLevelIndex) , obj.m_arrPKEnergyLevelsLimits.GetAt(nLevelIndex));
				strTemp.Format(_T(",%lf"), obj.m_arrPKEnergyLevels[nLevelIndex]);
				strEnergyLevels += strTemp;
			}
			str = str + strEnergyLevels;
			/*int nLen = str.GetLength() + 1;
			LPBYTE pByte = new BYTE[nLen];
			memcpy(pByte, (VOID*)LPCTSTR(str), nLen-1);
			AfxGetApp()->WriteProfileBinary(_T("Settings"),strCompound,pByte,nLen);
			delete[] pByte;
			pByte = NULL;*/
			AfxGetApp()->WriteProfileString(_T("Settings"),strCompound,str);
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
        CString strTemp;
		//Flame Settings
		CString str=AfxGetApp()->GetProfileString(_T("Settings"),_T("FlameSettings"));
		if(str.IsEmpty()!= TRUE)
		{
			i = 0;
			while(1)
			{
				if(i == 0)
					pstrTok = _tcstok_s((wchar_t*)(LPCTSTR)str,_T(","),&next_token);
				else
					pstrTok = _tcstok_s(NULL,_T(","),&next_token);
				if(pstrTok==NULL)
					break;
				i++;
				strTemp = pstrTok;
				arrStrTokenizedData.Add(strTemp);
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
			i =0;
			while(1)
			{
				if(i == 0)
					pstrTok = _tcstok_s((wchar_t*)(LPCTSTR)str,_T(","),&next_token);
				else
					pstrTok = _tcstok_s(NULL,_T(","),&next_token);
				if(pstrTok==NULL)
					break;
				i++;
				strTemp = pstrTok;
				arrStrCompoundNames.Add(strTemp);
			}
		}

		//Compound Settings
		//CCompoundSettings arrCompoundSettings[NO_OF_COMPOUNDS];
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
				i =0;
				while(1)
				{
					if(i == 0)
						pstrTok = _tcstok_s((wchar_t*)(LPCTSTR)str,_T(","),&next_token);
					else
						pstrTok = _tcstok_s(NULL,_T(","),&next_token);
					if(pstrTok == NULL)
						break;
					i++;
					strTemp = pstrTok;
					arrStrTokenizedData.Add(strTemp);
				}
			}
			CCompoundSettings obj;
			int nCount = arrStrTokenizedData.GetCount();
			if((nCount > 0))
			{
				int i = 0;
				obj.m_strCompoundName = arrStrCompoundNames.GetAt(nIndex);
				if(nCount > 0)
					obj.m_dlPeakWL = _tcstod(arrStrTokenizedData.GetAt(i++),NULL);
				if(nCount > 1)	
					obj.m_dlPeakWLTOLLimit = _tcstod(arrStrTokenizedData.GetAt(i++),NULL);
				if(nCount > 2)
				{
					//obj.m_arrPKEnergyLevels.SetSize(5);
					obj.m_arrPKEnergyLevels[0]=  _tcstod(arrStrTokenizedData.GetAt(i++),NULL);
				}
				if(nCount > 3)
					obj.m_arrPKEnergyLevels[1] = _tcstod(arrStrTokenizedData.GetAt(i++),NULL);
				if(nCount > 4)
					obj.m_arrPKEnergyLevels[2] = _tcstod(arrStrTokenizedData.GetAt(i++),NULL);
				if(nCount > 5)
					obj.m_arrPKEnergyLevels[3] = _tcstod(arrStrTokenizedData.GetAt(i++),NULL);
				if(nCount > 6)
					obj.m_arrPKEnergyLevels[4] = _tcstod(arrStrTokenizedData.GetAt(i++),NULL);
			}
			objTempSettings.m_arrobjCompoundSettings[nIndex] = obj;
		}
		//objTempSettings.m_arrobjCompoundSettings = arrCompoundSettings;
		m_objSettings = objTempSettings;
	}
}



///Finds the nearest given value in an array by using binary search algorithm principle
///if the provided value found in the given array then, ptrbExactMatchFound is set to true and the found index information is 
///in ptrnNearestIndex.
///else the value is not found in the given array then, ptrbExactMatchFound is set to false and the nearest index information is
///in ptrnNearestIndex. it can be greater or lessthan value.
void CArraySpectrumDoc::FindNeareastIndex(double* dblArray, int nSize,double value,bool* ptrbExactMatchFound,int* ptrnNearestIndex)
{
	int nStartIndex = 0;
	int nLastIndex = nSize - 1;

	int nMiddleIndex = (nStartIndex + nLastIndex)/2;

	while (nStartIndex <= nLastIndex) 
	{
		if (dblArray[nMiddleIndex] == value)
		{
			*ptrbExactMatchFound = true;
			*ptrnNearestIndex = nMiddleIndex;
			return;
		}

		if (dblArray[nMiddleIndex] < value)
			nStartIndex = nMiddleIndex + 1;  
		else
			nLastIndex = nMiddleIndex - 1;
		
		nMiddleIndex = (nStartIndex + nLastIndex)/2;
	}

	*ptrbExactMatchFound = false;
	*ptrnNearestIndex = nMiddleIndex;
}

