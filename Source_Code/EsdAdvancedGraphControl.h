// EsdAdvancedGraphControl.h  : Declaration of ActiveX Control wrapper class(es) created by Microsoft Visual C++

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CDEsdAdvancedGraphControl

class CDEsdAdvancedGraphControl : public CWnd
{
protected:
	DECLARE_DYNCREATE(CDEsdAdvancedGraphControl)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xE98E4ED3, 0xC038, 0x4705, { 0x8E, 0xAB, 0x43, 0xAD, 0x8A, 0x1B, 0x75, 0xAB } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// Attributes
public:

// Operations
public:

	long AddGraph(LPCTSTR strName, long lngColor)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strName, lngColor);
		return result;
	}
	double InterPolateData(long lngGraphId, double dblXvalue)
	{
		double result;
		static BYTE parms[] = VTS_I4 VTS_R8 ;
		InvokeHelper(0x96, DISPATCH_METHOD, VT_R8, (void*)&result, parms, lngGraphId, dblXvalue);
		return result;
	}
	void AddDataPoint(long lngGraphIdx, double dblXVal, double dblYVal)
	{
		static BYTE parms[] = VTS_I4 VTS_R8 VTS_R8 ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lngGraphIdx, dblXVal, dblYVal);
	}
	void AddDataPoints(long lngGraphIdx, long lngNoOfPoints, VARIANT varXVals, VARIANT varYVals)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lngGraphIdx, lngNoOfPoints, &varXVals, &varYVals);
	}
	void ModifyDataPoint(long lngGraphIdx, long lngPtIdx, double dblXVal, double dblYVal)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_R8 VTS_R8 ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lngGraphIdx, lngPtIdx, dblXVal, dblYVal);
	}
	void DrawMultiColorGraph(long lngGraphIdx, long lngNoOfPoints, VARIANT varLngColors, VARIANT varDblXVals, VARIANT varDblYValues, long lngPenWdth)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_I4 ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lngGraphIdx, lngNoOfPoints, &varLngColors, &varDblXVals, &varDblYValues, lngPenWdth);
	}
	void SetGraphPointColor(long lngGraphIdx, long lngPtIdx, unsigned long clrColor)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_UI4 ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lngGraphIdx, lngPtIdx, clrColor);
	}
	BOOL RemoveDataPoint(long lngGraphIdx, long lngPtIdx)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lngGraphIdx, lngPtIdx);
		return result;
	}
	void RemoveGraph(long lngGraphIdx)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lngGraphIdx);
	}
	void RemoveAllGraphs()
	{
		InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SetGraphtype(long lngGraphIdx, unsigned short unGraphType)
	{
		static BYTE parms[] = VTS_I4 VTS_UI2 ;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lngGraphIdx, unGraphType);
	}
	void SetGraphVisible(long lngGraphIdx, BOOL bShowRHide)
	{
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lngGraphIdx, bShowRHide);
	}
	BOOL ModifyLegends(long lngGraphIdx, LPCTSTR strGraphName, unsigned long clrGraphColor)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_UI4 ;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lngGraphIdx, strGraphName, clrGraphColor);
		return result;
	}
	BOOL StartOnlinePeakDetection()
	{
		BOOL result;
		InvokeHelper(0xd, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL StopOnlinePeakDetection()
	{
		BOOL result;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void StartOfflinePeakDetection()
	{
		InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void StopOfflinePeakDetection()
	{
		InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void StartAnimation(BOOL bStartRStop)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bStartRStop);
	}
	LPUNKNOWN GetControlUnknown()
	{
		LPUNKNOWN result;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_UNKNOWN, (void*)&result, NULL);
		return result;
	}
	void CopyGraph()
	{
		InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void CopyData()
	{
		InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL ExportGraphData(long lngGraphIdx, long lngExpType, BOOL bIncludeIndex, BOOL bIncludeHeader, BOOL bIncludeTitle)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BOOL VTS_BOOL VTS_BOOL ;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lngGraphIdx, lngExpType, bIncludeIndex, bIncludeHeader, bIncludeTitle);
		return result;
	}
	void CalculateTrendLine(long lngGraphIdx, long lngTrendLineType, BOOL bShowTrendLine, long lngtrendLineColor)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BOOL VTS_I4 ;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lngGraphIdx, lngTrendLineType, bShowTrendLine, lngtrendLineColor);
	}
	BOOL FindLinearCoefficients(long lngDataCount, VARIANT varDblArrXData, VARIANT varDblArrYData, double * dblSlope, double * dblIntercept)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_VARIANT VTS_VARIANT VTS_PR8 VTS_PR8 ;
		InvokeHelper(0x17, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lngDataCount, &varDblArrXData, &varDblArrYData, dblSlope, dblIntercept);
		return result;
	}
	BOOL FindQuadraticCoefficients(long lngDataCount, VARIANT varDblArrXData, VARIANT varDblArrYData, double * dblA0, double * dblA1, double * dblA2)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_VARIANT VTS_VARIANT VTS_PR8 VTS_PR8 VTS_PR8 ;
		InvokeHelper(0x18, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lngDataCount, &varDblArrXData, &varDblArrYData, dblA0, dblA1, dblA2);
		return result;
	}
	BOOL LinearCoefficients(long lngGraphIdx, double * dblByAddSlope, double * dblByAddC)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_PR8 VTS_PR8 ;
		InvokeHelper(0x19, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lngGraphIdx, dblByAddSlope, dblByAddC);
		return result;
	}
	BOOL QuadraticCoefficients(long lngGraphIdx, double * dblByAddA0, double * dblByAddA1, double * dblByAddA2)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_PR8 VTS_PR8 VTS_PR8 ;
		InvokeHelper(0x1a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lngGraphIdx, dblByAddA0, dblByAddA1, dblByAddA2);
		return result;
	}
	void LinearFitX(long lngDataCount, double dblSlope, double dblIntercept, double * dblArrXdata, double * dblArrYData)
	{
		static BYTE parms[] = VTS_I4 VTS_R8 VTS_R8 VTS_PR8 VTS_PR8 ;
		InvokeHelper(0x1b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lngDataCount, dblSlope, dblIntercept, dblArrXdata, dblArrYData);
	}
	void QuadraticFitX(long lngDataCount, double dblA0, double dblA1, double dblA2, double * dblArrXdata, double * dblArrYData)
	{
		static BYTE parms[] = VTS_I4 VTS_R8 VTS_R8 VTS_R8 VTS_PR8 VTS_PR8 ;
		InvokeHelper(0x1c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lngDataCount, dblA0, dblA1, dblA2, dblArrXdata, dblArrYData);
	}
	void GetPeakInfo(long lngGraphIdx, VARIANT * dblHeight, VARIANT * dblWidth, VARIANT * dblArea, VARIANT * lngPeakStartIndex, VARIANT * lngPeakMaxindex, VARIANT * lngPeakEndIndex)
	{
		static BYTE parms[] = VTS_I4 VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x1d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lngGraphIdx, dblHeight, dblWidth, dblArea, lngPeakStartIndex, lngPeakMaxindex, lngPeakEndIndex);
	}
	long GetPeakIndexes(long lngGraphIdx, long lngPeakLevel, VARIANT * varLngPeakIndexes)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PVARIANT ;
		InvokeHelper(0x1e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lngGraphIdx, lngPeakLevel, varLngPeakIndexes);
		return result;
	}
	void PeakFillArea(long lngGraphIdx)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x20, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lngGraphIdx);
	}
	void DrawBaseLine(long lngGraphIdx)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x21, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lngGraphIdx);
	}
	long GetNumberOfGraphs()
	{
		long result;
		InvokeHelper(0x24, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetAllGraphIDs(VARIANT * varLngGraphIndexes)
	{
		long result;
		static BYTE parms[] = VTS_PVARIANT ;
		InvokeHelper(0x25, DISPATCH_METHOD, VT_I4, (void*)&result, parms, varLngGraphIndexes);
		return result;
	}
	void GetPeaksCount(VARIANT * varLngPeaksCount)
	{
		static BYTE parms[] = VTS_PVARIANT ;
		InvokeHelper(0x2a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, varLngPeaksCount);
	}
	void DisplayTextAt(long lngGraphIdx, LPCTSTR bstrName, double dblXVal, double dblYVal)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_R8 VTS_R8 ;
		InvokeHelper(0x2b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lngGraphIdx, bstrName, dblXVal, dblYVal);
	}
	long GetGraphData(long lngGraphIdx, VARIANT * varDblXval, VARIANT * varDblYval)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x32, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lngGraphIdx, varDblXval, varDblYval);
		return result;
	}
	void GetGraphDataAt(long lngGraphIdx, long lngIndex, double * dblXVal, double * dblYVal)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PR8 VTS_PR8 ;
		InvokeHelper(0x33, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lngGraphIdx, lngIndex, dblXVal, dblYVal);
	}
	long GetGraphDataCont(long lngGraphIdx)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x34, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lngGraphIdx);
		return result;
	}
	void GetGraphMinMax(long lngGraphIdx, double * dblXmin, double * dblYmin, double * dblXmax, double * dblYmax)
	{
		static BYTE parms[] = VTS_I4 VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8 ;
		InvokeHelper(0x35, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lngGraphIdx, dblXmin, dblYmin, dblXmax, dblYmax);
	}
	long GetGraphPeaksCount(long lngGraphIdx)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x39, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lngGraphIdx);
		return result;
	}
	void PrintGraph(long lngPrinterDC, long lngPageLeft, long lngPageTop, long lngPageRight, long lngPageBottom)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x3a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lngPrinterDC, lngPageLeft, lngPageTop, lngPageRight, lngPageBottom);
	}
	void PrintPreview(long lngDC, long lngPageLeft, long lngPageTop, long lngPageRight, long lngPageBottom)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x3b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lngDC, lngPageLeft, lngPageTop, lngPageRight, lngPageBottom);
	}
	void DrawDatumLine(long lngGraphIdx, double dblXVal, double dblYVal, unsigned long clrLineColor)
	{
		static BYTE parms[] = VTS_I4 VTS_R8 VTS_R8 VTS_UI4 ;
		InvokeHelper(0x3e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lngGraphIdx, dblXVal, dblYVal, clrLineColor);
	}
	long FindPeaks(VARIANT varDblYvals, long lngDataPointsCount, long lngPeakLevel, VARIANT * varLngPeakIndexes)
	{
		long result;
		static BYTE parms[] = VTS_VARIANT VTS_I4 VTS_I4 VTS_PVARIANT ;
		InvokeHelper(0x46, DISPATCH_METHOD, VT_I4, (void*)&result, parms, &varDblYvals, lngDataPointsCount, lngPeakLevel, varLngPeakIndexes);
		return result;
	}
	BOOL EntireGraph(long lngGraphIdx)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x50, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lngGraphIdx);
		return result;
	}
	BOOL ShowPeaks(long lngGraphIdx, short intPeakLevel)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I2 ;
		InvokeHelper(0x56, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lngGraphIdx, intPeakLevel);
		return result;
	}
	BOOL HidePeaks(long lngGraphIdx)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x57, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lngGraphIdx);
		return result;
	}
	BOOL MoveCrossWireToFirst(long * lngGraphId, long * lngDataPoint)
	{
		BOOL result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x5a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lngGraphId, lngDataPoint);
		return result;
	}
	BOOL MoveCrossWireToLast(long * lngGraphId, long * lngDataPoint)
	{
		BOOL result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x5b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lngGraphId, lngDataPoint);
		return result;
	}
	BOOL MoveCrossWireToNext(long * lngGraphId, long * lngDataPoint, short intStepBy)
	{
		BOOL result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 VTS_I2 ;
		InvokeHelper(0x5c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lngGraphId, lngDataPoint, intStepBy);
		return result;
	}
	BOOL MoveCrossWireToPrev(long * lngGraphId, long * lngDataPoint, short intStepBy)
	{
		BOOL result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 VTS_I2 ;
		InvokeHelper(0x5d, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lngGraphId, lngDataPoint, intStepBy);
		return result;
	}
	BOOL DisplayCrossWireAt(double dblXVal, double dblYVal)
	{
		BOOL result;
		static BYTE parms[] = VTS_R8 VTS_R8 ;
		InvokeHelper(0x5e, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, dblXVal, dblYVal);
		return result;
	}
	void SetCustomCrosswireText(LPCTSTR bstrCrosswireText, BOOL blnHideXYValues, double Concentration)
	{
		static BYTE parms[] = VTS_BSTR VTS_BOOL VTS_R8 ;
		InvokeHelper(0x5f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrCrosswireText, blnHideXYValues, Concentration);
	}
	short get_AxesMarkingPrecision(long lngAxis)
	{
		short result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x4d, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, lngAxis);
		return result;
	}
	void put_AxesMarkingPrecision(long lngAxis, short newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I2 ;
		InvokeHelper(0x4d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, lngAxis, newValue);
	}
	CString get_Axestitle(long lngAxis)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x4e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, lngAxis);
		return result;
	}
	void put_Axestitle(long lngAxis, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x4e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, lngAxis, newValue);
	}
	double get_AxisMaximum(long lngAxis)
	{
		double result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x51, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, parms, lngAxis);
		return result;
	}
	void put_AxisMaximum(long lngAxis, double newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_R8 ;
		InvokeHelper(0x51, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, lngAxis, newValue);
	}
	unsigned long get_AxesTitlesColor(long lngAxis)
	{
		unsigned long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x52, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, parms, lngAxis);
		return result;
	}
	void put_AxesTitlesColor(long lngAxis, unsigned long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_UI4 ;
		InvokeHelper(0x52, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, lngAxis, newValue);
	}
	double get_AxisMinimum(long lngAxis)
	{
		double result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x53, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, parms, lngAxis);
		return result;
	}
	void put_AxisMinimum(long lngAxis, double newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_R8 ;
		InvokeHelper(0x53, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, lngAxis, newValue);
	}
	unsigned long get_AxisGridColor(long lngAxis)
	{
		unsigned long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x54, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, parms, lngAxis);
		return result;
	}
	void put_AxisGridColor(long lngAxis, unsigned long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_UI4 ;
		InvokeHelper(0x54, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, lngAxis, newValue);
	}
	short get_AxisGridStyle(long lngAxis)
	{
		short result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x55, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, lngAxis);
		return result;
	}
	void put_AxisGridStyle(long lngAxis, short newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I2 ;
		InvokeHelper(0x55, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, lngAxis, newValue);
	}
	long get_ZoomDirection()
	{
		long result;
		InvokeHelper(0x3f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_ZoomDirection(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_EnableZoom()
	{
		BOOL result;
		InvokeHelper(0x40, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_EnableZoom(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x40, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_BaseLineType()
	{
		long result;
		InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_BaseLineType(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x22, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	unsigned long get_BaseLineColor()
	{
		unsigned long result;
		InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
		return result;
	}
	void put_BaseLineColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x23, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	unsigned long get_PeakFillColor()
	{
		unsigned long result;
		InvokeHelper(0x26, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
		return result;
	}
	void put_PeakFillColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x26, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	double get_PeakMinArea()
	{
		double result;
		InvokeHelper(0x27, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
		return result;
	}
	void put_PeakMinArea(double newValue)
	{
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x27, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	double get_PeakMinHeight()
	{
		double result;
		InvokeHelper(0x28, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
		return result;
	}
	void put_PeakMinHeight(double newValue)
	{
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x28, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	double get_PeakMinWidth()
	{
		double result;
		InvokeHelper(0x29, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
		return result;
	}
	void put_PeakMinWidth(double newValue)
	{
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x29, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	unsigned long get_BackGroundColor()
	{
		unsigned long result;
		InvokeHelper(0x2c, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
		return result;
	}
	void put_BackGroundColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x2c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	unsigned long get_CustomTextColor()
	{
		unsigned long result;
		InvokeHelper(0x2d, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
		return result;
	}
	void put_CustomTextColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x2d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	unsigned long get_CustomTextBackColor()
	{
		unsigned long result;
		InvokeHelper(0x2e, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
		return result;
	}
	void put_CustomTextBackColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x2e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	double get_AverageNoise()
	{
		double result;
		InvokeHelper(0x2f, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
		return result;
	}
	void put_AverageNoise(double newValue)
	{
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x2f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	unsigned long get_AxesMarkingColor()
	{
		unsigned long result;
		InvokeHelper(0x30, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
		return result;
	}
	void put_AxesMarkingColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x30, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_ShowLegend()
	{
		BOOL result;
		InvokeHelper(0x31, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_ShowLegend(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x31, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_BackImage()
	{
		CString result;
		InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_BackImage(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x36, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_EnableHorzDatumLine()
	{
		BOOL result;
		InvokeHelper(0x3c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_EnableHorzDatumLine(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x3c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_EnableVericalDatumLine()
	{
		BOOL result;
		InvokeHelper(0x3d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_EnableVericalDatumLine(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x3d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_MouseButtonForZoom()
	{
		long result;
		InvokeHelper(0x41, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_MouseButtonForZoom(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x41, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_MinimumPixelsForZoom()
	{
		long result;
		InvokeHelper(0x42, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_MinimumPixelsForZoom(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x42, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_ScrollDirection()
	{
		long result;
		InvokeHelper(0x43, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_ScrollDirection(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x43, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_MouseButtonForScroll()
	{
		long result;
		InvokeHelper(0x44, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_MouseButtonForScroll(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x44, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_ShowHeader()
	{
		BOOL result;
		InvokeHelper(0x48, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_ShowHeader(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x48, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_Header()
	{
		CString result;
		InvokeHelper(0x49, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_Header(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x49, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_ShowDataAtPeak()
	{
		BOOL result;
		InvokeHelper(0x58, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_ShowDataAtPeak(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x58, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_CrossWire()
	{
		BOOL result;
		InvokeHelper(0x59, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_CrossWire(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x59, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_CrossWireDataPointIndex()
	{
		long result;
		InvokeHelper(0x60, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_CrossWireDataPointIndex(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x60, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_Sort()
	{
		BOOL result;
		InvokeHelper(0x61, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_Sort(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x61, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_AutoRange()
	{
		BOOL result;
		InvokeHelper(0x62, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_AutoRange(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x62, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_PerConc()
	{
		BOOL result;
		InvokeHelper(0x63, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_PerConc(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x63, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_ShowConcAtPeaks()
	{
		BOOL result;
		InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_ShowConcAtPeaks(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_ShowXTitle()
	{
		BOOL result;
		InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_ShowXTitle(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_ShowYTitle()
	{
		BOOL result;
		InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_ShowYTitle(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void SetLegendFont(LPCTSTR strFontName, long lngFontSize)
	{
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x67, DISPATCH_METHOD, VT_EMPTY, NULL, parms, strFontName, lngFontSize);
	}
	void SetXYMarkingFont(LPCTSTR strFontName, long lngFontSize)
	{
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x68, DISPATCH_METHOD, VT_EMPTY, NULL, parms, strFontName, lngFontSize);
	}
	void SetCustomTextFont(LPCTSTR strFontName, long lngFontSize)
	{
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x69, DISPATCH_METHOD, VT_EMPTY, NULL, parms, strFontName, lngFontSize);
	}
	short get_XGrids()
	{
		short result;
		InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
		return result;
	}
	void put_XGrids(short newValue)
	{
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x6a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	short get_YGrids()
	{
		short result;
		InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
		return result;
	}
	void put_YGrids(short newValue)
	{
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x6b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL ZoomIn(double dblXmin, double dblXmax, double dblYmin, double dblYmax)
	{
		BOOL result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 ;
		InvokeHelper(0x6c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, dblXmin, dblXmax, dblYmin, dblYmax);
		return result;
	}
	void ZoomOut()
	{
		InvokeHelper(0x6d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SetHeaderFont(LPCTSTR strFontName, long lngFontSize)
	{
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x6e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, strFontName, lngFontSize);
	}
	void SetAxesTitlesFont(LPCTSTR strFontName, long lngFontSize)
	{
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x6f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, strFontName, lngFontSize);
	}
	void DisplayText(LPCTSTR bstrText, long lngLeftMargin, long lngRightMargin)
	{
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 ;
		InvokeHelper(0x70, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrText, lngLeftMargin, lngRightMargin);
	}
	void ClearCustomText()
	{
		InvokeHelper(0x71, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void WidthAt5PercentHeight(long lngPos, double * dblWidth, double * dblLeftWidth, double * dblRightWidth)
	{
		static BYTE parms[] = VTS_I4 VTS_PR8 VTS_PR8 VTS_PR8 ;
		InvokeHelper(0x73, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lngPos, dblWidth, dblLeftWidth, dblRightWidth);
	}
	void WidthAt10PercentHeight(long lngPos, double * dblWidth, double * dblLeftWidth, double * dblRightWidth)
	{
		static BYTE parms[] = VTS_I4 VTS_PR8 VTS_PR8 VTS_PR8 ;
		InvokeHelper(0x74, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lngPos, dblWidth, dblLeftWidth, dblRightWidth);
	}
	void WidthAtHalfHeight(long lngPos, double * dblWidth, double * dblLeftWidth, double * dblRightWidth)
	{
		static BYTE parms[] = VTS_I4 VTS_PR8 VTS_PR8 VTS_PR8 ;
		InvokeHelper(0x75, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lngPos, dblWidth, dblLeftWidth, dblRightWidth);
	}
	void MoveAxisFromBasePosition(long lngAxisIdx, long lngPositionInPercent, BOOL blnIsStdAxis)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BOOL ;
		InvokeHelper(0x77, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lngAxisIdx, lngPositionInPercent, blnIsStdAxis);
	}
	void ChangeAxisStartPosition(long lngAxisIdx, long lngPositionInPercent, BOOL blnIsStdAxis)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BOOL ;
		InvokeHelper(0x78, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lngAxisIdx, lngPositionInPercent, blnIsStdAxis);
	}
	void ChangeAxisEndPosition(long lngAxisIdx, long lngPositionInPercent, BOOL blnIsStdAxis)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BOOL ;
		InvokeHelper(0x79, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lngAxisIdx, lngPositionInPercent, blnIsStdAxis);
	}
	void AssignAxesForGraph(long lngGraphIdx, long lngCustomHorzAxis, long lngCustomVertAxis)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x7a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lngGraphIdx, lngCustomHorzAxis, lngCustomVertAxis);
	}
	void RemoveCustomAxis(long lngCustomAxisIdx)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x7b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lngCustomAxisIdx);
	}
	void RemoveAllCustomAxes()
	{
		InvokeHelper(0x7c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long AddCustomAxis(BOOL lbnIsHorizontal)
	{
		long result;
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x7d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lbnIsHorizontal);
		return result;
	}
	CString get_CustomAxisTitle(long lngAxisIdx)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x7e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, lngAxisIdx);
		return result;
	}
	void put_CustomAxisTitle(long lngAxisIdx, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x7e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, lngAxisIdx, newValue);
	}
	double get_CustomAxisMaximum(long lngAxisIdx)
	{
		double result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x7f, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, parms, lngAxisIdx);
		return result;
	}
	void put_CustomAxisMaximum(long lngAxisIdx, double newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_R8 ;
		InvokeHelper(0x7f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, lngAxisIdx, newValue);
	}
	double get_CustomAxisMinimum(long lngAxisIdx)
	{
		double result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x80, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, parms, lngAxisIdx);
		return result;
	}
	void put_CustomAxisMinimum(long lngAxisIdx, double newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_R8 ;
		InvokeHelper(0x80, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, lngAxisIdx, newValue);
	}
	long get_CustomAxisGrids(long lngAxisIdx)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x81, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, lngAxisIdx);
		return result;
	}
	void put_CustomAxisGrids(long lngAxisIdx, long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x81, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, lngAxisIdx, newValue);
	}
	long get_CustomAxisTitleAngle(long lngAxisIdx)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x82, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, lngAxisIdx);
		return result;
	}
	void put_CustomAxisTitleAngle(long lngAxisIdx, long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x82, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, lngAxisIdx, newValue);
	}
	void DoGraphReprocess(unsigned char * bytEventInfo, long lngNoOfEvents)
	{
		static BYTE parms[] = VTS_PUI1 VTS_I4 ;
		InvokeHelper(0x83, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bytEventInfo, lngNoOfEvents);
	}
	double get_PeakMinTreshold()
	{
		double result;
		InvokeHelper(0x84, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
		return result;
	}
	void put_PeakMinTreshold(double newValue)
	{
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x84, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void MarkStartnEndpts(long lngGraphIdx)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x85, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lngGraphIdx);
	}
	void SetStartnEndptMarkingColor(unsigned long newVal)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x86, DISPATCH_METHOD, VT_EMPTY, NULL, parms, newVal);
	}
	
	unsigned long GetStartnEndptMarkingColor()
	{
		unsigned long result;
		InvokeHelper(0x87, DISPATCH_METHOD, VT_UI4, (void*)&result, NULL);
		return result;
	}
	void FindArea(LONG lngGraphID, DOUBLE dblStartPointXVal,DOUBLE dblStartPointYVal, DOUBLE dblEndPointXVal,DOUBLE dblEndPointYVal,LONG nStartIndex,LONG nEndIndex,DOUBLE* dblArea)
	{
		static BYTE parms[] = VTS_I4 VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_I4 VTS_I4 VTS_PR8 ;
		InvokeHelper(0x88, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lngGraphID, dblStartPointXVal, dblStartPointYVal, dblEndPointXVal, dblEndPointYVal, nStartIndex, nEndIndex, dblArea);
	}
	void GetArea(LONG lngGraphID, DOUBLE dblStartPointXVal,DOUBLE dblStartPointYVal, DOUBLE dblEndPointXVal,DOUBLE dblEndPointYVal,LONG nStartIndex,LONG nEndIndex,DOUBLE* dblArea)
	{
		static BYTE parms[] = VTS_I4 VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_I4 VTS_I4 VTS_PR8 ;
		InvokeHelper(0x97, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lngGraphID, dblStartPointXVal, dblStartPointYVal, dblEndPointXVal, dblEndPointYVal, nStartIndex, nEndIndex, dblArea);
	}
};
