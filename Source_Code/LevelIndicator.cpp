// LevelIndicator.cpp : implementation file
//

#include "stdafx.h"
#include "ArraySpectrum.h"
#include "LevelIndicator.h"
#include <math.h>

// CLevelIndicator

IMPLEMENT_DYNAMIC(CLevelIndicator, CStatic)

CLevelIndicator::CLevelIndicator()
{
	m_rcdecimalbar = CRect(0,0,25,150);

	m_GrayPen.CreatePen(PS_SOLID,2,RGB(198,195,198));
	m_GrayBr.CreateSolidBrush(RGB(198,195,198));

	m_BluePen.CreatePen(PS_SOLID,2,RGB(255,99,71)/*RGB(255,0,132)*/);
	m_BlueBr.CreateSolidBrush(RGB(255,99,71)/*RGB(0,0,132)*/);

	m_YellowPen.CreatePen(PS_SOLID,2,RGB(255,236,71));
	m_YellowBr.CreateSolidBrush(RGB(255,236,71));


	m_dblprevEnergyDecimalPart = 0;
	m_nRectdecEnergy = 0;
	m_nCurEnergyDecimalPart = 0;
	m_brushBKColor.CreateSolidBrush(RGB(4,123,207));
	m_dblMaxEnergyValue = 50;
	m_dblMinEnergyValue = 0;
	m_nCurEnergyDecimalPart = 55;
	m_nNoOfLevels = 5;
	m_nBaseEnergyVal = 1;
	m_nCurrentLevel = 0;
}

CLevelIndicator::~CLevelIndicator()
{
	m_GrayPen.DeleteObject();
	m_GrayBr.DeleteObject();
	m_BlueBr.DeleteObject();
	m_BluePen.DeleteObject();
	m_YellowPen.DeleteObject();
	m_YellowBr.DeleteObject();
}


BEGIN_MESSAGE_MAP(CLevelIndicator, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CLevelIndicator message handlers


void CLevelIndicator:: PreSubclassWindow( )
{
	ModifyStyle(0,0,SWP_NOSIZE|SWP_NOACTIVATE);
	CRect rcWnd;
	GetWindowRect(&rcWnd);
	if(GetParent() != NULL)
	{
		GetParent()->ScreenToClient(&rcWnd);
		::SetWindowPos(m_hWnd,HWND_BOTTOM,rcWnd.left,rcWnd.top,0,0,SWP_NOSIZE);
	}
	CStatic::PreSubclassWindow();
}

void CLevelIndicator::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CStatic::OnPaint() for painting messages
	CPen pen,Progresspen;
	CPen *pOldPen;
	CBrush *pOlBr;
	Progresspen.CreatePen(PS_SOLID,2,RGB(198,195,198));
	pOldPen=dc.SelectObject(&Progresspen);
	CBrush br(RGB(198,195,198));
	pOlBr = dc.SelectObject(&br);
	dc.Rectangle(&m_rcdecimalbar);
	dc.SelectObject(pOldPen);
	dc.SelectObject(pOlBr);

	ShowEnergyLevelOnProgressBar(&dc);

	pen.CreatePen(PS_SOLID,2,RGB(115,182,231));
	pOldPen = dc.SelectObject(&pen);
	pOlBr=dc.SelectObject(&m_brushBKColor);
	dc.RoundRect(&m_rcResult,CPoint(15,15));
	dc.RoundRect(&m_rcBalanceRect,CPoint(15,15));

	//
	int l1 = m_rcdecimalbar.left-1;
	int w = 5;
	int t = m_rcdecimalbar.top;
	int step = (( m_rcdecimalbar.Height())/(m_nNoOfLevels));

	for(int i = 0;i <= m_nNoOfLevels;i++)
	{
		dc.MoveTo(l1,t+i*step);
		//if(i == 0) 
		//{
		//dc.LineTo(l1-w-5,t+i*step);
		//dc.SetBkMode(TRANSPARENT);
		//dc.TextOut(l1-w-35-m_nLenOfMinEnergy,((t+i*step)-8),m_strMinEnergyVal,m_nLenOfMinEnergy);
		//dc.TextOut(l1-w-35-m_nLenOfMaxEnergy,((t+i*step)-8),_itot,);
		//}
		//if(i == m_nNoOfLevels)
		//{
		//dc.LineTo(l1-w-5,t+i*step);
		//dc.SetBkMode(TRANSPARENT);
		//dc.TextOut(l1-w-35-m_nLenOfMaxEnergy,((t+i*step)-8),m_strMaxEnergyVal,m_nLenOfMaxEnergy);
		//dc.TextOut(l1-w-35-m_nLenOfMinEnergy,((t+i*step)-8),m_strMinEnergyVal,m_nLenOfMinEnergy);
		//}
		if(i < m_nNoOfLevels)
		{
			dc.LineTo(l1-w,t+i*step);
			dc.SetBkMode(TRANSPARENT);
			str.Format(_T("%d"),(m_nNoOfLevels - i));
			dc.TextOut(l1-w-15,((t+i*step)-8),str,1);
		}
	}

	dc.SelectObject(pOldPen);
	dc.SelectObject(pOlBr);
	if(br.m_hObject)
		br.DeleteObject();
	if(pen.m_hObject)
		pen.DeleteObject();
	if(Progresspen.m_hObject)
		Progresspen.DeleteObject();
}


/*!
* \brief \n
* Shows HCL energy on progress bar .
* 
* \param pDC
* DC of the dialog.
* 
* \remarks
* Calculated HCL Energy is divided into two parts decimal part, fractional part e.g 3.0445 '3'decimal part '.0445' represents fractional part.
* and value of each part is represented using decimal and fractional progress bars.
*/
void CLevelIndicator::ShowEnergyLevelOnProgressBar(CDC *pDC)
{
	CPen *Oldpen = NULL;
	CBrush *OldBr = NULL;

	CRect rc;
	//double dbldecimal = m_nCurEnergyDecimalPart;

	//if((m_dblprevEnergyDecimalPart > dbldecimal)||(dbldecimal == 0))
	//if(m_nCurrentLevel <= 0)
	//{
	OldBr = pDC->SelectObject(&m_GrayBr);
	Oldpen = pDC->SelectObject(&m_GrayPen);
	int ntemp;
	int nVal;
	rc = m_rcdecimalbar;
	
	//if(dbldecimal < m_dblMinEnergyValue)
	//{
	//rc.left += 1;
	//rc.right -= 1;
	//rc.top = m_rcdecimalbar.top/*m_nRectdecEnergy*/;
	//rc.bottom = m_rcdecimalbar.bottom;
	//pDC->Rectangle(&rc);
	//}
	//else if((dbldecimal <= m_dblMaxEnergyValue) && (dbldecimal > m_dblMinEnergyValue))
	//{
	//double dblInterval = m_dblMaxEnergyValue/m_nNoOfLevels;
	//nVal = (int)(m_dblMaxEnergyValue-m_dblMinEnergyValue);
	//double dblTempVal = ndecimal - m_dblMinEnergyValue;
	//dblTempVal = ceil(dblTempVal/dblInterval);
	//dblTempVal = dblTempVal*dblInterval;
	////ntemp = (int)( m_rcdecimalbar.bottom - ((nTempVal*m_rcdecimalbar.Height())/nVal) );
	//ntemp = (int)( m_rcdecimalbar.bottom - ((dblTempVal*m_rcdecimalbar.Height())/nVal) );

	//double dblInterval = m_rcdecimalbar.Height()/m_nNoOfLevels;
	//nVal = dblInterval*m_nCurrentLevel;
	//ntemp = (int)( m_rcdecimalbar.bottom - nVal );

	//rc.left += 1;
	//rc.right -= 1;
	//rc.top = m_rcdecimalbar.top/*m_nRectdecEnergy*/;
	//rc.bottom = ntemp;
	//pDC->Rectangle(&rc);
	//}

	double dblInterval = m_rcdecimalbar.Height()/m_nNoOfLevels;
	nVal = dblInterval*m_nCurrentLevel;
	ntemp = (int)( m_rcdecimalbar.bottom - nVal );
	rc.left += 1;
	rc.right -= 1;
	rc.top = m_rcdecimalbar.top/*m_nRectdecEnergy*/;
	rc.bottom = ntemp;
	pDC->Rectangle(&rc);

	pDC->SelectObject(Oldpen);
	pDC->SelectObject(OldBr);
	if(m_nCurrentLevel <= 0)
	{
		return;
	}
	//}
	//else
	//{
	if(OldBr!=NULL&&Oldpen!=NULL)
	{
		pDC->SelectObject(OldBr);
		pDC->SelectObject(Oldpen);
	}
	if(m_nCurrentLevel == 1)
	{
		Oldpen=pDC->SelectObject(&m_YellowPen);
		OldBr=pDC->SelectObject(&m_YellowBr);
	}
	else if(m_nCurrentLevel > 1)
	{
		Oldpen=pDC->SelectObject(&m_BluePen);
		OldBr=pDC->SelectObject(&m_BlueBr);
	}
	rc = m_rcdecimalbar;
	//int nVal;
	//if(ndecimal < m_dblMinEnergyValue)
	//{
	//	m_nRectdecEnergy  = m_rcdecimalbar.bottom;
	//}
	//else if(ndecimal < m_dblMaxEnergyValue)
	//if((dbldecimal <= m_dblMaxEnergyValue) && (dbldecimal > m_dblMinEnergyValue))
	//{
	//double dblInterval = m_dblMaxEnergyValue/m_nNoOfLevels;
	//nVal = (int)(m_dblMaxEnergyValue-m_dblMinEnergyValue);
	////int nTempVal = ndecimal - m_dblMinEnergyValue;
	//double dblTempVal = ndecimal - m_dblMinEnergyValue;
	//dblTempVal = ceil(dblTempVal/dblInterval);
	//dblTempVal = dblTempVal*dblInterval;
	////m_nRectdecEnergy=(int)(m_rcdecimalbar.bottom- ((nTempVal*m_rcdecimalbar.Height())/nVal) );
	//m_nRectdecEnergy=(int)(m_rcdecimalbar.bottom - ((dblTempVal* m_rcdecimalbar.Height())/nVal) );

	dblInterval = m_rcdecimalbar.Height()/m_nNoOfLevels;
	nVal = dblInterval*m_nCurrentLevel;
	m_nRectdecEnergy = (int)(m_rcdecimalbar.bottom - nVal );
	//rc.left+=1;
	//rc.right-=1;
	//rc.bottom-=1;
	rc.top=m_nRectdecEnergy;
	pDC->Rectangle(&rc);
	//}
	//else if( dbldecimal > m_dblMaxEnergyValue)
	//{
	//m_nRectdecEnergy = m_rcdecimalbar.top;
	//rc.left+=1;
	//rc.right-=1;
	//rc.bottom-=1;
	//rc.top=m_nRectdecEnergy;
	//pDC->Rectangle(&rc);
	//}

	pDC->SelectObject(Oldpen);
	pDC->SelectObject(OldBr);
	//}

	//m_dblprevEnergyDecimalPart = dbldecimal;
}


void CLevelIndicator::SetMinMaxEnergyVals(int nMinVal,int nMaxVal)
{
	m_dblMinEnergyValue = nMinVal;
	m_strMinEnergyVal.Format(_T("%d"),nMinVal);
	m_nLenOfMinEnergy = m_strMinEnergyVal.GetLength();
	m_dblMaxEnergyValue = nMaxVal;
	m_strMaxEnergyVal.Format(_T("%d"),nMaxVal);
	m_nLenOfMaxEnergy = m_strMaxEnergyVal.GetLength();
}

void CLevelIndicator::SetNoOfLevels(int nLevels)
{
	m_nNoOfLevels = nLevels;
}

void CLevelIndicator::SetBaseEnergyVal(int nBaseEnergyLevel)
{
	m_nBaseEnergyVal = nBaseEnergyLevel;
}

void CLevelIndicator::SetCurEnergyVal(int nEnergyVal)
{
	m_nCurEnergyDecimalPart = nEnergyVal;
}

void CLevelIndicator::SetCurEnergyLevel(int nEnergyLevel)
{
	m_nCurrentLevel = nEnergyLevel;
}