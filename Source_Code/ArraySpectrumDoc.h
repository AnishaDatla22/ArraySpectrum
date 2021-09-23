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

// ArraySpectrumDoc.h : interface of the CArraySpectrumDoc class
//


#pragma once

#include "capturepixels.h"
#include "SerialComm.h"
#include "settings.h"

class CArraySpectrumDoc : public CDocument
{
protected: // create from serialization only
	CArraySpectrumDoc();

	DECLARE_DYNCREATE(CArraySpectrumDoc)

	// Attributes
public:
	///
    double m_bufWLDataPoints[MAX_PIXEL_DATA_COUNT_PER_LINE];

	////Each item in 
 //   CArray<double*,double*> m_PixelDataLines;
	///
    CSettings m_objSettings;
	///
	CString m_strSelectedCommPortName;
	///
	CCapturePixels m_objCapturePixelBuff;
	///
	CSerialComm m_objSerialComm;
	 //polynomial Co-efficients
    double m_dblCoeffA;
	///
	double m_dblCoeffB;
	///
	double m_dblCoeffC;
	///
	double m_dblCoeffD;
	///
	double m_arrdblCompoundPeakArea[NO_OF_COMPOUNDS];
	///
	

	// Overrides
public:
	///
	virtual BOOL OnNewDocument();
	///
	virtual void Serialize(CArchive& ar);

	// Implementation
public:
	virtual ~CArraySpectrumDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	
protected:

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	// This method is used to Start the Capturing of Spectrum continuously (based on the Integration time). If the Capturing is Started, the "Capture Start" button is toggled to "Stop".
	void StartCapture(void);
	
	// Apply the Capture Properties to the Data Acquisition h/w. This method should be called before the "Capturing" or "Snap Shot" of the Spectrum (Pixels) is invoked 
	void ApplyCaptureProperties(void);
	
	//Acquires a single snap shot frame data from the device
	BOOL AcquireSnapShotData(void);
    
	//Start Continuous Capturing of Frames from CCD
	//void CArraySpectrumDoc::StartCapture(void);
	
	//Stop Continuous Capturing of Frames from CCD
	void StopCapture(void);
	// Updaate the Propery Pane with property values respective to the opened Job and if bEnable is FALSE, disable the Property pane. 
	void UpdatePropertiesPane(bool bEnable);
	///
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	///
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	///
	virtual void DeleteContents();
	///
	BYTE fncCalcChecksum(BYTE* ptrchksumcontents,int nlenofbytearr);

	//for getting absorbance value by clubbing msb and lsb value sent by instrument
	unsigned short fncGetADCValue(BYTE* bhibyte,BYTE* blowbyte);
	///
	double fncCalEnergy(double dblRefval,double dblSmpval);
	///
	unsigned short* fncSetData(BYTE *RawScanData,LONG lngLength);

	//Arrays for holding data related to d2 scan
	//CArray<unsigned short,unsigned short> m_ArrD2RefOpen;

	// Retrieve the Polynomial Co-efficients required for mapping Pixel to WL
	void RetrievePolyCoEfficients(void);
	
	//Convert the Pixel Numbers to WL numbers based on the Polynomial co-efficients obtained in Calibration.
	//Returns the buffer containing the converted WaveLength numbers
	double * ConvertPixelNumbersToWL();
	///
	//void RetrieveSettings(void);
	///
	void SerializeSettingsData(bool bSave);
	///Finds the nearest given value in an array by using binary search algorithm principle
	void FindNeareastIndex(double* dblArray, int nSize,double value,bool* ptrbExactMatchFound,int* ptrnNearestIndex);
};


