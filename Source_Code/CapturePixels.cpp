#include "stdafx.h"
#include "arraySpectrum.h"
#include "capturePixels.h"
#include "DCamUSB.h"
#include "DcIcUSB.h"
#include "constants.h"
//#include "SerialComm.h"
#include "MainFrm.h"
#include "ArraySpectrumDoc.h"

#include <math.h>


//Saves the Data to a CSV file. If nMode=0, the Pixel Data is saved. If nMode=1, the WaveLength Data is Saved
void CCapturePixels::SaveDataToCSVFile( CString strFileName, int nMode)
{

	FILE *fp;

	fp = _wfopen( strFileName, _T("w"));
	if( fp == NULL )	
		return;
	//Write the Header
	if(nMode==0)
		fprintf(fp,"Type:,PIXEL DATA FILE\n");
	if(nMode==1)
		fprintf(fp,"Type:,WAVELENGH DATA FILE\n");
	char b[200];
	sprintf(b,"Exposure Time:,%d m.Sec\n",m_nExposureTime);
	fprintf(fp,b);

	sprintf(b,"Gain:,%d\n",m_nGain);
	fprintf(fp,b);

	sprintf(b,"Offset:,%d\n",m_nOffset);
	fprintf(fp,b);

	sprintf(b,"Line Count:,%d\n",m_nLineCount);
	fprintf(fp,b);

	fprintf(fp,"\n\n");



	//Get the Average pixel buffer of All Pixel Line Buffers
	double* pAvgData= m_pBufAvgPixelData;

	//Get the SD pixel bufferof All Pixel Line Buffers
	double*pSDData=NULL;
	if(m_bShowSD)
		pSDData=m_pBufSDPixelData;

	//Get the RSD pixel bufferof All Pixel Line Buffers
	double*pRSDData=NULL;
	if(m_bShowRSD)
		pRSDData=m_pBufRSDPixelData;

	//Put the Labels on the Header row of CSV file
	if(nMode==0) //Pixel Mode Data
		fprintf(fp,"Pixel No,");
	else if(nMode==1) //WL Mode Data
	{
		fprintf(fp,"Pixel No,");	
		fprintf(fp,"WaveLength(nm),");
	}
	fprintf(fp,"Average,");
	if(m_bShowSD)
		fprintf(fp,"SD,");
	if(m_bShowRSD)
		fprintf(fp,"RSD,");
	for(int i=0;i<m_nLineCount;i++)
	{
		if(i==m_nLineCount-1)
			fprintf(fp,"L%d\n",i+1);
		else
			fprintf(fp,"L%d,",i+1);
	}
	double * m_dblBufWLNo=NULL;
	if(nMode==1) //If WL Mode, Get the buffer of Converted WL Numbers from Pixel Numbers
	{
		/*
		CArraySpectrumApp *pApp=(CArraySpectrumApp*)AfxGetApp();
		//fill the x-data points (WL) mapped to pixels based on Polynomial Co-Efficeints
		//m_dblBufWLNo= pApp->ConvertPixelNumbersToWL();
		m_dblBufWLNo= pApp->m_bufWLDataPoints;
		*/

		CMainFrame * pFrame = (CMainFrame*)AfxGetMainWnd();
		CArraySpectrumDoc* pDoc = NULL;
		pDoc = (CArraySpectrumDoc*)(pFrame->GetActiveDocument());
		
		if(pDoc != NULL)
			m_dblBufWLNo= pDoc->m_bufWLDataPoints;
	}
	for(int j=0;j<MAX_PIXEL_DATA_COUNT_PER_LINE;j++)
	{
		if(nMode==0) //show Pixel Number
			fprintf(fp,"%d,",j);
		else if(nMode==1) //Show WL
		{
			fprintf(fp,"%d,",j);
			fprintf(fp,"%.3f,",m_dblBufWLNo[j]);
		}
		//print the Avg,SD and RSD values
		fprintf(fp,"%f,",pAvgData[j]);

		if(m_bShowSD)
			fprintf(fp,"%f,",pSDData[j]);

		if(m_bShowRSD)
			fprintf(fp,"%f,",pRSDData[j]);

		//Now Print the Line Buffers	
		for(int i=0;i<m_nLineCount;i++)
		{
			if(i!=m_nLineCount-1)
			{
				#ifdef _SA165
					fprintf(fp,"%f,",m_pPixelLines[i][j]);
				#else
					fprintf(fp,"%6d,",m_pPixelLines[i][j]);
				#endif
			}
			else
			{
				#ifdef _SA165
					fprintf(fp,"%f\n",m_pPixelLines[i][j]);
				#else
					fprintf(fp,"%6d\n",m_pPixelLines[i][j]);
				#endif
			}
		}
	}
	fclose(fp);

}

void SaveToFile( char* pFileName, WORD *pDataBuff, int nWidth, int nHeight, int nFrame ) 
{
	FILE *fp;
	int  nCountW, nCountH, nCountF;

	fp = fopen( pFileName, "w" );
	if( fp == NULL )	return;

	WORD *pData = pDataBuff;

	CString s;
	s.Format(_T("Width=%d,Height=%d,Frames=%d"),nWidth,nHeight,nFrame);
	AfxMessageBox(s);
	for(nCountF = 0; nCountF < nFrame; nCountF++)
	{
		for( nCountH = 0; nCountH < nHeight; nCountH++ )
		{
			for( nCountW = 0; nCountW < nWidth; nCountW++ )
			{
				//fprintf( fp, "%d,", *pData );
				fprintf( fp, "%d\n", *pData );

				pData ++;
			}
			fprintf( fp, "\n" );
		}
		//njrs
		fprintf(fp,"Frame%d Ends\n",nCountF);
	}

	fclose( fp );
}

void CaptureSnapFromCCD(CCapturePixels* pObjPixelData)
{
	WORD* pDataBuff = NULL;
	//double* pDataBuff = NULL;//1.3
	int		nWidth = 0, nHeight = 0, nImageSize = 0, nLineCount = 0, nBitSize = 0;
	BOOL bResult, bStat, bValue;
	nWidth = nHeight = nImageSize = 0;
	nLineCount = pObjPixelData->m_nLineCount;						 // Line Count( 50 line )

	BYTE btValue = 0;	                                             // Internal Sync Mode
	bStat = DcIc_SetTriggerMode(pObjPixelData->nDevID, btValue);


	bValue = TRUE;		                                             // High Active
	bStat = DcIc_SetTriggerPolarity(pObjPixelData->nDevID, bValue);                 // Set trigger polarity

	bValue = FALSE;	                                                 // Disable
	bStat = DcIc_SetTriggerEffective(pObjPixelData->nDevID, bValue);                // Set trigger effective

																	 // Set Integration cycle(= Exposure time)
	bStat = DcIc_SetStartPulseTime(pObjPixelData->nDevID, pObjPixelData->m_nExposureTime);

	bStat = DcIc_SetGain(pObjPixelData->nDevID, pObjPixelData->m_nGain);            // Set GAIN

	bStat = DcIc_SetOffset(pObjPixelData->nDevID, pObjPixelData->m_nOffset);        // set OFFSET

	int wValue = 32;
	bStat = DcIc_SetVerticalPixel(pObjPixelData->nDevID, wValue);

	// Create capture buffer.
	INT nFramCnt = nLineCount;
	ULONG ulTotalPixels = 0;
	WORD wPixels = 0;
	WORD wLines = 0;

	bStat = DcIc_GetVerticalPixel(pObjPixelData->nDevID, &wLines);
	bStat = DcIc_GetHorizontalPixel(pObjPixelData->nDevID, &wPixels);
	ulTotalPixels = (ULONG)nFramCnt * (ULONG)wLines * (ULONG)wPixels;

	CString strM;
	strM.Format(_T("Image p=%s,l=%s"), wPixels,wLines);
	AfxMessageBox(strM);

	pObjPixelData->m_nPixelBufImageSize = ulTotalPixels;
	pObjPixelData->ClearPixelBuffer();

	pDataBuff = new WORD[pObjPixelData->m_nPixelBufImageSize];
	if (pDataBuff)
	{
		memset(pDataBuff, 0, pObjPixelData->m_nPixelBufImageSize * 2);

		// Acquire the image data
		bStat = DcIc_Capture(pObjPixelData->nDevID, pDataBuff, pObjPixelData->m_nPixelBufImageSize * 2);
		INT nRsltStat = DcIc_WAITSTATUS_CAPTURING;
		while (TRUE)
		{
			// Wait to complete the capture image
		    ::Sleep(1000);
			nRsltStat = DcIc_Wait(pObjPixelData->nDevID);
			if (nRsltStat == DcIc_WAITSTATUS_CAPTURED)
			{
				break;
			}
		}
	}
	else
	{
		
		return;
	}
	pObjPixelData->m_pBuffPixelData = pDataBuff;
	SaveToFile("Sample.csv", pDataBuff, wPixels, wLines, nFramCnt);
	
	// Process for exit. 
	bStat = DcIc_Abort(pObjPixelData->nDevID);
	if (pDataBuff != NULL)
	{
		delete[] pDataBuff;
		pDataBuff = NULL;
	}


}
//<--Added for 1.2
typedef struct _CAPTURE_SNAP_FROM_DA_PARAMS
{
	//CSerialComm* ptrSerialComm;

	CCapturePixels* ptrPixelBuff;

	CArraySpectrumDoc* ptrDoc;

	_CAPTURE_SNAP_FROM_DA_PARAMS()
	{
		//ptrSerialComm = NULL;
		ptrPixelBuff = NULL;
		ptrDoc = NULL;
	}
	~_CAPTURE_SNAP_FROM_DA_PARAMS()
	{
		//ptrSerialComm = NULL;
		ptrPixelBuff = NULL;
		ptrDoc = NULL;
	}
}CAPTURE_SNAP_FROM_DA_PARAMS;

UINT CaptureSnapFromDiodeArray(LPVOID param) 
{
	//Send D2 on command to the instrument
	CAPTURE_SNAP_FROM_DA_PARAMS* ptrThreadParmas = (CAPTURE_SNAP_FROM_DA_PARAMS*)param;
	CArraySpectrumDoc* ptrDoc = (CArraySpectrumDoc*)ptrThreadParmas->ptrDoc;
	CCapturePixels* ptrPixelBuff = (CCapturePixels*)ptrThreadParmas->ptrPixelBuff;
	////Frame Lamp Command(Send D2-ON and W-OFF)
	//BYTE byteLampCmd[4];
	//byteLampCmd[0] = 'A';
	//byteLampCmd[1] = '1';
	//byteLampCmd[2] = '0';
	//byteLampCmd[3] = 'Z';
	////Send lamp command
	//ptrDoc->m_objSerialComm.Send((unsigned char *)byteLampCmd,4);
	////receive the response from the instrument
	//BYTE byteRespBuff[1];
	//LONG lngReceiveLen = 0;
	//BOOL bIsTotalResponseRecevied = FALSE;
	//BOOL bIsTimeOutOccurred = FALSE;
	//ptrDoc->m_objSerialComm.Receive(1,10,byteRespBuff,&lngReceiveLen,&bIsTotalResponseRecevied,&bIsTimeOutOccurred);
	//if(bIsTotalResponseRecevied == TRUE)
	//{
	//	if(byteRespBuff[0] == 0x06)//if success
	//	{				

	/*	}
	}	*/

	//<--Frame Energy Command reference open with integration time(Exposure Time input is considered)
	BYTE byteScanArrayCmd[6];
	byteScanArrayCmd[0] = 'S';
	//int nIniTime = 350;
	int nIniTime = ptrPixelBuff->m_nExposureTime;
	short int p = nIniTime;
	short int q = p >> 8;
	byteScanArrayCmd[1] = q & 0x00FF;
	byteScanArrayCmd[2] = p & 0x00FF;
	byteScanArrayCmd[3] = 'r';
	byteScanArrayCmd[4] = 0x31;//open
	byteScanArrayCmd[5] = ptrDoc->fncCalcChecksum(byteScanArrayCmd,5);

	ptrDoc->m_objSerialComm.Send((unsigned char *)byteScanArrayCmd,6);

	BYTE* byteScanArrayRespBuff = NULL;
	byteScanArrayRespBuff = new BYTE[DA_SCANARRAY_CMD_RESPONE_LEN];

	BOOL bIsTotalResponseRecevied = FALSE;
	BOOL bIsTimeOutOccurred = FALSE;
	LONG lngReceiveLen = 0;
	ptrDoc->m_objSerialComm.Receive(DA_SCANARRAY_CMD_RESPONE_LEN,SCANARRAY_CMD_TIMEOUT_IN_SEC,byteScanArrayRespBuff,&lngReceiveLen,&bIsTotalResponseRecevied,&bIsTimeOutOccurred);

	if(bIsTotalResponseRecevied == TRUE)
	{
		int nRawDataLen = MAX_PIXEL_DATA_COUNT_PER_LINE*2;

		BYTE* byteScanDataTempBuf = NULL;
		byteScanDataTempBuf = new BYTE[nRawDataLen];
		memcpy(byteScanDataTempBuf,&byteScanArrayRespBuff[2],DA_SCANARRAY_CMD_RESPONE_LEN-1);
		
		if(byteScanArrayRespBuff != NULL)
		{
			delete[] byteScanArrayRespBuff;
			byteScanArrayRespBuff = NULL;
		}

		unsigned short* shADCD2RefOpenData = ptrDoc->fncSetData(byteScanDataTempBuf,nRawDataLen);
		if(byteScanDataTempBuf != NULL)
		{
			delete[] byteScanDataTempBuf;
			byteScanDataTempBuf = NULL;
		}
		int nLineCount = 0;
		nLineCount = ptrPixelBuff->m_nLineCount;										// Line Count( 50 line )
		ptrPixelBuff->m_nPixelBufImageSize = MAX_PIXEL_DATA_COUNT_PER_LINE*nLineCount;
		ptrPixelBuff->ClearPixelBuffer();

		double*	pDataBuff   = NULL;
		pDataBuff = new double[ptrPixelBuff->m_nPixelBufImageSize];

		if(pDataBuff)
		{
			memset( pDataBuff, 0, ptrPixelBuff->m_nPixelBufImageSize*2 );
			double dblRefVal,dblEnergy;
			for(int nElementIndex = 0; nElementIndex < MAX_PIXEL_DATA_COUNT_PER_LINE; nElementIndex++)
			{
				dblRefVal = (double)shADCD2RefOpenData[nElementIndex];
				dblEnergy = ptrDoc->fncCalEnergy(dblRefVal,0);
				pDataBuff[nElementIndex] = dblEnergy;
			}
			//ptrPixelBuff->m_pBuffPixelData=pDataBuff;
		}
	}
	return 0;
}

//<--Added for 1.2
UINT CaptureSnapShotThread(LPVOID param)
{
	//CAPTURE_SNAP_FROM_DA_PARAMS* ptrThreadParmas = (CAPTURE_SNAP_FROM_DA_PARAMS*)param;
	//CCapturePixels * pObjPixelBuff = (CCapturePixels*)ptrThreadParmas->ptrPixelBuff;
	CCapturePixels * pObjPixelBuff = (CCapturePixels*)param;

	//<--Commented for Version 1.2
	#ifdef _SA165
	//<--Added for Version 1.2
		CaptureSnapFromDiodeArray(ptrThreadParmas);
	//<--Added for Version 1.2
	#elif _SIM
	//prompt the user to provide the pixel data in a csv format for a sigle line count
	// Create an Open dialog; the default file name extension is ".my".
	//CFileDialog objFileDlg(TRUE,_T("Untitled"), _T("*.csv"),OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,_T("Pixel Data File(*.csv)|*.csv||"));

	// Display the file dialog. When user clicks OK, fileDlg.DoModal() 
	// returns IDOK.
	//if(objFileDlg.DoModal() == IDOK)
	//{
		//CString strPathName = objFileDlg.GetPathName();
	    CString strPathName;
		if(((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_nNoOfScanCompl == 0)
		{
		    strPathName = _T("D:\\UD\\ArraySpectrum_Ver_1.3Beta11\\Documents\\Test_Files\\capture\\S.csv");
		}
		else if(((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_nNoOfScanCompl == 1)
		{
			strPathName = _T("D:\\UD\\ArraySpectrum_Ver_1.3Beta11\\Documents\\Test_Files\\capture\\Flame.csv");
		}
		else
		{
			strPathName = _T("D:\\UD\\ArraySpectrum_Ver_1.3Beta11\\Documents\\Test_Files\\capture\\As.csv");
			((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_nNoOfScanCompl = -1;
		}
		////   // Implement opening and reading file in here.

		////   //Change the window's title to the opened file's title.
		////   CString strFileName = objFileDlg.GetFileTitle();
		////FILE *fp;

		////fp = _wfopen( strPathName, _T("r"));
		////if( fp == NULL )	
		//// return;
		//// /* Set pointer to beginning of file: */
		////   fseek( fp, 0L, SEEK_SET );
		//////CString strRowData;
		////char szRowData[MAX_PATH+1];
		////fscanf( fp, "%s", szRowData );
		////   fclose( fp);
		////fp = NULL;

		//Sleep(1000);

		CStdioFile readFile;
		CFileException fileException;
		CString strLine;

		if(readFile.Open(strPathName, CFile::modeRead, &fileException))
		{
			readFile.ReadString(strLine);//LineCount
			CString resToken;
			int curPos = 0;

			resToken= strLine.Tokenize(_T("\t"),curPos);
			if(resToken != _T(""))
			{
				resToken = strLine.Tokenize(_T("\t"), curPos);
				int nLineCount = _ttoi(strLine);
			}
			readFile.ReadString(strLine);//Empty line
			readFile.ReadString(strLine);//column names
			double dblADUVal = 0;
			pObjPixelBuff->ClearPixelBuffer();
			pObjPixelBuff->m_nLineCount = 1;
			pObjPixelBuff->m_nPixelBufImageSize = MAX_PIXEL_DATA_COUNT_PER_LINE;
			pObjPixelBuff->m_pBuffPixelData = new WORD[MAX_PIXEL_DATA_COUNT_PER_LINE];
			pObjPixelBuff->m_pBuffPixelData = new WORD[MAX_PIXEL_DATA_COUNT_PER_LINE];
			for(int nIndex = 0; nIndex < MAX_PIXEL_DATA_COUNT_PER_LINE; nIndex++)
			{
				readFile.ReadString(strLine);//Line ADU values
				pObjPixelBuff->m_pBuffPixelData[nIndex] = _tcstod(strLine,NULL);
			}
			//pDoc->m_objCapturePixelBuff.PreparePixelLineBuffFromSnapShot();
			//GetActiveDocument()->UpdateAllViews(NULL);
		}
		else
		{
			CString strErrorMsg;
			strErrorMsg.Format(_T("Can't open file %s , error : %u"), strPathName, fileException.m_cause);
			AfxMessageBox(strErrorMsg);
		}
		readFile.Close();

	//}
	#else
	//Do Capturte
		CaptureSnapFromCCD(pObjPixelBuff);
	#endif
	
	//<--Commented for Version 1.2

	
	//Capturing is not succesful
	if(pObjPixelBuff->ISEmpty())
	{
		AfxGetApp()->m_pMainWnd->PostMessage(WM_CAPTURING_FAILED,0,0);
		return 0;
	}

	//Prepare a series of buffers to reference each Scan Pixel Line buffer individually
	pObjPixelBuff->PreparePixelLineBuffFromSnapShot();

	// Save data
	//pObjPixelBuff->SavePixelDataToCSVFile( "Sample.csv");//, nWidth, nHeight, nLineCount );

	////Send a notification that the Snap Shot Capturing is complete
	//if(pObjPixelBuff->m_bContinuousCapture)
	//{
	//	AfxGetApp()->m_pMainWnd->PostMessage(WM_SNAPSHOT_COMPLETED,0,TRUE);//if LPARAM is TRUE, application should go on capturing the next frame when notified 
	//}
	//else if(pObjPixelBuff->m_bSnapShot)
	//{
	//	AfxGetApp()->m_pMainWnd->PostMessage(WM_SNAPSHOT_COMPLETED,0,FALSE);
	//	pObjPixelBuff->m_bSnapShot=FALSE;
	//}

	//Send a notification that the Snap Shot Capturing is complete
	if(pObjPixelBuff->m_bContinuousCapture)
	{
		AfxGetApp()->m_pMainWnd->PostMessage(WM_SNAPSHOT_COMPLETED,0,TRUE);//if LPARAM is TRUE, application should go on capturing the next frame when notified 
	}
	else
	{
		AfxGetApp()->m_pMainWnd->PostMessage(WM_SNAPSHOT_COMPLETED,0,TRUE);//if LPARAM is TRUE, application should go on capturing the next frame when notified 
	}
	
	if(pObjPixelBuff->m_bSnapShot)
	{
		AfxGetApp()->m_pMainWnd->PostMessage(WM_SNAPSHOT_COMPLETED,0,FALSE);
		pObjPixelBuff->m_bSnapShot=FALSE;
	}

	return 0;
}

CCapturePixels::CCapturePixels()
{
	m_nGain = 1;
	//m_nExposureTime=10;
	//m_nExposureTime=100;
	m_nExposureTime = DEFAULT_EXPOSURE_TIME;
	m_nLineCount = 1;
	m_nOffset = 10;

	m_bShowAvg = FALSE;
	m_bShowRSD = FALSE;
	m_bShowSD = FALSE;

	m_pBuffPixelData = NULL;
	m_pPixelLines = NULL;
	m_bContinuousCapture = FALSE;
	m_bSnapShot = FALSE;

	m_pBufAvgPixelData = new double[MAX_PIXEL_DATA_COUNT_PER_LINE];
	m_pBufSDPixelData = new double[MAX_PIXEL_DATA_COUNT_PER_LINE];
	m_pBufRSDPixelData = new double[MAX_PIXEL_DATA_COUNT_PER_LINE];
	m_nVersion = DOC_VERSION;
}
void CCapturePixels::ClearPixelBuffer()
{
	if(m_pBuffPixelData!=NULL)
	{
		delete [] m_pBuffPixelData;
		m_pBuffPixelData=NULL;
	}
	//memset(m_pBufAvgPixelData,0,MAX_PIXEL_DATA_COUNT_PER_LINE*sizeof(double));
}
CCapturePixels::~CCapturePixels()
{
	ClearPixelBuffer();
	if(m_pBufAvgPixelData)
		delete [] m_pBufAvgPixelData;
	if(m_pBufSDPixelData)
		delete [] m_pBufSDPixelData;
	if(m_pBufRSDPixelData)
		delete [] m_pBufRSDPixelData;
}

//Prepare a series of buffers to reference each Scan Pixel Line buffer individually
void CCapturePixels::PreparePixelLineBuffFromSnapShot()
{
	if(m_pPixelLines)
		delete [] m_pPixelLines;

	m_pPixelLines = new WORD*[m_nLineCount];
	//m_pPixelLines = new double*[m_nLineCount];//1.3
	for(int i=0;i<m_nLineCount;i++)
	{
		m_pPixelLines[i]=GetLinePixelBuf(i);
	}
	GetAvgPixelDataBuf();
	GetSDPixelBuffer();
	GetRSDPixelBuffer();
}



//Returns the Pixel buffer of a scanned line with the given Line Number.
//The Length of the returned pixel buffer is defined by MAX_PIXEL_DATA_COUNT_PER_LINE value
WORD* CCapturePixels::GetLinePixelBuf(int nLineNo)
//double* CCapturePixels::GetLinePixelBuf(int nLineNo)
{
	if(  m_pBuffPixelData == NULL)
		return NULL;
	WORD (*pBuf)[MAX_PIXEL_DATA_COUNT_PER_LINE] = (WORD(*)[MAX_PIXEL_DATA_COUNT_PER_LINE])m_pBuffPixelData;
	//double (*pBuf)[MAX_PIXEL_DATA_COUNT_PER_LINE] = (double(*)[MAX_PIXEL_DATA_COUNT_PER_LINE])m_pBuffPixelData;
	if((nLineNo>=0) && (nLineNo<m_nLineCount))
		return pBuf[nLineNo];
	else
		return NULL;
}

// Get the pixel buffer with the Average of all the Pixel line buffers
double* CCapturePixels::GetAvgPixelDataBuf(void)
{
	for(int i=0;i<MAX_PIXEL_DATA_COUNT_PER_LINE;i++)
	{
		unsigned long sum=0;
		for(int j=0;j<m_nLineCount;j++)
		{
			sum+=m_pPixelLines[j][i];
		}
		m_pBufAvgPixelData[i]=(double)sum/m_nLineCount;
	}

	return m_pBufAvgPixelData;
}

// Get the Pixel buffer with the Standard Deviation of all the Pixel Line buffers
double* CCapturePixels::GetSDPixelBuffer(void)
{
	//get the sum of sqr(Xi-Avg)
	for(int i=0;i<MAX_PIXEL_DATA_COUNT_PER_LINE;i++)
	{
		double sum=0;
		for(int j=0;j<m_nLineCount;j++)
		{
			sum +=  pow((double)(m_pPixelLines[j][i]-m_pBufAvgPixelData[i]),2.0);
		}
		double sd= sqrt(sum/(m_nLineCount-1));
		m_pBufSDPixelData[i]=sd;
	}

	return m_pBufSDPixelData;
}

// Get the Pixel Buffer with the RSD of  all the Pixel Line Buffers
double* CCapturePixels::GetRSDPixelBuffer(void)
{
	for(int j=0;j<MAX_PIXEL_DATA_COUNT_PER_LINE;j++)
	{
		m_pBufRSDPixelData[j]=  (m_pBufSDPixelData[j]*100.0)/m_pBufAvgPixelData[j];
	}
	return m_pBufRSDPixelData;
}

//Start the Capturing of Pixel Buffer as per the given Line Count
void CCapturePixels::CaptureSnapShot()
{
	//<--1.3--
	/*CMainFrame * pFrame = (CMainFrame*)AfxGetMainWnd();
	CArraySpectrumDoc* pDoc = NULL;
	pDoc = (CArraySpectrumDoc*)(pFrame->GetActiveDocument());
	if(pDoc == NULL)
		return;*/
	//--1.3-->

	m_bSnapShot = TRUE;
	m_bContinuousCapture = FALSE;
	ClearPixelBuffer();
	NotifyToClearAllViews();

	//<--1.3--
	//CAPTURE_SNAP_FROM_DA_PARAMS* ptrThreadParams = new CAPTURE_SNAP_FROM_DA_PARAMS();
	//ptrThreadParams->ptrPixelBuff = this;
	//ptrThreadParams->ptrDoc = pDoc;
	//--1.3-->

	AfxBeginThread(CaptureSnapShotThread,this);
	//AfxBeginThread(CaptureSnapShotThread,ptrThreadParams);//<--Added for 1.2-->

}
// Start Capturing Continuous Frames
void CCapturePixels::StartCapture(void)
{
	CMainFrame * pFrame = (CMainFrame*)AfxGetMainWnd();
	CArraySpectrumDoc* pDoc=NULL;
	pDoc = (CArraySpectrumDoc*)(pFrame->GetActiveDocument());
	if(pDoc == NULL)
		return;

	m_bContinuousCapture=TRUE;
	m_bSnapShot=FALSE;
	ClearPixelBuffer();  

	//<--1.3
	//CAPTURE_SNAP_FROM_DA_PARAMS* ptrThreadParams = new CAPTURE_SNAP_FROM_DA_PARAMS();
	//ptrThreadParams->ptrPixelBuff = this;
	//ptrThreadParams->ptrDoc = pDoc;
	//--1.3->

	AfxBeginThread(CaptureSnapShotThread,this);
}


// Stop Capturing Continuous Frames
void CCapturePixels::StopCapture(void)
{
	m_bContinuousCapture=FALSE;
}


//Notify the Frame to Clear all the  Data Presentation of the Views. Here the FrameWnd will  notify the Views to Clear the existing Data Presentations
void CCapturePixels::NotifyToClearAllViews(void)
{
	AfxGetApp()->m_pMainWnd->SendMessage(WM_CLEAR_ALL_VIEWS,0,0);
}


void CCapturePixels::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar << m_nVersion;
		ar << m_nGain; 
		ar << m_nExposureTime;
		ar << m_nLineCount;
		ar << m_nOffset;
		ar << m_bShowAvg;
		ar << m_bShowRSD;
		ar << m_bShowSD;
		//Now, Save the whole Pixel Data Buffer of the Snap Shot
		ar << m_nPixelBufImageSize;
		//ar.Write(m_pBuffPixelData,m_nPixelBufImageSize*sizeof(WORD));
		ar.Write(m_pBuffPixelData,m_nPixelBufImageSize*sizeof(double));

		//TEST Code to store the single line pixel buffer 
		//ar <<(int)MAX_PIXEL_DATA_COUNT_PER_LINE;
		//ar.Write(m_pBuffPixelData,MAX_PIXEL_DATA_COUNT_PER_LINE*sizeof(WORD));
	}
	else
	{	// loading code
		ar >> m_nVersion;
		ar >> m_nGain; 
		ar >> m_nExposureTime;
		ar >> m_nLineCount;
		ar >> m_nOffset;
		ar >> m_bShowAvg;
		ar >> m_bShowRSD;
		ar >> m_bShowSD;
		//Retrieve the Whole Pixel Data Buffer of the Snap Shot
		ar >> m_nPixelBufImageSize;
		m_pBuffPixelData= new WORD[m_nPixelBufImageSize];
		ar.Read(m_pBuffPixelData,m_nPixelBufImageSize*sizeof(WORD));
		
		//<--1.3
		//m_pBuffPixelData= new double[m_nPixelBufImageSize];
		//ar.Read(m_pBuffPixelData,m_nPixelBufImageSize*sizeof(double));
		//--1.3-->

		//Now,Prepare a series of buffers to reference each Scan Pixel Line buffer individually
		PreparePixelLineBuffFromSnapShot();

		/*GetAvgPixelDataBuf();
		GetSDPixelBuffer();
		GetRSDPixelBuffer();*/
	}
}
//returns TRUE, if the Pixel Data Buffer is NULL (i.e No Captured Data is Available)
BOOL CCapturePixels::ISEmpty()
{
	if(m_pBuffPixelData)
		return FALSE;
	else
		return TRUE;

}