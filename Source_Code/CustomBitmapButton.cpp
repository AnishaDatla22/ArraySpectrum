// CustomBitmapButton.cpp : implementation file
//

#include "stdafx.h"

#include "CustomBitmapButton.h"
#include "constants.h"



// CCustomBitmapButton

CCustomBitmapButton::CCustomBitmapButton()
{
	//Default Text Color is White 
	m_rgbCaption= RGB_BUTTON_TEXT_COLOR;
	m_bDrawCaption = FALSE;
	m_unDisableBitmapID=m_unNormalBitmapID=0; //25-01-09
	m_bLBTNDown=FALSE;
	m_strButtonCaption=_T("");
	m_bDelayedNotification=FALSE; //No delay in Click notification
	m_nDelayInterval=0;
	m_bDelayTimerStarted=FALSE;
	m_dwAlignCaption=CENTER_ALIGN_CAPTION;
	m_bToolTip = FALSE;
	m_bToolTipShown = FALSE;
	m_unBtnLogoID=-1;
	m_bSizeToContent=FALSE;

}

CCustomBitmapButton::~CCustomBitmapButton()
{

}
BEGIN_MESSAGE_MAP(CCustomBitmapButton, CButton)

	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()

END_MESSAGE_MAP()


//Ver 2.0
//if bFlag=TRUE, size the button to the size of the Background Bitmap
void CCustomBitmapButton::SetSizeToContent(BOOL bFlag)
{
  m_bSizeToContent=bFlag;
  Invalidate();
}

void CCustomBitmapButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	//attaching handle of button dc to our dc
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);
	//get rect of button
	CRect rc =lpDrawItemStruct->rcItem;
	//creating secondary dc
	CDC memDC,memDCLogo;	
	memDC.CreateCompatibleDC(&dc);
	CBitmap bmpBtnFace,bmpLogo, *pOldBmpLogo;
	BITMAP bmFace,bmLogo;
	//getting handle of bitmap using its id
    if(m_unBtnLogoID != -1)
	{
		bmpLogo.LoadBitmap(m_unBtnLogoID);
		bmpLogo.GetBitmap(&bmLogo);
		memDCLogo.CreateCompatibleDC(&dc);
	    pOldBmpLogo=memDCLogo.SelectObject(&bmpLogo);
	}
	if(bmpBtnFace.LoadBitmap(m_unNormalBitmapID))
	{
		//loading bitmap into secondary dc
		CBitmap *oldbmpBtnFace	=	memDC.SelectObject(&bmpBtnFace);
		//Getting info of bitmap
		bmpBtnFace.GetBitmap(&bmFace);
		//size to the bkg bitmap content 
		if(m_bSizeToContent)
		{
			CRect rc;
			//GetClientRect(&rc);
			this->GetWindowRect(&rc);	
			GetParent()->ScreenToClient(&rc);
			this->MoveWindow(rc.left,rc.top,bmFace.bmWidth,bmFace.bmHeight,FALSE);
		}
		if(!m_bLBTNDown)		
		{
			//dc.DrawFrameControl(&lpDrawItemStruct->rcItem,DFC_BUTTON,DFCS_BUTTONPUSH);
			dc.StretchBlt(0,0,rc.Width(),rc.Height(),&memDC,0,0,bmFace.bmWidth,bmFace.bmHeight,SRCCOPY);
			if(m_unBtnLogoID !=-1)
			{
				int nVertMargin=(rc.Height()-bmLogo.bmHeight)/2;
				int nLeftMargin = DEF_LEFT_LOGO_MARGIN;
				::TransparentBlt(dc.m_hDC,DEF_LEFT_LOGO_MARGIN,nVertMargin, bmLogo.bmWidth,bmLogo.bmHeight,memDCLogo.m_hDC,0,0,bmLogo.bmWidth,bmLogo.bmHeight,memDCLogo.GetPixel(0,0));
			}
		}
		else 
		{
		   const int iDiff = 2; 
		   COLORREF rgbTranperantBkg=memDC.GetPixel(0,0);

		   dc.FillSolidRect(&rc,rgbTranperantBkg);
			::StretchBlt(dc.m_hDC,iDiff,iDiff, rc.Width()-(2*iDiff), rc.Height()-(2*iDiff),memDC.m_hDC,0,0,bmFace.bmWidth,bmFace.bmHeight,SRCCOPY);
		  // dc.DrawFrameControl(&lpDrawItemStruct->rcItem,DFC_BUTTON,DFCS_CHECKED);
		   if(m_unBtnLogoID !=-1)
			{
				int nVertMargin=(rc.Height()-(2*iDiff)-bmLogo.bmHeight)/2;
				int nLeftMargin = DEF_LEFT_LOGO_MARGIN;
				::TransparentBlt(dc.m_hDC,DEF_LEFT_LOGO_MARGIN,nVertMargin, bmLogo.bmWidth,bmLogo.bmHeight,memDCLogo.m_hDC,0,0,bmLogo.bmWidth,bmLogo.bmHeight,memDCLogo.GetPixel(0,0));
			}
		}

		memDC.SelectObject(oldbmpBtnFace);
		memDC.DeleteDC();
		if(m_unBtnLogoID!=-1)
		{
		   memDCLogo.SelectObject(pOldBmpLogo);
		   memDCLogo.DeleteDC();
		}
	}

	//Draw the Text on the Button	

	if(m_bDrawCaption)
	{	
		dc.SetBkMode(TRANSPARENT);
		CFont font;
		font.CreateFont(FONT_HEIGHT,FONT_WIDTH,0,0,FW_BOLD,0,0,0,0,0,0,1,0,TAHOMA_FONT);
		CFont *oldFont	=	dc.SelectObject(&font);	
		CString str;
		GetWindowText(str);
		dc.GetTextExtent(str);
		dc.SetTextColor(m_rgbCaption);
		if(m_dwAlignCaption==CENTER_ALIGN_CAPTION) //center Align
		{
			//dc.DrawText(str,rc,DT_VCENTER|DT_CENTER|DT_WORDBREAK);
			dc.DrawText(str,rc,DT_VCENTER|DT_CENTER|DT_WORDBREAK);
		}
		else if(m_dwAlignCaption==LEFT_ALIGN_CAPTION)//Left Align
		{
            CRect rc1=rc;
			rc1.left+=DEF_CAPTION_MARGIN;
			dc.DrawText(str,rc1,DT_VCENTER|DT_LEFT|DT_WORDBREAK);
		}
		else if(m_dwAlignCaption==RIGHT_ALIGN_CAPTION)//Right Align
		{
            CRect rc1=rc;
			rc1.right-=DEF_CAPTION_MARGIN;
			dc.DrawText(str,rc1,DT_RIGHT|DT_WORDBREAK);
		}

		dc.SelectObject(oldFont);	
	}	
	dc.Detach();
}
/*************************************************
PURPOSE				 : It will store the bitmap for the button and 
//					   this bitmap will be set to the button in 'OnPaint'
INPUTS				 : uBmpID		-	Bitmap ID that is to be placed on the Button
bTextonbmp	-	Flag that specifies weather the text of the button has to be write
on the Bitmap with the specified font or not.
ASSUMES				 : 
RETURNS				 : 
EFFECTS				 : 
AUTHOR				 : Akshaya
LAST MODIFIED DATE   : 
MODIFICATION HISTORY : 
RevNo  Date        Author    Brief Description
---------  --------       ----------    ------------------------
N      dd-mm-yy    xxx
*************************************************/
BOOL CCustomBitmapButton::LoadBmp(UINT unNormalBmpID,UINT unDisableBmpID,BOOL bTextOnBmp)
{

	//vaasu  ////25-01-09

	if (unNormalBmpID!=0)
	{
		m_unNormalBitmapID = unNormalBmpID;
		m_unDisableBitmapID=unNormalBmpID;
	}
	if(unDisableBmpID !=0)
		m_unDisableBitmapID=unDisableBmpID;

	m_bDrawCaption = bTextOnBmp;

	if(m_unNormalBitmapID==0)
		return FALSE;
	return TRUE;
}

/*************************************************
PURPOSE				 : Load the unique button face bitmap, button Icon image and caption text
//					   these are rendered on the button in 'OnPaint'
INPUTS:				 
nBmpButtonFaceID		-	Bitmap ID that is to be drawn as the Buton Face
nBmpBtnIcon				-	The Button Logo bmp used to show on the Left side of the Button
strCaption				-   The caption of the Button to be drawn
clrCaptionText			-   The Color the Caption Text
ASSUMES				 : 
RETURNS				 : 
EFFECTS				 : 
AUTHOR				 : 
LAST MODIFIED DATE   : 
MODIFICATION HISTORY : added in Ver 2.0
RevNo  Date        Author    Brief Description
---------  --------       ----------    ------------------------
N      dd-mm-yy    xxx
*************************************************/
BOOL CCustomBitmapButton::LoadBmp(UINT nBmpButtonFaceID, UINT nBmpBtnIcon, CString strCaption, COLORREF clrCaptionText, DWORD dwCaptionAlignment)
{
  
		m_unNormalBitmapID = nBmpButtonFaceID;
		m_unDisableBitmapID=nBmpButtonFaceID;
		//m_strButtonCaption=strCaption;
		SetWindowText(strCaption);
		

		m_unBtnLogoID=nBmpBtnIcon;
		m_rgbCaption=clrCaptionText;
		m_bDrawCaption=TRUE;
		m_dwAlignCaption=dwCaptionAlignment;
		return TRUE;
	
}

BOOL CCustomBitmapButton::ToggleBmp(UINT unBmpID) ////25-01-09
{
	m_unNormalBitmapID=unBmpID;
	Invalidate();
	return TRUE;
}


void CCustomBitmapButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	/*if(m_bToolTip)
	{
		m_pToolTipCtrl = new CToolTip;
		if(!m_pToolTipCtrl->m_hWnd)
		{
			m_pToolTipCtrl->Create(NULL,_T("ToolTip window"),WS_OVERLAPPED|WS_CHILD|WS_BORDER|WS_VISIBLE,CRect(0,0,0,0),this->GetParent(),1000);
			SetTimer(ID_TOOLTIP_TIMER,TOOLTIP_DELAY,0);
		}
	}*/
	if(m_bLBTNDown==TRUE)
		return;

	SetCapture();	
	m_bLBTNDown=TRUE;
	CButton::OnLButtonDown(nFlags, point);

}

void CCustomBitmapButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	/*if(m_bToolTip)
	{
		KillTimer(ID_TOOLTIP_TIMER);
		if(IsWindow(m_pToolTipCtrl->m_hWnd))
		{
			delete m_pToolTipCtrl;
		}
		if(m_bToolTipShown)
		{
			ReleaseCapture();
			m_bLBTNDown=FALSE;
			m_bToolTipShown = FALSE;
			CButton::OnLButtonUp(nFlags, point);
			Invalidate();
			return;
		}

	}*/

	if(m_bDelayTimerStarted)
		return;
	m_nFlags=nFlags;
	m_Point=point;
	if(m_bDelayedNotification)
	{
		SetTimer(ID_BTN_CLICK_DELAY_TIMER,m_nDelayInterval,0);
		m_bDelayTimerStarted=TRUE;
	}
	else
	{
		m_bDelayTimerStarted=FALSE;

		m_bLBTNDown=FALSE;		
		CButton::OnLButtonUp(nFlags, point);	
		ReleaseCapture();
		if(IsWindow(this->m_hWnd))
			Invalidate();
	}

}

void CCustomBitmapButton::OnTimer(UINT nIDTimer)
{
	//if(nIDTimer == ID_TOOLTIP_TIMER)
	//{
	//	KillTimer(ID_TOOLTIP_TIMER);
	//	CRect rectButton;
	//	GetWindowRect(&rectButton);
	//	CPoint ptToolTip;
	//	//ptToolTip.x = rectButton.left;
	//	ptToolTip.x = rectButton.left-40;
	//	ptToolTip.y = rectButton.Height() + 10;
	//	CString str;
	//	GetWindowText(str);
	//	m_pToolTipCtrl->SetToolTipText(str,ptToolTip);
	//	m_bToolTipShown = TRUE;
	//}

	if(nIDTimer==ID_BTN_CLICK_DELAY_TIMER)
	{
		KillTimer(ID_BTN_CLICK_DELAY_TIMER);
		Invalidate();
		UINT ID=GetDlgCtrlID();
		WPARAM wp=MAKEWPARAM(ID,BN_CLICKED);
		LPARAM lp=(LPARAM)m_hWnd;
		GetParent()->PostMessage(WM_COMMAND,wp,lp);
		//ShowCursor(FALSE);
		ReleaseCapture();
		//ShowCursor(FALSE);
		m_bLBTNDown=FALSE;	
		m_bDelayTimerStarted=FALSE;

	}
}
/*!
* \brief \n
* 	Sets Delays,button click event is sent to parent only after the specified dealy.
* 
* \param nDelay
* Delay after whick click event is to be sent.
* 
* 
* \remarks
* Setting dealy will avoid user to do consective click in no time, user will be allowed
* to click button only after specified dealy.
*/
void CCustomBitmapButton:: SetBtnClickDelay(int nDelay)
{
	if(nDelay>0)
	{
		m_bDelayedNotification=TRUE;
		m_nDelayInterval=nDelay;
	}

}
BOOL CCustomBitmapButton::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}
void CCustomBitmapButton::SetToolTip(BOOL bToolTip)
{
	m_bToolTip = bToolTip;
}


void CCustomBitmapButton::SetCaptionAlignment(DWORD dwAlign)
{
    m_dwAlignCaption=dwAlign;
	if(IsWindow(this->m_hWnd))
		Invalidate();
}
