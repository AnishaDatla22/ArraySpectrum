#pragma once


// CLevelIndicator

class CLevelIndicator : public CStatic
{
	DECLARE_DYNAMIC(CLevelIndicator)
public:
	CBrush m_brBkg;
	CBrush m_brushBKColor;
	COLORREF m_clr;
	///Min Energy Limit
	double m_dblMinEnergyValue;
	///Max Energy Limit
	double m_dblMaxEnergyValue;
	///
	CString m_strMinEnergyVal;
	///
	CString m_strMaxEnergyVal;
	///
	int m_nLenOfMinEnergy;
	///
	int m_nLenOfMaxEnergy;

	///Rect for drawing Energy value.
	CRect m_rcResult;
	///Rect for drawing Balance value.
	CRect m_rcBalanceRect;
    ///HCL Energy is divided into parts decimal part, fractional part e.g 3.0445 '3'decimal part '.0445' represents fractional part.
	///Dimensions of Scale used for drawing decimal part of HCL Energy.
    CRect m_rcdecimalbar;
	
	///HCL Energy is divided into parts decimal part, fractional part e.g 3.0445 '3'decimal part '.0445' represents fractional part.
    ///Decimal part of HCL Energy
	int m_nCurEnergyDecimalPart;

	///Total Rect of decimal scale is divided into 10 parts.
	///Part of decimal scale to be filled 
	int m_nRectdecEnergy;

	///Previous Energy decimal part.
	int m_dblprevEnergyDecimalPart;
	
	CPen m_GrayPen,m_BluePen,m_YellowPen;
	CBrush m_GrayBr,m_BlueBr,m_YellowBr;
	//
	int m_nNoOfLevels;
	///
	int m_nBaseEnergyVal;
	///
	int m_nCurrentLevel;
private:
	CString str;
public:
	CLevelIndicator();
	virtual ~CLevelIndicator();
	virtual void PreSubclassWindow( );
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	///Shows Sample energy level on progress bar .
	void ShowEnergyLevelOnProgressBar(CDC *pDC);
	///
    void SetMinMaxEnergyVals(int nMinVal,int nMaxVal);
	///
	void SetNoOfLevels(int nLevels);
	///
	void SetBaseEnergyVal(int nBaseEnergy);
	///
	void SetCurEnergyVal(int nEnergyVal);
	///
	void SetCurEnergyLevel(int nEnergyLevel);
};


