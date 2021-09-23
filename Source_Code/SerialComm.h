#pragma once


class CSerialComm
{
private:
	//handle of the port
	HANDLE m_hfile;

	CString m_strPortname;
	
	BOOL m_bPortOpened;

public:
	OVERLAPPED olRead;
	
	OVERLAPPED olWrite;

public:
	CSerialComm();

	~CSerialComm();

	//Open the ComPort
	BOOL Open(CString strPortName);

	//This will close the COMPort
	BOOL Close();

	//This is for sending the Data to instrument
	BOOL Send(BYTE* buf, LONG lngBuflen);

	///this function read the serial port data
	///read the serial port data until lngwaitTimeInSec timeout occures.
	///function will return if total bytes read from the port is lngActualResponseLen and timeout is not occured.
	///if successfully total bytes read from the port then bIsTotalBuffReceived is set to TRUE.
	///if the timeout occures then, bIsTimeoutOccured is set to TRUE.
	BOOL Receive(LONG lngActualResponeLen,LONG lngWaitTimeInSec,BYTE* ptrReceivedBuff,LONG* lngReceivedBuffLen,BOOL* bIsTotalBuffReceived,BOOL* bIsTimeoutOccurred);

	BOOL SyncReceive(BYTE* pBuf, LONG* pLength);

	BOOL IsPortOpened();

};
