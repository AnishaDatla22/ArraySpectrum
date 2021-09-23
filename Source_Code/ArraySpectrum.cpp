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

// ArraySpectrum.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "ArraySpectrum.h"
#include "MainFrm.h"

#include "ArraySpectrumDoc.h"
#include "ArraySpectrumView.h"
#include "SpreadSheet.h"
#include "constants.h"
#include "WLSpectrumView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CArraySpectrumApp

BEGIN_MESSAGE_MAP(CArraySpectrumApp, CWinAppEx)
	ON_COMMAND(ID_INFORMATION_ABOUT,OnAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CArraySpectrumApp construction

CArraySpectrumApp::CArraySpectrumApp()
{

	m_bHiColorIcons = TRUE;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CArraySpectrumApp object

CArraySpectrumApp theApp;


// CArraySpectrumApp initialization

BOOL CArraySpectrumApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	//SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	SetRegistryKey(_T("ArraySpectrum"));
	LoadStdProfileSettings(0);  // Load standard INI file options
	
	TCHAR szPath[MAX_PATH];

	if( GetModuleFileName( NULL, szPath, MAX_PATH ) != 0)
	{
		m_strConfigIniPath = szPath;
		int nPos = m_strConfigIniPath.ReverseFind(_T('\\'));
		if(nPos != -1)
		{
			m_strConfigIniPath = m_strConfigIniPath.Mid(0,nPos);	
		}
		m_strConfigIniPath += _T("\\Calib_Config.ini");
	}


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	
	//pDocTemplate = new CSingleDocTemplate(
	//	IDR_MAINFRAME,
	//	RUNTIME_CLASS(CArraySpectrumDoc),
	//	RUNTIME_CLASS(CMainFrame),       // main SDI frame window
	//	RUNTIME_CLASS(CArraySpectrumView));

	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CArraySpectrumDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CWLSpectrumView));

	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	//Update Property Pane Dlg
	//m_pMainWnd->PostMessage(WM_UPDATE_PROPERTIES,0,0);
	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();
	return TRUE;
}



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// App command to run the dialog
void CArraySpectrumApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CArraySpectrumApp customization load/save methods

void CArraySpectrumApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	//GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	///*bNameValid = strName.LoadString(IDS_EXPLORER);
	//ASSERT(bNameValid);
	//GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);*/
}

void CArraySpectrumApp::LoadCustomState()
{
}

void CArraySpectrumApp::SaveCustomState()
{
}

// CArraySpectrumApp message handlers


void CArraySpectrumApp::OnAbout(void)
{
	//<--Commented for testing setting floating dialog
	CAboutDlg dlg;
	dlg.DoModal();
    //<--Commented for testing setting floating dialog

    //<--Testing--
	//CMainFrame *pMainWnd = (CMainFrame *)AfxGetMainWnd();
	/*((CMainFrame *)m_pMainWnd)->m_ptrSettingsDlg->m_pDoc = 
	((CMainFrame *)m_pMainWnd)->m_ptrSettingsDlg->ShowWindow(SW_SHOWNORMAL);*/
	//((CMainFrame *)m_pMainWnd)->Invalidate();
	//--Testing-->
}

///////
////int CArraySpectrumApp::binary_search(double* arr,int first,int last, double search_key)
////{
////	int index;
////
////	if (first > last)
////		index = -1;
////
////	else
////	{
////		int mid = (first + last)/2;
////
////		if (search_key == arr[mid])
////			index = mid;
////		else
////
////			if (search_key < arr[mid])
////				index = binary_search(arr,first, mid-1, search_key);
////			else
////				index = binary_search(arr, mid+1, last, search_key);
////
////	} // end if
////	return index;
////}// end binarySearch



void CArraySpectrumApp::GetLinearCoefficient(double* ptrdblXVals,double* ptrdblYVals,int nStartIndex, int nSize,double* ptrdblSlope,double* ptrdblIntercept)
{
	double dblSumX =0;
	double dblSumXSquare = 0;
	double dblSumY = 0;
	double dblSumXY = 0;

	double dblNumerator = 0;
	double dblDenominator = 0;

	for (int nIndex = nStartIndex; nIndex < (nStartIndex+nSize) ; nIndex++)
	{
		dblSumX += ptrdblXVals[nIndex];
		dblSumXSquare += (ptrdblXVals[nIndex] * ptrdblXVals[nIndex]);
		dblSumY += ptrdblYVals[nIndex];
		dblSumXY += (ptrdblXVals[nIndex] * ptrdblYVals[nIndex]);
	}
	
	dblNumerator = ((nSize*dblSumXY)-(dblSumX*dblSumY));
	dblDenominator = ((nSize*dblSumXSquare)-(dblSumX*dblSumX));

	if(dblDenominator!=0)
		*ptrdblSlope = dblNumerator/dblDenominator;
	dblNumerator = ((dblSumY*dblSumXSquare)-(dblSumX*dblSumXY));
	if(dblDenominator!=0)
		*ptrdblIntercept = dblNumerator/dblDenominator;
}

