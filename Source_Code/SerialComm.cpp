#include "stdafx.h"
#include "SerialComm.h"


CSerialComm::CSerialComm()
{
	m_bPortOpened = FALSE;
}

CSerialComm::~CSerialComm()
{

}

BOOL CSerialComm::Open(CString strPortName)
{
	m_strPortname = strPortName;

	m_hfile = CreateFile (m_strPortname, // Port Name (Unicode compatible)
		GENERIC_READ | GENERIC_WRITE, // Open for Read-Write
		0,             // COM port cannot be shared
		NULL,          
		OPEN_EXISTING, // For communication resource
		FILE_FLAG_OVERLAPPED,
		NULL);  

	if(m_hfile == INVALID_HANDLE_VALUE)
	{
		//AfxMessageBox(_T("Device is not found"));
		//EFCMessageBox(_T("Invalid Handle"),_T("truVision"),MB_OK,MB_ICONINFORMATION);
		return FALSE;
	}


	// set the timeouts to specify the behavior of reads and writes.
	COMMTIMEOUTS ct;
	ct.ReadIntervalTimeout = MAXDWORD; 
	ct.ReadTotalTimeoutMultiplier = 0; 
	ct.ReadTotalTimeoutConstant = 0; 
	ct.WriteTotalTimeoutMultiplier = 0; 
	ct.WriteTotalTimeoutConstant = 0;
	/*
	ct.ReadIntervalTimeout = MAXDWORD; 
	ct.ReadTotalTimeoutMultiplier = MAXDWORD; 
	ct.ReadTotalTimeoutConstant = 1;
	ct.WriteTotalTimeoutMultiplier = 0; 
	ct.WriteTotalTimeoutConstant = 0; 
	*/
	if(!SetCommTimeouts(m_hfile, &ct))
	{
		AfxMessageBox(_T("Unable to set comm. timeouts. "));
		Close(); // close com port
		return FALSE;
	}


	// get the current communications parameters, and configure baud rate
	DCB dcb={0};
	dcb.DCBlength = sizeof(DCB);
	if(!GetCommState(m_hfile, &dcb))
	{

		AfxMessageBox(_T("Unable to get COM State"));
		Close(); // close comm port
		return S_FALSE;
	}
	dcb.BaudRate = CBR_115200;		// set baud rate to 115200
	dcb.ByteSize=8;
	dcb.fBinary=TRUE;
	dcb.fDsrSensitivity = FALSE ;
	//
	dcb.Parity = NOPARITY;
	dcb.StopBits= ONESTOPBIT;
	dcb.fOutxCtsFlow = FALSE;
	dcb.fOutxDsrFlow = FALSE;
	dcb.fOutX = FALSE;
	dcb.fInX = FALSE;	
	
	memset(&olWrite,0,sizeof(olWrite));
	memset(&olRead,0,sizeof(olRead));

	olWrite.hEvent = CreateEvent(NULL,TRUE,FALSE,_T(""));
	olRead.hEvent = CreateEvent(NULL,TRUE,FALSE,_T(""));

	//reinitialize the Serial Port state and control settings with our own settings  
	if(!SetCommState(m_hfile, &dcb))
	{

		AfxMessageBox(_T("Unable to Get COM State"));
		Close(); // close comm port
		return S_FALSE;
	}
	SetCommMask (m_hfile, EV_RXCHAR|EV_TXEMPTY);
	//FlushFileBuffers(m_hfile);
	PurgeComm(m_hfile,PURGE_TXCLEAR|PURGE_RXCLEAR);
	COMSTAT cs;
	DWORD dw;

	ClearCommError(m_hfile,&dw,&cs);

	m_bPortOpened = TRUE;

	return TRUE;
}

BOOL CSerialComm::Close()
{
	BOOL blretval;
	if(m_hfile != NULL)
	{
		blretval = CloseHandle(m_hfile);
		m_hfile = NULL;

		m_bPortOpened = FALSE;
	}
	return blretval;
}
CEvent ev(FALSE,TRUE,_T("event"));
BOOL CSerialComm::Send(BYTE* buf, LONG lngBuflen)
{
	DWORD dwBytesWritten,dwBytesWritten1;

	ev.ResetEvent();
	
	if(!WriteFile(m_hfile,	// where to write to (the open comm port)
		buf,			// what to write
		lngBuflen,		// number of bytes to be written to port
		&dwBytesWritten,	// number of bytes that were actually written
		&olWrite))				// overlapped I/O not supported			
	{

		return FALSE;
	}

	ev.SetEvent();


	GetOverlappedResult(m_hfile,&olWrite,&dwBytesWritten1,TRUE);

	return TRUE;
}

BOOL CSerialComm::Receive(LONG lngActualResponeLen,LONG lngWaitTimeInSec,BYTE* ptrReceivedBuff,LONG* lngReceivedBuffLen,BOOL* bIsTotalBuffReceived,BOOL* bIsTimeoutOccurred)
{
	if((lngActualResponeLen == 0) || (lngWaitTimeInSec == 0))
	{
		return FALSE;
	}

	//BYTE* byteDataBuf =  NULL;
	//byteDataBuf = new BYTE[lngActualResponeLen];
	memset(ptrReceivedBuff,0,lngActualResponeLen);//initialize the buffer
	long lngCurrentIndex = 0;//actual response last element index

	//wait for 
	CTime startTime(CTime::GetCurrentTime());
	CTime currenttime(CTime::GetCurrentTime());

	CTimeSpan tsStartTime(startTime.GetDay(),startTime.GetHour(),startTime.GetMinute(),startTime.GetSecond());
	CString strLog;
	//read the serial port data until timeout occures or totalresponse is received
	while(1)
	{
		CTimeSpan tsCurrenTime(currenttime.GetDay(),currenttime.GetHour(),currenttime.GetMinute(),currenttime.GetSecond());
		LONG lngWaitTimeDuraion  = (tsCurrenTime-tsStartTime).GetTotalSeconds();//find the duration of loop.
		if (lngWaitTimeDuraion > lngWaitTimeInSec)
		{	
			//if timeout is happened then exit
			*bIsTimeoutOccurred = TRUE;
			*bIsTotalBuffReceived = FALSE;
			break;
		}
		//store the response in a temp buff
		BYTE* tempBuff = NULL;
		tempBuff = new BYTE[lngActualResponeLen];
		//BYTE tempBuff[2051];
		memset(tempBuff,0,lngActualResponeLen);//initialize the buffer
		long lngTempLen = lngActualResponeLen;

		SyncReceive(tempBuff,&lngTempLen);

		//copy the response into actual buffer
		if((tempBuff != NULL) && (lngTempLen > 0))
		{
			for(int nIndex = 0; nIndex < lngTempLen; nIndex++)
			{
				ptrReceivedBuff[lngCurrentIndex++] = tempBuff[nIndex];
			}

			delete[] tempBuff;
			tempBuff = NULL;
		}

		//if total response is received then exit
		if(lngCurrentIndex == lngActualResponeLen)
		{
			*bIsTotalBuffReceived = TRUE;
			*bIsTimeoutOccurred = FALSE;
			return FALSE;
		}
		Sleep(1);
		currenttime = CTime::GetCurrentTime();
	}
}

BOOL CSerialComm::SyncReceive(BYTE* pBuf, LONG* pLength)
{
	if ( (pBuf == NULL)  || (pLength == NULL))
	{
		return FALSE;
	}
	// TODO: Add your implementation code here
	DWORD dwBytesRead=0;
	/*LPVOID lpMsgBuf;*/
	//BYTE tempBuff[3000];
	//memset(tempBuff,0,3000);
	//DWORD lngTempLen = 2051;
	BOOL bResult =  ReadFile(m_hfile,		// where to read from (the open comm port)
		pBuf,			// where to put the character
		*pLength,				// number of bytes to read
		&dwBytesRead,		// how many bytes were actually read
		&olRead);//;				// overlapped I/O not supported

	//FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,NULL,GetLastError(),0,(LPTSTR) &lpMsgBuf,0,NULL);
	//WriteDiodeArrayLog((LPCTSTR)lpMsgBuf);
	//WriteDiodeArrayLog(_T("\r\n"));
	//CString strTemp;
	//strTemp.Format(_T("%ld\r\n"),dwBytesRead);
	//WriteDiodeArrayLog(strTemp);
	//LocalFree( lpMsgBuf );

	BOOL b2 = GetOverlappedResult(m_hfile,&olRead,&dwBytesRead,FALSE);
	if(b2 == FALSE)
	{
		*pLength=0;
		return FALSE;
	}
	*pLength = dwBytesRead;
	return TRUE;
}

BOOL CSerialComm::IsPortOpened()
{
	return m_bPortOpened;
}