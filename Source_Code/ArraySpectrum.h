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

// ArraySpectrum.h : main header file for the ArraySpectrum application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include "constants.h"

// CArraySpectrumApp:
// See ArraySpectrum.cpp for the implementation of this class
//

//<--Version 1.1
//Purpose:
//		  The "ArraySpectrum" application is developed to work with HAMAMATSU CCD Module to capture the Pixel Data(2068)
//<--Version 1.2
//Purpose:
//        The "ArraySpectrum" application is developed to work with DiodeArray module to capture the pixel data(1024)
//        Add _SA165 preprocessor and _NoBYTEREVERSAL preprocessor if detector is diodearray
//        Remove _SA165 and _NoBYTEREVERSAL if detector is not diodearray

class CArraySpectrumApp : public CWinAppEx
{
public:
	CArraySpectrumApp();
  
// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	///
	void OnAbout(void);
	///
	//void OnDisplaySettings(void);
	
	DECLARE_MESSAGE_MAP()
public:
	
	///
	void GetLinearCoefficient(double* ptrdblXVals,double* ptrdblYVals,int nStartIndex, int nSize,double* dblSlope,double* dblIntercept);
	///
	CString m_strConfigIniPath;
};

extern CArraySpectrumApp theApp;
