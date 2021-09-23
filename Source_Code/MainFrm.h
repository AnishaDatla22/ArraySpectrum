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

// MainFrm.h : interface of the CMainFrame class
//

#pragma once

#include "PropertiesPane.h"
#include "ArraySpectrumView.h"
#include "calibdatadlg.h"
#include "SettingsDlg.h"
#include "CustomSplitterWnd.h"

class CMainFrame : public CFrameWndEx
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)
protected:
	//CSplitterWnd m_wndSplitter;
	CCustomSplitterWnd m_wndSplitter;
	
// Attributes
public:
  enum VIEW_MODE {PIXEL_MODE,WAVELENGTH_MODE};

public:
	///
	CSettingsDlg* m_ptrSettingsDlg;
    
	// Operations
public:
    VIEW_MODE m_PresentationMode;
	CCreateContext m_CC;
// Operations
public:
     CMFCRibbonButton* pBtnCapture;
	 CMFCRibbonPanel* pPanelCapture;
// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
   CPropertiesPane  m_wndPropertiesPane;
protected:  // control bar embedded members
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;
	
	CCalibDataDlg m_dlgCalibration;
	///
	CMFCRibbonButton* pBtnViewData;
public:
    BOOL m_bStartCapturing;
	//TRUE, if the Snap shot process is in progress
	BOOL m_bSnapShot;	
	///
	int m_nNoOfScanCompl;
	//virtual void SaveData(char* pFileName, WORD* pDataBuff, int nWidth, int nHeight, int nFrameCnt, int nDataIdx);

public:
	///
	BOOL m_bShowViewData;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	/*afx_msg void OnFilePrint();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);*/
	afx_msg void OnStartCapture();
	DECLARE_MESSAGE_MAP()

	void InitializeRibbon();
	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	// User defiened Message Handler for Clear All Views notification raised before capturing the Snap shot
	LRESULT OnNotifyClearAllViews(WPARAM wp, LPARAM lp);
	// The message handler for the notification receivied when the Snap Shot capturing is completed
	LRESULT OnNotifySnapShotCompleted(WPARAM wp, LPARAM lp);
	void OnUpdateStartCapture(CCmdUI* pCmdUI);
	void OnUpdateStopCapture(CCmdUI* pCmdUI);
	// Stop Continuous  Frames Capturing
	void OnStopCapture(void);
	void OnUpdateSnapShot(CCmdUI* pCmdUI);
	// Capture a single Frame
	void OnSnapShot(void);
	// Event Handler for Pixel Mode Selection event 
	void OnSelectPixelMode(void);
	void OnUpdateSelectPixelMode(CCmdUI* pCmdUI);
	// Event Handler for WL Mode Selection Event (Presents the Views w.r.t WL)
	void OnSelectWLMode(void);
	void OnUpdateSelectWLMode(CCmdUI* pCmdUI);
	
	// Update the  Properties Pane with iniial values present in the CapturePixels Data object
	LRESULT OnUpdateProperties(WPARAM wp, LPARAM lp);
	// //USed for Entering the Csalibration data
	void OnCalibration(void);
	///
	void OnUpdateCalibration(CCmdUI* pCmdUI);
	///
	void OnFileExportPixelData(void);
	///
	void OnFileExportWLData(void);

	// This Notification is  raised when Pixel acquiring is FAiled (can be due to the Instrument failure)
	LRESULT OnNotifyCaptureFailed(WPARAM wp , LPARAM lp);
	
	///
	void OnConect(void);
	///
	bool m_bConnected;
	///
	void OnUpdateConnectOrDisconnect(CCmdUI* pCmdUI);
	///
	void OnConnectOrDisconnect();
	///
	CMFCRibbonButton* pBtnConnectOrDisconnect; 
	///iterate all views and call Invalidate.
	void OnGetviewGetallviews();
	///
	void OnAbout(void);
	///
	void UpdateSettingsDlg();
	///
	void OnDisplaySettings(void);
	///
	void OnViewDataShow(void);
	///
	void OnLaserSettings(void);
	/// <summary>
	/// 
	/// </summary>
	/// <param name=""></param>
	void ShowGraphViewORGraph_DataSplitView(void);
	///
	void RedrawGraphCtrl();
	///
	void CalculateArea();
	afx_msg void OnClose();
};


