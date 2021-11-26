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

// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ArraySpectrum.h"
#include "MainFrm.h"
#include "DataView.h"
#include "pixeldataview.h"
#include "wldataview.h"
#include "wlspectrumview.h"
#include "constants.h"
#include "CommPortSettings.h"
#include "DcIcUSB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnUpdateApplicationLook)

	ON_COMMAND(ID_FILE_CAPTURE_START,OnStartCapture)
	ON_UPDATE_COMMAND_UI(ID_FILE_CAPTURE_START, &CMainFrame::OnUpdateStartCapture)

	ON_COMMAND(ID_FILE_CAPTURE_STOP,OnStopCapture)
	ON_UPDATE_COMMAND_UI(ID_FILE_CAPTURE_STOP, &CMainFrame::OnUpdateStopCapture)

	ON_COMMAND(ID_FILE_SNAP,OnSnapShot)
	ON_UPDATE_COMMAND_UI(ID_FILE_SNAP, &CMainFrame::OnUpdateSnapShot)

	ON_COMMAND(ID_FILE_PIXEL,OnSelectPixelMode)
	ON_UPDATE_COMMAND_UI(ID_FILE_PIXEL, &CMainFrame::OnUpdateSelectPixelMode)

	ON_COMMAND(ID_FILE_WAVELENGTH,OnSelectWLMode)
	ON_UPDATE_COMMAND_UI(ID_FILE_WAVELENGTH, &CMainFrame::OnUpdateSelectWLMode)

	ON_COMMAND(ID_FILE_CALIB, OnCalibration)
	ON_UPDATE_COMMAND_UI(ID_FILE_CALIB,OnUpdateCalibration)

	ON_COMMAND(ID_FILE_EXPORT_PIXEL_DATA,OnFileExportPixelData)
	ON_COMMAND(ID_FILE_EXPORT_WL_DATA,OnFileExportWLData)

	ON_COMMAND(ID_FILE_CONNECT,OnConnectOrDisconnect)
	ON_UPDATE_COMMAND_UI(ID_FILE_CONNECT,OnUpdateConnectOrDisconnect)
	//	ON_COMMAND(ID_FILE_PRINT, &CMainFrame::OnFilePrint)
	//ON_COMMAND(ID_FILE_PRINT_DIRECT, &CMainFrame::OnFilePrint)
	//ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMainFrame::OnFilePrintPreview)
	//ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, &CMainFrame::OnUpdateFilePrintPreview)
	ON_WM_SIZE()


	ON_MESSAGE(WM_SNAPSHOT_COMPLETED,OnNotifySnapShotCompleted)
	ON_MESSAGE(WM_CLEAR_ALL_VIEWS,OnNotifyClearAllViews)
	ON_MESSAGE(WM_UPDATE_PROPERTIES,OnUpdateProperties)
	ON_MESSAGE(WM_CAPTURING_FAILED,OnNotifyCaptureFailed)
	//ON_COMMAND(ID_INFORMATION_ABOUT,OnAbout)
	ON_COMMAND(ID_DISPLAY_SETTINGS,OnDisplaySettings)
	ON_COMMAND(ID_VIEW_DATA_SHOW,OnViewDataShow)
	ON_COMMAND(ID_LASER_SETTINGS, OnLaserSettings)

	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	//theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2005);
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_BLACK);
	m_bStartCapturing = FALSE;
	m_bSnapShot = FALSE;

	//m_PresentationMode=PIXEL_MODE; //defaultz
	m_PresentationMode = WAVELENGTH_MODE; //defaultz

	m_ptrSettingsDlg =  new CSettingsDlg;
	m_bShowViewData = false;
	#if _SIM
	m_nNoOfScanCompl = 0;
	#endif
}

CMainFrame::~CMainFrame()
{
	if(m_ptrSettingsDlg != NULL)
	{
		delete m_ptrSettingsDlg;
		m_ptrSettingsDlg = NULL;
	}
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;
	// set the visual manager and style based on persisted value
	/*OnApplicationLook(theApp.m_nAppLook);*/

	m_wndRibbonBar.Create(this);
	InitializeRibbon();

	//if (!m_wndStatusBar.Create(this))
	//{
	//	TRACE0("Failed to create status bar\n");
	//	return -1;      // fail to create
	//}

	/*CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);*/

	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// Load menu item image (not placed on any standard toolbars):
	//CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);

	// create docking windows
	if (!CreateDockingWindows())
	{
		TRACE0("Failed to create docking windows\n");
		return -1;
	}
	//Properties Wnd

	m_wndPropertiesPane.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndPropertiesPane);

	m_ptrSettingsDlg->Create(IDD_SETTINGS, this);

	Invalidate();
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

void CMainFrame::InitializeRibbon()
{
	BOOL bNameValid;

	CString strTemp;
	bNameValid = strTemp.LoadString(IDS_RIBBON_FILE);
	//ASSERT(bNameValid);

	//// Load panel images:
	//m_PanelImages.SetImageSize(CSize(16, 16));
	//m_PanelImages.Load(IDB_BUTTONS);

	//// Init main button:
	m_MainButton.SetImage(IDB_MAIN);
	m_MainButton.SetText(_T("\nf"));
	m_MainButton.SetToolTipText(strTemp);

	m_wndRibbonBar.SetApplicationButton(&m_MainButton, CSize (45, 45));
	/*CMFCRibbonMainPanel* pMainPanel = m_wndRibbonBar.AddMainCategory(strTemp, IDB_FILESMALL, IDB_FILELARGE);

	bNameValid = strTemp.LoadString(IDS_RIBBON_NEW);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_NEW, strTemp, 0, 0));
	bNameValid = strTemp.LoadString(IDS_RIBBON_OPEN);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_OPEN, strTemp, 1, 1));
	bNameValid = strTemp.LoadString(IDS_RIBBON_SAVE);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_SAVE, strTemp, 2, 2));
	bNameValid = strTemp.LoadString(IDS_RIBBON_SAVEAS);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_SAVE_AS, strTemp, 3, 3));

	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnPrint = new CMFCRibbonButton(ID_FILE_PRINT, strTemp, 6, 6);
	pBtnPrint->SetKeys(_T("p"), _T("w"));
	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT_LABEL);
	ASSERT(bNameValid);
	pBtnPrint->AddSubItem(new CMFCRibbonLabel(strTemp));
	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT_QUICK);
	ASSERT(bNameValid);
	pBtnPrint->AddSubItem(new CMFCRibbonButton(ID_FILE_PRINT_DIRECT, strTemp, 7, 7, TRUE));
	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT_PREVIEW);
	ASSERT(bNameValid);
	pBtnPrint->AddSubItem(new CMFCRibbonButton(ID_FILE_PRINT_PREVIEW, strTemp, 8, 8, TRUE));
	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT_SETUP);
	ASSERT(bNameValid);
	pBtnPrint->AddSubItem(new CMFCRibbonButton(ID_FILE_PRINT_SETUP, strTemp, 11, 11, TRUE));
	pMainPanel->Add(pBtnPrint);
	pMainPanel->Add(new CMFCRibbonSeparator(TRUE));

	bNameValid = strTemp.LoadString(IDS_RIBBON_CLOSE);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_CLOSE, strTemp, 9, 9));

	bNameValid = strTemp.LoadString(IDS_RIBBON_RECENT_DOCS);
	ASSERT(bNameValid);
	pMainPanel->AddRecentFilesList(strTemp);

	bNameValid = strTemp.LoadString(IDS_RIBBON_EXIT);
	ASSERT(bNameValid);
	pMainPanel->AddToBottom(new CMFCRibbonMainPanelButton(ID_APP_EXIT, strTemp, 15));*/

	// Add "Home" category with "Clipboard" panel:
	bNameValid = strTemp.LoadString(IDS_RIBBON_HOME);
	ASSERT(bNameValid);
	CMFCRibbonCategory* pCategoryHome = m_wndRibbonBar.AddCategory(strTemp,IDB_SMALL_ICONS,IDB_LARGE_RIBBON_ICONS);// IDB_WRITESMALL, IDB_WRITELARGE);

	// Create "File" panel:
	bNameValid = strTemp.LoadString(IDS_RIBBON_FILE);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelFile = pCategoryHome->AddPanel(strTemp);//, m_PanelImages.ExtractIcon(27));

	//New Btn in FilePanel
	bNameValid = strTemp.LoadString(ID_FILE_NEW);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnNew = new CMFCRibbonButton(ID_FILE_NEW,strTemp, -1, 0);
	pPanelFile->Add(pBtnNew);

	//Open Button
	bNameValid = strTemp.LoadString(ID_FILE_OPEN);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnOpen = new CMFCRibbonButton(ID_FILE_OPEN,strTemp,-1, 1);
	pPanelFile->Add(pBtnOpen);

	//Save Button
	bNameValid = strTemp.LoadString(ID_FILE_SAVE);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnSave = new CMFCRibbonButton(ID_FILE_SAVE,strTemp, -1, 2);
	pPanelFile->Add(pBtnSave);

	//Save As Button
	bNameValid = strTemp.LoadString(ID_FILE_SAVE_AS);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnSaveAs = new CMFCRibbonButton(ID_FILE_SAVE_AS,strTemp, -1, 3);
	pPanelFile->Add(pBtnSaveAs);


	//Capture panel
	bNameValid = strTemp.LoadString(IDS_RIBBON_CAPTURE);
	ASSERT(bNameValid);
	pPanelCapture = pCategoryHome->AddPanel(strTemp);//, m_PanelImages.ExtractIcon(27));

	//Capture Start Button
	bNameValid = strTemp.LoadString(ID_FILE_CAPTURE_START);
	ASSERT(bNameValid);
	pBtnCapture = new CMFCRibbonButton(ID_FILE_CAPTURE_START,strTemp, -1, 4);
	pPanelCapture->Add(pBtnCapture);

	//Capture Stop Button
	bNameValid = strTemp.LoadString(ID_FILE_CAPTURE_STOP);
	ASSERT(bNameValid);
	pBtnCapture = new CMFCRibbonButton(ID_FILE_CAPTURE_STOP,strTemp, -1, 5);
	pPanelCapture->Add(pBtnCapture);

	//Snap Shot Button
	bNameValid = strTemp.LoadString(ID_FILE_SNAP);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnSnap = new CMFCRibbonButton(ID_FILE_SNAP,strTemp, -1, 6);
	pPanelCapture->Add(pBtnSnap);


	//View Panel
	bNameValid = strTemp.LoadString(IDS_RIBBON_VIEW);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelView = pCategoryHome->AddPanel(strTemp);//, m_PanelImages.ExtractIcon(27));

	//Pixel Button
	bNameValid = strTemp.LoadString(ID_FILE_PIXEL);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnView = new CMFCRibbonButton(ID_FILE_PIXEL,strTemp, -1, 7);
	pPanelView->Add(pBtnView);

	//WaveLength Button
	bNameValid = strTemp.LoadString(ID_FILE_WAVELENGTH);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnWL = new CMFCRibbonButton(ID_FILE_WAVELENGTH,strTemp, -1, 8);
	pPanelView->Add(pBtnWL);

	//#ifdef _SA165
	//Calib Panel
	bNameValid = strTemp.LoadString(IDS_RIBBON_CALIB);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelCalib = pCategoryHome->AddPanel(strTemp);//, m_PanelImages.ExtractIcon(27));

	//Calib Button
	bNameValid = strTemp.LoadString(ID_FILE_CALIB);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnCalib = new CMFCRibbonButton(ID_FILE_CALIB,strTemp, -1, 9);
	pPanelCalib->Add(pBtnCalib);
	//#endif

	//Export Panel
	bNameValid = strTemp.LoadString(IDS_RIBBON_EXPORT_DATA);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelExport = pCategoryHome->AddPanel(strTemp);//, m_PanelImages.ExtractIcon(27));

	//Pixel Export Button
	bNameValid = strTemp.LoadString(ID_FILE_EXPORT_PIXEL_DATA);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnExport = new CMFCRibbonButton(ID_FILE_EXPORT_PIXEL_DATA,strTemp, -1, 10);
	pPanelExport->Add(pBtnExport);
	//WL Data  Export Button
	bNameValid = strTemp.LoadString(ID_FILE_EXPORT_WL_DATA);
	ASSERT(bNameValid);
	pBtnExport = new CMFCRibbonButton(ID_FILE_EXPORT_WL_DATA,strTemp, -1, 11);
	pPanelExport->Add(pBtnExport);


	//Communication Panel
	bNameValid = strTemp.LoadString(IDS_RIBBON_COMMUNICATION);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelCommunication = pCategoryHome->AddPanel(strTemp);//, m_PanelImages.ExtractIcon(27));

	//Connect Button
	bNameValid = strTemp.LoadString(ID_FILE_CONNECT);
	ASSERT(bNameValid);
	pBtnConnectOrDisconnect = new CMFCRibbonButton(ID_FILE_CONNECT,strTemp, -1, 12);
	pPanelCommunication->Add(pBtnConnectOrDisconnect);

	//View Data Panel
	bNameValid = strTemp.LoadString(IDS_RIBBON_VIEW_DATA);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelViewData = pCategoryHome->AddPanel(strTemp);//, m_PanelImages.ExtractIcon(27));
	//Show View Data button
	bNameValid = strTemp.LoadString(ID_VIEW_DATA_SHOW);
	ASSERT(bNameValid);
	pBtnViewData = new CMFCRibbonButton(ID_VIEW_DATA_SHOW,strTemp, -1, 13);

	pPanelViewData->Add(pBtnViewData);

	//Display Settings Panel
	bNameValid = strTemp.LoadString(IDS_RIBBON_DISPLAY_SETTINGS);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelDisplaySettings = pCategoryHome->AddPanel(strTemp);//, m_PanelImages.ExtractIcon(27));
	//Display Settings button
	bNameValid = strTemp.LoadString(ID_DISPLAY_SETTINGS);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnDisplaySettings = new CMFCRibbonButton(ID_DISPLAY_SETTINGS,strTemp, -1, 15);

	pPanelDisplaySettings->Add(pBtnDisplaySettings);


	//InfoPanel
	bNameValid = strTemp.LoadString(IDS_RIBBON_ABOUT);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelInfo = pCategoryHome->AddPanel(strTemp);//, m_PanelImages.ExtractIcon(27));

	//About Button
	bNameValid = strTemp.LoadString(ID_INFORMATION_ABOUT);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnAbout = new CMFCRibbonButton(ID_INFORMATION_ABOUT,strTemp, -1, 16);

	pPanelInfo->Add(pBtnAbout);


	//LaserPanel
	bNameValid = strTemp.LoadString(IDS_RIBBON_LASER);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelLaser = pCategoryHome->AddPanel(strTemp);//, m_PanelImages.ExtractIcon(27));

	//Laser Settings Button
	bNameValid = strTemp.LoadString(ID_LASER_SETTINGS);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnLaser = new CMFCRibbonButton(ID_LASER_SETTINGS, strTemp, -1, 17);

	pPanelLaser->Add(pBtnLaser);

	//   //Properties Panel

	//bNameValid = strTemp.LoadString(IDS_RIBBON_SHOW_PROPERTIES);
	//ASSERT(bNameValid);
	//CMFCRibbonPanel* pPanelProps = pCategoryHome->AddPanel(strTemp, m_PanelImages.ExtractIcon(27));

	////Show Properties PAne
	//bNameValid = strTemp.LoadString(ID_FILE_SHOW_PROPERTIES);
	//ASSERT(bNameValid);
	//CMFCRibbonButton* pBtnShowPropPane = new CMFCRibbonButton(ID_FILE_SHOW_PROPERTIES,strTemp, 0, 0);
	//pPanelProps->Add(pBtnShowPropPane);


	//bNameValid = strTemp.LoadString(IDS_RIBBON_OPEN);
	//ASSERT(bNameValid);
	//pPanelClipboard->Add(new CMFCRibbonButton(ID_FILE_OPEN, strTemp, 1));
	//bNameValid = strTemp.LoadString(IDS_RIBBON_COPY);
	//ASSERT(bNameValid);
	//pPanelClipboard->Add(new CMFCRibbonButton(ID_EDIT_COPY, strTemp, 2));
	//bNameValid = strTemp.LoadString(IDS_RIBBON_SELECTALL);
	//ASSERT(bNameValid);
	//pPanelClipboard->Add(new CMFCRibbonButton(ID_EDIT_SELECT_ALL, strTemp, -1));

	//// Create and add a "View" panel:
	//bNameValid = strTemp.LoadString(IDS_RIBBON_VIEW);
	//ASSERT(bNameValid);
	//CMFCRibbonPanel* pPanelView = pCategoryHome->AddPanel(strTemp, m_PanelImages.ExtractIcon (7));

	//bNameValid = strTemp.LoadString(IDS_RIBBON_STATUSBAR);
	//ASSERT(bNameValid);
	//CMFCRibbonButton* pBtnStatusBar = new CMFCRibbonCheckBox(ID_VIEW_STATUS_BAR, strTemp);
	//pPanelView->Add(pBtnStatusBar);

	// Add elements to the right side of tabs:
	bNameValid = strTemp.LoadString(IDS_RIBBON_STYLE);
	ASSERT(bNameValid);
	CMFCRibbonButton* pVisualStyleButton = new CMFCRibbonButton(-1, strTemp, -1, -1);

	pVisualStyleButton->SetMenu(IDR_THEME_MENU, FALSE /* No default command */, TRUE /* Right align */);
	bNameValid = strTemp.LoadString(IDS_RIBBON_STYLE_TIP);
	ASSERT(bNameValid);
	pVisualStyleButton->SetToolTipText(strTemp);
	bNameValid = strTemp.LoadString(IDS_RIBBON_STYLE_DESC);
	ASSERT(bNameValid);

	pVisualStyleButton->SetDescription(strTemp);
	m_wndRibbonBar.AddToTabs(pVisualStyleButton);

	// Add quick access toolbar commands:
	//CList<UINT, UINT> lstQATCmds;

	/*lstQATCmds.AddTail(ID_FILE_NEW);
	lstQATCmds.AddTail(ID_FILE_OPEN);
	lstQATCmds.AddTail(ID_FILE_SAVE);
	lstQATCmds.AddTail(ID_FILE_PRINT_DIRECT);

	m_wndRibbonBar.SetQuickAccessCommands(lstQATCmds);
	m_wndRibbonBar.AddToTabs(new CMFCRibbonButton(ID_APP_ABOUT, _T("\na"), m_PanelImages.ExtractIcon (0)));*/
}

BOOL CMainFrame::CreateDockingWindows()
{

	BOOL bNameValid;

	CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);

	//Don't show the Close button of the DockPanel
	DWORD dwNoCloseBarStyle = AFX_DEFAULT_DOCKING_PANE_STYLE & ~AFX_CBRS_CLOSE;
	if(!m_wndPropertiesPane.Create(strPropertiesWnd,this,CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI,AFX_CBRS_REGULAR_TABS,dwNoCloseBarStyle))
	{

		TRACE0("Failed to create Properties window\n");
		return FALSE; // failed to create
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);

	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{

	HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndPropertiesPane.SetIcon(hPropertiesBarIcon, FALSE);

}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

//void CMainFrame::OnFilePrint()
//{
//	if (IsPrintPreview())
//	{
//		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_PRINT);
//	}
//}

//void CMainFrame::OnFilePrintPreview()
//{
//	if (IsPrintPreview())
//	{
//		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_CLOSE);  // force Print Preview mode closed
//	}
//}

//void CMainFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI)
//{
//	pCmdUI->SetCheck(IsPrintPreview());
//}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class
	////////if(!m_wndSplitter.CreateStatic(this,1,2))
	////////{
	////////	return FALSE;
	////////}

	////////CRect rect;
	////////GetClientRect(&rect);
	////////m_CC=*pContext;
	//////////if ( !m_wndSplitter.CreateView( 0, 1,RUNTIME_CLASS(CPixelDataView),CSize(rect.Width()/2, rect.Height()), pContext )) 
	////////   CSize sz;
	////////if(m_bShowViewData == false)
	////////{
	////////	sz.cx = rect.Width();
	////////	sz.cy = rect.Height();
	////////}
	////////else
	////////{
	////////	sz.cx = rect.Width()/2;
	////////	sz.cy = rect.Height();
	////////}
	////////if ( !m_wndSplitter.CreateView( 0, 0,RUNTIME_CLASS(CArraySpectrumView),sz, pContext )) 
	////////{ 
	////////	AfxMessageBox(_T("Splitter Creation Failed"));
	////////	return FALSE; 
	////////}
	////////

	//////////CArraySpectrumView
	//////////
	////////if(m_bShowViewData == false)
	////////{
	////////	sz.cx = 0;
	////////	sz.cy = rect.Height();
	////////}
	////////else
	////////{
	////////	sz.cx = rect.Width()/2;
	////////	sz.cy = rect.Height();
	////////}
	////////if ( !m_wndSplitter.CreateView( 0,1,RUNTIME_CLASS(CPixelDataView),CSize(rect.Width()/2, rect.Height()), pContext )) 
	////////{ 
	////////	AfxMessageBox(_T("Splitter Creation Failed"));
	////////	return FALSE; 
	////////}

	m_CC = *pContext;
	if(m_bShowViewData == TRUE)//Show Graph and DGrid Data Views in Splitter
	{
		if(!m_wndSplitter.CreateStatic(this,1,2))
		{
			return FALSE;
		}

		CRect rect;
		GetClientRect(&rect);
		m_CC=*pContext;
		//CArraySpectrumView
		/*if ( !m_wndSplitter.CreateView( 0, 0,RUNTIME_CLASS(CArraySpectrumView),CSize(rect.Width()/2, rect.Height()), pContext )) 
		{ 
			AfxMessageBox(_T("Splitter Creation Failed"));
			return FALSE; 
		}

		if ( !m_wndSplitter.CreateView( 0, 1,RUNTIME_CLASS(CPixelDataView),CSize(rect.Width()/2, rect.Height()), pContext )) 
		{ 
			AfxMessageBox(_T("Splitter Creation Failed"));
			return FALSE; 
		}*/

		if ( !m_wndSplitter.CreateView( 0, 0,RUNTIME_CLASS(CWLSpectrumView),CSize(rect.Width()/2, rect.Height()), pContext )) 
		{ 
			AfxMessageBox(_T("Splitter Creation Failed"));
			return FALSE; 
		}
		if ( !m_wndSplitter.CreateView( 0, 1,RUNTIME_CLASS(CWLDataView),CSize(rect.Width()/2, rect.Height()), pContext )) 
		{ 
			AfxMessageBox(_T("Splitter Creation Failed"));
			return FALSE; 
		}

		return TRUE;
	}
	else //Show Only Graph View
	{
		BOOL bRes=CFrameWndEx::OnCreateClient(lpcs, pContext);
		return TRUE;
	}

	//OnDisplaySettings();
	//return CFrameWndEx::OnCreateClient(lpcs, pContext);
	return TRUE;
}

void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWndEx::OnSize(nType, cx, cy);

	//if(m_wndSplitter.m_hWnd)
	///m_wndSplitter.RecalcLayout();
	// TODO: Add your message handler code here

}

// User defiened Message Handler for Clear All Views notification raised before capturing the Snap shot
LRESULT CMainFrame::OnNotifyClearAllViews(WPARAM wp, LPARAM lp)
{
	CArraySpectrumDoc* pDoc= (CArraySpectrumDoc*)GetActiveDocument();
	pDoc->m_objCapturePixelBuff.ClearPixelBuffer();
	pDoc->UpdateAllViews(NULL);
	return LRESULT();
}

// The message handler for the notification receivied when the Snap Shot capturing is completed.
//If the LPARAM is TRUE, then continue to capture a new snap shot again
LRESULT CMainFrame::OnNotifySnapShotCompleted(WPARAM wp, LPARAM lp)
{
	CArraySpectrumDoc* pDoc= (CArraySpectrumDoc*)GetActiveDocument();


	if(lp) //If non Zero, continue captureing
	{
		pDoc->UpdateAllViews(NULL,lp); //If Update Hint is non Zero, The Plot View should updates the line plot serieses with new pixel values
		//Sleep(2000);
		m_nNoOfScanCompl++;
		if(pDoc->m_objCapturePixelBuff.m_bContinuousCapture)
			pDoc->StartCapture();
	}
	else
	{
		m_bSnapShot=FALSE;
		pDoc->UpdateAllViews(NULL,lp);
	}
	return LRESULT();
}


void CMainFrame::OnStartCapture()
{
	CArraySpectrumDoc* pDoc = NULL;
	pDoc = (CArraySpectrumDoc*)GetActiveDocument();
	if (pDoc == NULL)
		return;

	/*#if _SIM
	m_nNoOfScanCompl = 0;
	#endif*/
	OnNotifyClearAllViews(0,0);
	pDoc->StartCapture();
	m_bStartCapturing=TRUE;
	

}

//Stop Continuous  Frames Capturing
void CMainFrame::OnStopCapture(void)
{
	#if _SIM
	m_nNoOfScanCompl = 0;
	#endif
	CArraySpectrumDoc* pDoc= (CArraySpectrumDoc*)GetActiveDocument();
	pDoc->StopCapture();
	m_bStartCapturing=FALSE;

}

void CMainFrame::OnUpdateStartCapture(CCmdUI* pCmdUI)
{
	if(m_bStartCapturing || m_bSnapShot)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

void CMainFrame::OnUpdateStopCapture(CCmdUI* pCmdUI)
{
	if(m_bStartCapturing && !m_bSnapShot)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}



void CMainFrame::OnUpdateSnapShot(CCmdUI* pCmdUI)
{
	if(m_bStartCapturing ||m_bSnapShot)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

// Capture a single Frame
void CMainFrame::OnSnapShot(void)
{
	CArraySpectrumDoc* pDoc=NULL;
	pDoc = (CArraySpectrumDoc*)GetActiveDocument();
	if(pDoc == NULL)
		return;
	/*if(pDoc->m_objSerialComm.IsPortOpened() == FALSE)
	{
	AfxMessageBox(_T("Please Connect the Communication Port"));
	return;
	}*/
#ifdef _SA165
	if(pDoc->m_strSelectedCommPortName.IsEmpty() == TRUE)
	{
		AfxMessageBox(_T("Please Connect the Communication Port"));
		return;
	}
#endif
	//else
	//{
	//	if(pDoc->m_objSerialComm.Open(pDoc->m_strSelectedCommPortName) == FALSE)
	//	{
	//		AfxMessageBox(_T("Failed to Open the Communication Port"));
	//		return;
	//	}
	//}
#ifdef _SIM
	//prompt the user to provide the pixel data in a csv format for a sigle line count
	// Create an Open dialog; the default file name extension is ".my".
	CFileDialog objFileDlg(TRUE,_T("Untitled"), _T("*.csv"),OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,_T("Pixel Data File(*.csv)|*.csv||"));

	// Display the file dialog. When user clicks OK, fileDlg.DoModal() 
	// returns IDOK.
	if(objFileDlg.DoModal() == IDOK)
	{
		CString strPathName = objFileDlg.GetPathName();

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
			pDoc->m_objCapturePixelBuff.ClearPixelBuffer();
			pDoc->m_objCapturePixelBuff.m_nLineCount = 1;
			pDoc->m_objCapturePixelBuff.m_nPixelBufImageSize = MAX_PIXEL_DATA_COUNT_PER_LINE;
			//pDoc->m_objCapturePixelBuff.m_pBuffPixelData = new double[MAX_PIXEL_DATA_COUNT_PER_LINE];
			pDoc->m_objCapturePixelBuff.m_pBuffPixelData = new WORD[MAX_PIXEL_DATA_COUNT_PER_LINE];
			for(int nIndex = 0; nIndex < MAX_PIXEL_DATA_COUNT_PER_LINE; nIndex++)
			{
				readFile.ReadString(strLine);//Line ADU values
				pDoc->m_objCapturePixelBuff.m_pBuffPixelData[nIndex] = _tcstod(strLine,NULL);
			}
			pDoc->m_objCapturePixelBuff.PreparePixelLineBuffFromSnapShot();
			GetActiveDocument()->UpdateAllViews(NULL);
		}
		else
		{
			CString strErrorMsg;
			strErrorMsg.Format(_T("Can't open file %s , error : %u"), strPathName, fileException.m_cause);
			AfxMessageBox(strErrorMsg);
		}
		readFile.Close();

	}

#else
	
	pDoc->AcquireSnapShotData();
	m_bSnapShot=TRUE;
#endif
}

// Event Handler for Pixel Mode Selection event 
void CMainFrame::OnSelectPixelMode(void)
{
	//////m_PresentationMode=PIXEL_MODE;
	//////CRect rect;
	//////GetClientRect(&rect);

	//////m_wndSplitter.DeleteView(0,0);
	//////CSize sz;
	//////if(m_bShowViewData == false)
	//////{
	//////	sz.cx = rect.Width();
	//////	sz.cy = rect.Height();
	//////}
	//////else
	//////{
	//////	sz.cx = rect.Width()/2;
	//////	sz.cy = rect.Height();
	//////}
	//////m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(CArraySpectrumView),sz,&m_CC);
	//////m_wndSplitter.RecalcLayout();
	////////m_wndSplitter.RedrawWindow();

	//////m_wndSplitter.DeleteView(0,1);
	////////CSize sz;
	//////if(m_bShowViewData == false)
	//////{
	//////	sz.cx = rect.Width();
	//////	sz.cy = rect.Height();
	//////}
	//////else
	//////{
	//////	sz.cx = 0;
	//////	sz.cy = rect.Height();
	//////}
	//////m_wndSplitter.CreateView(0,1,RUNTIME_CLASS(CPixelDataView),sz,&m_CC);
	//////m_wndSplitter.RecalcLayout();
	////////m_wndSplitter.RedrawWindow();

	if(m_PresentationMode==PIXEL_MODE)
		return;
	m_PresentationMode=PIXEL_MODE;
	ShowGraphViewORGraph_DataSplitView();

	GetActiveDocument()->UpdateAllViews(NULL);
}

void CMainFrame::OnUpdateSelectPixelMode(CCmdUI* pCmdUI)
{
	if(m_PresentationMode==PIXEL_MODE)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

// Event Handler for WL Mode Selection Event (Presents the Views w.r.t WL)
void CMainFrame::OnSelectWLMode(void)
{
	////m_PresentationMode=WAVELENGTH_MODE;
	////CRect rect;
	////GetClientRect(&rect);

	////m_wndSplitter.DeleteView(0,0);
	////CSize sz;
	////if(m_bShowViewData == false)
	////{
	////	sz.cx = rect.Width();
	////	sz.cy = rect.Height();
	////}
	////else
	////{
	////	sz.cx = rect.Width()/2;
	////	sz.cy = rect.Height();
	////}
	////m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(CWLSpectrumView),sz,&m_CC);
	//////m_wndSplitter.RecalcLayout();
	//////m_wndSplitter.RedrawWindow();

	////m_wndSplitter.DeleteView(0,1);
	//////CSize sz;
	////if(m_bShowViewData == false)
	////{
	////	sz.cx = rect.Width();
	////	sz.cy = rect.Height();
	////}
	////else
	////{
	////	sz.cx = 0;
	////	sz.cy = rect.Height();
	////}
	////m_wndSplitter.CreateView(0,1,RUNTIME_CLASS(CWLDataView),sz,&m_CC);
	////
	////m_wndSplitter.RecalcLayout();
	//////m_wndSplitter.RedrawWindow();


	if(m_PresentationMode==WAVELENGTH_MODE)
		return;
	m_PresentationMode=WAVELENGTH_MODE;
	ShowGraphViewORGraph_DataSplitView();

	GetActiveDocument()->UpdateAllViews(NULL);
	//m_wndSplitter.RecalcLayout();
	//RecalcLayout();
	//m_wndSplitter.Invalidate();
	//Invalidate();
	//OnGetviewGetallviews();
	//int i;
	RedrawGraphCtrl();
}

void CMainFrame::OnUpdateSelectWLMode(CCmdUI* pCmdUI)
{
	if(m_PresentationMode==WAVELENGTH_MODE)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}



// Update the  Properties Pane with iniial values present in the CapturePixels Data object
LRESULT CMainFrame::OnUpdateProperties(WPARAM wp, LPARAM lp)
{
	m_wndPropertiesPane.m_PropertiesPaneDlg.InitProperties();
	return LRESULT();
}

// //USed for Entering the Csalibration data
void CMainFrame::OnCalibration(void)
{
	if(m_dlgCalibration.m_hWnd==NULL)
		m_dlgCalibration.Create(IDD_CALIBDATADLG);
	CArraySpectrumDoc* pDoc=NULL;
	pDoc = (CArraySpectrumDoc*)GetActiveDocument();
	if(pDoc != NULL)
		m_dlgCalibration.m_pDoc = pDoc;

	m_dlgCalibration.ShowWindow(SW_SHOW);
}
void CMainFrame::OnUpdateCalibration(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnConnectOrDisconnect(void)
{

	CArraySpectrumDoc* pDoc = NULL;
	pDoc=(CArraySpectrumDoc*)GetActiveDocument();
	if(pDoc == NULL)
		return;
	BOOL bStat = FALSE;
	LONG lDevCount = 0;
	BOOL bValue = TRUE;
	INT nDevID = 0;


	CString strResource;
	BOOL bNameValid;
	if (m_bConnected == TRUE)
	{
		//Disconnect
		// Set LED mode
		bValue = FALSE;
		bStat = DcIc_SetLEDMode(pDoc->m_objCapturePixelBuff.nDevID, bValue);
		bStat = DcIc_Abort(pDoc->m_objCapturePixelBuff.nDevID);
		bStat = DcIc_Disconnect(pDoc->m_objCapturePixelBuff.nDevID);
		bStat = DcIc_Terminate();
		m_bConnected = FALSE;

		/*if (pDoc->m_objSerialComm.Close() == FALSE)
			AfxMessageBox(_T("Failed to Close the Communication Port"));*/
			//change the text to connect
		bNameValid = strResource.LoadString(ID_FILE_CONNECT);
		if (bNameValid)
			pBtnConnectOrDisconnect->SetText(strResource);
	}
	else
	{
		//Show the PortSetting Dialog
		CCommPortSettings dlgCommPortSettings;
		/*dlgCommPortSettings.Create(IDD_COMMPORTSETTINGS);
		dlgCommPortSettings.ShowWindow(SW_SHOW);*/
		dlgCommPortSettings.DoModal();


		/*pDoc->m_strSelectedCommPortName = dlgCommPortSettings.GetSelectedCommPortName();

		if(pDoc->m_strSelectedCommPortName.IsEmpty() == FALSE)
		{
			if(pDoc->m_objSerialComm.Open(pDoc->m_strSelectedCommPortName) == FALSE)
			{
				AfxMessageBox(_T("Failed to Open the Communication Port"));
				m_bConnected = FALSE;
				pDoc->m_strSelectedCommPortName = _T("");
			}
			else
			{
				m_bConnected = TRUE;
				//pDoc->m_objSerialComm.Close();//to use the serial port in the background thread we have close the port temporiarly.
				//change the text to disconnect
				bNameValid = strResource.LoadString(IDS_FILE_DISCONNECT);
				if(bNameValid)
					pBtnConnectOrDisconnect->SetText(strResource);
			}
		}*/
		// Init library and create device information array.
		
		bStat = DcIc_Initialize();		// Initialize library(DLL).
		if (bStat != TRUE)
		{
			// Initialize is faled
			return;
		}
		bStat = DcIc_CreateDeviceInfo(&lDevCount);	// Create device information table.
		if (bStat != TRUE)
		{
			// Exit this function
			DcIc_Terminate();	// Terminate process of library.
			return;
		}

		// Connect hardware
		UINT unTargetDevIdx = 0;
		pDoc->m_objCapturePixelBuff.nDevID = DcIc_Connect(unTargetDevIdx);
		if (pDoc->m_objCapturePixelBuff.nDevID <= 0)
		{
			// Connection is failed -> Exit this function
			DcIc_Terminate();	// Terminate process of library.
			return;
		}

		// Send ABORT command, when if hardware is BUSY.
		bStat = DcIc_Abort(pDoc->m_objCapturePixelBuff.nDevID);
		if (bStat == FALSE)
		{
			// Send "STOP" is failed -> Exit this function
			DcIc_Disconnect(pDoc->m_objCapturePixelBuff.nDevID);
			DcIc_Terminate();	// Terminate process of library.
			return;
		}

		// Set LED mode
		bValue = TRUE;
		bStat = DcIc_SetLEDMode(pDoc->m_objCapturePixelBuff.nDevID, bValue);
		if (bStat == FALSE)
		{
			// Change LED condition is failed -> Exit this function
			DcIc_Disconnect(pDoc->m_objCapturePixelBuff.nDevID);
			DcIc_Terminate();	// Terminate process of library.
			return;
		}
		m_bConnected = TRUE;
		bNameValid = strResource.LoadString(IDS_FILE_DISCONNECT);
		if (bNameValid)
			pBtnConnectOrDisconnect->SetText(strResource);
	}
}


void CMainFrame::OnUpdateConnectOrDisconnect(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
}


void CMainFrame::OnFileExportPixelData()
{
	//Test Code for importing the the Pixel data from a CSV
	//CArraySpectrumDoc* pDoc=NULL;
	//pDoc=(CArraySpectrumDoc*)GetActiveDocument();

	//pDoc->m_objCapturePixelBuff.ClearPixelBuffer();
	//pDoc->m_objCapturePixelBuff.m_pBuffPixelData = new WORD[MAX_PIXEL_DATA_COUNT_PER_LINE];

	//FILE* fp= fopen("C:\\Documents and Settings\\srinivasn\\Desktop\\data.csv","r");
	//int d,i=0;
	//pDoc->m_objCapturePixelBuff.m_nLineCount=1;
	//pDoc->m_objCapturePixelBuff.m_bShowAvg=FALSE;
	//pDoc->m_objCapturePixelBuff.m_bShowSD=FALSE;
	//pDoc->m_objCapturePixelBuff.m_bShowRSD=FALSE;


	//while(!feof(fp))
	//{
	//	fscanf(fp,"%d",&d);
	//	pDoc->m_objCapturePixelBuff.m_pBuffPixelData[i]=d;
	//	i++;

	//}
	//fclose(fp);
	//pDoc->m_objCapturePixelBuff.PreparePixelLineBuffFromSnapShot();
	//pDoc->UpdateAllViews(NULL);
	//return;

	CArraySpectrumDoc* pDoc=NULL;
	pDoc=(CArraySpectrumDoc*)GetActiveDocument();

	if(pDoc->m_objCapturePixelBuff.ISEmpty())
		AfxMessageBox(_T("No Captured Pixel Data is Available"));

	CFileDialog objFileDlg(FALSE,_T("csv"),_T("Untitled"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("Pixel Data File(*.csv)|*.csv||"));
	if(objFileDlg.DoModal()==IDOK)
	{
		CString strFullPathName;
		strFullPathName=objFileDlg.GetPathName();


		pDoc->m_objCapturePixelBuff.SaveDataToCSVFile(strFullPathName,0);//Svae the Pixel Data
	}
}

void CMainFrame::OnFileExportWLData()
{
	CArraySpectrumDoc* pDoc=NULL;
	pDoc=(CArraySpectrumDoc*)GetActiveDocument();

	if(pDoc->m_objCapturePixelBuff.ISEmpty())
		AfxMessageBox(_T("No Captured Pixel Data is Available"));

	CFileDialog objFileDlg(FALSE,_T("csv"),_T("Untitled"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("WaveLength Data File(*.csv)|*.csv||"));
	if(objFileDlg.DoModal()==IDOK)
	{
		CString strFullPathName;
		strFullPathName=objFileDlg.GetPathName();


		pDoc->m_objCapturePixelBuff.SaveDataToCSVFile(strFullPathName,1);//Svae the WL Data
	}
}

// This Notification is  raised when Pixel acquiring is FAiled (can be due to the Instrument failure)
LRESULT CMainFrame::OnNotifyCaptureFailed(WPARAM wp , LPARAM lp)
{
	m_bStartCapturing = FALSE;
	m_bSnapShot = FALSE;
	CArraySpectrumDoc* pDoc = NULL;
	pDoc = (CArraySpectrumDoc*)GetActiveDocument();
	pDoc->UpdateAllViews(NULL);
	AfxMessageBox(_T("Data Acquisition Failed..\n\nPlease Check the Connection and Retry."));
	return LRESULT();
}

//iterate all views and call Invalidate. 
void CMainFrame::OnGetviewGetallviews() 
{
	CDocTemplate *pTempl = NULL;
	CDocument *pDoc = NULL;
	CView *pView = NULL;

	POSITION posT = theApp.GetFirstDocTemplatePosition();

	while(posT) 
	{
		pTempl = theApp.GetNextDocTemplate(posT);

		POSITION posD = pTempl->GetFirstDocPosition();
		while(posD) 
		{
			pDoc = pTempl->GetNextDoc(posD);

			POSITION posV = pDoc->GetFirstViewPosition();
			while(posV) 
			{
				pView = pDoc->GetNextView(posV);
				pView->Invalidate();
			} 
		}
	}
}


void CMainFrame::OnAbout(void)
{
	//CArraySpectrumDoc* pDoc=NULL;
	//pDoc=(CArraySpectrumDoc*)GetActiveDocument();
	//m_ptrSettingsDlg->m_pDoc = pDoc;
	/*m_ptrSettingsDlg->ApplyDocDataIntoCtrls();
	m_ptrSettingsDlg->ShowWindow(SW_SHOWNORMAL);*/
	//m_ptrSettingsDlg->OnBnClickedBtnApply();
}

//void CMainFrame::UpdateView()
//{
//	pDoc->UpdateAllViews(NULL);
//}

void CMainFrame::UpdateSettingsDlg()
{
	if((m_ptrSettingsDlg != NULL) && (m_ptrSettingsDlg->m_hWnd != NULL))
	{
		if(m_ptrSettingsDlg->IsWindowVisible() == TRUE)
		{
			//m_ptrSettingsDlg->UpdateSettings();
			//::PostMessage(m_ptrSettingsDlg->m_hWnd, WM_APPLY_SETTINGS,0,0);
			::SendMessage(m_ptrSettingsDlg->m_hWnd, WM_APPLY_SETTINGS,0,0);
		}
	}
}

void CMainFrame::OnDisplaySettings(void)
{
	if(m_ptrSettingsDlg->IsWindowVisible() == false)
	{
		CArraySpectrumDoc* pDoc=NULL;
		//CMainFrame* pWnd=NULL;
		//pWnd=(CMainFrame*)GetParent();
		pDoc=(CArraySpectrumDoc*)GetActiveDocument();

		if(pDoc != NULL)
		{
			m_ptrSettingsDlg->m_pDoc = pDoc;
			//m_ptrSettingsDlg->ApplyDocDataIntoCtrls();
		}
		//m_ptrSettingsDlg->ApplyDocDataIntoCtrls();
		m_ptrSettingsDlg->ShowWindow(SW_SHOWNORMAL);
		//::PostMessage(m_ptrSettingsDlg->m_hWnd,WM_APPLY_SETTINGS,0,0);
		::SendMessage(m_ptrSettingsDlg->m_hWnd,WM_APPLY_SETTINGS,0,0);
	}
}
void CMainFrame::OnLaserSettings(void)
{

}

void CMainFrame::OnViewDataShow(void)
{
	if(m_bShowViewData == false)
	{
		pBtnViewData->SetImageIndex(14,TRUE);
		pBtnViewData->SetText(_T("Hide"));
		m_bShowViewData = true;
	}
	else
	{
		pBtnViewData->SetImageIndex(13,TRUE);
		pBtnViewData->SetText(_T("Show"));
		m_bShowViewData = false;
	}


	//////////CRect rect;
	////////////GetClientRect(&rect);
	//////////m_wndSplitter.GetClientRect(&rect);
	//////////CSize sz;
	//////////	
	//////////CDocTemplate *pTempl = NULL;
	//////////CDocument *pDoc = NULL;
	//////////CView *pView = NULL;

	//////////if(m_bShowViewData == false)
	//////////{
	//////////	sz.cx = rect.Width();
	//////////	sz.cy = rect.Height();
	//////////

	//////////	POSITION posT = theApp.GetFirstDocTemplatePosition();

	//////////	while(posT) 
	//////////	{
	//////////		pTempl = theApp.GetNextDocTemplate(posT);

	//////////		POSITION posD = pTempl->GetFirstDocPosition();
	//////////		while(posD) 
	//////////		{
	//////////			pDoc = pTempl->GetNextDoc(posD);

	//////////			POSITION posV = pDoc->GetFirstViewPosition();
	//////////			while(posV) 
	//////////			{
	//////////				pView = pDoc->GetNextView(posV);
	//////////				if(pView->IsKindOf(RUNTIME_CLASS(CDataView)) == true)
	//////////				{
	//////////					pView->MoveWindow(0,0,0,sz.cy);
	//////////					CRect rc;
	//////////					pView->GetWindowRect(&rc);
	//////////					pView->RedrawWindow(&rc);
	//////////					//break;
	//////////				}
	//////////				else if(pView->IsKindOf(RUNTIME_CLASS(CBasePlotView)) == true)
	//////////				{
	//////////					pView->MoveWindow(0,0,sz.cx,sz.cy);
	//////////					CRect rc;
	//////////					pView->GetWindowRect(&rc);
	//////////					pView->RedrawWindow(&rc);
	//////////				}
	//////////				//pView->Invalidate();
	//////////			} 
	//////////		}
	//////////	}
	//////////}
	//////////else
	//////////{
	//////////	sz.cx = rect.Width();
	//////////	sz.cy = rect.Height();
	//////////

	//////////	POSITION posT = theApp.GetFirstDocTemplatePosition();

	//////////	while(posT) 
	//////////	{
	//////////		pTempl = theApp.GetNextDocTemplate(posT);

	//////////		POSITION posD = pTempl->GetFirstDocPosition();
	//////////		while(posD) 
	//////////		{
	//////////			pDoc = pTempl->GetNextDoc(posD);

	//////////			POSITION posV = pDoc->GetFirstViewPosition();
	//////////			while(posV) 
	//////////			{
	//////////				pView = pDoc->GetNextView(posV);
	//////////				if(pView->IsKindOf(RUNTIME_CLASS(CDataView)) == true)
	//////////				{
	//////////					pView->MoveWindow((rect.left+(sz.cx/2)),0,sz.cx/2,sz.cy);
	//////////					CRect rc;
	//////////					pView->GetWindowRect(&rc);
	//////////					pView->RedrawWindow(&rc);
	//////////					//break;
	//////////				}
	//////////				else if(pView->IsKindOf(RUNTIME_CLASS(CBasePlotView)) == true)
	//////////				{
	//////////					pView->MoveWindow(0,0,sz.cx/2,sz.cy);
	//////////					CRect rc;
	//////////					pView->GetWindowRect(&rc);
	//////////					pView->RedrawWindow(&rc);
	//////////				}
	//////////				//pView->Invalidate();
	//////////			} 
	//////////		}
	//////////	}
	//////////}
	//////////
	////////////CArraySpectrumDoc* pDoc=NULL;
	////////////pDoc=(CArraySpectrumDoc*)GetActiveDocument();
	////////////m_wndSplitter.RecalcLayout();
	//////////pDoc->UpdateAllViews(NULL);


	ShowGraphViewORGraph_DataSplitView();
	RedrawGraphCtrl();

}


void CMainFrame::ShowGraphViewORGraph_DataSplitView()
{
	CDocument *pDoc =GetActiveDocument();
	pDoc->m_bAutoDelete=FALSE;
	CRect rect;
	GetClientRect(&rect);

	if(m_bShowViewData ==TRUE)//Show Graph and Data Grid Views in Splitter
	{
		//CView * pv=GetActiveView();

		POSITION pos=pDoc->GetFirstViewPosition();
		while(pos!=NULL)
		{
			CView * pv= pDoc->GetNextView(pos);
			pDoc->RemoveView(pv);

			// delete pv;
		}
		GetDlgItem(AFX_IDW_PANE_FIRST)->DestroyWindow();
		SetActiveView(NULL);
		//RecalcLayout();
		if(!m_wndSplitter.CreateStatic(this,1,2))
		{
			return ;
		}


		CCreateContext cc;
		cc.m_pCurrentDoc=NULL;//GetActiveDocument();
		cc.m_pCurrentFrame=NULL;//this;
		cc.m_pNewDocTemplate=NULL;
		cc.m_pLastView=NULL;
		cc.m_pNewViewClass=RUNTIME_CLASS(CArraySpectrumView);

		if(PIXEL_MODE == m_PresentationMode)
		{
			//CArraySpectrumView
			if ( !m_wndSplitter.CreateView( 0, 0,RUNTIME_CLASS(CArraySpectrumView),CSize(rect.Width()/2, rect.Height()), &cc)) 
			{ 
				AfxMessageBox(_T("Splitter Creation Failed"));
				return; 
			}

			if ( !m_wndSplitter.CreateView( 0, 1,RUNTIME_CLASS(CPixelDataView),CSize(rect.Width()/2, rect.Height()), &cc)) 
			{ 
				AfxMessageBox(_T("Splitter Creation Failed"));
				return; 
			}
		}
		if(WAVELENGTH_MODE == m_PresentationMode)
		{
			//CArraySpectrumView
			if ( !m_wndSplitter.CreateView( 0, 0,RUNTIME_CLASS(CWLSpectrumView),CSize(rect.Width()/2, rect.Height()), &cc)) 
			{ 
				AfxMessageBox(_T("Splitter Creation Failed"));
				return; 
			}

			if ( !m_wndSplitter.CreateView( 0, 1,RUNTIME_CLASS(CWLDataView),CSize(rect.Width()/2, rect.Height()), &cc)) 
			{ 
				AfxMessageBox(_T("Splitter Creation Failed"));
				return; 
			}
		}
		pDoc->AddView((CView*)m_wndSplitter.GetPane(0,0));
		pDoc->AddView((CView*)m_wndSplitter.GetPane(0,1));
		this->SetActiveView((CView*)m_wndSplitter.GetPane(0,0));

		RecalcLayout();
		pDoc->UpdateAllViews(NULL);

	}
	else //Show only Graph View
	{
		/*m_wndSplitter.DeleteView(0,0);
		m_wndSplitter.SetActivePane(0,0,NULL);
		m_wndSplitter.DeleteView(0,1);*/
		POSITION pos=pDoc->GetFirstViewPosition();
		while(pos!=NULL)
		{
			CView * pv= pDoc->GetNextView(pos);
			pDoc->RemoveView(pv);
		}

		//m_wndSplitter.DestroyWindow();
		GetDlgItem(AFX_IDW_PANE_FIRST)->DestroyWindow();
		SetActiveView(NULL);
		//RecalcLayout();
		CView * pv=NULL;
		if(m_PresentationMode==PIXEL_MODE)
			pv =new CArraySpectrumView();
		else
			pv =new CWLSpectrumView();
		pv->Create(NULL,_T(""),WS_CHILD|WS_VISIBLE,rect,this,AFX_IDW_PANE_FIRST,NULL);
		pDoc->AddView(pv);
		SetActiveView(pv);
		RecalcLayout();
		pDoc->UpdateAllViews(NULL);
	}
}

void CMainFrame::RedrawGraphCtrl()
{
	CDocTemplate *pTempl = NULL;
	CDocument *pDoc = NULL;
	CView *pView = NULL;

	POSITION posT = theApp.GetFirstDocTemplatePosition();

	while(posT) 
	{
		pTempl = theApp.GetNextDocTemplate(posT);
		POSITION posD = pTempl->GetFirstDocPosition();
		while(posD) 
		{
			pDoc = pTempl->GetNextDoc(posD);
			POSITION posV = pDoc->GetFirstViewPosition();
			while(posV) 
			{
				pView = pDoc->GetNextView(posV);
				//pView->Invalidate();
				if(pView->IsKindOf(RUNTIME_CLASS(CBasePlotView)) == TRUE)
				{
					CRect rc;
					((CWLSpectrumView*)pView)->m_objGraphCtrl.GetWindowRect(&rc);
					((CWLSpectrumView*)pView)->m_objGraphCtrl.RedrawWindow(&rc);
					break;
				}
			} 
		}
	}	
}

void CMainFrame::CalculateArea()
{
	CDocTemplate *pTempl = NULL;
	CDocument *pDoc = NULL;
	CView *pView = NULL;

	POSITION posT = theApp.GetFirstDocTemplatePosition();

	while(posT) 
	{
		pTempl = theApp.GetNextDocTemplate(posT);
		POSITION posD = pTempl->GetFirstDocPosition();
		while(posD) 
		{
			pDoc = pTempl->GetNextDoc(posD);
			POSITION posV = pDoc->GetFirstViewPosition();
			while(posV) 
			{
				pView = pDoc->GetNextView(posV);
				//pView->Invalidate();
				if(pView->IsKindOf(RUNTIME_CLASS(CBasePlotView)) == TRUE)
				{
					::SendMessage(pView->m_hWnd,WM_CALCULATE_AREA,0,0);
					break;
				}
			} 
		}
	}
}
void CMainFrame::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	if((m_ptrSettingsDlg != NULL) && (m_ptrSettingsDlg->m_hWnd != NULL))
	{
		CArraySpectrumDoc *pDoc = (CArraySpectrumDoc*)GetActiveDocument();
		if(pDoc != NULL)
		{
			pDoc->SerializeSettingsData(TRUE);
		}
	}
	CFrameWndEx::OnClose();
}
