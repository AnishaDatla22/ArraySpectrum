//#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Author	:	Srinivas N J R
//	Date	:	-
//	File	:	CustomBitmapButton.h
//  Purpose :   This class is used to create a custom button with given bitmaps
//	History	:	This 2.0Ver is updated from 1.0Ver. 
//			    To reduce the no. of bitmap resources used to show different Mode buttons, A new method is added to load the unique
//              Plain button face, button Icon image and caption text and OnDraw methjod is modified to draw all these items accordingly.  
////////////////////////////////////////////////////////////////////////////////////////////////////////


// CCustomBitmapButton
#ifndef _CUSTOMBMPBTN_H
#define _CUSTOMBMPBTN_H
#include "resource.h"
//#include "ToolTip.h"

#define ID_BTN_CLICK_DELAY_TIMER  20202
#define ID_TOOLTIP_TIMER 5000
#define TOOLTIP_DELAY 500
#define DEF_CAPTION_MARGIN 15
#define DEF_LEFT_LOGO_MARGIN 15
#define CENTER_ALIGN_CAPTION 0
#define LEFT_ALIGN_CAPTION 1
#define RIGHT_ALIGN_CAPTION 2

class CCustomBitmapButton : public CButton
{
private:
	BOOL m_bToolTipShown;
	BOOL m_bSizeToContent;
	BOOL m_bToolTip;
	COLORREF m_rgbCaption; 
//	CToolTip * m_pToolTipCtrl;

public:
	BOOL m_bLBTNDown;
	BOOL m_bDrawCaption;
	BOOL m_bDelayedNotification;//set to TRUE, if Delayed Click response is required. by default this is FALSE
	BOOL m_bDelayTimerStarted;
	BOOL m_flag;
	int m_nDelayInterval;
	//m_unNormalBitmapID -> shown in normal state; 
	//m_unDisableBitmapID -> Shown in disable state
	UINT m_unNormalBitmapID,m_unDisableBitmapID, m_unBtnLogoID,m_unClickedBitmapID;
	UINT m_nFlags;
	//<----Ver 2.0
	///Alignment of caption on button. Alignmet - 0-Center,1-Left,2-Right
    DWORD m_dwAlignCaption;
	//UINT m_unBitmapID;
	CRgn m_rgnBmpSize;
	//Text to be shown on bitmap
	CString m_strButtonCaption;
	//font used to write text on the button
	CFont m_font;
	CPoint m_Point;

public:
	//afx_msg LRESULT OnNcHitTest(CPoint point);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct );
    virtual ~CCustomBitmapButton();


public:	    
	//Constructor
	CCustomBitmapButton();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd*);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnEnable(BOOL bEnable );
	
	//afx_msg BOOL LoadBmp(UINT unBmpID,BOOL bTextOnBmp);
	afx_msg BOOL LoadBmp(UINT unNormalBmpID,UINT unDisableBmpID,BOOL bTextOnBmp);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	void OnTimer(UINT id);
	///Sets Delays,button click event is sent to
	///to parent only after the specified dealy.
	void SetBtnClickDelay(int nDelay=0);
	///Set alignment of caption on button. Caption Alignmet - 0-Center,1-Left,2-Right
	void SetCaptionAlignment(DWORD dwAlign);
	//----Ver 2.0>///////////////////////////////
	void SetToolTip(BOOL bToolTip);
	//Ver 2.0
	//if bFlag=TRUE, size the button to the size of the Background Bitmap
	void SetSizeToContent(BOOL bFlag=TRUE);
	void SetCaptionColor(COLORREF clrText);
	BOOL ToggleBmpClicked(UINT unBmpID); ////25-01-09
	BOOL ToggleBmp(UINT unBmpID); //This function changes the existing Normal bitmap with the new one. 
	//this method is newly added in 2.0 Ver
	//Load the unique button face bitmap, button Icon image and caption text
	BOOL LoadBmp(UINT nBmpButtonFaceID, UINT nBmpBtnIcon, CString strCaption,COLORREF clrCaptionText, DWORD dwCaptionAlignment=CENTER_ALIGN_CAPTION);
	

	DECLARE_MESSAGE_MAP()
};
#endif


