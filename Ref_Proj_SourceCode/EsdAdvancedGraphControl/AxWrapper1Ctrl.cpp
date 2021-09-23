// AxWrapper1Ctrl.cpp : Implementation of the CEsdAdvancedGraphCtrl ActiveX Control class.

#include "stdafx.h"
#include "AxWrapper1.h"
#include "AxWrapper1Ctrl.h"
#include "AxWrapper1PropPage.h"
#include "math.h"
#include<Shlwapi.h>  //To use "PathFileExists" Function


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CEsdAdvancedGraphCtrl, COleControl)

#define ID_TCHART 1000
#define MANUALPEAK_NOTPOSSIBLE 5000
#define MANUALPEAK_NEW  5001
#define MANUALPEAK_REPLACE 5002

// Message map

BEGIN_MESSAGE_MAP(CEsdAdvancedGraphCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CEsdAdvancedGraphCtrl,COleControl)
	ON_EVENT(CEsdAdvancedGraphCtrl, ID_TCHART, 1  /* OnAfterDraw */, OnAfterDrawTChart, VTS_NONE)
	ON_EVENT(CEsdAdvancedGraphCtrl, ID_TCHART, 3  /* OnClick */, OnClickTChart, VTS_NONE)
	ON_EVENT(CEsdAdvancedGraphCtrl, ID_TCHART, 4  /* OnClickAxis */, OnClickTChartAxis, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CEsdAdvancedGraphCtrl, ID_TCHART, 5  /* OnClickBackground */, OnClickTChartBackground, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CEsdAdvancedGraphCtrl, ID_TCHART, 6  /* OnClickLegend */, OnClickTChartLegend, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CEsdAdvancedGraphCtrl, ID_TCHART, 7  /* OnClickSeries */, OnClickTChartSeries, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CEsdAdvancedGraphCtrl, ID_TCHART, 8  /* OnDblClick */, OnDblClickTChart, VTS_NONE)
	ON_EVENT(CEsdAdvancedGraphCtrl, ID_TCHART, 14 /* OnGetAxisLabel */, OnGetTChartAxisLabel, VTS_I4 VTS_I4 VTS_I4 VTS_PBSTR)
	ON_EVENT(CEsdAdvancedGraphCtrl, ID_TCHART, 16 /* OnGetLegendRect */, OnGetTChartLegendRect, VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4)
	ON_EVENT(CEsdAdvancedGraphCtrl, ID_TCHART, 18 /* OnGetNextAxisLabel */, OnGetTChartNextAxisLabel, VTS_I4 VTS_I4 VTS_PR8 VTS_PBOOL)
	ON_EVENT(CEsdAdvancedGraphCtrl, ID_TCHART, 19 /* OnMouseDown */, OnTChartMouseDown, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CEsdAdvancedGraphCtrl, ID_TCHART, 20 /* OnMouseMove */, OnTChartMouseMove, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CEsdAdvancedGraphCtrl, ID_TCHART, 21 /* OnMouseUp */, OnTChartMouseUp, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CEsdAdvancedGraphCtrl, ID_TCHART, 22 /* OnPageChange */, OnTChartPageChange, VTS_NONE)
	ON_EVENT(CEsdAdvancedGraphCtrl, ID_TCHART, 23 /* OnResize */, OnResizeTChart, VTS_NONE)
	ON_EVENT(CEsdAdvancedGraphCtrl, ID_TCHART, 24 /* OnScroll */, OnScrollTChart, VTS_NONE)
	ON_EVENT(CEsdAdvancedGraphCtrl, ID_TCHART, 26 /* OnUndoZoom */, OnUndoZoomTChart, VTS_NONE)
	ON_EVENT(CEsdAdvancedGraphCtrl, ID_TCHART, 27 /* OnZoom */, OnZoomTChart, VTS_NONE)
	ON_EVENT(CEsdAdvancedGraphCtrl, ID_TCHART, 29 /* OnBeforeDrawSeries */, OnBeforeDrawTChartSeries, VTS_NONE)
	ON_EVENT(CEsdAdvancedGraphCtrl, ID_TCHART, 30 /* OnBeforeDrawAxes */, OnBeforeDrawTChartAxes, VTS_NONE)
	ON_EVENT(CEsdAdvancedGraphCtrl, ID_TCHART, 31 /* OnTimerTChart */, OnTChartTimer, VTS_NONE) 
	ON_EVENT(CEsdAdvancedGraphCtrl, ID_TCHART, 35 /*OnSeriesAfterDrawValues*/, OnTChartSeriesAfterDrawValues, VTS_I4)//11/10
	ON_EVENT(CEsdAdvancedGraphCtrl, ID_TCHART, 36 /*OnSeriesBeforeDrawValues*/, OnTChartSeriesBeforeDrawValues,VTS_I4) //11/10
	ON_EVENT(CEsdAdvancedGraphCtrl, ID_TCHART, 40 /*OnCursorToolChange*/,OnTChartCursorToolChange, VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_I4 VTS_I4)
	ON_EVENT(CEsdAdvancedGraphCtrl, ID_TCHART, 45 /*OnSeriesBeforeAdd*/, OnTChartSeriesBeforeAdd, VTS_I4 VTS_PBOOL)//11/10
	ON_EVENT(CEsdAdvancedGraphCtrl, ID_TCHART, 201/*OnMouseEnterSeries*/,OnMouseEnterTChartSeries,VTS_I4) //11/10
	ON_EVENT(CEsdAdvancedGraphCtrl, ID_TCHART, 202/*OnMouseLeaveSeries*/,OnMouseLeaveTChartSeries,VTS_I4) //11/10
	ON_EVENT(CEsdAdvancedGraphCtrl, ID_TCHART, 212 /*OnKeyDown*/, OnTChartKeyDown, VTS_I4 VTS_I4)
	ON_EVENT(CEsdAdvancedGraphCtrl, ID_TCHART, 213 /*OnKeyUp*/  , OnTChartKeyUp  , VTS_I4 VTS_I4) //11/10
	ON_EVENT(CEsdAdvancedGraphCtrl, ID_TCHART, 234 /*OnSeriesAfterAdd*/, OnTChartSeriesAfterAdd,VTS_I4 VTS_I4)//11/10
	ON_EVENT(CEsdAdvancedGraphCtrl, ID_TCHART, 32 /*OnGetSeriesMarks*/, OnGetTChartSeriesMarks, VTS_I4 VTS_I4 VTS_PBSTR)

END_EVENTSINK_MAP()

BEGIN_DISPATCH_MAP(CEsdAdvancedGraphCtrl, COleControl)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "AddGraph", dispidAddGraph, AddGraph, VT_I4, VTS_BSTR VTS_I4)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "AddDataPoint", dispidAddDataPoint, AddDataPoint, VT_EMPTY, VTS_I4 VTS_R8 VTS_R8)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "InterPolateData", dispidInterPolateData, InterPolateData, VT_EMPTY, VTS_I4 VTS_R8)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "AddDataPoints", dispidAddDataPoints, AddDataPoints, VT_EMPTY, VTS_I4 VTS_I4 VTS_VARIANT VTS_VARIANT)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "ModifyDataPoint", dispidModifyDataPoint, ModifyDataPoint, VT_EMPTY, VTS_I4 VTS_I4 VTS_R8 VTS_R8)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "DrawMultiColorGraph", dispidDrawMultiColorGraph, DrawMultiColorGraph, VT_EMPTY, VTS_I4 VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_I4)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "SetGraphPointColor", dispidSetGraphPointColor, SetGraphPointColor, VT_EMPTY, VTS_I4 VTS_I4 VTS_COLOR)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "RemoveDataPoint", dispidRemoveDataPoint, RemoveDataPoint, VT_BOOL, VTS_I4 VTS_I4)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "RemoveGraph", dispidRemoveGraph, RemoveGraph, VT_EMPTY, VTS_I4)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "RemoveAllGraphs", dispidRemoveAllGraphs, RemoveAllGraphs, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "SetGraphtype", dispidSetGraphtype, SetGraphtype, VT_EMPTY, VTS_I4 VTS_UI2)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "SetGraphVisible", dispidSetGraphVisible, SetGraphVisible, VT_EMPTY, VTS_I4 VTS_BOOL)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "ModifyLegends", dispidModifyLegends, ModifyLegends, VT_BOOL, VTS_I4 VTS_BSTR VTS_COLOR)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "StartOnlinePeakDetection", dispidStartOnlinePeakDetection, StartOnlinePeakDetection, VT_BOOL, VTS_NONE)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "StopOnlinePeakDetection", dispidStopOnlinePeakDetection, StopOnlinePeakDetection, VT_BOOL, VTS_NONE)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "StartOfflinePeakDetection", dispidStartOfflinePeakDetection, StartOfflinePeakDetection, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "StopOfflinePeakDetection", dispidStopOfflinePeakDetection, StopOfflinePeakDetection, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "StartAnimation", dispidStartAnimation, StartAnimation, VT_EMPTY, VTS_BOOL)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "GetControlUnknown", dispidGetControlUnknown, GetControlUnknown, VT_UNKNOWN, VTS_NONE)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "CopyGraph", dispidCopyGraph, CopyGraph, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "CopyData", dispidCopyData, CopyData, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "ExportGraphData", dispidExportGraphData, ExportGraphData, VT_BOOL, VTS_I4 VTS_I4 VTS_BOOL VTS_BOOL VTS_BOOL)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "CalculateTrendLine", dispidCalculateTrendLine, CalculateTrendLine, VT_EMPTY, VTS_I4 VTS_I4 VTS_BOOL VTS_I4)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "FindLinearCoefficients", dispidFindLinearCoefficients, FindLinearCoefficients, VT_BOOL, VTS_I4 VTS_VARIANT VTS_VARIANT VTS_PR8 VTS_PR8)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "FindQuadraticCoefficients", dispidFindQuadraticCoefficients, FindQuadraticCoefficients, VT_BOOL, VTS_I4 VTS_VARIANT VTS_VARIANT VTS_PR8 VTS_PR8 VTS_PR8)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "LinearCoefficients", dispidLinearCoefficients, LinearCoefficients, VT_BOOL, VTS_I4 VTS_PR8 VTS_PR8)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "QuadraticCoefficients", dispidQuadraticCoefficients, QuadraticCoefficients, VT_BOOL, VTS_I4 VTS_PR8 VTS_PR8 VTS_PR8)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "LinearFitX", dispidLinearFitX, LinearFitX, VT_EMPTY, VTS_I4 VTS_R8 VTS_R8 VTS_PR8 VTS_PR8)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "QuadraticFitX", dispidQuadraticFitX, QuadraticFitX, VT_EMPTY, VTS_I4 VTS_R8 VTS_R8 VTS_R8 VTS_PR8 VTS_PR8)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "GetPeakInfo", dispidGetPeakInfo, GetPeakInfo, VT_EMPTY, VTS_I4 VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "GetPeakIndexes", dispidGetPeakIndexes, GetPeakIndexes, VT_I4, VTS_I4 VTS_I4 VTS_PVARIANT)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "PeakFillArea", dispidPeakFillArea, PeakFillArea, VT_EMPTY, VTS_I4)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "DrawBaseLine", dispidDrawBaseLine, DrawBaseLine, VT_EMPTY, VTS_I4)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "BaseLineType", dispidBaseLineType, GetBaseLineType, SetBaseLineType, VT_I4)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "BaseLineColor", dispidBaseLineColor, GetBaseLineColor, SetBaseLineColor, VT_COLOR)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "GetNumberOfGraphs", dispidGetNumberOfGraphs, GetNumberOfGraphs, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "GetAllGraphIDs", dispidGetAllGraphIDs, GetAllGraphIDs, VT_I4, VTS_PVARIANT)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "PeakFillColor", dispidPeakFillColor, GetPeakFillColor, SetPeakFillColor, VT_COLOR)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "PeakMinArea", dispidPeakMinArea, GetPeakMinArea, SetPeakMinArea, VT_R8)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "PeakMinHeight", dispidPeakMinHeight, GetPeakMinHeight, SetPeakMinHeight, VT_R8)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "PeakMinWidth", dispidPeakMinWidth, GetPeakMinWidth, SetPeakMinWidth, VT_R8)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "GetPeaksCount", dispidGetPeaksCount, GetPeaksCount, VT_EMPTY, VTS_PVARIANT)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "DisplayTextAt", dispidDisplayTextAt, DisplayTextAt, VT_EMPTY, VTS_I4 VTS_BSTR VTS_R8 VTS_R8)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "BackGroundColor", dispidBackGroundColor, GetBackGroundColor, SetBackGroundColor, VT_COLOR)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "CustomTextColor", dispidCustomTextColor, GetCustomTextColor, SetCustomTextColor, VT_COLOR)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "CustomTextBackColor", dispidCustomTextBackColor, GetCustomTextBackColor, SetCustomTextBackColor, VT_COLOR)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "AxesMarkingColor", dispidAxesMarkingColor, GetAxesMarkingColor, SetAxesMarkingColor, VT_COLOR)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "ShowLegend", dispidShowLegend, GetShowLegends, SetShowLegends, VT_BOOL)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "GetGraphData", dispidGetGraphData, GetGraphData, VT_I4, VTS_I4 VTS_PVARIANT VTS_PVARIANT)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "GetGraphDataAt", dispidGetGraphDataAt, GetGraphDataAt, VT_EMPTY, VTS_I4 VTS_I4 VTS_PR8 VTS_PR8)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "GetGraphDataCont", dispidGetGraphDataCont, GetGraphDataCont, VT_I4, VTS_I4)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "GetGraphMinMax", dispidGetGraphMinMax, GetGraphMinMax, VT_EMPTY, VTS_I4 VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "BackImage", dispidBackImage, GetBackImage, SetBackImage, VT_BSTR)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "GetGraphPeaksCount", dispidGetGraphPeaksCount, GetGraphPeaksCount, VT_I4, VTS_I4)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "PrintGraph", dispidPrintGraph, PrintGraph, VT_EMPTY, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "PrintPreview", dispidPrintPreview, PrintPreview, VT_EMPTY, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "EnableHorzDatumLine", dispidEnableHorzDatumLine, GetEnableHorzDatumLine, SetEnableHorzDatumLine, VT_BOOL)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "EnableVericalDatumLine", dispidEnableVericalDatumLine, GetEnableVericalDatumLine, SetEnableVericalDatumLine, VT_BOOL)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "DrawDatumLine", dispidDrawDatumLine, DrawDatumLine, VT_EMPTY, VTS_I4 VTS_R8 VTS_R8 VTS_COLOR)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "ZoomDirection", dispidZoomDirection, GetZoomDirection, SetZoomDirection, VT_I4)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "EnableZoom", dispidEnableZoom, GetEnableZoom, SetEnableZoom, VT_BOOL)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "MouseButtonForZoom", dispidMouseButtonForZoom, GetMouseButtonForZoom, SetMouseButtonForZoom, VT_I4)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "MinimumPixelsForZoom", dispidMinimumPixelsForZoom, GetMinimumPixelsForZoom, SetMinimumPixelsForZoom, VT_I4)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "ScrollDirection", dispidScrollDirection, GetScrollDirection, SetScrollDirection, VT_I4)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "MouseButtonForScroll", dispidMouseButtonForScroll, GetMouseButtonForScroll, SetMouseButtonForScroll, VT_I4)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "FindPeaks", dispidFindPeaks, FindPeaks, VT_I4, VTS_VARIANT VTS_I4 VTS_I4 VTS_PVARIANT)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "ShowHeader", dispidShowHeader, GetShowHeader, ShowHeader, VT_BOOL)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "Header", dispidHeader, GetHeader, SetHeader, VT_BSTR)


	DISP_PROPERTY_PARAM_ID(CEsdAdvancedGraphCtrl, "AxesMarkingPrecision", dispidAxesMarkingPrecision, GetAxesMarkingPrecision, SetAxesMarkingPrecision, VT_I2, VTS_I4)
	DISP_PROPERTY_PARAM_ID(CEsdAdvancedGraphCtrl, "Axestitle", dispidAxestitle, GetAxestitle, SetAxestitle, VT_BSTR, VTS_I4)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "EntireGraph", dispidEntireGraph, EntireGraph, VT_BOOL, VTS_I4)
	DISP_PROPERTY_PARAM_ID(CEsdAdvancedGraphCtrl, "AxisMaximum", dispidAxisMaximum, GetAxisMaximum, SetAxisMaximum, VT_R8, VTS_I4)
	DISP_PROPERTY_PARAM_ID(CEsdAdvancedGraphCtrl, "AxesTitlesColor", dispidAxesTitlesColor, GetAxesTitlesColor, SetAxesTitlesColor, VT_COLOR, VTS_I4)
	DISP_PROPERTY_PARAM_ID(CEsdAdvancedGraphCtrl, "AxisMinimum", dispidAxisMinimum, GetAxisMinimum, SetAxisMinimum, VT_R8, VTS_I4)
	DISP_PROPERTY_PARAM_ID(CEsdAdvancedGraphCtrl, "AxisGridColor", dispidAxisGridColor, GetAxisGridColor, SetAxisGridColor, VT_COLOR, VTS_I4)
	DISP_PROPERTY_PARAM_ID(CEsdAdvancedGraphCtrl, "AxisGridStyle", dispidAxisGridStyle, GetAxisGridStyle, SetAxisGridStyle, VT_I2, VTS_I4)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "ShowPeaks", dispidShowPeaks, ShowPeaks, VT_BOOL, VTS_I4 VTS_I2)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "HidePeaks", dispidHidePeaks, HidePeaks, VT_BOOL, VTS_I4)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "ShowDataAtPeak", dispidShowDataAtPeak, GetShowDataAtPeak, SetShowDataAtPeak, VT_BOOL)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "CrossWire", dispidCrossWire, GetCrossWire, SetCrossWire, VT_BOOL)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "MoveCrossWireToFirst", dispidMoveCrossWireToFirst, MoveCrossWireToFirst, VT_BOOL, VTS_PI4 VTS_PI4)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "MoveCrossWireToLast", dispidMoveCrossWireToLast, MoveCrossWireToLast, VT_BOOL, VTS_PI4 VTS_PI4)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "MoveCrossWireToNext", dispidMoveCrossWireToNext, MoveCrossWireToNext, VT_BOOL, VTS_PI4 VTS_PI4 VTS_I2)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "MoveCrossWireToPrev", dispidMoveCrossWireToPrev, MoveCrossWireToPrev, VT_BOOL, VTS_PI4 VTS_PI4 VTS_I2)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "DisplayCrossWireAt", dispidDisplayCrossWireAt, DisplayCrossWireAt, VT_BOOL, VTS_R8 VTS_R8)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "SetCustomCrosswireText", dispidSetCustomCrosswireText, SetCustomCrosswireText, VT_EMPTY, VTS_BSTR VTS_BOOL VTS_R8)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "CrossWireDataPointIndex", dispidCrossWireDataPointIndex, GetCrossWireDataPointIndex, SetCrossWireDataPointIndex, VT_I4)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "Sort", dispidSort, GetSort, SetSort, VT_BOOL)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "AutoRange", dispidAutoRange, GetAutoRange, SetAutoRange, VT_BOOL)

	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "PerConc", dispidPerConc, GetPerConc, SetPerConc, VT_BOOL)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "ShowConcAtPeaks", dispidShowConcAtPeaks, GetShowConcAtPeaks, SetShowConcAtPeaks, VT_BOOL)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "ShowXTitle", dispidShowXTitle, GetShowXTitle, SetShowXTitle, VT_BOOL)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "ShowYTitle", dispidShowYTitle, GetShowYTitle, SetShowYTitle, VT_BOOL)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "SetLegendFont", dispidSetLegendFont, SetLegendFont, VT_EMPTY, VTS_BSTR VTS_I4)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "SetXYMarkingFont", dispidSetXYMarkingFont, SetXYMarkingFont, VT_EMPTY, VTS_BSTR VTS_I4)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "SetCustomTextFont", dispidSetCustomTextFont, SetCustomTextFont, VT_EMPTY, VTS_BSTR VTS_I4)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "XGrids", dispidXGrids, GetXGrids, SetXGrids, VT_I2)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "YGrids", dispidYGrids, GetYGrids, SetYGrids, VT_I2)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "ZoomIn", dispidZoomIn, ZoomIn, VT_BOOL, VTS_R8 VTS_R8 VTS_R8 VTS_R8)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "ZoomOut", dispidZoomOut, ZoomOut, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "SetHeaderFont", dispidSetHeaderFont, SetHeaderFont, VT_EMPTY, VTS_BSTR VTS_I4)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "SetAxesTitlesFont", dispidSetAxesTitlesFont, SetAxesTitlesFont, VT_EMPTY, VTS_BSTR VTS_I4)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "DisplayText", dispidDisplayText, DisplayText, VT_EMPTY, VTS_BSTR VTS_I4 VTS_I4)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "ClearCustomText", dispidClearCustomText, ClearCustomText, VT_EMPTY, VTS_NONE)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "PeakWidthCalculationType", dispidPeakWidthCalculationType, GetPeakWidthCalculationType, SetPeakWidthCalculationType, VT_I2)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "WidthAt5PercentHeight", dispidWidthAt5PercentHeight, WidthAt5PercentHeight, VT_EMPTY, VTS_I4 VTS_PR8 VTS_PR8 VTS_PR8)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "WidthAt10PercentHeight", dispidWidthAt10PercentHeight, WidthAt10PercentHeight, VT_EMPTY, VTS_I4 VTS_PR8 VTS_PR8 VTS_PR8)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "WidthAtHalfHeight", dispidWidthAtHalfHeight, WidthAtHalfHeight, VT_EMPTY, VTS_I4 VTS_PR8 VTS_PR8 VTS_PR8)
	//15/04/08
	//	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "AddCustomAxis", dispidAddCustomAxis, AddCustomAxis, VT_I4, VTS_BOOL)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "MoveAxisFromBasePosition", dispidMoveAxisFromBasePosition, MoveAxisFromBasePosition, VT_EMPTY, VTS_I4 VTS_I4 VTS_BOOL)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "ChangeAxisStartPosition", dispidChangeAxisStartPosition, ChangeAxisStartPosition, VT_EMPTY, VTS_I4 VTS_I4 VTS_BOOL)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "ChangeAxisEndPosition", dispidChangeAxisEndPosition, ChangeAxisEndPosition, VT_EMPTY, VTS_I4 VTS_I4 VTS_BOOL)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "AssignAxesForGraph", dispidAssignAxesForGraph, AssignAxesForGraph, VT_EMPTY, VTS_I4 VTS_I4 VTS_I4)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "RemoveCustomAxis", dispidRemoveCustomAxis, RemoveCustomAxis, VT_EMPTY, VTS_I4)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "RemoveAllCustomAxes", dispidRemoveAllCustomAxes, RemoveAllCustomAxes, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "AddCustomAxis", dispidAddCustomAxis, AddCustomAxis, VT_I4, VTS_BOOL)
	DISP_PROPERTY_PARAM_ID(CEsdAdvancedGraphCtrl, "CustomAxisTitle", dispidCustomAxisTitle, GetCustomAxisTitle, SetCustomAxisTitle, VT_BSTR, VTS_I4)
	DISP_PROPERTY_PARAM_ID(CEsdAdvancedGraphCtrl, "CustomAxisMaximum", dispidCustomAxisMaximum, GetCustomAxisMaximum, SetCustomAxisMaximum, VT_R8, VTS_I4)
	DISP_PROPERTY_PARAM_ID(CEsdAdvancedGraphCtrl, "CustomAxisMinimum", dispidCustomAxisMinimum, GetCustomAxisMinimum, SetCustomAxisMinimum, VT_R8, VTS_I4)
	DISP_PROPERTY_PARAM_ID(CEsdAdvancedGraphCtrl, "CustomAxisGrids", dispidCustomAxisGrids, GetCustomAxisGrids, SetCustomAxisGrids, VT_I4, VTS_I4)
	DISP_PROPERTY_PARAM_ID(CEsdAdvancedGraphCtrl, "CustomAxisTitleAngle", dispidCustomAxisTitleAngle, GetCustomAxisTitleAngle, SetCustomAxisTitleAngle, VT_I4, VTS_I4)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "DoGraphReprocess", dispidDoGraphReprocess, DoGraphReprocess, VT_EMPTY, VTS_PUI1 VTS_I4)
	DISP_PROPERTY_EX_ID(CEsdAdvancedGraphCtrl, "PeakMinTreshold", dispidPeakMinTreshold, GetPeakMinTreshold, SetPeakMinTreshold, VT_R8)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "MarkStartnEndpts", dispidMarkStartnEndpts, MarkStartnEndpts, VT_EMPTY, VTS_I4)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "SetStartnEndptMarkingColor", dispidSetStartnEndptMarkingColor, SetStartnEndptMarkingColor, VT_EMPTY, VTS_COLOR)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "GetStartnEndptMarkingColor", dispidGetStartnEndptMarkingColor, GetStartnEndptMarkingColor, VT_COLOR, VTS_NONE)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "FindArea", dispidFindArea, FindArea, VT_EMPTY, VTS_I4 VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_I4 VTS_I4 VTS_PR8)
	DISP_FUNCTION_ID(CEsdAdvancedGraphCtrl, "GetArea", dispidGetArea, GetArea, VT_EMPTY, VTS_I4 VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_I4 VTS_I4 VTS_PR8)
	END_DISPATCH_MAP()



// Event map

BEGIN_EVENT_MAP(CEsdAdvancedGraphCtrl, COleControl)
	EVENT_CUSTOM_ID("OnAfterDraw", eventidOnAfterDraw, OnAfterDraw, VTS_NONE)
	EVENT_CUSTOM_ID("OnBeforeDrawSeries", eventidOnBeforeDrawSeries, OnBeforeDrawSeries, VTS_NONE)
	EVENT_CUSTOM_ID("OnBeforeDrawAxes", eventidOnBeforeDrawAxes, OnBeforeDrawAxes, VTS_NONE)
	EVENT_CUSTOM_ID("OnClick", eventidOnClick, OnClick, VTS_NONE)
	EVENT_CUSTOM_ID("OnClickAxis", eventidOnClickAxis, OnClickAxis, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	EVENT_CUSTOM_ID("OnClickBackground", eventidOnClickBackground, OnClickBackground, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	EVENT_CUSTOM_ID("OnClickLegend", eventidOnClickLegend, OnClickLegend, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	EVENT_CUSTOM_ID("OnClickSeries", eventidOnClickSeries, OnClickSeries, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	EVENT_CUSTOM_ID("OnDblClick", eventidOnDblClick, OnDblClick, VTS_NONE)
	EVENT_CUSTOM_ID("OnCursorToolChange", eventidOnCursorToolChange, OnCursorToolChange, VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_I4 VTS_I4)
	EVENT_CUSTOM_ID("OnKeyDown", eventidOnKeyDown, OnKeyDown, VTS_I4 VTS_I4)
	EVENT_CUSTOM_ID("OnKeyUp", eventidOnKeyUp, OnKeyUp, VTS_I4 VTS_I4)
	EVENT_CUSTOM_ID("OnMouseDown", eventidOnMouseDown, OnMouseDown, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	EVENT_CUSTOM_ID("OnMouseMove", eventidOnMouseMove, OnMouseMove, VTS_I4 VTS_I4 VTS_I4)
	EVENT_CUSTOM_ID("OnMouseUp", eventidOnMouseUp, OnMouseUp, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	EVENT_CUSTOM_ID("OnMouseEnterGraph", eventidOnMouseEnterGraph, OnMouseEnterGraph, VTS_I4)
	EVENT_CUSTOM_ID("OnMouseLeaveGraph", eventidOnMouseLeaveGraph, OnMouseLeaveGraph, VTS_I4)
	EVENT_CUSTOM_ID("OnResize", eventidOnResize, OnResize, VTS_NONE)
	EVENT_CUSTOM_ID("OnScroll", eventidOnScroll, OnScroll, VTS_NONE)
	EVENT_CUSTOM_ID("OnTimer", eventidOnTimer, OnTimer, VTS_NONE)
	EVENT_CUSTOM_ID("OnZoom", eventidOnZoom, OnZoom, VTS_NONE)
	EVENT_CUSTOM_ID("OnUndoZoom", eventidOnUndoZoom, OnUndoZoom, VTS_NONE)
	EVENT_CUSTOM_ID("OnGraphAfterAdd", eventidOnGraphAfterAdd, OnGraphAfterAdd, VTS_I4 VTS_I4)
	EVENT_CUSTOM_ID("OnGraphAfterDrawValues", eventidOnGraphAfterDrawValues, OnGraphAfterDrawValues, VTS_I4)
	EVENT_CUSTOM_ID("OnGraphBeforeAdd", eventidOnGraphBeforeAdd, OnGraphBeforeAdd, VTS_I4 VTS_PBOOL)
	EVENT_CUSTOM_ID("OnGraphBeforeDrawValues", eventidOnGraphBeforeDrawValues, OnGraphBeforeDrawValues, VTS_I4)
	EVENT_CUSTOM_ID("OnPageChange", eventidOnPageChange, OnPageChange, VTS_NONE)
	EVENT_CUSTOM_ID("OnGetLegendRect", eventidOnGetLegendRect, OnGetLegendRect, VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4)
	EVENT_CUSTOM_ID("OnOnPeakDetected", eventidOnPeakDetected, OnOnPeakDetected, VTS_NONE)
END_EVENT_MAP()



// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CEsdAdvancedGraphCtrl, 1)
PROPPAGEID(CEsdAdvancedGraphControlPropPage::guid)
END_PROPPAGEIDS(CEsdAdvancedGraphCtrl)



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CEsdAdvancedGraphCtrl, "ESDADVANCEDGRAPHCONTROL.EsdAdvancedGraphCtrl.1",
					   0xe98e4ed3, 0xc038, 0x4705, 0x8e, 0xab, 0x43, 0xad, 0x8a, 0x1b, 0x75, 0xab)



					   // Type library ID and version

					   IMPLEMENT_OLETYPELIB(CEsdAdvancedGraphCtrl, _tlid, _wVerMajor, _wVerMinor)



					   // Interface IDs

					   const IID BASED_CODE IID_DEsdAdvancedGraphControl =
{ 0x9117C567, 0x1EAD, 0x48B3, { 0xBA, 0x9E, 0xC4, 0xD4, 0x48, 0x52, 0xD1, 0x81 } };
const IID BASED_CODE IID_DEsdAdvancedGraphControlEvents =
{ 0x7A82910, 0x34BC, 0x43C2, { 0xAD, 0xAE, 0xA4, 0x62, 0x28, 0x6D, 0x4E, 0x10 } };



// Control type information

static const DWORD BASED_CODE _dwEsdAdvancedGraphControlOleMisc =
OLEMISC_ACTIVATEWHENVISIBLE |
OLEMISC_SETCLIENTSITEFIRST |
OLEMISC_INSIDEOUT |
OLEMISC_CANTLINKINSIDE |
OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CEsdAdvancedGraphCtrl, IDS_AXWRAPPER1, _dwEsdAdvancedGraphControlOleMisc)



// CEsdAdvancedGraphCtrl::CEsdAdvancedGraphCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CEsdAdvancedGraphCtrl

BOOL CEsdAdvancedGraphCtrl::CEsdAdvancedGraphCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.
	if (bRegister)
		return AfxOleRegisterControlClass(
		AfxGetInstanceHandle(),
		m_clsid,
		m_lpszProgID,
		IDS_AXWRAPPER1,
		IDB_AXWRAPPER1,
		afxRegApartmentThreading,
		_dwEsdAdvancedGraphControlOleMisc,
		_tlid,
		_wVerMajor,
		_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CEsdAdvancedGraphCtrl::CEsdAdvancedGraphCtrl - Constructor

CEsdAdvancedGraphCtrl::CEsdAdvancedGraphCtrl()
{
	InitializeIIDs(&IID_DEsdAdvancedGraphControl, &IID_DEsdAdvancedGraphControlEvents);
	// TODO: Initialize your control's instance data here.

	//m_xInnerUnknown=0;

	//	m_bWindowOnly				     = TRUE;	
	m_bShowLegends				     = TRUE;
	m_bSortPoints				     = TRUE;
	m_bFirstXYvalue					 = TRUE;	
	/*	m_bZoomRestore					 = TRUE;	//Commented on 23/11/07 by Silpa
	m_bIsZoomable					 = FALSE;
	m_bLockZoom						 = FALSE;
	m_bSaveLockZoomStateForAutoRange = TRUE;
	m_bTrackingZoomArea				 = FALSE;
	m_bShowZeroAxes					 = FALSE;
	m_bShowHeader					 = FALSE;
	m_bShowMarking					 = TRUE;
	m_bIsPrinting					 = FALSE;
	m_bCopyGraph					 = FALSE;
	m_bHasMoreThanTwoPoints			 = FALSE;	
	m_bIsMousePtInGraph				 = FALSE;
	m_bIsPaning						 = FALSE;	
	m_bLButtonPressed				 = FALSE;
	m_bCanRemoveLastZoomState	=	FALSE;
	*/	// Commented on 23/11/07 by Silpa

	m_bAutoRangeEnable				 = FALSE;
	m_bShowXTitle					 = TRUE;
	m_bShowYTitle					 = TRUE;
	//	m_blnLockXYLimits				 = FALSE;//
	//	m_bIsPeakFillEnable              =FALSE;    //ss
	//	m_bIsBaseLineDraw                =FALSE;   //ss

	//	m_bPrintMode = FALSE;		//Commented on 23/11/07 by Silpa23/11

	m_dblXmin		= m_dblMinOfXmin	= 0;
	m_dblXmax		= m_dblMaxOfXmax	= 100;
	m_dblYmin		= m_dblMinOfYmin	= 0;
	m_dblYmax		= m_dblMaxOfYmax	= 100;

	/*m_dblXCurPos	= 0;
	m_dblYCurPos    = 0;*/	// Commented on 23/11/07 by Silpa

	m_intXPrecision			 = 2;
	m_intYPrecision			 = 2;
	m_intGraphType			 = 0;
	m_intCounterForGraphsPeaks = 0;
	m_intXNumOfGrids		 = 5;	
	m_intYNumOfGrids		 = 5;	

	/*m_intGridStyle		 = 0;	//Commented on 23/11/07 by Silpa	
	m_intZeroAxesStyle		 = 0;
	m_intBackgroundStyle	 = 0;
	m_intPlotAreaStyle		 = 0;
	m_intBorderStyle		 = 0;
	m_intPlotAreaBorderStyle = 0;
	m_intDefaultPointStyle	 = 0;

	m_strHeader				 = "";*/	// Commented on 23/11/07 by Silpa

	m_strXAxisTitle			 = "";
	m_strYAxisTitle			 = "";

	m_clrBackColor			= RGB(255,255,255);
	m_clrCustomTextBackColor = RGB(255,255,255); 
	m_clrGridColor			= RGB(200,200,200);		
	m_clrZeroAxesColor		= 0;
	m_clrCustomTextColor	= 0;
	m_clrTitlesColor		= 0;	
	m_clrMarkingColor		= 0;		

	//	m_objSamples = new CArray<struct EsdGRAPH_STRUCT*,struct EsdGRAPH_STRUCT*>;

	m_bCanUpdateMinMax	= FALSE;

	///// Cross Wire variables /////////////////
	m_bShowCrossWire	=	FALSE;

	bForcedpeak         =   FALSE;

	blnManualPeak   =  FALSE;

	m_ptCrossWirePos.x  =	0;
	m_ptCrossWirePos.y	=	0;

	m_ptStartEndPos.x = 0;
	m_ptStartEndPos.y = 0;



	m_intCrossWireGraphID = -1;
	m_lngCrossWireDataPointIndex = -1;	
	m_lngManualBaselineStartPointIndex = -1;
	m_lngManualBaselineEndPointIndex = -1;
	m_bFirstTimeCrossWire = TRUE;	
	m_bClickEvent = FALSE;

	m_bShowDataAtPeak		=	FALSE;

	m_blnHideXYValues = FALSE;

	m_dblconcentration	=	0.0;
	//////////////// end of Cross wire variables //////

	m_dblMinArea = 0;
	m_dblMinHeight = 0;
	m_dblMinWidth = 0;
	m_dblMinPeakThreshold=0;
	m_dblAverageNoise = 0;
	m_blnDetectNegativePeaksAlso = FALSE;

	m_intBaseLineType = 1;	// Point - Point Base Line


	m_blnOnlinePeakDetection = FALSE;
	m_blnOfflinePeakDetection = FALSE;

	m_lngXmin	=	0;
	m_lngXmax	=	0;
	m_lngYmin	=	0;
	m_lngYmax	=	0;

	/*	m_intPeakFillStyle = 0;
	m_blnDrawingBaseLine = FALSE;	//Commented on 23/11/07 by Silpa
	m_dblBaseLineStartX = 0.0;
	m_dblBaseLineStartY = 0.0;
	m_dblBaseLineEndX   = 0.0;
	m_dblBaseLineEndY   = 0.0;
	m_blnCustomBaseLineDrawn = FALSE;	
	m_blnShowPeakData = FALSE;	
	m_blnPeakWindowDisplayed = FALSE;*/	//Commented on 23/11/07 by Silpa

	m_dblBaseLineLevel = 0;

	m_clrPeakFillColor = 0;
	m_clrBaseLineColor = 0;
	m_clrStartnEndMarking = 0;

	m_blnLockBaseLine		=	FALSE;

	m_objPeakInfo			=	NULL;
	//m_objPeakInfo           =   NULL;
	m_objTangentPeakInfo    =   NULL;

	m_intPeakWidthCalType	=	1;

	//	nCustomTextIdx=-1;			//ss 10/09/07
	blnCustomText		=	FALSE;
	m_strBackImage		=	_T("");			//	Silpa 12/09/07
	m_blnLinearFit		=	FALSE;			//	Silpa 12/09/07
	m_blnQuadraticFit	=	FALSE;		//	Silpa 12/09/07
	m_blnLogFit			=	FALSE;
	m_blnExpFit			=	FALSE;
	m_blnPowerFit		=	FALSE;
	blnHorzDatumLine	=	FALSE;	//	Silpa on 04/10/07
	blnVertDatumLine	=	FALSE;	//	silpa on 04/10/07

	m_bPerConc			=	FALSE;	// SpectraTreatz
	m_bShowConcAtPeak	= FALSE; // Spectratreatz 

	//Bharath.
	m_bMarkStartnEndPoints = FALSE;
	//Added to avoid the problem in peak detection while debugging.
	m_lngNoOfDataPoints = 0;

	m_lngSize=0;
	m_nManualPeakindex=-1;

}


// CEsdAdvancedGraphCtrl::~CEsdAdvancedGraphCtrl - Destructor

CEsdAdvancedGraphCtrl::~CEsdAdvancedGraphCtrl()
{
	// TODO: Cleanup your control's instance data here.
#ifdef _TCHART_LOG
	WriteTChartLog("After Entering into TChart Destructor \n");
#endif
	m_arrGraphRelatedSerieses.RemoveAll();
	m_arrGraphRelatedSerieses.FreeExtra();
	//AfxMessageBox(_T("Ctrl Destrutor"));
#ifdef _TCHART_LOG
	WriteTChartLog("Before leaving Teechart Wrapper Destructor \n");
#endif
}



// CEsdAdvancedGraphCtrl::OnDraw - Drawing function

void CEsdAdvancedGraphCtrl::OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}

// CEsdAdvancedGraphCtrl::DoPropExchange - Persistence support

void CEsdAdvancedGraphCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.
}



// CEsdAdvancedGraphCtrl::GetControlFlags -
// Flags to customize MFC's implementation of ActiveX controls.
//
DWORD CEsdAdvancedGraphCtrl::GetControlFlags()
{
	DWORD dwFlags = COleControl::GetControlFlags();
	// The control will not be redrawn when making the transition
	// between the active and inactivate state.
	dwFlags |= noFlickerActivate;
	return dwFlags;
}

// CEsdAdvancedGraphCtrl::OnResetState - Reset control to default state

void CEsdAdvancedGraphCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange


	// TODO: Reset any other control state here.
}

// CEsdAdvancedGraphCtrl message handlers

int CEsdAdvancedGraphCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  Add your specialized creation code here

	CLSID clsid;
	clsid	=	m_chart.GetClsid();
	if((m_chart.CreateControl(clsid,NULL,WS_CHILD|WS_VISIBLE,CRect(0,0,100,100),this,ID_TCHART))==FALSE)
	{
		MessageBox(_T("Control not created"),NULL,0);
		return 0;
	}	

	LPDISPATCH pDisp	=	NULL;
	pDisp	=	m_chart.get_Aspect();
	IAspectPtr pAspect	=	pDisp;
	pDisp->Release();
	pAspect->View3D	=	FALSE;

	pDisp	=	m_chart.get_Header();
	ITitlesPtr pTitles	=	pDisp;
	pDisp->Release();
	pTitles->Visible	=	FALSE;

	pDisp	=	m_chart.get_Axis();
	IAxesPtr	pAxes	=	pDisp;
	pDisp->Release();

	_bstr_t	bstrPrecisionFormat	=	_T("0.00");	//By Default Axes marking Precision is Two.
	pAxes->GetLeft()->GetLabels()->ValueFormat		=	bstrPrecisionFormat;
	pAxes->GetBottom()->GetLabels()->ValueFormat	=	bstrPrecisionFormat;

	pAspect	=	NULL;
	pTitles	=	NULL;
	pAxes	=	NULL;
	return 1;
}

void CEsdAdvancedGraphCtrl::OnSize(UINT nType, int cx, int cy)
{
	COleControl::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if(m_chart)
		m_chart.MoveWindow(0,0,cx,cy,0);
}

//*************************************************
//PURPOSE : To add a new graph to the current list and return the newly added Graph ID.
//INPUTS  : LPCTSTR strTitle - Graph title 
//			long clrColor    -    Color for this Graph
//ASSUMES : -
//RETURNS : LONG			 -  Graph ID.
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
LONG CEsdAdvancedGraphCtrl::AddGraph(LPCTSTR strName, LONG lngColor)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	//stuGraphdata obj;
	long lngGraphID	=	-1;
	CString str=strName;
	BSTR bstr;
	LPDISPATCH pDisp	=	NULL;
	if(m_chart)
	{
		//lngGraphID=m_chart.AddSeries(scLine);
		lngGraphID=m_chart.AddSeries(scLine);
		if(lngGraphID>=0)
		{
			pDisp	=	m_chart.get_Aspect();
			IAspectPtr	pAspect	=	pDisp;
			pDisp->Release();
			pAspect->put_View3D(FALSE);

			pDisp	=	m_chart.Series(lngGraphID);
			ISeriesPtr	pSeries	=	pDisp;
			pDisp->Release();
			pSeries->put_Color(lngColor);

			//if(pSeries->SeriesType	==	scLine)
			//{
			////	pSeries->GetasLine()->GetPointer()->Visible	=	TRUE;
			//	pSeries->GetasLine()->GetPointer()->Style	=	psCircle;
			//}
			IMarksPtr	pMarks	=	pSeries->Marks; // To display the values at each point of graph(Used in Custom text display)
			pMarks->Visible	=TRUE;
			//pMarks->Clip	=	TRUE;
			pMarks->Transparent	=	TRUE;
			//pMarks->Multiline	=	TRUE;
			((IPen*)(pMarks->Arrow))->Color	=	RGB(0,0,0);
			((IPen*)(pMarks->Arrow))->Width	=	2;	
			//pMarks->ArrowLength	=	18;

			bstr=str.AllocSysString();
			pSeries->put_Title(bstr);
			SysFreeString(bstr);

			//((ILineSeries*)((ISeries *)(m_chart.Series(lngGraphID)))->get_asLine())->Stacked(1);
			pDisp	=	m_chart.get_Legend();
			ILegendPtr	pLegend	=	pDisp;
			pDisp->Release();
			pLegend->put_LegendStyle(lsSeries);	// It displays the Names of the graphs in the Legend .

			//// To remove All Series related to one particular series while removing this particular one 
			stuRemovableGraphData temp ;//= new stuRemovableGraphData;	
			CComBSTR bstrNull(_T(""));
			temp.bstrGraphName=	pSeries->GetName().copy();	
			//SysFreeString(bstrTemp);
			temp.bsrLinearfitName=bstrNull.Copy();
			temp.bstrBaseLinename=bstrNull.Copy();
			temp.bstrFillName=bstrNull.Copy();
			temp.bstrQuadraticFitName=bstrNull.Copy();
			temp.bstrCustomTrendLineName=bstrNull.Copy();

			temp.bstrLogFit		=	bstrNull.Copy();
			temp.bstrPowerFit	=	bstrNull.Copy();
			temp.bstrExpFit		=	bstrNull.Copy();

			temp.bShowPeaks		=	FALSE;
			temp.intPeakLevel	=	0;
			m_arrGraphRelatedSerieses.Add(temp);
			m_lngSize=0;
			bstrNull.Detach();


			// /////////////
			pMarks	=	NULL;
			pAspect	=	NULL;
			pSeries	=	NULL;
			pLegend	=	NULL;
		}
		return lngGraphID;
	}
	else
		return -1;

}
//*************************************************
//PURPOSE : To add a new data point to the graph specified by the ID and plot it.
//INPUTS  : long intGraphID   - Graph ID 
//			double dblXval -  X coord value
//			double dblYval -  Y coord value
//ASSUMES : -
//RETURNS : 
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::AddDataPoint(LONG lngGraphIdx, DOUBLE dblXval, DOUBLE dblYval)
{
	if(lngGraphIdx<0 || lngGraphIdx >=m_chart.get_SeriesCount())  // Make sure that data point which is to be added to the Graph specified 
	{                                         // GraphID exists or not.
		MessageBox(_T("Graph with specified ID doesn't exists"),NULL,0);
		return ;//Error(_T("Graph with specified ID doesn't exists"));
	} 		
	else
	{		
		LPDISPATCH pDisp	=	NULL;
		pDisp	=	m_chart.Series(lngGraphIdx);
		ISeriesPtr	pSeries	=	pDisp;
		//IFastLineSeriesPtr pSeries=pDisp;
		pDisp->Release();



		_bstr_t bstrGraphName=pSeries->GetName().copy();
		long LTblIdx=GetLtblIdxFromName(bstrGraphName);
		if(LTblIdx<0)
		{
			MessageBox(_T("Graph with this index doesn't exist"));
			return;
		}  

		if(m_blnOnlinePeakDetection)    // If Peak detection is Performed on Graph then store that Graph Name.It is used to retrieve the 
		{								// Peak values of the specified Graph
			// Store the Graph name for which Peak detection is going to be performed
			m_objPeakInfo->strGraphName = bstrGraphName.copy();
			m_GraphPeaks.SetAt((m_GraphPeaks.GetSize()-1),m_objPeakInfo);
		}

		if(!m_bSortPoints) //Sorting values is disabled 
			pSeries->GetXValues()->Order	=	loNone;


		if(m_blnOnlinePeakDetection == TRUE)
		{
			ProcessPtForPeakDetection(dblXval, dblYval);	
		}
		pSeries->AddXY(dblXval,dblYval,_T(""),clTeeColor);
		pSeries	=	NULL;	
		if(m_bFirstXYvalue)                             // If this is the first data point then 
		{
			m_dblMinOfXmin = m_dblMaxOfXmax = dblXval;  // store the first data point in  min. & max. variables.
			m_dblMinOfYmin = m_dblMaxOfYmax = dblYval;
			m_bFirstXYvalue = FALSE;
		}
		else                                            // Or Else compare the data point with min. & max. values 
		{
			if(dblXval<m_dblMinOfXmin)                  // and accordingly update the min. & max. values.
				m_dblMinOfXmin = dblXval;
			if(dblXval>m_dblMaxOfXmax)
				m_dblMaxOfXmax = dblXval;
			if(dblYval<m_dblMinOfYmin)
				m_dblMinOfYmin = dblYval;
			if(dblYval>m_dblMaxOfYmax)
				m_dblMaxOfYmax = dblYval;

			//			m_bHasMoreThanTwoPoints = TRUE;				// Used in Auto Range.	// Commented on 23/11/07 by Silpa

		}
	}
}
//*************************************************
//PURPOSE : Method to add the more than one Data Point(s)
//INPUTS  : long intGraphID		-	Graph ID
//			long lngNumOfPoints	-	Number of Data Point(s)
//			double *dblXval		-	X values array
//			double *dblYval		-	Y values array
//ASSUMES : -
//RETURNS : 
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//----------------------------------------------
void CEsdAdvancedGraphCtrl::AddDataPoints(LONG lngGraphIDx, LONG lngNumOfPoints, VARIANT &varXVals, VARIANT &varYVals)
{
	m_lngNoOfDataPoints = lngNumOfPoints;

	if(lngGraphIDx > m_chart.get_SeriesCount()-1)  // Make sure that data point which is to be added to the Graph specified 
	{                                        // GraphID exists or not.
		MessageBox(_T("Graph with this specified ID doesn't exists"));//String Table
		return ;//Error(IDS_GRAPHID_DONOT_EXIST);//String Table
	} 		
	else if((varXVals.vt&VT_ARRAY && varXVals.vt&VT_R8)&& (varYVals.vt&VT_ARRAY && varYVals.vt&VT_R8))
	{
		LPDISPATCH pDisp	=	NULL;
		pDisp	=	m_chart.Series(lngGraphIDx);
		ISeriesPtr	pSeries	=	pDisp;
		pDisp->Release();

		_bstr_t bstrGraphName	=	pSeries->GetName().copy();
		long LTblIdx=GetLtblIdxFromName(bstrGraphName);
		if(LTblIdx<0)
		{
			MessageBox(_T("Graph with this index doesn't exist"));
			return;
		}
		long lngLBound,lngUBound,lngResultBound;

		// The arrays created must be of the same size as the data count present in VARIANT's
		// If not it will give assertion in while retrieving data from VARIANT"s to Double in 'fncGetDoubleValuesFromSafeArry' function
		SafeArrayGetLBound(varXVals.parray,1,&lngLBound);
		SafeArrayGetUBound(varXVals.parray,1,&lngUBound);
		lngResultBound	=	lngUBound	-	lngLBound;
		double *dblTempXval= new double[lngResultBound+1]; // Allocate space for the new data points and store the values in them.		

		SafeArrayGetLBound(varYVals.parray,1,&lngLBound);
		SafeArrayGetUBound(varYVals.parray,1,&lngUBound);
		lngResultBound	=	lngUBound	-	lngLBound;
		double *dblTempYval= new double[lngResultBound+1];

		long lSize=fncGetDoubleValuesFromSafeArray(varXVals,dblTempXval);

		if(lngNumOfPoints>lSize)
			lngNumOfPoints=lSize;

		lSize=fncGetDoubleValuesFromSafeArray(varYVals,dblTempYval);

		if(lngNumOfPoints>lSize)
			lngNumOfPoints=lSize;

		if(m_blnOnlinePeakDetection)
		{
			m_objPeakInfo->strGraphName = bstrGraphName.copy();
			m_GraphPeaks.SetAt((m_GraphPeaks.GetSize()-1),m_objPeakInfo);
		}
		pSeries->AddArray(lngNumOfPoints,varYVals,varXVals);
		//if(!m_bSortPoints) //Sorting values is disabled 
		//	pSeries->GetXValues()->Order	=	loNone;

		/*for(long intIndex = 0; intIndex < lngNumOfPoints; intIndex++)
		{*/

		/*CString s;
		s.Format(_T("%ld"),m_lngSize);
		AfxMessageBox(s);*/
		for(long intIndex = m_lngSize; intIndex < lngNumOfPoints; intIndex++)
		{


			if(m_blnOnlinePeakDetection == TRUE)  //ss  06/01/07
			{	
				ProcessPtForPeakDetection(dblTempXval[intIndex], dblTempYval[intIndex]);
			}

			//pSeries->AddXY(dblTempXval[intIndex],dblTempYval[intIndex],_T(""),clTeeColor);			
			if(m_bFirstXYvalue)                             // If this is the first data point then 
			{
				m_dblMinOfXmin = m_dblMaxOfXmax = dblTempXval[intIndex];  // store the first data point in  min. & max. variables.
				m_dblMinOfYmin = m_dblMaxOfYmax = dblTempYval[intIndex];
				m_bFirstXYvalue = FALSE;
			}
			else                                            // Or Else compare the data point with min. & max. values 
			{					
				if(dblTempXval[intIndex] < m_dblMinOfXmin)                  // and accordingly update the min. & max. values.
					m_dblMinOfXmin = dblTempXval[intIndex];
				if(dblTempXval[intIndex] > m_dblMaxOfXmax)
					m_dblMaxOfXmax = dblTempXval[intIndex];
				if(dblTempYval[intIndex] < m_dblMinOfYmin)
					m_dblMinOfYmin = dblTempYval[intIndex];
				if(dblTempYval[intIndex] > m_dblMaxOfYmax)
					m_dblMaxOfYmax = dblTempYval[intIndex];

				//				m_bHasMoreThanTwoPoints = TRUE;				// Used in Auto Range.	// Commented on 23/11/07 by Silpa
			}
		}
		/*CString s;
		s.Format(_T("%ld"),m_lngSize);
		AfxMessageBox(s);*/
		m_lngSize=lngNumOfPoints;
		pSeries	=	NULL;
		delete [] dblTempXval;
		delete [] dblTempYval;
	}	
	else
	{
		MessageBox(_T("values must send through SafeArrays"));
		return;
	}

}
//************************************************************
//PURPOSE : Method to start up the Peak Detection process(Data Analysis)
//			for a single Graph (Online Processing i.e processing data at 
//			the time of drawing the data on the Control)
//INPUTS  : 
//ASSUMES : StopOnlinePeakDetection() must also be called to restrict the 
//			other Graphs data analysys when we don't require
//RETURNS : VARIANT_BOOL 
//EFFECTS : 
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//------------------------------------------------------------
VARIANT_BOOL CEsdAdvancedGraphCtrl::StartOnlinePeakDetection(void)
{
	InitializePeakDetectionVariables();

	m_blnOnlinePeakDetection = TRUE;

	m_objPeakInfo = new stuPeakInfo;
	m_objTempPeakInfo = new stuPeakInfo;
	m_objTangentPeakInfo = new stuPeakInfo;

	if(m_objPeakInfo != NULL)
		m_GraphPeaks.Add(m_objPeakInfo);

	//To clear the arrays that store the various percentages of heights.

	m_dblWidthAt5PercentHeight.RemoveAll();
	m_dblLeftWidthAt5PercentHeight.RemoveAll();
	m_dblRightWidthAt5PercentHeight.RemoveAll();
	m_dblWidthAt10PercentHeight.RemoveAll();
	m_dblLeftWidthAt10PercentHeight.RemoveAll();
	m_dblRightWidthAt10PercentHeight.RemoveAll();
	m_dblWidthAtHalfHeight.RemoveAll();
	m_dblLeftWidthAtHalfHeight.RemoveAll();
	m_dblRightWidthAtHalfHeight.RemoveAll();

	//clearing the arrays completed.


	return VARIANT_TRUE;
}
//**************************************************************************
//PURPOSE : Method to stop the Online Peak detection Process(Data Analysis)
//INPUTS  : 
//ASSUMES : 
//RETURNS : 
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//----------------------------------------------
VARIANT_BOOL CEsdAdvancedGraphCtrl::StopOnlinePeakDetection(void)
{
	m_blnOnlinePeakDetection = FALSE;

	//	if(m_objPeakInfo != NULL)
	//		m_GraphPeaks.Add(m_objPeakInfo);
	m_objPeakInfo = NULL;
	m_objTempPeakInfo = NULL;
	delete m_objPeakInfo;
	delete m_objTempPeakInfo;


	//fncPerformIntegration();
	return VARIANT_TRUE;
}
//*****************************************************************************
//PURPOSE : Method to start up the Data analysis on all the Graphs at a time.
//INPUTS  : 
//ASSUMES : -
//RETURNS : 
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//------------------------------------------------------------------------------
void CEsdAdvancedGraphCtrl::StartOfflinePeakDetection(void)
{
	//m_blnOfflinePeakDetection = TRUE;

	////for (int i = 0; i<m_objSamples->GetSize(); i++ )
	////{
	////temp = m_objSamples->GetAt(i);      //ss 06/01/07

	//m_objPeakInfo = new stuPeakInfo;

	//InitializePeakDetectionVariables();

	////for(int j=0;j<temp->dblXval.GetSize();j++)		
	////ProcessPtForPeakDetection( *(temp->dblXval.GetAt(j)), *(temp->dblYval.GetAt(j)));
	//

	//if(m_objPeakInfo != NULL)
	//	m_GraphPeaks.Add(m_objPeakInfo);

	////	m_objPeakInfo = NULL;
	////}

	////	fncPerformIntegration();   //ss 06/01/07
	

	
	m_blnOfflinePeakDetection = TRUE;

	ClearPeakInformation();

	stuRemovableGraphData temp ;
	LPDISPATCH pDisp	=	NULL;

	for (int i = 0; i<m_arrGraphRelatedSerieses.GetSize(); i++ )
	{
		temp = m_arrGraphRelatedSerieses.GetAt(i);

		_bstr_t bstrGraphName(temp.bstrGraphName,TRUE);
		long lngIdx	=	GetGraphIdxFromName(bstrGraphName);
		if(lngIdx<0)
			continue;
		pDisp	=	m_chart.Series(lngIdx);
		ISeriesPtr pSeries	=	pDisp;
		pDisp->Release();

		m_objPeakInfo = new stuPeakInfo;
		m_objTempPeakInfo = new stuPeakInfo;//for temporory purpose store the peak info in another structure

		InitializePeakDetectionVariables();

		for(long j=0;j<pSeries->GetXValues()->Count;j++)		
			ProcessPtForPeakDetection( pSeries->GetXValues()->GetValue(j), pSeries->GetYValues()->GetValue(j));

		m_objPeakInfo->strGraphName	=	pSeries->GetName().copy();

		if(m_objPeakInfo != NULL)
			m_GraphPeaks.Add(m_objPeakInfo);

		m_objPeakInfo = NULL;
		pSeries	=	NULL;
	}
	fncPerformIntegration();
	

}
//*************************************************
//PURPOSE : Method to stop the Offline Data Analysis process
//INPUTS  : long intGraphID		-	Graph ID
//			long lngNumOfPoints	-	Number of Data Point(s)
//			double *dblXval		-	X values array
//			double *dblYval		-	Y values array
//ASSUMES : -
//RETURNS : 
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//----------------------------------------------
void CEsdAdvancedGraphCtrl::StopOfflinePeakDetection(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	m_blnOfflinePeakDetection = FALSE;
	ClearPeakInformation();
	InitializePeakDetectionVariables();
}
//*************************************************
//PURPOSE : Method to change the Legends i.e Graph name and Graph color
//			displayed on the Right side of the Graph control
//INPUTS  : long intGraphID         - Graph ID 
//			LPCTSTR strGraphName    - New Graph name to be displayed at the right side 
//			OLE_COLOR clrGraphColor - New Color to be displayed on right side and
//			also applied to the Graph drawn with the Specified index.
//ASSUMES : It assumes the Graph already drawn.
//RETURNS : VARIANT_BOOL
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
VARIANT_BOOL CEsdAdvancedGraphCtrl::ModifyLegends(LONG lngGraphIdx, LPCTSTR strGraphName, OLE_COLOR clrGraphColor)
{
	if(lngGraphIdx>=0 && lngGraphIdx<m_chart.get_SeriesCount())
	{
		LPDISPATCH pDisp	=	NULL;
		pDisp	=	m_chart.Series(lngGraphIdx);
		ISeriesPtr	pSeries	=	pDisp;
		pDisp->Release();
		_bstr_t bstrGraphName=(pSeries->GetName().copy());
		long LTblIdx=GetLtblIdxFromName(bstrGraphName);
		if(LTblIdx<0)
		{
			MessageBox(_T("Graph with this ID doesn't exist to modify the legends"));
			return VARIANT_FALSE;
		}

		CString str=strGraphName;
		BSTR bstr=str.AllocSysString();
		pSeries->put_Title(bstr);
		pSeries->put_Color(clrGraphColor);
		SysFreeString(bstr);

		pSeries	=	NULL;
		return VARIANT_TRUE;
	}
	else
	{
		MessageBox(_T("Graph with this index doesn't exist to modify the legends"));
		return VARIANT_FALSE;
	}
}
//*************************************************
//PURPOSE : Method to remove the data point of the drawn graph
//INPUTS  : long intGraphIdx   - Graph ID 
//			long lngPtIdx      - Index of the graph point which is to be remove
//ASSUMES : -
//RETURNS : VARIANT_BOOL --- Success or Failure of this Method
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------

VARIANT_BOOL CEsdAdvancedGraphCtrl::RemoveDataPoint(LONG lngGraphIdx, LONG lngPtIdx)
{
	if(lngGraphIdx>=0 && lngGraphIdx < m_chart.get_SeriesCount())			   // Check whether Graph exists or not.
	{
		LPDISPATCH pDisp	=	m_chart.Series(lngGraphIdx);
		ISeriesPtr	pSeries	=	pDisp;
		pDisp->Release();
		_bstr_t bstrGraphName=	pSeries->GetName().copy();
		long lngIdx=GetLtblIdxFromName(bstrGraphName);
		if(lngIdx<0)
		{
			MessageBox(_T("Graph with this specified ID doesn't exist"));
			pSeries	=	NULL;
			return VARIANT_FALSE;
		}
		if(lngPtIdx>=0 && lngPtIdx<pSeries->GetYValues()->GetCount())			   // Check whether data point exists or not.
		{					
			pSeries->Delete(lngPtIdx);
			m_bCanUpdateMinMax = TRUE;
		}				
		else
		{
			MessageBox(_T("Index value is beyond the range."));//String Table
			pSeries	=	NULL;
			return VARIANT_FALSE;//Error(IDS_INDEXVALUE_OUT_OF_RANGE);//String Table

		}		
		pSeries	=	NULL;
	}

	return VARIANT_TRUE;
}
//*************************************************
//PURPOSE : To draw the single graph with Multiple Colors 
//INPUTS  : LONG lngGraphIdx    - Graph ID 
//			LONG lngNoOfPoints  - Total Number of data points
//			LONG *lngColors		- Color Values 
//			double *dblXValues  - X Coord Values
//			double *dblYValues  - Y Coord Values
//			LONG lngPenWidth    - Width of the pen which is used to fill the Color
//ASSUMES : X,Y Coord values count and Color values count are equal
//RETURNS : 
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::DrawMultiColorGraph(LONG lngGraphIdx, LONG lngNoOfPoints,VARIANT &varLngColors, VARIANT &varDblXVals, VARIANT &varDblYVals, LONG lngPenWdth)
{
	if(lngPenWdth>10)
	{
		MessageBox(_T("Pen width must be between 1-10"));
		return;
	}
	if(lngGraphIdx>=0 && lngGraphIdx <m_chart.get_SeriesCount())
	{
		LPDISPATCH pDisp	=	m_chart.Series(lngGraphIdx);
		ISeriesPtr	pSeries	=	pDisp;
		pDisp->Release();
		_bstr_t bstrGraphName=	pSeries->GetName().copy();
		long lngLTblIdx=GetLtblIdxFromName(bstrGraphName);
		if(lngLTblIdx<0)
		{
			MessageBox(_T("Graph with this index doesn't exist"));
			return;
		}
		//double *dblTempXval= new double[lngNoOfPoints]; // Allocate space for the new data points and store the values in them.		
		//double *dblTempYval= new double[lngNoOfPoints];
		//long *lngTempColors=new long[lngNoOfPoints];

		long lngLBound,lngUBound,lngResultBound;

		// The arrays created must be of the same size as the data count present in VARIANT's
		// If not it will give assertion in while retrieving data from VARIANT"s to Double in 'fncGetDoubleValuesFromSafeArry' function
		SafeArrayGetLBound(varDblXVals.parray,1,&lngLBound);
		SafeArrayGetUBound(varDblXVals.parray,1,&lngUBound);
		lngResultBound	=	lngUBound	-	lngLBound;
		double *dblTempXval= new double[lngResultBound]; // Allocate space for the new data points and store the values in them.		

		SafeArrayGetLBound(varDblYVals.parray,1,&lngLBound);
		SafeArrayGetUBound(varDblYVals.parray,1,&lngUBound);
		lngResultBound	=	lngUBound	-	lngLBound;
		double *dblTempYval= new double[lngResultBound];

		SafeArrayGetLBound(varLngColors.parray,1,&lngLBound);
		SafeArrayGetUBound(varLngColors.parray,1,&lngUBound);
		lngResultBound	=	lngUBound	-	lngLBound;
		long *lngTempColors= new long[lngResultBound];


		long lSize=fncGetDoubleValuesFromSafeArray(varDblXVals,dblTempXval);
		lSize=fncGetDoubleValuesFromSafeArray(varDblYVals,dblTempYval);
		if((varLngColors.vt&VT_ARRAY && varLngColors.vt&VT_I4))
		{
			LONG lngLBndX,lngUBndX;
			SafeArrayGetLBound(varLngColors.parray,1,&lngLBndX);
			SafeArrayGetUBound(varLngColors.parray,1,&lngUBndX);
			long lngArrIdx=0;
			for(long i=lngLBndX;i<lngUBndX;i++)
			{
				SafeArrayGetElement(varLngColors.parray,&i,&lngTempColors[lngArrIdx]);
				lngArrIdx++;
			}
		}
		else
		{
			MessageBox(_T("Color values must be of Long type"));
			pSeries	=	NULL;
			return ;
		}
		if(lngNoOfPoints>lSize)
			lngNoOfPoints=lSize;
		pSeries->GetPen()->put_Width(lngPenWdth);
		pSeries->put_ColorEachPoint(TRUE);
		for(long cnt=0;cnt<lngNoOfPoints;cnt++)
		{
			pSeries->AddXY(dblTempXval[cnt],dblTempYval[cnt],_T(""),lngTempColors[cnt]);
			pSeries->put_PointColor(cnt,lngTempColors[cnt]);
		}
		delete[] dblTempXval;
		delete[] dblTempYval;
		delete[] lngTempColors;
		//	SysFreeString(bstrGraphName);
		pSeries	=	NULL;
	}
	else
	{
		MessageBox(_T("Graph with this index doesn't exist"));
		return;
	}
}
//*************************************************
//PURPOSE : Method to modify the data point of the drawn graph
//INPUTS  : long intGraphIdx   -  Graph ID whose data point is going to be modify
//			LONG lngPtIdx      -  Index of the Graph Point which is to be modified
//			double dblXval	   -  New X coord value
//			double dblYval	   -  New Y coord value
//ASSUMES : -
//RETURNS : 
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------


void CEsdAdvancedGraphCtrl::ModifyDataPoint(LONG lngGraphIdx, LONG lngPtIdx, DOUBLE dblXVal, DOUBLE dblYVal)
{
	if(lngGraphIdx>=0 && lngGraphIdx<m_chart.get_SeriesCount())
	{
		LPDISPATCH pDisp	=	m_chart.Series(lngGraphIdx);
		ISeriesPtr	pSeries	=	pDisp;
		pDisp->Release();
		_bstr_t bstrGraphName=	pSeries->GetName().copy();
		long lIdx=GetLtblIdxFromName(bstrGraphName);
		if(lIdx>=0)
		{
			if(lngPtIdx>=0 && lngPtIdx <pSeries->GetXValues()->GetCount())
			{
				pSeries->GetXValues()->put_Value(lngPtIdx,dblXVal);
				pSeries->GetYValues()->put_Value(lngPtIdx,dblYVal);
			}
			else
				MessageBox(_T("Point index is beyond the range"));
		}
		//SysFreeString(bstrGraphName);
		pSeries	=	NULL;
	}
	else
		MessageBox(_T("Graph with this ID doesn't exist"));

}
//*************************************************
//PURPOSE : Method to remove a graph with particular index
//INPUTS  : long intGraphID   - Graph ID which is to be removed
//ASSUMES : -
//RETURNS : 
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::RemoveGraph(LONG lngGraphIdx)
{

	if(lngGraphIdx>=0 && lngGraphIdx< m_chart.get_SeriesCount())		  // Check whether Graph exists or not.
	{
		LPDISPATCH pDisp	=	NULL;
		//Remove the Related Graph Info of this particular Graph

		if(m_arrGraphRelatedSerieses.GetSize() > 0)
		{
			pDisp	=	m_chart.Series(lngGraphIdx);
			ISeriesPtr	pSeries=	pDisp;
			pDisp->Release();
			_bstr_t bstrGraphName=pSeries->GetName().copy();
			//Check whether this Graph ID is User Added Graph's ID or not
			long lngLTblIdx=GetLtblIdxFromName(bstrGraphName);
			if(lngLTblIdx<0)
			{

				MessageBox(_T("Graph with this index doesn't exist"));
				pSeries	=	NULL;
				return;
			}
			// Remove datum Lines
			if(m_objDatumLineInfo.GetSize()>0)
			{
				EsdDATUMLINEINFO_STRUCT objDatumInfo=m_objDatumLineInfo.GetAt(0);
				if(bstrGraphName==objDatumInfo.bstrGraphName)
				{
					pDisp	=	m_chart.get_Tools();
					IToolListPtr pToolList	=	pDisp;
					pDisp->Release();
					int nToolCnt=pToolList->GetCount();
					for(int i=0;i<nToolCnt;i++)
					{
						long lngToolType=pToolList->GetItems(i)->GetToolType();
						if(lngToolType==objDatumInfo.lngDatumLineToolType) // Remove Manual Cursor 
							pToolList->Delete(i);
						if(lngToolType==objDatumInfo.lngTextDisplayToolType) // Remove Tool used to display the text
							pToolList->Delete(i);    // 
					}

					for(int i=0;i<2;i++)
					{
						_bstr_t bstrFixedDatumLine=(objDatumInfo.bstrFixedDatumLineName[i].copy());
						long lIdx=GetGraphIdxFromName(bstrFixedDatumLine);
						if(lIdx>=0)
						{
							m_chart.RemoveSeries(lIdx);
							// Assign the empty string &Free the space allocated for BSTR variables.
							objDatumInfo.bstrFixedDatumLineName[i]=_T("");
						}							
						//SysFreeString(bstrFixedDatumLine);
					}
					objDatumInfo.bstrGraphName=_T("");
					//SysFreeString(objDatumInfo.bstrGraphName);

					pToolList	=	NULL;
					m_objDatumLineInfo.RemoveAll();
					m_objDatumLineInfo.FreeExtra();
				}
			}
			if(m_arrPeakDetectPoint.GetSize() > 0 )
			{
				m_arrPeakDetectPoint.RemoveAll();
				m_arrPeakDetectPoint.FreeExtra();
			}
			// Remove Plot Area Text
			if(m_objPlotAreaText.GetSize()>0)
			{
				_bstr_t bstr=(pSeries->GetName().copy());
				long lIdx=GetCutomtextLTblIdxFromName(bstr);
				if(lIdx>=0)
				{
					EsdPLOTAREATEXT_STRUCT * pPlotAreaText=m_objPlotAreaText.GetAt(lIdx);
					//Remove the Plot area text data stored in this Structure pointers
					//	pPlotAreaText->bstrGraphName=_T(""); // If not assign to empty string it will refer some other string
					SysFreeString(pPlotAreaText->bstrGraphName);
					pPlotAreaText->dblXVal.RemoveAll();
					pPlotAreaText->dblYVal.RemoveAll();
					pPlotAreaText->strPlotAreaText.RemoveAll();
					// Remove this lot area text reference from the Array
					m_objPlotAreaText.RemoveAt(lIdx);
					m_objPlotAreaText.FreeExtra();

					delete pPlotAreaText;
					m_chart.Repaint();
				}
				//	SysFreeString(bstr);
			}

			// If the cross wire currently existing on this graph then Disable the Cross wire, 
			//otherwise it will give assertion because cross wire location(x,y) will not exist when graph is removed
			if(m_intCrossWireGraphID==lngLTblIdx) // Cross wire graph ID is equal to the current removing graph ID
			{
				m_bShowCrossWire	=	FALSE;
			}

			m_chart.RemoveSeries(lngGraphIdx); // Remove the Specified Graph

			// Remove Graphs drawn for  BaseLine,PeakFill,TrendLine etc Which are related to the given Graph ID
			long idx;
			if(lngLTblIdx>=0)
			{
				stuRemovableGraphData obj;
				CComBSTR Name;

				obj=m_arrGraphRelatedSerieses.GetAt(lngLTblIdx);
				Name=obj.bstrBaseLinename;
				if(Name!=_T(""))
				{
					idx=GetGraphIdxFromName(Name);
					if(idx>=0)
					{
						m_chart.RemoveSeries(idx);
					}
				}
				Name=obj.bsrLinearfitName;
				if(Name!=_T(""))
				{
					idx=GetGraphIdxFromName(Name);
					if(idx>=0)
					{
						m_chart.RemoveSeries(idx);

					}
				}
				//Peakfill comment on 02/04/08 
				//Name=obj.bstrFillName;
				//if(Name!=_T(""))
				//{
				//	idx=GetGraphIdxFromName(Name);
				//	if(idx>=0)
				//	{
				//		m_chart.RemoveSeries(idx);
				//		IToolListPtr	pToolList	=	m_chart.get_Tools();
				//		int nToolCnt	=	pToolList->GetCount();
				//		for(int i=0;i<nToolCnt;i++)
				//		{
				//			long lngToolType=pToolList->GetItems(i)->GetToolType();
				//			if(lngToolType==23) // Remove tool used for Peak filling i.e series band tool whose type=23
				//				pToolList->Delete(i);
				//		}
				//		pToolList	=	NULL;
				//	}
				//}

				Name=obj.bstrQuadraticFitName;
				if(Name!=_T(""))
				{
					idx=GetGraphIdxFromName(Name);
					if(idx>=0)
					{
						m_chart.RemoveSeries(idx);

					}
				}
				Name=obj.bstrLogFit;
				if(Name!=_T(""))
				{
					idx	=	GetGraphIdxFromName(Name);
					if(idx>=0)
					{
						m_chart.RemoveSeries(idx);

					}
				}
				Name	=	obj.bstrPowerFit;
				if(Name!=_T(""))
				{
					idx=GetGraphIdxFromName(Name);
					if(idx>=0)
					{
						m_chart.RemoveSeries(idx);

					}
				}
				Name	=	obj.bstrExpFit;
				if(Name!=_T(""))
				{
					idx=GetGraphIdxFromName(Name);
					if(idx>=0)
					{
						m_chart.RemoveSeries(idx);

					}
				}

				Name=obj.bstrCustomTrendLineName;
				if(Name!=_T(""))
				{
					idx=GetGraphIdxFromName(Name);
					if(idx>=0)
					{
						m_chart.RemoveSeries(idx);

					}
				}
				// Free the space allocated for the BSTR variables.
				SysFreeString(obj.bstrBaseLinename);
				SysFreeString(obj.bsrLinearfitName);
				SysFreeString(obj.bstrFillName);
				SysFreeString(obj.bstrQuadraticFitName);
				SysFreeString(obj.bstrExpFit);
				SysFreeString(obj.bstrLogFit);
				SysFreeString(obj.bstrPowerFit);
				SysFreeString(obj.bstrCustomTrendLineName);
				Name.Detach();

				m_arrGraphRelatedSerieses.RemoveAt(lngLTblIdx);
				m_arrGraphRelatedSerieses.FreeExtra();

			}

			// Remove the data that stored to display the information at peaks (i.e 'prcDisplayPeaks')of the removing graph
			if(m_arrPeakInfoIndexes.GetSize()>0)
			{
				EsdPeakInfoDisplay_Struct *temp	=	NULL;
				for(int nPInfoCnt=0;nPInfoCnt<m_arrPeakInfoIndexes.GetSize();nPInfoCnt++)
				{
					temp	=	m_arrPeakInfoIndexes.GetAt(nPInfoCnt);
					if(temp->lngGraphIdx	==	lngGraphIdx) // If the removing graph ID is equal to the ID stored in the array then delete it
					{
						delete temp;

						/*temp->lngvalueIdx.RemoveAll(); 
						temp->lngvalueIdx.FreeExtra();
						temp->strPeakInfo.RemoveAll();
						temp->strPeakInfo.FreeExtra();*/

						m_arrPeakInfoIndexes.RemoveAt(nPInfoCnt);
						m_arrPeakInfoIndexes.FreeExtra();
					}
					temp	=	NULL;
				}
			}

			//	m_chart.RemoveSeries(lngGraphIdx); // Remove the Specified Graph 

			//Remove Peak information(Height,Width,Area etc) of this Graph ID
			stuPeakInfo* PeakInfo = NULL;

			/*	if(lngLTblIdx>=m_GraphPeaks.GetSize())
			return;*/
			for(int i=0;i<m_GraphPeaks.GetSize();i++)   // Silpa.S 26/10/07
			{
				PeakInfo = m_GraphPeaks.GetAt(i);
				_bstr_t strPeakInfoGraph(PeakInfo->strGraphName,TRUE);
				if(bstrGraphName==strPeakInfoGraph)
				{
					PeakInfo->dblArea.RemoveAll();
					PeakInfo->dblHeight.RemoveAll();
					PeakInfo->dblPeakEndX.RemoveAll();
					PeakInfo->dblPeakEndY.RemoveAll();
					PeakInfo->dblPeakMaxX.RemoveAll();
					PeakInfo->dblPeakMaxY.RemoveAll();
					PeakInfo->dblPeakStartX.RemoveAll();
					PeakInfo->dblPeakStartY.RemoveAll();
					PeakInfo->dblWidth.RemoveAll();
					PeakInfo->intPeakEndIndex.RemoveAll();
					PeakInfo->intPeakMaxIndex.RemoveAll();
					PeakInfo->intPeakStartIndex.RemoveAll();

					PeakInfo->dblArea.FreeExtra();
					PeakInfo->dblHeight.FreeExtra();
					PeakInfo->dblPeakEndX.FreeExtra();
					PeakInfo->dblPeakEndY.FreeExtra();
					PeakInfo->dblPeakMaxX.FreeExtra();
					PeakInfo->dblPeakMaxY.FreeExtra();
					PeakInfo->dblPeakStartX.FreeExtra();
					PeakInfo->dblPeakStartY.FreeExtra();
					PeakInfo->dblWidth.FreeExtra();
					PeakInfo->intPeakEndIndex.FreeExtra();
					PeakInfo->intPeakMaxIndex.FreeExtra();
					PeakInfo->intPeakStartIndex.FreeExtra();

					delete PeakInfo;	
					PeakInfo = NULL;
					m_GraphPeaks.RemoveAt(i);
					m_GraphPeaks.FreeExtra();
					break;
				}
				//		SysFreeString(strPeakInfoGraph);
			}
			//	SysFreeString(bstrGraphName);  // assertion
			PeakInfo	=	NULL;
			pSeries	=NULL;
		}

	}
	else
	{
		MessageBox(_T("Graph with this index doesn't exist"));
		return;
	}
	m_bCanUpdateMinMax = TRUE;

	/*if(m_objSamples->GetSize() == 0)
	m_bFirstXYvalue    = TRUE;*/
}
//*************************************************
//PURPOSE : To remove All the graphs drawn on the Graph Control
//			at a time 
//INPUTS  : 
//ASSUMES : -
//RETURNS : 
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------p
void CEsdAdvancedGraphCtrl::RemoveAllGraphs(void)
{		

	if(m_arrPeakDetectPoint.GetSize() > 0 )
	{
		m_arrPeakDetectPoint.RemoveAll();
		m_arrPeakDetectPoint.FreeExtra();
	}

	//Remove All Tools Added to the TeeChart
	LPDISPATCH pDisp	=	m_chart.get_Tools();
	IToolListPtr pToolList	=	pDisp;
	pDisp->Release();
	pToolList->Clear();
	pToolList	=	NULL;

	// Remove the information about Datum Line 
	if(m_objDatumLineInfo.GetSize()>0)
	{
		EsdDATUMLINEINFO_STRUCT objDatumInfo;
		objDatumInfo=m_objDatumLineInfo.GetAt(0);
		for(int i=0;i<2;i++)
		{
			_bstr_t bstrFixedDatumLine=(objDatumInfo.bstrFixedDatumLineName[i].copy());
			long lIdx=GetGraphIdxFromName(bstrFixedDatumLine);
			if(lIdx>=0)
			{
				m_chart.RemoveSeries(lIdx);

				// Free the space allocated for BSTR variable.
				objDatumInfo.bstrFixedDatumLineName[i]=_T("");
				//	SysFreeString(objDatumInfo.bstrFixedDatumLineName[i]);						
			}							
			//SysFreeString(bstrFixedDatumLine);			
		}
		objDatumInfo.bstrGraphName=_T("");
		//	SysFreeString(objDatumInfo.bstrGraphName);
		m_objDatumLineInfo.RemoveAll();
		m_objDatumLineInfo.FreeExtra();
	}



	// Remove PlotArea Text info
	if(m_objPlotAreaText.GetSize()>0)
	{
		EsdPLOTAREATEXT_STRUCT * pPlotAreaText=NULL;
		for(int i=0;i<m_objPlotAreaText.GetSize();i++)
		{
			pPlotAreaText=m_objPlotAreaText.GetAt(i);
			pPlotAreaText->bstrGraphName=NULL;	//18/12
			SysFreeString(pPlotAreaText->bstrGraphName);
			pPlotAreaText->clrTextColor=0;
			pPlotAreaText->dblXVal.RemoveAll();
			pPlotAreaText->dblYVal.RemoveAll();
			pPlotAreaText->strPlotAreaText.RemoveAll();
			delete pPlotAreaText;
			pPlotAreaText=NULL;
		}
		m_objPlotAreaText.RemoveAll();
		m_objPlotAreaText.FreeExtra();

	}



	//Remove All the Graph Info Relating to the Client Added graphs
	if(m_arrGraphRelatedSerieses.GetSize() > 0)
	{
		//	m_chart.RemoveAllSeries();
		m_arrGraphRelatedSerieses.RemoveAll();
		m_arrGraphRelatedSerieses.FreeExtra();
		stuPeakInfo* PeakInfo = NULL;
		for(int i = 0; i < m_GraphPeaks.GetSize(); i++)
		{
			PeakInfo = m_GraphPeaks.GetAt(i);

			PeakInfo->dblArea.RemoveAll();
			PeakInfo->dblHeight.RemoveAll();
			PeakInfo->dblPeakEndX.RemoveAll();
			PeakInfo->dblPeakEndY.RemoveAll();
			PeakInfo->dblPeakMaxX.RemoveAll();
			PeakInfo->dblPeakMaxY.RemoveAll();
			PeakInfo->dblPeakStartX.RemoveAll();
			PeakInfo->dblPeakStartY.RemoveAll();
			PeakInfo->dblWidth.RemoveAll();
			PeakInfo->intPeakEndIndex.RemoveAll();
			PeakInfo->intPeakMaxIndex.RemoveAll();
			PeakInfo->intPeakStartIndex.RemoveAll();

			PeakInfo->dblArea.FreeExtra();
			PeakInfo->dblHeight.FreeExtra();
			PeakInfo->dblPeakEndX.FreeExtra();
			PeakInfo->dblPeakEndY.FreeExtra();
			PeakInfo->dblPeakMaxX.FreeExtra();
			PeakInfo->dblPeakMaxY.FreeExtra();
			PeakInfo->dblPeakStartX.FreeExtra();
			PeakInfo->dblPeakStartY.FreeExtra();
			PeakInfo->dblWidth.FreeExtra();
			PeakInfo->intPeakEndIndex.FreeExtra();
			PeakInfo->intPeakMaxIndex.FreeExtra();
			PeakInfo->intPeakStartIndex.FreeExtra();
			//	SysFreeString(PeakInfo->strGraphName); // 26/10/'07

			delete PeakInfo;

			PeakInfo = NULL;
		}

		m_GraphPeaks.RemoveAll();
		m_GraphPeaks.FreeExtra();
	}



	// To Remove Graphs data related to all the User Added graphs
	if(m_arrGraphRelatedSerieses.GetSize()>0)
	{
		stuRemovableGraphData objRemoveGraphs;
		for(int i=0;i<m_arrGraphRelatedSerieses.GetSize();i++)
		{
			objRemoveGraphs=m_arrGraphRelatedSerieses.GetAt(i);
			SysFreeString(objRemoveGraphs.bsrLinearfitName);
			SysFreeString(objRemoveGraphs.bstrBaseLinename);
			SysFreeString(objRemoveGraphs.bstrCustomTrendLineName);
			SysFreeString(objRemoveGraphs.bstrFillName);
			SysFreeString(objRemoveGraphs.bstrGraphName);
			SysFreeString(objRemoveGraphs.bstrQuadraticFitName);
			SysFreeString(objRemoveGraphs.bstrExpFit);
			SysFreeString(objRemoveGraphs.bstrLogFit);
			SysFreeString(objRemoveGraphs.bstrPowerFit);
		}
		m_arrGraphRelatedSerieses.RemoveAll();
		m_arrGraphRelatedSerieses.FreeExtra();
	}



	//Remove the data stored to display the information at peaks(i.e 'prcDisplayPeaks')
	if(m_arrPeakInfoIndexes.GetSize()>0)
	{
		EsdPeakInfoDisplay_Struct *temp	=	NULL;
		for(int i=0;i<m_arrPeakInfoIndexes.GetSize();i++)
		{
			temp	=	m_arrPeakInfoIndexes.GetAt(i);
			delete temp;
		}
		temp	=	NULL;
		m_arrPeakInfoIndexes.RemoveAll();
		m_arrPeakInfoIndexes.FreeExtra();

	}


	m_chart.RemoveAllSeries();

	InitializePeakDetectionVariables();

	m_bCanUpdateMinMax = TRUE;

	m_bFirstXYvalue    = TRUE;

}
//*************************************************
//PURPOSE : To initialize the variables used for Peak detection 
//			process, with default values
//INPUTS  : 
//ASSUMES : -
//RETURNS : 
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::InitializePeakDetectionVariables(void)
{
	m_dblCurrentX = 0;
	m_dblCurrentY = 0;

	m_dblOldX = 0;
	m_dblOldY = 0;

	m_dblPeakStartX = 0;
	m_dblPeakStartY = 0;

	m_dblPeakMaxX = 0;
	m_dblPeakMaxY = 0;

	m_dblPeakEndX = 0;
	m_dblPeakEndY = 0;

	m_dblPeakLeftWidth = 0;
	m_dblPeakLeftHeight = 0;

	m_dblSlope = 0;
	m_dblOldSlope = 0;
	//	m_dblThresholdSlope = 0;
	m_dblSavedSlopeForDownHill = 0;

	m_dblCurve = 0;
	m_dblOldCurve = 0;	

	//	m_dblPeakMaximumSlope = 0;
	//	m_dblPeakMaximumCurve = 0;

	m_dblPeakMaxSlopeX = 0;
	m_dblPeakMaxSlopeY = 0;

	m_dblPeakMaxCurveX = 0;
	m_dblPeakMaxCurveY = 0;	

	m_dblUpCurveLimit = LARGEFLOAT;
	m_dblDownCurveLimit = LARGEFLOAT;

	m_dblPreviousDerivativeX = 0;
	m_dblPreviousDerivativeY = 0;
	m_dblPreviousDerivativeXDiffValue = 0;

	m_dblLastPeakEndX = 0;
	/*
	m_dblAverageNoise = 0;
	m_dblAverageLength = 0;
	m_dblMinArea = 0;
	m_dblMinHeight = 0;
	m_dblMinWidth = 0;
	*/
	m_dblAvCurve = 0;

	m_intPeakStartIndex = -1;
	m_intPeakMaxIndex = -1;
	m_intPeakEndIndex = -1;
	m_intDownCount = 0;
	m_intDerivativeRetValue = 0;
	m_intPeakStatus = FLAT;
	m_intPeakUpCount = 0;
	m_intPeakDownCount = 0;
	m_intMaxCurveIndex = -1;	

	m_intCurrentDataPointIndex = -1;

	if(m_arrPeakDetectPoint.GetSize() > 0)
	{
		m_arrPeakDetectPoint.RemoveAll();
		m_arrPeakDetectPoint.FreeExtra();
	}

}
//*************************************************
//PURPOSE : To set starting point for the next peak after the data
//			processing is completed on the previous peak .
//INPUTS  : 
//ASSUMES : -
//RETURNS : 
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------

void CEsdAdvancedGraphCtrl::InitializationsForNextPeak(void)
{
	stuPeakDetectPoint obj;
	for(int intIndex = 0; intIndex < m_arrPeakDetectPoint.GetSize(); intIndex++)
	{
		obj = m_arrPeakDetectPoint.GetAt(intIndex);
		if(obj.X == m_dblLastPeakEndX)
		{

			m_dblPeakStartX = obj.X;
			m_dblPeakStartY = obj.Y;

			m_intPeakStartIndex = intIndex;
			break;
		}		
	}    

	m_intPeakUpCount = 1;    

	if (m_blnDetectNegativePeaksAlso == TRUE && m_dblSlope < 0)	
		m_intPeakStatus = NEGUPCRV;
	else 
		m_intPeakStatus = UPCRV;
}
//*************************************************
//PURPOSE : To perform the Algorithmic analysis on the data for Peak 
//			detection process
//INPUTS  : double dblXval -  X coord value of the point which is going to be processed
//			double dblYval -  Y coord value of the point which is going to be processed
//ASSUMES : -
//RETURNS : 
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::ProcessPtForPeakDetection(double dblXVal, double dblYVal)
{

	stuPeakDetectPoint obj;
	obj.X = dblXVal;
	obj.Y = dblYVal;

	m_arrPeakDetectPoint.Add(obj);

	m_intCurrentDataPointIndex++;

	if (m_intCurrentDataPointIndex >= m_arrPeakDetectPoint.GetSize())
		return;

	obj = m_arrPeakDetectPoint.GetAt(m_intCurrentDataPointIndex);

	m_dblOldX = m_dblCurrentX;
	m_dblOldY = m_dblCurrentY;

	m_dblCurrentX = obj.X;
	m_dblCurrentY = obj.Y;

	m_intDerivativeRetValue = Derivative();

	CString str;
	switch (m_intPeakStatus)
	{     
	case FLAT:
		//MessageBox(_T("Flat"));
		if (isFlat())
			break;

	case NEGUPCRV:
	case UPCRV:
		//MessageBox(_T("UpCurv"));
		if (isFlankNotYetAccepted(m_intPeakStatus == NEGUPCRV))
			break;

	case NEGUP:
	case UP:
		//AfxMessageBox(_T("Up"));
		if (isUpHill(m_intPeakStatus == NEGUP))
			break;

	case NEGDOWN:
	case DOWN:
		//AfxMessageBox(_T("Down"));
		if (isDownHill(m_intPeakStatus == NEGDOWN))
			break;
	case PKEND:
		//AfxMessageBox(_T("End"));
		StorePeak();

	}

}
//**************************************************************************
//PURPOSE : Function used for Data analysis procedure
//INPUTS  : 
//ASSUMES : -
//RETURNS : int -- return the state of the data point with respect to peak.
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//----------------------------------------------------------------------------
int CEsdAdvancedGraphCtrl::Derivative()
{
	double dblXDiff1;
	double dblXDiff2;
	double dblYDiff;
	double dblAverageCurve;


	dblYDiff = m_dblCurrentY - m_dblPreviousDerivativeY;
	dblXDiff1 = m_dblCurrentX - m_dblPreviousDerivativeX;

	if(fabs(dblYDiff) < m_dblAverageNoise)
		return 0;

	m_dblOldSlope = m_dblSlope;
	m_dblPreviousDerivativeX = m_dblCurrentX;
	m_dblPreviousDerivativeY = m_dblCurrentY;

	if(dblXDiff1 != 0.0)
		m_dblSlope = dblYDiff / dblXDiff1;

	m_dblOldCurve = m_dblCurve;    

	dblXDiff2 = (dblXDiff1 + m_dblPreviousDerivativeXDiffValue) / 2;

	if(dblXDiff2 != 0.0)
		m_dblCurve = (m_dblSlope - m_dblOldSlope) / dblXDiff2;

	m_dblPreviousDerivativeXDiffValue = dblXDiff1;

	switch(m_intPeakStatus)
	{
	case NEGUPCRV:
		if (m_dblSlope < 0.0)
			m_intPeakUpCount++;

	case UPCRV:
		if (m_dblSlope >= 0.0)
			m_intPeakUpCount++;

	case FLAT:
		m_dblAvCurve += fabs(m_dblCurve) * dblXDiff2;
		m_dblAverageLength += dblXDiff2;            

		if(m_dblAverageLength != 0)
			dblAverageCurve = m_dblAvCurve / m_dblAverageLength;

		m_dblUpCurveLimit = PACURVE * dblAverageCurve;

		if (m_dblAverageLength> MAXAVLENGTH)
		{
			m_dblAvCurve /= 2.0;
			m_dblAverageLength= MAXAVLENGTH / 2;
		}

		return 2;

	case BCKDN:
	case DOWN:
		if (m_dblSlope >= 0.0 || (-m_dblSlope <= m_dblThresholdSlope
			&& m_dblCurve < m_dblOldCurve && m_dblCurve < m_dblDownCurveLimit))
			m_intPeakDownCount++;
		else
			m_intPeakDownCount = 0;
		return 1;

	case NEGBCKDN:
	case NEGDOWN:
		if (m_dblSlope < 0.0 || (m_dblSlope <= m_dblThresholdSlope
			&& m_dblCurve > m_dblOldCurve && -m_dblCurve < m_dblDownCurveLimit))
			m_intPeakDownCount++;                
		else
			m_intPeakDownCount = 0;

	case NEGUP:
	case UP:
		return 1;
	}

	return 0;
}


//*************************************************
//PURPOSE : Function to determine whether the data point is in Flat position or 
//			not with respect to graph.
//INPUTS  : 
//ASSUMES : -
//RETURNS : bool
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
bool CEsdAdvancedGraphCtrl::isFlat()
{
	m_intPeakUpCount = 0;	

	if((m_blnDetectNegativePeaksAlso == FALSE && m_dblCurve < m_dblUpCurveLimit) || (m_blnDetectNegativePeaksAlso == TRUE && fabs(m_dblCurve) < m_dblUpCurveLimit))
		return 1;

	m_intPeakStatus = (m_dblSlope > 0.0 || m_blnDetectNegativePeaksAlso == FALSE)? UPCRV: NEGUPCRV;

	m_dblPeakStartX = m_dblCurrentX;
	m_dblPeakStartY = m_dblCurrentY;

	//	m_intPeakStartIndex = m_arrPeakDetectPoint.GetSize() - 1 ;
	m_intPeakStartIndex = m_intCurrentDataPointIndex;

	return FALSE;
}
//*************************************************
//PURPOSE : 
//INPUTS  : 
//ASSUMES : -
//RETURNS : 
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
bool CEsdAdvancedGraphCtrl::isFlankNotYetAccepted(bool  blnNegative)
{	
	if(blnNegative == FALSE && m_dblSlope < 0.0 || blnNegative == TRUE && m_dblSlope > 0.0)
	{
		m_intPeakStatus = FLAT;
		return TRUE;
	}

	if(m_intPeakUpCount < NUP)
		return TRUE;

	m_dblPeakMaxX = m_dblCurrentX;
	m_dblPeakMaxY = m_dblCurrentY;

	//	m_intPeakMaxIndex = m_arrPeakDetectPoint.GetSize() - 1;
	m_intPeakMaxIndex = m_intCurrentDataPointIndex;

	m_intDownCount = 0;

	m_dblPeakMaximumSlope = 0.0;
	m_dblPeakMaximumCurve = -LARGEFLOAT;
	m_dblPeakLeftHeight = m_dblPeakLeftWidth = -LARGEFLOAT;

	m_intPeakStatus = (blnNegative == TRUE) ? NEGUP : UP;    


	return FALSE;
}


//*************************************************
//PURPOSE : 
//INPUTS  : 
//ASSUMES : -
//RETURNS : 
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
bool CEsdAdvancedGraphCtrl::isUpHill(bool blnNegative)
{
	if (blnNegative == TRUE && -m_dblSlope > m_dblPeakMaximumSlope)
		m_dblPeakMaximumSlope = -m_dblSlope;

	if (blnNegative == FALSE && m_dblSlope > m_dblPeakMaximumSlope)
		m_dblPeakMaximumSlope =  m_dblSlope;

	if (blnNegative == TRUE && -m_dblCurve > m_dblPeakMaximumCurve || blnNegative == FALSE && m_dblCurve > m_dblPeakMaximumCurve)
	{
		m_dblPeakMaximumCurve = fabs(m_dblCurve);

		m_dblPeakMaxCurveX = m_dblCurrentX;
		m_dblPeakMaxCurveY = m_dblCurrentY;

		//		m_intMaxCurveIndex = m_arrPeakDetectPoint.GetSize() - 1;
		m_intMaxCurveIndex = m_intCurrentDataPointIndex;
	}

	if (blnNegative == TRUE && m_dblCurrentY <= m_dblOldY || blnNegative == FALSE && m_dblCurrentY >= m_dblOldY)
	{
		m_intDownCount = 0;

		if(blnNegative == TRUE && m_dblCurrentY < m_dblPeakMaxY || blnNegative == FALSE && m_dblCurrentY> m_dblPeakMaxY)
		{
			m_dblPeakMaxX = m_dblCurrentX;
			m_dblPeakMaxY = m_dblCurrentY;

			m_intPeakMaxIndex = m_intCurrentDataPointIndex;//m_arrPeakDetectPoint.GetSize() - 1;

			m_dblPeakLeftHeight = fabs( m_dblPeakMaxY - m_dblPeakStartY) * MINENDPROZ; 
			m_dblPeakLeftWidth = fabs(m_dblPeakMaxX - m_dblPeakStartX) * MINENDPROZ;
		}

		return true;
	}
	else
		if (blnNegative == TRUE && m_dblPeakStartY < m_dblCurrentY || blnNegative == FALSE && m_dblPeakStartY > m_dblCurrentY)
		{

			m_dblPeakStartX	= m_dblCurrentX;
			m_dblPeakStartY = m_dblCurrentY;

			//	m_intPeakStartIndex = m_arrPeakDetectPoint.GetSize() - 1;
			m_intPeakStartIndex = m_intCurrentDataPointIndex;
		}


		if (blnNegative == TRUE && m_dblCurrentY - m_dblPeakMaxY < m_dblPeakLeftHeight
			|| blnNegative == FALSE && m_dblPeakMaxY - m_dblCurrentY < m_dblPeakLeftHeight
			|| m_dblCurrentX - m_dblPeakMaxX < m_dblPeakLeftWidth)
		{
			m_intDownCount++;        
			return true;
		}

		if (++m_intDownCount < NDO)
			return true;


		if (m_dblPeakMaxCurveX > m_dblPeakMaxX)
		{
			m_dblPeakMaxCurveX = m_dblPeakMaxX;
			m_dblPeakMaxCurveY = m_dblPeakMaxY;        
		}

		m_dblThresholdSlope = (m_dblPeakMaximumSlope < MINPESLOPE)? MINPESLOPE * PESLOPEproz :
			(m_dblPeakMaximumSlope > MAXPESLOPE)? MAXPESLOPE * PESLOPEproz :
			m_dblPeakMaximumSlope * PESLOPEproz;

		m_dblDownCurveLimit = (m_dblPeakMaximumCurve < MINPECURVE)? MINPECURVE * PECURVEproz :
			(m_dblPeakMaximumCurve > MAXPECURVE)? MAXPECURVE * PECURVEproz :
			m_dblPeakMaximumCurve * PECURVEproz;    

		m_dblSavedSlopeForDownHill = m_dblSlope;

		m_intPeakStatus = (blnNegative == TRUE)? NEGBCKDN:BCKDN;

		m_dblPreviousDerivativeX = m_dblCurrentX = m_dblPeakMaxCurveX;
		m_dblPreviousDerivativeY = m_dblCurrentY = m_dblPeakMaxCurveY;

		/*
		double dblSaveCurrentDPIndex = m_intCurrentDataPointIndex;
		stuPeakDetectPoint

		for(int intIndex = 0; intIndex < m_arrPeakDetectPoint.GetSize(); intIndex++)
		{
		m_intCurrentDataPointIndex = intIndex;
		dblTempX = m_arrPeakDetectPoint.GetAt(intIndex);
		if(dblTempX == m_dblPeakMaxCurveX)
		break;
		}
		*/

		SearchForPeakStart(blnNegative);  



		//	m_intCurrentDataPointIndex = dblSaveCurrentDPIndex;
		stuPeakDetectPoint obj;
		obj = m_arrPeakDetectPoint.GetAt(m_intCurrentDataPointIndex);

		//	m_dblPreviousDerivativeX = m_dblCurrentX = m_dblPeakMaxX;
		//	m_dblPreviousDerivativeY = m_dblCurrentY = m_dblPeakMaxY;

		m_dblPreviousDerivativeX = m_dblCurrentX = obj.X;
		m_dblPreviousDerivativeY = m_dblCurrentY = obj.Y;;    

		m_dblPeakEndX = m_dblCurrentX;
		m_dblPeakEndY = m_dblCurrentY;	

		//	m_intPeakEndIndex = m_arrPeakDetectPoint.GetSize() - 1;
		m_intPeakEndIndex = m_intCurrentDataPointIndex;

		m_dblSlope = (blnNegative == TRUE) ? LARGEFLOAT : -LARGEFLOAT;

		m_dblThresholdSlope /= PAPEfak;

		m_intPeakDownCount = m_intDerivativeRetValue = m_intDownCount = 0;

		m_intPeakStatus = (blnNegative == TRUE)? NEGDOWN: DOWN;

		return false;	
}


//*************************************************
//PURPOSE : 
//INPUTS  : 
//ASSUMES : -
//RETURNS : 
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
bool CEsdAdvancedGraphCtrl::isDownHill(bool blnNegative)
{

	//actually it is if
	if(blnNegative == TRUE && m_dblCurrentY > m_dblPeakEndY || blnNegative == FALSE && m_dblCurrentY < m_dblPeakEndY)
	{
		m_dblPeakEndX = m_dblCurrentX;
		m_dblPeakEndY = m_dblCurrentY;
		//		m_intPeakEndIndex = m_arrPeakDetectPoint.GetSize() - 1;
		m_intPeakEndIndex = m_intCurrentDataPointIndex;
		CString str;
		str.Format(_T("peak endx =%lf %lf "),m_dblPeakEndX,m_dblPeakEndY);
		//AfxMessageBox(str);
		str.Format(_T("Down Hill: dwnCnt=%d %d %ld"),m_intPeakDownCount,m_intCurrentDataPointIndex,m_lngNoOfDataPoints);
		//AfxMessageBox(str);

	}


	////if by sivagnaehs
	if(m_lngNoOfDataPoints!=0)//Offline peak detection
	{
		CString str;
		str.Format(_T("Down Hill: dwnCnt=%d %d %ld"),m_intPeakDownCount,m_intCurrentDataPointIndex,m_lngNoOfDataPoints);
		//AfxMessageBox(str);
		if(m_lngNoOfDataPoints-m_intCurrentDataPointIndex==0)
		{
			m_dblPeakEndX = m_dblCurrentX;
			m_dblPeakEndY = m_dblCurrentY;
			m_intPeakEndIndex = m_intCurrentDataPointIndex;
		}
		if(m_intPeakDownCount==0)
			if(m_lngNoOfDataPoints-m_intCurrentDataPointIndex<3)
				return false;
	}
	if(m_intDerivativeRetValue)
		m_intDownCount = 1;

	return (m_intPeakDownCount <  NPE);
}


//*************************************************
//PURPOSE : 
//INPUTS  : 
//ASSUMES : -
//RETURNS : 
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
bool CEsdAdvancedGraphCtrl::SearchForPeakStart(bool blnNegative)
{
	double dblDeltaHeight;
	double dblDeltaWidth;
	double dblSavedPeakStartX;
	double dblSavedPeakStartY;

	dblSavedPeakStartX = m_dblPeakStartX;
	dblSavedPeakStartY = m_dblPeakStartY;

	m_dblPeakStartX = m_dblPeakMaxX;
	m_dblPeakStartY	= m_dblPeakMaxY;

	m_dblSlope = (blnNegative == TRUE)? LARGEFLOAT:-LARGEFLOAT;
	m_intPeakDownCount = 0;	

	m_intMaxCurveIndex = m_intPeakMaxIndex;

	while ((m_intPeakDownCount < NPE || dblDeltaHeight < m_dblPeakLeftHeight
		|| dblDeltaWidth < m_dblPeakLeftWidth) && m_dblCurrentX > m_dblLastPeakEndX)
	{
		stuPeakDetectPoint obj;
		if(--m_intMaxCurveIndex <0) 
			return false;
		obj = m_arrPeakDetectPoint.GetAt(m_intMaxCurveIndex);

		m_dblCurrentX = obj.X;
		m_dblCurrentY = obj.Y;

		if(blnNegative == TRUE && m_dblCurrentY > m_dblPeakStartY || blnNegative == FALSE && m_dblCurrentY < m_dblPeakStartY)
		{				
			m_dblPeakStartX = m_dblCurrentX;
			m_dblPeakStartY = m_dblCurrentY;

			m_intPeakStartIndex = m_intMaxCurveIndex;		

			m_dblPeakLeftHeight = m_dblPeakLeftWidth = -LARGEFLOAT;
			dblDeltaHeight = dblDeltaWidth = 0;
		}

		if (blnNegative == TRUE && m_dblCurrentY <= m_dblPeakStartY || blnNegative == FALSE && m_dblCurrentY >= m_dblPeakStartY)
		{
			m_dblPeakLeftHeight = (m_dblCurrentY - dblSavedPeakStartY) * MINENDPROZ;
			m_dblPeakLeftWidth =  (m_dblCurrentX - dblSavedPeakStartX) * (long) MINENDPROZ;

			dblDeltaHeight = fabs(m_dblCurrentY - m_dblPeakStartY);
			dblDeltaWidth = (m_dblPeakStartX - m_dblCurrentX);
		}

		Derivative();		

		if(m_blnLockBaseLine == TRUE)
			if((blnNegative == TRUE && m_dblCurrentY >= m_dblBaseLineLevel) || (blnNegative == FALSE && m_dblCurrentY <= m_dblBaseLineLevel))
				break;
	}

	return false;
}

//*************************************************
//PURPOSE :  To store All the peak parameters at the end of 
//			 Peak Detection process
//INPUTS  : 
//ASSUMES : -
//RETURNS : 
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
bool CEsdAdvancedGraphCtrl::StorePeak()
{
	//	While Peak Detection is going on Point to Point Base Line is taken into consideration irrespective of the Base Line type.
	//  In fncPerformIntegration function, Integration is once again performed based on the Base Line Type.


	double dblTmpHeight = 0;
	double dblTmpWidth = 0;
	double dblTmpArea = 0;
	double dblBLSLope;
	double dblYOnBL;
	double dblHalfHeight;
	double dblWidthX1 = 0;
	double dblWidthX2 = 0;
	double dblTmpPeakThreshold=0;

	stuPeakDetectPoint obj1, obj2;

	if ((m_dblPeakEndX - m_dblPeakStartX) != 0)
		dblBLSLope = (m_dblPeakEndY - m_dblPeakStartY) / (m_dblPeakEndX - m_dblPeakStartX);

	dblYOnBL = dblBLSLope *(m_dblPeakMaxX - m_dblPeakStartX) + m_dblPeakStartY;

	dblTmpHeight = fabs(m_dblPeakMaxY - dblYOnBL);	

	m_dblLastPeakEndX = m_dblPeakEndX;

	if((dblTmpHeight < m_dblMinHeight) && (bForcedpeak == FALSE)  )
	{
		InitializationsForNextPeak();
		return false;
	}

	switch(m_intPeakWidthCalType)
	{
	case 1: // Point - Point 
		{
			dblTmpWidth = (m_dblPeakEndX - m_dblPeakStartX);

		}
		break;
	case 2: // Full Width at Half Maximum
		{
			dblHalfHeight = dblTmpHeight / 2;

			for(int i = m_intPeakMaxIndex; i>=m_intPeakStartIndex; i--)
			{
				obj1 = m_arrPeakDetectPoint.GetAt(i);
				if((obj1.Y - m_dblPeakStartY) <= dblHalfHeight)
				{
					dblWidthX1 = obj1.X;
					break;
				}
			}
			for(int i = m_intPeakMaxIndex; i<=m_intPeakEndIndex; i++)
			{
				obj1 = m_arrPeakDetectPoint.GetAt(i);
				if((obj1.Y - m_dblPeakEndY/*m_dblPeakStartY /* changed by sivaganesh*/) <= dblHalfHeight)
				{
					dblWidthX2 = obj1.X;
					break;
				}
			}

			dblTmpWidth = dblWidthX2 - dblWidthX1;
		}		
		break;

	case 3: // Width @ 0.607 Height
		{
			dblHalfHeight = 0.607 * dblTmpHeight;

			for(int i = m_intPeakMaxIndex; i>=m_intPeakStartIndex; i--)
			{
				obj1 = m_arrPeakDetectPoint.GetAt(i);
				if((obj1.Y - m_dblPeakStartY) <= dblHalfHeight)
				{
					dblWidthX1 = obj1.X;
					break;
				}
			}
			for(int i = m_intPeakMaxIndex; i<=m_intPeakEndIndex; i++)
			{
				obj1 = m_arrPeakDetectPoint.GetAt(i);
				if((obj1.Y - m_dblPeakEndY/*m_dblPeakStartY /* changed by sivaganesh*/) <= dblHalfHeight)
				{
					dblWidthX2 = obj1.X;
					break;
				}
			}

			dblTmpWidth = dblWidthX2 - dblWidthX1;
		}

		break;
	}

	if((dblTmpWidth < m_dblMinWidth)&& (bForcedpeak == FALSE))
	{	
		InitializationsForNextPeak();
		return false;
	}

	//   //start of sivaganesh's 

	//stuPeakDetectPoint obj3;

	////width at 5 percent height 
	//{
	//	dblHalfHeight = dblTmpHeight / 20;

	//	for(int i = m_intPeakMaxIndex; i>=m_intPeakStartIndex; i--)
	//	{
	//		obj3 = m_arrPeakDetectPoint.GetAt(i);
	//		if((obj3.Y - m_dblPeakStartY) <= dblHalfHeight)
	//		{
	//			dblWidthX1 = obj3.X;
	//			break;
	//		}
	//	}

	//	for(int i = m_intPeakMaxIndex; i<=m_intPeakEndIndex; i++)
	//	{
	//		obj3 = m_arrPeakDetectPoint.GetAt(i);
	//		if((obj3.Y - m_dblPeakEndY/*m_dblPeakStartY /* changed by sivaganesh*/) <= dblHalfHeight)
	//		{

	//			dblWidthX2 = obj3.X;
	//			break;
	//		}
	//	}
	//	//double dblSlope1 = ((m_dblPeakEndY-m_dblPeakStartY)/(m_intPeakEndIndex-m_intPeakStartIndex));
	//	//double dblIntercept1= (m_dblPeakStartY - (dblBLSLope * m_dblPeakStartX));
	//	//	double dblSlope2 = -(1 / dblBLSLope);
	//	//	double dblIntercept2= (m_dblPeakMaxY - (dblSlope2 * m_dblPeakMaxX));

	//	double dblCenterX= m_dblPeakMaxX;

	//	double dblLeftWidth = dblCenterX - dblWidthX1;
	//	double dblRightWidth = dblWidthX2 - dblCenterX;

	//	double dblWidth =(dblWidthX2 - dblWidthX1);



	//	m_dblWidthAt5PercentHeight.Add(dblWidth);
	//	m_dblLeftWidthAt5PercentHeight.Add(dblLeftWidth);
	//	m_dblRightWidthAt5PercentHeight.Add(dblRightWidth);

	//}
	////Width at 10 percent height 
	//{
	//	dblWidthX1 = 0;
	//	dblWidthX2 = 0;
	//	dblHalfHeight=0;
	//	dblHalfHeight = dblTmpHeight / 10;

	//	for(int i = m_intPeakMaxIndex; i>=m_intPeakStartIndex; i--)
	//	{
	//		obj3 = m_arrPeakDetectPoint.GetAt(i);
	//		if((obj3.Y - m_dblPeakStartY) <= dblHalfHeight)
	//		{
	//			dblWidthX1 = obj3.X;
	//			break;
	//		}
	//	}

	//	for(int i = m_intPeakMaxIndex; i<=m_intPeakEndIndex; i++)
	//	{
	//		obj3 = m_arrPeakDetectPoint.GetAt(i);
	//		if((obj3.Y - m_dblPeakEndY/*m_dblPeakStartY /* changed by sivaganesh*/) <= dblHalfHeight)
	//		{
	//			dblWidthX2 = obj3.X;
	//			break;
	//		}
	//	}

	//	double dblCenterX= m_dblPeakMaxX;

	//	double dblLeftWidth = dblCenterX - dblWidthX1;
	//	double dblRightWidth = dblWidthX2 - dblCenterX;

	//	double dblWidth =(dblWidthX2 - dblWidthX1);


	//	m_dblWidthAt10PercentHeight.Add(dblWidth);
	//	m_dblLeftWidthAt10PercentHeight.Add(dblLeftWidth);
	//	m_dblRightWidthAt10PercentHeight.Add(dblRightWidth);


	//}
	////width at half height
	//{
	//	dblWidthX1 = 0;
	//	dblWidthX2 = 0;
	//	dblHalfHeight=0;

	//	dblHalfHeight = dblTmpHeight / 2;

	//	for(int i = m_intPeakMaxIndex; i>=m_intPeakStartIndex; i--)
	//	{
	//		obj3 = m_arrPeakDetectPoint.GetAt(i);
	//		if((obj3.Y - m_dblPeakStartY) <= dblHalfHeight)
	//		{
	//			dblWidthX1 = obj3.X;
	//			break;
	//		}
	//	}

	//	for(int i = m_intPeakMaxIndex; i<=m_intPeakEndIndex; i++)
	//	{
	//		obj3 = m_arrPeakDetectPoint.GetAt(i);
	//		if((obj3.Y - m_dblPeakEndY/*m_dblPeakStartY /* changed by sivaganesh*/) <= dblHalfHeight)
	//		{
	//			dblWidthX2 = obj3.X;
	//			break;
	//		}
	//	}

	//	double dblCenterX= m_dblPeakMaxX;

	//	double dblLeftWidth = dblCenterX - dblWidthX1;
	//	double dblRightWidth = dblWidthX2 - dblCenterX;

	//	double dblWidth =(dblWidthX2 - dblWidthX1);

	//	m_dblWidthAtHalfHeight.Add(dblWidth);
	//	m_dblLeftWidthAtHalfHeight.Add(dblLeftWidth);
	//	m_dblRightWidthAtHalfHeight.Add(dblRightWidth);

	//}

	////end of sivaganesh's code

	obj1 = m_arrPeakDetectPoint.GetAt(m_intPeakStartIndex);
	obj2 = m_arrPeakDetectPoint.GetAt(m_intPeakEndIndex);

	double dblBaseLineArea =  0.5 * (obj1.Y + obj2.Y) * (obj2.X - obj1.X);

	double dblY0 = obj1.Y;
	double dblYn = obj2.Y;
	double dblY = 0;
	double dblInterval = 0;


	if(m_intPeakEndIndex > m_intPeakStartIndex)
	{
		obj2 = m_arrPeakDetectPoint.GetAt(m_intPeakStartIndex+1);
		dblInterval = fabs(obj2.X - obj1.X);
	}

	for(int i = m_intPeakStartIndex+1  ; i <= m_intPeakEndIndex-1; i++)
	{
		obj1 = m_arrPeakDetectPoint.GetAt(i);

		dblY += obj1.Y;
	}


	dblTmpArea = dblInterval /2 * (dblY0 + dblYn + (2 * dblY));

	dblTmpArea = fabs(dblTmpArea - dblBaseLineArea);


	if((dblTmpArea <  m_dblMinArea) && (bForcedpeak == FALSE) )
	{
		InitializationsForNextPeak();
		return false;
	}

	//Abhinav
	stuPeakDetectPoint obj4,obj5;
	obj4=m_arrPeakDetectPoint.GetAt(m_intPeakStartIndex);


	for (int i=m_intPeakStartIndex+1;i<m_intPeakStartIndex+3;i++)
	{

		obj5=m_arrPeakDetectPoint.GetAt(i);


		double tempSlope=(obj5.Y-obj4.Y)/(obj5.X-obj4.X);

		if(tempSlope < m_dblMinPeakThreshold)
		{
			dblTmpPeakThreshold=tempSlope;
		}
		else
		{
			dblTmpPeakThreshold=tempSlope;
			break;
		}
		//To move to next point.
		obj4 = obj5;
	}
	if ((dblTmpPeakThreshold<m_dblMinPeakThreshold))
	{

		InitializationsForNextPeak();

		return false;
	}

	//Abhinav

	//filling the structure for baseline correction

	if((bForcedpeak == TRUE) && (m_objPeakInfo->arrStartPointType.GetSize()>0))
	{
		bForcedpeak=FALSE;
		blnManualPeak = FALSE ;
		///filling the structure for baseline correction

		//To add the peak detected into the structure based on the peak max index
		int index=-1;
		for(int i=0;i<(int)m_objPeakInfo->dblPeakMaxX.GetSize();i++)
		{
			//s.Format(_T("%lf"),m_objPeakInfo->dblPeakMaxX.GetAt(i));
			if(m_dblPeakMaxX<=m_objPeakInfo->dblPeakMaxX.GetAt(i))
			{
				index=i;
				break;
			}
		}
		if (index==-1)
			index=(int)m_objPeakInfo->dblPeakMaxX.GetSize();

		m_objPeakInfo->dblArea.InsertAt(index,dblTmpArea);
		m_objPeakInfo->dblHeight.InsertAt(index,dblTmpHeight);
		m_objPeakInfo->dblWidth.InsertAt(index,dblTmpWidth);

		m_objPeakInfo->dblPeakStartX.InsertAt(index,m_dblPeakStartX);
		m_objPeakInfo->dblPeakStartY.InsertAt(index,m_dblPeakStartY);

		m_objPeakInfo->dblPeakMaxX.InsertAt(index,m_dblPeakMaxX);

		m_objPeakInfo->dblPeakMaxY.InsertAt(index,m_dblPeakMaxY);

		m_objPeakInfo->dblPeakEndX.InsertAt(index,m_dblPeakEndX);
		m_objPeakInfo->dblPeakEndY.InsertAt(index,m_dblPeakEndY);

		m_objPeakInfo->intPeakStartIndex.InsertAt(index,m_intPeakStartIndex);
		m_objPeakInfo->intPeakMaxIndex.InsertAt(index,m_intPeakMaxIndex);
		m_objPeakInfo->intPeakEndIndex.InsertAt(index,m_intPeakEndIndex);

		//start of sivaganesh's 

		stuPeakDetectPoint obj3;

		//width at 5 percent height 
		{
			dblHalfHeight = dblTmpHeight / 20;

			for(int i = m_intPeakMaxIndex; i>=m_intPeakStartIndex; i--)
			{
				obj3 = m_arrPeakDetectPoint.GetAt(i);
				if((obj3.Y - m_dblPeakStartY) <= dblHalfHeight)
				{
					dblWidthX1 = obj3.X;
					break;
				}
			}

			for(int i = m_intPeakMaxIndex; i<=m_intPeakEndIndex; i++)
			{
				obj3 = m_arrPeakDetectPoint.GetAt(i);
				if((obj3.Y - m_dblPeakEndY/*m_dblPeakStartY /* changed by sivaganesh*/) <= dblHalfHeight)
				{

					dblWidthX2 = obj3.X;
					break;
				}
			}

			double dblCenterX= m_dblPeakMaxX;

			double dblLeftWidth = dblCenterX - dblWidthX1;
			double dblRightWidth = dblWidthX2 - dblCenterX;



			double dblWidth =(dblWidthX2 - dblWidthX1);



			m_dblWidthAt5PercentHeight.InsertAt(index,dblWidth);
			m_dblLeftWidthAt5PercentHeight.InsertAt(index,dblLeftWidth);
			m_dblRightWidthAt5PercentHeight.InsertAt(index,dblRightWidth);

			CString s;
			s.Format(_T("width=%d LW=%d RW=%d"),m_dblWidthAt5PercentHeight.GetSize(),m_dblLeftWidthAt5PercentHeight.GetSize(),m_dblRightWidthAt5PercentHeight.GetSize());
			//AfxMessageBox(s);

		}
		//Width at 10 percent height 
		{
			dblWidthX1 = 0;
			dblWidthX2 = 0;
			dblHalfHeight=0;
			dblHalfHeight = dblTmpHeight / 10;

			for(int i = m_intPeakMaxIndex; i>=m_intPeakStartIndex; i--)
			{
				obj3 = m_arrPeakDetectPoint.GetAt(i);
				if((obj3.Y - m_dblPeakStartY) <= dblHalfHeight)
				{
					dblWidthX1 = obj3.X;
					break;
				}
			}

			for(int i = m_intPeakMaxIndex; i<=m_intPeakEndIndex; i++)
			{
				obj3 = m_arrPeakDetectPoint.GetAt(i);
				if((obj3.Y - m_dblPeakEndY/*m_dblPeakStartY /* changed by sivaganesh*/) <= dblHalfHeight)
				{
					dblWidthX2 = obj3.X;
					break;
				}
			}

			double dblCenterX= m_dblPeakMaxX;

			double dblLeftWidth = dblCenterX - dblWidthX1;
			double dblRightWidth = dblWidthX2 - dblCenterX;

			double dblWidth =(dblWidthX2 - dblWidthX1);


			m_dblWidthAt10PercentHeight.InsertAt(index,dblWidth);
			m_dblLeftWidthAt10PercentHeight.InsertAt(index,dblLeftWidth);
			m_dblRightWidthAt10PercentHeight.InsertAt(index,dblRightWidth);


		}
		//width at half height
		{
			dblWidthX1 = 0;
			dblWidthX2 = 0;
			dblHalfHeight=0;

			dblHalfHeight = dblTmpHeight / 2;

			for(int i = m_intPeakMaxIndex; i>=m_intPeakStartIndex; i--)
			{
				obj3 = m_arrPeakDetectPoint.GetAt(i);
				if((obj3.Y - m_dblPeakStartY) <= dblHalfHeight)
				{
					dblWidthX1 = obj3.X;
					break;
				}
			}

			for(int i = m_intPeakMaxIndex; i<=m_intPeakEndIndex; i++)
			{
				obj3 = m_arrPeakDetectPoint.GetAt(i);
				if((obj3.Y - m_dblPeakEndY/*m_dblPeakStartY /* changed by sivaganesh*/) <= dblHalfHeight)
				{
					dblWidthX2 = obj3.X;
					break;
				}
			}

			double dblCenterX= m_dblPeakMaxX;

			double dblLeftWidth = dblCenterX - dblWidthX1;
			double dblRightWidth = dblWidthX2 - dblCenterX;

			double dblWidth =(dblWidthX2 - dblWidthX1);

			m_dblWidthAtHalfHeight.InsertAt(index,dblWidth);
			m_dblLeftWidthAtHalfHeight.InsertAt(index,dblLeftWidth);
			m_dblRightWidthAtHalfHeight.InsertAt(index,dblRightWidth);

		}

		//end of sivaganesh's code


		/*m_objPeakInfo->dblArea.Add(dblTmpArea);
		m_objPeakInfo->dblHeight.Add(dblTmpHeight);
		m_objPeakInfo->dblWidth.Add(dblTmpWidth);

		m_objPeakInfo->dblPeakStartX.Add(m_dblPeakStartX);
		m_objPeakInfo->dblPeakStartY.Add(m_dblPeakStartY);

		m_objPeakInfo->dblPeakMaxX.Add(m_dblPeakMaxX);

		m_objPeakInfo->dblPeakMaxY.Add(m_dblPeakMaxY);

		m_objPeakInfo->dblPeakEndX.Add(m_dblPeakEndX);
		m_objPeakInfo->dblPeakEndY.Add(m_dblPeakEndY);

		m_objPeakInfo->intPeakStartIndex.Add(m_intPeakStartIndex);
		m_objPeakInfo->intPeakMaxIndex.Add(m_intPeakMaxIndex);
		m_objPeakInfo->intPeakEndIndex.Add(m_intPeakEndIndex);*/

	}
	else
	{
		////filling the structure for baseline correction
		m_objPeakInfo->dblArea.Add(dblTmpArea);
		m_objPeakInfo->dblHeight.Add(dblTmpHeight);
		m_objPeakInfo->dblWidth.Add(dblTmpWidth);

		m_objPeakInfo->dblPeakStartX.Add(m_dblPeakStartX);
		m_objPeakInfo->dblPeakStartY.Add(m_dblPeakStartY);

		m_objPeakInfo->dblPeakMaxX.Add(m_dblPeakMaxX);
		m_objPeakInfo->dblPeakMaxY.Add(m_dblPeakMaxY);

		m_objPeakInfo->dblPeakEndX.Add(m_dblPeakEndX);
		m_objPeakInfo->dblPeakEndY.Add(m_dblPeakEndY);

		m_objPeakInfo->intPeakStartIndex.Add(m_intPeakStartIndex);
		m_objPeakInfo->intPeakMaxIndex.Add(m_intPeakMaxIndex);
		m_objPeakInfo->intPeakEndIndex.Add(m_intPeakEndIndex);


		stuPeakDetectPoint obj3;

		//width at 5 percent height 
		{
			dblHalfHeight = dblTmpHeight / 20;

			for(int i = m_intPeakMaxIndex; i>=m_intPeakStartIndex; i--)
			{
				obj3 = m_arrPeakDetectPoint.GetAt(i);
				if((obj3.Y - m_dblPeakStartY) <= dblHalfHeight)
				{
					dblWidthX1 = obj3.X;
					break;
				}
			}

			for(int i = m_intPeakMaxIndex; i<=m_intPeakEndIndex; i++)
			{
				obj3 = m_arrPeakDetectPoint.GetAt(i);
				if((obj3.Y - m_dblPeakEndY/*m_dblPeakStartY /* changed by sivaganesh*/) <= dblHalfHeight)
				{

					dblWidthX2 = obj3.X;
					break;
				}
			}

			double dblCenterX= m_dblPeakMaxX;

			double dblLeftWidth = dblCenterX - dblWidthX1;
			double dblRightWidth = dblWidthX2 - dblCenterX;

			double dblWidth =(dblWidthX2 - dblWidthX1);

			m_dblWidthAt5PercentHeight.Add(dblWidth);
			m_dblLeftWidthAt5PercentHeight.Add(dblLeftWidth);
			m_dblRightWidthAt5PercentHeight.Add(dblRightWidth);

			CString s;
			s.Format(_T("width1=%d LW1=%d RW1=%d"),m_dblWidthAt5PercentHeight.GetSize(),m_dblLeftWidthAt5PercentHeight.GetSize(),m_dblRightWidthAt5PercentHeight.GetSize());
			//AfxMessageBox(s);

		}
		//Width at 10 percent height 
		{
			dblWidthX1 = 0;
			dblWidthX2 = 0;
			dblHalfHeight=0;
			dblHalfHeight = dblTmpHeight / 10;

			for(int i = m_intPeakMaxIndex; i>=m_intPeakStartIndex; i--)
			{
				obj3 = m_arrPeakDetectPoint.GetAt(i);
				if((obj3.Y - m_dblPeakStartY) <= dblHalfHeight)
				{
					dblWidthX1 = obj3.X;
					break;
				}
			}

			for(int i = m_intPeakMaxIndex; i<=m_intPeakEndIndex; i++)
			{
				obj3 = m_arrPeakDetectPoint.GetAt(i);
				if((obj3.Y - m_dblPeakEndY/*m_dblPeakStartY /* changed by sivaganesh*/) <= dblHalfHeight)
				{
					dblWidthX2 = obj3.X;
					break;
				}
			}

			double dblCenterX= m_dblPeakMaxX;

			double dblLeftWidth = dblCenterX - dblWidthX1;
			double dblRightWidth = dblWidthX2 - dblCenterX;

			double dblWidth =(dblWidthX2 - dblWidthX1);


			m_dblWidthAt10PercentHeight.Add(dblWidth);
			m_dblLeftWidthAt10PercentHeight.Add(dblLeftWidth);
			m_dblRightWidthAt10PercentHeight.Add(dblRightWidth);


		}
		//width at half height
		{
			dblWidthX1 = 0;
			dblWidthX2 = 0;
			dblHalfHeight=0;

			dblHalfHeight = dblTmpHeight / 2;

			for(int i = m_intPeakMaxIndex; i>=m_intPeakStartIndex; i--)
			{
				obj3 = m_arrPeakDetectPoint.GetAt(i);
				if((obj3.Y - m_dblPeakStartY) <= dblHalfHeight)
				{
					dblWidthX1 = obj3.X;
					break;
				}
			}

			for(int i = m_intPeakMaxIndex; i<=m_intPeakEndIndex; i++)
			{
				obj3 = m_arrPeakDetectPoint.GetAt(i);
				if((obj3.Y - m_dblPeakEndY/*m_dblPeakStartY /* changed by sivaganesh*/) <= dblHalfHeight)
				{
					dblWidthX2 = obj3.X;
					break;
				}
			}

			double dblCenterX= m_dblPeakMaxX;

			double dblLeftWidth = dblCenterX - dblWidthX1;
			double dblRightWidth = dblWidthX2 - dblCenterX;

			double dblWidth =(dblWidthX2 - dblWidthX1);

			m_dblWidthAtHalfHeight.Add(dblWidth);
			m_dblLeftWidthAtHalfHeight.Add(dblLeftWidth);
			m_dblRightWidthAtHalfHeight.Add(dblRightWidth);

		}

		//end of sivaganesh's code
	}

	if(m_blnOnlinePeakDetection)
	{
		m_objTempPeakInfo->dblArea.Add(dblTmpArea);
		m_objTempPeakInfo->dblHeight.Add(dblTmpHeight);
		m_objTempPeakInfo->dblWidth.Add(dblTmpWidth);

		m_objTempPeakInfo->dblPeakStartX.Add(m_dblPeakStartX);
		m_objTempPeakInfo->dblPeakStartY.Add(m_dblPeakStartY);

		m_objTempPeakInfo->dblPeakMaxX.Add(m_dblPeakMaxX);
		m_objTempPeakInfo->dblPeakMaxY.Add(m_dblPeakMaxY);

		m_objTempPeakInfo->dblPeakEndX.Add(m_dblPeakEndX);
		m_objTempPeakInfo->dblPeakEndY.Add(m_dblPeakEndY);

		m_objTempPeakInfo->intPeakStartIndex.Add(m_intPeakStartIndex);
		m_objTempPeakInfo->intPeakMaxIndex.Add(m_intPeakMaxIndex);
		m_objTempPeakInfo->intPeakEndIndex.Add(m_intPeakEndIndex);

	}

	int nSize = (int)m_objPeakInfo->intPeakStartIndex.GetSize();

	int nPrevPeakEndIndex, nPrevPeakStartIndex;
	m_objPeakInfo->arrEndPointType.Add(TYPE_BASE);
	if(m_blnOnlinePeakDetection)
		m_objTempPeakInfo->arrEndPointType.Add(TYPE_BASE);

	if(nSize>1)
	{
		nPrevPeakStartIndex =  m_objPeakInfo->intPeakStartIndex.GetAt(nSize-2);
		stuPeakDetectPoint objTemp;
		objTemp = m_arrPeakDetectPoint.GetAt(nPrevPeakStartIndex);

		nPrevPeakEndIndex =  m_objPeakInfo->intPeakEndIndex.GetAt(nSize-2);
		if(nPrevPeakEndIndex == m_intPeakStartIndex)
		{
			if(objTemp.Y > m_dblPeakStartY)
			{
				m_objPeakInfo->arrStartPointType.Add(TYPE_PENETRATION);
				m_objPeakInfo->arrEndPointType.SetAt(nSize-2, TYPE_PENETRATION);
				if(m_blnOnlinePeakDetection)
				{
					m_objTempPeakInfo->arrStartPointType.Add(TYPE_PENETRATION);
					m_objTempPeakInfo->arrEndPointType.SetAt(nSize-2, TYPE_PENETRATION);

				}
			}
			else
			{
				m_objPeakInfo->arrStartPointType.Add(TYPE_VALLEY);
				m_objPeakInfo->arrEndPointType.SetAt(nSize-2, TYPE_VALLEY);
				if(m_blnOnlinePeakDetection)
				{
					m_objTempPeakInfo->arrStartPointType.Add(TYPE_VALLEY);
					m_objTempPeakInfo->arrEndPointType.SetAt(nSize-2, TYPE_VALLEY);

				}
			}
		}
		else
		{
			m_objPeakInfo->arrStartPointType.Add(TYPE_BASE);
			m_objPeakInfo->arrEndPointType.SetAt(nSize-2, TYPE_BASE);
			if(m_blnOnlinePeakDetection)
			{
				m_objTempPeakInfo->arrStartPointType.Add(TYPE_BASE);
				m_objTempPeakInfo->arrEndPointType.SetAt(nSize-2, TYPE_BASE);
			}
		}
	}
	else
	{
		m_objPeakInfo->arrStartPointType.Add(TYPE_BASE);
		if(m_blnOnlinePeakDetection)
			m_objTempPeakInfo->arrStartPointType.Add(TYPE_BASE);

	}



	//end of structure filling
	m_intPeakStatus = FLAT;	

	//m_dblLastPeakEndX = m_dblPeakEndX;
	/*	m_dblPreviousDerivativeX = m_dblCurrentX = m_dblPeakEndX;
	m_dblOldY = m_dblPreviousDerivativeY = m_dblCurrentY = m_dblPeakEndY;    

	m_intCurrentDataPointIndex = m_intPeakEndIndex;
	*/
	FireEvent(eventidOnPeakDetected , EVENT_PARAM(VTS_NONE));
	InitializationsForNextPeak();

	return true;
}
//*************************************************
//PURPOSE : To set the color for a particular point of the Graph
//INPUTS  : long lngGraphIdx   -  Graph Id 
//          long lngPtIdx      -  Index of the point whose color is going to change
//			OLE_COLOR clrColor -  New Color value 
//ASSUMES : -
//RETURNS : 
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::SetGraphPointColor(LONG lngGraphIdx, LONG lngPtIdx, OLE_COLOR clrColor)
{
	if(lngGraphIdx>=0 && lngGraphIdx<m_chart.get_SeriesCount())
	{
		LPDISPATCH pDisp	=	m_chart.Series(lngGraphIdx);
		ISeriesPtr	pSeries	=	pDisp;
		pDisp->Release();
		_bstr_t bstrGraphName=	pSeries->GetName().copy();
		long lIdx=GetLtblIdxFromName(bstrGraphName);
		if(lIdx>=0)
		{
			if(lngPtIdx<=pSeries->GetXValues()->GetCount())
				pSeries->put_PointColor(lngPtIdx,clrColor);
			else
				MessageBox(_T("Point index is out of Range"));
		}
		//SysFreeString(bstrGraphName);
		pSeries	=	NULL;
	}
	else
	{
		MessageBox(_T("Graph with this ID doesn't exist"));
		return;
	}

}
//*************************************************
//PURPOSE : To change the style of the Graph
//INPUTS  : long intGraphIdx    - Graph ID 
//			USHORT unGraphType  - New style of the Graph
// unGraphType = 0  ---->  Line Series   (0)
// unGraphType = 1  ---->  Point Series  (4)
// unGraphType = 2  ---->  Bar Series    (1)
// unGraphType = 3  ---->  ImageBar Series (24)
// unGraphType = 4  ---->  Bubble series (9) // not working in TeeChart Trial version
//ASSUMES : -
//RETURNS : 
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::SetGraphtype(LONG lngGraphIdx, USHORT unGraphType)
{
	if(lngGraphIdx>=0 && lngGraphIdx<m_chart.get_SeriesCount())
	{
		LPDISPATCH pDisp	=	m_chart.Series(lngGraphIdx);
		ISeriesPtr	pSeries	=	pDisp;
		pDisp->Release();
		_bstr_t bstrGraphName=	pSeries->GetName().copy();
		long lIdx=GetLtblIdxFromName(bstrGraphName);
		if(lIdx<0)
		{
			MessageBox(_T("Graph with this specified ID doesn't exist"));
			return;
		}

		if(lIdx>=0)
		{
			switch(unGraphType)
			{
			case 0:
				m_chart.ChangeSeriesType(lngGraphIdx,scLine);
				break;
			case 1:
				m_chart.ChangeSeriesType(lngGraphIdx,scPoint);
				break;
			case 2:
				m_chart.ChangeSeriesType(lngGraphIdx,scBar);
				break;
			case 3:
				m_chart.ChangeSeriesType(lngGraphIdx,scImageBar);
				break;
				/*case 4:
				m_chart.ChangeSeriesType(lngGraphIdx,scBubble);
				break;*/ // This type is commented bcz it is not working in TChart Trial version
			default:					
				MessageBox(_T("Graph Type Range must be within 0-3"));// 0-4"));
				break;
			}

		}

		//AfxMessageBox(_T("heeee"));
		//	SysFreeString(bstrGraphName);
		m_intGraphType	=	unGraphType;
		pSeries	=	NULL;				


		stuRemovableGraphData obj;
		//Call PeakFill function if Peak filling is already enabled and erased bcz of Redrawing
		for(long lngID=0;lngID<m_arrGraphRelatedSerieses.GetCount();lngID++) 
		{
			obj=m_arrGraphRelatedSerieses.GetAt(lngID);
			_bstr_t bstrGraph(obj.bstrGraphName,TRUE);
			if(bstrGraph==bstrGraphName) // Check for the Graph which is equal to the above specified graph
			{
				_bstr_t bstrFill(obj.bstrFillName,TRUE);
				_bstr_t bstrNull(_T(""));
				if(bstrFill!=bstrNull) // Check weather the Peak Fill is enable or not for the specified graph
				{
					PeakFillArea(lngGraphIdx);
				}
			}

		}
	}
	else
	{
		MessageBox(_T("Graph with this specified ID doesn't exist"));
		return;
	}

}
void CEsdAdvancedGraphCtrl::SetGraphVisible(LONG lngGraphIdx, VARIANT_BOOL bShowRHide)
{
	if(lngGraphIdx>=0 && lngGraphIdx<m_chart.get_SeriesCount())
	{	
		LPDISPATCH pDisp	=	m_chart.Series(lngGraphIdx);
		ISeriesPtr	pSeries	=	pDisp;
		pDisp->Release();
		_bstr_t bstrGraphName=	pSeries->GetName().copy();
		long lIdx=GetLtblIdxFromName(bstrGraphName);
		if(lIdx<0)
		{
			pSeries	=	NULL;
			MessageBox(_T("Graph With the specified ID doesn't exist to Show/Hide"));
			return;
		}
		pSeries->PutActive(bShowRHide); // Show or Hide the Graph with specified index



		// Now show/hide the Specified Graph ID's related Graphs i.e Trend line,baseline etc of this Specified Graph.
		stuRemovableGraphData obj;
		long lngRelatedGraphIdx	=	lngGraphIdx;
		obj=m_arrGraphRelatedSerieses.GetAt(lIdx);

		_bstr_t bstrNull=_T("");

		// Hide Linear Fit Graph	
		ISeriesPtr pS=NULL;

		_bstr_t bstrLinearFitGraph(obj.bsrLinearfitName,TRUE);
		if(bstrLinearFitGraph!=bstrNull)  // If it is Equal to bstrNull means there is no Linear fit graph drawn for this Graph ID
		{
			lngRelatedGraphIdx	=	GetGraphIdxFromName(bstrLinearFitGraph);
			pDisp	=	m_chart.Series(lngRelatedGraphIdx);
			pS	=	pDisp;
			pDisp->Release();
			if(lngRelatedGraphIdx>=0)
				pS->PutActive(bShowRHide);
			pS	=	NULL;
		}

		// Hide Graph drawn for Base line 
		_bstr_t bstrBaseLine(obj.bstrBaseLinename,TRUE);
		if(bstrBaseLine!=bstrNull)  // If it is Equal to bstrNull means there is no Base Line drawn for this Graph ID
		{
			lngRelatedGraphIdx	=	GetGraphIdxFromName(bstrBaseLine);
			pDisp	=	m_chart.Series(lngRelatedGraphIdx);
			pS	=	pDisp;
			pDisp->Release();
			if(lngRelatedGraphIdx>=0)
				pS->PutActive(bShowRHide);
			pS	=	NULL;
		}

		// Hide Graph drawn for QuadraticFit 
		_bstr_t bstrQuadraticFit(obj.bstrQuadraticFitName,TRUE);
		if(bstrQuadraticFit!=bstrNull)  // If it is Equal to bstrNull means there is no Quadratic Fit drawn for this Graph ID
		{
			lngRelatedGraphIdx	=	GetGraphIdxFromName(bstrQuadraticFit);
			pDisp	=	m_chart.Series(lngRelatedGraphIdx);
			pS	=	pDisp;
			pDisp->Release();
			if(lngRelatedGraphIdx>=0)
				pS->PutActive(bShowRHide);
			pS	=	NULL;
		}
		// Hide Graph drawn for ExpFit 
		_bstr_t bstrExpFit(obj.bstrExpFit,TRUE);
		if(bstrExpFit!=bstrNull)  // If it is Equal to bstrNull means there is no Quadratic Fit drawn for this Graph ID
		{
			lngRelatedGraphIdx	=	GetGraphIdxFromName(bstrExpFit);
			pDisp	=	m_chart.Series(lngRelatedGraphIdx);
			pS	=	pDisp;
			pDisp->Release();
			if(lngRelatedGraphIdx>=0)
				pS->PutActive(bShowRHide);
			pS	=	NULL;
		}
		// Hide Graph drawn for PowerFit
		_bstr_t bstrPowerFit(obj.bstrPowerFit,TRUE);
		if(bstrPowerFit!=bstrNull)  // If it is Equal to bstrNull means there is no Quadratic Fit drawn for this Graph ID
		{
			lngRelatedGraphIdx	=	GetGraphIdxFromName(bstrPowerFit);
			pDisp	=	m_chart.Series(lngRelatedGraphIdx);
			pS	=	pDisp;
			pDisp->Release();
			if(lngRelatedGraphIdx>=0)
				pS->PutActive(bShowRHide);
			pS	=	NULL;
		}
		// Hide Graph drawn for LogFit 
		_bstr_t bstrLogFit(obj.bstrLogFit,TRUE);
		if(bstrLogFit!=bstrNull)  // If it is Equal to bstrNull means there is no Quadratic Fit drawn for this Graph ID
		{
			lngRelatedGraphIdx	=	GetGraphIdxFromName(bstrLogFit);
			pDisp	=	m_chart.Series(lngRelatedGraphIdx);
			pS	=	pDisp;
			pDisp->Release();
			if(lngRelatedGraphIdx>=0)
				pS->PutActive(bShowRHide);
			pS	=	NULL;
		}

		// Hide Peak Filling graphs (No need to hide this bcz it will automatically hides the filling when Graph hides)
		/*	_bstr_t bstrPeakFill(obj.bstrFillName,TRUE);
		if(bstrPeakFill!=bstrNull)  // If it is Equal to bstrNull means there is no Peak Fill drawn for this Graph ID
		{
		lngRelatedGraphIdx	=	GetGraphIdxFromName(bstrPeakFill);
		pDisp	=	m_chart.Series(lngRelatedGraphIdx);
		pS	=	pDisp;
		pDisp->Release();
		if(lngRelatedGraphIdx>=0)
		pS->PutActive(bShowRHide);
		pS	=	NULL;
		}*/

		// Hide Custom Trend Line
		_bstr_t bstrCustomTrend(obj.bstrCustomTrendLineName,TRUE);
		if(bstrCustomTrend!=bstrNull)  // If it is Equal to bstrNull means there is no Custom TrendLine drawn for this Graph ID
		{
			lngRelatedGraphIdx	=	GetGraphIdxFromName(bstrCustomTrend);
			pDisp	=	m_chart.Series(lngRelatedGraphIdx);
			pS	=	pDisp;
			pDisp->Release();
			if(lngRelatedGraphIdx>=0)
				pS->PutActive(bShowRHide);
			pS	=	NULL;
		}
		pSeries	=	NULL;
	}
	else
	{
		MessageBox(_T("Graph With the specified ID doesn't exist to Show/Hide"));
		return;
	}

}
void CEsdAdvancedGraphCtrl::StartAnimation(VARIANT_BOOL bStartRStop)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	LPDISPATCH pDisp	=	m_chart.get_Aspect();
	IAspectPtr pAspect	=	pDisp;
	pDisp->Release();
	if(bStartRStop)
	{
		pAspect->put_View3D(TRUE);
		pAspect->put_Orthogonal(FALSE);
		pAspect->put_Rotation(1000);
		m_chart.put_TimerEnabled(TRUE);
		m_chart.put_TimerInterval(150);
	}
	if(!bStartRStop)
	{
		pAspect->put_View3D(FALSE);
		pAspect->put_Orthogonal(TRUE);
		//((IAspect*)m_chart.get_Aspect())->put_Rotation(300);
		m_chart.put_TimerEnabled(TRUE);
		//m_chart.put_TimerInterval(150);
	}
	pAspect	=	NULL;
}

//*************************************************
//PURPOSE : To get the direct Control on the inner TeeChart control
//INPUTS  : 
//ASSUMES : -
//RETURNS : IUnknown* ---- TeeChart control pointer
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
IUnknown* CEsdAdvancedGraphCtrl::GetControlUnknown(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	if(m_chart.m_hWnd==NULL)
	{
		AfxMessageBox(_T("Control not created still"));
		return NULL;
	}

	IUnknown *pUnk=NULL;
	pUnk=m_chart.GetControlUnknown();
	pUnk->AddRef();	
	return pUnk;
}

void CEsdAdvancedGraphCtrl::CopyGraph(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	LPDISPATCH pDisp	=	m_chart.get_Export();
	IExportPtr pExport	=	pDisp;
	pDisp->Release();
	pExport->ShowExport();
	pExport	=	NULL;


}

void CEsdAdvancedGraphCtrl::CopyData(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	/*	ISeriesXMLSource *xml;
	CString str=_T("C:\\Documents and Settings\\silpas\\Desktop\\myXml.xml");
	BSTR bstr=SysAllocString(str);
	xml->put_FileName(bstr);
	ITChart *m_pTeeChart;
	LPUNKNOWN pUnk=GetControlUnknown();
	pUnk->QueryInterface(__uuidof(ITChart),(void**)&m_pTeeChart);
	xml->put_Chart(m_pTeeChart);
	xml->Load();*/
	/*CFileDialog fileDlg(FALSE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("Text Files (*.txt)|*.txt|Excel Files (*.xls)|*.xls||"));
	if(fileDlg.DoModal()==IDOK)
	{
	ITextExportPtr	pExport	=	((IExport *)m_chart.get_Export())->asText;
	pExport->IncludeHeader	=	TRUE;
	pExport->IncludeIndex	=	TRUE;
	pExport->IncludeLabels	=	FALSE;
	CString str	=	fileDlg.GetPathName();
	_bstr_t bstrFilePath	=	fileDlg.GetPathName();
	pExport->SaveToFile(bstrFilePath);
	}*/

	LPDISPATCH pDisp	=	m_chart.get_Export();
	IExportPtr pExport	=	pDisp;
	pDisp->Release();
	ITextExportPtr	pTxtExport	=	pExport->GetasText();
	pTxtExport->IncludeHeader	=	TRUE;
	pTxtExport->IncludeIndex	=	TRUE;
	_bstr_t bstrData =	pTxtExport->AsString();
	CString strSource;
	strSource	=	(wchar_t*)bstrData;


	if(OpenClipboard()==TRUE) // Access the ClipBoard
	{
		HGLOBAL clipbuffer;
		TCHAR *buffer;	
		EmptyClipboard();
		clipbuffer = GlobalAlloc(GMEM_FIXED,(strSource.GetLength() + 1)*sizeof(TCHAR)); //Allocate Global memory based on the data size
		buffer = (TCHAR* )GlobalLock(clipbuffer); //lock the buffer
		_tcscpy(buffer, strSource);//copy the data buffer 
		GlobalUnlock(clipbuffer);//unlock the buffer
		SetClipboardData(CF_UNICODETEXT,clipbuffer);//Set the data to the clipboard
		CloseClipboard();//Done with the ClipBoard...close it
		GlobalFree(clipbuffer);
	}

	pExport	=	NULL;
}
//*************************************************************
//PURPOSE : Method to copy the data points onto a clipboard
//			or to Export the data in desired format.
//INPUTS  : -
//ASSUMES : -
//RETURNS : VARIANT_BOOL  - Boolean value.
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
VARIANT_BOOL CEsdAdvancedGraphCtrl::ExportGraphData(LONG lngGraphIdx,LONG lngExpType, VARIANT_BOOL bIncludeIndex, VARIANT_BOOL bIncludeHeader, VARIANT_BOOL bIncludeTitle)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	//this is for exporting 

	LPDISPATCH pDisp	=	m_chart.get_Export();
	IExportPtr pExport	=	pDisp;
	pDisp->Release();
	pExport->ShowExport();


	return VARIANT_TRUE;
}


//*************************************************
//PURPOSE : Method to draw(Display) the Trend line On the Control
//INPUTS  : long lngCalculationGraphIdx -  Graph ID for which Trend line is Calculating
//			LONG lngTrendGraphIdx		-  Index for the Trend Line Graph 
//ASSUMES : -
//RETURNS : 
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::prcDrawTrendLine(LONG lngCalculationGraphIdx, LONG lngTrendGraphIdx)
{

	LPDISPATCH pDisp	=	m_chart.Series(lngCalculationGraphIdx);
	ISeriesPtr pSeries	=	pDisp;
	pDisp->Release();
	if(m_blnLinearFit==TRUE && pSeries->GetYValues()->GetCount()>=2)  //  ->dblXval.GetSize()>=2)  // For Linear Fit there must be atleast 2 data points.
	{

		double dblSlope;
		double dblC;
		double dblX1;
		double dblXn;
		double dblY1;
		double dblYn;

		prcLinearFit(lngCalculationGraphIdx,dblSlope,dblC);	// Call to LinearFit Functions. This will return Slope & Y-intercept.


		dblX1 = pSeries->GetXValues()->GetMinimum();/*-
													(0.15*(pSeries->GetXValues()->GetMinimum()));*/
		dblXn = pSeries->GetXValues()->GetMaximum();/*-
													(0.15*(pSeries->GetXValues()->GetMaximum()));*/


		dblY1 = dblSlope*dblX1+dblC;  // Calculate the new Y1 value.
		dblYn = dblSlope*dblXn+dblC;  // Calculate the new Yn value.



		pDisp	=	m_chart.Series(lngTrendGraphIdx);
		ISeriesPtr pTrendSeries	=	pDisp;
		pDisp->Release();

		pTrendSeries->AddXY(dblX1,dblY1,_T(""),123);
		pTrendSeries->AddXY(dblXn,dblYn,_T(""),123);
		pTrendSeries	=	NULL;

	}

	if(m_blnQuadraticFit==TRUE && pSeries->GetYValues()->GetCount()>=3) // For Quadratic Fit there must be at least 3 data points.
	{
		double dblA0;
		double dblA1;
		double dblA2;
		double dblX1;
		double dblXn;			
		double dblXNewValue;
		double dblYNewValue;			

		prcQuadraticFit(lngCalculationGraphIdx,dblA0,dblA1,dblA2);  // Call to QuadraticFit function. This will return 3 co-efficient values from which Quadratic equation .
		//CString strCoeff;
		//strCoeff.Format(_T("A0: %lf  A1: %lf A2: %lf"),dblA0,dblA1,dblA2);
		//AfxMessageBox(strCoeff);

		// Y = A2XSquare + A1X + A0 can be obtained.

		dblX1 = pSeries->GetXValues()->GetMinimum()
			-(0.15*(pSeries->GetXValues()->GetMinimum()));
		dblXn = pSeries->GetXValues()->GetMaximum()
			+(0.15*(pSeries->GetXValues()->GetMaximum()));

		double dblDiff	=	dblXn - dblX1;
		double dblXIncrement	=	1.0;
		dblXIncrement	=	(dblDiff/500.0);

		for(dblXNewValue = dblX1;dblXNewValue<=dblXn;)
		{
			//AfxMessageBox(L"1");
			dblYNewValue = (dblA2*pow(dblXNewValue,2)) + (dblA1*dblXNewValue) + dblA0;

			// Following table shows the increment of X values for which Y values are obtained.
			//
			//  ----------------------------------------
			//  |    X value              Increment    |
			//  ----------------------------------------      
			//  |     <= 100                0.1		   |	
			//	|									   |	
			//	----------------------------------------		
			//  |     >100 & <= 500         0.2		   |		
			//	|									   |	
			//  ----------------------------------------
			//	|	 >500 & <= 1000		    0.5		   |	
			//  |                                      |   
			//  ----------------------------------------
			//  |     >1000                 1          |
			//  |                                      |
			//  ----------------------------------------
			//	
			//Commented by swathi...
			//{
			/*if(dblXNewValue<=100)				
			dblXNewValue+=0.1;
			else if(dblXNewValue>100 && dblXNewValue<=500)
			dblXNewValue+=0.2;
			else if(dblXNewValue>500 && dblXNewValue<=1000)
			dblXNewValue+=0.5;
			else
			dblXNewValue+=1;*/

			//Swathi}.............		

			dblXNewValue	=	dblXNewValue + dblXIncrement; 

			dblYNewValue = (dblA2*pow(dblXNewValue,2)) + (dblA1*dblXNewValue) + dblA0; // Calculate the new Y value.

			pDisp	=	m_chart.Series(lngTrendGraphIdx);
			ISeriesPtr pTrendSeries	=	pDisp;
			pDisp->Release();
			pTrendSeries->AddXY(dblXNewValue,dblYNewValue,_T(""),123);
			pTrendSeries->AddXY(dblXNewValue,dblYNewValue,_T(""),123);
			pTrendSeries	=	NULL;
		}			
	}
	if(m_blnPowerFit ==TRUE&&  pSeries->GetYValues()->GetCount()>=2) // For Power-Curve Fit there must be atleast 2 data points.
	{
		double dblA;
		double dblB;
		double dblX1;
		double dblXn;			
		double dblXNewValue;
		double dblYNewValue;
		double dblX,dblY;
		//POINT pt1,pt2;

		prcFitPowerCurve(lngCalculationGraphIdx,dblA,dblB);  // Call to FitPowerCurve function. This will return A & B co-efficients from which Power-Curve equation .
		// y = Ax^B can be obtained.

		dblX1 = pSeries->GetXValues()->GetMinimum()-
			(0.15*(pSeries->GetXValues()->GetMinimum()));
		dblXn = pSeries->GetXValues()->GetMaximum()-
			(0.15*(pSeries->GetXValues()->GetMaximum()));


		for(dblXNewValue = dblX1;dblXNewValue<=dblXn;)
		{
			dblYNewValue = dblA*(pow(dblXNewValue,dblB));

			dblX = dblXNewValue*pow(10.0,m_intXPrecision);
			dblY = dblYNewValue*pow(10.0,m_intYPrecision);

			// Following table shows the increment of X values for which Y values are obtained.
			//
			//  ----------------------------------------
			//  |    X value              Increment    |
			//  ----------------------------------------      
			//  |     <= 100                0.1		   |	
			//	|									   |	
			//	----------------------------------------		
			//  |     >100 & <= 500         0.2		   |		
			//	|									   |	
			//  ----------------------------------------
			//	|	 >500 & <= 1000		    0.5		   |	
			//  |                                      |   
			//  ----------------------------------------
			//  |     >1000                 1          |
			//  |                                      |
			//  ----------------------------------------
			//	

			if(dblXNewValue<=100)				
				dblXNewValue+=0.1;
			else if(dblXNewValue>100 && dblXNewValue<=500)
				dblXNewValue+=0.2;
			else if(dblXNewValue>500 && dblXNewValue<=1000)
				dblXNewValue+=0.5;
			else
				dblXNewValue+=1;

			dblYNewValue = dblA*(pow(dblXNewValue,dblB));
			double dblX2	=	dblXNewValue;
			double dblY2	=	dblYNewValue;

			pDisp	=	m_chart.Series(lngTrendGraphIdx);
			ISeriesPtr pTrendSeries	=	pDisp;
			pDisp->Release();
			pTrendSeries->AddXY(dblX,dblY,_T(""),123);
			pTrendSeries->AddXY(dblX2,dblY2,_T(""),123);
			pTrendSeries	=	NULL;
		}			
	}

	if(m_blnLogFit==TRUE && pSeries->GetYValues()->GetCount()>=2) // For Log-Curve Fit there must be atleast 2 data points.
	{
		double dblA;
		double dblB;
		double dblX1;
		double dblXn;			
		double dblXNewValue;
		double dblYNewValue;
		double dblY,dblX;

		prcFitLogCurve(lngCalculationGraphIdx,dblA,dblB);  // Call to FitLogCurve function. This will return A & B co-efficients from which Logarithmic-Curve equation .
		// y = A+(B*ln(x)) can be obtained.

		dblX1 = pSeries->GetXValues()->GetMinimum()- (0.15*(pSeries->GetXValues()->GetMinimum()));
		dblXn = pSeries->GetXValues()->GetMaximum()- (0.15*(pSeries->GetXValues()->GetMaximum()));

		for(dblXNewValue = dblX1;dblXNewValue<=dblXn;)
		{
			dblYNewValue = dblA+(dblB * log(dblXNewValue));

			dblX = dblXNewValue*pow(10.0,m_intXPrecision);
			dblY = dblYNewValue*pow(10.0,m_intYPrecision);

			// Following table shows the increment of X values for which Y values are obtained.
			//
			//  ----------------------------------------
			//  |    X value              Increment    |
			//  ----------------------------------------      
			//  |     <= 100                0.1		   |	
			//	|									   |	
			//	----------------------------------------		
			//  |     >100 & <= 500         0.2		   |		
			//	|									   |	
			//  ----------------------------------------
			//	|	 >500 & <= 1000		    0.5		   |	
			//  |                                      |   
			//  ----------------------------------------
			//  |     >1000                 1          |
			//  |                                      |
			//  ----------------------------------------
			//	

			if(dblXNewValue<=100)				
				dblXNewValue+=0.1;
			else if(dblXNewValue>100 && dblXNewValue<=500)
				dblXNewValue+=0.2;
			else if(dblXNewValue>500 && dblXNewValue<=1000)
				dblXNewValue+=0.5;
			else
				dblXNewValue+=1;

			dblYNewValue = dblA+(dblB * log(dblXNewValue));

			double dblX2	=	dblXNewValue;
			double dblY2	=	dblYNewValue;
			pDisp	=	m_chart.Series(lngTrendGraphIdx);
			ISeriesPtr pTrendSeries	=	pDisp;
			pDisp->Release();
			pTrendSeries->AddXY(dblX,dblY,_T(""),123);
			pTrendSeries->AddXY(dblX2,dblY2,_T(""),123);
			pTrendSeries	=	NULL;
		}			
	}

	if(m_blnExpFit==TRUE && pSeries->GetYValues()->GetCount()>=2) // For Exp-Curve Fit there must be atleast 2 data points.
	{
		double dblA;
		double dblB;
		double dblX1;
		double dblXn;			
		double dblXNewValue;
		double dblYNewValue;
		double dblX,dblY;

		prcFitExpCurve(lngCalculationGraphIdx,dblA,dblB);  // Call to FitExpCurve function. This will return A & B co-efficients from which Exponential-Curve equation .
		// y = Ae^(Bx) can be obtained.

		dblX1 = pSeries->GetXValues()->GetMinimum()- (0.15*(pSeries->GetXValues()->GetMinimum()));
		dblXn = pSeries->GetXValues()->GetMaximum()- (0.15*(pSeries->GetXValues()->GetMaximum()));

		for(dblXNewValue = dblX1;dblXNewValue<=dblXn;)
		{
			dblYNewValue = dblA*(exp(dblB * dblXNewValue));

			dblX = dblXNewValue*pow(10.0,m_intXPrecision);
			dblY = dblYNewValue*pow(10.0,m_intYPrecision);

			// Following table shows the increment of X values for which Y values are obtained.
			//
			//  ----------------------------------------
			//  |    X value              Increment    |
			//  ----------------------------------------      
			//  |     <= 100                0.1		   |	
			//	|									   |	
			//	----------------------------------------		
			//  |     >100 & <= 500         0.2		   |		
			//	|									   |	
			//  ----------------------------------------
			//	|	 >500 & <= 1000		    0.5		   |	
			//  |                                      |   
			//  ----------------------------------------
			//  |     >1000                 1          |
			//  |                                      |
			//  ----------------------------------------
			//	

			if(dblXNewValue<=100)				
				dblXNewValue+=0.1;
			else if(dblXNewValue>100 && dblXNewValue<=500)
				dblXNewValue+=0.2;
			else if(dblXNewValue>500 && dblXNewValue<=1000)
				dblXNewValue+=0.5;
			else
				dblXNewValue+=1;

			dblYNewValue = dblA*(exp(dblB * dblXNewValue));

			double dblX2	=	dblXNewValue;
			double dblY2	=	dblYNewValue;
			pDisp	=	m_chart.Series(lngTrendGraphIdx);
			ISeriesPtr pTrendSeries	=	pDisp;
			pDisp->Release();
			pTrendSeries->AddXY(dblX,dblY,_T(""),123);
			pTrendSeries->AddXY(dblX2,dblY2,_T(""),123);
			pTrendSeries	=	NULL;
		}			
	}

	pSeries	=	NULL;
	/*
	if(temp->bShow && temp->bUserTrendLine == TRUE && temp->dblXval.GetSize()>= (temp->intDegree+1))
	{
	double dblX1;
	double dblXn;			
	double dblXNewValue;
	double dblYNewValue;			
	POINT pt1,pt2;
	dblX1 = (temp->lngMinOfXval)/pow(10,m_intXPrecision)-
	(0.15*(temp->lngMaxOfXval-temp->lngMinOfXval)/pow(10,m_intXPrecision));
	dblXn = (temp->lngMaxOfXval)/pow(10,m_intXPrecision)+
	(0.15*(temp->lngMaxOfXval-temp->lngMinOfXval)/pow(10,m_intXPrecision));			

	for(dblXNewValue = dblX1;dblXNewValue<=dblXn;)
	{
	//dblYNewValue = (dblA2*pow(dblXNewValue,2)) + (dblA1*dblXNewValue) + dblA0;
	dblYNewValue   = 0;

	for(int k = temp->intDegree;k>=0;k--)
	dblYNewValue+= temp->dblCoEfficients[k]*pow(dblXNewValue,(temp->intDegree - k));



	pt1.x = dblXNewValue*pow(10,m_intXPrecision);
	pt1.y = dblYNewValue*pow(10,m_intYPrecision);

	// Following table shows the increment of X values for which Y values are obtained.
	//
	//  ----------------------------------------
	//  |    X value              Increment    |
	//  ----------------------------------------      
	//  |     <= 100                0.1		   |	
	//	|									   |	
	//	----------------------------------------		
	//  |     >100 & <= 500         0.2		   |		
	//	|									   |	
	//  ----------------------------------------
	//	|	 >500 & <= 1000		    0.5		   |	
	//  |                                      |   
	//  ----------------------------------------
	//  |     >1000                 1          |
	//  |                                      |
	//  ----------------------------------------
	//	

	if(dblXNewValue<=100)				
	dblXNewValue+=0.1;
	else if(dblXNewValue>100 && dblXNewValue<=500)
	dblXNewValue+=0.2;
	else if(dblXNewValue>500 && dblXNewValue<=1000)
	dblXNewValue+=0.5;
	else
	dblXNewValue+=1;

	//dblYNewValue = (dblA2*pow(dblXNewValue,2)) + (dblA1*dblXNewValue) + dblA0; // Calculate thenew Y value.
	dblYNewValue   = 0;

	for(k = temp->intDegree;k>=0;k--)
	dblYNewValue+= temp->dblCoEfficients[k]*pow(dblXNewValue,(temp->intDegree - k));

	pt2.x = dblXNewValue*pow(10,m_intXPrecision);
	pt2.y = dblYNewValue*pow(10,m_intYPrecision);

	prcCalculatePoints(pt1,pt2);    // Call to Calculate Points method.

	if(pt1.x >= m_lngXmin && pt1.x <= m_lngXmax && pt2.x >= m_lngXmin && pt2.x <= m_lngXmax && pt1.y >= m_lngYmin && pt1.y	<= m_lngYmax && pt2.y >= m_lngYmin && pt2.y	<= m_lngYmax)
	{

	MoveToEx(di.hdcDraw,pt1.x,m_lngYmax-pt1.y+m_lngYmin,NULL); 
	LineTo(di.hdcDraw,pt2.x,m_lngYmax-pt2.y+m_lngYmin);			
	}
	}
	}

	SelectObject(di.hdcDraw,oldPen);
	DeleteObject(pen);
	DeleteObject(oldPen);*/
	//}
}

//*************************************************
//PURPOSE : Method to find the Linear fit values
//INPUTS  : long lngGraphIdx   -  Graph ID for which Linear fitting Values are Calculating
//			
//ASSUMES : -
//RETURNS : double dblSlope	-  Resultant Linear Fit value(Slope)
//			double dblC	    -  Resultant Linear Fit Value(Intercept)
//			i.e Coefficients of the Equation  Y=mX+C
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::prcLinearFit(LONG lngGraphIdx, double & dblSlope, double & dblC)
{
	double dblNumerator;
	double dblDenominator;
	double dblSumXY=0;
	double dblSumX=0;
	double dblSumY=0;
	double dblSumXSquare=0;

	//EsdGRAPH_STRUCT* temp = m_objSamples->GetAt(GraphID); // Get the address of the Graph.
	ISeriesPtr	pSeries	=	m_chart.Series(lngGraphIdx);

	long intN = pSeries->GetXValues()->GetCount();	

	for(long i=0;i<intN;i++)
	{
		dblSumX+= pSeries->GetXValues()->GetValue(i);
		dblSumY+= pSeries->GetYValues()->GetValue(i);
		dblSumXY+=pSeries->GetXValues()->GetValue(i) * (pSeries->GetYValues()->GetValue(i));
		dblSumXSquare+=pow((pSeries->GetXValues()->GetValue(i)),2);
	}

	dblNumerator = ((intN*dblSumXY)-(dblSumX*dblSumY));
	dblDenominator = ((intN*dblSumXSquare)-(dblSumX*dblSumX));

	if(dblDenominator!=0)
		dblSlope = dblNumerator/dblDenominator;
	dblNumerator = ((dblSumY*dblSumXSquare)-(dblSumX*dblSumXY));
	if(dblDenominator!=0)
		dblC = dblNumerator/dblDenominator;	

	pSeries	=	NULL;
}

//*************************************************
//PURPOSE : Method to find the Quadratic fit values
//INPUTS  : long lngGraphIdx   -  Graph ID for which Quadratic fitting 
//			Values are Calculating
//ASSUMES : -
//RETURNS : double dblA0	-  Resultant Quadratic Fit value
//			double dblA1	-  Resultant Quadratic Fit Value
//			double dblA2	-  Resultant Quadratic Fit value
//         i.e Coefficients of the Equation  Y=A0X2+A1X+A2
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::prcQuadraticFit(LONG lngGraphIdx, double & dblA0, double & dblA1, double & dblA2)
{
	// Function to calculate the co-efficients of Quadratic Fit.

	double dblP1;
	double dblP2;
	double dblDelta1;
	double dblDelta2;
	double dblDelta3;
	double dblDelta4;
	double dblSumX=0;
	double dblSumY=0;
	double dblSumXY=0;
	double dblSumXSquare=0;
	double dblSumXSquareY=0;
	double dblSumXCube=0;
	double dblSumXFour=0;
	//	EsdGRAPH_STRUCT* temp = m_objSamples->GetAt(GraphID);	

	LPDISPATCH pDisp	=	m_chart.Series(lngGraphIdx);
	ISeriesPtr	pSeries	=	pDisp;
	pDisp->Release();
	long  intN =	pSeries->GetYValues()->GetCount();	

	for(int i=0;i<intN;i++)
	{
		dblSumX+= pSeries->GetXValues()->GetValue(i);
		dblSumY+= pSeries->GetYValues()->GetValue(i);
		dblSumXY+=(pSeries->GetXValues()->GetValue(i)) * (pSeries->GetYValues()->GetValue(i));
		dblSumXSquare+=pow((pSeries->GetXValues()->GetValue(i)),2);

		dblSumXSquareY+=pow((pSeries->GetXValues()->GetValue(i)),2)* (pSeries->GetYValues()->GetValue(i));

		dblSumXCube+=pow((pSeries->GetXValues()->GetValue(i)),3);
		dblSumXFour+=pow((pSeries->GetXValues()->GetValue(i)),4);		
	}	

	dblP1  = (dblSumX*dblSumY)-(intN*dblSumXY);
	dblP2 =  (dblSumXSquare*dblSumXY)-(dblSumX*dblSumXSquareY);
	dblDelta1 = pow(dblSumX,2)-(intN*dblSumXSquare);
	dblDelta2 = (dblSumX*dblSumXSquare)-(intN*dblSumXCube);
	dblDelta3 = pow(dblSumXSquare,2)-(dblSumX*dblSumXCube);
	dblDelta4 = (dblSumXSquare*dblSumXCube)-(dblSumX*dblSumXFour);

	if((dblDelta1*dblDelta4)-(dblDelta2*dblDelta3)!=0)
		dblA1 = ((dblP1*dblDelta4)-(dblP2*dblDelta2))/
		((dblDelta1*dblDelta4)-(dblDelta2*dblDelta3));	

	if((dblDelta2*dblDelta3)-(dblDelta1*dblDelta4)!=0)
		dblA2 = ((dblP1*dblDelta3)-(dblP2*dblDelta1))/
		((dblDelta2*dblDelta3)-(dblDelta1*dblDelta4));

	dblA0 = (dblSumY-(dblA1*dblSumX)-(dblA2*dblSumXSquare))/intN;

	pSeries	=	NULL;

}
//*************************************************
//PURPOSE : Calculates the A & B Coefficients of Power-Curve y=Ax^B, for  a particular graph.
//INPUTS  : int GraphID     -   Graph ID
//			double& dblA    -   Reference variable for A-Coefficient
//			double& dblB    -   Reference variable for B-Coefficient	
//ASSUMES : -
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::prcFitPowerCurve(int GraphID, double &dblA, double &dblB)
{
	int i=0;
	LPDISPATCH pDisp	=	m_chart.Series(GraphID);
	ISeriesPtr	pSeries	=	pDisp;
	pDisp->Release();
	long  intNoOfPoints =	pSeries->GetYValues()->GetCount();	
	double *dblNewX		= new double[intNoOfPoints];
	double *dblNewY		= new double[intNoOfPoints];
	double dblA_Coeff, dblB_Coeff;

	for(i=0;i<intNoOfPoints;i++)
	{
		dblNewX[i] = log( pSeries->GetXValues()->GetValue(i));
		dblNewY[i] = log( pSeries->GetYValues()->GetValue(i));
	}

	//	BOOL blnRetVal;

	SAFEARRAY *pSa,*pSa1;
	SAFEARRAYBOUND sab[1];
	sab[0].cElements=intNoOfPoints;
	sab[0].lLbound=0;
	pSa=SafeArrayCreate(VT_R8,1,sab);
	pSa1=SafeArrayCreate(VT_R8,1,sab);

	for(long i=0;i<intNoOfPoints;i++)
	{
		SafeArrayPutElement(pSa,&i,&dblNewX[i]);
		SafeArrayPutElement(pSa1,&i,&dblNewY[i]);
	}

	VARIANT varX,varY;
	VariantClear(&varX);
	VariantClear(&varY);

	varX.vt=VT_ARRAY|VT_R8;
	varY.vt=VT_ARRAY|VT_R8;

	varX.parray=pSa;
	varY.parray=pSa1;

	FindLinearCoefficients(intNoOfPoints,varX,varY,&dblB_Coeff,&dblA_Coeff);

	delete [] dblNewX;
	delete [] dblNewY;
	pSeries	=	NULL;

	SafeArrayDestroy(pSa);
	SafeArrayDestroy(pSa1);

	dblA = exp(dblA_Coeff);
	dblB = dblB_Coeff;
}

//*************************************************
//PURPOSE : Calculates the A & B Coefficients of Logarithmic-Curve y=A+(B*ln(x)), for  a particular graph.
//INPUTS  : int GraphID     -   Graph ID
//			double& dblA    -   Reference variable for A-Coefficient
//			double& dblB    -   Reference variable for B-Coefficient	
//ASSUMES : -
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 05-05-06
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::prcFitLogCurve(int GraphID, double &dblA, double &dblB)
{
	int i=0;
	LPDISPATCH pDisp	=	m_chart.Series(GraphID);
	ISeriesPtr	pSeries	=	pDisp;
	pDisp->Release();
	long  intNoOfPoints =	pSeries->GetYValues()->GetCount();	
	double *dblNewX = new double[intNoOfPoints];
	double *dblNewY = new double[intNoOfPoints];
	double dblA_Coeff, dblB_Coeff;

	for(i=0;i<intNoOfPoints;i++)
	{
		dblNewX[i] = log(pSeries->GetXValues()->GetValue(i));
		dblNewY[i] = (pSeries->GetYValues()->GetValue(i));
	}

	//	BOOL blnRetVal;
	SAFEARRAY *pSa,*pSa1;
	SAFEARRAYBOUND sab[1];
	sab[0].cElements=intNoOfPoints;
	sab[0].lLbound=0;
	pSa=SafeArrayCreate(VT_R8,1,sab);
	pSa1=SafeArrayCreate(VT_R8,1,sab);

	for(long i=0;i<intNoOfPoints;i++)
	{
		SafeArrayPutElement(pSa,&i,&dblNewX[i]);
		SafeArrayPutElement(pSa1,&i,&dblNewY[i]);
	}

	VARIANT varX,varY;
	VariantClear(&varX);
	VariantClear(&varY);

	varX.vt=VT_ARRAY|VT_R8;
	varY.vt=VT_ARRAY|VT_R8;

	varX.parray=pSa;
	varY.parray=pSa1;
	FindLinearCoefficients(intNoOfPoints,varX,varY,&dblB_Coeff,&dblA_Coeff);

	delete [] dblNewX;
	delete [] dblNewY;

	pSeries	=	NULL;


	SafeArrayDestroy(pSa);
	SafeArrayDestroy(pSa1);
	dblA = dblA_Coeff;
	dblB = dblB_Coeff;
}
//*************************************************
//PURPOSE : Calculates the A & B Coefficients of Exponential-Curve y=Ae^(Bx), for  a particular graph.
//INPUTS  : int GraphID     -   Graph ID
//			double& dblA    -   Reference variable for A-Coefficient
//			double& dblB    -   Reference variable for B-Coefficient	
//ASSUMES : -
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : -
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::prcFitExpCurve(int GraphID, double &dblA, double &dblB)
{
	int i=0;
	LPDISPATCH pDisp	=	m_chart.Series(GraphID);
	ISeriesPtr	pSeries	=	pDisp;
	pDisp->Release();
	long  intNoOfPoints =	pSeries->GetYValues()->GetCount();
	double *dblNewX = new double[intNoOfPoints];
	double *dblNewY = new double[intNoOfPoints];
	double dblA_Coeff, dblB_Coeff;

	for(i=0;i<intNoOfPoints;i++)
	{
		dblNewX[i] = (pSeries->GetXValues()->GetValue(i));
		dblNewY[i] = log(pSeries->GetYValues()->GetValue(i));
	}

	//	BOOL blnRetVal;


	SAFEARRAY *pSa,*pSa1;
	SAFEARRAYBOUND sab[1];
	sab[0].cElements=intNoOfPoints;
	sab[0].lLbound=0;
	pSa=SafeArrayCreate(VT_R8,1,sab);
	pSa1=SafeArrayCreate(VT_R8,1,sab);

	for(long i=0;i<intNoOfPoints;i++)
	{
		SafeArrayPutElement(pSa,&i,&dblNewX[i]);
		SafeArrayPutElement(pSa1,&i,&dblNewY[i]);
	}

	VARIANT varX,varY;
	VariantClear(&varX);
	VariantClear(&varY);

	varX.vt=VT_ARRAY|VT_R8;
	varY.vt=VT_ARRAY|VT_R8;

	varX.parray=pSa;
	varY.parray=pSa1;
	FindLinearCoefficients(intNoOfPoints,varX,varY,&dblB_Coeff,&dblA_Coeff);

	delete [] dblNewX;
	delete [] dblNewY;
	pSeries	=	NULL;
	SafeArrayDestroy(pSa);
	SafeArrayDestroy(pSa1);

	dblA = exp(dblA_Coeff);
	dblB = dblB_Coeff;
}
//*************************************************
//PURPOSE : To enable/disable the CurveFitType for a graph.
//INPUTS  : long GraphID           -  Graph ID
//			long lngTrendLineType  -  Curve Fit Type
//			BOOL bShowTrendLine    -  Boolean Value Indicating Show/Hide
//          LONG lngTrendLineColor -  Color of this Trend line
//ASSUMES : -
//RETURNS : 
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::CalculateTrendLine(LONG lngGraphIdx, LONG lngTrendLineType, VARIANT_BOOL bShowTrendline, LONG lngTrendLineColor)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	//------------------------------------------
	//|					    |				   |	
	//| intTrendLine value  |    CurveFit      |
	//------------------------------------------
	//|						|				   | 	
	//|			1			|	Linear Fit.	   |	
	//|			2           |   Quadratic Fit. |	
	//|						|    			   |	
	//------------------------------------------

	if(lngGraphIdx>=0 && lngGraphIdx< m_chart.get_SeriesCount())			   // Check whether GraphID exists or not.
	{

		/// Check weather the Given Graph ID is Existed or not
		LPDISPATCH pDisp	=	m_chart.Series(lngGraphIdx);
		ISeriesPtr	pSeries	=	pDisp;
		pDisp->Release();
		_bstr_t bstrGraphName = pSeries->GetName().copy();
		long idx=GetLtblIdxFromName(bstrGraphName);
		if(idx<0)
		{
			MessageBox(_T("Graph with this ID doesn't exist"));
			return;
		}

		// Check the Trend line type specified by the user is valid or not
		if(lngTrendLineType<1 && lngTrendLineType>5) 
		{
			MessageBox(_T("Trend line type must be between 1 to 5"));
			return;
		}
		_bstr_t bstr1(_T(""));

		long lTrendLineIdx=m_chart.AddSeries(0); // Graph for Trend Line
		pDisp	=	m_chart.Series(lTrendLineIdx);
		ISeriesPtr	pTrendSeries	=	pDisp;
		pDisp->Release();
		pTrendSeries->ShowInLegend	=	VARIANT_FALSE;// Hide the Graph name in Legend Rectangle

		stuRemovableGraphData obj=m_arrGraphRelatedSerieses.GetAt(idx);
		if(lngTrendLineType==1)
		{
			m_blnLinearFit		=	TRUE;
			m_blnQuadraticFit	=	FALSE;
			m_blnLogFit			=	FALSE;
			m_blnPowerFit		=	FALSE;
			m_blnExpFit			=	FALSE;

			bstr1=_T("");
			_bstr_t bstr2(obj.bsrLinearfitName,TRUE);

			if(bstr1==bstr2) //Check, Linear fit curve is not exists to this Graph
				obj.bsrLinearfitName = pTrendSeries->GetName().copy();

			else // If Linear fit curve is Already exists for this graph,remove the old one and draw new Curve
			{
				long subidx=GetGraphIdxFromName(bstr2);
				m_chart.RemoveSeries(subidx);
				obj.bsrLinearfitName = (pTrendSeries->GetName()).copy();
			}
		}
		else if(lngTrendLineType==2)
		{
			m_blnLinearFit		=	FALSE;
			m_blnQuadraticFit	=	TRUE;
			m_blnLogFit			=	FALSE;
			m_blnPowerFit		=	FALSE;
			m_blnExpFit			=	FALSE;

			bstr1=_T("");
			_bstr_t bstr2(obj.bstrQuadraticFitName,TRUE);

			if(bstr1==bstr2)//Check, Quadratic fit curve is not drawn to this Graph
				obj.bstrQuadraticFitName = pTrendSeries->GetName().copy();
			else // If Quadratic fit curve is Already exists for this graph,remove the old one and draw new Curve
			{
				long subidx	=	GetGraphIdxFromName(bstr2);
				m_chart.RemoveSeries(subidx);
				SysFreeString(obj.bstrQuadraticFitName);
				obj.bstrQuadraticFitName = pTrendSeries->GetName().copy();
			}
		}
		if(lngTrendLineType==3) //log fit
		{
			m_blnLinearFit		=	FALSE;
			m_blnQuadraticFit	=	FALSE;
			m_blnLogFit			=	TRUE;
			m_blnPowerFit		=	FALSE;
			m_blnExpFit			=	FALSE;

			bstr1=_T("");
			_bstr_t bstr2(obj.bstrLogFit,TRUE);
			if(bstr1==bstr2) //Check, Linear fit curve is not exists to this Graph
				obj.bstrLogFit = pTrendSeries->GetName().copy();
			else // If Linear fit curve is Already exists for this graph,remove the old one and draw new Curve
			{
				long subidx=GetGraphIdxFromName(bstr2);
				m_chart.RemoveSeries(subidx);
				obj.bstrLogFit = (pTrendSeries->GetName()).copy();
			}
		}
		if(lngTrendLineType==4) //Exp Fit
		{
			m_blnLinearFit		=	FALSE;
			m_blnQuadraticFit	=	FALSE;
			m_blnLogFit			=	FALSE;
			m_blnPowerFit		=	FALSE;
			m_blnExpFit			=	TRUE;

			bstr1=_T("");
			_bstr_t bstr2(obj.bstrExpFit,TRUE);
			if(bstr1==bstr2) //Check, Linear fit curve is not exists to this Graph
				obj.bstrExpFit = (pTrendSeries->GetName()).copy();
			else // If Linear fit curve is Already exists for this graph,remove the old one and draw new Curve
			{
				long subidx=GetGraphIdxFromName(bstr2);
				m_chart.RemoveSeries(subidx);
				obj.bstrExpFit = (pTrendSeries->GetName()).copy();
			}
		}
		if(lngTrendLineType==5) //power fit
		{
			m_blnLinearFit		=	FALSE;
			m_blnQuadraticFit	=	FALSE;
			m_blnLogFit			=	FALSE;
			m_blnPowerFit		=	TRUE;
			m_blnExpFit			=	FALSE;

			bstr1=_T("");
			_bstr_t bstr2(obj.bsrLinearfitName,TRUE);
			if(bstr1==bstr2) //Check, Linear fit curve is not exists to this Graph
				obj.bstrPowerFit = (pTrendSeries->GetName()).copy();
			else // If Linear fit curve is Already exists for this graph,remove the old one and draw new Curve
			{
				long subidx=GetGraphIdxFromName(bstr2);
				m_chart.RemoveSeries(subidx);
				obj.bstrPowerFit = (pTrendSeries->GetName()).copy();
			}
		}

		m_arrGraphRelatedSerieses.SetAt(idx,obj);

		pTrendSeries->put_Color(lngTrendLineColor);
		pTrendSeries->put_Active( bShowTrendline);
		if(bShowTrendline)
			prcDrawTrendLine(lngGraphIdx,lTrendLineIdx);


		pSeries	=	NULL;
		pTrendSeries	=	NULL;

	}
	else
	{		
		MessageBox(_T("Graph ID does not exist"),NULL,0);
	}

	//	AfxMessageBox(L"T Line");

}


//*************************************************
//PURPOSE :  To find the Linear Coefficients for the given data
//INPUTS  : LONG lngDataCount		  - Total number of Data points
//			VARIANT varDdblArrXData	  - array of X Coordinate points
//			VARIANT varDblArrYData	  - Array of Y Coordinate points
//			
//ASSUMES : 
//RETURNS : DOUBLE *Slope		- value Which holds resultant Slope value
//			DOUBLE *Intercept	- Value Which holds resultant Intercept value.
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
VARIANT_BOOL CEsdAdvancedGraphCtrl::FindLinearCoefficients(LONG lngDataCount, VARIANT &varDblArrXData, VARIANT &varDblArrYData, DOUBLE* dblSlope, DOUBLE* dblIntercept)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	double dblNumerator;
	double dblDenominator;
	double dblSumXY=0;
	double dblSumX=0;
	double dblSumY=0;
	double dblSumXSquare=0;	

	long lngLBound,lngUBound,lngResultBound;

	// The arrays created must be of the same size as the data count present in VARIANT's
	// If not it will give assertion in while retrieving data from VARIANT"s to Double in 'fncGetDoubleValuesFromSafeArry' function
	VARIANT var;
	VariantInit(&var);
	VariantCopy(&var,&varDblArrXData);
	SafeArrayGetLBound(var.parray,1,&lngLBound);
	SafeArrayGetUBound(var.parray,1,&lngUBound);

	lngResultBound	=	lngUBound	-	lngLBound;

	double *dblArrXData=new double[lngResultBound];

	SafeArrayGetLBound(varDblArrYData.parray,1,&lngLBound);
	SafeArrayGetUBound(varDblArrYData.parray,1,&lngUBound);
	lngUBound	=6;
	lngResultBound	=	lngUBound	-	lngLBound;


	double *dblArrYData=new double[lngResultBound];

	long lSize=fncGetDoubleValuesFromSafeArray(varDblArrXData,dblArrXData);

	if(lngDataCount>lSize)
		lngDataCount	=	lSize;
	lSize=fncGetDoubleValuesFromSafeArray(varDblArrYData,dblArrYData);

	if(lngDataCount>lSize)
		lngDataCount=lSize;

	for(int i=0;i<lngDataCount;i++)
	{
		dblSumX += dblArrXData[i];
		dblSumY += dblArrYData[i];
		dblSumXY += dblArrXData[i] * dblArrYData[i];
		dblSumXSquare +=pow(dblArrXData[i],2);
	}

	dblNumerator = ((lngDataCount*dblSumXY)-(dblSumX*dblSumY));
	dblDenominator = ((lngDataCount*dblSumXSquare)-(dblSumX*dblSumX));

	if(dblDenominator!=0)
		*dblSlope = dblNumerator/dblDenominator;
	dblNumerator = ((dblSumY*dblSumXSquare)-(dblSumX*dblSumXY));
	if(dblDenominator!=0)
		*dblIntercept = dblNumerator/dblDenominator;


	delete[] dblArrXData;
	delete[] dblArrYData;

	return VARIANT_TRUE;
}

//*************************************************
//PURPOSE :  To find the Quadratic Coefficients for the given data
//INPUTS  : LONG lngDataCount		  - Total number of Data points
//			VARIANT varDdblArrXData	  - array of X Coordinate points
//			VARIANT varDblArrYData	  - Array of Y Coordinate points
//			
//ASSUMES : 
//RETURNS : DOUBLE *dblA0	- value Which holds resultant Quadratic value
//			DOUBLE *dblA1	- Value Which holds resultant Quadratic value.
//			DOUBLE *dblA2	- Value which holds resultant Quadratic value
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
VARIANT_BOOL CEsdAdvancedGraphCtrl::FindQuadraticCoefficients(LONG lngDataCount, VARIANT &varDblArrXData, VARIANT &varDblArrYData, DOUBLE* dblA0, DOUBLE* dblA1, DOUBLE* dblA2)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	double dblP1;
	double dblP2;
	double dblDelta1;
	double dblDelta2;
	double dblDelta3;
	double dblDelta4;
	double dblSumX=0;
	double dblSumY=0;
	double dblSumXY=0;
	double dblSumXSquare=0;
	double dblSumXSquareY=0;
	double dblSumXCube=0;
	double dblSumXFour=0;	

	long lngLBound,lngUBound,lngResultBound;

	// The arrays created must be of the same size as the data count present in VARIANT's
	// If not it will give assertion in while retrieving data from VARIANT"s to Double in 'fncGetDoubleValuesFromSafeArry' function
	SafeArrayGetLBound(varDblArrXData.parray,1,&lngLBound);
	SafeArrayGetUBound(varDblArrYData.parray,1,&lngUBound);
	lngResultBound	=	lngUBound	-	lngLBound;

	double *dblArrXData=new double[lngResultBound];

	SafeArrayGetLBound(varDblArrXData.parray,1,&lngLBound);
	SafeArrayGetUBound(varDblArrYData.parray,1,&lngUBound);
	lngResultBound	=	lngUBound	-	lngLBound;

	double *dblArrYData=new double[lngResultBound];

	long lSize=fncGetDoubleValuesFromSafeArray(varDblArrXData,dblArrXData);

	if(lngDataCount>lSize)
		lngDataCount=lSize;

	lSize=fncGetDoubleValuesFromSafeArray(varDblArrYData,dblArrYData);

	if(lngDataCount>lSize)
		lngDataCount=lSize;

	for(long i=0;i<lngDataCount;i++)
	{
		dblSumX+= dblArrXData[i];
		dblSumY+= dblArrYData[i];
		dblSumXY+= dblArrXData[i] * dblArrYData[i];
		dblSumXSquare += pow(dblArrXData[i],2);

		dblSumXSquareY += pow(dblArrXData[i],2) * dblArrYData[i];

		dblSumXCube += pow(dblArrXData[i],3);
		dblSumXFour += pow(dblArrXData[i],4);
	}	

	dblP1  = (dblSumX*dblSumY)-(lngDataCount*dblSumXY);
	dblP2 =  (dblSumXSquare*dblSumXY)-(dblSumX*dblSumXSquareY);
	dblDelta1 = pow(dblSumX,2)-(lngDataCount*dblSumXSquare);
	dblDelta2 = (dblSumX*dblSumXSquare)-(lngDataCount*dblSumXCube);
	dblDelta3 = pow(dblSumXSquare,2)-(dblSumX*dblSumXCube);
	dblDelta4 = (dblSumXSquare*dblSumXCube)-(dblSumX*dblSumXFour);

	if((dblDelta1*dblDelta4)-(dblDelta2*dblDelta3)!=0)
		*dblA1 = ((dblP1*dblDelta4)-(dblP2*dblDelta2))/
		((dblDelta1*dblDelta4)-(dblDelta2*dblDelta3));	

	if((dblDelta2*dblDelta3)-(dblDelta1*dblDelta4)!=0)
		*dblA2 = ((dblP1*dblDelta3)-(dblP2*dblDelta1))/
		((dblDelta2*dblDelta3)-(dblDelta1*dblDelta4));

	*dblA0 = (dblSumY-((*dblA1) * dblSumX)-((*dblA2) * dblSumXSquare))/lngDataCount;

	delete[] dblArrXData;
	delete[] dblArrYData;



	return VARIANT_TRUE;
}


//*************************************************
//PURPOSE :  To find linear Coefficients for particular Graph

//INPUTS  : long lngGraphIdx   -  Graph ID for which Linear fitting Values are Calculating
//			
//ASSUMES : -
//RETURNS : double dblSlope	-  Resultant Linear Fit value(Slope)
//			double dblC	    -  Resultant Linear Fit Value(Intercept)
//			i.e Coefficients of the Equation  Y=mX+C
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
VARIANT_BOOL CEsdAdvancedGraphCtrl::LinearCoefficients(LONG lngGraphIdx, DOUBLE* dblByAddSlope, DOUBLE* dblByAddC)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	if(lngGraphIdx>=0 && lngGraphIdx < m_chart.get_SeriesCount())		 // Check whether Graph specified by GraphID exists or not.
	{
		LPDISPATCH pDisp	=	m_chart.Series(lngGraphIdx);
		ISeriesPtr	pSeries	=	pDisp;
		pDisp->Release();

		if((pSeries->GetYValues()->GetCount())>=2)                           // Graph must have atleast 2 data points to retrieve the 
		{														 // Linear co-efficients. Check for that.
			prcLinearFit(lngGraphIdx,*dblByAddSlope,*dblByAddC);     // Call to LinearFit function.
			pSeries	=	NULL;
			return VARIANT_TRUE;
		}
		else
		{
			MessageBox(_T("There must be atleast two points to get the Linear Coefficients."));
			pSeries	=	NULL;
			return VARIANT_FALSE;

		}
	}
	else
	{
		MessageBox(_T("Graph with this ID does not fount"));
		return VARIANT_FALSE;

	}				

	return VARIANT_TRUE;
}
//*************************************************
//PURPOSE : To find the Quadratic fit Coefficient values
//INPUTS  : long lngGraphIdx   -  Graph ID for which Quadratic fitting 
//			Values are Calculating
//ASSUMES : -
//RETURNS : double dblA0	-  Resultant Quadratic Fit value
//			double dblA1	-  Resultant Quadratic Fit Value
//			double dblA2	-  Resultant Quadratic Fit value
//         i.e Coefficients of the Equation  Y=A0X2+A1X+A2
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------

VARIANT_BOOL CEsdAdvancedGraphCtrl::QuadraticCoefficients(LONG lngGraphIdx, DOUBLE* dblByAddA0, DOUBLE* dblByAddA1, DOUBLE* dblByAddA2)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	if(lngGraphIdx>=0 && lngGraphIdx < m_chart.get_SeriesCount())		 // Check whether Graph specified by GraphID exists or not.
	{
		LPDISPATCH pDisp	=	m_chart.Series(lngGraphIdx);
		ISeriesPtr	pSeries	=	pDisp;
		pDisp->Release();
		_bstr_t bstrGraphName = pSeries->GetName().copy();
		long lngLTblIdx=GetLtblIdxFromName(bstrGraphName);
		if(lngLTblIdx<0)
		{
			MessageBox(_T("Graph with this index doesn't exist"));
			pSeries	=	NULL;
			return VARIANT_FALSE;
		}
		//SysFreeString(bstrGraphName);
		if((pSeries->GetYValues()->GetCount())>3) // Graph must have atleast 3 data points to retrieve the 	
		{														 // Quadratic co-efficients. Check for that.	
			prcQuadraticFit(lngGraphIdx,*dblByAddA0,*dblByAddA1,*dblByAddA2); // Call to QuadraticFit function.
			pSeries	=	NULL;
			return VARIANT_TRUE;
		}
		else
		{
			MessageBox(_T("There must be at least three points to get the Quadratic Coefficients"),NULL,0);
			pSeries	=	NULL;
			return VARIANT_FALSE;

		}
	}
	else
	{
		MessageBox(_T("Graph with this ID does not fount"));
		return VARIANT_FALSE;
	}				

	return VARIANT_TRUE;
}
//*************************************************
//PURPOSE : To get the 'X' Value of Linear fit expression(Y=m*X+C))
//INPUTS  : LONG lngDataCount   -- Count of Values to be Find
//			DOUBLE dblSlope	    -- Coefficient(m) of the Linear fit Expression
//			DOUBLE dblA1	    --   "        (C)  "  "     "    "      "
//			DOUBLE *dblArrYData --  'Y' Values of the Linear Fit Expression
//ASSUMES : 
//RETURNS : DOUBLE *dblArrXData --  'X' Values of theLinear Fit Equation
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::LinearFitX(LONG lngDataCount, DOUBLE dblSlope, DOUBLE dblIntercept, DOUBLE* dblArrXdata, DOUBLE* dblArrYData)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	if(dblSlope !=0)
	{
		for(long intIndex = 0;intIndex < lngDataCount;intIndex++)
			dblArrXdata[intIndex] = (dblArrYData[intIndex] - dblIntercept)/ dblSlope;
	}
	else
		MessageBox(_T("Slope must not be Zero"));
}
//*************************************************
//PURPOSE : To get the 'X' Value of Quadratic fit expression(A0*X2 +A1*X +A2-Y=0)
//INPUTS  : LONG lngDataCount   -- Count of Values to be Find
//			DOUBLE dblA0	    -- Coefficient value of the Quadratic Equation
//			DOUBLE dblA1	    --   "           "    "  "    "            "
//			DOUBLE dblA2	    --   "			"	 "	"	 "			  "
//			DOUBLE *dblArrYData --  'Y' Values of the Quadratic equation
//ASSUMES : 
//RETURNS : DOUBLE *dblArrXData --  'X' Values of the Quadratic Equation
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::QuadraticFitX(LONG lngDataCount, DOUBLE dblA0, DOUBLE dblA1, DOUBLE dblA2, DOUBLE* dblArrXData, DOUBLE* dblArrYData)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	double dblRoot1 = 0;
	double dblRoot2 = 0;
	double dblTempA0;

	for(long intIndex=0;intIndex<lngDataCount;intIndex++)
	{
		// y = ax2 + bx + c => ax2 + bx + (c-y)= 0 

		dblTempA0 = dblA0 - dblArrYData[intIndex];

		// checking whether the value under root is lees than zero
		//if ((dblA1 * dblA1)-(4 * dblA0 * dblA2) < 0)
		if ((dblA1 * dblA1)-(4 * dblTempA0 * dblA2) < 0)
		{
			dblArrXData[intIndex] = -1;                
			continue;
		}
		else
		{
			dblRoot1 = (- dblA1 + sqrt((dblA1 * dblA1)-(4 * dblA2 * dblTempA0)))/(2*dblA2);
			dblRoot2 = (- dblA1 - sqrt((dblA1 * dblA1)-(4 * dblA2 * dblTempA0)))/(2*dblA2); 

			// Checking for the First condition if both roots are negative 
			// Return that the roots are not valid

			if (dblRoot1 < 0 && dblRoot2 < 0)
			{
				dblArrXData[intIndex] = -1;   			
				continue;
			}  

			// Checking for the second condition when one root is postive and the other is
			// negative discard the negative root
			if (dblRoot1 < 0) 
			{
				if(dblRoot2 >=0) 
				{
					dblArrXData[intIndex] = dblRoot2;
					continue;
				} 
			}  

			if (dblRoot2 < 0) 
			{
				if(dblRoot1>=0) 
				{
					dblArrXData[intIndex] = dblRoot1;
					continue;
				}
			}	   


			// Checking for the thrid condition when both roots are postive
			if (dblA2 == 0)
			{
				MessageBox(_T("Didision by Zero not permitted"),NULL,MB_OK|MB_ICONWARNING); //String Table
			}
			else
			{
				if ((dblRoot2 >= 0) && (dblRoot1 >= 0))
				{
					if (dblRoot1 < (-dblA1/(2*dblA2)) && dblRoot2 < (-dblA1/(2*dblA2)))
					{
						dblArrXData[intIndex] = -1;
						continue;
					}
					else if (dblRoot2 <= (-dblA1/(2* dblA2)))
					{
						dblArrXData[intIndex] = dblRoot2;
						continue;
					}
					else if (dblRoot1 <= (-dblA1/(2* dblA2)))
					{
						dblArrXData[intIndex] = dblRoot1;
						continue; 
					}  
					else
					{
						dblArrXData[intIndex] = dblRoot1;
						continue; 
					}
				}                 
			}  
		} 
	}

}
//*************************************************
//PURPOSE :  To get the Peak values information of the graph
//INPUTS  : LONG lngGraphIdx  - Graph ID 
//ASSUMES : 
//RETURNS : VARIANT * dblHeight		  -- Height of Each Peak.
//			VARIANT * dblWidth		  -- Width Of Each Peak.
//			VARIANT * dblArea		  -- Area of Each Peak.
//			VARIANT * lngPeakStartIdx -- Stating point Index of each peak .
//			VARIANT * lngPeakMaxIdx   -- Maximum point Index of each peak.
//			VARIANT * lngPeakEndIdx	  -- End point Index of each Peak.
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::GetPeakInfo(LONG lngGraphIdx, VARIANT* dblHeight, VARIANT* dblWidth, VARIANT* dblArea, VARIANT* lngPeakStartIndex, VARIANT* lngPeakMaxIndex, VARIANT* lngPeakEndIndex)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	dblHeight->vt         =VT_ARRAY|VT_R8;
	dblWidth->vt          =VT_ARRAY|VT_R8;
	dblArea->vt           =VT_ARRAY|VT_R8;
	lngPeakStartIndex->vt =VT_ARRAY|VT_I4;
	lngPeakMaxIndex->vt   =VT_ARRAY|VT_I4;
	lngPeakEndIndex->vt   =VT_ARRAY|VT_I4;

	if(lngGraphIdx > m_chart.get_SeriesCount()-1)  // Make sure that data point which is to be added to the Graph specified 
	{                                        // GraphID exists or not.
		MessageBox(_T("Graph with this specified ID doesn't exists"));//String Table
		dblHeight->parray		  = NULL;
		dblWidth->parray		  = NULL;
		dblArea->parray			  = NULL;
		lngPeakStartIndex->parray = NULL;
		lngPeakMaxIndex->parray   = NULL;
		lngPeakEndIndex->parray   = NULL;
		return ; //Error(IDS_GRAPHID_DONOT_EXIST);//String Table
	} 		
	else 
	{	
		LPDISPATCH pDisp	=	m_chart.Series(lngGraphIdx);
		ISeriesPtr	pSeries	=	pDisp;
		pDisp->Release();
		_bstr_t bstrGraphName = pSeries->GetName().copy();
		long lngLTblIdx=GetLtblIdxFromName(bstrGraphName);
		if(lngLTblIdx<0)
		{
			MessageBox(_T("Graph with this specified index doesn't exist"));
			pSeries	=	NULL;
			return;
		}
		lngGraphIdx=lngLTblIdx;		
		if(m_GraphPeaks.GetSize()==0)
		{
			dblHeight = NULL;
			dblWidth  = NULL;
			dblArea	  = NULL;
			lngPeakStartIndex = NULL;
			lngPeakMaxIndex = NULL;
			lngPeakEndIndex = NULL;
			pSeries	=	NULL;

			return;
		}

		stuPeakInfo * PeakInfo = NULL;

		for(int i=0;i<m_GraphPeaks.GetSize();i++)   // Silpa.S 26/10/07
		{
			PeakInfo = m_GraphPeaks.GetAt(i);


			_bstr_t strPeakInfoGraph(PeakInfo->strGraphName,TRUE);
			if(bstrGraphName==strPeakInfoGraph)
			{
				if(PeakInfo != NULL)
				{
					SAFEARRAYBOUND Sab[]       = {PeakInfo->dblArea.GetSize()};
					SAFEARRAY *safeAryHeight   = SafeArrayCreate(VT_R8,1,Sab);
					SAFEARRAY *safeAryWidth    = SafeArrayCreate(VT_R8,1,Sab);
					SAFEARRAY *SafeAryArea     = SafeArrayCreate(VT_R8,1,Sab);
					SAFEARRAY *safeArystartIdx = SafeArrayCreate(VT_I4,1,Sab);
					SAFEARRAY *safeAryMaxIdx   = SafeArrayCreate(VT_I4,1,Sab);
					SAFEARRAY *safeAryEndIdx   = SafeArrayCreate(VT_I4,1,Sab);


					for(long j = 0; j< PeakInfo->dblArea.GetSize(); j++)
					{

						SafeArrayPutElement  (safeAryHeight,&j,&(PeakInfo->dblHeight.GetAt(j)));
						SafeArrayPutElement  (safeAryWidth, &j,&(PeakInfo->dblWidth.GetAt(j)));
						SafeArrayPutElement  (SafeAryArea, &j,&(PeakInfo->dblArea.GetAt(j)));
						SafeArrayPutElement  (safeArystartIdx,&j,&(PeakInfo->intPeakStartIndex.GetAt(j)));
						SafeArrayPutElement  (safeAryMaxIdx,  &j,&(PeakInfo->intPeakMaxIndex.GetAt(j)));
						SafeArrayPutElement  (safeAryEndIdx,  &j,&(PeakInfo->intPeakEndIndex.GetAt(j)));

					}

					dblHeight->parray		     =  safeAryHeight;
					dblWidth->parray		     =  safeAryWidth;
					dblArea->parray			     =  SafeAryArea;
					lngPeakStartIndex->parray    = safeArystartIdx;
					lngPeakMaxIndex->parray      = safeAryMaxIdx;
					lngPeakEndIndex->parray      = safeAryEndIdx;
				} 
				else
				{
					dblHeight			=	NULL;
					dblWidth			=	NULL;
					dblArea				=	NULL;
					lngPeakStartIndex	=	NULL;
					lngPeakMaxIndex		=	NULL;
					lngPeakEndIndex		=	NULL;
				}				
			}
			//SysFreeString(strPeakInfoGraph);
		}
		m_chart.Repaint();
		//SysFreeString(bstrGraphName);
		pSeries	=	NULL;

	}

}
//*************************************************
//PURPOSE : Method to get the Peak indexes of the Graph
//INPUTS  : LONG lngGraphIdx   -- Graph ID
//			LONG lngPeakLevel  -- Peak Level At which range Peak indexes are Required
//ASSUMES : 
//RETURNS : VARIANT *varLngPeakIndexes
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
LONG CEsdAdvancedGraphCtrl::GetPeakIndexes(LONG lngGraphIdx, LONG lngPeakLevel, VARIANT* varLngPeakIndexes)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	if(lngGraphIdx>=0 && lngGraphIdx< m_chart.get_SeriesCount())		//	Check for the existence of Graph.
	{
		LONG lngPeakCnt;
		varLngPeakIndexes->vt=VT_ARRAY|VT_I4;	// Declare the VARIANT as Array of Long Elements
		VariantInit(varLngPeakIndexes);
		if(lngPeakLevel > 0 && lngPeakLevel <=10)
		{
			LPDISPATCH pDisp	=	m_chart.Series(lngGraphIdx);
			ISeriesPtr	pSeries	=	pDisp;
			pDisp->Release();
			_bstr_t bstrGraphName=pSeries->GetName().copy();
			long lngIdx=GetLtblIdxFromName(bstrGraphName);
			if(lngIdx<0)
			{
				MessageBox(_T("Graph with this specified ID doesn't exist."));
				return 0;
			}
			//	SysFreeString(bstrGraphName);
			long *lngPeakIndexes=NULL;
			stuRemovableGraphData	temp;
			temp	=	m_arrGraphRelatedSerieses.GetAt(lngIdx);	 

			if((pSeries->GetYValues()->GetCount())>2)							//	Check if Graph has more than 2 data points.	
			{
				temp.intPeakLevel =	lngPeakLevel;   // Store the peak level
				m_arrGraphRelatedSerieses.SetAt(lngIdx,temp);// Store the new Peak level value in the Graph Stucture

				lngPeakIndexes	=	new long[pSeries->GetXValues()->Count];
				lngPeakCnt = fncCalculatePeakIndexes(lngGraphIdx, lngPeakIndexes);	// Invoking this function will get the Peak Indexes and it will return the number of Peaks.
				SAFEARRAYBOUND sab[1];
				sab[0].cElements=lngPeakCnt;
				sab[0].lLbound=0;
				SAFEARRAY *pSa=SafeArrayCreate(VT_I4,1,sab);
				for(long i=0;i<lngPeakCnt;i++)
				{
					SafeArrayPutElement(pSa,&i,&lngPeakIndexes[i]);
				}

				varLngPeakIndexes->parray=pSa;	// Assign the Safe array to the VARIANT
				delete lngPeakIndexes;
				pSeries	=	NULL;
				return lngPeakCnt;
			}
			else
			{
				MessageBox(_T("There must be atleast 3 data points to determine the peaks."));
				varLngPeakIndexes	=	NULL;					
				return -1;
			}

		}
		else
		{
			MessageBox(_T("Peak Level value must be within 1 - 10."));
			varLngPeakIndexes	=	NULL;
			return -1;
		}
	}
	else
	{
		MessageBox(_T("Graph with specified ID doesn't exist."));
		varLngPeakIndexes	=	NULL;
		return -1;
	}	

}


////  Begin of internal TeeChart control Events definitions
void CEsdAdvancedGraphCtrl::OnAfterDrawTChart() 
{	

	FireEvent(eventidOnAfterDraw, EVENT_PARAM(VTS_NONE));
	LPDISPATCH pDisp	=	NULL;
	if(blnCustomText)
	{	
		int nSize=(int)m_objPlotAreaText.GetSize();

		for(int i=0;i<nSize;i++)
		{
			//AfxMessageBox(_T("Came"));
			EsdPLOTAREATEXT_STRUCT *text=m_objPlotAreaText.GetAt(i);
			int nCustomTxtWdth,nCustomTextHt;
			_bstr_t bstrGraphName(text->bstrGraphName,TRUE);
			long lngIdx=GetLtblIdxFromName(bstrGraphName);
			if(lngIdx<0)
			{
				MessageBox(_T("Graph with the Specified ID doesn't exist."));
				break;
			}
			lngIdx=GetGraphIdxFromName(bstrGraphName);

			pDisp	=	m_chart.get_Canvas();
			ICanvasPtr pCanvas = pDisp;
			pDisp->Release();
			pCanvas->GetFont()->PutColor(m_clrCustomTextColor);
			pCanvas->PutBackMode(cbmOpaque);
			//	pCanvas->PutBackColor(m_clrCustomTextBackColor);
			//((ICanvas*)m_chart.get_Canvas())->GetFont()->PutBold(TRUE);

			IDispatchPtr pDisp =	m_chart.Series(lngIdx);
			ISeriesPtr	pSeries	=	pDisp;///*m_chart.Series(lngIdx)*/;
			pDisp	=	NULL;

			pDisp	=	m_chart.get_Aspect();
			IAspectPtr	pAspect	=	pDisp;
			pDisp	=	NULL;

			// If 3D mode is enabled use 3D methods to display text, otherwise use 2D Methods
			if(pAspect->View3D==VARIANT_TRUE)// If 3D enabled
			{
				for(int j=0;j<text->dblXVal.GetSize();j++)
				{
					_bstr_t bstr(text->strPlotAreaText.GetAt(j));
					nCustomTxtWdth	=	pCanvas->TextWidth(bstr);
					nCustomTextHt	=	pCanvas->TextHeight(bstr);
					long lngXCord	=	pSeries->CalcXPosValue((text->dblXVal).GetAt(j));
					long lngYCord	=	pSeries->CalcYPosValue((text->dblYVal).GetAt(j));
					long lngZCord	=	pAspect->GetChart3DPercent()/4;
					//pCanvas->TextOut(lngXCord-(2*nCustomTxtLen),lngYCord-15,bstr);
					pCanvas->TextOut3D(lngXCord-nCustomTxtWdth/2,lngYCord-nCustomTextHt,lngZCord,bstr);
				}
				text=NULL;
			}
			else if(pAspect->View3D==VARIANT_FALSE)
			{
				for(int j=0;j<text->dblXVal.GetSize();j++)
				{
					_bstr_t bstr(text->strPlotAreaText.GetAt(j));
					//nCustomTxtLen=bstr.length();
					nCustomTxtWdth	=	pCanvas->TextWidth(bstr);
					nCustomTextHt	=	pCanvas->TextHeight(bstr);
					long lngXCord=	pSeries->CalcXPosValue((text->dblXVal).GetAt(j));
					long lngYCord=	pSeries->CalcYPosValue((text->dblYVal).GetAt(j));
					//pCanvas->TextOut(lngXCord-(2*nCustomTxtLen),lngYCord-15,bstr);//SysAllocString(text->strPlotAreaText.GetAt(i)));

					pCanvas->RotateLabel(lngXCord-nCustomTextHt/4,lngYCord-nCustomTextHt/4,bstr,90);

					///////{Commented by Swathi to display the R.T in vertical direction
					//pCanvas->TcTextOut(lngXCord-nCustomTxtWdth/2,lngYCord-nCustomTextHt,bstr);
					////////////}....................
					//	SysFreeString(bstr);
				}
				//SysFreeString(bstrGraphName); 
				text=NULL;
			}			

			pSeries	=	NULL;
			pCanvas	=	NULL;
			pAspect	=	NULL;
		}
	}
	stuRemovableGraphData obj;
	long lngGraphID;
	for(long lngID=0;lngID<m_arrGraphRelatedSerieses.GetCount();lngID++) //Call PeakFill function if Peak filling is already enabled and erased bcz of Redrawing
	{
		obj=m_arrGraphRelatedSerieses.GetAt(lngID);
		_bstr_t bstrFill(obj.bstrFillName,TRUE);
		_bstr_t bstrNull(_T(""));
		if(bstrFill!=bstrNull)
		{
			lngGraphID=	GetGraphIdxFromName(obj.bstrGraphName);
			if(lngGraphID<0)
				continue;
			else
				PeakFillArea(lngGraphID);
		}

	}

	if(m_intCounterForGraphsPeaks>0)
		prcDisplayPeaks();
	if(m_bShowCrossWire && m_arrGraphRelatedSerieses.GetSize()>0)
		prcDrawCrossWire();
	if(m_bClickEvent && m_arrGraphRelatedSerieses.GetSize()>0)
		prcBaseLine();
	if(m_bShowCrossWire && m_arrGraphRelatedSerieses.GetSize()>0 && m_intCrossWireGraphID>-1 && m_intCrossWireGraphID<m_arrGraphRelatedSerieses.GetSize())
		prcDisplayCrossWireXYValues();
	if(m_objCustomText.GetSize()>0)    // If there is any custom text to be displayed 
		prcDisplayCustomText();		// then display it.

	if (m_bMarkStartnEndPoints)
	{
		MarkStartnEndpts(0);
	}
}

void CEsdAdvancedGraphCtrl::OnBeforeDrawTChartSeries() 
{

	FireEvent(eventidOnBeforeDrawSeries, EVENT_PARAM(VTS_NONE));
}

void CEsdAdvancedGraphCtrl::OnBeforeDrawTChartAxes() 
{
	FireEvent(eventidOnBeforeDrawAxes, EVENT_PARAM(VTS_NONE));

}
void CEsdAdvancedGraphCtrl::OnClickTChart() 
{
	FireEvent(eventidOnClick, EVENT_PARAM(VTS_NONE));
}
void CEsdAdvancedGraphCtrl::OnClickTChartAxis(long Axis, long Button, long Shift, long X, long Y) 
{
	FireEvent(eventidOnClickAxis, EVENT_PARAM(VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4), Axis, Button, Shift, X, Y);
}
void CEsdAdvancedGraphCtrl::OnTChartCursorToolChange(long lTool,long X,long Y,double XVal,double YVal,long lSeries,long ValueIdx )
{	

	FireEvent(eventidOnCursorToolChange, EVENT_PARAM(VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_I4 VTS_I4), lTool, X, Y, XVal, YVal, lSeries, ValueIdx);

	if(blnHorzDatumLine || blnVertDatumLine)
	{
		fncDisplayDatumLineText(lTool,XVal,YVal,lSeries);
	}

}
void CEsdAdvancedGraphCtrl::OnClickTChartBackground(long Button, long Shift, long X, long Y) 
{
	FireEvent(eventidOnClickBackground, EVENT_PARAM(VTS_I4 VTS_I4 VTS_I4 VTS_I4), Button, Shift, X, Y);
	/**************************  Cross Wire *********************************/	
	// Raise this Cross wire drawing when click on the Background or on the Series i.e either of the 'OnClickTChartBackGround'
	// or 'OnClickTChartSerires'
	//

	if(Button==1) // Check weather button is left Mouse button or not
	{
		m_ptCrossWirePos.x = X;		// Save the Cursor coords of the Graph to display Cross wire
		m_ptCrossWirePos.y = Y;

		m_ptStartEndPos.x=X;
		m_ptStartEndPos.y=Y;
		/*if(m_bShowCrossWire)
		{
		m_bFirstTimeCrossWire = TRUE;

		m_bClickEvent=TRUE;

		if(m_arrGraphRelatedSerieses.GetSize()>0)
		m_chart.Repaint();
		}*/
	}
}

void CEsdAdvancedGraphCtrl::OnClickTChartLegend(long Button, long Shift, long X, long Y) 
{
	FireEvent(eventidOnClickLegend, EVENT_PARAM(VTS_I4 VTS_I4 VTS_I4 VTS_I4), Button, Shift, X, Y);
}

void CEsdAdvancedGraphCtrl::OnClickTChartSeries(long SeriesIndex, long ValueIndex, long Button, long Shift, long X, long Y) 
{

	//FireEvent(eventidOnClickSeries, EVENT_PARAM(VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4), SeriesIndex, ValueIndex, Button, Shift, X, Y);

	/**************************  Cross Wire *********************************/	
	// Raise this Cross wire drawing when click on the Background or on the Series i.e either of the 'OnClickTChartBackGround'
	// or 'OnClickTChartSerires'
	if(Button==1) // Check weather button is left Mouse button or not
	{
		m_ptStartEndPos.x = X;
		m_ptStartEndPos.y = Y;

		m_bClickEvent = TRUE;

		if(m_arrGraphRelatedSerieses.GetSize()>0)
			m_chart.Repaint();

		//	m_ptCrossWirePos.x = X;		// Save the Cursor coords of the Graph to display Cross wire
		//	m_ptCrossWirePos.y = Y;

		//	IDispatchPtr pDisp	=	m_chart.Series();
		//	ISeriesPtr	pSeries	=	pDisp;
		//	pDisp	=	NULL;

		//  double dblX,dblY;
		//	dblX = pSeries->GetXValues()->GetValue(X); 
		//	dblY = pSeries->GetYValues()->GetValue(Y); 


		//	CString str;
		//	str.Format(_T("%lf %lf"),dblX,dblY);
		//	AfxMessageBox(str);

		//LPDISPATCH pDisp	=	m_chart.Series(SeriesIndex);
		//ISeriesPtr	pSeries	=	pDisp;
		//pDisp->Release();
		//if(pSeries->Clicked(m_ptCrossWirePos.x, m_ptCrossWirePos.y)!=-1)
		//{
		//	if(m_bShowCrossWire)
		//	{
		//		m_bFirstTimeCrossWire = TRUE;

		//		if(m_arrGraphRelatedSerieses.GetSize()>0)
		//			m_chart.Repaint();
		//	}
		//}
		//pSeries	=	NULL;

		//m_chart.Repaint();


	}
}

void CEsdAdvancedGraphCtrl::OnDblClickTChart() 
{
	FireEvent(eventidOnDblClick, EVENT_PARAM(VTS_NONE));

	ZoomOut();

}

void CEsdAdvancedGraphCtrl::OnGetTChartAxisLabel(long Axis, long SeriesIndex, long ValueIndex, BSTR FAR* LabelText) 
{

}
void CEsdAdvancedGraphCtrl::OnGetTChartLegendRect(long FAR* Left, long FAR* Top, long FAR* Right, long FAR* Bottom) 
{
	FireEvent(eventidOnGetLegendRect, EVENT_PARAM(VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4), Left, Top, Right, Bottom);

}
void CEsdAdvancedGraphCtrl::OnTChartMouseDown(long Button, long Shift, long X, long Y) 
{
	FireEvent(eventidOnMouseDown, EVENT_PARAM(VTS_I4 VTS_I4 VTS_I4 VTS_I4), Button, Shift, X, Y);


}
void CEsdAdvancedGraphCtrl::OnGetTChartNextAxisLabel(long Axis, long LabelIndex, double FAR* LabelValue, BOOL FAR* MoreLabels) 
{
}

void CEsdAdvancedGraphCtrl::OnTChartMouseMove(long Shift, long X, long Y) 
{

	FireEvent(eventidOnMouseMove, EVENT_PARAM(VTS_I4 VTS_I4 VTS_I4),Shift, X, Y);

}
void CEsdAdvancedGraphCtrl::OnTChartMouseUp(long Button, long Shift, long X, long Y) 
{

	FireEvent(eventidOnMouseUp, EVENT_PARAM(VTS_I4 VTS_I4 VTS_I4 VTS_I4), Button, Shift, X, Y);

}
void CEsdAdvancedGraphCtrl::OnTChartPageChange() 
{
	FireEvent(eventidOnPageChange, EVENT_PARAM(VTS_NONE));

}
void CEsdAdvancedGraphCtrl::OnResizeTChart() 
{
	FireEvent(eventidOnResize, EVENT_PARAM(VTS_NONE));

	m_chart.Repaint();

}

void CEsdAdvancedGraphCtrl::OnScrollTChart() 
{
	FireEvent(eventidOnScroll, EVENT_PARAM(VTS_NONE));

}
void CEsdAdvancedGraphCtrl::OnTChartTimer() 
{
	FireEvent(eventidOnTimer, EVENT_PARAM(VTS_NONE));

}
void CEsdAdvancedGraphCtrl::OnUndoZoomTChart() 
{
	FireEvent(eventidOnUndoZoom, EVENT_PARAM(VTS_NONE));
}
void CEsdAdvancedGraphCtrl::OnZoomTChart() 
{
	FireEvent(eventidOnZoom, EVENT_PARAM(VTS_NONE));
}
void CEsdAdvancedGraphCtrl::OnTChartKeyDown(long lngKeyCode,long lngShiftstate)
{
	FireEvent(eventidOnKeyDown, EVENT_PARAM(VTS_I4 VTS_I4), lngKeyCode, lngShiftstate);

	/*if(lngKeyCode==VK_RIGHT )
	{	double dbl=((IToolList*)m_chart.get_Tools())->GetItems(0)->GetasTeeCursor()->GetXVal();
	if(dbl<=((IAxes*)m_chart.get_Axis())->GetBottom()->GetMaximum())
	((IToolList*)m_chart.get_Tools())->GetItems(0)->GetasTeeCursor()->XVal=dbl+1;
	CString str;
	str.Format(_T("Key:%ld is Down"),lngKeyCode);
	//AfxMessageBox(str);
	}
	if(lngKeyCode==VK_LEFT )
	{			
	((IToolList*)m_chart.get_Tools())->GetItems(0)->GetasTeeCursor()->XVal=((IToolList*)m_chart.get_Tools())->GetItems(0)->GetasTeeCursor()->GetXVal()-1;
	CString str;
	str.Format(_T("Key:%ld is Down"),lngKeyCode);
	//AfxMessageBox(str);
	}*/

}
void CEsdAdvancedGraphCtrl::OnTChartKeyUp(long lngKeyCode,long lngShiftState)
{
	FireEvent(eventidOnKeyUp, EVENT_PARAM(VTS_I4 VTS_I4), lngKeyCode, lngShiftState);
}
void CEsdAdvancedGraphCtrl::OnMouseEnterTChartSeries(long lngSeriesIdx)
{
	FireEvent(eventidOnMouseEnterGraph, EVENT_PARAM(VTS_I4), lngSeriesIdx);
}

void CEsdAdvancedGraphCtrl::OnMouseLeaveTChartSeries(long lngSeriesIdx)
{
	FireEvent(eventidOnMouseLeaveGraph, EVENT_PARAM(VTS_I4), lngSeriesIdx);
}

void CEsdAdvancedGraphCtrl::OnTChartSeriesAfterAdd(long lngSeriesIdx,long lngPointIdx)
{
	FireEvent(eventidOnGraphAfterAdd, EVENT_PARAM(VTS_I4 VTS_I4), lngSeriesIdx, lngPointIdx);


}
void CEsdAdvancedGraphCtrl::OnTChartSeriesAfterDrawValues(long lngSeriesIdx)
{
	FireEvent(eventidOnGraphAfterDrawValues, EVENT_PARAM(VTS_I4), lngSeriesIdx);

	LPDISPATCH pDisp	=	m_chart.get_Canvas();
	ICanvasPtr pCanvas	=	pDisp;
	pDisp->Release();
	pCanvas->UnClipRectangle();

	pCanvas	=	NULL;

}

void CEsdAdvancedGraphCtrl::OnTChartSeriesBeforeAdd(long lngSeriesIdx,VARIANT_BOOL *bMoreValues)
{
	FireEvent(eventidOnGraphAfterAdd, EVENT_PARAM(VTS_I4 VTS_PBOOL), lngSeriesIdx, bMoreValues);

}
void CEsdAdvancedGraphCtrl::OnTChartSeriesBeforeDrawValues(long lngSeriesIdx)
{
	FireEvent(eventidOnGraphBeforeDrawValues, EVENT_PARAM(VTS_I4), lngSeriesIdx);

	long lngLeft,lngTop,lngRight,lngBottom;
	CalculateGraphRect(lngSeriesIdx,&lngLeft,&lngTop,&lngRight,&lngBottom);
	LPDISPATCH pDisp	=	m_chart.get_Canvas();
	ICanvasPtr pCanvas	=	pDisp;
	pDisp->Release();

	pCanvas->ClipRectangle(lngLeft,lngTop,lngRight,lngBottom);

	pCanvas	=	NULL;

}

void CEsdAdvancedGraphCtrl::OnGetTChartSeriesMarks(long lngSeriesIdx,long lngValueIdx,BSTR *strMarkText)
{
	SysFreeString(*strMarkText);
	CString strNull(_T(""));
	_bstr_t bstr	=	strNull;
	//if(m_bShowDataAtPeak==FALSE)
	//{
	//	*strMarkText	=	bstr.copy();
	//}
	//else if(m_bShowDataAtPeak	==	TRUE)
	//{
	/*strNull	=	_T("MyText");
	_bstr_t bstr	=	strNull;
	LPDISPATCH pDisp	=	m_chart.Series(lngSeriesIdx);
	ISeriesPtr	pSeries	=	pDisp;
	pDisp->Release();
	IMarksPtr pMarks	=	pseries->Marks;
	IMarksItemPtr pItem	=	pMarks->GetItem(lngValueIdx);

	pItem->Text	=	bstr;

	pItem	=NULL;
	pMarks	=	NULL;
	pseries	=NULL;*/
	//	_bstr_t bstr;


	//	strNull	=	_T("T");
	//	bstr	=	strNull;
	*strMarkText	=	bstr.copy();// initialize to empty value
	EsdPeakInfoDisplay_Struct *temp	=	NULL;
	CString str;
	for(int i=0;i<m_arrPeakInfoIndexes.GetSize();i++)
	{

		temp	=	m_arrPeakInfoIndexes.GetAt(i);
		if(lngSeriesIdx	==	temp->lngGraphIdx)
		{
			for(int j=0;j<temp->lngvalueIdx.GetSize();j++)
			{
				if(lngValueIdx==temp->lngvalueIdx.GetAt(j))
				{	
					bstr	=	(temp->strPeakInfo.GetAt(j));
					*strMarkText	=	bstr.copy();				
					continue;
				}
			}
		}

		//else if(temp.bFlag==true)
		//{
		//	//*strMarkText	=	temp.strPeakInfo.copy(); //restore old value
		//	continue;
		//}
		//else
		//{	
		//	str.Format(_T("Idx	= %ld"),temp.lngvalueIdx);			
		//	*strMarkText	=	bstr.copy(); //empty value
		//}	
	}	
}


/////  End of TChart Events Definitions ///////////////


//*************************************************
//PURPOSE : To Fill the Graph Area with Color
//INPUTS  : LONG lngGraphIdx  - Graph ID 
//ASSUMES : 
//RETURNS : 
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::PeakFillArea(LONG lngGraphIdx)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	LPDISPATCH pDisp =	m_chart.get_Aspect();
	IAspectPtr pAspect	=	pDisp;
	pDisp->Release();
	if(pAspect->View3D==VARIANT_TRUE)
	{
		AfxMessageBox(_T("Peak Fill not possible in when 3D mode is enabled"));
		pAspect	=	NULL;
		return;
	}

	pAspect	=	NULL;	

	pDisp	=	m_chart.get_Canvas();
	ICanvasPtr pcanvas	=	pDisp; // Get the DC to draw
	pDisp->Release();


	long intPeakStartIndex,intPeakStartIndex1;
	long intPeakEndIndex;//,intPeakEndIndex1;
	long intPeakNo = 0;

	double dblX1;
	double dblY1;

	double dblX2;
	double dblY2;

	double dblBLSlope = 0;

	long intX1, intY1, intX2, intY2;


	pDisp	=	m_chart.Series(lngGraphIdx);
	ISeriesPtr pSeries	=	pDisp;	// Smart pointer for 'Series' interface of the Specified Graph ID
	pDisp	=	NULL;


	if(lngGraphIdx<0 ||lngGraphIdx>=m_chart.get_SeriesCount())
	{
		MessageBox(_T("Graph with this ID doesn't exist"));
		return;
	}
	else
	{
		_bstr_t bstrGraphName=pSeries->GetName().copy();
		long lIdx=GetLtblIdxFromName(bstrGraphName);
		if(lIdx<0) // IF the specified Graph ID is not the valid ID
		{
			MessageBox(_T("Graph with this ID doesn't exist"));
			pSeries	=	NULL;
			return;
		}

		long lngLtblIdx	=	GetLtblIdxFromName(bstrGraphName);

		if(lngLtblIdx<0)
			return;

		stuRemovableGraphData obj	=	m_arrGraphRelatedSerieses.GetAt(lngLtblIdx);
		_bstr_t bstrFill(obj.bstrFillName,TRUE);
		_bstr_t bstrNull(_T(""));
		if(bstrFill==bstrNull) //If Fill is not enabled for this graph
		{
			bstrFill	=	_T("Fill");
			obj.bstrFillName	=	bstrFill.copy();
			m_arrGraphRelatedSerieses.SetAt(lngLtblIdx,obj);
		}

		stuPeakInfo *pPeakInfo=NULL;

		for(int i=0;i<m_GraphPeaks.GetSize();i++)   // Silpa.S 26/10/07
		{

			pPeakInfo = m_GraphPeaks.GetAt(i);

			if(pPeakInfo!=NULL)
			{
				_bstr_t strPeakInfoGraph(pPeakInfo->strGraphName,TRUE);
				if(bstrGraphName==strPeakInfoGraph) // If peak detection is performed before then only do filling
				{
					// Set the pen and brush colors to fill
					pcanvas->GetPen()->Color	=	m_clrPeakFillColor;
					pcanvas->GetBrush()->Color	=	m_clrPeakFillColor;

					if((pSeries->GetYValues()->GetCount())>1)	// Draw the graph only if it has more than one data point.
					{	
						dblBLSlope = 0;
						intPeakStartIndex = pPeakInfo->intPeakStartIndex.GetAt(intPeakNo);
						intPeakEndIndex = pPeakInfo->intPeakEndIndex.GetAt(intPeakNo);


						if(!(m_intBaseLineType == 2))
						{
							////Abhinav
							//stuPeakDetectPoint objPeakStartPoint = m_arrPeakDetectPoint.GetAt(intPeakStartIndex);
							//dblX1 =objPeakStartPoint.X;
							//dblY1 =objPeakStartPoint.Y;

							//stuPeakDetectPoint objPeakEndPoint = m_arrPeakDetectPoint.GetAt(intPeakEndIndex);
							//dblX2 = objPeakEndPoint.X;
							//dblY2 = objPeakEndPoint.Y;
							////Abhinav

							dblX1 = pSeries->GetXValues()->GetValue(intPeakStartIndex);//)*pow(10,m_intXPrecision);				
							dblY1 = pSeries->GetYValues()->GetValue(intPeakStartIndex);//)*pow(10,m_intYPrecision);

							dblX2 = pSeries->GetXValues()->GetValue(intPeakEndIndex);//)*pow(10,m_intXPrecision);				
							dblY2 = pSeries->GetYValues()->GetValue(intPeakEndIndex);//)*pow(10,m_intYPrecision);
						}	

						if(m_intBaseLineType==2)
						{
							/*int nPeakCnt	=	pPeakInfo->intPeakEndIndex.GetSize();
							intPeakEndIndex1	=	pPeakInfo->intPeakEndIndex.GetAt(nPeakCnt-1);*/
							intPeakStartIndex1	=	pPeakInfo->intPeakStartIndex.GetAt(0);
							dblX1 = pSeries->GetXValues()->GetValue(intPeakStartIndex);
							dblY1 = pSeries->GetYValues()->GetValue(intPeakStartIndex1);

							dblX2 = pSeries->GetXValues()->GetValue(intPeakEndIndex);//
							dblY2 = pSeries->GetYValues()->GetValue(intPeakStartIndex1);//

						}

						if((dblX2 - dblX1) != 0)
							dblBLSlope = (dblY2 - dblY1) / (dblX2 - dblX1);

						intX1	=	pSeries->CalcXPosValue(dblX1);
						intY1	=	pSeries->CalcYPosValue(dblY1);

						intX2	=	pSeries->CalcXPosValue(dblX2);
						intY2	=	pSeries->CalcYPosValue(dblY2);

						int intRectCount =0;
						//POINT *ptFillPeak = new POINT[4];	
						POINT *ptFillPeak	=	new POINT[4];

						for(long j=0;j<pSeries->GetXValues()->GetCount();j++)  
						{
							if( j>= intPeakStartIndex)
							{

								double dbltmpX = (pSeries->GetXValues()->GetValue(j));//*pow(10,m_intXPrecision);
								double dbltmpY = (pSeries->GetYValues()->GetValue(j));//*pow(10,m_intYPrecision);

								double dblYOnBL = dblBLSlope * (dbltmpX - dblX1) + dblY1;

								/*if((m_intBaseLineType == 2))
								if(dbltmpY <= dblYOnBL)
								continue;*/

								long intX;
								long intY;

								long intYOnBL;

								intX	=	pSeries->CalcXPosValue(dbltmpX);

								intY	=	pSeries->CalcYPosValue(dbltmpY);

								intYOnBL	=	pSeries->CalcYPosValue(dblYOnBL);


								VARIANT var;
								var.vt	=	VT_ARRAY|VT_I4;

								SAFEARRAY *pSa;
								SAFEARRAYBOUND sab[1]={8};
								if(intRectCount == 0)
								{							
									ptFillPeak[0].x = intX;
									ptFillPeak[0].y = /*m_lngYmax -*/ intYOnBL /*+ m_lngYmin*/;

									ptFillPeak[1].x = intX;
									ptFillPeak[1].y = /*m_lngYmax - */intY /*+ m_lngYmin*/;									

									intRectCount = 1;
								}
								else
								{
									ptFillPeak[2].x = intX;
									ptFillPeak[2].y = /*m_lngYmax -*/ intY /*+ m_lngYmin*/;

									ptFillPeak[3].x = intX;
									ptFillPeak[3].y = /*m_lngYmax -*/ intYOnBL /*+ m_lngYmin*/;	

									prcCalculatePoints(ptFillPeak[0], ptFillPeak[1]);
									prcCalculatePoints(ptFillPeak[1], ptFillPeak[2]);
									prcCalculatePoints(ptFillPeak[2], ptFillPeak[3]);
									prcCalculatePoints(ptFillPeak[3], ptFillPeak[1]);


									pSa	=	SafeArrayCreate(VT_I4,1,sab);
									long lngIndeces	=	0;
									for(int cnt=0;cnt<4;cnt++)
									{
										SafeArrayPutElement(pSa,&lngIndeces,&ptFillPeak[cnt].x);
										lngIndeces++;
										SafeArrayPutElement(pSa,&lngIndeces,&ptFillPeak[cnt].y);
										lngIndeces++;
									}

									var.parray	=	pSa;

									pcanvas->Polygon(4,var); //Polygon(hdcDraw,ptFillPeak,4);

									SafeArrayDestroy(pSa);
									//	VariantClear(&var); // if puts this ,gives assertion

									ptFillPeak[0].x = ptFillPeak[3].x;
									ptFillPeak[0].y = ptFillPeak[3].y;									

									ptFillPeak[1].x = ptFillPeak[2].x;
									ptFillPeak[1].y = ptFillPeak[2].y;									
								}


								if(j == intPeakEndIndex) // Peak End is reached
								{

									if(!(m_intBaseLineType == 2 ))//&& m_blnCustomBaseLineDrawn == TRUE)) // Draw the Point - Point BaseLine;
									{
										POINT p1, p2;
										p1.x = intX1;
										p1.y = intY1;

										p2.x = intX2;
										p2.y = intY2;

										prcCalculatePoints(p1,p2);

									}

									++intPeakNo; // Move Onto Next Peak

									if(intPeakNo >= pPeakInfo->intPeakStartIndex.GetSize())
									{
										break;
									}

									intPeakStartIndex = pPeakInfo->intPeakStartIndex.GetAt(intPeakNo);
									intPeakEndIndex = pPeakInfo->intPeakEndIndex.GetAt(intPeakNo);

									if(intPeakStartIndex==j)
										j--;

									if(!(m_intBaseLineType == 2 ))
									{
										//Abhinav
										stuPeakDetectPoint objPeakStartPoint = m_arrPeakDetectPoint.GetAt(intPeakStartIndex);
										dblX1 =objPeakStartPoint.X;
										dblY1 =objPeakStartPoint.Y;

										stuPeakDetectPoint objPeakEndPoint = m_arrPeakDetectPoint.GetAt(intPeakEndIndex);
										dblX2 = objPeakEndPoint.X;
										dblY2 = objPeakEndPoint.Y;
										//Abhinav

										//dblX1 = (pSeries->GetXValues()->GetValue(intPeakStartIndex));//*pow(10,m_intXPrecision);
										//dblY1 = (pSeries->GetYValues()->GetValue(intPeakStartIndex));//*pow(10,m_intYPrecision);

										//dblX2 = (pSeries->GetXValues()->GetValue(intPeakEndIndex));//*pow(10,m_intXPrecision);
										//dblY2 = (pSeries->GetYValues()->GetValue(intPeakEndIndex));//*pow(10,m_intYPrecision);
									}
									if(m_intBaseLineType==2)
									{
										/*int nPeakCnt	=	pPeakInfo->intPeakEndIndex.GetSize();
										intPeakEndIndex1	=	pPeakInfo->intPeakEndIndex.GetAt(nPeakCnt-1);*/
										dblX1 = pSeries->GetXValues()->GetValue(intPeakStartIndex);
										dblY1 = pSeries->GetYValues()->GetValue(intPeakStartIndex1);

										dblX2 = pSeries->GetXValues()->GetValue(intPeakEndIndex);//
										dblY2 = pSeries->GetYValues()->GetValue(intPeakStartIndex1);//

									}

									dblBLSlope = 0;

									if((dblX2 - dblX1) != 0)
										dblBLSlope = (dblY2 - dblY1) / (dblX2 - dblX1);

									intX1	=	pSeries->CalcXPosValue(dblX1);
									intY1	=	pSeries->CalcYPosValue(dblY1);

									intX2	=	pSeries->CalcXPosValue(dblX2);
									intY2	=	pSeries->CalcYPosValue(dblY2);


									intRectCount = 0;

								} //if(j == intPeakEndIndex)

							}  //if( j>= intPeakStartIndex)

						}//for(long j=0;j<pSeries->GetXValues()->GetCount();j++)	

						delete []ptFillPeak;

					}  //if					

				} //BSTR's Comparison 'if' loop				

			}  // first 'if' loop within 'for		

		}  //First  'for' loop		

	} // First else condition	

	m_chart.Repaint();

	pSeries	=	NULL;
	pcanvas	=	NULL;
}
//*************************************************
//PURPOSE : To draw the baseline for the Graph.
//INPUTS  : LONG lngGraphIdx  - Graph ID 
//ASSUMES : 
//RETURNS : 
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::DrawBaseLine(LONG lngGraphIdx) 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	if(lngGraphIdx<0 || lngGraphIdx>=m_chart.get_SeriesCount())
	{
		MessageBox(_T("Graph with this ID not exist"));
		return;
	}


	LPDISPATCH pDisp	=	m_chart.Series(lngGraphIdx);
	ISeriesPtr	pSeries	=	pDisp;
	pDisp->Release();
	_bstr_t bstrGraphName	=	pSeries->GetName();
	long lngIdx=GetLtblIdxFromName(bstrGraphName);
	if(lngIdx<0)
	{
		pSeries	=	NULL;
		return;
	}
	/*else
	{	
	stuRemovableGraphData obj=m_arrGraphRelatedSerieses.GetAt(lngIdx);
	_bstr_t bstr1(obj.bstrBaseLinename,TRUE);
	_bstr_t bstr2(_T(""));
	if(bstr1!=bstr2)
	{
	pSeries	=	NULL;
	return;
	}
	}*/	//Commented on 10/01/'08


	/*	if(lngIdx>m_GraphPeaks.GetSize())
	return;*/ // 26/10/'07
	stuPeakInfo *pPeakInfo=NULL; 
	for(int i=0;i<m_GraphPeaks.GetSize();i++)   // Silpa.S 26/10/07
	{
		pPeakInfo = m_GraphPeaks.GetAt(i);
		_bstr_t strPeakInfoGraph(pPeakInfo->strGraphName,TRUE);
		if(bstrGraphName==strPeakInfoGraph)
		{
			stuRemovableGraphData obj;
			long size=(long)pPeakInfo->dblPeakEndX.GetSize();//intArrPeakEndIndex.GetSize();
			if(size>0)
			{
				long SeriesNo1	=	m_chart.AddSeries(0); // To hold the Graph ID which is used for BaseLine Drawing

				LPDISPATCH pDisp	=	m_chart.Series(SeriesNo1);
				ISeriesPtr	pBLSeries	=	pDisp;// Smart pointer for 'Series' interface of series used for Baseline
				pDisp->Release();
				pBLSeries->put_Color(m_clrBaseLineColor);
				/// Removable 		
				stuRemovableGraphData obj=m_arrGraphRelatedSerieses.GetAt(lngIdx);
				_bstr_t bstr1(obj.bstrBaseLinename,TRUE);
				_bstr_t bstr2(_T(""));
				if(bstr1==bstr2)// If Base line for specified graph is drawn for first time store the Graph name(i.e 'SeriesNo1'graph)
				{
					obj.bstrBaseLinename=(pBLSeries->GetName()).copy();
				}
				else// If Baseline function is calling more than once for the same graph, then remove the Graph used
				{	// for Base line for previous call and store the present call's Graph name.
					long subidx=GetGraphIdxFromName(bstr1);
					m_chart.RemoveSeries(subidx);
					obj.bstrBaseLinename=pBLSeries->GetName().copy();
				}
				m_arrGraphRelatedSerieses.SetAt(lngIdx,obj);

				pBLSeries->put_ShowInLegend(FALSE);
				//((ISeries*)m_chart.Series(SeriesNo1))->put_Color(RGB(0,0,255));
				if(m_intBaseLineType==2)
				{			
					pBLSeries->AddXY(pPeakInfo->dblPeakStartX.GetAt(0),pPeakInfo->dblPeakStartY.GetAt(0),"",123);
					for(long i=0;i<pPeakInfo->intPeakMaxIndex.GetSize();i++)
					{
						pBLSeries->AddXY(pPeakInfo->dblPeakEndX.GetAt(i),pPeakInfo->dblPeakStartY.GetAt(0),"",123);
						pBLSeries->AddXY(pPeakInfo->dblPeakEndX.GetAt(i),pPeakInfo->dblPeakEndY.GetAt(i),"",123);
						pBLSeries->AddXY(pPeakInfo->dblPeakEndX.GetAt(i),pPeakInfo->dblPeakStartY.GetAt(0),"",123);
					}
					pBLSeries->AddXY(pPeakInfo->dblPeakEndX.GetAt(size-1),pPeakInfo->dblPeakStartY.GetAt(0),"",123);

				}
				else if(m_intBaseLineType!=2)
				{
					for(long i=0;i<size;i++)
					{				
						pBLSeries->AddXY(pPeakInfo->dblPeakStartX.GetAt(i),pPeakInfo->dblPeakStartY.GetAt(i),"",237);
						pBLSeries->AddXY(pPeakInfo->dblPeakEndX.GetAt(i),pPeakInfo->dblPeakEndY.GetAt(i),"",237);
						if(i<(size-1))
							pBLSeries->AddNullXY(pPeakInfo->dblPeakStartX.GetAt(i+1),pPeakInfo->dblPeakStartY.GetAt(i+1),"");
					}

				}				
				pBLSeries	=	NULL;
			}
		} 
		//	SysFreeString(strPeakInfoGraph);
	}
	//SysFreeString(bstrGraphName);
	//	stuPeakInfo *pPeakInfo=m_GraphPeaks.GetAt(lngIdx);	//26/10/'07


	pSeries	=	NULL;
}

//*************************************************
//PURPOSE : Function to find the Peak values based on the 
//			selected values baseline Type 
//INPUTS  : 
//ASSUMES : 
//RETURNS : 
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::fncPerformIntegration(void)
{
	if(m_GraphPeaks.GetSize() < 1 ) // If not even one peak is detected
		return; 

	stuPeakInfo *PeakInfo = NULL;

	double dblTmpHeight = 0;
	double dblTmpWidth = 0;
	double dblTmpArea = 0;

	double dblBLSLope;
	double dblYOnBL;

	CArray<int, int> arrPeaksToBeRemoved;

	for(int i = 0; i<m_GraphPeaks.GetSize(); i++)
	{
		PeakInfo = m_GraphPeaks.GetAt(i);

		if(PeakInfo == NULL)
			continue;

		if(PeakInfo->intPeakMaxIndex.GetSize() < 1) 
			continue;

		for(int j = 0; j < PeakInfo->intPeakMaxIndex.GetSize(); j++)
		{
			dblTmpArea = 0.0;
			dblTmpHeight = 0.0;
			dblTmpWidth = 0.0;

			m_dblPeakStartX = PeakInfo->dblPeakStartX.GetAt(j);
			m_dblPeakStartY = PeakInfo->dblPeakStartY.GetAt(j);
			m_dblPeakMaxX   = PeakInfo->dblPeakMaxX.GetAt(j); 
			m_dblPeakMaxY   = PeakInfo->dblPeakMaxY.GetAt(j); 
			m_dblPeakEndX   = PeakInfo->dblPeakEndX.GetAt(j);
			m_dblPeakEndY   = PeakInfo->dblPeakEndY.GetAt(j);


			m_intPeakStartIndex = PeakInfo->intPeakStartIndex.GetAt(j);
			m_intPeakMaxIndex   = PeakInfo->intPeakMaxIndex.GetAt(j);
			m_intPeakEndIndex   = PeakInfo->intPeakEndIndex.GetAt(j);


			// Width Calculation
			dblTmpWidth = (m_dblPeakEndX - m_dblPeakStartX);

			if(dblTmpWidth < m_dblMinWidth)
			{
				arrPeaksToBeRemoved.Add(j);				
				continue;
			}

			// Height Calculation
			if(m_intBaseLineType == 2 )
			{				
				/*if ((m_dblBaseLineEndX - m_dblBaseLineStartX) != 0)
				dblBLSLope =PeakInfo-> (m_dblBaseLineEndY - m_dblBaseLineStartY) / (m_dblBaseLineEndX - m_dblBaseLineStartX);*/

				dblYOnBL =PeakInfo->dblPeakStartY.GetAt(0);// dblBLSLope *(m_dblPeakMaxX - m_dblBaseLineStartX) + m_dblBaseLineStartY;
			}
			else
			{
				if ((m_dblPeakEndX - m_dblPeakStartX) != 0)
					dblBLSLope = (m_dblPeakEndY - m_dblPeakStartY) / (m_dblPeakEndX - m_dblPeakStartX);

				dblYOnBL = dblBLSLope *(m_dblPeakMaxX - m_dblPeakStartX) + m_dblPeakStartY;
			}

			dblTmpHeight = fabs(m_dblPeakMaxY - dblYOnBL);	

			if( dblTmpHeight < m_dblMinHeight)
			{
				arrPeaksToBeRemoved.Add(j);
				continue;
			}


			// Area Calculation
			stuPeakDetectPoint obj1, obj2;
			obj1 = m_arrPeakDetectPoint.GetAt(m_intPeakStartIndex);
			obj2 = m_arrPeakDetectPoint.GetAt(m_intPeakEndIndex);
			double dblBaseLineArea;

			if(m_intBaseLineType == 2 )
			{	
				/*double dblYStartOnBL = dblBLSLope * (obj1.X - m_dblBaseLineStartX) + m_dblBaseLineStartY;
				double dblYEndOnBL = dblBLSLope * (obj2.X - m_dblBaseLineStartX) + m_dblBaseLineStartY;
				dblBaseLineArea = 0.5 * (dblYStartOnBL + dblYEndOnBL) * (obj2.X - obj1.X);*/
				double dblTempYValue; // ss For Area calculation under baseline
				if(PeakInfo->dblPeakStartY.GetSize()>0)			
					dblTempYValue=PeakInfo->dblPeakStartY.GetAt(0);		
				else
					dblTempYValue=obj1.Y;

				double dblInterval = 0;
				dblBaseLineArea =  0.5 * (2*dblTempYValue) * (obj2.X - obj1.X);
			}
			else
			{
				dblBaseLineArea =  0.5 * (obj1.Y + obj2.Y) * (obj2.X - obj1.X);
			}


			double dblY0 = obj1.Y;
			double dblYn = obj2.Y;
			double dblY = 0;
			double dblInterval = 0;

			if(m_intPeakEndIndex > m_intPeakStartIndex)
			{
				obj2 = m_arrPeakDetectPoint.GetAt(m_intPeakStartIndex+1);
				dblInterval = fabs(obj2.X - obj1.X);
			}

			for(int i = m_intPeakStartIndex + 1 ; i < m_intPeakEndIndex; i++)
			{
				obj1 = m_arrPeakDetectPoint.GetAt(i);				
				dblY += obj1.Y;
			}

			dblTmpArea = dblInterval /2 * (dblY0 + dblYn + (2 * dblY));
			dblTmpArea = fabs(dblTmpArea - dblBaseLineArea);

			//CString s;
			//s.Format(_T("%lf %lf"),dblTmpArea,m_dblMinArea);
			//AfxMessageBox(s);

			if(dblTmpArea <  m_dblMinArea)
			{
				arrPeaksToBeRemoved.Add(j);
				continue;
			}

			PeakInfo->dblArea.SetAt(j,dblTmpArea);
			PeakInfo->dblHeight.SetAt(j, dblTmpHeight);
			PeakInfo->dblWidth.SetAt(j, dblTmpWidth);			
		}


		// Remove the Unwanted Peaks
		int intPeakNoToRemove;

		for(int j = 0; j < arrPeaksToBeRemoved.GetSize(); j++)
		{
			intPeakNoToRemove = arrPeaksToBeRemoved.GetAt(j);

			PeakInfo->dblPeakStartX.RemoveAt(intPeakNoToRemove);
			PeakInfo->dblPeakStartY.RemoveAt(intPeakNoToRemove);

			PeakInfo->dblPeakMaxX.RemoveAt(intPeakNoToRemove);
			PeakInfo->dblPeakMaxY.RemoveAt(intPeakNoToRemove);

			PeakInfo->dblPeakEndX.RemoveAt(intPeakNoToRemove);
			PeakInfo->dblPeakEndY.RemoveAt(intPeakNoToRemove);

			PeakInfo->intPeakEndIndex.RemoveAt(intPeakNoToRemove);
			PeakInfo->intPeakMaxIndex.RemoveAt(intPeakNoToRemove);
			PeakInfo->intPeakStartIndex.RemoveAt(intPeakNoToRemove);

			PeakInfo->dblArea.RemoveAt(intPeakNoToRemove);
			PeakInfo->dblHeight.RemoveAt(intPeakNoToRemove);			
			PeakInfo->dblWidth.RemoveAt(intPeakNoToRemove);

			int intNumber;

			for(int k = j+1; k < arrPeaksToBeRemoved.GetSize(); k++)
			{
				intNumber = arrPeaksToBeRemoved.GetAt(k) - 1;
				arrPeaksToBeRemoved.SetAt(k, intNumber);
			}
		}

		if(arrPeaksToBeRemoved.GetSize() > 0)
		{
			arrPeaksToBeRemoved.RemoveAll();
			arrPeaksToBeRemoved.FreeExtra();
		}

	}
}


//*************************************************
//PURPOSE : Function to retrieve the Index(ID) of the Graph based on the Given Name.
//INPUTS  : BSTR bstrGraphName  -- Name of the Graph 			
//ASSUMES : 
//RETURNS : long	   -- Index of the Graph if given Graph name is Exists
//			returns -1 -- if given Name not exists .
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
long CEsdAdvancedGraphCtrl::GetGraphIdxFromName(BSTR bstrGraphName)
{
	LPDISPATCH pDisp = NULL;
	ISeriesPtr	pSeries	=	NULL;
	for(long i=0;i<m_chart.get_SeriesCount();i++)
	{
		pDisp	=	m_chart.Series(i);
		pSeries	=	pDisp;
		pDisp->Release();
		_bstr_t bstrTemp=((ISeries*)m_chart.Series(i))->GetName();
		//	_bstr_t bstr1(bstr,TRUE);
		_bstr_t bstrGraph(bstrGraphName,TRUE);

		pSeries	=	NULL;
		if(bstrTemp==bstrGraph)
		{
			//	SysFreeString(bstrTemp);
			//	SysFreeString(bstrGraph);
			return i;
		}
	}
	return -1;
}

//*************************************************
//PURPOSE : Function to retrieve the Index(ID) of the Graph stored in the 
//			LookUp table of "stuRemovableGraphData" based on the Given Name.
//INPUTS  : BSTR bstrLtblGraphName  -- Name of the Graph 			
//ASSUMES : 
//RETURNS : long	   -- Index of the Graph if given Graph name is Stored in the LookUp Table
//			returns -1 -- if given Name not exists in the Look Up Table
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
long CEsdAdvancedGraphCtrl::GetLtblIdxFromName(BSTR bstrLtblgraphName)
{
	for(long i=0;i<m_arrGraphRelatedSerieses.GetSize();i++)
	{
		stuRemovableGraphData obj=m_arrGraphRelatedSerieses.GetAt(i);
		_bstr_t bstr1((obj.bstrGraphName),TRUE);
		_bstr_t bstr2(bstrLtblgraphName,TRUE);
		if(bstr1==bstr2)//obj.bstrGraphName==bstrLtblgraphName)
		{
			//	SysFreeString(bstr1);
			//	SysFreeString(bstr2);
			return i;
		}
	}
	return -1;

}

//*************************************************
//PURPOSE : Function to retrieve the Index(ID) of the Graph stored in the 
//			LookUp table of Custom Text Information , based on the Given Name.
//INPUTS  : BSTR bstrLtblGraphName  -- Name of the Graph 			
//ASSUMES : 
//RETURNS : long	   -- Index of the Graph if given Graph name is Stored in the LookUp Table
//			returns -1 -- if given Name not exists in the Look Up Table
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
long CEsdAdvancedGraphCtrl::GetCutomtextLTblIdxFromName(BSTR bstrLtblGraphName)
{
	for(long i=0;i<m_objPlotAreaText.GetSize();i++)
	{
		stuRemovableGraphData obj=m_arrGraphRelatedSerieses.GetAt(i);
		_bstr_t bstr1((obj.bstrGraphName),TRUE);
		_bstr_t bstr2(bstrLtblGraphName,TRUE);
		if(bstr1==bstr2)//obj.bstrGraphName==bstrLtblgraphName)
		{
			//	SysFreeString(bstr1);
			//	SysFreeString(bstr2);
			return i;
		}
	}
	return -1;

}

// Property to Get the BaseLine Type
LONG CEsdAdvancedGraphCtrl::GetBaseLineType(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	return m_intBaseLineType;
}

//Property to set the BaseLine Type
void CEsdAdvancedGraphCtrl::SetBaseLineType(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	if(newVal>=1 && newVal<=2)
		m_intBaseLineType=newVal;
	else
		MessageBox(_T("BaseLine Type must be b/w 1 to 2"));

	SetModifiedFlag(TRUE);
}

//Property to Get the BaseLine Color value
OLE_COLOR CEsdAdvancedGraphCtrl::GetBaseLineColor(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	return m_clrBaseLineColor;
}

// Property to set the BaseLine Color Value
void CEsdAdvancedGraphCtrl::SetBaseLineColor(OLE_COLOR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here

	OleTranslateColor(newVal, NULL, &m_clrBaseLineColor);
	SetModifiedFlag(TRUE);
}

//*************************************************
//PURPOSE : Method to get the Count of Graphs drawn on the Control
//INPUTS  : 
//ASSUMES : 
//RETURNS : LONG  -- Count of the Graphs
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
LONG CEsdAdvancedGraphCtrl::GetNumberOfGraphs(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	LONG lngNoOfGraphs;
	lngNoOfGraphs=(LONG)m_arrGraphRelatedSerieses.GetSize();

	return lngNoOfGraphs;
}

//*************************************************
//PURPOSE : Method to get All Graph IDs drawn by client on The Control
//INPUTS  : 
//ASSUMES : 
//RETURNS : LONG  -- Count of the Graphs
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
LONG CEsdAdvancedGraphCtrl::GetAllGraphIDs(VARIANT* varLngGraphIndexes)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	if(m_arrGraphRelatedSerieses.GetSize()<=0)
	{
		varLngGraphIndexes=NULL;
		return 0;
	}
	else
	{
		long lngGraphsCnt=(long)m_arrGraphRelatedSerieses.GetSize();
		SAFEARRAYBOUND sab[1];
		sab[0].cElements=lngGraphsCnt;
		sab[0].lLbound=0;
		SAFEARRAY *pSa=SafeArrayCreate(VT_R8,1,sab);
		long *lngArrGraphIndex=new long[lngGraphsCnt];
		for(long i=0;i<lngGraphsCnt;i++)
		{
			stuRemovableGraphData obj;
			obj=m_arrGraphRelatedSerieses.GetAt(i);
			_bstr_t bstrName(obj.bstrGraphName,TRUE);//(((ISeries*)m_chart.Series(i))->GetName()).copy();
			lngArrGraphIndex[i]=GetGraphIdxFromName(bstrName);
			SafeArrayPutElement(pSa,&i,&lngArrGraphIndex[i]);
		}
		varLngGraphIndexes->vt=VT_ARRAY|VT_I4;
		varLngGraphIndexes->parray=pSa;
		delete[] lngArrGraphIndex;
		return lngGraphsCnt;
	}
}

OLE_COLOR CEsdAdvancedGraphCtrl::GetPeakFillColor(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	return m_clrPeakFillColor;
}

void CEsdAdvancedGraphCtrl::SetPeakFillColor(OLE_COLOR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	OleTranslateColor(newVal,NULL,&m_clrPeakFillColor);

	SetModifiedFlag(TRUE);
}

DOUBLE CEsdAdvancedGraphCtrl::GetPeakMinArea(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	return m_dblMinArea;
}

void CEsdAdvancedGraphCtrl::SetPeakMinArea(DOUBLE newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	m_dblMinArea=newVal;

	SetModifiedFlag();
}

DOUBLE CEsdAdvancedGraphCtrl::GetPeakMinHeight(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	return m_dblMinHeight;
}

void CEsdAdvancedGraphCtrl::SetPeakMinHeight(DOUBLE newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here

	m_dblMinHeight=newVal;
	SetModifiedFlag();
}

DOUBLE CEsdAdvancedGraphCtrl::GetPeakMinWidth(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	return m_dblMinWidth;
}

void CEsdAdvancedGraphCtrl::SetPeakMinWidth(DOUBLE newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	m_dblMinWidth= newVal;
	SetModifiedFlag();
}

//*************************************************
//PURPOSE : Method to get the Peaks count in all the Graphs drawn on the Control
//INPUTS  : 
//ASSUMES : 
//RETURNS : VARIANT * varLngPeaksCount  -- Peaks Count 
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::GetPeaksCount(VARIANT* varLngPeaksCount)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	varLngPeaksCount->vt=VT_ARRAY|VT_I4;
	if(m_arrGraphRelatedSerieses.GetSize() <= 0)
	{		
		varLngPeaksCount->parray = NULL;
		return ;
	}
	stuPeakInfo * PeakInfo = NULL;
	long lngPeaksCnt=(long)m_GraphPeaks.GetSize();
	long* lngPeaksCount=new long[lngPeaksCnt];

	SAFEARRAYBOUND sab[1];


	sab[1].cElements=lngPeaksCnt;
	sab[1].lLbound=0;
	SAFEARRAY *pSafeArrPeakCnt=SafeArrayCreate(VT_I4,1,sab);

	for(long i = 0 ;i< lngPeaksCnt > 0; i++)
	{
		PeakInfo = m_GraphPeaks.GetAt(i);
		if(PeakInfo != NULL)
			lngPeaksCount[i] =(LONG) PeakInfo->dblArea.GetSize();
		else
			lngPeaksCount[i] = 0;
		SafeArrayPutElement(pSafeArrPeakCnt,&i,&lngPeaksCount[i]);
	}
	varLngPeaksCount->parray=pSafeArrPeakCnt;
	delete[] lngPeaksCount;
	delete PeakInfo;
}

//*************************************************
//PURPOSE : Function to Calculate All the Peaks indexes of the Particular graph
//INPUTS  : LONG lngGRaphIdx    -- GRaph ID
//ASSUMES : 
//RETURNS : long *lngPeakIndex  -- Indexes of all the Peaks 
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
long CEsdAdvancedGraphCtrl::fncCalculatePeakIndexes(long lngGraphIdx, long * lngPeakIndex)
{
	//EsdGRAPH_STRUCT* temp = m_objSamples->GetAt(intGraphID);

	stuRemovableGraphData temp;

	LPDISPATCH pDisp	=	m_chart.Series(lngGraphIdx);
	ISeriesPtr	pSeries	=	pDisp;
	pDisp->Release();
	_bstr_t bstrName=pSeries->GetName().copy();
	long lngIdx=GetLtblIdxFromName(bstrName);
	if(lngIdx<0)
		return 0;
	temp=m_arrGraphRelatedSerieses.GetAt(lngIdx);

	double dblOffset=((pSeries->GetYValues()->GetMaximum())-(pSeries->GetYValues()->GetMinimum()))*(temp.intPeakLevel)*0.05;// = ((temp->lngMaxOfYval - temp->lngMinOfYval)/pow(10, m_intYPrecision)) * temp->intPeakLevel * 0.05;

	double dblBase=pSeries->GetYValues()->GetValue(0);// = *temp->dblYval.GetAt(0);

	long	lngIndex = 0;

	int	i = 0;

	while(i<pSeries->GetYValues()->Count)
	{
		if(pSeries->GetYValues()->GetValue(i) < dblBase)			// This is for down the slope
			dblBase = pSeries->GetYValues()->GetValue(i);			

		if((pSeries->GetYValues()->GetValue(i) - dblBase) > dblOffset)
		{
			lngPeakIndex[lngIndex] = i;

			while(((pSeries->GetYValues()->GetValue(lngPeakIndex[lngIndex])) - (pSeries->GetYValues()->GetValue(i))) < dblOffset
				&& (i < pSeries->GetYValues()->Count-2))
			{

				i++;
				if((pSeries->GetYValues()->GetValue(i)) > (pSeries->GetYValues()->GetValue(lngPeakIndex[lngIndex])))				
					lngPeakIndex[lngIndex] = i;				
			}
			dblBase	= pSeries->GetYValues()->GetValue(i); //*temp->dblYval.GetAt(i);
			lngIndex++;
		}
		i++;
	}

	// Sorting the Peak values in Descending Order.

	for(i=0;i<lngIndex;i++)	
		for(int j=i+1;j<lngIndex;j++)
		{
			if(pSeries->GetYValues()->GetValue(lngPeakIndex[i]) < pSeries->GetYValues()->GetValue(lngPeakIndex[j]))
			{
				lngPeakIndex[i]+= lngPeakIndex[j];
				lngPeakIndex[j] = lngPeakIndex[i] - lngPeakIndex[j];
				lngPeakIndex[i] = lngPeakIndex[i] - lngPeakIndex[j];
			}
		}

		pSeries	=	NULL;
		return lngIndex;	
}


//*************************************************
//PURPOSE : Method to display the text at a point on the chart
//INPUTS  : LONG lngGraphIdx    -   Graph ID 
//          LPCTSTR bstrText	-	Text to be Displayed	 
//			double dblXval		-	X coord of data point.
//			double dblYval		-	Y coord of data point.
//			int intAlignStyle	-	Text Alignment with respect to data point.
//ASSUMES : -
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::DisplayTextAt(LONG lngGraphIdx, LPCTSTR bstrText, DOUBLE dblXVal, DOUBLE dblYVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	if(lngGraphIdx>=0 && lngGraphIdx<m_chart.get_SeriesCount())
	{
		EsdPLOTAREATEXT_STRUCT* text = new EsdPLOTAREATEXT_STRUCT;		//	Create a new object;

		text->clrTextColor		= m_clrCustomTextColor;

		LPDISPATCH pDisp	=	m_chart.Series(lngGraphIdx);
		ISeriesPtr	pSeries	=	pDisp;
		pDisp->Release();
		_bstr_t bstrGraphName = pSeries->GetName().copy();
		pSeries	=	NULL;

		long lngIdx=GetLtblIdxFromName(bstrGraphName);
		if(lngIdx<0)
			return;
		int nSize=(int)m_objPlotAreaText.GetSize();
		BOOL bFlag=FALSE; // To Know weather this text belongs to the Graph already containing  Text info or not
		if(nSize>0)
		{
			EsdPLOTAREATEXT_STRUCT *temp;
			for(int i=0;i<nSize;i++)
			{

				temp		=	m_objPlotAreaText.GetAt(i);
				_bstr_t bstr(temp->bstrGraphName,TRUE); 
				if(bstr==bstrGraphName) // Compare the Graph name stored in all the indexes, is equal to the
				{						// Current Graph Name.i.e The Text belongs to the Graph which hd already has Custom data
					temp->dblXVal.Add(dblXVal);   // If Graph name Already exists,then this new data added to the Old data
					temp->dblYVal.Add(dblYVal);	// otherwise New Instance is added to the new Graph in the Array.
					temp->strPlotAreaText.Add(bstrText);
					m_objPlotAreaText.SetAt(i,temp);
					bFlag=TRUE;
				}
				//	SysFreeString(bstr);
				/*	else
				{
				text->bstrGraphName     = bstrGraphName.copy();
				text->strPlotAreaText.Add(bstrText);								// Initialize all the member variables. 
				text->dblXVal.Add(dblXVal);
				text->dblYVal.Add(dblYVal);
				m_objPlotAreaText.Add(text);

				}*/

			}
			if(!bFlag)// 
			{			
				text->bstrGraphName     = bstrGraphName.copy();
				text->strPlotAreaText.Add(bstrText);								// Initialize all the member variables. 
				text->dblXVal.Add(dblXVal);
				text->dblYVal.Add(dblYVal);
				m_objPlotAreaText.Add(text);
			}
			temp=NULL;
		}
		else// For the very first time when this function is called this loop executes. For remaining calls 'IF' loop will execute
		{
			text->bstrGraphName     = bstrGraphName.copy();
			text->strPlotAreaText.Add(bstrText);								// Initialize all the member variables. 
			text->dblXVal.Add(dblXVal);
			text->dblYVal.Add(dblYVal);
			m_objPlotAreaText.Add(text);									// Store the address.
		}
		//	text = NULL;
		blnCustomText=TRUE;
		//	SysFreeString(bstrGraphName);;
		m_chart.Repaint();
	}
}

OLE_COLOR CEsdAdvancedGraphCtrl::GetBackGroundColor(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	return m_clrBackColor;
}

void CEsdAdvancedGraphCtrl::SetBackGroundColor(OLE_COLOR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here

	OleTranslateColor(newVal,NULL,&m_clrBackColor);
	//((ICanvas*)m_chart.get_Canvas())->BackColor	=	m_clrBackColor;
	//((ICanvas*)m_chart.get_Canvas())->BackMode	=	cbmOpaque;
	LPDISPATCH pDisp	=	m_chart.get_Panel();
	IPanelPtr pPanel	=	pDisp;
	pDisp->Release();
	pPanel->Color	=	m_clrBackColor;
	pPanel	=	NULL;

	SetModifiedFlag();
}

OLE_COLOR CEsdAdvancedGraphCtrl::GetCustomTextColor(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	return m_clrCustomTextColor;
}

void CEsdAdvancedGraphCtrl::SetCustomTextColor(OLE_COLOR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	OleTranslateColor(newVal,NULL,&m_clrCustomTextColor);
	SetModifiedFlag();
}

OLE_COLOR CEsdAdvancedGraphCtrl::GetCustomTextBackColor(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	return m_clrCustomTextBackColor;
}

void CEsdAdvancedGraphCtrl::SetCustomTextBackColor(OLE_COLOR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here

	OleTranslateColor(newVal,NULL,&m_clrCustomTextBackColor);
	SetModifiedFlag(TRUE);
}

DOUBLE CEsdAdvancedGraphCtrl::GetAverageNoise(void)
{
	return m_dblAverageNoise;
}

void CEsdAdvancedGraphCtrl::SetAverageNoise(DOUBLE newVal)
{
	m_dblAverageNoise=newVal;
}

OLE_COLOR CEsdAdvancedGraphCtrl::GetAxesMarkingColor(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	return m_clrMarkingColor;
}

void CEsdAdvancedGraphCtrl::SetAxesMarkingColor(OLE_COLOR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here

	OleTranslateColor(newVal,NULL,&m_clrMarkingColor);

	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes	=	pDisp;
	pDisp->Release();
	pAxes->GetLeft()->GetLabels()->GetFont()->put_Color(m_clrMarkingColor);
	pAxes->GetBottom()->GetLabels()->GetFont()->put_Color(m_clrMarkingColor);
	//	pAxes->GetBottom()->GetTitle()->GetFont()->GetGradient()->ShowEditor(TRUE);
	pAxes	=	NULL;
	SetModifiedFlag();
}

VARIANT_BOOL CEsdAdvancedGraphCtrl::GetShowLegends(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	return m_bShowLegends;
}

void CEsdAdvancedGraphCtrl::SetShowLegends(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	m_bShowLegends=newVal;

	LPDISPATCH pDisp = m_chart.get_Legend();
	ILegendPtr pLegend	=	pDisp;
	pLegend	=	pDisp;
	pLegend->put_Visible(newVal);
	pLegend	=	NULL;

	SetModifiedFlag();
}
//*************************************************
//PURPOSE : Method to get the graph data(X and Y Values)
//INPUTS  : LONG lngGRaphIdx  -- Graph ID
//ASSUMES : 
//RETURNS : VARIANT *varDblXval   -- 'X' coord values of the Graph
//			VARIANT *varDblYVal   -- 'Y' Coord values of the Graph
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
LONG CEsdAdvancedGraphCtrl::GetGraphData(LONG lngGraphIdx, VARIANT* varDblXval, VARIANT* varDblYval)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	LONG lngTotaldataCnt;
	if(lngGraphIdx>=0 && lngGraphIdx<m_chart.get_SeriesCount())		// Check for the existence of Graph.
	{	
		LPDISPATCH pDisp	=	m_chart.Series(lngGraphIdx);
		ISeriesPtr	pSeries	=	pDisp;
		pDisp->Release();
		_bstr_t bstrGraphName = pSeries->GetName().copy();
		long LTblIdx=GetLtblIdxFromName(bstrGraphName);
		if(LTblIdx<0)
		{
			MessageBox(_T("Graph with this Specified index doesn't exist"));
			pSeries	=	NULL;
			return 0;
		}
		//	SysFreeString(bstrGraphName);
		//		VARIANT varTemp;
		double Xval,Yval;
		lngTotaldataCnt = pSeries->GetXValues()->GetCount();// temp->dblXval.GetSize();
		SAFEARRAYBOUND sab[1];
		sab[0].cElements=lngTotaldataCnt;
		sab[0].lLbound=0;
		SAFEARRAY *pSa=SafeArrayCreate(VT_R8,1,sab);
		SAFEARRAY *pSa1=SafeArrayCreate(VT_R8,1,sab);
		for(long i=0;i<lngTotaldataCnt;i++)
		{
			Xval = pSeries->GetXValues()->GetValue(i);//*(temp->dblXval.GetAt(i));
			Yval = pSeries->GetYValues()->GetValue(i);//*(temp->dblXval.GetAt(i));
			SafeArrayPutElement(pSa,&i,&Xval);
			SafeArrayPutElement(pSa1,&i,&Yval);
		}
		VariantInit(varDblXval);
		VariantInit(varDblYval);
		varDblXval->vt=VT_ARRAY|VT_R8;
		varDblYval->vt=VT_ARRAY|VT_R8;
		varDblXval->parray=pSa;
		varDblYval->parray=pSa1;
		pSeries	=	NULL;
		return lngTotaldataCnt;
	}
	else
	{
		lngTotaldataCnt = 0;
		MessageBox(_T("Graph with this specified ID doesn't exists"));//String Table
		return lngTotaldataCnt;
	}

}
//*************************************************
//PURPOSE : Method to get X and Y Values at particular index of a given Graph
//INPUTS  : LONG lngGraphIdx	-- Graph ID
//			LONG lngIndex		-- Index At which we require X and Y values
//ASSUMES : 
//RETURNS : DOUBLE * dblXVal	-- 'X' coord value at given Index
//			DOUBLE * dblYVal	-- 'Y'   "	   "   "	"	  "
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::GetGraphDataAt(LONG lngGraphIdx, LONG lngIndex, DOUBLE* dblXval, DOUBLE* dblYval)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	//	EsdGRAPH_STRUCT* temp = NULL;

	if(lngGraphIdx>=0 && lngGraphIdx<m_chart.get_SeriesCount())			//	Check for the existence of Graph.
	{
		//	temp	=	m_objSamples->GetAt(lngGraphIdx);				//	Get the address of the Graph.
		LPDISPATCH pDisp	=	m_chart.Series(lngGraphIdx);
		ISeriesPtr	pSeries	=	pDisp;
		pDisp->Release();
		_bstr_t bstrGraphName = pSeries->GetName();
		LONG lIdx=GetLtblIdxFromName(bstrGraphName);
		if(lIdx<0)
		{
			MessageBox(_T("Graph With this ID doesn't exist"));
			pSeries	=	NULL;
			return;
		}
		if(lngIndex>=0 && lngIndex< pSeries->GetXValues()->GetCount())			//	Check for the validity of the Index.
		{

			*dblXval	=	pSeries->GetXValues()->GetValue(lngIndex);	//	Get the data points.	
			*dblYval	=	pSeries->GetYValues()->GetValue(lngIndex);
			pSeries	=	NULL;
			return ;
		}
		else
		{
			MessageBox(_T("Index value beyond the range."));////String Table
			pSeries	=	NULL;
			return ;//Error(IDS_INDEXVALUE_OUT_OF_RANGE);////String Table

		}
		//		SysFreeString(bstrGraphName);
	}
	else
	{
		MessageBox(_T("Graph with specified ID doesn't exists"));//String Table
		return;// Error(IDS_GRAPHID_DONOT_EXIST);//String Table
	}
}
//*************************************************
//PURPOSE : Method to get the total data count for the given Graph
//INPUTS  : LONG lngGRaphIdx	--  Graph ID
//ASSUMES : 
//RETURNS : LONG  -- Count of the Graph data points
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
LONG CEsdAdvancedGraphCtrl::GetGraphDataCont(LONG lngGraphIdx)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	LONG lngDataCnt;
	if(lngGraphIdx>=0 && lngGraphIdx<m_chart.get_SeriesCount())		// Check for the existence of Graph.
	{
		//temp = m_objSamples->GetAt(lngGraphIdx);		// Get the address of the Graph.
		LPDISPATCH pDisp	=	m_chart.Series(lngGraphIdx);
		ISeriesPtr	pSeries	=	pDisp;
		pDisp->Release();
		_bstr_t bstrGraphName = pSeries->GetName();
		LONG lIdx=GetLtblIdxFromName(bstrGraphName);
		if(lIdx<0)
		{
			MessageBox(_T("Graph With this ID doesn't exist"));
			pSeries	=NULL;
			return 0;
		}
		else
		{
			lngDataCnt = pSeries->GetXValues()->GetCount();			// Return the data count.
			pSeries	=	NULL;
			return lngDataCnt;
		}
		//	SysFreeString(bstrGraphName);
	}
	else
	{
		MessageBox(_T("Graph with specified ID doesn't exists"));//String Table
		return 0;//Error(IDS_GRAPHID_DONOT_EXIST);//String Table
	}	

}

//*************************************************
//PURPOSE : Method to return the least and highest X & Y data values of a Graph.
//INPUTS  : LONG lngGraphIdx	--  Graph ID
//ASSUMES : 
//RETURNS : DOUBLE *dblXmin		--  Minimum of 'X' coord values of the Graph
//			DOUBLE *dblYmin		--		"    " 'Y'   "     "	"   "    "
//			DOUBLE *dblXmax		--	Maximum of 'X'	 "	   "	"	"	 "
//			DOUBLE *dblYmax		--		"	"  'Y'	 "	   "	"	"	 "
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::GetGraphMinMax(LONG lngGraphIdx, DOUBLE* dblXmin, DOUBLE* dblYmin, DOUBLE* dblXmax, DOUBLE* dblYmax)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	if(lngGraphIdx>=0 && lngGraphIdx<m_chart.get_SeriesCount())		// Check for the existence of Graph.
	{
		//temp = m_objSamples->GetAt(lngGraphIdx);					// Get the address of Graph.
		LPDISPATCH pDisp	=	m_chart.Series(lngGraphIdx);
		ISeriesPtr	pSeries	=	pDisp;
		pDisp->Release();
		_bstr_t bstrGraphName = pSeries->GetName();
		LONG lIdx=GetLtblIdxFromName(bstrGraphName);
		if(lIdx<0)
		{
			MessageBox(_T("Graph With this ID doesn't exist"));
			pSeries	=	NULL;
			return;
		}
		//	SysFreeString(bstrGraphName);
		if(pSeries->GetXValues()->GetCount()>0)							// Check for the number of data points in this particular Graph
		{
			*dblXmin = pSeries->GetXValues()->GetMinimum();	// Copy the least & highest values of this particular Graph.
			*dblYmin = pSeries->GetYValues()->GetMinimum();
			*dblXmax = pSeries->GetXValues()->GetMaximum();
			*dblYmax = pSeries->GetYValues()->GetMaximum();
		}

		pSeries	=	NULL;
	}
	else
	{
		MessageBox(_T("Graph with specified ID doesn't exists"));//String Table
		return ;//Error(IDS_GRAPHID_DONOT_EXIST);//String Table
	}	

}
void CEsdAdvancedGraphCtrl::OnDestroy()
{
	COleControl::OnDestroy();
	// TODO: Add your message handler code here

	// Remove PlotArea Text info
	if(m_objPlotAreaText.GetSize()>0)
	{
		EsdPLOTAREATEXT_STRUCT * pPlotAreaText=NULL;
		for(int i=0;i<m_objPlotAreaText.GetSize();i++)
		{
			pPlotAreaText=m_objPlotAreaText.GetAt(i);
			//	pPlotAreaText->bstrGraphName=_T("");
			SysFreeString(pPlotAreaText->bstrGraphName);
			pPlotAreaText->clrTextColor=0;
			pPlotAreaText->dblXVal.RemoveAll();
			pPlotAreaText->dblYVal.RemoveAll();
			pPlotAreaText->strPlotAreaText.RemoveAll();
			delete pPlotAreaText;
			pPlotAreaText=NULL;
		}
		m_objPlotAreaText.RemoveAll();
		m_objPlotAreaText.FreeExtra();

	}
	if(m_objCustomText.GetSize()>0)						// Clear the custom text.
	{
		m_objCustomText.RemoveAll();
		m_objCustomText.FreeExtra();			
	}
	// To Remove Graphs data related to all the User Added graphs
	if(m_arrGraphRelatedSerieses.GetSize()>0)
	{
		stuRemovableGraphData objRemoveGraphs;
		for(int i=0;i<m_arrGraphRelatedSerieses.GetSize();i++)
		{
			objRemoveGraphs=m_arrGraphRelatedSerieses.GetAt(i);
			SysFreeString(objRemoveGraphs.bsrLinearfitName);
			SysFreeString(objRemoveGraphs.bstrBaseLinename);
			SysFreeString(objRemoveGraphs.bstrCustomTrendLineName);
			SysFreeString(objRemoveGraphs.bstrFillName);
			SysFreeString(objRemoveGraphs.bstrGraphName);
			SysFreeString(objRemoveGraphs.bstrQuadraticFitName);
			SysFreeString(objRemoveGraphs.bstrLogFit);
			SysFreeString(objRemoveGraphs.bstrExpFit);
			SysFreeString(objRemoveGraphs.bstrPowerFit);
		}
		m_arrGraphRelatedSerieses.RemoveAll();
		m_arrGraphRelatedSerieses.FreeExtra();
	}			

	if(m_arrPeakDetectPoint.GetSize() > 0 )
	{
		m_arrPeakDetectPoint.RemoveAll();
		m_arrPeakDetectPoint.FreeExtra();
	}

	// To Remove info about Manual Cursor(Datum Line)
	if(m_objDatumLineInfo.GetSize()>0)
	{
		m_objDatumLineInfo.RemoveAll();
		m_objDatumLineInfo.FreeExtra();
	}

	//Remove the data stored to display the information at peaks(i.e 'prcDisplayPeaks')
	if(m_arrPeakInfoIndexes.GetSize()>0)
	{
		EsdPeakInfoDisplay_Struct *temp	=	NULL;
		for(int i=0;i<m_arrPeakInfoIndexes.GetSize();i++)
		{
			temp	=	m_arrPeakInfoIndexes.GetAt(i);

			/*temp->lngvalueIdx.RemoveAll();
			temp->lngvalueIdx.FreeExtra();
			temp->strPeakInfo.RemoveAll();
			temp->strPeakInfo.FreeExtra();*/

			delete temp;
		}
		temp	=	NULL;
		m_arrPeakInfoIndexes.RemoveAll();
		m_arrPeakInfoIndexes.FreeExtra();

	}

	//Delete peak Information 
	if(m_GraphPeaks.GetSize() > 0)
	{
		stuPeakInfo* PeakInfo = NULL;
		for(int i = 0; i < m_GraphPeaks.GetSize(); i++)
		{
			PeakInfo = m_GraphPeaks.GetAt(i);

			PeakInfo->dblArea.RemoveAll();
			PeakInfo->dblHeight.RemoveAll();
			PeakInfo->dblPeakEndX.RemoveAll();
			PeakInfo->dblPeakEndY.RemoveAll();
			PeakInfo->dblPeakMaxX.RemoveAll();
			PeakInfo->dblPeakMaxY.RemoveAll();
			PeakInfo->dblPeakStartX.RemoveAll();
			PeakInfo->dblPeakStartY.RemoveAll();
			PeakInfo->dblWidth.RemoveAll();
			PeakInfo->intPeakEndIndex.RemoveAll();
			PeakInfo->intPeakMaxIndex.RemoveAll();
			PeakInfo->intPeakStartIndex.RemoveAll();

			PeakInfo->dblArea.FreeExtra();
			PeakInfo->dblHeight.FreeExtra();
			PeakInfo->dblPeakEndX.FreeExtra();
			PeakInfo->dblPeakEndY.FreeExtra();
			PeakInfo->dblPeakMaxX.FreeExtra();
			PeakInfo->dblPeakMaxY.FreeExtra();
			PeakInfo->dblPeakStartX.FreeExtra();
			PeakInfo->dblPeakStartY.FreeExtra();
			PeakInfo->dblWidth.FreeExtra();
			PeakInfo->intPeakEndIndex.FreeExtra();
			PeakInfo->intPeakMaxIndex.FreeExtra();
			PeakInfo->intPeakStartIndex.FreeExtra();
			//SysFreeString(PeakInfo->strGraphName);

			m_dblWidthAtHalfHeight.RemoveAll();
			m_dblWidthAtHalfHeight.FreeExtra();
			m_dblLeftWidthAtHalfHeight.RemoveAll();
			m_dblLeftWidthAtHalfHeight.FreeExtra();
			m_dblRightWidthAtHalfHeight.RemoveAll();
			m_dblRightWidthAtHalfHeight.FreeExtra();


			delete PeakInfo;

			PeakInfo = NULL;
		}
		m_GraphPeaks.RemoveAll();
		m_GraphPeaks.FreeExtra();
	}

}

BSTR CEsdAdvancedGraphCtrl::GetBackImage(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: Add your dispatch handler code here
	strResult=m_strBackImage;

	return strResult.AllocSysString();
}

void CEsdAdvancedGraphCtrl::SetBackImage(LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	m_strBackImage=newVal;
	if(!PathFileExists(m_strBackImage))
	{
		MessageBox(_T("Given Image path is inCorrect"));
		return;
	}
	_bstr_t bstrImage(m_strBackImage);
	LPDISPATCH pDisp	=	m_chart.get_Panel();
	IPanelPtr pPanel	=	pDisp;
	pDisp->Release();
	pPanel->BackImageClear();
	pPanel->put_BackImageInside(TRUE);
	pPanel->BackImageLoad(bstrImage);
	pPanel	=	NULL;

	SetModifiedFlag();
}

//*************************************************
//PURPOSE : Function to retrieve the 'double' values from the 'VARIANT'
//INPUTS  : VARIANT varSource	-- VARIANt from which to retrive the Double Valueas
//ASSUMES : 
//RETURNS : DOUBLE * dblArrResult	-- Double values 
//			long					-- Count of the Double Values.
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
long CEsdAdvancedGraphCtrl::fncGetDoubleValuesFromSafeArray(VARIANT &varSource, DOUBLE * dblArrResult)
{
	if((varSource.vt&VT_ARRAY && varSource.vt&VT_R8))
	{
		LONG lngLBndX,lngUBndX;
		SafeArrayGetLBound(varSource.parray,1,&lngLBndX);
		SafeArrayGetUBound(varSource.parray,1,&lngUBndX);
		long lngArrIdx=0;
		for(long i=lngLBndX;i<=lngUBndX;i++)
		{
			SafeArrayGetElement(varSource.parray,&i,&dblArrResult[lngArrIdx]);
			lngArrIdx++;
		}
		return lngArrIdx;
	}
	else
		return 0;
}

//*************************************************
//PURPOSE : Method to get the Peaks Count of the perticular Graph
//INPUTS  : LONG lngGraphIdx	--	Graph ID
//ASSUMES : 
//RETURNS : LONG  -- Count of the Graphs
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
LONG CEsdAdvancedGraphCtrl::GetGraphPeaksCount(LONG lngGraphIdx)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	if(lngGraphIdx<0 && lngGraphIdx>=m_chart.get_SeriesCount())
	{
		MessageBox(_T("Graph with this Specified ID doesn't exist"));
		return 0;
	}
	LPDISPATCH pDisp	=	m_chart.Series(lngGraphIdx);
	ISeriesPtr	pSeries	=	pDisp;
	pDisp->Release();
	_bstr_t bstrGraphName = pSeries->GetName().copy();		
	pSeries	=	NULL;

	long lngIdx=GetLtblIdxFromName(bstrGraphName);
	if(lngIdx<0)
	{
		MessageBox(_T("Graph with this Specified ID doesn't exist"));
		return 0;
	}
	stuPeakInfo *pPeakInfo=NULL;
	for(int i=0;i<m_GraphPeaks.GetSize();i++)   // Silpa.S 26/10/07
	{
		pPeakInfo = m_GraphPeaks.GetAt(i);
		if(pPeakInfo!=NULL)
		{
			_bstr_t strPeakInfoGraph(pPeakInfo->strGraphName,TRUE);
			if(bstrGraphName==strPeakInfoGraph)
			{
				long lngPeakCount=(long)pPeakInfo->dblArea.GetSize();
				SysFreeString(strPeakInfoGraph);
				SysFreeString(bstrGraphName);
				return lngPeakCount;

			} 
			//	SysFreeString(strPeakInfoGraph);
		}
	}
	//	SysFreeString(bstrGraphName);	
	return 0;
}

//*************************************************
//PURPOSE : Method to print the total area of the control
//INPUTS  : LONG lngPrinterDC	--	DC of the selected printer
//			LONG lngPageLeft	--	Left position of the page from where the printing has to be started
//			LONG lngPageTop		--	Top     "	  "   "   "     "    "    "    "       "   "  "   "
//			LONG lngPageRight	--	Right   "	  "   "   "    upto  "    "    "       "   "  "   done.
//			LONG lngPageBottom	--	Bottom  "     "   "   "     "    "    "    "       "   "  "    "
//ASSUMES : 
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::PrintGraph(LONG lngPrinterDC, LONG lngPageLeft, LONG lngPageTop, LONG lngPageRight, LONG lngPageBottom)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	/*CPrintDialog m_PrintDlg(FALSE);
	if(m_PrintDlg.DoModal()==IDCANCEL)
	return;*/
	/*m_PrintDlg.GetPrinterDC();*/
	//	CDC dcPrinter;
	//	dcPrinter.Attach(PrinterhDC);

	HDC PrinterhDC=(HDC)lngPrinterDC;

	LPDISPATCH pDisp		=	m_chart.get_Printer();
	IPrinterPtr pPrinter	=	pDisp;
	pDisp->Release();
	//	pPrinter->put_Detail(0);	// If it sets to more than '0' then in printing fonts will change & also position of TextOuts changes
	pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes	=	pDisp;
	pDisp->Release();
	pAxes->GetLeft()->GetGridPen()->PutWidth(0);	// put '0' value to print the grid styles as we set. If we doesn't set it always grids will print
	// as solid lines (irrespective of Grid style)
	pAxes->GetBottom()->GetGridPen()->PutWidth(0);

	pPrinter->PrintPartialHandle(COleVariant(LONG(PrinterhDC)),lngPageLeft,lngPageTop,lngPageRight,lngPageBottom);//w-50,h/*lngPageBottom*/);

	pPrinter	=	NULL;
	pAxes		=	NULL;

	/**************************************************************/
	//	dcPrinter.DeleteDC();

	/*DOCINFO docinfo;
	memset(&docinfo, 0, sizeof(docinfo));
	docinfo.cbSize = sizeof(docinfo);
	docinfo.lpszDocName = _T("Silpa Graph Print");

	if (dcPrinter.StartDoc(&docinfo) < 0)
	{
	MessageBox(_T("Printer would not initalize"));
	}
	else
	{
	if (dcPrinter.StartPage() < 0)
	{
	MessageBox(_T("Could not start page"));
	dcPrinter.AbortDoc();
	}

	else
	{	
	dcPrinter.SetMapMode(MM_LOENGLISH);*/
	/*	long w;
	if (pPrinter->GetOrientation() == poLandscape)
	{
	w = pPrinter->GetPageHeight();
	}
	else
	{
	w = pPrinter->GetPageWidth();
	}
	long h=dcPrinter.GetDeviceCaps(VERTRES);			
	w=dcPrinter.GetDeviceCaps(HORZRES);*/
	//	pPrinter->BeginDoc();
	//	pPrinter->put_Detail(100);
	//	pPrinter->PrintPartialHandle(COleVariant(LONG(PrinterhDC)),lngPageLeft,lngPageTop,lngPageRight,lngPageBottom);//w-50,h/*lngPageBottom*/);
	//	pPrinter>EndDoc(PrinterhDC);
	/*	dcPrinter.EndPage();
	dcPrinter.EndDoc();			
	}
	}
	pPrinter	=	NULL;
	dcPrinter.DeleteDC();*/
	/***********************************************************************/
}

//*************************************************
//PURPOSE : Method to preview the total area of the control on the selected device
//INPUTS  : LONG lngPrinterDC	--	DC of the selected printer/Window
//			LONG lngPageLeft	--	Left position of the page from where the printing has to be started
//			LONG lngPageTop		--	Top     "	  "   "   "     "    "    "    "       "   "  "   "
//			LONG lngPageRight	--	Right   "	  "   "   "    upto  "    "    "       "   "  "   done.
//			LONG lngPageBottom	--	Bottom  "     "   "   "     "    "    "    "       "   "  "    "
//ASSUMES : 
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::PrintPreview(LONG lnghDC, LONG lngPageLeft, LONG lngPageTop, LONG lngPageRight, LONG lngPageBottom)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	HDC PrinterhDC=(HDC)lnghDC;
	/*	
	//CDC dcPrinter;
	//dcPrinter.Attach(PrinterhDC);

	//int iSavedDC = dcPrinter.SaveDC();
	////pPrinter->PrintPartialHandle(COleVariant(LONG(PrinterhDC)),lngPageLeft,lngPageTop,lngPageRight,lngPageBottom);
	//	m_chart.Draw(lnghDC,lngPageLeft,lngPageTop,lngPageRight,lngPageBottom);
	////	pPrinter->ShowPreview();
	//dcPrinter.Detach();
	//dcPrinter.RestoreDC(iSavedDC);
	//PrintGraph(lnghDC,lngPageLeft,lngPageTop,lngPageRight,lngPageBottom);
	*/
	RECTL r;
	r.left	=	lngPageLeft;
	r.top	=	lngPageTop;
	r.right	=	lngPageRight;
	r.bottom	=	lngPageBottom;

	// Take the 'IViewObjectPtr' for 'PrintPreview' bcz the methods in TeeChart control are not working
	LPUNKNOWN pUnk	=	GetControlUnknown();
	if(pUnk!=NULL)
	{	
		// query for the IViewObject interface for printing (note, some don't support this, like lite controls)	
		IViewObjectPtr ptrView;
		HRESULT hRes	=	pUnk->QueryInterface(__uuidof(ptrView),(void**)&ptrView);
		if(!FAILED(hRes))
		{
			hRes =	ptrView->Draw(DVASPECT_CONTENT, -1, NULL, NULL,NULL, PrinterhDC, &r, NULL, NULL, 0);
			if (FAILED(hRes))
				AfxMessageBox(_T("Failed to draw the control"));
			ptrView = 0;
		}
		pUnk	=	NULL;
	}
}

//*************************************************
//PURPOSE : Returns weather the Horizontal datum line drawing is enabled or not
//INPUTS  : -
//ASSUMES : 
//RETURNS : VARIANT_BOOL	--	Boolean value
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
VARIANT_BOOL CEsdAdvancedGraphCtrl::GetEnableHorzDatumLine(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	return blnHorzDatumLine;
}

//*************************************************
//PURPOSE : Set the enable/Disable condition of Horizontal Datum line drawing
//INPUTS  : VARIANT_BOOL newVal		--	Enable(TRUE)/Disable(FALSE) condition
//ASSUMES : -
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::SetEnableHorzDatumLine(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	blnHorzDatumLine=newVal;
	//m_chart.Repaint();
	fncSetStateForDatumLine();

	SetModifiedFlag();
}

//*************************************************
//PURPOSE : Returns weather the Vertical datum line drawing is enabled or not
//INPUTS  : -
//ASSUMES : 
//RETURNS : VARIANT_BOOL	--	Boolean value
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
VARIANT_BOOL CEsdAdvancedGraphCtrl::GetEnableVericalDatumLine(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	return blnVertDatumLine;
}

//*************************************************
//PURPOSE : Set the enable/Disable condition of Vertical Datum line drawing
//INPUTS  : VARIANT_BOOL newVal		--	Enable(TRUE)/Disable(FALSE) condition
//ASSUMES : -
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::SetEnableVericalDatumLine(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	blnVertDatumLine	=	newVal;
	//	m_chart.Repaint();
	fncSetStateForDatumLine();

	SetModifiedFlag();
}

//*************************************************
//PURPOSE : Method to Draw the Datum line(Movable Line) For a particular
//			graph to find the Values corresponding to the Datum line on the Graph
//INPUTS  : LONG lngGraphIdx	--	Graph ID
//			DOUBLE dblXVal		--	X coord value where to start the Datum Line.
//			DOUBLE dblYVal		--	Y   "	  "		"	"	"	  "		"	"
//			OLE_COLOR clrLineColor -- Color of the Datum Line.
//ASSUMES : 
//RETURNS : 
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::DrawDatumLine(LONG lngGraphIdx, DOUBLE dblXVal, DOUBLE dblYVal, OLE_COLOR clrLineColor)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	if(blnHorzDatumLine==TRUE || blnVertDatumLine==TRUE)
	{
		if(lngGraphIdx<0 || lngGraphIdx>=m_chart.get_SeriesCount())
		{
			MessageBox(_T("Graph with this Specified ID doesn't exist"));
			return;
		}
		LPDISPATCH pDisp	=	m_chart.Series(lngGraphIdx);
		ISeriesPtr	pSeries	=	pDisp;
		pDisp->Release();
		_bstr_t bstrGraphName = pSeries->GetName().copy();
		long LTblIdx=GetLtblIdxFromName(bstrGraphName);
		if(LTblIdx<0)
		{
			MessageBox(_T("Graph with this index doesn't exist"));
			pSeries	=	NULL;
			return;
		}	
		EsdDATUMLINEINFO_STRUCT objDatumLine;
		pDisp	=	m_chart.get_Tools();
		IToolListPtr pToolList = pDisp;
		pDisp->Release();
		if(m_objDatumLineInfo.GetSize()>0)
		{
			EsdDATUMLINEINFO_STRUCT objDatumLinetemp=m_objDatumLineInfo.GetAt(0);

			int nToolCnt	=	pToolList->GetCount();
			for(int i=0;i<nToolCnt;i++)
			{
				long lngToolType	=	pToolList->GetItems(i)->GetToolType();
				if(lngToolType==objDatumLinetemp.lngDatumLineToolType)
					pToolList->Delete(i);
				if(lngToolType==objDatumLinetemp.lngTextDisplayToolType)
					pToolList->Delete(i);
			}	
			// If Datum line is already drawn for the graph then remove the old datum line 
			// and All data corresponding to the existing Datum line and insert new data
			for(int i=0;i<2;i++)
			{		
				_bstr_t bstrFixedDatumLine=(objDatumLinetemp.bstrFixedDatumLineName[i].copy());
				long lIdx=GetGraphIdxFromName(bstrFixedDatumLine);
				if(lIdx>=0)
				{
					objDatumLinetemp.bstrFixedDatumLineName[i]=_T("");
					//	SysFreeString(objDatumLinetemp.bstrFixedDatumLineName[i]);				
					m_chart.RemoveSeries(lIdx);
				}
			}
			objDatumLinetemp.bstrGraphName=_T("");
			//	SysFreeString(objDatumLine.bstrGraphName);
			m_objDatumLineInfo.RemoveAll();  // Remove previous instances of datum line and add new instances.
			m_objDatumLineInfo.FreeExtra();	
		}
		objDatumLine.bstrGraphName = pSeries->GetName().copy();
		objDatumLine.dblXVal=dblXVal;
		objDatumLine.dblYVal=dblYVal;
		objDatumLine.clrDatumLineColor=clrLineColor;

		// to Draw the Movable Datum Line
		VARIANT var;
		var.vt=VT_I8;
		var.lVal=lngGraphIdx;

		int nDatumLineIdx = pToolList->Add(tcCursor); //if '0' it Adds 'Cursor' Tool of TeeChart

		pToolList->GetItems(nDatumLineIdx)->GetasTeeCursor()->put_Series(var);

		pToolList->GetItems(nDatumLineIdx)->GetasTeeCursor()->GetPen()->put_Color(clrLineColor);
		pToolList->GetItems(nDatumLineIdx)->GetasTeeCursor()->GetPen()->put_Width(1);

		if(blnHorzDatumLine && !blnVertDatumLine) 
			pToolList->GetItems(nDatumLineIdx)->GetasTeeCursor()->put_Style(cssHorizontal);
		if(blnVertDatumLine && !blnHorzDatumLine)
			pToolList->GetItems(nDatumLineIdx)->GetasTeeCursor()->put_Style(cssVertical);
		if(blnHorzDatumLine && blnVertDatumLine)
			pToolList->GetItems(nDatumLineIdx)->GetasTeeCursor()->put_Style(cssBoth);
		pToolList->GetItems(nDatumLineIdx)->GetasTeeCursor()->XVal+=0.2;//dblXVal;//pToolList->GetItems(nDatumLineIdx)->GetasTeeCursor()->XVal+dblXVal;

		objDatumLine.lngDatumLineToolType = pToolList->GetItems(nDatumLineIdx)->GetToolType();

		long lngX = pSeries->CalcXPosValue(dblYVal);//GetXValues()->GetMaximum();//CalcXPosValue(dblXVal);  // Left position of Text display Tool
		long lngY = pSeries->CalcYPosValue(dblXVal);//GetYValues()->GetMaximum();//CalcYPosValue(dblYVal);	// Top Position of Text Display Tool

		//TChart1.Tools.Items(0).asTeeCursor.XVal

		//////// To Draw the Fixed datum Line
		//double dblMaxY,dblMaxX;
		//double dblMinY,dblMinX;
		//long lngFixedDatumLineIdx,lngFixedDatumLine2Idx;
		//lngFixedDatumLineIdx=m_chart.AddSeries(0);  // To draw the Fixed Datum Line 

		//pDisp	=	m_chart.Series(lngFixedDatumLineIdx);
		//ISeriesPtr pFxdDatumSeries1,pFxdDatumSeries2;
		//pFxdDatumSeries1	=	pDisp;
		//pDisp->Release();

		//pFxdDatumSeries1->put_ShowInLegend(FALSE); // Not display this Name in Legends
		//pFxdDatumSeries1->put_Color(clrLineColor);
		//pFxdDatumSeries1->GetPen()->Style=psDash;
		//pFxdDatumSeries1->GetPen()->put_Width(2);
		//if(blnVertDatumLine && !blnHorzDatumLine)
		//{		
		//	dblMaxY = pSeries->GetYValues()->GetMaximum();
		//	dblMinY = pSeries->GetYValues()->GetMinimum();

		//	pFxdDatumSeries1->AddXY(dblXVal,dblMinY,_T(""),123);
		//	pFxdDatumSeries1->AddXY(dblXVal,dblMaxY,_T(""),123);
		//}
		//if(blnHorzDatumLine && !blnVertDatumLine)
		//{
		//	dblMaxX = pSeries->GetXValues()->GetMaximum();
		//	dblMinX = pSeries->GetXValues()->GetMinimum();

		//	pFxdDatumSeries1->AddXY(dblMinX,dblYVal,_T(""),123);
		//	pFxdDatumSeries1->AddXY(dblMaxX,dblYVal,_T(""),123);
		//}
		//if(blnHorzDatumLine && blnVertDatumLine)
		//{
		//	lngFixedDatumLine2Idx=m_chart.AddSeries(0);  // To draw the Fixed Datum Line 
		//	pDisp	=	m_chart.Series(lngFixedDatumLine2Idx);
		//	pFxdDatumSeries2	=	pDisp;
		//	pDisp->Release();
		//	pFxdDatumSeries2->put_ShowInLegend(FALSE); // Not to display this name in legends
		//	pFxdDatumSeries2->put_Color(clrLineColor);
		//	pFxdDatumSeries2->GetPen()->Style=psDash;
		//	pFxdDatumSeries2->GetPen()->put_Width(2);

		//	dblMaxY = pSeries->GetYValues()->GetMaximum();
		//	dblMinY = pSeries->GetYValues()->GetMinimum();

		//	dblMaxX = pSeries->GetXValues()->GetMaximum();
		//	dblMinX = pSeries->GetXValues()->GetMinimum();

		//	pFxdDatumSeries1->AddXY(dblMinX,dblYVal,_T(""),123); // Horiz Fixed cursor
		//	pFxdDatumSeries1->AddXY(dblMaxX,dblYVal,_T(""),123);

		//	pFxdDatumSeries2->AddXY(dblXVal,dblMinY,_T(""),123); // Vert Fixed cursor
		//	pFxdDatumSeries2->AddXY(dblXVal,dblMaxY,_T(""),123);


		//}

		// To display the Corresponding Text of the Datum line Position
		long lngTextDisplayIdx = pToolList->Add(tcAnnotate);
		pToolList->GetItems(lngTextDisplayIdx)->GetasAnnotation()->put_AutoSize(TRUE);


		//pToolList->GetItems(lngTextDisplayIdx)->GetasAnnotation()->put_Left(lngX);
		//pToolList->GetItems(lngTextDisplayIdx)->GetasAnnotation()->put_Top(lngY);
		pToolList->GetItems(lngTextDisplayIdx)->GetasAnnotation()->Position=ppLeftTop;

		objDatumLine.lngTextDisplayToolType = pToolList->GetItems(lngTextDisplayIdx)->GetToolType();

		CString strDatumText;
		if(blnHorzDatumLine && blnVertDatumLine)
		{
			strDatumText.Format(_T("Ref X=%lf Ref Y=%lf"),dblXVal,dblYVal);
		}
		else if(!blnHorzDatumLine && blnVertDatumLine)
		{
			strDatumText.Format(_T("Ref X=%lf"),dblXVal);

		}
		else if(blnHorzDatumLine && !blnVertDatumLine)
		{
			strDatumText.Format(_T("Ref Y=%lf"),dblYVal);
		}

		_bstr_t bstrDatumTxt(strDatumText);
		pToolList->GetItems(lngTextDisplayIdx)->GetasAnnotation()->put_Text(bstrDatumTxt.copy());
		//	SysFreeString(bstrDatumTxt);
		//fncDisplayDatumLineText(nDatumLineIdx,dblXVal,dblYVal,lngGraphIdx);



		/*	if(objDatumLine.bstrFixedDatumLineName.GetSize()>1)  // If Previous Datum line is Both Horz& Vertical 
		{													 // Remove data about second fixed datum line otherwise it is not necessary.
		bstrFixedDatumLine = (objDatumLine.bstrFixedDatumLineName.GetAt(0).copy());
		lIdx=GetGraphIdxFromName(bstrFixedDatumLine);
		if(lIdx>=0)
		{
		SysFreeString(objDatumLine.bstrFixedDatumLineName.GetAt(1));
		m_chart.RemoveSeries(lIdx);
		}
		}*/


		/*objDatumLine.bstrFixedDatumLineName[0] = pFxdDatumSeries1->GetName().copy();
		if(blnVertDatumLine && blnHorzDatumLine)
		objDatumLine.bstrFixedDatumLineName[1] = pFxdDatumSeries2->GetName().copy();*/

		m_objDatumLineInfo.Add(objDatumLine);

		pToolList	=	NULL;
		//pFxdDatumSeries1	=	NULL;
		//pFxdDatumSeries2	=	NULL;
		pSeries	=	NULL;

	}
}
//*************************************************
//PURPOSE : Function to display the values corresponding to the Datum Line
//INPUTS  : LONG lngGraphIdx	--	Graph ID
//			DOUBLE dblXVal		--	X coord value where to start the Datum Line.
//			DOUBLE dblYVal		--	Y   "	  "		"	"	"	  "		"	"
//			int nDatumLineIdx	--  Index of the tool used for the Datum Line
//ASSUMES : 
//RETURNS : 
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------

void CEsdAdvancedGraphCtrl::fncDisplayDatumLineText(int nDatumLineIdx,double dblXVal,double dblYVal,long lngGraphIdx)
{

	EsdDATUMLINEINFO_STRUCT objDatumLine;
	long lngTextToolIdx=-1;
	LPDISPATCH pDisp	=	m_chart.get_Tools();
	IToolListPtr pToolList	=	pDisp;
	pDisp->Release();

	if(m_objDatumLineInfo.GetSize()>0) 
	{
		objDatumLine=m_objDatumLineInfo.GetAt(0);
		int nToolCnt = pToolList->GetCount();
		for(int i=0;i<nToolCnt;i++)
		{
			long lngToolType = pToolList->GetItems(i)->GetToolType();
			if(lngToolType==objDatumLine.lngTextDisplayToolType)
				lngTextToolIdx=i;
		}

		if(lngTextToolIdx>=0)
		{
			CString strHorzDatumText,strVertDatumText;
			double dblResult;

			if(blnHorzDatumLine && blnVertDatumLine)
			{
				dblResult	=	objDatumLine.dblXVal	-	dblXVal;
				strHorzDatumText.Format(_T("Wd=%lf :: X=%lf"),dblResult,dblXVal);
				dblResult	=	objDatumLine.dblYVal	-	dblYVal;
				strVertDatumText.Format(_T("Ht=%lf :: Y=%lf"),dblResult,dblYVal);
				CString strResult;
				strResult	=	strHorzDatumText	+	strVertDatumText;
				_bstr_t bstrDatumText(strResult);
				pToolList->GetItems(lngTextToolIdx)->GetasAnnotation()->put_Text(bstrDatumText);

			}
			if(blnHorzDatumLine)
			{
				dblResult	=	objDatumLine.dblYVal - dblYVal;
				strHorzDatumText.Format(_T("Height = %.4lf :: Y = %.4lf"),/*abs*/(dblResult),dblYVal);
				_bstr_t bstrDatumTxt(strHorzDatumText);
				pToolList->GetItems(lngTextToolIdx)->GetasAnnotation()->put_Text(bstrDatumTxt);

			}
			if(blnVertDatumLine)
			{
				dblResult	=	objDatumLine.dblXVal  -  dblXVal;
				strVertDatumText.Format(_T("X=%.4lf"),/*abs*/dblXVal);

				_bstr_t bstrDatumTxt(strVertDatumText);
				pToolList->GetItems(lngTextToolIdx)->GetasAnnotation()->put_Text(bstrDatumTxt);
			}
		}
	}

	pToolList	=	NULL;
}
//*************************************************
//PURPOSE : Property to get the direction of Zoom
//INPUTS  : 
//ASSUMES : 
//RETURNS : LONG	---   Zoom Direction value (Default is '2'(Both directions)
//			if  '0'	---	  Zoom is only in Horizontal direction
//			if	'1'	---	  Zoom is only in Vertical Direction
//			if	'2'	---	  Zoom is in Both Horizontal and vertical direction
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
LONG CEsdAdvancedGraphCtrl::GetZoomDirection(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	LONG lngZoomDirection;
	LPDISPATCH pDisp	=	m_chart.get_Zoom();
	IZoomPtr pZoom	=	pDisp;
	pDisp->Release();
	lngZoomDirection = pZoom->GetDirection();
	pZoom	=	NULL;

	return lngZoomDirection;
}
//*************************************************
//PURPOSE : Property to set the Direction of Zoom
//INPUTS  : LONg newVal		---		Zoom Direction
//			newVal	=	0	---		Zoom is only in Horizontal direction
//			newVal	=	1	---		Zoom is only in Vertical Direction
//			newVal	=	2	---		Zoom is in Both Horizontal and vertical direction
//ASSUMES :							
//RETURNS :							
//EFFECTS : -						
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::SetZoomDirection(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here

	if(newVal<0 || newVal>2)
	{
		MessageBox(_T("Zooming Direction value must be between 0-2"));
		return;
	}
	else
	{
		LPDISPATCH pDisp	=	m_chart.get_Zoom();
		IZoomPtr pZoom	=	pDisp;
		pDisp->Release();
		switch(newVal)
		{
		case 0:
			pZoom->Direction=tzdHorizontal;
			break;
		case 1:
			pZoom->Direction=tzdVertical;
			break;
		case 2:
			pZoom->Direction=tzdBoth;
			break;
		}
		pZoom	=	NULL;
	}

	SetModifiedFlag();
}


//*************************************************
//PURPOSE : Property to get the status(Enable/Disable) of Zoom 
//INPUTS  : 
//ASSUMES :							
//RETURNS :	VARIANT_BOOL		//if 'VARIANT_TRUE'	zooming is enabled
// if 'VARIANT_FALSE'	Zooming is disabled
//EFFECTS : -						
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
VARIANT_BOOL CEsdAdvancedGraphCtrl::GetEnableZoom(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	VARIANT_BOOL varBlnIsZoomEnable;
	LPDISPATCH pDisp	=	m_chart.get_Zoom();
	IZoomPtr pZoom	=	pDisp;
	pDisp->Release();
	varBlnIsZoomEnable	=	pZoom->GetEnable();
	pZoom	=	NULL;

	return varBlnIsZoomEnable;
}
//*************************************************
//PURPOSE : Property to enable/Disable Zoom
//INPUTS  : VARIANT_BOOL  newVal	---		Zoom state
//ASSUMES :							
//RETURNS :							
//EFFECTS : -						
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::SetEnableZoom(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	LPDISPATCH pDisp	=	m_chart.get_Zoom();
	IZoomPtr pZoom	=	pDisp;
	pDisp->Release();
	pZoom->PutEnable(newVal);
	pZoom	=	NULL;

	SetModifiedFlag();
}
//*************************************************
//PURPOSE : Property to get the mouse button(Left/Right) used for the Zoom
//INPUTS  : 
//ASSUMES :							
//RETURNS :	LONG	// if	'1'	Left mouse button
//					// if	'2' Right Mouse button
//EFFECTS : -						
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
LONG CEsdAdvancedGraphCtrl::GetMouseButtonForZoom(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	LONG lngMouseButton;
	LPDISPATCH pDisp	=	m_chart.get_Zoom();
	IZoomPtr pZoom	=	pDisp;
	pDisp->Release();
	lngMouseButton = pZoom->GetMouseButton();
	pZoom	=	NULL;

	return lngMouseButton;
}
//*************************************************
//PURPOSE : Property to Set the Mouse button with which Zoom 
//			operation has to be done (Default is 'Left Button' for Zoom)
//INPUTS  : LONG neVal	---	Button Value 
//			newVal	=	1	---	Left button will set for Zoom operation
//			newVal	=	2	---	Right button will set for Zoom operation
//ASSUMES :							
//RETURNS :							
//EFFECTS : -						
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::SetMouseButtonForZoom(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	if(newVal<1 ||newVal>2)
	{
		MessageBox(_T("Mouse button value is either '0' or '1'"));
		return;
	}
	else
	{
		LPDISPATCH pDisp	=	m_chart.get_Zoom();
		IZoomPtr pZoom	=	pDisp;
		pDisp->Release();
		switch(newVal)
		{
		case 1: 
			pZoom->PutMouseButton(mbLeft);
			break;
		case 2: 
			pZoom->PutMouseButton(mbRight);
			break;
		}
		pZoom	=	NULL;
	}

	SetModifiedFlag();
}

//*************************************************
//PURPOSE : Property to get the Minimum No.of pixels, at which Zoom will happen 
//INPUTS  : 
//ASSUMES :							
//RETURNS :	LONG	;	Mimimum Number of pixels						
//EFFECTS : -						
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------

LONG CEsdAdvancedGraphCtrl::GetMinimumPixelsForZoom(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	LONG lngMinimumPixels;
	LPDISPATCH pDisp	=	m_chart.get_Zoom();
	IZoomPtr pZoom	=	pDisp;
	pDisp->Release();
	lngMinimumPixels = pZoom->GetMinimumPixels();
	pZoom	=	NULL;

	return lngMinimumPixels;
}
//*************************************************
//PURPOSE : Property to Set the minimum number of onscreen pixels traversed by the
//			mouse drag for the zoom action to actuate.(Default Minimum No. is '15')
//INPUTS  : LONG neVal	---	Number of pixels
//ASSUMES :							
//RETURNS :							
//EFFECTS : -						
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------

void CEsdAdvancedGraphCtrl::SetMinimumPixelsForZoom(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	if(newVal<1)
	{
		MessageBox(_T("Minimum pixels must be greater than zero"));
		return;
	}
	LPDISPATCH pDisp	=	m_chart.get_Zoom();
	IZoomPtr pZoom	=	pDisp;
	pDisp->Release();
	pZoom->PutMinimumPixels(newVal);
	pZoom	=	NULL;

	SetModifiedFlag();
}

//*************************************************
//PURPOSE : Property to get the Scrolling direction of the chart
//INPUTS  : 
//ASSUMES :							
//RETURNS :	LONG	: Scrolling direction
//			if '0'		---		Scrolling is Enabled both in horizontal&Vertical direction
//			if '1'		---			"	   "	"	 only in Horizontal direction
//			if '2'		---			"	   "	"	  "	  "	 vertical		"
//			if '3'		---		Scrolling is disabled in Both the directions
//EFFECTS : -						
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------


LONG CEsdAdvancedGraphCtrl::GetScrollDirection(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	LONG lngScrollDirection;
	LPDISPATCH pDisp	=	m_chart.get_Scroll();
	IScrollPtr pScroll	=	pDisp;
	pDisp->Release();
	lngScrollDirection = pScroll->GetEnable();
	pScroll	=	NULL;

	return lngScrollDirection;
}
//*************************************************
//PURPOSE : Property to Set the Direction or state of scrolling 
//			(Default is Enabled in Both Horizontal& vertical direction(i.e '3')
//INPUTS  :	LONG newVal 	---		Scroll Direction
//			newVal	= 0		---		Scrolling Enabled both in horizontal&Vertical direction
//			newVal	= 1		---			"	  	"	 only in Horizontal direction
//			newVal	= 2		---			"	  	"	  "	  "	 vertical		"
//			newVal	= 3		---		Scrolling disabled in Both the directions
//ASSUMES :							
//RETURNS :							
//EFFECTS : -						
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------


void CEsdAdvancedGraphCtrl::SetScrollDirection(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// TODO: Add your property handler code here

	if(newVal<0 || newVal>3)
	{
		MessageBox(_T("Scrooling Direction value is between 0-3"));
		return;
	}
	else
	{
		LPDISPATCH pDisp	=	m_chart.get_Scroll();
		IScrollPtr pScroll	=	pDisp;
		pDisp->Release();
		switch(newVal)
		{
		case 0:
			pScroll->PutEnable(pmBoth);
			break;

		case 1:
			pScroll->PutEnable(pmHorizontal);
			break;

		case 2:
			pScroll->PutEnable(pmVertical);
			break;

		case 3:
			pScroll->PutEnable(pmNone);
			break;
		}
		pScroll = NULL;
	}

	SetModifiedFlag();
}

//*************************************************
//PURPOSE : Property to get the mouse button(Left/Right) used for the Scroll
//INPUTS  : 
//ASSUMES :							
//RETURNS :	LONG	// if	'1'	Left mouse button
//					// if	'2' Right Mouse button
//EFFECTS : -						
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
LONG CEsdAdvancedGraphCtrl::GetMouseButtonForScroll(void)
{

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	LONG lngMouseButton;
	LPDISPATCH pDisp	=	m_chart.get_Scroll();
	IScrollPtr pScroll	=	pDisp;
	pDisp->Release();
	lngMouseButton=pScroll->GetMouseButton();

	pScroll = NULL;

	return lngMouseButton;
	return 0;
}
//*************************************************
//PURPOSE : Property to Set the Mouse button with which Scroll 
//			operation has to be actuated (Default is 'right Button' for Scroll)
//INPUTS  : LONG neVal	---	Button Value 
//			newVal	=	1	---	Left button will set for Scroll operation
//			newVal	=	2	---	Right button will set for Scroll operation
//ASSUMES :							
//RETURNS :							
//EFFECTS : -						
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::SetMouseButtonForScroll(LONG newVal)
{

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here


	if(newVal<1 ||newVal>2)
	{
		MessageBox(_T("Mouse button value is either '0' or '1'"));
		return;
	}
	else
	{
		LPDISPATCH pDisp	=	m_chart.get_Scroll();
		IScrollPtr pScroll	=	pDisp;
		pDisp->Release();
		switch(newVal)
		{
		case 1: 
			pScroll->PutMouseButton(mbLeft);
			break;
		case 2: 
			pScroll->PutMouseButton(mbRight);
			break;
		}
		pScroll	=	NULL;
	}

	SetModifiedFlag();
}

//*************************************************
//PURPOSE : Method to determine the peak values for the given array of Y values.
//INPUTS  : VARIANT varDblYVals			-	Y values.	
//			LONG lngDataPointsCount		-	Number of Y values.	
//			LONG lngPeakLevel			-	Peak Level
//			VARIANT *varLngPeakIndexes	-	Array which holds the peak indexes.
//ASSUMES : -
//RETURNS : LONG						-	Number of peaks found in the given array of Y values.	
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//----------------------------------------------
LONG CEsdAdvancedGraphCtrl::FindPeaks(VARIANT &varDblYvals, LONG lngDataPointsCount, LONG lngPeakLevel, VARIANT* varLngPeakIndexes)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	if(lngDataPointsCount > 2)
	{
		double	dblMinY;
		double	dblMaxY;
		double	dblOffset;
		double	dblBase;

		long	lngIndex = 0;

		int		i = 0;

		double *dblYArray=new double[lngDataPointsCount];
		long *lngPeakIndexes=new long[lngDataPointsCount];
		// To Get Double values from the VARIANT
		fncGetDoubleValuesFromSafeArray(varDblYvals,dblYArray);

		dblMinY		=	dblYArray[0];
		dblMaxY		=	dblYArray[0];

		for(int intIndex = 0; intIndex < lngDataPointsCount; intIndex++)
		{
			if(dblMinY > dblYArray[intIndex])
				dblMinY	=	dblYArray[intIndex];
			if(dblMaxY < dblYArray[intIndex])
				dblMaxY = dblYArray[intIndex];
		}

		dblOffset	=	(dblMaxY - dblMinY) * lngPeakLevel * 0.05;

		dblBase		=	dblYArray[0];

		while(i<lngDataPointsCount)
		{
			if(dblYArray[i] < dblBase)			// This is for down the slope
				dblBase = dblYArray[i];

			if((dblYArray[i] - dblBase) > dblOffset)
			{
				lngPeakIndexes[lngIndex] = i;

				while(((dblYArray[lngPeakIndexes[lngIndex]] - dblYArray[i]) < dblOffset)
					&& (i < lngDataPointsCount-2))
				{					
					i++;
					if((dblYArray[i]) > dblYArray[lngPeakIndexes[lngIndex]])
						lngPeakIndexes[lngIndex] = i;
				}

				dblBase	= dblYArray[i];

				lngIndex++;
			}

			i++;
		}

		// Sorting the Peak values in Descending Order.

		for(i=0;i<lngIndex;i++)	
			for(int j=i+1;j<lngIndex;j++)
			{
				if(dblYArray[lngPeakIndexes[i]] < dblYArray[lngPeakIndexes[j]])
				{
					lngPeakIndexes[i]+= lngPeakIndexes[j];
					lngPeakIndexes[j] = lngPeakIndexes[i] - lngPeakIndexes[j];
					lngPeakIndexes[i] = lngPeakIndexes[i] - lngPeakIndexes[j];
				}
			}	

			SAFEARRAYBOUND sab[]={lngIndex};
			SAFEARRAY *pSa=SafeArrayCreate(VT_I4,1,sab);
			for(long i=0;i<lngIndex;i++)
			{
				SafeArrayPutElement(pSa,&i,&lngPeakIndexes[i]);
			}

			varLngPeakIndexes->parray=pSa;

			delete []dblYArray;
			delete []lngPeakIndexes;

			return lngIndex;
	}
	else
	{
		MessageBox(_T("Minimum 3 data points must be present to determine the peaks."));
		return 0;

	}

	return 0;
}
//*************************************************
//PURPOSE : Property to return the Axis Titles color 
//INPUTS  : LONG lngAxis	-	Axis whose title color has to be returned
//				 lngAxis	=	1	-	Left Axis(Y-Axis)
//				 lngAxis	=	2	-	Bottom Axis(X-Axis)
//ASSUMES : -
//RETURNS : OLE_COLOR 	-	Titles Color
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//----------------------------------------------
OLE_COLOR CEsdAdvancedGraphCtrl::GetAxesTitlesColor(LONG lngAxis)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	if(lngAxis<1 || lngAxis>2)
	{
		MessageBox(_T("Axis value between 1-2"));
		return NULL;
	}
	OLE_COLOR clrTitleColor;
	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes	=	pDisp;
	pDisp->Release();
	switch(lngAxis)
	{

	case 1:
		clrTitleColor = pAxes->GetLeft()->GetTitle()->GetFont()->Color;
		break;
	case 2:
		clrTitleColor = pAxes->GetBottom()->GetTitle()->GetFont()->Color;
		break;
	}
	pAxes	=	NULL;

	return clrTitleColor;
}


//*************************************************
//PURPOSE : Property to Set the new Titles Color for the Axis
//INPUTS  : LONG lngAxis	-	Axis Whose Titles color has to return
//				 lngAxis	=	1	-	Left Axis(Y-Axis)
//				 lngAxis	=	2	-	Bottom Axis(X-Axis)
//			OLE_COLOR newVal	-	New Titles Color.
//ASSUMES : -
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//----------------------------------------------
void CEsdAdvancedGraphCtrl::SetAxesTitlesColor(LONG lngAxis, OLE_COLOR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	if(lngAxis<1 || lngAxis>2)
	{
		MessageBox(_T("Axis value between 1-2")); 
		return ;
	}
	//COLORREF clrTitles;
	OleTranslateColor(newVal,NULL,&m_clrTitlesColor);

	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes	=	pDisp;
	pDisp->Release();
	switch(lngAxis)
	{
	case 1:
		pAxes->GetLeft()->GetTitle()->GetFont()->Color=m_clrTitlesColor;
		break;
	case 2:
		pAxes->GetBottom()->GetTitle()->GetFont()->Color=m_clrTitlesColor;
		break;
	}
	pAxes	=	NULL;

	SetModifiedFlag();
}
//*************************************************
//PURPOSE : To return the boolean value which indicates whether Graph Header is shown / hidden. 
//INPUTS  : -
//ASSUMES : -
//RETURNS : VARIANT_BOOL  - Boolean value.
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
VARIANT_BOOL CEsdAdvancedGraphCtrl::GetShowHeader(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	LPDISPATCH pDisp	=	m_chart.get_Header();
	ITitlesPtr pTitles	=	pDisp;
	pDisp->Release();
	VARIANT_BOOL varBlnStatus = pTitles->Visible;
	pTitles = NULL;

	return varBlnStatus;
}
//*************************************************
//PURPOSE : To set whether Graph Header to be displayed or not. 
//INPUTS  : VARIANT_BOOL newVal -	Boolean value.
//ASSUMES : -
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::ShowHeader(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here

	LPDISPATCH pDisp	=	m_chart.get_Header();
	ITitlesPtr pTitle	=	pDisp;
	pDisp->Release();
	pTitle->Visible=newVal;
	pTitle	=	NULL;

	SetModifiedFlag();
}

//*************************************************
//PURPOSE : To return the Graph Header. 
//INPUTS  : -
//ASSUMES : -
//RETURNS : BSTR  - Header which has to be returned.
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
BSTR CEsdAdvancedGraphCtrl::GetHeader(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	//CString strResult;

	// TODO: Add your dispatch handler code here

	LPDISPATCH pDisp	=	m_chart.get_Header();
	ITitlesPtr pTitles	=	pDisp;
	pDisp->Release();
	_bstr_t bstrHeader = pTitles->Caption.copy();
	pTitles	=	NULL;

	return bstrHeader;
}

//*************************************************
//PURPOSE : To set the Graph Header. 
//INPUTS  : LPCTSTR newVal - Graph Header.
//ASSUMES : -
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    :
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::SetHeader(LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	//CString strHeader=newVal;
	_bstr_t bstrHeader(newVal);
	LPDISPATCH pDisp	=	m_chart.get_Header();
	ITitlesPtr pTitles	=	pDisp;
	pDisp->Release();
	pTitles->Caption=bstrHeader.copy();
	pTitles	=	NULL;

	//	SysFreeString(bstrHeader);
	SetModifiedFlag();
}
//*************************************************
//PURPOSE : To return the current grid color value of the specified Axis
//INPUTS  : LONG lngAxis	-	Axis whose title color has to be returned
//				 lngAxis	=	1	-	Left Axis(Y-Axis)
//				 lngAxis	=	2	-	Bottom Axis(X-Axis)
//ASSUMES : -
//RETURNS : OLE_COLOR *pVal -  Current grid color.
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------

OLE_COLOR CEsdAdvancedGraphCtrl::GetAxisGridColor(LONG lngAxis)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	if(lngAxis<1 || lngAxis>2)
	{
		MessageBox(_T("Axis value between 1-2"));
		return 0;
	}
	OLE_COLOR clrGridColor;

	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes	=	pDisp;
	pDisp->Release();
	switch(lngAxis)
	{
	case 1:
		clrGridColor = pAxes->GetLeft()->GetGridPen()->Color;
		break;
	case 2:
		clrGridColor = pAxes->GetBottom()->GetGridPen()->Color;
		break;
	}
	pAxes	=	NULL;


	return clrGridColor;
}

//*************************************************
//PURPOSE : To set the grid color of an axis.
//INPUTS  : LONG lngAxis	-	Axis whose grid color has to be changed
//				 lngAxis	=	1	-	Left Axis(Y-Axis)
//				 lngAxis	=	2	-	Bottom Axis(X-Axis)
//			OLE_COLOR newVal - New grid color
//ASSUMES : -
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::SetAxisGridColor(LONG lngAxis,OLE_COLOR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	if(lngAxis<1 || lngAxis>2)
	{
		MessageBox(_T("Axis value between 1-2"));
		return;
	}
	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes	=	pDisp;
	pDisp->Release();
	switch(lngAxis)
	{
	case 1:
		pAxes->GetLeft()->GetGridPen()->Color=newVal;
		break;
	case 2:
		pAxes->GetBottom()->GetGridPen()->Color=newVal;
		break;
	}
	pAxes	=	NULL;

	SetModifiedFlag();
}

//*************************************************
//PURPOSE : To return the Specified Axis precision value.
//INPUTS  : LONG lngAxis	-	Axis whose precision has to be returned
//				 lngAxis	=	1	-	Left Axis(Y-Axis)
//				 lngAxis	=	2	-	Bottom Axis(X-Axis)
//ASSUMES : -
//RETURNS : SHORT -  Axis precision
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
SHORT CEsdAdvancedGraphCtrl::GetAxesMarkingPrecision(LONG lngAxis)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	if(lngAxis<1 || lngAxis>2)
	{
		MessageBox(_T("Axis value between 1-2"));
		return -1;
	}
	_bstr_t bstrFormat	=	_T("");
	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes	=	pDisp;
	pDisp->Release();
	switch(lngAxis)
	{
	case 1:
		bstrFormat	=	pAxes->GetLeft()->GetLabels()->ValueFormat;
		break;
	case 2:
		bstrFormat	=	pAxes->GetBottom()->GetLabels()->ValueFormat;
		break;
	default:
		break;
	}
	pAxes	=	NULL;

	CString strPrecision	=	/*(wchar_t*)*/bstrFormat;
	int nPosition=strPrecision.Find(_T("."));

	SHORT nLength	=	strPrecision.GetLength()-(nPosition+1);
	if(strPrecision.GetLength()==1 && nPosition==-1)
		nLength	=	0;

	return nLength;
}

//*************************************************
//PURPOSE : To set the Specified Axis precision value.
//INPUTS  : LONG lngAxis	-	Axis whose precision has to be Set
//				 lngAxis	=	1	-	Left Axis(Y-Axis)
//				 lngAxis	=	2	-	Bottom Axis(X-Axis)
//			SHORT newVal	 -	New precision value.
//ASSUMES : -
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::SetAxesMarkingPrecision(LONG lngAxis, SHORT newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	if(lngAxis<1 || lngAxis>2 )
	{
		MessageBox(_T("Axis value between 1-2"));
		return;
	}
	if(newVal<0)
	{
		MessageBox(_T("Precision value must be Greter than Zero"));
		return;
	}
	CString strForamt;//=_T("0");
	/*	for(SHORT i=0;i<=newVal;i++)
	{
	if(i==1)
	strForamt+=_T(".");
	strForamt+='0';
	}*/
	double intZero	=	0.0;
	strForamt.Format(_T("%.*lf"),newVal,intZero); // bcz precision must be send in "#.###..." format


	_bstr_t bstrFormat(strForamt);  
	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes	=	pDisp;
	pDisp->Release();
	switch(lngAxis)
	{
	case 1:
		pAxes->GetLeft()->GetLabels()->ValueFormat=bstrFormat;
		m_intYPrecision	=	newVal;
		break;
	case 2:
		pAxes->GetBottom()->GetLabels()->ValueFormat=bstrFormat;
		m_intXPrecision	=	newVal;
		break;
	default:
		break;
	}
	pAxes	=	NULL;
	//	SysFreeString(bstrFormat);


	SetModifiedFlag();
}

//*************************************************
//PURPOSE : To return the current Title of the specified Axis.
//INPUTS  : LONG lngAxis	-	Axis Whose title has to be returned
//				 lngAxis	=	1	-	Left Axis(Y-Axis)
//				 lngAxis	=	2	-	Bottom Axis(X-Axis)
//ASSUMES : -
//RETURNS : BSTR	  -		Axis Title.
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
BSTR CEsdAdvancedGraphCtrl::GetAxestitle(LONG lngAxis)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	//	CString strResult;

	// TODO: Add your dispatch handler code here

	if(lngAxis<1 || lngAxis>2)
	{
		MessageBox(_T("Axis value between 1-2"));
		return NULL;
	}
	_bstr_t bstrTitle	=	_T("");
	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes	=	pDisp;
	pDisp->Release();
	switch(lngAxis)
	{
	case 1:
		bstrTitle = pAxes->GetLeft()->GetTitle()->Caption.copy();
		break;
	case 2:
		bstrTitle = pAxes->GetBottom()->GetTitle()->Caption.copy();
		break;
	}
	pAxes	=	NULL;

	return bstrTitle;
}

//*************************************************
//PURPOSE : To set the specified Axis Title.
//INPUTS  : LONG lngAxis	-	Axis whose Title has to be Set
//				 lngAxis	=	1	-	Left Axis(Y-Axis)
//				 lngAxis	=	2	-	Bottom Axis(X-Axis)
//			BSTR newVal  - New  title.
//ASSUMES : -
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::SetAxestitle(LONG lngAxis, LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here

	if(lngAxis<1 || lngAxis>2)
	{
		MessageBox(_T("Axis value between 1-2"));
		return;
	}
	_bstr_t bstrTitle(newVal);
	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes	=	pDisp;
	pDisp->Release();
	switch(lngAxis)
	{
	case 1:
		m_strYAxisTitle	=	newVal;	//Store the Axis Title
		pAxes->GetLeft()->GetTitle()->Caption	=	bstrTitle;
		break;
	case 2:
		m_strXAxisTitle	=	newVal;	// Store the Axis Title
		pAxes->GetBottom()->GetTitle()->Caption	=	bstrTitle;
		break;
	}
	pAxes	=	NULL;
	//	SysFreeString(bstrTitle);

	SetModifiedFlag();
}
//*************************************************
//PURPOSE : Property to return the Minimum value of the Axis.
//INPUTS  : LONG lngAxis	-	Axis whose Minimum has to be return
//				 lngAxis	=	1	-	Left Axis(Y-Axis)
//				 lngAxis	=	2	-	Bottom Axis(X-Axis)
//ASSUMES : -
//RETURNS : DOUBLE	-	Minimum value
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------

DOUBLE CEsdAdvancedGraphCtrl::GetAxisMinimum(LONG lngAxis)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	DOUBLE dblMinimum	=	0.0;
	if(lngAxis<1 || lngAxis>2)
	{
		MessageBox(_T("Axis value between 1-2"));
		return 0;
	}
	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes	=	pDisp;
	pDisp->Release();
	switch(lngAxis)
	{
	case 1:
		dblMinimum = pAxes->GetLeft()->Minimum;
		break;
	case 2:
		dblMinimum = pAxes->GetBottom()->Minimum;
		break;
	default:
		break;
	}
	pAxes	=	NULL;

	return dblMinimum;
}
//*************************************************
//PURPOSE : Property to set the minimum value for the Axis.
//INPUTS  : LONG lngAxis	-	Axis whose Title has to be Set
//				 lngAxis	=	1	-	Left Axis(Y-Axis)
//				 lngAxis	=	2	-	Bottom Axis(X-Axis)
//			
//ASSUMES : -
//RETURNS : -	DOUBLE newVal			-	Axis minimum value
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::SetAxisMinimum(LONG lngAxis, DOUBLE newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here

	if(lngAxis<1 || lngAxis>2)
	{
		MessageBox(_T("Axis value between 1-2"));
		return;
	}
	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes	=	pDisp;
	pDisp->Release();
	switch(lngAxis)
	{
	case 1:
		pAxes->GetLeft()->AutomaticMinimum=FALSE;

		pAxes->GetLeft()->Minimum=newVal;
		break;
	case 2:
		pAxes->GetBottom()->AutomaticMinimum=FALSE;

		pAxes->GetBottom()->PutMinimum(newVal);
		break;
	default:
		break;
	}
	pAxes	=	NULL;

	SetModifiedFlag();
}

//*************************************************
//PURPOSE : 
//INPUTS  : 
//ASSUMES : -
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
VARIANT_BOOL CEsdAdvancedGraphCtrl::EntireGraph(LONG lngGraphIdx)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	return VARIANT_TRUE;
}
//*************************************************
//PURPOSE : Property to return the Maximum value of the Axis.
//INPUTS  : LONG lngAxis	-	Axis whose Minimum has to be return
//				 lngAxis	=	1	-	Left Axis(Y-Axis)
//				 lngAxis	=	2	-	Bottom Axis(X-Axis)
//			DOUBLE newVal			-	New value.

//ASSUMES : -
//RETURNS : 
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
DOUBLE CEsdAdvancedGraphCtrl::GetAxisMaximum(LONG lngAxis)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// TODO: Add your dispatch handler code here
	DOUBLE dblMaximum	=	0.0;
	if(lngAxis<1 || lngAxis>2)
	{
		MessageBox(_T("Axis value between 1-2"));
		return 0;
	}
	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes	=	pDisp;
	pDisp->Release();
	switch(lngAxis)
	{
	case 1:
		dblMaximum = pAxes->GetLeft()->Maximum;
		break;
	case 2:
		dblMaximum = pAxes->GetBottom()->Maximum;
		break;
	default:
		break;
	}
	pAxes	=	NULL;
	CString str;
	str.Format(_T("%lf"),dblMaximum);
	//AfxMessageBox(str);
	return dblMaximum;
}
//*************************************************
//PURPOSE : Property to set the Maximum value for the Axis.
//INPUTS  : LONG lngAxis	-	Axis whose Minimum has to be return
//				 lngAxis	=	1	-	Left Axis(Y-Axis)
//				 lngAxis	=	2	-	Bottom Axis(X-Axis)
//ASSUMES : -
//RETURNS : DOUBLE	-	Minimum value
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::SetAxisMaximum(LONG lngAxis, DOUBLE newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here

	if(lngAxis<1 || lngAxis>2)
	{
		MessageBox(_T("Axis value between 1-2"));
		return;
	}
	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes	=	pDisp;
	pDisp->Release();
	switch(lngAxis)
	{
	case 1:
		pAxes->GetLeft()->AutomaticMaximum=FALSE;
		pAxes->GetLeft()->Maximum=newVal;
		break;
	case 2:
		pAxes->GetBottom()->AutomaticMaximum=FALSE;
		pAxes->GetBottom()->Maximum=newVal;
		break;
	default:
		break;
	}
	pAxes	=	NULL;

	SetModifiedFlag();
}
//*************************************************
//PURPOSE : To return the current grid style value of the Specifies Axis.
//INPUTS  : LONG lngAxis	-	Axis whose grid style has to be changed.
//				 lngAxis	=	1	-	Left Axis(Y-Axis)
//				 lngAxis	=	2	-	Bottom Axis(X-Axis)
//ASSUMES : -
//RETURNS : SHORT	  -  Grid style value.
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
SHORT CEsdAdvancedGraphCtrl::GetAxisGridStyle(LONG lngAxis)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	if(lngAxis<1 || lngAxis>2)
	{
		MessageBox(_T("Axis value between 1-2"));
		return 0;
	}
	SHORT shStyle;
	EChartPenStyle style;
	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes	=	pDisp;
	pDisp->Release();
	switch(lngAxis)
	{
	case 1:
		style =pAxes->GetLeft()->GetGridPen()->Style;
		break;
	case 2:
		style = pAxes->GetBottom()->GetGridPen()->Style;
		break;
	}
	pAxes	=	NULL;
	if(style==psSolid)
		shStyle=1;
	else if(style==psDot)
		shStyle=2;
	else if(style==psDash)
		shStyle=3;
	else if(style==psDashDot)
		shStyle=4;
	else if(style==psDashDotDot)
		shStyle=5;

	return shStyle;

}
//*************************************************
//PURPOSE : To change the grid style of the specified Axis
//INPUTS  : LONG lngAxis	-	Axis whose Grid Style has to be changed.
//				 lngAxis	=	1	-	Left Axis(Y-Axis)
//				 lngAxis	=	2	-	Bottom Axis(X-Axis)
//			SHORT newVal	-	New grid style value.
//				 newVal		=	1	-	Solid Line
//				 newVal		=	2	-	Dotted Line
//				 newVal		=	3	-	Dashed Line
//				 newVal		=	4	-	Dash Dot Line
//				 newVal		=	5	-	DashDotDot Line
//ASSUMES : -
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::SetAxisGridStyle(LONG lngAxis, SHORT newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	if(lngAxis<1 || lngAxis>2)
	{
		MessageBox(_T("Axis value between 1-2"));
		return;
	}
	if(newVal<1 ||newVal>5)
	{
		MessageBox(_T("Grid style value must be b/n 1-5"));
		return;
	}
	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes	=	pDisp;
	pDisp->Release();
	switch(newVal)
	{
	case 1:
		if(lngAxis==1)
		{
			pAxes->GetLeft()->GetGridPen()->Style=psSolid;
		}
		if(lngAxis==2)
		{
			pAxes->GetBottom()->GetGridPen()->Style=psSolid;
		}
		break;
	case 2:
		if(lngAxis==1)
		{
			pAxes->GetLeft()->GetGridPen()->Style=psDot;
		}
		if(lngAxis==2)
		{
			pAxes->GetBottom()->GetGridPen()->Style=psDot;
		}
		break;
	case 3:
		if(lngAxis==1)
		{
			pAxes->GetLeft()->GetGridPen()->Style=psDash;
		}
		if(lngAxis==2)
		{
			pAxes->GetBottom()->GetGridPen()->Style=psDash;
		}
		break;
	case 4:
		if(lngAxis==1)
		{
			pAxes->GetLeft()->GetGridPen()->Style=psDashDot;
		}
		if(lngAxis==2)
		{
			pAxes->GetBottom()->GetGridPen()->Style=psDashDot;
		}
		break;
	case 5:
		if(lngAxis==1)
		{
			pAxes->GetLeft()->GetGridPen()->Style=psDashDotDot;
		}
		if(lngAxis==2)
		{
			pAxes->GetBottom()->GetGridPen()->Style=psDashDotDot;
		}
		break;
	}
	pAxes	=	NULL;


	SetModifiedFlag();
}

//*************************************************
//PURPOSE : To set enable/Disable state corresponding to the Variables set for the datum line 
//			and to remove the  Info about disabled datum line.
//INPUTS  : -
//ASSUMES : -
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::fncSetStateForDatumLine(void)
{
	LPDISPATCH pDisp	=	m_chart.get_Tools();
	IToolListPtr pToolList	=	pDisp;
	pDisp->Release();
	if(!blnHorzDatumLine && !blnVertDatumLine)// if both Datum line is disabled remove all the information from the 
	{										  // structure and remove these lines from Control 
		if(m_objDatumLineInfo.GetSize()>0)
		{
			EsdDATUMLINEINFO_STRUCT objDatumLine;
			objDatumLine=m_objDatumLineInfo.GetAt(0);

			int nToolCnt = pToolList->GetCount();
			for(int i=0;i<nToolCnt;i++)
			{
				long lngToolType = pToolList->GetItems(i)->GetToolType();
				if(lngToolType==objDatumLine.lngDatumLineToolType)  // remove manual cursor if Exists
					pToolList->Delete(i);
				if(lngToolType==objDatumLine.lngTextDisplayToolType) // Remove tool Used to display text corresponding to the Manual cursor if exists
					pToolList->Delete(i);
			}
			for(int i=0;i<2;i++) // Remove the Graph's added for the Vert & Horz Fixed Datum Lines from Control
			{					 // also remove Info about these lines from the Structure.
				_bstr_t bstrFixedDatumLine=(objDatumLine.bstrFixedDatumLineName[i]).copy();
				long lIdx=GetGraphIdxFromName(bstrFixedDatumLine);
				if(lIdx>=0)
				{
					m_chart.RemoveSeries(lIdx);
					objDatumLine.bstrFixedDatumLineName[i]=_T("");
					//	SysFreeString(objDatumLine.bstrFixedDatumLineName[i]);
				}
				//	SysFreeString(bstrFixedDatumLine);
			}
			m_objDatumLineInfo.RemoveAll();
			m_objDatumLineInfo.FreeExtra();	
			m_chart.RedrawWindow();
		}
	}
	if((blnHorzDatumLine && !blnVertDatumLine)||(!blnHorzDatumLine && blnVertDatumLine))// if any one of the Datum line is disabled remove the information about the disabled datum linefrom the 
	{																	// structure and remove that line from Control 
		if(m_objDatumLineInfo.GetSize()>0)
		{	

			EsdDATUMLINEINFO_STRUCT objDatumLine;
			objDatumLine=m_objDatumLineInfo.GetAt(0);
			int nToolCnt = pToolList->GetCount();
			for(int i=0;i<nToolCnt;i++)
			{
				long lngToolType = pToolList->GetItems(i)->GetToolType();
				if(lngToolType==objDatumLine.lngDatumLineToolType)  // Change the Cursor According to the status Set to the Datum lines
				{
					//pToolList->Delete(i);
					if(blnHorzDatumLine && !blnVertDatumLine)
						pToolList->GetItems(i)->GetasTeeCursor()->PutStyle(cssHorizontal);
					if(!blnHorzDatumLine && blnVertDatumLine)
						pToolList->GetItems(i)->GetasTeeCursor()->PutStyle(cssVertical);
					if(blnHorzDatumLine && blnVertDatumLine)
						pToolList->GetItems(i)->GetasTeeCursor()->PutStyle(cssBoth);
				}
			}
			//	if((blnHorzDatumLine && !blnVertDatumLine)||(!blnHorzDatumLine && blnVertDatumLine)) // Remove the Graph's added for the disabled Fixed Datum Line from Control
			{													 // also remove Info about this disabled line from the Structure.
				_bstr_t bstrFixedDatumLine=(objDatumLine.bstrFixedDatumLineName[1]).copy();
				long lIdx=GetGraphIdxFromName(bstrFixedDatumLine);
				if(lIdx>=0)
				{
					m_chart.RemoveSeries(lIdx);
					objDatumLine.bstrFixedDatumLineName[1]=_T("");
					//SysFreeString(objDatumLine.bstrFixedDatumLineName[1]);
				}
				//SysFreeString(bstrFixedDatumLine);
			}

			m_chart.RedrawWindow();			

		}
	}
	pToolList	=	NULL;

}
//*************************************************
//PURPOSE : To display the Peaks for a specified Graph.
//INPUTS  : LONG intGraphID		-	Graph ID
//			SHORT intPeakLevel	-	Peak Level
//RETURNS : VARIANT_BOOL			-	Boolean value
//ASSUMES : Peaks will be displayed only when Graph(s) is / are displayed by sorting the data points.
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    :
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
VARIANT_BOOL CEsdAdvancedGraphCtrl::ShowPeaks(LONG lngGraphIdx, SHORT intPeakLevel)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	/*	if(m_bSortPoints)						// Check whether Sorting is enabled / not.
	{*/


	stuRemovableGraphData  temp ;	
	if(lngGraphIdx>=0 && lngGraphIdx<m_chart.get_SeriesCount())		// Check for the existence of the Graph.
	{
		LPDISPATCH pDisp	=	m_chart.Series(lngGraphIdx);
		ISeriesPtr	pSeries	=	pDisp;
		pDisp->Release();
		_bstr_t bstrGraphName = pSeries->GetName().copy();
		pSeries	=	NULL;
		long lngIdx=GetLtblIdxFromName(bstrGraphName); // Check weather the Graph ID specified is the Valid user added graph or not
		if(lngIdx<0)
		{
			MessageBox(_T("Graph with specified ID doesn't exists"));//String Table
			return FALSE;
		}

		lngGraphIdx	=	lngIdx;
		if(intPeakLevel>=1 && intPeakLevel<=10)					// Check for the Peak Level.
		{	
			temp = m_arrGraphRelatedSerieses.GetAt(lngGraphIdx);				// Get the address of the Graph.

			if(!temp.bShowPeaks)								// Increment the variable m_intCounterForGraphsPeaks only if temp->bShowPeaks
				m_intCounterForGraphsPeaks++;					// is FALSE. This is done to avoid the incrementation of m_intCounterForGraphsPeaks when this method is again invoked 
			// by the Client without calling the HidePeaks method.
			temp.bShowPeaks	= TRUE;							 
			temp.intPeakLevel	= intPeakLevel;
			m_arrGraphRelatedSerieses.SetAt(lngGraphIdx,temp);

			m_chart.Repaint();									// Call to OnAfterDrawTChart

			//below two fns are called bcz peak info is not displayed immediately(it requires manual redrawing).
			//By calling this it will once again forced to redraw the control and displays the info.Adding custom axis 
			//and immediately removing it will not effect any thing.
			LPDISPATCH pDisp	=	m_chart.get_Axis();
			IAxesPtr pAxes	=	pDisp;
			pDisp->Release();
			long lngAxisIdx	=	pAxes->AddCustom(TRUE);
			pAxes->RemoveCustom(lngAxisIdx);
			pAxes	=	NULL;

			return TRUE;
		}
		else
		{
			MessageBox(_T("Peak Level value must be within 1 to 10."));//String Table
			return FALSE;
		}
	}
	else
	{
		MessageBox(_T("Graph with specified ID doesn't exists"));//String Table
		return FALSE;
	}
}
//*************************************************
//PURPOSE : Method to display the Peaks.
//INPUTS  : -
//ASSUMES : -
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------

void CEsdAdvancedGraphCtrl::prcDisplayPeaks(void)
{
	if(m_chart.get_SeriesCount()<0)// If no graphs are drawn on the chart return from this function
	{
		return;
	}
	//	CString str;
	//	_bstr_t bstrText;
	//	long lngTextHt,lngTextWd;
	//
	//	stuRemovableGraphData temp ;
	//	CRect rect;			// Rectangle to contain the plot area region coordinates
	//	double tempPlot;
	//	IAxesPtr  axes= m_chart.get_Axis();						//Get Axes pointer to access the functions
	//	tempPlot=axes->GetBottom()->GetMinimum();				// Axes Coordinates(in Doubles)
	//	rect.left= axes->GetBottom()->CalcXPosValue(tempPlot); // Convert Axes coords to Screen coords(in Pixels)
	//
	//	tempPlot=axes->GetBottom()->GetMaximum();
	//	rect.right=axes->GetBottom()->CalcXPosValue(tempPlot);
	//
	//	tempPlot=axes->GetLeft()->GetMinimum();
	//	rect.bottom= axes->GetLeft()->CalcYPosValue(tempPlot);
	//
	//	tempPlot=axes->GetLeft()->GetMaximum();
	//	rect.top=axes->GetLeft()->CalcYPosValue(tempPlot);
	//	axes=NULL;
	//
	//	m_arrPeakInfoIndexes.RemoveAll();
	//	m_arrPeakInfoIndexes.FreeExtra();
	//	for(long i=0;i<m_arrGraphRelatedSerieses.GetSize();i++)			
	//	{
	//		temp = m_arrGraphRelatedSerieses.GetAt(i);
	//		if(temp.bShowPeaks)							// Check whether Peaks to be displayed or not.
	//		{
	//			_bstr_t bstrGraphName(temp.bstrGraphName,TRUE);
	//
	//			long lngGraphIdx= GetGraphIdxFromName(bstrGraphName);
	//			if(lngGraphIdx<0)
	//				return;
	//			ISeriesPtr	pSeries= m_chart.Series(lngGraphIdx);			
	//
	//			IAspectPtr	pAspect	=	m_chart.get_Aspect();
	//			if((pSeries->GetXValues()->Count)>2)// To display Peaks, no. of data points must be more than 2.
	//			{
	//				long* lngIndex	=	 new long[pSeries->GetXValues()->Count];
	//				long lngNumOfPeaks	= fncCalculatePeakIndexes(lngGraphIdx,lngIndex);;	// Call to CalculatePeakIndexes function
	//
	//				ICanvasPtr	pCanvas=	m_chart.get_Canvas(); // Get the Canvas pointer
	//
	//				IAspectPtr	pAspect	=	m_chart.get_Aspect(); //
	//				// Select the text color.	
	//				pCanvas->GetPen()->Color = pSeries->GetColor();
	//				for(int i=0;i<lngNumOfPeaks;i++)		// Start marking the peak with a pipe character.
	//				{
	//					double tempX= pSeries->GetXValues()->GetValue(lngIndex[i]);
	//					double tempY= pSeries->GetYValues()->GetValue(lngIndex[i]);
	//					POINT pt;
	//					//if(pAspect->View3D==VARIANT_TRUE)
	//					//{
	//					//	pt.x	= pSeries->CalcXPosValue(tempX)+12/*-pAspect->Width3D*/; 
	//					//	pt.y	= pSeries->CalcYPosValue(tempY)-pAspect->Height3D+8;
	//					//	CString strPer;
	//					//	strPer.Format(_T("X=%ld"),pt.x);
	//					//	AfxMessageBox(strPer);
	//					//}
	//					//else
	//					//{
	//					pt.x	= pSeries->CalcXPosValue(tempX);
	//					pt.y	= pSeries->CalcYPosValue(tempY);
	//					//}
	//
	//
	//					str.Format(_T("%c"),124); // 124= pipe symbol('|')
	//					bstrText= str;
	//
	//					lngTextHt=pCanvas->TextHeight(bstrText);// Get the Height of the character.
	//					lngTextWd=pCanvas->TextWidth(bstrText);// Get the width of the character.
	//
	//					pt.x-= lngTextWd/2;			//	Aligning the pipe operator so that it will displayed
	//					pt.y-= lngTextHt/2;			//	exactly center of the peak data point.
	//
	//					if(pt.x <rect.left)
	//						pt.x= rect.left;
	//					if(pt.x > rect.left && pt.x <rect.right && pt.y > rect.top && pt.y < rect.bottom)
	//					{
	//						if(pAspect->View3D	==	VARIANT_TRUE) // if 3D mode enabled
	//						{
	//							pCanvas->TextOut3D(pt.x,pt.y,pAspect->Chart3DPercent/4,bstrText);// Display the character('|')
	//						}
	//						else if(pAspect->View3D	==	VARIANT_FALSE)
	//						{	
	//				//			pCanvas->TextOut(pt.x,pt.y,bstrText);// Display the character('|')
	//						}
	//					}
	////					bstrText=_T("");
	//
	//					pt.x+= lngTextWd/2;		//	Adjusting the location so that Peak number to be 
	//					pt.y-= lngTextHt/2;		//	displayed at the top of pipe operator.
	//
	//					str.Format(_T("%d"),i+1);
	//					bstrText	=	str;
	//
	//					lngTextHt=pCanvas->TextHeight(bstrText);// Get the Height of the character.
	//					lngTextWd=pCanvas->TextWidth(bstrText);// Get the width of the character.
	//
	//					pt.x-= lngTextWd/2;
	//					pt.y-= lngTextHt/2;
	//					if(pt.x < rect.left)
	//						pt.x = rect.left;
	//					if((pt.x+str.GetLength()) > rect.right)
	//						pt.x-= lngTextWd/2;
	//					if(pt.y > rect.bottom)
	//						pt.y = rect.bottom;
	//
	//					if(pt.x > rect.left && pt.x <rect.right && pt.y > rect.top && pt.y < rect.bottom)
	//					{
	//						if(pAspect->View3D	==	VARIANT_TRUE) // if 3D mode enabled
	//						{
	//							pCanvas->TextOut3D(pt.x,pt.y,pAspect->Chart3DPercent/4,bstrText);// Display the Peak number.
	//						}
	//						else if(pAspect->View3D	==	VARIANT_FALSE)
	//						{	
	//				//			pCanvas->TextOut(pt.x,pt.y,bstrText);// Display the Peak number.
	//						}
	//					}
	////						bstrText=_T("");
	//
	//					if(m_bShowDataAtPeak)
	//					{
	//						pt.x+= lngTextWd/2;			//	Adjusting the location so that Peak data to be 
	//						pt.y-= lngTextHt/2;			//	displayed at the top of peak number.
	//
	//						CString strTemp;
	//						strTemp	=	str;
	//						str.Format(_T("(%.*lf, %.*lf)"), m_intXPrecision, ((ISeries*)m_chart.Series(lngGraphIdx))->GetXValues()->GetValue(lngIndex[i]), m_intYPrecision, ((ISeries*)m_chart.Series(lngGraphIdx))->GetYValues()->GetValue(lngIndex[i]));
	//						str	=	str+_T("\r")+strTemp;
	//						bstrText=str;
	//
	//						lngTextHt=pCanvas->TextHeight(bstrText);// Get the Height of the character.
	//						lngTextWd=pCanvas->TextWidth(bstrText);// Get the width of the character.
	//
	//						pt.x-= lngTextWd/2;
	//						pt.y-= lngTextHt/2;
	//						if(pt.x < rect.left)
	//							pt.x = rect.left;
	//						if(pt.y > rect.bottom)
	//							pt.y = rect.bottom;
	//						if(pt.x+(lngTextWd) > rect.right)
	//							pt.x = pt.x-(lngTextWd/2);
	//
	//						if(pt.x >= rect.left && pt.x <=rect.right && pt.y >= rect.top && pt.y <= rect.bottom)
	//						{
	//							if(pAspect->View3D	==	VARIANT_TRUE) // if 3D mode enabled
	//							{
	//								pCanvas->TextOut3D(pt.x,pt.y,pAspect->Chart3DPercent/4,bstrText);// Display the Peak data
	//							}
	//							else if(pAspect->View3D	==	VARIANT_FALSE)
	//							{	
	//								//	pCanvas->TextOut(pt.x,pt.y,bstrText);// Display the Peak data
	//								
	//
	//							}
	//						}
	//					}			
	//
	//					if(m_bShowConcAtPeak & !m_bPerConc)
	//					{
	//						//		Fire_Clicked(*(temp->dblXval.GetAt(lngIndex[i])),(*temp->dblYval.GetAt(lngIndex[i])));
	//
	//						double PercntConc= m_dblconcentration * (pSeries->GetYValues()->GetValue(lngIndex[i]));//(*(temp->dblYval.GetAt(lngIndex[i])));
	//
	//						CString StrConc,Strname = _T("%Conc :");
	//						pt.x+= lngTextHt/2;//szChar.cx/2;
	//						pt.y-= lngTextWd/2;//szChar.cy/2;
	//
	//						if(m_dblconcentration==0.0)
	//							StrConc.Format(_T("%s #Error"),Strname);
	//						else if(m_bPerConc==TRUE || (m_bShowConcAtPeak))
	//							StrConc.Format(_T("%s %.2f"),Strname,PercntConc);
	//
	//						//	GetTextExtentPoint(di.hdcDraw,StrConc,StrConc.GetLength(),&szChar); //Comented 16/01/08
	//						bstrText=StrConc;
	//
	//						lngTextHt=pCanvas->TextHeight(bstrText);// Get the Height of the character.
	//						lngTextWd=pCanvas->TextWidth(bstrText);// Get the width of the character.
	//
	//						pt.x-= lngTextHt/2;//szChar.cx/2;
	//						pt.y-= lngTextWd/2;//szChar.cy/2;
	//
	//						//TextOut(di.hdcDraw,pt.x ,pt.y ,StrConc,StrConc.GetLength());
	//					}
	//					EsdPeakInfoDisplay_Struct temp;
	//					temp.lngvalueIdx	=	lngIndex[i];
	////					temp.bFlag			=	false;
	//					temp.strPeakInfo	=	bstrText;
	//					m_arrPeakInfoIndexes.Add(temp);	
	//					
	//				}
	//
	//				if(m_bShowDataAtPeak)
	//				{
	//					BSTR bstr;//=bstrText.copy();
	//					OnGetTChartSeriesMarks(lngGraphIdx,0,&bstr);
	//				}
	//					
	//
	//				pCanvas=NULL;
	//				pAspect	=	NULL;
	//				delete [] lngIndex;
	//			}
	//			
	//			pSeries=NULL;
	//		}
	//	}


	CString str	, strTemp;
	_bstr_t bstrText;

	stuRemovableGraphData temp ;
	EsdPeakInfoDisplay_Struct *tempInfo,*checkInfo;
	tempInfo	=	NULL;
	checkInfo	=	NULL;

	int nSize	=(int)	m_arrGraphRelatedSerieses.GetSize();

	for(int i=0;i<nSize;i++)			
	{
		temp = m_arrGraphRelatedSerieses.GetAt(i);
		if(temp.bShowPeaks)							// Check whether Peaks to be displayed or not.
		{
			/*m_arrPeakInfoIndexes.RemoveAll();
			m_arrPeakInfoIndexes.FreeExtra();*/
			_bstr_t bstrGraphName(temp.bstrGraphName,TRUE);

			long lngGraphIdx= GetGraphIdxFromName(bstrGraphName); // Get the ID of the Graph
			if(lngGraphIdx<0) //If graph doesn't exist
				return;

			for(int cnt=0;cnt<m_arrPeakInfoIndexes.GetSize();cnt++)// Check and remove the data if exists for the graph ID 'lngGraphIdx'
			{
				checkInfo	=	m_arrPeakInfoIndexes.GetAt(cnt);
				if(checkInfo->lngGraphIdx	==	lngGraphIdx)
				{
					delete checkInfo;

					/*checkInfo->lngvalueIdx.RemoveAll(); 
					checkInfo->lngvalueIdx.FreeExtra();
					checkInfo->strPeakInfo.RemoveAll();
					checkInfo->strPeakInfo.FreeExtra();*/

					m_arrPeakInfoIndexes.RemoveAt(cnt);
					m_arrPeakInfoIndexes.FreeExtra();
				}
				checkInfo	=	NULL;
			}

			LPDISPATCH pDisp = m_chart.Series(lngGraphIdx);
			ISeriesPtr	pSeries= pDisp; // Get the control for the Graph ID 'lngGraphIdx'
			pDisp->Release();

			//set the color for text displaying the Peak info.
			IMarksPtr pMarks	=	pSeries->Marks;
			((IPen*)pMarks->Arrow)->Color	=	pSeries->GetColor();
			((ITeeFont*)pMarks->GetFont())->Color	=	pSeries->GetColor();

			pMarks	=	NULL;

			tempInfo	=	new EsdPeakInfoDisplay_Struct;
			tempInfo->lngGraphIdx	=	lngGraphIdx;

			if((pSeries->GetXValues()->Count)>2)// To display Peaks, no. of data points must be greater than 2.
			{
				long* lngIndex	=	 new long[pSeries->GetXValues()->Count];
				long lngNumOfPeaks	= fncCalculatePeakIndexes(lngGraphIdx,lngIndex);;	// Call to CalculatePeakIndexes function

				for(int j=0;j<lngNumOfPeaks;j++)		
				{
					str.Format(_T("%d"),j+1);
					bstrText	=	str;

					if(m_bShowDataAtPeak)
					{
						strTemp	=	str;
						str.Format(_T("(%.*lf, %.*lf)"), m_intXPrecision, pSeries->GetXValues()->GetValue(lngIndex[j]), m_intYPrecision, ((ISeries*)m_chart.Series(lngGraphIdx))->GetYValues()->GetValue(lngIndex[j]));
						str	=	str+_T("\r")+strTemp;
						bstrText=str;

						if(m_bShowConcAtPeak & !m_bPerConc)
						{
							double PercntConc= m_dblconcentration * (pSeries->GetYValues()->GetValue(lngIndex[j]));//(*(temp->dblYval.GetAt(lngIndex[i])));

							CString StrConc,Strname = _T("%Conc :");

							if(m_dblconcentration==0.0)
								StrConc.Format(_T("%s #Error"),Strname);
							else if(m_bPerConc==TRUE || (m_bShowConcAtPeak))
								StrConc.Format(_T("%s %.2f"),Strname,PercntConc);

							bstrText=StrConc;
						}			

					}	

					tempInfo->lngvalueIdx.Add(lngIndex[j]);
					tempInfo->strPeakInfo.Add(bstrText);				
				}	
				m_arrPeakInfoIndexes.Add(tempInfo);	

				tempInfo	=	NULL;

				delete [] lngIndex;
				pSeries=NULL;
			}
			BSTR bstr;
			OnGetTChartSeriesMarks(lngGraphIdx,0,&bstr); // raise the Event to display the Marks at Peak points only
		}
	}

}
//*************************************************
//PURPOSE : To hide the Peaks for a specified Graph.
//INPUTS  : LONG lngGraphIdx		-	Graph ID
//RETURNS : VARIANT_BOOL			-	Boolean value
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
VARIANT_BOOL CEsdAdvancedGraphCtrl::HidePeaks(LONG lngGraphIdx)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	stuRemovableGraphData temp ;
	if(lngGraphIdx>=0 && lngGraphIdx<m_chart.get_SeriesCount())		//	Check for the existence of the Graph.
	{
		LPDISPATCH pDisp = m_chart.Series(lngGraphIdx);
		ISeriesPtr	pSeries= pDisp; // Get the control for the Graph ID 'lngGraphIdx'
		pDisp->Release();

		_bstr_t bstrGraphName = pSeries->GetName().copy();
		pSeries	=	NULL;
		long lngIdx=GetLtblIdxFromName(bstrGraphName);
		if(lngIdx<0)
		{
			MessageBox(_T("Graph with specified ID doesn't exists hide"));
			return VARIANT_FALSE;
		}
		lngGraphIdx=lngIdx;
		temp = m_arrGraphRelatedSerieses.GetAt(lngGraphIdx);					//	Get the object of the Graph.
		if(temp.bShowPeaks)						
			m_intCounterForGraphsPeaks--;		//	Decrement the m_intCounterForGraphsPeaks only if ShowPeaks variable is TRUE
		temp.bShowPeaks	= FALSE;			//	for this Graph.
		temp.intPeakLevel	= 0;
		m_arrGraphRelatedSerieses.SetAt(lngGraphIdx,temp);
		m_chart.Repaint();						//	Call to OnDraw
		return VARIANT_TRUE;		
	}
	else
	{
		MessageBox(_T("Graph with specified ID doesn't exists"));
		return VARIANT_FALSE;
	}	



	return VARIANT_TRUE;
}


//*************************************************
//PURPOSE : Property returns the boolean value which indicates whether the data point at the peak is shown or not.
//INPUTS  : -
//ASSUMES : -
//RETURNS : VARIANT_BOOL value
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//----------------------------------------------
VARIANT_BOOL CEsdAdvancedGraphCtrl::GetShowDataAtPeak(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	return m_bShowDataAtPeak;
}
//*************************************************
//PURPOSE : Property to Set whether to show the data of the peak at the top of that peak.
//INPUTS  : VARIANT_BOOL newVal		-	Set / Unset
//ASSUMES : -
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//----------------------------------------------
void CEsdAdvancedGraphCtrl::SetShowDataAtPeak(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	m_bShowDataAtPeak	=	newVal;
	m_chart.Repaint();
	//below two fns are called bcz peak info is not displayed immediately(it requires manual redrawing).
	//By calling this it will once again forced to redraw the control and displays the info.Adding custom axis 
	//and immediately removing it will not effect any thing.
	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes	=	pDisp;
	pDisp->Release();
	long lngAxisIdx	=	pAxes->AddCustom(TRUE);
	pAxes->RemoveCustom(lngAxisIdx);
	pAxes	=	NULL;
	SetModifiedFlag();
}
//*************************************************
//PURPOSE : Property to return the cross wire status.
//INPUTS  : -
//ASSUMES : -
//RETURNS : VARIANT_BOOL 	-	Cross Wire Enabled / Disabled.
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//----------------------------------------------

VARIANT_BOOL CEsdAdvancedGraphCtrl::GetCrossWire(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	return m_bShowCrossWire;
}
//*************************************************
//PURPOSE : Property to Set / Unset the Cross wire status.
//INPUTS  : VARIANT_BOOL newVal		-	Enable / Disable
//ASSUMES : -
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//----------------------------------------------
void CEsdAdvancedGraphCtrl::SetCrossWire(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	m_bShowCrossWire	=	newVal;
	m_chart.Repaint();
	SetModifiedFlag();
}

//*************************************************
//PURPOSE : Method to draw the cross wire.
//INPUTS  : -
//ASSUMES : -
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//----------------------------------------------
void CEsdAdvancedGraphCtrl::prcDrawCrossWire(void)
{	
	long lngXDistance;
	long lngYDistance;
	long lngX;
	long lngY;
	double dblX;
	double dblY;

	//	Whenever LButton down occurs in the plot area when cross wire is enabled then trace the nearest data point.
	if(m_bFirstTimeCrossWire)
	{
		BOOL bFirstTime = TRUE;

		for(int intGraphCount = 0; intGraphCount < m_arrGraphRelatedSerieses.GetSize(); intGraphCount++)
		{
			stuRemovableGraphData temp = m_arrGraphRelatedSerieses.GetAt(intGraphCount);

			_bstr_t bstrGraphName(temp.bstrGraphName,TRUE);
			long lngIdx	=	GetGraphIdxFromName(bstrGraphName); // Get the index of the Graph stored in the 'intGraphCount' location of 'm_arrGraphRelatedSerises'
			if(lngIdx<0)
				continue;

			IDispatchPtr pDisp	=	m_chart.Series(lngIdx);
			ISeriesPtr	pSeries	=	pDisp;
			pDisp	=	NULL;

			for( long intDataCount = 0; intDataCount < pSeries->GetXValues()->Count; intDataCount++)
			{
				dblX = pSeries->GetXValues()->GetValue(intDataCount); 
				dblY = pSeries->GetYValues()->GetValue(intDataCount); 

				lngX =	pSeries->CalcXPosValue(dblX); // Covert to Long values
				lngY =	pSeries->CalcYPosValue(dblY);



				if(bFirstTime)
				{
					lngXDistance = abs(lngX - m_ptCrossWirePos.x);
					lngYDistance = abs(lngY - m_ptCrossWirePos.y);



					bFirstTime = FALSE;
				}


				if((abs(m_ptCrossWirePos.x - lngX) < lngXDistance)&& (abs(m_ptCrossWirePos.y - lngY) <= lngYDistance))
				{

					//	if((abs(m_ptCrossWirePos.x - lngX) <= lngXDistance) && (abs(m_ptCrossWirePos.y - lngY) <= lngYDistance))
					//	{ //20/12
					m_intCrossWireGraphID = intGraphCount;
					//	} //20/12
					m_lngCrossWireDataPointIndex = intDataCount;
					lngXDistance = abs(lngX - m_ptCrossWirePos.x);
					lngYDistance = abs(lngY - m_ptCrossWirePos.y);


				}		
			}

			m_bFirstTimeCrossWire = FALSE;

			pSeries	=	NULL;
		}
	}


	//	Now display the cross wire
	if(m_intCrossWireGraphID >= 0 && m_intCrossWireGraphID <= m_arrGraphRelatedSerieses.GetSize())
	{
		stuRemovableGraphData temp = m_arrGraphRelatedSerieses.GetAt(m_intCrossWireGraphID);

		_bstr_t bstrGraphName(temp.bstrGraphName);
		long lngIdx	=	GetGraphIdxFromName(bstrGraphName);
		if(lngIdx<0)
			return;

		IDispatchPtr pDisp  =	m_chart.Series(lngIdx);
		ISeriesPtr	pSeries	=	pDisp;
		pDisp	=	NULL;

		pDisp	=	m_chart.get_Aspect();
		IAspectPtr	pAspect	=	pDisp;
		pDisp	=	NULL;

		if(m_lngCrossWireDataPointIndex >= 0  && m_lngCrossWireDataPointIndex <=pSeries->GetXValues()->Count)
		{
			dblX	=	pSeries->GetXValues()->GetValue(m_lngCrossWireDataPointIndex);
			dblY	=	pSeries->GetYValues()->GetValue(m_lngCrossWireDataPointIndex);

			m_ptCrossWirePos.x	=	pSeries->CalcXPosValue(dblX);
			m_ptCrossWirePos.y	=	pSeries->CalcYPosValue(dblY);

			//	m_ptCrossWirePos.x = pow(10, m_intXPrecision) * (*(temp->dblXval.GetAt(m_lngCrossWireDataPointIndex)));
			//	m_ptCrossWirePos.y = pow(10, m_intYPrecision) * (*(temp->dblYval.GetAt(m_lngCrossWireDataPointIndex)));

			pDisp	=	m_chart.get_Axis();
			IAxesPtr	pAxes	=	pDisp;	// Get the Axes pointer 
			pDisp	=	NULL;

			// Store the Axes minimum and maximum values.
			m_lngXmin	=	pAxes->GetBottom()->CalcXPosValue(pAxes->GetBottom()->Minimum);
			m_lngXmax	=	pAxes->GetBottom()->CalcXPosValue(pAxes->GetBottom()->Maximum);

			m_lngYmax	=	pAxes->GetLeft()->CalcYPosValue(pAxes->GetLeft()->Minimum); // GetLeft()->Minimum means it gives the coords from bottom
			m_lngYmin	=	pAxes->GetLeft()->CalcYPosValue(pAxes->GetLeft()->Maximum);

			pAxes	=	NULL;

			pDisp	=	m_chart.get_Canvas();
			ICanvasPtr	pCanvas	=	pDisp;
			pDisp	=	NULL;
			pCanvas->GetPen()->Color	=	pSeries->Color;
			if(m_ptCrossWirePos.x >= m_lngXmin && m_ptCrossWirePos.x <= m_lngXmax && m_ptCrossWirePos.y	>= m_lngYmin && m_ptCrossWirePos.y <= m_lngYmax)
			{
				{
					if(pAspect->View3D	==	VARIANT_TRUE) // if 3D mode enabled
					{
						pCanvas->MoveTo3D(m_ptCrossWirePos.x, m_lngYmin,pAspect->Chart3DPercent/4);
						pCanvas->LineTo3D(m_ptCrossWirePos.x, m_lngYmax,pAspect->Chart3DPercent/4);

						pCanvas->MoveTo3D(m_lngXmin, /*m_lngXmax-*/m_ptCrossWirePos.y/*+m_lngYmin*/,pAspect->Chart3DPercent/4);
						pCanvas->LineTo3D(m_lngXmax, /*m_lngXmax-*/m_ptCrossWirePos.y/*+m_lngYmin*/,pAspect->Chart3DPercent/4);

					}
					else if(pAspect->View3D	==	VARIANT_FALSE)
					{		
						pCanvas->MoveTo(m_ptCrossWirePos.x, m_lngYmin);
						pCanvas->LineTo(m_ptCrossWirePos.x, m_lngYmax);

						pCanvas->MoveTo(m_lngXmin, /*m_lngXmax-*/m_ptCrossWirePos.y/*+m_lngYmin*/);
						pCanvas->LineTo(m_lngXmax, /*m_lngXmax-*/m_ptCrossWirePos.y/*+m_lngYmin*/);

					}
				}


				/*	MoveToEx(di.hdcDraw, m_ptCrossWirePos.x, m_lngYmin,NULL);
				LineTo(di.hdcDraw, m_ptCrossWirePos.x, m_lngYmax);

				MoveToEx(di.hdcDraw, m_lngXmin, m_lngYmax - m_ptCrossWirePos.y + m_lngYmin, NULL);				
				LineTo(di.hdcDraw, m_lngXmax, m_lngYmax - m_ptCrossWirePos.y + m_lngYmin);*/

			}
			pCanvas	=	NULL;
			/*	// ****** SURYA on 09/11/2006*********
			// This is used to Calculate the %Conc Value (WHEN USER CLICKS IN GRAPH CTRL)
			// in client by firing the event which uses current Xpos and Ypos.
			if(m_bPerConc && m_bLbtn)							 
			{
			double m_dblXCur,m_dblYCur;
			m_dblXCur = m_ptCrossWirePos.x/pow(10,m_intXPrecision); // convert the long values to double values.
			m_dblYCur = m_ptCrossWirePos.y/pow(10,m_intYPrecision); 
			Fire_Clicked(m_dblXCur,m_dblYCur);
			}*/
		}
		pSeries	=	NULL;
		pAspect	=	NULL;
	}
}
//////
void CEsdAdvancedGraphCtrl::prcBaseLine(void)
{
	if(m_bClickEvent)
	{
		double dblX,dblY;
		long lngX,lngY;
		long lngXDistance,lngYDistance;
		long nStartEndPoint=0;
		long m_lngYmax=0;	
		long m_lngYmin=0;

		stuRemovableGraphData temp = m_arrGraphRelatedSerieses.GetAt(0);

		bstr_t bstrGraphName(temp.bstrGraphName,TRUE);
		long lngIdx	=	GetGraphIdxFromName(bstrGraphName); // Get the index of the Graph stored in the 'intGraphCount' location of 'm_arrGraphRelatedSerises'

		IDispatchPtr pDisp	=	m_chart.Series(lngIdx);
		ISeriesPtr	pSeries	=	pDisp;
		pDisp	=	NULL;

		BOOL bFirstTime = TRUE;

		for( long intDataCount = 0; intDataCount < pSeries->GetXValues()->Count; intDataCount++)
		{
			dblX = pSeries->GetXValues()->GetValue(intDataCount); 
			dblY = pSeries->GetYValues()->GetValue(intDataCount); 

			lngX =	pSeries->CalcXPosValue(dblX); // Covert to Long values
			lngY =	pSeries->CalcYPosValue(dblY);

			if(bFirstTime)
			{
				lngXDistance = abs(lngX - m_ptStartEndPos.x);
				lngYDistance = abs(lngY - m_ptStartEndPos.y);

				bFirstTime = FALSE;
			}

			if((abs(m_ptStartEndPos.x - lngX) < lngXDistance))
			{
				nStartEndPoint= intDataCount;

				lngXDistance = abs(lngX - m_ptStartEndPos.x);
				lngYDistance = abs(lngY - m_ptStartEndPos.y);
			}
		}

		m_lngManualBaselineStartPointIndex = nStartEndPoint;

		FireEvent(eventidOnClickSeries, EVENT_PARAM(VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I8 ), 0, 0, 0, 0,pSeries->GetXValues()->GetValue(m_lngManualBaselineStartPointIndex));

		m_bClickEvent=FALSE;

		pSeries = NULL;

	}

}



//*************************************************
//PURPOSE : Method to display the cross wire at first data point on the Graph.
//INPUTS  : LONG *lngGraphID		-	Pointer variable to hold the Graph ID.	
//			LONG *lngDataPoint		-	Pointer variable to hold the Data Point Index.
//ASSUMES : -
//RETURNS : VARIANT_BOOL			-	Success / Failure
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//----------------------------------------------
VARIANT_BOOL CEsdAdvancedGraphCtrl::MoveCrossWireToFirst(LONG* lngGraphID, LONG* lngDataPoint)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	if(m_bShowCrossWire)		//	Is cross wire to be shown.
	{		
		if(m_arrGraphRelatedSerieses.GetSize()>0)		// Check for the existence of atleast one Graph(s).
		{
			if(m_intCrossWireGraphID <= -1)	// If Cross Wire Graph ID < 1 then.....
			{	
				double	dblTempX;
				double	dblTempY;
				stuRemovableGraphData temp = m_arrGraphRelatedSerieses.GetAt(0);

				_bstr_t bstrGraphName(temp.bstrGraphName,TRUE);
				long lngIdx	=	GetGraphIdxFromName(bstrGraphName); // Get the ID of the Graph that exists in the '0' index of 'm_arrGraphRelatedData'
				if(lngIdx<0)			// If ID doesn't exists return FALSE;
					return VARIANT_FALSE;

				LPDISPATCH pDisp = m_chart.Series(lngIdx);
				ISeriesPtr	pSeries= pDisp; // Get the control for the Graph ID 'lngGraphIdx'
				pDisp->Release();

				if(pSeries->GetXValues()->Count > 0)		// If there is atleast one data point
				{
					m_intCrossWireGraphID = 0;	// Set the cross wire Graph ID to the first Graph.
					m_lngCrossWireDataPointIndex = 0;// Set the cross wire data point index to the first data point.

					*lngGraphID		 =	 0;		// Return the cross wire Graph ID.
					*lngDataPoint	 =	 0;		// Return the Cross Wire Data Point Index.


					//Check if the data point is with in the graph area or not.....if not return false otherwise continue					
					if(pSeries->Clicked(m_ptCrossWirePos.x ,m_ptCrossWirePos.y)==-1) 
					{

						return VARIANT_FALSE;
					}


					dblTempX	=	pSeries->GetXValues()->GetValue(0); // Get Graph data at '0' index
					dblTempY	=	pSeries->GetXValues()->GetValue(0);

					m_ptCrossWirePos.x = pSeries->CalcXPosValue(dblTempX);// convert Graph data screen coords, bcz we cann't use double values on Screen
					m_ptCrossWirePos.y = pSeries->CalcYPosValue(dblTempY);

					m_chart.Repaint();
				}
				pSeries	=	NULL;
			}
			else if(m_intCrossWireGraphID < m_arrGraphRelatedSerieses.GetSize())	// If it is a valid Cross Wire Graph ID then......
			{
				stuRemovableGraphData temp = m_arrGraphRelatedSerieses.GetAt(m_intCrossWireGraphID);

				_bstr_t bstrGraphName(temp.bstrGraphName,TRUE);
				long lngIdx	=	GetGraphIdxFromName(bstrGraphName);  //Get the ID of the Graph existed at 'm_intCrossWireGraphID' index 
				if(lngIdx<0)
					return VARIANT_FALSE;

				LPDISPATCH pDisp = m_chart.Series(lngIdx);
				ISeriesPtr	pSeries= pDisp; // Get the control for the Graph ID 'lngGraphIdx'
				pDisp->Release();
				if(pSeries->GetXValues()->Count>0)
				{ 
					m_lngCrossWireDataPointIndex = 0;	// Set the Cross Wire Data Point Index to the first data point.

					*lngGraphID		=	lngIdx;	//	Return the Cross Wire Graph ID.
					*lngDataPoint	=	0;						//	Return the Cross Wire Data Point Index.

					m_chart.Repaint();
				}
				pSeries	=	NULL;
			}
			else
			{
				m_intCrossWireGraphID	=	-1;
				m_lngCrossWireDataPointIndex	=	-1;

				*lngGraphID			=	-1;
				*lngDataPoint	=	-1;
			}
		}

		return VARIANT_TRUE;
	}
	else
		return VARIANT_FALSE;


}
//*************************************************
//PURPOSE : Method to display the cross wire at last data point on the Graph.
//INPUTS  : LONG *lngGraphID		-	Pointer variable to hold the Graph ID.	
//			LONG *lngDataPoint		-	Pointer variable to hold the Data Point Index.
//ASSUMES : -
//RETURNS : VARIANT_BOOL			-	Success / Failure
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//----------------------------------------------

VARIANT_BOOL CEsdAdvancedGraphCtrl::MoveCrossWireToLast(LONG* lngGraphID, LONG* lngDataPoint)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	if(m_bShowCrossWire)		//	Is cross wire to be shown.
	{		
		if(m_arrGraphRelatedSerieses.GetSize()>0)		// Check for the existence of atleast one Graph(s).
		{
			if(m_intCrossWireGraphID <= -1)	// If Cross Wire Graph ID < 1 then.....
			{	
				double dblTempX;
				double dblTempY;
				stuRemovableGraphData temp = m_arrGraphRelatedSerieses.GetAt(0);

				_bstr_t bstrGraphName(temp.bstrGraphName,TRUE);
				long lngIdx	=	GetGraphIdxFromName(bstrGraphName); // Get the ID of the Graph that exists in the '0' index of 'm_arrGraphRelatedData'
				if(lngIdx<0)			// If ID doesn't exists return FALSE;
					return VARIANT_FALSE;

				LPDISPATCH pDisp = m_chart.Series(lngIdx);
				ISeriesPtr	pSeries= pDisp; // Get the control for the Graph ID 'lngGraphIdx'
				pDisp->Release();

				if(pSeries->GetXValues()->Count > 0)		// If there is atleast one data point
				{
					m_intCrossWireGraphID	=	0;	// Set the cross wire Graph ID to the first Graph.
					m_lngCrossWireDataPointIndex	=	(pSeries->GetXValues()->Count)-1;	// Set the cross wire data point index to the last data point.

					*lngGraphID		=	0;				// Return the cross wire Graph ID.
					*lngDataPoint	=	(pSeries->GetXValues()->Count)-1;	// Return the Cross Wire Data Point Index.

					//Check if the data point is with in the graph area or not.....if not return false otherwise continue
					if(pSeries->Clicked(m_ptCrossWirePos.x ,m_ptCrossWirePos.y)==-1)
					{

						return VARIANT_FALSE;
					}


					dblTempX	=	pSeries->GetXValues()->GetValue(m_lngCrossWireDataPointIndex); // Get Graph data at 'm_lngCrossWireDataPointIndex' index
					dblTempY	=	pSeries->GetXValues()->GetValue(m_lngCrossWireDataPointIndex);

					m_ptCrossWirePos.x = pSeries->CalcXPosValue(dblTempX);// convert Graph data screen coords, bcz we cann't use double values on Screen
					m_ptCrossWirePos.y = pSeries->CalcYPosValue(dblTempY);

					m_chart.Repaint();
				}
				pSeries	=	NULL;
			}
			else if(m_intCrossWireGraphID < m_arrGraphRelatedSerieses.GetSize())	// If it is a valid Cross Wire Graph ID then......
			{
				stuRemovableGraphData temp = m_arrGraphRelatedSerieses.GetAt(m_intCrossWireGraphID);

				_bstr_t bstrGraphName(temp.bstrGraphName,TRUE);
				long lngIdx	=	GetGraphIdxFromName(bstrGraphName);
				if(lngIdx<0)
					return VARIANT_FALSE;

				LPDISPATCH pDisp = m_chart.Series(lngIdx);
				ISeriesPtr	pSeries= pDisp; // Get the control for the Graph ID 'lngGraphIdx'
				pDisp->Release();

				if(pSeries->GetXValues()->Count>0)
				{
					m_lngCrossWireDataPointIndex = (pSeries->GetXValues()->Count)-1;	// Set the Cross Wire Data Point Index to the last data point.

					*lngGraphID		=	lngIdx;									//	Return the Cross Wire Graph ID.
					*lngDataPoint	=	(pSeries->GetXValues()->Count)-1;		//	Return the Cross Wire Data Point Index.

					m_chart.Repaint();
				}
				pSeries	=	NULL;
			}
			else
			{
				m_intCrossWireGraphID	=	-1;
				m_lngCrossWireDataPointIndex	=	-1;

				*lngGraphID			=	-1;
				*lngDataPoint	=	-1;
			}	
			return VARIANT_TRUE;
		}
		/*	if(!fncIsPtInGraph(m_ptCrossWirePos.x ,m_ptCrossWirePos.y))
		return VARIANT_FALSE;
		else
		return VARIANT_TRUE;*/
		return VARIANT_TRUE;
	}
	else
		return VARIANT_FALSE;
}

/******************************************************************************************
//PURPOSE : Method to move the cross wire forward to another data point from the current data point with the step size specified by the intStepBy.
//INPUTS  : LONG *lngGraphID		-	Pointer variable to hold the Graph ID.	
//			LONG *lngDataPoint		-	Pointer variable to hold the Data Point Index.
//			SHORT intStepBy			-	Step Size	
//ASSUMES : -
//RETURNS : VARIANT_BOOL		-	Success / Failure
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//---------------------------------------------------------------------------------*/

VARIANT_BOOL CEsdAdvancedGraphCtrl::MoveCrossWireToNext(LONG* lngGraphID, LONG* lngDataPoint, SHORT intStepBy)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	if(m_bShowCrossWire)						// Is cross wire to be shown.
	{
		if(m_arrGraphRelatedSerieses.GetSize()>0)	//	Check for existence of atleast one Graph(s).
		{
			if(m_intCrossWireGraphID <= -1)		// If Cross Wire Graph ID is -1 then set it to the first graph.
			{		
				double	dblTempX;
				double	dblTempY;
				stuRemovableGraphData temp = m_arrGraphRelatedSerieses.GetAt(0);

				_bstr_t bstrGraphName(temp.bstrGraphName,TRUE);
				long lngIdx	=	GetGraphIdxFromName(bstrGraphName); // Get the ID of the Graph that exists in the '0' index of 'm_arrGraphRelatedData'
				if(lngIdx<0)			// If ID doesn't exists return FALSE;
					return VARIANT_FALSE;

				LPDISPATCH pDisp = m_chart.Series(lngIdx);
				ISeriesPtr	pSeries= pDisp; // Get the control for the Graph ID 'lngIdx'
				pDisp->Release();

				if(pSeries->GetXValues()->Count > 0)
				{
					m_intCrossWireGraphID = 0;		//	Set Cross Wire Graph ID to the first Graph.
					m_lngCrossWireDataPointIndex = 0;	//	Set Cross Wire Data Point index to the first data point.

					*lngGraphID		=	0;			//	Return the Cross Wire Graph ID.	
					*lngDataPoint	=	0;			//	Return the Cross Wire Data Point Index.



					//Check if the data point is with in the graph area or not.....if not return false otherwise continue
					if(pSeries->Clicked(m_ptCrossWirePos.x ,m_ptCrossWirePos.y)==-1 && !m_bPerConc) //Surya...!m_bPerconc is added  to display %conc at first point
					{

						return VARIANT_FALSE;
					}

					dblTempX	=	pSeries->GetXValues()->GetValue(0); // Get Graph data at '0' index
					dblTempY	=	pSeries->GetXValues()->GetValue(0);

					m_ptCrossWirePos.x = pSeries->CalcXPosValue(dblTempX);// convert Graph data as screen coords, bcz we cann't use double values on Screen
					m_ptCrossWirePos.y = pSeries->CalcYPosValue(dblTempY);

					m_chart.Repaint();
				}
				pSeries	=	NULL;
			}
			else if(m_intCrossWireGraphID < m_arrGraphRelatedSerieses.GetSize())	// If the Cross Wire Graph ID is a valid one then...
			{
				stuRemovableGraphData temp = m_arrGraphRelatedSerieses.GetAt(m_intCrossWireGraphID);

				_bstr_t bstrGraphName(temp.bstrGraphName,TRUE);
				long lngIdx	=	GetGraphIdxFromName(bstrGraphName); // Get the ID of the Graph that exists in the '0' index of 'm_arrGraphRelatedData'
				if(lngIdx<0)			// If ID doesn't exists return FALSE;
					return VARIANT_FALSE;

				LPDISPATCH pDisp = m_chart.Series(lngIdx);
				ISeriesPtr	pSeries= pDisp; // Get the control for the Graph ID 'lngIdx'
				pDisp->Release();

				// Set the Cross Wire Data point with the step size
				if((m_lngCrossWireDataPointIndex + intStepBy) <= pSeries->GetXValues()->Count-1)
					m_lngCrossWireDataPointIndex += intStepBy;
				else
					m_lngCrossWireDataPointIndex = pSeries->GetXValues()->Count - 1;

				m_chart.Repaint();

				pSeries	=	NULL;

				*lngGraphID			=	lngIdx;							// Return the Cross Wire Graph ID.
				*lngDataPoint		=	m_lngCrossWireDataPointIndex;	// Return the Cross Wire Data Point Index.

			}
			else
			{
				m_intCrossWireGraphID			=	-1;
				m_lngCrossWireDataPointIndex	=	-1;

				*lngGraphID			=	-1;
				*lngDataPoint	=	-1;
			}
		}

		return VARIANT_TRUE;
	}
	else
	{
		return VARIANT_FALSE;
	}
}

//******************************************************************************************
//PURPOSE : Method to move the cross wire backward to another data point from the current data point with the step size specified by the intStepBy.
//INPUTS  : LONG *lngGraphID		-	Pointer variable to hold the Graph ID.	
//			LONG *lngDataPoint		-	Pointer variable to hold the Data Point Index.
//			SHORT intStepBy			-	Step Size	
//ASSUMES : -
//RETURNS : VARIANT_BOOL		-	Success / Failure
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//---------------------------------------------------------------------------------
VARIANT_BOOL CEsdAdvancedGraphCtrl::MoveCrossWireToPrev(LONG* lngGraphID, LONG* lngDataPoint, SHORT intStepBy)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	if(m_bShowCrossWire)				// Is cross wire to be shown.
	{ 		
		if(m_arrGraphRelatedSerieses.GetSize()>0)	//	Check for exisstence of atleast one Graph(s).
		{
			if(m_intCrossWireGraphID <= -1)		// If Cross Wire Graph ID is -1 then set it to the first graph.
			{		
				double	dblTempX;
				double	dblTempY;
				stuRemovableGraphData temp = m_arrGraphRelatedSerieses.GetAt(0);

				_bstr_t bstrGraphName(temp.bstrGraphName,TRUE);
				long lngIdx	=	GetGraphIdxFromName(bstrGraphName); // Get the ID of the Graph that exists in the '0' index of 'm_arrGraphRelatedData'
				if(lngIdx<0)			// If ID doesn't exists return FALSE;
					return VARIANT_FALSE;

				LPDISPATCH pDisp = m_chart.Series(lngIdx);
				ISeriesPtr	pSeries= pDisp; // Get the control for the Graph ID 'lngIdx'
				pDisp->Release();
				if(pSeries->GetXValues()->Count > 0)		// Check if there are any data points present in the first graph or not.	
				{
					m_intCrossWireGraphID = 0;		//	Set Cross Wire Graph ID to the first Graph.
					m_lngCrossWireDataPointIndex = 0;	//	Set Cross Wire Data Point index to the first data point.

					*lngGraphID		=	0;			//	Return the Cross Wire Graph ID.	
					*lngDataPoint	=	0;			//	Return the Cross Wire Data Point Index.


					//Check if the data point is with in the graph area or not.....if not return false otherwise continue
					if(pSeries->Clicked(m_ptCrossWirePos.x ,m_ptCrossWirePos.y)==-1)
					{

						return VARIANT_FALSE;
					}

					dblTempX	=	pSeries->GetXValues()->GetValue(0); // Get Graph data at '0' index
					dblTempY	=	pSeries->GetXValues()->GetValue(0);

					m_ptCrossWirePos.x = pSeries->CalcXPosValue(dblTempX);// convert Graph data screen coords, bcz we cann't use double values on Screen 
					m_ptCrossWirePos.y = pSeries->CalcYPosValue(dblTempY);// and save in 'm_ptCrossWire'

					m_chart.Repaint();
				}
				pSeries	=	NULL;
			}
			else if(m_intCrossWireGraphID < m_arrGraphRelatedSerieses.GetSize())	// If the Cross Wire Graph ID is a valid one then...
			{
				stuRemovableGraphData temp = m_arrGraphRelatedSerieses.GetAt(m_intCrossWireGraphID);	

				_bstr_t bstrGraphName(temp.bstrGraphName,TRUE);
				long lngIdx	=	GetGraphIdxFromName(bstrGraphName); // Get the ID of the Graph that exists in the '0' index of 'm_arrGraphRelatedData'
				if(lngIdx<0)			// If ID doesn't exists return FALSE;
					return VARIANT_FALSE;

				LPDISPATCH pDisp = m_chart.Series(lngIdx);
				ISeriesPtr	pSeries= pDisp; // Get the control for the Graph ID 'lngIdx'
				pDisp->Release();

				if(m_lngCrossWireDataPointIndex > 0)
				{
					// Set the Cross Wire Data point with the step size
					if((m_lngCrossWireDataPointIndex - intStepBy) >= 0)
						m_lngCrossWireDataPointIndex  -= intStepBy;		
					else
						m_lngCrossWireDataPointIndex = 0;

					m_chart.Repaint();
				}

				pSeries	=	NULL;

				*lngGraphID			=	lngIdx;		// Return the Cross Wire Graph ID.
				*lngDataPoint		=	m_lngCrossWireDataPointIndex;	// Return the Cross Wire Data Point Index.

			}
			else
			{
				m_intCrossWireGraphID			=	-1;
				m_lngCrossWireDataPointIndex	=	-1;

				*lngGraphID			=	-1;
				*lngDataPoint	=	-1;
			}
		}
		return VARIANT_TRUE;
	}
	else
		return VARIANT_FALSE;
}

//*************************************************
//PURPOSE : Method to display the cross wire at desired data point on the Graph.
//INPUTS  : DOUBLE dblXval	-	X value
//		  :	DOUBLE dblYval	-	Y value			
//ASSUMES : 
//RETURNS : VARIANT_BOOL		-	Success / Failure
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//----------------------------------------------
VARIANT_BOOL CEsdAdvancedGraphCtrl::DisplayCrossWireAt(DOUBLE dblXval, DOUBLE dblYval)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	if(m_bShowCrossWire)
	{
		LPDISPATCH pDisp	=	m_chart.get_Axis();
		IAxesPtr pAxes	=	pDisp;
		pDisp->Release();
		m_ptCrossWirePos.x	=	pAxes->GetBottom()->CalcXPosValue(dblXval);// convert double values into Screen Coords(long values)
		m_ptCrossWirePos.y	=	pAxes->GetLeft()->CalcYPosValue(dblYval);  

		m_bFirstTimeCrossWire = TRUE;

		pAxes	=	NULL;

		if(m_arrGraphRelatedSerieses.GetSize()>0)
			m_chart.Repaint();

		return VARIANT_TRUE;
	}
	return VARIANT_FALSE;
}
//*************************************************
//PURPOSE : Method to set the custom text to be displayed at the peaks
//INPUTS  : LPCTSTR	bstrCrosswireText		-	Custom text
//			VARIANT_BOOL blnHideXYValues	-	boolean value to hide/show the X,Y values at peaks when custom text displayed
//			DOUBLE	concentration			-	value to be displayed at peak(Addition to 'bstrCrossWireText')
//ASSUMES : 
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//----------------------------------------------
void CEsdAdvancedGraphCtrl::SetCustomCrosswireText(LPCTSTR bstrCrosswireText, VARIANT_BOOL blnHideXYValues, DOUBLE Concentration)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	m_dblconcentration = Concentration;
	m_strCrosswireText=bstrCrosswireText;
	m_blnHideXYValues=blnHideXYValues;
	m_chart.Repaint();
}
//*************************************************
//PURPOSE : property to get the cross wire data point index
//INPUTS  : 			
//ASSUMES : 
//RETURNS : LONG	-	Index of the cross wire data point
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//----------------------------------------------

LONG CEsdAdvancedGraphCtrl::GetCrossWireDataPointIndex(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	return m_lngCrossWireDataPointIndex;
}
//*************************************************
//PURPOSE : Property to set the  index of the data point(where the the cross wire want to be displayed)
//INPUTS  : LONG newValue	-	index 		
//ASSUMES : 
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//----------------------------------------------
void CEsdAdvancedGraphCtrl::SetCrossWireDataPointIndex(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	m_lngCrossWireDataPointIndex = newVal;

	SetModifiedFlag();
}

//*************************************************
//PURPOSE : Function to display the Cross wire corresponding values
//INPUTS  : -	
//ASSUMES : -
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//----------------------------------------------
void CEsdAdvancedGraphCtrl::prcDisplayCrossWireXYValues(void)
{
	if(m_bPerConc ) // IF PERCENT CONCENTRATION MODE IS SELECTED..FOR MULTIPLE TOOLTIPS
	{	

		LPDISPATCH pDisp	=	NULL;
		IAxesPtr  axes = NULL;
		ISeriesPtr	pSeries	=	NULL;
		ICanvasPtr	pCanvas	=	NULL;
		IAspectPtr	pAspect	=	NULL;

		for(long k= 0 ; k < m_arrGraphRelatedSerieses.GetSize(); k++)
		{
			stuRemovableGraphData temp;
			//	if((m_arrGraphRelatedSerieses.GetAt(k)))
			{
				temp = m_arrGraphRelatedSerieses.GetAt(k);

			}
			CString strXYValues;
			_bstr_t bstrXYValues;
			long lngTextHt,lngTextWd;
			RECT	rectXYValues;
			// 19/12/07 ////
			CRect rect;	// Rectangle to store plot area region 
			double tempPlot; // Temporary variable to store dimensions

			pDisp	=	m_chart.get_Axis();
			axes = pDisp;						//Get Axes pointer to access the functions
			pDisp->Release();
			tempPlot=axes->GetBottom()->GetMinimum();				// Axes Coordinates(in Doubles)
			rect.left= axes->GetBottom()->CalcXPosValue(tempPlot); // Convert Axes coords to Screen coords(in Pixels)

			tempPlot=axes->GetBottom()->GetMaximum();
			rect.right=axes->GetBottom()->CalcXPosValue(tempPlot);

			tempPlot=axes->GetLeft()->GetMinimum();
			rect.bottom= axes->GetLeft()->CalcYPosValue(tempPlot);

			tempPlot=axes->GetLeft()->GetMaximum();
			rect.top=axes->GetLeft()->CalcYPosValue(tempPlot);

			/*	// Get The precision of the X and Y Axes scaling,
			_bstr_t bstrPrecision;
			CString strPrecision;

			// Bottom axis(X-Axis) precision
			bstrPrecision	=	axes->GetBottom()->GetLabels()->ValueFormat; 
			strPrecision	=	(wchar_t*)bstrPrecision;

			int nPosition=strPrecision.Find(_T("."));
			m_intXPrecision	=	strPrecision.GetLength()-(nPosition+1);

			if(strPrecision.GetLength()==1 && nPosition==-1)
			m_intXPrecision	=	0;
			bstrPrecision	=	_T("");

			//Left Axis(Y-Axis) precision
			bstrPrecision	=	axes->GetLeft()->GetLabels()->ValueFormat; 
			strPrecision	=	(wchar_t*)bstrPrecision;

			nPosition=strPrecision.Find(_T("."));
			m_intYPrecision	=	strPrecision.GetLength()-(nPosition+1);

			if(strPrecision.GetLength()==1 && nPosition==-1)
			m_intYPrecision	=	0;
			bstrPrecision	=	_T("");*/

			axes=NULL;
			// 19/12/07 ////

			_bstr_t bstrGraphName(temp.bstrGraphName,TRUE);
			long lngIdx	=	GetGraphIdxFromName(bstrGraphName); // Get the ID of the Graph that exists in the '0' index of 'm_arrGraphRelatedData'
			if(lngIdx<0)			// If ID doesn't exists return FALSE;
				return ;

			pDisp = m_chart.Series(lngIdx);
			pSeries = pDisp; // Get the control for the Graph ID 'lngIdx'
			pDisp->Release();
			m_ptCrossWirePos.x = pSeries->CalcXPosValue(pSeries->GetXValues()->GetValue(m_lngCrossWireDataPointIndex));//pow(10, m_intXPrecision) * (*(temp->dblXval.GetAt(m_lngCrossWireDataPointIndex)));	// Set the Cross Wire data point.
			m_ptCrossWirePos.y = pSeries->CalcYPosValue(pSeries->GetYValues()->GetValue(m_lngCrossWireDataPointIndex));//pow(10, m_intYPrecision) * (*(temp->dblYval.GetAt(m_lngCrossWireDataPointIndex)));

			POINT	ptTemp	=	m_ptCrossWirePos;

			pDisp	=	m_chart.get_Canvas();
			pCanvas	=	pDisp;
			pDisp->Release();
			pDisp	=	m_chart.get_Aspect();
			pAspect	=	pDisp;
			pDisp->Release();

			pCanvas->GetBrush()->Style	=	bsSolid;
			pCanvas->GetBrush()->Color	=	(OLE_COLOR)RGB(255,255,220); // Set the Color for the rectangle, where text will be displayed


			CString strGraphTitle	=	(wchar_t *)pSeries->GetTitle();
			strXYValues.Format(_T(" %s (%.*lf , %.*lf)"),strGraphTitle , m_intXPrecision, pSeries->GetXValues()->GetValue(m_lngCrossWireDataPointIndex), m_intYPrecision, pSeries->GetYValues()->GetValue(m_lngCrossWireDataPointIndex));
			bstrXYValues	=	strXYValues;

			double dblTempYVal	=	pSeries->GetYValues()->GetValue(m_lngCrossWireDataPointIndex);

			double PercntConc= (m_dblconcentration * dblTempYVal);

			if(m_blnHideXYValues)
			{
				strXYValues.Format(_T("%s %f"),m_strCrosswireText,PercntConc);
				bstrXYValues	=	strXYValues;
			}
			CString StrConc,Strname = _T("%Conc :");


			if(m_dblconcentration==0.0)
				StrConc.Format(_T("%s #Error"),Strname);
			else if(m_bPerConc==TRUE)
				StrConc.Format(_T("%s %.2f"),Strname,PercntConc);

			lngTextHt	=	pCanvas->TextHeight(bstrXYValues); // Get Size of the Text
			lngTextWd	=	pCanvas->TextWidth(bstrXYValues);

			rectXYValues.left	=	ptTemp.x + 2;
			rectXYValues.top	=	ptTemp.y + 2;				// For Rectangle display 
			rectXYValues.right	=	ptTemp.x +  lngTextWd+ 0;	
			rectXYValues.bottom	=	ptTemp.y + lngTextHt + 7;


			if((!m_blnHideXYValues)&&(m_strCrosswireText.GetLength()>0))
				rectXYValues.bottom = rectXYValues.bottom + lngTextHt-7;

			//here


			if(pSeries->Clicked(rectXYValues.right,rectXYValues.bottom)==-1) //If this point is not exist in the Graph 
			{
				if(rectXYValues.right > rect.right)
				{
					rectXYValues.right= ptTemp.x - 2;
					rectXYValues.left= ptTemp.x - lngTextWd - 0; 
				}

				if(rectXYValues.bottom > rect.bottom)
				{
					rectXYValues.bottom= ptTemp.y - 2;
					rectXYValues.top= ptTemp.y - lngTextHt - 15;
				}

			}

			if(pAspect->View3D	==	VARIANT_TRUE)// If 3D mode enabled
			{
				pCanvas->RectangleWithZ(rectXYValues.left,rectXYValues.top,rectXYValues.right,rectXYValues.bottom,pAspect->Chart3DPercent/4);
				pCanvas->TextOut3D(rectXYValues.left,rectXYValues.top,pAspect->Chart3DPercent/4,bstrXYValues);

			}
			else if(pAspect->View3D	==	VARIANT_FALSE)// If 3D mode not enabled
			{
				pCanvas->Rectangle(rectXYValues.left,rectXYValues.top,rectXYValues.right,rectXYValues.bottom);
				pCanvas->TcTextOut(rectXYValues.left, rectXYValues.top,bstrXYValues);
			}

			//			pCanvas->Rectangle(rectXYValues.left,rectXYValues.top,rectXYValues.right,rectXYValues.bottom);
			//			pCanvas->TextOut(rectXYValues.left, rectXYValues.top,bstrXYValues);

			if((!m_blnHideXYValues)&&(StrConc.GetLength()>0))
			{
				_bstr_t bstrConc	=	StrConc;
				pCanvas->TcTextOut((long)rectXYValues.left+4, (long)rectXYValues.top+(0.9*lngTextHt),bstrConc);
			}
			pCanvas	=	NULL;
			pSeries	=	NULL;
			pAspect	=	NULL;
		}

	}
	else // FOR NORMAL DISPLAY OF THE TEXT NEAR THE CROSSWIRE 
	{
		CString strXYValues;	
		_bstr_t bstrXYValues;
		long	lngTextWd,lngTextHt;
		RECT	rectXYValues;
		POINT	ptTemp	=	m_ptCrossWirePos;
		CRect rect;	// Rectangle to store plot area region 

		double tempPlot;
		IDispatchPtr pDisp =	m_chart.get_Axis();
		IAxesPtr  axes= pDisp;						//Get Axes pointer to access the functions
		pDisp	=	NULL;
		tempPlot=axes->GetBottom()->GetMinimum();				// Axes Coordinates(in Doubles)
		rect.left= axes->GetBottom()->CalcXPosValue(tempPlot); // Convert Axes coords to Screen coords(in Pixels)

		tempPlot=axes->GetBottom()->GetMaximum();
		rect.right=axes->GetBottom()->CalcXPosValue(tempPlot);

		tempPlot=axes->GetLeft()->GetMinimum();
		rect.bottom= axes->GetLeft()->CalcYPosValue(tempPlot);

		tempPlot=axes->GetLeft()->GetMaximum();
		rect.top=axes->GetLeft()->CalcYPosValue(tempPlot);
		axes=NULL;

		pDisp	=	m_chart.get_Canvas();
		ICanvasPtr	pCanvas	=	pDisp;
		pDisp	=	NULL;

		pCanvas->GetBrush()->Style	=	bsSolid;
		pCanvas->GetBrush()->Color	=	(OLE_COLOR)RGB(255,255,220); // Set the Color for the rectangle, where text will be displayed

		pCanvas->GetPen()->Color	=	(OLE_COLOR)RGB(0,0,0);
		stuRemovableGraphData temp = m_arrGraphRelatedSerieses.GetAt(m_intCrossWireGraphID);

		_bstr_t bstrGraphName(temp.bstrGraphName,TRUE);
		long lngIdx	=	GetGraphIdxFromName(bstrGraphName); // Get the ID of the Graph that exists in the '0' index of 'm_arrGraphRelatedData'
		if(lngIdx<0)			// If ID doesn't exists return FALSE;
			return ;

		pDisp	=	m_chart.Series(lngIdx);
		ISeriesPtr	pSeries	=	pDisp;
		pDisp	=	NULL;

		/*		ptTemp.y	=	m_lngYmax	-	ptTemp.y;
		ptTemp.x	=	ptTemp.x	-	m_lngXmin;	

		prcLPtoDP(ptTemp);*/

		CString strGraphTitle	=	/*(wchar_t*)*/pSeries->GetTitle();	//18/122
		strXYValues.Format(_T(" %s (%.*lf , %.*lf)"),strGraphTitle , m_intXPrecision, pSeries->GetXValues()->GetValue(m_lngCrossWireDataPointIndex), m_intYPrecision, pSeries->GetYValues()->GetValue(m_lngCrossWireDataPointIndex));

		if(m_blnHideXYValues)
			strXYValues = /*_T(" ") +*/ m_strCrosswireText;

		bstrXYValues	=	strXYValues;


		//	GetTextExtentPoint(di.hdcDraw, strXYValues, strXYValues.GetLength(),&szChar);
		lngTextHt	=	pCanvas->TextHeight(bstrXYValues); // Get Size of the Text
		lngTextWd	=	pCanvas->TextWidth(bstrXYValues);

		rectXYValues.left	=	ptTemp.x + 2;
		rectXYValues.top	=	ptTemp.y + 2;
		rectXYValues.right	=	ptTemp.x + /*szChar.cx*/ lngTextWd+ 7;
		rectXYValues.bottom	=	ptTemp.y + /*szChar.cy*/lngTextHt + 7;

		if(pSeries->Clicked(rectXYValues.right,rectXYValues.bottom)==-1)
		{
			if(rectXYValues.right > rect.right)
			{
				rectXYValues.right= ptTemp.x - 2;
				rectXYValues.left= ptTemp.x - /*szChar.cx*/lngTextWd - 7;
			}

			if(rectXYValues.bottom > rect.bottom)
			{
				rectXYValues.bottom= ptTemp.y - 2;
				rectXYValues.top= ptTemp.y - /*szChar.cy*/lngTextHt - 15;
			}

		}

		//pCanvas->Rectangle(rectXYValues.left,rectXYValues.top,rectXYValues.right,rectXYValues.bottom);
		//pCanvas->TextOut(rectXYValues.left, rectXYValues.top,bstrXYValues);

		pDisp	=	m_chart.get_Aspect();
		IAspectPtr pAspect =	pDisp;
		pDisp	=	NULL;
		if(pAspect->View3D	==	VARIANT_TRUE)// If 3D mode enabled
		{
			pCanvas->RectangleWithZ(rectXYValues.left,rectXYValues.top,rectXYValues.right,rectXYValues.bottom,pAspect->Chart3DPercent/4);
			pCanvas->TextOut3D(rectXYValues.left,rectXYValues.top,pAspect->Chart3DPercent/4,bstrXYValues);

		}
		else if(pAspect->View3D	==	VARIANT_FALSE)// If 3D mode not enabled
		{
			pCanvas->Rectangle(rectXYValues.left,rectXYValues.top,rectXYValues.right,rectXYValues.bottom);
			pCanvas->TcTextOut(rectXYValues.left, rectXYValues.top,bstrXYValues);
		}


		if((!m_blnHideXYValues)&&(m_strCrosswireText.GetLength()>0))
		{
			m_strCrosswireText = m_strCrosswireText;
		}

		pAspect	=	NULL;
		pCanvas	=	NULL;
		pSeries	=	NULL;
	}

}

//*************************************************
//PURPOSE : To return the boolean which indicates whether displaying of Graph(s) is/are done by sorting the data points or not.
//INPUTS  : -
//ASSUMES : -
//RETURNS : VARIANT_BOOL  - Boolean value.
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
VARIANT_BOOL CEsdAdvancedGraphCtrl::GetSort(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	return m_bSortPoints;
}
//*************************************************
//PURPOSE : To set the boolean value which decides whether Graph(s) displaying is/are done by sorting the data points.
//INPUTS  : VARIANT_BOOL newVal -	Boolean value.
//ASSUMES : -
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::SetSort(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here

	m_bSortPoints	=	newVal;

	SetModifiedFlag();
}

//*************************************************
//PURPOSE : Function to clear all Graphs Peak information Stored in structures
//INPUTS  : -
//ASSUMES : -
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::ClearPeakInformation(void)
{
	if(m_arrPeakDetectPoint.GetSize() > 0 )
	{
		m_arrPeakDetectPoint.RemoveAll();
		m_arrPeakDetectPoint.FreeExtra();
	}

	if(m_GraphPeaks.GetSize() > 0)
	{
		stuPeakInfo* PeakInfo = NULL;
		for(int i = 0; i < m_GraphPeaks.GetSize(); i++)
		{
			PeakInfo = m_GraphPeaks.GetAt(i);

			PeakInfo->dblArea.RemoveAll();
			PeakInfo->dblHeight.RemoveAll();
			PeakInfo->dblPeakEndX.RemoveAll();
			PeakInfo->dblPeakEndY.RemoveAll();
			PeakInfo->dblPeakMaxX.RemoveAll();
			PeakInfo->dblPeakMaxY.RemoveAll();
			PeakInfo->dblPeakStartX.RemoveAll();
			PeakInfo->dblPeakStartY.RemoveAll();
			PeakInfo->dblWidth.RemoveAll();
			PeakInfo->intPeakEndIndex.RemoveAll();
			PeakInfo->intPeakMaxIndex.RemoveAll();
			PeakInfo->intPeakStartIndex.RemoveAll();

			PeakInfo->dblArea.FreeExtra();
			PeakInfo->dblHeight.FreeExtra();
			PeakInfo->dblPeakEndX.FreeExtra();
			PeakInfo->dblPeakEndY.FreeExtra();
			PeakInfo->dblPeakMaxX.FreeExtra();
			PeakInfo->dblPeakMaxY.FreeExtra();
			PeakInfo->dblPeakStartX.FreeExtra();
			PeakInfo->dblPeakStartY.FreeExtra();
			PeakInfo->dblWidth.FreeExtra();
			PeakInfo->intPeakEndIndex.FreeExtra();
			PeakInfo->intPeakMaxIndex.FreeExtra();
			PeakInfo->intPeakStartIndex.FreeExtra();

			delete PeakInfo;

			PeakInfo = NULL;
		}

		m_GraphPeaks.RemoveAll();
		m_GraphPeaks.FreeExtra();
	}

	InitializePeakDetectionVariables();
}

//*************************************************
//PURPOSE : Returns BOOL value which indicates whether AutoRange is enabled or not.
//INPUTS  : -
//ASSUMES : -
//RETURNS : VARIANT_BOOL -  BOOL value.
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
VARIANT_BOOL CEsdAdvancedGraphCtrl::GetAutoRange(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	return m_bAutoRangeEnable;
}
//*************************************************
//PURPOSE : To Enable/Disable the AutoRange.
//INPUTS  : BOOL newVal - BOOL value.
//ASSUMES : 
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------

void CEsdAdvancedGraphCtrl::SetAutoRange(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here

	m_bAutoRangeEnable = newVal;	

	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes	=	pDisp;
	pDisp->Release();
	pAxes->GetLeft()->Automatic	=	newVal;// Set the BOOL value which enables/disables the Auto Range.
	pAxes->GetBottom()->Automatic	=	newVal;// Set the BOOL value which enables/disables the Auto Range.

	pAxes	=	NULL;

	SetModifiedFlag();
}
//*************************************************
//PURPOSE : Returns weather the Percentage concentration 
//			value is Visible/Invisible at Cross wire position
//INPUTS  : 
//ASSUMES : 
//RETURNS : Boolean value
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
VARIANT_BOOL CEsdAdvancedGraphCtrl::GetPerConc(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	return m_bPerConc;
}
//*************************************************
//PURPOSE : Sets the Percentage concentration value visibility / Invisibility status at Cross wire position
//INPUTS  : BOOL newVal - BOOL value.
//			if	'TRUE'	-	%Conc value will display at Cross wire
//			if	'FALSE'	-	%Conc value will not be displayed at Cross wire
//ASSUMES : 
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::SetPerConc(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	m_bPerConc	=	newVal;

	SetModifiedFlag();
}

//*************************************************
//PURPOSE : Returns the Visibility/invisibility status for the % Conc 
//			at graph peaks.
//INPUT	  :	-		
//ASSUMES : 
//RETURNS : Boolean value
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
VARIANT_BOOL CEsdAdvancedGraphCtrl::GetShowConcAtPeaks(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	return m_bShowConcAtPeak;
}

//*************************************************
//PURPOSE : Enables/Disables the visibility of % Concentration value at peaks.
//INPUTS  : VARIANT_BOOL	--	Boolean value			
//ASSUMES : This will effect if only 'ShowPeaks' condition is true.
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::SetShowConcAtPeaks(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	m_bShowConcAtPeak	=	newVal;
	m_chart.Repaint();
	//below two fns are called bcz peak info is not displayed immediately(it requires manual redrawing).
	//By calling this it will once again forced to redraw the control and displays the info.Adding custom axis 
	//and immediately removing it will not effect any thing.
	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes	=	pDisp;
	pDisp->Release();
	long lngAxisIdx	=	pAxes->AddCustom(TRUE);
	pAxes->RemoveCustom(lngAxisIdx);
	pAxes	=	NULL;

	SetModifiedFlag();
}

//*************************************************
//PURPOSE : Returns the Visible/Invisible condition of the X-Axis Title 
//INPUT	  :	-		
//ASSUMES : -
//RETURNS : VARIANT_BOOL	---	Boolean value.
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
VARIANT_BOOL CEsdAdvancedGraphCtrl::GetShowXTitle(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	return m_bShowXTitle;
}

//*************************************************
//PURPOSE : Show/Hides the X-Axis Title
//INPUT	  :	VARIANT_BOOL newVal		--		Boolean value	
//ASSUMES : 
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::SetShowXTitle(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here

	m_bShowXTitle	=	newVal;

	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes	=	pDisp;
	pDisp->Release();
	IAxisTitlePtr pAxisTitle	=	pAxes->GetBottom()->GetTitle();
	pAxisTitle->Caption	=	_bstr_t(m_strXAxisTitle);
	pAxisTitle->Visible	=	m_bShowXTitle;

	pAxisTitle	=	NULL;
	pAxes	=	NULL;

	SetModifiedFlag();
}

//*************************************************
//PURPOSE : Returns the Visible/Invisible condition of the Y-Axis Title 
//INPUT	  :	-		
//ASSUMES : -
//RETURNS : VARIANT_BOOL	---	Boolean value.
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
VARIANT_BOOL CEsdAdvancedGraphCtrl::GetShowYTitle(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	return m_bShowYTitle;
}

//*************************************************
//PURPOSE : Show/Hides the Y-Axis Title
//INPUT	  :	VARIANT_BOOL newVal		--		Boolean value	
//			
//ASSUMES : 
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::SetShowYTitle(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	m_bShowYTitle	=	newVal;
	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes	=	pDisp;
	pDisp->Release();
	IAxisTitlePtr pAxisTitle	=	pAxes->GetLeft()->GetTitle();
	pAxisTitle->Caption	=	_bstr_t(m_strYAxisTitle);
	pAxisTitle->Visible	=	m_bShowXTitle;

	pAxisTitle	=	NULL;
	pAxes	=	NULL;

	SetModifiedFlag();
}

//*************************************************
//PURPOSE : Sets the font name and size for the text used to
//			display the Legends i.e graph name and Graph color
//INPUT   :	LPCTSTR	strFontName		--	Name of the font
//			LONG lngFontSize		--	Size of the font
//ASSUMES : 
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::SetLegendFont(LPCTSTR strFontName, LONG lngFontSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	LPDISPATCH pDisp	=	m_chart.get_Axis();
	ILegendPtr pLegend	=	pDisp;
	pDisp->Release();
	pLegend->GetTitle()->GetFont()->Name	=	_bstr_t(strFontName);
	pLegend->GetTitle()->GetFont()->Size	=	lngFontSize;

	pLegend	=	NULL;
}




//*************************************************
//PURPOSE : Sets the font name and size for the text used to
//			display the Scale of the X and Y axes.
//INPUT   :	LPCTSTR	strFontName		--	Name of the font
//			LONG lngFontSize		--	Size of the font
//ASSUMES : -
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::SetXYMarkingFont(LPCTSTR strFontName, LONG lngFontSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes	=	pDisp;
	pDisp->Release();

	//Set the font name and font size for the X-Axis Marking
	pAxes->GetBottom()->GetLabels()->GetFont()->Name	=	_bstr_t(strFontName);
	pAxes->GetBottom()->GetLabels()->GetFont()->Size	=	lngFontSize;

	//Set the font name and font size for the Y-Axis Marking
	pAxes->GetLeft()->GetLabels()->GetFont()->Name	=	_bstr_t(strFontName);
	pAxes->GetLeft()->GetLabels()->GetFont()->Size	=	lngFontSize;

	pAxes	=	NULL;
}



//*************************************************
//PURPOSE : Sets the font name and size for the custom text used to
//			display the information.
//INPUT   :	LPCTSTR	strFontName		--	Name of the font
//			LONG lngFontSize		--	Size of the font
//ASSUMES : 
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::SetCustomTextFont(LPCTSTR strFontName, LONG lngFontSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	LPDISPATCH pDisp	=	m_chart.get_Axis();
	ICanvasPtr pCanvas	=	pDisp;
	pDisp->Release();
	//Set the Font name and font Size for the Custom text displayed on the chart area.
	pCanvas->GetFont()->Name	=	_bstr_t(strFontName);
	pCanvas->GetFont()->Size	=	lngFontSize;

	pCanvas	=	NULL;
}

//*************************************************
//PURPOSE :  Returns the Number of grids drawn for the X-Axis
//INPUT	  :	-		
//ASSUMES : 
//RETURNS : SHORT	--	Grids Count
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
SHORT CEsdAdvancedGraphCtrl::GetXGrids(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	return m_intXNumOfGrids;
}

//*************************************************
//PURPOSE : Sets the number of grids to be drawn for the X-Axis
//INPUT	  : SHORT newVal	--	Number of grids 
//ASSUMES : 
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::SetXGrids(SHORT newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here

	m_chart.Repaint(); //  After drawing data points and then Immediately Call this function, This fn will not give below max and min values
	// and will not draw the Grids to the specified  number,if this 'Repiaint' method is called first.
	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes	=	pDisp;
	pDisp->Release();
	//IAxisPtr pLeft	=	pAxes->GetLeft();
	IAxisPtr pBottom	=	pAxes->GetBottom();

	double dblMin,dblMax;
	dblMin	=	pBottom->GetMinimum();
	dblMax	=	pBottom->GetMaximum();

	m_intXNumOfGrids	=	newVal;
	pBottom->Increment	=	(dblMax	-	dblMin)/newVal;

	pBottom	=	NULL;
	pAxes	=	NULL;

	SetModifiedFlag();
}

//*************************************************
//PURPOSE : Returns the Number of grids drawn for the Y-Axis
//INPUT	  :	-		
//ASSUMES : -
//RETURNS : SHORT	--	Grids Count
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
SHORT CEsdAdvancedGraphCtrl::GetYGrids(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	return m_intYNumOfGrids;
}

//*************************************************
//PURPOSE : Sets the number of grids to be drawn for the Y-Axis
//INPUT	  : SHORT newVal	--	Number of grids 
//ASSUMES : 
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::SetYGrids(SHORT newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here

	m_chart.Repaint();//  After drawing data points and then Immediately Call this function, This fn will not give below max and min values
	// and will not draw the Grids to the specified  number,if this 'Repiaint' method is called first.
	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes	=	pDisp;
	pDisp->Release();
	IAxisPtr pLeft	=	pAxes->GetLeft();

	double dblMin,dblMax;
	dblMin	=	pLeft->GetMinimum();
	dblMax	=	pLeft->GetMaximum();

	m_intYNumOfGrids	=	newVal;

	pLeft->Increment	=	(dblMax	-	dblMin)/newVal;

	pLeft	=	NULL;
	pAxes	=	NULL;


	SetModifiedFlag();
}

//*************************************************
//PURPOSE : Method to programatically zoom the specified region
//			DOUBLE dblXMin	--	minimum X position from where zoom has to be started
//			DOUBLE dblXMax	--	Maximum X position of the area that has to be zoomed
//			DOUBLE dblYMin	--	minimum Y position from where zoom has to be started
//			DOUBLE dblYMax	--	Maximum Y position of the area that has to be zoomed
//ASSUMES : 
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
VARIANT_BOOL CEsdAdvancedGraphCtrl::ZoomIn(DOUBLE dblXMin, DOUBLE dblXMax, DOUBLE dblYMin, DOUBLE dblYMax)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	if(m_bAutoRangeEnable==FALSE) // If Auto range is not enabled then only Zooming can be performed
	{
		LPDISPATCH pDisp	=	m_chart.get_Zoom();
		IZoomPtr pZoom		=	pDisp;
		pDisp->Release();

		pZoom->ZoomRect((LONG)dblXMin,(LONG)dblXMax,(LONG)dblYMin,(LONG)dblYMax);
		pZoom	=	NULL;
	}

	return VARIANT_TRUE;
}

//*************************************************
//PURPOSE : Method to unzoom 
//			
//			
//ASSUMES : 
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::ZoomOut(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	LPDISPATCH pDisp	=	m_chart.get_Zoom();
	IZoomPtr pZoom		=	pDisp;
	pDisp->Release();

	pZoom->Undo();
	pZoom	=	NULL;

}

//*************************************************
//PURPOSE : Sets the font name and size for the text used to
//			display the header of the control
//INPUT   :	LPCTSTR	strFontName		--	Name of the font
//			LONG lngFontSize		--	Size of the font
//ASSUMES : -
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::SetHeaderFont(LPCTSTR strFontName, LONG lngFontSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	LPDISPATCH pDisp	=	m_chart.get_Header();
	ITitlesPtr pHeader	=	pDisp;
	pDisp->Release();
	pHeader->GetFont()->Name	=	_bstr_t(strFontName);
	pHeader->GetFont()->Size	=	lngFontSize;

	pHeader	=	NULL;
}

//*************************************************
//PURPOSE : Method to set the Font name and size for the
//			Axes Titles		
//			
//ASSUMES : 
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa.S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::SetAxesTitlesFont(LPCTSTR strFontName, LONG lngFontSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	//Set the font name and font size for the X-Axis Marking
	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes	=	pDisp;
	pDisp->Release();

	pAxes->GetBottom()->GetTitle()->GetFont()->Name		=	_bstr_t(strFontName);
	pAxes->GetBottom()->GetTitle()->GetFont()->Size		=	lngFontSize;

	//Set the font name and font size for the Y-Axis Marking
	pAxes->GetLeft()->GetTitle()->GetFont()->Name	=	_bstr_t(strFontName);
	pAxes->GetLeft()->GetTitle()->GetFont()->Size	=	lngFontSize;

	pAxes	=	NULL;

}
//*************************************************
//PURPOSE : Method to set the custom text and position
//INPUTS  : LPCTSTR bstrText	   -	Custom Text
//          LONG lngLeftMargin	   -	XMargin
//			LONg lngRightMargin	   -	YMargin 
//ASSUMES : -
//RETURNS : - 
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::DisplayText(LPCTSTR bstrText, LONG lngLeftMargin, LONG lngRightMargin)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// TODO: Add your dispatch handler code here

	EsdCUSTOMTEXT_STRUCT* text = new EsdCUSTOMTEXT_STRUCT;   // Create a new Custom Text object.
	text->strCustomText	=	bstrText;								 // Set the text.	
	text->clrTextColor  = m_clrCustomTextColor;
	text->lngXmargin    = lngLeftMargin;				 // Set the X & Y locations 	
	text->lngYmargin    = lngRightMargin;

	m_objCustomText.Add(text);								 // Save the address of the newly created Custom text object.	
	m_chart.Repaint();					// Call to 'OnAfterDrawTChart'
}

//*************************************************
//PURPOSE : Method to display the custom text at specified location.
//INPUTS  : -
//ASSUMES : -
//RETURNS : -
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::prcDisplayCustomText(void)
{	
	int nSize=(int)m_objCustomText.GetSize();
	if(nSize > 0) // If Custom text exists
	{	
		int nCustomTxtWdth,nCustomTextHt; // Holds the Custom text Width and Height

		LPDISPATCH pDisp	=	m_chart.get_Canvas();		
		ICanvasPtr pCanvas = pDisp;
		pDisp->Release();

		pDisp	=	m_chart.get_Aspect();
		IAspectPtr	pAspect	=	pDisp;
		pDisp->Release();
		EsdCUSTOMTEXT_STRUCT *text	=	NULL;

		for(int i=0;i<nSize;i++)
		{
			text	=	m_objCustomText.GetAt(i);
			pCanvas->GetFont()->PutColor(m_clrCustomTextColor);
			pCanvas->PutBackMode(cbmTransparent);

			// If 3D mode is enabled use 3D methods to display text, otherwise use 2D Methods
			if(pAspect->View3D==VARIANT_TRUE)// If 3D enabled
			{
				_bstr_t bstr	=	text->strCustomText;
				nCustomTxtWdth	=	pCanvas->TextWidth(bstr);
				nCustomTextHt	=	pCanvas->TextHeight(bstr);
				long lngXCord	=	text->lngXmargin;
				long lngYCord	=	text->lngYmargin;
				long lngZCord	=	pAspect->GetChart3DPercent()/4;

				pCanvas->TextOut3D(lngXCord/*-nCustomTxtWdth/2*/,lngYCord-nCustomTextHt,lngZCord,bstr);

			}
			else if(pAspect->View3D==VARIANT_FALSE) // if 3D not enabled
			{
				_bstr_t bstr	=	text->strCustomText;
				nCustomTxtWdth	=	pCanvas->TextWidth(bstr);
				nCustomTextHt	=	pCanvas->TextHeight(bstr);
				long lngXCord	=	text->lngXmargin;
				long lngYCord	=	text->lngYmargin;
				if(lngXCord<m_chart.get_Left())
					lngXCord	=	m_chart.get_Left();
				if(lngXCord > m_chart.get_Width())
					lngXCord	=	m_chart.get_Height();
				if(lngYCord	<	m_chart.get_Top())
					lngYCord	=	m_chart.get_Top();
				if(lngYCord	>	m_chart.get_Height())
					lngYCord	=	m_chart.get_Height();
				pCanvas->TcTextOut(lngXCord,lngYCord,bstr);
			}
			text=NULL;	
		}
		pCanvas	=	NULL;
		pAspect	=	NULL;
	}

}
//*************************************************
//PURPOSE : Method to clear the custom text
//INPUTS  : -
//ASSUMES : -
//RETURNS : - 
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::ClearCustomText(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	if(m_objCustomText.GetSize()>0)
	{
		m_objCustomText.RemoveAll();		// Clear the m_objCustomText( CArray variable). 
		m_objCustomText.FreeExtra();		
	}

	if(m_objPlotAreaText.GetSize()>0)
	{		
		blnCustomText	=	FALSE;	// to stop unnecessary checking in 'OnAfterDrawTChart'
		m_objPlotAreaText.RemoveAll();		//	Clear the Plot Area Custom Text.
		m_objPlotAreaText.FreeExtra();
	}

	m_chart.Repaint();	// call to 'OnAfterDrawTChart'
}

//*************************************************
//PURPOSE : Returns the peak width calculation type
//INPUTS  : -
//ASSUMES : -
//RETURNS : SHORT	--	Calculation type 
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
SHORT CEsdAdvancedGraphCtrl::GetPeakWidthCalculationType(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	return m_intPeakWidthCalType;
}

//*************************************************
//PURPOSE : Sets the type of the peak width calculation (Default is '1')
//INPUTS  : SHORT newVal	--	Calculation type
//				newVal	=	1	---		Pt-to-pt Calculation
//				newVal	=	2	---		FWHM(Full width Half Maximum) type calculation
//				newVal	=	3	---		Width at 0.65% calculation type
//ASSUMES : -
//RETURNS : - 
//EFFECTS : -
//AUTHOR  : Silpa S
//DATE    : 
//MODIFICATION HISTORY :
//RevNo  Date        Author    Brief Description
//-----  --------    ------    -----------------
//N      dd-mm-yy    XX		   
//-------------------------------------------------
void CEsdAdvancedGraphCtrl::SetPeakWidthCalculationType(SHORT newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	if(newVal >0 && newVal <4)	
		m_intPeakWidthCalType = newVal;	
	else
	{
		MessageBox(_T("Peak Width Calculation Type Value must be within 1 to 3."));
		return;
	}

	SetModifiedFlag();
}


void CEsdAdvancedGraphCtrl::WidthAt5PercentHeight(LONG lngPos, DOUBLE* dblWidth, DOUBLE* dblLeftWidth, DOUBLE* dblRightWidth)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	*dblWidth = m_dblWidthAt5PercentHeight.GetAt(lngPos);
	*dblLeftWidth=m_dblLeftWidthAt5PercentHeight.GetAt(lngPos);
	*dblRightWidth=m_dblRightWidthAt5PercentHeight.GetAt(lngPos);

	// TODO: Add your dispatch handler code here
}

void CEsdAdvancedGraphCtrl::WidthAt10PercentHeight(LONG lngPos, DOUBLE* dblWidth, DOUBLE* dblLeftWidth, DOUBLE* dblRightWidth)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	*dblWidth = m_dblWidthAt10PercentHeight.GetAt(lngPos);
	*dblLeftWidth = m_dblLeftWidthAt10PercentHeight.GetAt(lngPos);
	*dblRightWidth=m_dblRightWidthAt10PercentHeight.GetAt(lngPos);
	// TODO: Add your dispatch handler code here
}

void CEsdAdvancedGraphCtrl::WidthAtHalfHeight(LONG lngPos, DOUBLE* dblWidth, DOUBLE* dblLeftWidth, DOUBLE* dblRightWidth)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	*dblWidth = m_dblWidthAtHalfHeight.GetAt(lngPos);
	*dblLeftWidth=m_dblLeftWidthAtHalfHeight.GetAt(lngPos);
	*dblRightWidth=m_dblRightWidthAtHalfHeight.GetAt(lngPos);

	// TODO: Add your dispatch handler code here
}

void CEsdAdvancedGraphCtrl::prcCalculatePoints(POINT &pt1, POINT &pt2)
{
	LPDISPATCH pDisp	=	m_chart.get_Axis();	// Get the Axes pointer 
	IAxesPtr pAxes	=	pDisp;
	pDisp->Release();

	// Store the Axes minimum and maximum values.
	m_lngXmin	=	pAxes->GetBottom()->CalcXPosValue(pAxes->GetBottom()->Minimum);
	m_lngXmax	=	pAxes->GetBottom()->CalcXPosValue(pAxes->GetBottom()->Maximum);

	m_lngYmax	=	pAxes->GetLeft()->CalcYPosValue(pAxes->GetLeft()->Minimum); // GetLeft()->Minimum means it gives the coords from bottom
	m_lngYmin	=	pAxes->GetLeft()->CalcYPosValue(pAxes->GetLeft()->Maximum);

	pAxes	=	NULL;

	if((pt2.x-pt1.x)==0)      // Case for line parallel to Y - Axis.
	{
		if(pt1.y<m_lngYmin)
			pt1.y = m_lngYmin;
		if(pt2.y<m_lngYmin)
			pt2.y = m_lngYmin;
		if(pt1.y>m_lngYmax)
			pt1.y = m_lngYmax;
		if(pt2.y>m_lngYmax)
			pt2.y = m_lngYmax;
	}

	if((pt2.y-pt1.y)==0)    // Case for line parallel to X - Axis.
	{
		if(pt1.x<m_lngXmin)
			pt1.x = m_lngXmin;
		if(pt2.x<m_lngXmin)
			pt2.x = m_lngXmin;
		if(pt1.x>m_lngXmax)
			pt1.x = m_lngXmax;
		if(pt2.x>m_lngXmax)
			pt2.x = m_lngXmax;
	}

	//								 (x2,y2)
	//								   Q	
	//								  /	
	//			---------------------Z-------- Y-min
	//			|	|	 |	 |	  |	/  |	|
	//			|	|	 |	 |	  |/   |    |
	//			|---|----|---|----|----|----|
	//			|	|	 |	 |	 /|    |	|										
	//			|	|	 |	 |	/ |    |    |
	//			|---|----|---|-/--|----|----|Y - Axis   // Here is the Z is the new point to be calculated.
	// 			|	|	 |	 |/	  |	   |	|           // This can be obtained from the line equation: Y-y1 = M(X-x1)
	//			|	|	 |	 |	  |	   |	|			// where M = (y2-y1)/(x2-x1)
	//			|---|----|--/|----|----|----|
	//			|	| (x1,y/1)    |	   |    |    
	//			|	|	 P	 |	  |    |    |  
	//          -----------------------------Y-max
	//			X-min	                    X-max
	//                   X - Axis	


	if((pt2.x-pt1.x)!=0)   
	{
		double dblSlope = ((double)(pt2.y-pt1.y))/((double)(pt2.x-pt1.x));

		double dblC		=	((double)pt1.y) - (dblSlope * pt1.x);

		if(pt1.y>m_lngYmax)
		{
			if(dblSlope!=0)
				pt1.x = (m_lngYmax-pt2.y)/dblSlope+pt2.x;
			pt1.y = m_lngYmax;

		}

		if(pt1.y<m_lngYmin)
		{
			if(dblSlope!=0)
				pt1.x = (m_lngYmin-pt2.y)/dblSlope +pt2.x;
			pt1.y = m_lngYmin;
		}

		if(pt1.x<m_lngXmin)
		{
			pt1.x = m_lngXmin;
			pt1.y = dblSlope*(m_lngXmin-pt2.x)+pt2.y;
		}

		if(pt1.x>m_lngXmax)
		{
			pt1.x=m_lngXmax;
			pt1.y=dblSlope*(m_lngXmax-pt2.x)+pt2.y;
		}

		if(pt2.y>m_lngYmax)
		{
			if(dblSlope!=0)
				pt2.x = ((m_lngYmax-pt1.y)/dblSlope)+pt1.x;			
			pt2.y = m_lngYmax;
		}

		if(pt2.y<m_lngYmin)
		{
			if(dblSlope!=0)
				pt2.x = ((m_lngYmin-pt1.y)/dblSlope)+pt1.x;
			pt2.y = m_lngYmin;
		}

		if(pt2.x<m_lngXmin)
		{
			pt2.x = m_lngXmin;
			pt2.y = dblSlope*(m_lngXmin-pt1.x)+pt1.y;
		}

		if(pt2.x>m_lngXmax)
		{
			pt2.x = m_lngXmax;
			pt2.y = dblSlope*(m_lngXmax-pt1.x)+pt1.y;
		}	
	}		

}
//17/04/08
//LONG CEsdAdvancedGraphCtrl::AddCustomAxis(VARIANT_BOOL blnIsHorizontal)
//{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
//
//	// TODO: Add your dispatch handler code here
//
//	LPDISPATCH pDisp	=	m_chart.get_Axis();
//	IAxesPtr pAxes		=	pDisp;
//	pDisp->Release();
//
//	long lngAxisIdx	=	-1;
//
//	lngAxisIdx	=	pAxes->AddCustom(blnIsHorizontal);
//
//	pAxes	=	NULL;
//
//	return lngAxisIdx;
//}
void CEsdAdvancedGraphCtrl::MoveAxisFromBasePosition(LONG lngAxisIdx, LONG lngPositionInPercent,VARIANT_BOOL blnIsStdAxis)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	if(lngAxisIdx<0)
	{
		AfxMessageBox(_T("Axis index must be a positive Number"));
		return;
	}
	if(lngPositionInPercent<0 || lngPositionInPercent>100)
	{
		AfxMessageBox(_T("Axis Position value must be 0-100"));
		return;
	}
	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes		=	pDisp;
	pDisp->Release();

	if(!blnIsStdAxis)// Is given Axis idx is Custom Axis idx
	{	
		pAxes->GetCustom(lngAxisIdx)->PositionUnits	=	puPercent;
		pAxes->GetCustom(lngAxisIdx)->PositionPercent	=	lngPositionInPercent;
	}
	if(blnIsStdAxis)// If given axis idx is standard Axis(i.e Left,Bottom,Right,top Axes) idx
	{
		switch(lngAxisIdx)
		{
		case 1:
			pAxes->GetLeft()->PositionUnits	=	puPercent;
			pAxes->GetLeft()->PositionPercent	=	lngPositionInPercent;
			break;
		case 2:
			pAxes->GetBottom()->PositionUnits	=	puPercent;
			pAxes->GetBottom()->PositionPercent	=	lngPositionInPercent;
			break;
		default:
			AfxMessageBox(_T("Standard Axis index value must be b/n 1-2"));
			break;
		}
	}
	pAxes	=	NULL;
}

void CEsdAdvancedGraphCtrl::ChangeAxisStartPosition(LONG lngAxisIdx, LONG lngPositionInPercent, VARIANT_BOOL blnIsStdAxis)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	if(lngAxisIdx<0)
	{
		AfxMessageBox(_T("Axis index must be a positive Number"));
		return;
	}
	if(lngPositionInPercent<0 || lngPositionInPercent>100)
	{
		AfxMessageBox(_T("Axis Position value must be 0-100"));
		return;
	}
	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes		=	pDisp;
	pDisp->Release();

	if(!blnIsStdAxis)// If given axis idx is Custom Axis idx
	{
		pAxes->GetCustom(lngAxisIdx)->PositionUnits	=	puPercent;
		pAxes->GetCustom(lngAxisIdx)->StartPosition	=	lngPositionInPercent;

	}
	if(blnIsStdAxis)// If given axis idx is standard Axis(i.e Left,Bottom,Right,top Axes) idx
	{
		switch(lngAxisIdx)
		{
		case 1:
			pAxes->GetLeft()->PositionUnits	=	puPercent;
			pAxes->GetLeft()->StartPosition	=	lngPositionInPercent;
			break;
		case 2:
			pAxes->GetBottom()->PositionUnits	=	puPercent;
			pAxes->GetBottom()->StartPosition	=	lngPositionInPercent;
			break;
		default:
			AfxMessageBox(_T("Standard Axis index value must be b/n 1-2"));
			break;
		}

	}
	pAxes	=	NULL;
}

void CEsdAdvancedGraphCtrl::ChangeAxisEndPosition(LONG lngAxisIdx, LONG lngPositionInPercent, VARIANT_BOOL blnIsStdAxis)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	if(lngAxisIdx<0)
	{
		AfxMessageBox(_T("Axis index must be a positive Number"));
		return;
	}
	if(lngPositionInPercent<0 || lngPositionInPercent>100)
	{
		AfxMessageBox(_T("Axis Position value must be 0-100"));
		return;
	}
	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes		=	pDisp;
	pDisp->Release();

	if(!blnIsStdAxis)// If given axis idx is Custom Axis idx
	{
		pAxes->GetCustom(lngAxisIdx)->PositionUnits	=	puPercent;
		pAxes->GetCustom(lngAxisIdx)->EndPosition	=	lngPositionInPercent;

	}
	if(blnIsStdAxis)// If given axis idx is standard Axis(i.e Left,Bottom,Right,top Axes) idx
	{
		switch(lngAxisIdx)
		{
		case 1:
			pAxes->GetLeft()->PositionUnits	=	puPercent;
			pAxes->GetLeft()->EndPosition	=	lngPositionInPercent;
			break;
		case 2:
			pAxes->GetBottom()->PositionUnits	=	puPercent;
			pAxes->GetBottom()->EndPosition	=	lngPositionInPercent;
			break;
		default:
			AfxMessageBox(_T("Standard Axis index value must be b/n 1-2"));
			break;
		}
	}
	pAxes	=	NULL;
}

void CEsdAdvancedGraphCtrl::AssignAxesForGraph(LONG lngGraphIdx, LONG lngCustomHorzAxis, LONG lngCustomVertAxis)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	LPDISPATCH pDisp	=	m_chart.Series(lngGraphIdx);
	ISeriesPtr pSeries	=	pDisp;
	pDisp->Release();	
	_bstr_t bstrGraphName	=	pSeries->Name;
	long lngIdx	=	GetLtblIdxFromName(bstrGraphName);
	if(lngIdx<0 || lngGraphIdx>=m_chart.get_SeriesCount())
	{
		AfxMessageBox(_T("Graph with specified index does not exist"));
		pSeries	=	NULL;
		return;
	}


	pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes		=	pDisp;
	pDisp->Release();


	if(lngCustomHorzAxis>=0 && lngCustomHorzAxis < pAxes->CustomCount)
	{
		pSeries->HorizontalAxisCustom	=	lngCustomHorzAxis;
	}
	else
	{
		AfxMessageBox(_T("Custom Horizontal Axis with Specified index doesn't exist"));
	}
	if(lngCustomVertAxis>=0 && lngCustomVertAxis < pAxes->CustomCount)
	{
		pSeries->VerticalAxisCustom	=	lngCustomVertAxis;
	}
	else
	{
		AfxMessageBox(_T("Custom Vertical Axis with Specified index doesn't exist"));
	}


	/*long lng	=	pSeries->HorizontalAxis;
	CString str;
	str.Format(_T("Vert Axis=%ld"),lng);
	AfxMessageBox(str);*/
	pSeries	=	NULL;
	pAxes	=	NULL;
}

void CEsdAdvancedGraphCtrl::RemoveCustomAxis(LONG lngCustomAxisIdx)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes		=	pDisp;
	pDisp->Release();
	if(lngCustomAxisIdx>=0 && lngCustomAxisIdx < pAxes->CustomCount)
	{
		pAxes->RemoveCustom(lngCustomAxisIdx);
	}
	else
	{
		AfxMessageBox(_T("Custom Axis with Specified index doesn't exist"));
	}

	pAxes	=	NULL;
}

void CEsdAdvancedGraphCtrl::RemoveAllCustomAxes(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes		=	pDisp;
	pDisp->Release();

	if(pAxes->CustomCount>0)
	{
		pAxes->RemoveAllCustom();
	}
	pAxes	=	NULL;
}

LONG CEsdAdvancedGraphCtrl::AddCustomAxis(VARIANT_BOOL blnIsHorizontal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes		=	pDisp;
	pDisp->Release();

	long lngAxisIdx	=	-1;

	lngAxisIdx	=	pAxes->AddCustom(blnIsHorizontal);

	pAxes	=	NULL;

	return lngAxisIdx;
}
BSTR CEsdAdvancedGraphCtrl::GetCustomAxisTitle(LONG lngAxisIdx)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: Add your dispatch handler code here
	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes		=	pDisp;
	pDisp->Release();
	bstr_t bstrTitle	=	_T("");
	if(lngAxisIdx<0 && lngAxisIdx>=pAxes->CustomCount)
	{
		pAxes	=	NULL;
		AfxMessageBox(_T("Custom Axis with this index doesn't exist"));
		return bstrTitle;
	}
	bstrTitle	=	pAxes->GetCustom(lngAxisIdx)->GetTitle()->Caption;

	pAxes	=	NULL;

	return bstrTitle;
}

void CEsdAdvancedGraphCtrl::SetCustomAxisTitle(LONG lngAxisIdx, LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here

	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes		=	pDisp;
	pDisp->Release();
	if(lngAxisIdx<0 && lngAxisIdx>=pAxes->CustomCount)
	{
		pAxes	=	NULL;
		AfxMessageBox(_T("Custom Axis with this index doesn't exist"));
		return;
	}

	//_bstr_t bstrTitle	=	newVal;
	pAxes->GetCustom(lngAxisIdx)->GetTitle()->Caption	=	newVal;

	pAxes	=	NULL;

	SetModifiedFlag();
}

DOUBLE CEsdAdvancedGraphCtrl::GetCustomAxisMaximum(LONG lngAxisIdx)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes		=	pDisp;
	pDisp->Release();
	double dblAxisMaximum	=	0;
	if(lngAxisIdx<0 && lngAxisIdx>=pAxes->CustomCount)
	{
		pAxes	=	NULL;
		AfxMessageBox(_T("Custom Axis with this index doesn't exist"));
		return dblAxisMaximum;
	}

	dblAxisMaximum	=	pAxes->GetCustom(lngAxisIdx)->Maximum;
	pAxes	=	NULL;

	return dblAxisMaximum;
}

void CEsdAdvancedGraphCtrl::SetCustomAxisMaximum(LONG lngAxisIdx, DOUBLE newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes		=	pDisp;
	pDisp->Release();
	if(lngAxisIdx<0 && lngAxisIdx>=pAxes->CustomCount)
	{
		pAxes	=	NULL;
		AfxMessageBox(_T("Custom Axis with this index doesn't exist"));
		return;
	}

	pAxes->GetCustom(lngAxisIdx)->AutomaticMaximum	=	FALSE;
	pAxes->GetCustom(lngAxisIdx)->Maximum	=	newVal;
	pAxes	=	NULL;

	SetModifiedFlag();
}

DOUBLE CEsdAdvancedGraphCtrl::GetCustomAxisMinimum(LONG lngAxisIdx)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes		=	pDisp;
	pDisp->Release();
	double dblAxisMinimum	=	0;
	if(lngAxisIdx<0 && lngAxisIdx>=pAxes->CustomCount)
	{
		pAxes	=	NULL;
		AfxMessageBox(_T("Custom Axis with this index doesn't exist"));
		return	dblAxisMinimum;
	}

	dblAxisMinimum	=	pAxes->GetCustom(lngAxisIdx)->Maximum;
	pAxes	=	NULL;

	return dblAxisMinimum;
}

void CEsdAdvancedGraphCtrl::SetCustomAxisMinimum(LONG lngAxisIdx, DOUBLE newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes		=	pDisp;
	pDisp->Release();
	if(lngAxisIdx<0 && lngAxisIdx>=pAxes->CustomCount)
	{
		pAxes	=	NULL;
		AfxMessageBox(_T("Custom Axis with this index doesn't exist"));
		return;
	}

	pAxes->GetCustom(lngAxisIdx)->AutomaticMinimum	=	FALSE;
	pAxes->GetCustom(lngAxisIdx)->Minimum	=	newVal;
	pAxes	=	NULL;

	SetModifiedFlag();
}

LONG CEsdAdvancedGraphCtrl::GetCustomAxisGrids(LONG lngAxisIdx)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	return 0;
}

void CEsdAdvancedGraphCtrl::SetCustomAxisGrids(LONG lngAxisIdx, LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	m_chart.Repaint(); //  After drawing data points and then Immediately Call this function, This fn will not give below max and min values
	// and will not draw the Grids to the specified  number,if this 'Repiaint' method is called first.

	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes		=	pDisp;
	pDisp->Release();

	if(lngAxisIdx<0 && lngAxisIdx>=pAxes->CustomCount)
	{
		pAxes	=	NULL;
		AfxMessageBox(_T("Custom Axis with this index doesn't exist"));
		return;
	}
	double dblMin,dblMax;
	dblMin	=	pAxes->GetCustom(lngAxisIdx)->GetMinimum();
	dblMax	=	pAxes->GetCustom(lngAxisIdx)->GetMaximum();

	m_intXNumOfGrids	=	newVal;
	pAxes->GetCustom(lngAxisIdx)->Increment	=	(dblMax	-	dblMin)/newVal;

	pAxes	=	NULL;


	SetModifiedFlag();
}

LONG CEsdAdvancedGraphCtrl::GetCustomAxisTitleAngle(LONG lngAxisIdx)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes		=	pDisp;
	pDisp->Release();

	double dblAngle	=	-1;
	if(lngAxisIdx<0 && lngAxisIdx>=pAxes->CustomCount)
	{
		pAxes	=	NULL;
		AfxMessageBox(_T("Custom Axis with this index doesn't exist"));
		return dblAngle;
	}
	dblAngle	=	pAxes->GetCustom(lngAxisIdx)->GetTitle()->Angle;
	pAxes	=	NULL;

	return dblAngle;
}

void CEsdAdvancedGraphCtrl::SetCustomAxisTitleAngle(LONG lngAxisIdx, LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	LPDISPATCH pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes		=	pDisp;
	pDisp->Release();

	if(lngAxisIdx<0 && lngAxisIdx>=pAxes->CustomCount)
	{
		pAxes	=	NULL;
		AfxMessageBox(_T("Custom Axis with this index doesn't exist"));
		return;
	}
	if(newVal<0 || newVal>360)
	{
		pAxes	=	NULL;
		AfxMessageBox(_T("Angle must be between 0-360"));
		return;

	}

	pAxes->GetCustom(lngAxisIdx)->GetTitle()->Angle	=	newVal;
	pAxes	=	NULL;
	SetModifiedFlag();
}

// Calculates the rectangle of the graph
void CEsdAdvancedGraphCtrl::CalculateGraphRect(long lngGraphIdx,long *lngLeft, long *lngTop, long *lngRight, long *lngBottom)
{
	////	AfxMessageBox(_T("CalculateGraphRect"));
	//long lngTempLeft,lngTempTop,lngTempRight,lngTempBottom;

	//lngTempLeft	=	lngTempTop	=	lngTempRight	=	lngTempBottom	=	0;
	//LPDISPATCH pDisp	=	m_chart.Series(lngGraphIdx);
	//ISeriesPtr pSeries	=	pDisp;
	//pDisp->Release();
	//pDisp	=	m_chart.get_Axis();
	//IAxesPtr pAxes	=	pDisp;
	//pDisp->Release();

	//lngTempTop		=	pAxes->GetTop()->Position;
	//lngTempRight	=	pAxes->GetRight()->Position;
	///*if(pSeries->VerticalAxis	==	aCustomVertAxis)
	//{
	//long lngCustomVertaAxisIdx	=	pSeries->VerticalAxisCustom;
	//lngTempLeft	=	pAxes->GetCustom(lngCustomVertaAxisIdx)->Position;
	//}
	//if(pSeries->HorizontalAxis	==	aCustomHorizAxis)
	//{		
	//long lngCustomHorzAxisIdx	=	pSeries->HorizontalAxisCustom;
	//lngTempBottom	=	pAxes->GetCustom(lngCustomHorzAxisIdx);
	//}*/

	//if(pSeries->HorizontalAxis	==	aBottomAxis)
	//	lngTempBottom	=	pAxes->GetBottom()->Position;
	//else
	//{
	//	long lngCustomHorzAxisIdx	=	pSeries->HorizontalAxisCustom;
	//	lngTempBottom	=	pAxes->GetCustom(lngCustomHorzAxisIdx)->Position;	
	//}

	//long lngStart,lngEnd,temp;
	//CString str;
	//if(pSeries->VerticalAxis	==	aLeftAxis)
	//{
	//	lngTempLeft		=	pAxes->GetLeft()->Position;
	//	lngStart			=	pAxes->GetLeft()->StartPosition;
	//	lngEnd			=	pAxes->GetLeft()->EndPosition;

	//	temp			=	((lngTempBottom-lngTempTop)*((100-lngStart)/100.0));
	//	lngTempTop		=	lngTempBottom-temp;//(lngTempTop+temp);/*-lngTempTop*/;//(lngStart/100)*lngTempTop;
	//	temp			=	lngTempBottom*((100-lngEnd)/100.0);//lntempend;	
	//	lngTempBottom		=	lngTempBottom-temp + 15;//'15' is Just like OffSet

	//}
	//else
	//{
	//	long lngCustomVertaAxisIdx	=	pSeries->VerticalAxisCustom;
	//	lngTempLeft		=	pAxes->GetCustom(lngCustomVertaAxisIdx)->Position;
	//	lngStart		=	pAxes->GetCustom(lngCustomVertaAxisIdx)->StartPosition;
	//	lngEnd			=	pAxes->GetCustom(lngCustomVertaAxisIdx)->EndPosition;

	//	temp			=	((lngTempBottom-lngTempTop)*((100-lngStart)/100.0));	
	//	lngTempTop		=	lngTempBottom-temp;//(lngTempTop+temp);//+= /*lngTempBottom-*/(lngTempTop*((100-lngStart)/100))/*-lngTempTop*/;
	//	temp			=	lngTempBottom*((100-lngEnd)/100.0);
	//	lngTempBottom		=	lngTempBottom-temp +12;//'12' is Just like OffSet
	//}
	//*lngLeft	=	lngTempLeft;
	//*lngTop		=	lngTempTop;
	//*lngRight	=	lngTempRight;
	//*lngBottom	=	lngTempBottom;
	//pSeries	=	NULL;
	//pAxes	=	NULL;

	//////////////////////////////////////////////////////////////////////
	long lngTempLeft,lngTempTop,lngTempRight,lngTempBottom;

	lngTempLeft	=	lngTempTop	=	lngTempRight	=	lngTempBottom	=	0;
	LPDISPATCH pDisp	=	m_chart.Series(lngGraphIdx);
	ISeriesPtr pSeries	=	pDisp;
	pDisp->Release();
	pDisp	=	m_chart.get_Axis();
	IAxesPtr pAxes	=	pDisp;
	pDisp->Release();

	/////////////////////////////////////  Added on 21/11/08  /////////////////////////////////////////////////////
	lngTempLeft		=	pAxes->GetLeft()->Position;
	lngTempRight	=	pAxes->GetRight()->Position;
	if(pSeries->VerticalAxis	==	aLeftAxis)
	{
		lngTempTop		=	pAxes->GetLeft()->IStartPos;
		lngTempBottom	=	pAxes->GetLeft()->IEndPos;
	}
	else
	{
		long lngCustomVertaAxisIdx	=	pSeries->VerticalAxisCustom;
		lngTempTop		=	pAxes->GetCustom(lngCustomVertaAxisIdx)->IStartPos;
		lngTempBottom	=	pAxes->GetCustom(lngCustomVertaAxisIdx)->IEndPos;
	}
	/////////////////////////////////////  Added on 21/11/08  /////////////////////////////////////////////////////
	*lngLeft	=	lngTempLeft;
	*lngTop		=	lngTempTop+1;
	*lngRight	=	lngTempRight;
	*lngBottom	=	lngTempBottom-1;
	pSeries	=	NULL;
	pAxes	=	NULL;
}

void CEsdAdvancedGraphCtrl::DoGraphReprocess(BYTE* ptrStEventInfo, LONG lngStructSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// TODO: Add your dispatch handler code here

	m_ptrEventInfo = (stEventInfo*)ptrStEventInfo;
	m_lngEventCount = lngStructSize;
	if (m_lngEventCount==0)
	{
		return;
	}

	//arrays used in NEGATIVE PEAK ON 
	m_arrNegativeStartIndex.RemoveAll();
	m_arrNegativeStartIndex.FreeExtra();
	m_arrNegativeEndIndex.RemoveAll();
	m_arrNegativeEndIndex.FreeExtra();
	m_arrTangentPeakIndex.RemoveAll();
	m_arrTangentPeakIndex.FreeExtra();
	m_dblTangentStartPoint.RemoveAll();
	m_dblTangentStartPoint.FreeExtra();

	for(int iEvent = 0;iEvent<lngStructSize;iEvent++)
	{

		if(m_ptrEventInfo[iEvent].dwEventCode==1)//force base
			fncForceBaseMethod(m_ptrEventInfo[iEvent].dblStartTime,m_ptrEventInfo[iEvent].dblEndTimeOrValue,m_ptrEventInfo[iEvent].dblEndTimeOrValue);
		if(m_ptrEventInfo[iEvent].dwEventCode==2)//base at next valley
			fncBaseAtNextValleyMethod(m_ptrEventInfo[iEvent].dblStartTime,m_ptrEventInfo[iEvent].dblEndTimeOrValue,m_ptrEventInfo[iEvent].dblEndTimeOrValue);
		if(m_ptrEventInfo[iEvent].dwEventCode==3)
			fncValleyToValleyMethod(m_ptrEventInfo[iEvent].dblStartTime,m_ptrEventInfo[iEvent].dblEndTimeOrValue,m_ptrEventInfo[iEvent].dblEndTimeOrValue);
		if (m_ptrEventInfo[iEvent].dwEventCode == 4)
			fncHorizontalBaselineMethod(m_ptrEventInfo[iEvent].dblStartTime,m_ptrEventInfo[iEvent].dblEndTimeOrValue,m_ptrEventInfo[iEvent].dblEndTimeOrValue);
		if (m_ptrEventInfo[iEvent].dwEventCode == 5)
			fncPenetrationWithNegativePeakMethod(m_ptrEventInfo[iEvent].dblStartTime,m_ptrEventInfo[iEvent].dblEndTimeOrValue,m_ptrEventInfo[iEvent].dblEndTimeOrValue);
		if (m_ptrEventInfo[iEvent].dwEventCode == 0)
			fncStartDetect(m_ptrEventInfo[iEvent].dblStartTime,m_ptrEventInfo[iEvent].dblEndTimeOrValue,m_ptrEventInfo[iEvent].dblEndTimeOrValue);
		if (m_ptrEventInfo[iEvent].dwEventCode == 6)
			fncTangentSkiming(m_ptrEventInfo[iEvent].dblStartTime,m_ptrEventInfo[iEvent].dblEndTimeOrValue,m_ptrEventInfo[iEvent].dblEndTimeOrValue);
		if (m_ptrEventInfo[iEvent].dwEventCode == 9)
			fncManualBaseline(m_ptrEventInfo[iEvent].dblStartTime,m_ptrEventInfo[iEvent].dblEndTimeOrValue,m_ptrEventInfo[iEvent].dblEndTimeOrValue);
		if (m_ptrEventInfo[iEvent].dwEventCode == 7)
			fncStopDetect(m_ptrEventInfo[iEvent].dblStartTime,m_ptrEventInfo[iEvent].dblEndTimeOrValue,m_ptrEventInfo[iEvent].dblEndTimeOrValue);
		if (m_ptrEventInfo[iEvent].dwEventCode == 8)
			fncForcedPeak(m_ptrEventInfo[iEvent].dblStartTime,m_ptrEventInfo[iEvent].dblEndTimeOrValue,m_ptrEventInfo[iEvent].dblEndTimeOrValue);
	}	

	DefaultBaseLineMethod(m_ptrEventInfo->dblStartTime,m_ptrEventInfo->dblEndTimeOrValue,0);

}

void CEsdAdvancedGraphCtrl::DefaultBaseLineMethod(double dblStartTime, double dblEndTime, double dblValue)
{
	int nPeaksCount =(int) m_objPeakInfo->arrStartPointType.GetSize();

	if(nPeaksCount==0)
		return;

	double dblSLope = 0;
	double YOnBL = 0;

	int nTemp = 0;
	int nTemp1 = 0;
	int nTempI = 0;

	_bstr_t bstrName(_T(""));

	BOOL blnNegativePeak = FALSE;
	if (m_arrNegativeStartIndex.GetSize()>0)
		blnNegativePeak = TRUE;

	double dblXValueAtValley=0;


	LPDISPATCH pDisp	=	NULL;
	ISeriesPtr	pBLSeries,pPLSeries,pVLSeries,pPLSeries1;
	pBLSeries	=	pPLSeries = pVLSeries = pPLSeries1 =  NULL;

	for (int i=0;i<nPeaksCount;i++)
	{                    
		if((m_objPeakInfo->arrStartPointType.GetAt(i) == TYPE_BASE) ||(m_objPeakInfo->arrStartPointType.GetAt(i) == TYPE_PENETRATION))
		{
			long lngSeriesNo	=	m_chart.AddSeries(0); // To hold the Graph ID which is used for BaseLine Drawing

			pDisp = m_chart.Series(lngSeriesNo);
			pBLSeries= pDisp; // Smart pointer for 'Series' interface of series used for Baseline
			pDisp->Release();

			pBLSeries->put_Color(m_clrBaseLineColor);//RGB(0,0,0));
			pBLSeries->ShowInLegend	=	FALSE;

			for(int j=i;j<nPeaksCount;j++)
			{
				if((m_objPeakInfo->arrEndPointType.GetAt(j)== TYPE_BASE) ||(m_objPeakInfo->arrEndPointType.GetAt(j) == TYPE_PENETRATION))
				{

					if(i!=j)
					{

						//calculate the slope of base line
						if ((m_objPeakInfo->dblPeakEndX.GetAt(j) - m_objPeakInfo->dblPeakStartX.GetAt(i)) != 0)
							dblSLope = (m_objPeakInfo->dblPeakEndY.GetAt(j) - m_objPeakInfo->dblPeakStartY.GetAt(i)) / (m_objPeakInfo->dblPeakEndX.GetAt(j) - m_objPeakInfo->dblPeakStartX.GetAt(i));

						int nValleyCount = j - i;
						BOOL blnFound = FALSE;

						int m=0;

						for(int k=1; k<=nValleyCount+1;k++)
						{

							nTemp = i+k-1;

							if(m_objPeakInfo->arrEndPointType.GetAt(i+k-1) == TYPE_VALLEY ||m_objPeakInfo->arrEndPointType.GetAt(i+k-1)==TYPE_BASE || m_objPeakInfo->arrEndPointType.GetAt(i+k-1) == TYPE_PENETRATION)
							{

								//Check for negative peak

								//Get the slope of the line joining the starting base point and current valley end point
								double dblSlopeValley =  (m_objPeakInfo->dblPeakEndY.GetAt(i+k-1)-m_objPeakInfo->dblPeakStartY.GetAt(i)) / (m_objPeakInfo->dblPeakEndX.GetAt(i+k-1)-m_objPeakInfo->dblPeakStartX.GetAt(i));

								if(i+k-1 ==j)
								{
									dblSlopeValley = dblSLope;
								}

								//Compare the slopes 
								if(dblSlopeValley < dblSLope) //Negative peak found
								{
									//Check for Negative Peak ON/OFF
									if (blnNegativePeak == FALSE)  //Negative peak OFF
									{
										m_objPeakInfo->arrStartPointType.SetAt(i+k, TYPE_BASE);
										if (k != 0)
											m_objPeakInfo->arrEndPointType.SetAt(i+k-1, TYPE_BASE);

										//Start the checking for base point from previous position
										j=(i+k-1)-1;
										/*if(nTempI!=0)
										j=nTempI-1;*/


										break;
									}
									else
									{
										//Draw the perpendicular line
										dblXValueAtValley = m_objPeakInfo->dblPeakEndX.GetAt(i+k-1);

										YOnBL = dblSLope * (dblXValueAtValley - m_objPeakInfo->dblPeakStartX.GetAt(i)) + (m_objPeakInfo->dblPeakStartY.GetAt(i));

										long lngPerpendicularNo	=	m_chart.AddSeries(0); // To hold the Graph ID which is used for BaseLine Drawing
										pDisp	=	m_chart.Series(lngPerpendicularNo);
										pPLSeries	=	pDisp;// Smart pointer for 'Series' interface of series used for Baseline
										pDisp->Release();
										pPLSeries->put_Color(RGB(0,0,255));
										pPLSeries->ShowInLegend	=	FALSE;

										//perpendicular line draw
										pPLSeries->AddXY(m_objPeakInfo->dblPeakEndX.GetAt(i+k-1),m_objPeakInfo->dblPeakEndY.GetAt(i+k-1),bstrName,RGB(0,0,255));
										pPLSeries->AddXY(m_objPeakInfo->dblPeakEndX.GetAt(i+k-1),YOnBL,bstrName,RGB(0,0,255));

										//Do calculations on the peak

										//Get the peak start index
										long lngStartIndex = m_objPeakInfo->intPeakStartIndex.GetAt(i+k-1);
										//Get the peak end index
										long lngEndIndex = m_objPeakInfo->intPeakEndIndex.GetAt(i+k-1);
										//Get the index of maximum height in the peak
										long lngMaxHeightIndex = m_objPeakInfo->intPeakMaxIndex.GetAt(i+k-1);
										//Calculate the number of points on peak
										long lngPointCount = lngEndIndex - lngStartIndex +1;
										long lngTempPeakCount = lngPointCount;

										lngPointCount+=2;
										lngTempPeakCount++;



										//Get the peak data
										double* dblXArr = new double[lngPointCount];
										double* dblYArr = new double[lngPointCount];

										int m=0;

										//Add the point on Base line on left side of peak
										if (m_objPeakInfo->arrStartPointType.GetAt(i+k-1) == TYPE_BASE || m_objPeakInfo->arrStartPointType.GetAt(i+k-1)== TYPE_PENETRATION)
										{
											stuPeakDetectPoint objPeakPoint = m_arrPeakDetectPoint.GetAt(lngStartIndex);
											dblXArr[m] = objPeakPoint.X;
											dblYArr[m] = objPeakPoint.Y;//dblSLope * (objPeakPoint.X - m_objPeakInfo->dblPeakStartX.GetAt(i)) + (m_objPeakInfo->dblPeakStartY.GetAt(i));


											m++;
										}

										if (m_objPeakInfo->arrStartPointType.GetAt(i+k-1) == TYPE_VALLEY)
										{

											stuPeakDetectPoint objPeakPoint = m_arrPeakDetectPoint.GetAt(lngStartIndex);
											dblXArr[m] = objPeakPoint.X;
											dblYArr[m] = dblSLope * (m_objPeakInfo->dblPeakEndX.GetAt(i+k-2) - m_objPeakInfo->dblPeakStartX.GetAt(i)) + (m_objPeakInfo->dblPeakStartY.GetAt(i));

											m++;
										}


										for (; m<lngTempPeakCount; m++)
										{
											stuPeakDetectPoint objPeakPoint = m_arrPeakDetectPoint.GetAt(lngStartIndex);
											dblXArr[m] = objPeakPoint.X;
											dblYArr[m] = objPeakPoint.Y;


											lngStartIndex++;
										}

										//Add the point on Base line on right side of peak
										if (m_objPeakInfo->arrEndPointType.GetAt(i+k-1) == TYPE_VALLEY)
										{
											stuPeakDetectPoint objPeakPoint = m_arrPeakDetectPoint.GetAt(lngEndIndex);
											dblXArr[m] = objPeakPoint.X;
											dblYArr[m] = YOnBL;


										}

										if (m_objPeakInfo->arrEndPointType.GetAt(i+k-1) == TYPE_BASE)
										{
											stuPeakDetectPoint objPeakPoint = m_arrPeakDetectPoint.GetAt(lngEndIndex);
											dblXArr[m] = objPeakPoint.X;
											dblYArr[m] = objPeakPoint.Y;
										}

										//Perform Peak calculations
										double dblPeakArea, dblPeakFWHH, dblPeakHeight, dblPeakWidth;
										fncPeakCalculations(lngMaxHeightIndex, dblXArr, dblYArr, lngPointCount,&dblPeakArea, &dblPeakFWHH, &dblPeakHeight, &dblPeakWidth,i+k-1);

										pPLSeries	=	NULL;


									}
								}
								else
								{
									//Draw base line
									pBLSeries->AddXY(m_objPeakInfo->dblPeakStartX.GetAt(i),m_objPeakInfo->dblPeakStartY.GetAt(i),bstrName,RGB(0,0,0));
									pBLSeries->AddXY(m_objPeakInfo->dblPeakEndX.GetAt(j),m_objPeakInfo->dblPeakEndY.GetAt(j),bstrName,RGB(0,0,0));

									long lngPerpendicularNo	=	m_chart.AddSeries(0); // To hold the Graph ID which is used for BaseLine Drawing
									pDisp	=	m_chart.Series(lngPerpendicularNo);
									pPLSeries	=	pDisp;// Smart pointer for 'Series' interface of series used for Baseline
									pDisp->Release();
									pPLSeries->put_Color(RGB(0,0,255));
									pPLSeries->ShowInLegend	=	FALSE;


									dblXValueAtValley = m_objPeakInfo->dblPeakEndX.GetAt(i+k-1);
									YOnBL = dblSLope * (dblXValueAtValley - m_objPeakInfo->dblPeakStartX.GetAt(i)) + (m_objPeakInfo->dblPeakStartY.GetAt(i));

									if(m_objPeakInfo->arrEndPointType.GetAt(i+k-1)== TYPE_VALLEY)
									{
										pPLSeries->AddXY(m_objPeakInfo->dblPeakEndX.GetAt(i+k-1),m_objPeakInfo->dblPeakEndY.GetAt(i+k-1),bstrName,RGB(0,0,255));
										pPLSeries->AddXY(m_objPeakInfo->dblPeakEndX.GetAt(i+k-1),YOnBL,bstrName,RGB(0,0,255));
									}

									//Do calculations on the peak

									//Get the peak start index
									long lngStartIndex; 
									if(m_objPeakInfo->arrStartPointType.GetAt(i+k-1)==TYPE_BKWSKIMMING)
									{
										lngStartIndex = m_objPeakInfo->intPeakStartIndex.GetAt(i);
									}
									else
										lngStartIndex = m_objPeakInfo->intPeakStartIndex.GetAt(i+k-1);



									//Get the peak end index
									long lngEndIndex= m_objPeakInfo->intPeakEndIndex.GetAt(i+k-1);

									//Get the index of maximum height in the peak
									long lngMaxHeightIndex = m_objPeakInfo->intPeakMaxIndex.GetAt(i+k-1);

									//Calculate the number of points on peak
									long lngPointCount = lngEndIndex - lngStartIndex +1;
									long lngTempPeakCount = lngPointCount;

									lngPointCount += 2;
									lngTempPeakCount++;

									//Get the peak data
									double* dblXArr = new double[lngPointCount];
									double* dblYArr = new double[lngPointCount];

									int m=0;

									//Add the point on Base line on left side of peak
									if (m_objPeakInfo->arrStartPointType.GetAt(i+k-1) == TYPE_VALLEY)
									{
										stuPeakDetectPoint objPeakPoint = m_arrPeakDetectPoint.GetAt(lngStartIndex);
										dblXArr[m] = objPeakPoint.X;
										dblYArr[m] = dblSLope * (objPeakPoint.X - m_objPeakInfo->dblPeakStartX.GetAt(i)) + (m_objPeakInfo->dblPeakStartY.GetAt(i));

										m++;
									}
									else
									{
										stuPeakDetectPoint objPeakPoint = m_arrPeakDetectPoint.GetAt(lngStartIndex);
										dblXArr[m] = objPeakPoint.X;
										dblYArr[m] = objPeakPoint.Y;

										m++;
									}

									for (;m<lngTempPeakCount; m++)
									{
										if(lngStartIndex<m_objPeakInfo->intPeakStartIndex.GetAt(i+k-1))
										{
											double dblSlope3 = (m_objPeakInfo->dblPeakStartY.GetAt(i+k-1)-m_objPeakInfo->dblPeakStartY.GetAt(i))/(m_objPeakInfo->dblPeakStartX.GetAt(i+k-1)-m_objPeakInfo->dblPeakStartX.GetAt(i));

											stuPeakDetectPoint objPeakPoint = m_arrPeakDetectPoint.GetAt(lngStartIndex);
											dblXArr[m] = objPeakPoint.X;
											dblYArr[m] = dblSlope3*(objPeakPoint.X - m_objPeakInfo->dblPeakStartX.GetAt(i))+m_objPeakInfo->dblPeakStartY.GetAt(i);

										}
										else
										{
											stuPeakDetectPoint objPeakPoint = m_arrPeakDetectPoint.GetAt(lngStartIndex);
											dblXArr[m] = objPeakPoint.X;
											dblYArr[m] = objPeakPoint.Y;
										}



										lngStartIndex++;
									}

									//Add the point on Base line on right side of peak
									if (m_objPeakInfo->arrEndPointType.GetAt(i+k-1) == TYPE_VALLEY)
									{
										stuPeakDetectPoint objPeakPoint = m_arrPeakDetectPoint.GetAt(lngEndIndex);
										dblXArr[m] = objPeakPoint.X;
										dblYArr[m] = YOnBL;




									}
									else
									{
										stuPeakDetectPoint objPeakPoint = m_arrPeakDetectPoint.GetAt(lngEndIndex);
										dblXArr[m] = objPeakPoint.X;
										dblYArr[m] = objPeakPoint.Y;



									}

									//Perform Peak calculations
									double dblPeakArea, dblPeakFWHH, dblPeakHeight, dblPeakWidth;
									fncPeakCalculations(lngMaxHeightIndex, dblXArr, dblYArr, lngPointCount,&dblPeakArea, &dblPeakFWHH, &dblPeakHeight, &dblPeakWidth,i+k-1);
								}


							}
							else if(m_objPeakInfo->arrEndPointType.GetAt(i+k-1)==TYPE_BKWSKIMMING)
							{

								//This is for Skimming
								long lngValleyBaseNo	=	m_chart.AddSeries(0); // To hold the Graph ID which is used for BaseLine Drawing
								pDisp	=	m_chart.Series(lngValleyBaseNo);
								pVLSeries	=	pDisp;// Smart pointer for 'Series' interface of series used for Baseline
								pDisp->Release();
								pVLSeries->put_Color(RGB(0,0,0));
								pVLSeries->ShowInLegend	=	FALSE;

								//					
								pVLSeries->AddXY(m_objPeakInfo->dblPeakStartX.GetAt(i),m_objPeakInfo->dblPeakStartY.GetAt(i),bstrName,RGB(0,0,0));
								pVLSeries->AddXY(m_objPeakInfo->dblPeakEndX.GetAt(i+k-1),m_objPeakInfo->dblPeakEndY.GetAt(i+k-1),bstrName,RGB(0,0,0));

								double dblSlope10=(m_objPeakInfo->dblPeakEndY.GetAt(i+k-1)-m_objPeakInfo->dblPeakStartY.GetAt(i))/(m_objPeakInfo->dblPeakEndX.GetAt(i+k-1)-m_objPeakInfo->dblPeakStartX.GetAt(i));

								int ValleyCount = (i+k-1)-i;



								long lngPerpendicularNo	=	m_chart.AddSeries(0); // To hold the Graph ID which is used for BaseLine Drawing
								pDisp	=	m_chart.Series(lngPerpendicularNo);
								pPLSeries	=	pDisp;// Smart pointer for 'Series' interface of series used for Baseline
								pDisp->Release();
								pPLSeries->put_Color(RGB(0,0,255));
								pPLSeries->ShowInLegend	=	FALSE;

								for (int n=1;n<=ValleyCount+1;n++)
								{
									dblXValueAtValley = m_objPeakInfo->dblPeakEndX.GetAt(i+n-1);

									YOnBL = dblSlope10 * (dblXValueAtValley -m_objPeakInfo->dblPeakStartX.GetAt(i))+(m_objPeakInfo->dblPeakStartY.GetAt(i));

									if(YOnBL != dblXValueAtValley)
									{
										pPLSeries->AddXY(m_objPeakInfo->dblPeakEndX.GetAt(i+n-1),m_objPeakInfo->dblPeakEndY.GetAt(i+n-1),bstrName,RGB(0,0,0));
										pPLSeries->AddXY(m_objPeakInfo->dblPeakEndX.GetAt(i+n-1),YOnBL,bstrName,RGB(0,0,0));
									}

									long lngStartIndex=m_objPeakInfo->intPeakStartIndex.GetAt(i+n-1);
									long lngEndIndex=m_objPeakInfo->intPeakEndIndex.GetAt(i+n-1);
									long lngMaxHeightIndex = m_objPeakInfo->intPeakMaxIndex.GetAt(i+n-1);

									long lngPointCount = lngEndIndex - lngStartIndex +1;
									long lngTempPeakCount = lngPointCount;

									lngPointCount += 2;
									lngTempPeakCount++;

									//Get the peak data
									double* dblXArr = new double[lngPointCount];
									double* dblYArr = new double[lngPointCount];

									int m=0;

									if(m_objPeakInfo->arrStartPointType.GetAt(i+n-1)==TYPE_SkMVALLEY)
									{
										stuPeakDetectPoint objPeakPoint = m_arrPeakDetectPoint.GetAt(lngStartIndex);
										dblXArr[m] = objPeakPoint.X;
										dblYArr[m] = dblSlope10 * (objPeakPoint.X-m_objPeakInfo->dblPeakStartX.GetAt(i) )+(m_objPeakInfo->dblPeakStartY.GetAt(i));

										m++;
									}
									else
									{
										stuPeakDetectPoint objPeakPoint = m_arrPeakDetectPoint.GetAt(lngStartIndex);
										dblXArr[m] = objPeakPoint.X;
										dblYArr[m] = objPeakPoint.Y;

										m++;
									}

									for (; m<lngTempPeakCount; m++)
									{
										stuPeakDetectPoint objPeakPoint=m_arrPeakDetectPoint.GetAt(lngStartIndex);

										dblXArr[m] = objPeakPoint.X;
										dblYArr[m] = objPeakPoint.Y;


										lngStartIndex++;

									}

									if(m_objPeakInfo->arrEndPointType.GetAt(i+n-1)==TYPE_SkMVALLEY)
									{
										stuPeakDetectPoint objPeakPoint = m_arrPeakDetectPoint.GetAt(lngEndIndex);
										dblXArr[m] = objPeakPoint.X;
										dblYArr[m] = YOnBL;

									}
									else
									{
										stuPeakDetectPoint objPeakPoint = m_arrPeakDetectPoint.GetAt(lngEndIndex);
										dblXArr[m] = objPeakPoint.X;
										dblYArr[m] = objPeakPoint.Y;

									}

									//Perform Peak calculations
									double dblPeakArea, dblPeakFWHH, dblPeakHeight, dblPeakWidth;
									fncPeakCalculations(lngMaxHeightIndex, dblXArr, dblYArr, lngPointCount,&dblPeakArea, &dblPeakFWHH, &dblPeakHeight, &dblPeakWidth,i+n-1);
								}

							}
							else if(m_objPeakInfo->arrEndPointType.GetAt(i+k-1)==TYPE_FRWSKIMMING)
							{
								long lngValleyBaseNo	=	m_chart.AddSeries(0); // To hold the Graph ID which is used for BaseLine Drawing
								pDisp	=	m_chart.Series(lngValleyBaseNo);
								pVLSeries	=	pDisp;// Smart pointer for 'Series' interface of series used for Baseline
								pDisp->Release();
								pVLSeries->put_Color(RGB(0,0,0));
								pVLSeries->ShowInLegend	=	FALSE;

								int m1 = i+k-1;

								pVLSeries->AddXY(m_objPeakInfo->dblPeakEndX.GetAt(m1),m_objPeakInfo->dblPeakEndY.GetAt(m1),bstrName,RGB(0,0,0));
								pVLSeries->AddXY(m_objPeakInfo->dblPeakEndX.GetAt(j),m_objPeakInfo->dblPeakEndY.GetAt(j),bstrName,RGB(0,0,0));


								double dblSLope2=0;
								dblSLope2=(m_objPeakInfo->dblPeakEndY.GetAt(j)-m_objPeakInfo->dblPeakEndY.GetAt(m1))/(m_objPeakInfo->dblPeakEndX.GetAt(j)-m_objPeakInfo->dblPeakEndX.GetAt(m1));

								int ValleyCount=0;
								ValleyCount = j-m1;


								long lngPerpendicularNo1	=	m_chart.AddSeries(0); // To hold the Graph ID which is used for BaseLine Drawing
								pDisp	=	m_chart.Series(lngPerpendicularNo1);
								pPLSeries1	=	pDisp;// Smart pointer for 'Series' interface of series used for Baseline
								pDisp->Release();
								pPLSeries1->put_Color(RGB(0,0,255));
								pPLSeries1->ShowInLegend	=	FALSE;

								for (int n=1; n<=ValleyCount+1; n++)
								{

									dblXValueAtValley = m_objPeakInfo->dblPeakEndX.GetAt(m1+n-1);

									double YOnBL = dblSLope2 * (dblXValueAtValley -m_objPeakInfo->dblPeakEndX.GetAt(m1))+(m_objPeakInfo->dblPeakEndY.GetAt(m1));

									pPLSeries1->AddXY(m_objPeakInfo->dblPeakEndX.GetAt(m1+n-1),m_objPeakInfo->dblPeakEndY.GetAt(m1+n-1),bstrName,RGB(0,0,0));
									pPLSeries1->AddXY(m_objPeakInfo->dblPeakEndX.GetAt(m1+n-1),YOnBL,bstrName,RGB(0,0,0));

									long lngStartIndex;
									if(m_objPeakInfo->arrStartPointType.GetAt(m1+n-1)==TYPE_BKWSKIMMING)
									{
										lngStartIndex=m_objPeakInfo->intPeakStartIndex.GetAt(i);

									}
									else
										lngStartIndex=m_objPeakInfo->intPeakStartIndex.GetAt(m1+n-1);


									long lngEndIndex;
									if(m_objPeakInfo->arrEndPointType.GetAt(m1+n-1)==TYPE_FRWSKIMMING)
									{
										lngEndIndex=m_objPeakInfo->intPeakEndIndex.GetAt(j);
									}
									else
										lngEndIndex=m_objPeakInfo->intPeakEndIndex.GetAt(m1+n-1);

									long lngMaxHeightIndex = m_objPeakInfo->intPeakMaxIndex.GetAt(m1+n-1);

									long lngPointCount = lngEndIndex - lngStartIndex +1;
									long lngTempPeakCount = lngPointCount;

									lngPointCount += 2;
									lngTempPeakCount++;


									//Get the peak data
									double* dblXArr = new double[lngPointCount];
									double* dblYArr = new double[lngPointCount];

									int m=0;
									if(m_objPeakInfo->arrStartPointType.GetAt(m1+n-1)==TYPE_SkMVALLEY||m_objPeakInfo->arrStartPointType.GetAt(m1+n-1) == TYPE_VALLEY)
									{

										if(m_objPeakInfo->arrStartPointType.GetAt(m1+n-1)==TYPE_SkMVALLEY)
										{

											stuPeakDetectPoint objPeakPoint = m_arrPeakDetectPoint.GetAt(lngStartIndex);
											dblXArr[m] = objPeakPoint.X;
											dblYArr[m] = dblSLope2 * (objPeakPoint.X-m_objPeakInfo->dblPeakEndX.GetAt(m1))+(m_objPeakInfo->dblPeakEndY.GetAt(m1));
										}
										else
										{
											stuPeakDetectPoint objPeakPoint = m_arrPeakDetectPoint.GetAt(lngStartIndex);
											dblXArr[m] = objPeakPoint.X;
											dblYArr[m] = dblSLope * (objPeakPoint.X-m_objPeakInfo->dblPeakStartX.GetAt(i))+(m_objPeakInfo->dblPeakStartY.GetAt(i));

										}

										m++;

									}
									else
									{
										stuPeakDetectPoint objPeakPoint = m_arrPeakDetectPoint.GetAt(lngStartIndex);
										dblXArr[m] = objPeakPoint.X;
										dblYArr[m] = objPeakPoint.Y;



										m++;
									}

									for (;m<lngTempPeakCount; m++)
									{
										stuPeakDetectPoint objPeakPoint=m_arrPeakDetectPoint.GetAt(lngStartIndex);

										if(lngStartIndex < m_objPeakInfo->intPeakStartIndex.GetAt(m1+n-1))
										{
											dblXArr[m] = objPeakPoint.X;
											dblYArr[m] = dblSLope2*(objPeakPoint.X-m_objPeakInfo->dblPeakEndX.GetAt(m1+n-1)) + m_objPeakInfo->dblPeakEndY.GetAt(m1+n-1);
										}
										else if(lngStartIndex > m_objPeakInfo->intPeakEndIndex.GetAt(m1+n-1))
										{
											dblXArr[m] = objPeakPoint.X;
											dblYArr[m] = dblSLope2*(objPeakPoint.X-m_objPeakInfo->dblPeakEndX.GetAt(m1+n-1)) + m_objPeakInfo->dblPeakEndY.GetAt(m1+n-1);
										}
										else
										{
											dblXArr[m] = objPeakPoint.X;
											dblYArr[m] = objPeakPoint.Y;

										}



										lngStartIndex++;

									}
									if(m_objPeakInfo->arrEndPointType.GetAt(m1+n-1)==TYPE_SkMVALLEY)
									{

										stuPeakDetectPoint objPeakPoint = m_arrPeakDetectPoint.GetAt(lngEndIndex);
										dblXArr[m] = objPeakPoint.X;
										dblYArr[m] = YOnBL;//dblSLope2 *(objPeakPoint.X -m_objPeakInfo->dblPeakStartX.GetAt(m+n-1))+(m_objPeakInfo->dblPeakStartY.GetAt(m+n-1));



									}
									else
									{
										stuPeakDetectPoint objPeakPoint = m_arrPeakDetectPoint.GetAt(lngEndIndex);
										dblXArr[m] = objPeakPoint.X;
										dblYArr[m] = objPeakPoint.Y;

									}

									//Perform Peak calculations
									double dblPeakArea, dblPeakFWHH, dblPeakHeight, dblPeakWidth;
									fncPeakCalculations(lngMaxHeightIndex, dblXArr, dblYArr, lngPointCount,&dblPeakArea, &dblPeakFWHH, &dblPeakHeight, &dblPeakWidth,m1+n-1);


								}
							}

						}


					}
					else
					{

						pBLSeries->AddXY(m_objPeakInfo->dblPeakStartX.GetAt(i),m_objPeakInfo->dblPeakStartY.GetAt(i),bstrName,RGB(0,0,0));
						pBLSeries->AddXY(m_objPeakInfo->dblPeakEndX.GetAt(j),m_objPeakInfo->dblPeakEndY.GetAt(j),bstrName,RGB(0,0,0));

						//Get the peak start index
						long lngStartIndex = m_objPeakInfo->intPeakStartIndex.GetAt(i);
						//Get the peak end index
						long lngEndIndex = m_objPeakInfo->intPeakEndIndex.GetAt(i);
						//Get the index of maximum height in the peak
						long lngMaxHeightIndex = m_objPeakInfo->intPeakMaxIndex.GetAt(i);
						//Calculate the number of points on peak
						long lngPointCount = lngEndIndex - lngStartIndex +1;
						long lngTempPeakCount=lngPointCount;

						lngPointCount += 2;
						lngTempPeakCount++;

						//Get the peak data
						double* dblXArr = new double[lngPointCount];
						double* dblYArr = new double[lngPointCount];

						//fill the arrays with the data of the peak

						int m=0;

						stuPeakDetectPoint objPeakPoint = m_arrPeakDetectPoint.GetAt(lngStartIndex);
						dblXArr[m] = objPeakPoint.X;
						dblYArr[m] = objPeakPoint.Y;

						m++;


						for (; m<lngTempPeakCount; m++)
						{
							stuPeakDetectPoint objPeakPoint = m_arrPeakDetectPoint.GetAt(lngStartIndex);
							dblXArr[m] = objPeakPoint.X;
							dblYArr[m] = objPeakPoint.Y;

							lngStartIndex++;
						}

						stuPeakDetectPoint objPeakPoint1 = m_arrPeakDetectPoint.GetAt(lngEndIndex);
						dblXArr[m] = objPeakPoint1.X;
						dblYArr[m] = objPeakPoint1.Y;



						//Perform Peak calculations
						double dblPeakArea, dblPeakFWHH, dblPeakHeight, dblPeakWidth;
						fncPeakCalculations(lngMaxHeightIndex, dblXArr, dblYArr, lngPointCount,&dblPeakArea, &dblPeakFWHH, &dblPeakHeight, &dblPeakWidth,i);

						nTemp=j;
					}

					if(nTemp == j)
					{


						i = j;
						break;

					}





				}

			}

		}
		else if (m_objPeakInfo->arrStartPointType.GetAt(i) == TYPE_HORZ_BASE)
			fncApplyHorizontalBaseMethod(i);
	}
}

FILE* fp;
int nVal = 0;

BOOL CEsdAdvancedGraphCtrl::fncPeakCalculations(long lngMaxHeightIndex, double* dblXArr, double* dblYArr, long lngCount, double* dblArea, double* dblFWHH, double* dblHeight, double* dblWidth,int PeakNo)
{

	double dblY0;
	double dblYn;

	dblY0 =dblYArr[0];
	dblYn =dblYArr[lngCount-1];


	double dblInterval = dblXArr[2]-dblXArr[1];
	double dblBaseLineArea =  0.5 * (dblY0 + dblYn) * (dblXArr[lngCount-1] - dblXArr[0]);

	//CString str;
	//str.Format(_T("XMAX=%lf ,XMIN=%lf"),dblXArr[lngCount-1],dblXArr[0]);
	//AfxMessageBox(str);
	////CString str;
	//str.Format(_T("%lf"),dblInterval);
	//AfxMessageBox(str);


	double dblYSum = 0.0f;


	for (int m=2; m<lngCount-2; m++)
	{

		dblYSum += dblYArr[m];


	}

	//dblYSum *= 2;
	*dblArea = fabs((( 2 * dblYSum + dblYArr[1] + dblYArr[lngCount-2]) * 0.5 * dblInterval) - dblBaseLineArea);

	//Calculate the peak width 
	*dblWidth = fabs(dblXArr[lngCount-1] - dblXArr[0]);

	//Calculate the peak height
	stuPeakDetectPoint objPeakMax = m_arrPeakDetectPoint.GetAt(lngMaxHeightIndex);
	double dblBaseLineSlope = (dblYArr[lngCount-1] - dblYArr[0]) /(dblXArr[lngCount-1] - dblXArr[0]);
	double dblYOnBaseLine = dblBaseLineSlope * (objPeakMax.X - dblXArr[0]) + (dblYArr[0]);
	*dblHeight = fabs(objPeakMax.Y - dblYOnBaseLine);;

	//Calculate Full Width Half Maximum (FWHH)
	//Find the maximum Y value
	double dblHalfHeight = *dblHeight / 2;
	int nMaxIndex =0;
	for (int i=0; i<lngCount-1; i++)
	{
		if (dblYArr[i] == objPeakMax.Y)
		{
			nMaxIndex=i;
			break;
		}
	}
	double dblStartX, dblEndX;
	for(int i = nMaxIndex; i>=0; i--)
	{
		if((dblYArr[i] - dblY0) <= dblHalfHeight)
		{
			dblStartX = dblXArr[i];
			break;
		}
	}
	for(int i = nMaxIndex; i<lngCount; i++)
	{
		if((dblYArr[i] - dblYn) <= dblHalfHeight)
		{
			dblEndX = dblXArr[i];
			break;
		}
	}

	m_objPeakInfo->dblArea.SetAt(PeakNo,*dblArea);
	m_objPeakInfo->dblHeight.SetAt(PeakNo,*dblHeight);
	m_objPeakInfo->dblWidth.SetAt(PeakNo,*dblWidth);



	*dblFWHH = dblEndX-dblStartX;


	/*if(*dblArea < m_dblMinArea)
	{
	return FALSE;
	}
	if(*dblHeight < m_dblMinHeight)
	{
	return FALSE;
	}
	if(*dblWidth < m_dblMinWidth)
	{
	return FALSE;
	}*/




	/*fprintf(fp," Area : %lf\nHeight : %lf\nWidth : %lf\nFWHH : %lf", *dblArea, *dblHeight, *dblWidth,*dblFWHH);
	fclose(fp);*/

	return TRUE;

}

void CEsdAdvancedGraphCtrl::fncForceBaseMethod(double dblStartTime, double dblEndTime, double dblValue)
{

	//check the dblStartTime is in which peak
	long lngPeaksCount = 0;
	if(m_objPeakInfo!=NULL)
		lngPeaksCount =(long) m_objPeakInfo->arrStartPointType.GetSize();


	int nFBPisOn = 0;//left side = 0 , right side = 1, else = 2;

	//Get the index corresponding to given Force base point 

	long lngFBPIndex = 0;
	LPDISPATCH pDisp =	m_chart.Series(0);
	ISeriesPtr pSeries	=	pDisp;
	pDisp->Release();

	//For getting the index of the FBP point
	lngFBPIndex	=	pSeries->GetXValues()->Locate(dblStartTime);

	if((dblStartTime==0.0)&(dblEndTime==0.0))
	{
		AfxMessageBox(L"Enter Start Time");
		return;
	}

	if(dblStartTime<0.0)
	{
		AfxMessageBox(_T("Time cannot be negative."));
		return;
	}






	pSeries	=	NULL;
	for(int nFind=0;nFind<lngPeaksCount;nFind++)
	{



		//on left side of the peak
		if( (m_objPeakInfo->dblPeakStartX.GetAt(nFind) <= dblStartTime) && (dblStartTime < m_objPeakInfo->dblPeakMaxX.GetAt(nFind) ) )
		{




			int nMaxInd = m_objPeakInfo->intPeakMaxIndex.GetAt(nFind);
			int nStartInd =  m_objPeakInfo->intPeakStartIndex.GetAt(nFind);
			int nEndInd = m_objPeakInfo->intPeakEndIndex.GetAt(nFind);

			//Test purpose.
			if(lngFBPIndex==-1)
				lngFBPIndex=nStartInd+5;



			//check the point satisfies the peak criteria or not
			if( (nMaxInd - lngFBPIndex) >= 3)
			{

				stuPeakDetectPoint obj1 = m_arrPeakDetectPoint.GetAt(lngFBPIndex);
				stuPeakDetectPoint obj2 = m_arrPeakDetectPoint.GetAt(nEndInd);




				stuPeakDetectPoint obj = m_arrPeakDetectPoint.GetAt(lngFBPIndex);;




				//FBP is above the end of the peak
				if(obj1.Y > obj2.Y)
				{					
					//if the first peak
					m_objPeakInfo->arrEndPointType.SetAt(nFind,TYPE_PENETRATION);
					if (nFind != (m_objPeakInfo->arrStartPointType.GetSize()-1))
						m_objPeakInfo->arrStartPointType.SetAt(nFind+1,TYPE_PENETRATION);

					//AfxMessageBox(L"Penetration");
				}



				//if the peaks are fused peaks
				m_objPeakInfo->arrStartPointType.SetAt(nFind,TYPE_BASE);
				if(nFind!=0)
					m_objPeakInfo->arrEndPointType.SetAt(nFind-1,TYPE_BASE);

				//changing the positions of start point of the peak
				m_objPeakInfo->intPeakStartIndex.SetAt(nFind,lngFBPIndex);
				m_objPeakInfo->dblPeakStartX.SetAt(nFind,obj.X);
				m_objPeakInfo->dblPeakStartY.SetAt(nFind,obj.Y);


			}
			else
			{
				AfxMessageBox(_T("Not a valid base point..."));
				return;
			}


		}
		else if( (m_objPeakInfo->dblPeakMaxX.GetAt(nFind) < dblStartTime) && (dblStartTime <= m_objPeakInfo->dblPeakEndX.GetAt(nFind) ) ) //Base point on Right side of peak
		{


			//nFind = 1;
			int nMaxInd = m_objPeakInfo->intPeakMaxIndex.GetAt(nFind);

			//check the point satisfies the peak criteria or not
			if( (lngFBPIndex - nMaxInd) >= 3 )
			{				
				int nStartInd=  m_objPeakInfo->intPeakStartIndex.GetAt(nFind);
				int nEndInd = m_objPeakInfo->intPeakEndIndex.GetAt(nFind);

				stuPeakDetectPoint objStart = m_arrPeakDetectPoint.GetAt(nStartInd);

				stuPeakDetectPoint obj = m_arrPeakDetectPoint.GetAt(lngFBPIndex);;

				//FBP is above the start of the peak
				//if(objStart.Y < obj.Y)
				//{	

				if(m_objPeakInfo->arrStartPointType.GetAt(nFind)  == TYPE_VALLEY)
				{
					//Get the index of previous base point
					int nPrevBaseIndex = 0;
					int m=nFind-1;						
					for (; m>=0; m--)
					{
						if( (m_objPeakInfo->arrStartPointType.GetAt(m)  == TYPE_BASE) || (m_objPeakInfo->arrStartPointType.GetAt(m)  == TYPE_PENETRATION)|| ((m_objPeakInfo->arrStartPointType.GetAt(m)  == TYPE_HORZ_BASE)) )
						{
							nPrevBaseIndex = m_objPeakInfo->intPeakStartIndex.GetAt(m);
							break;
						}
					}	
					if (m<0)
						m=0;						

					//Get the previous base point
					stuPeakDetectPoint objPrevBase;

					for (int n=m; n<nFind; n++)
					{
						objPrevBase = m_arrPeakDetectPoint.GetAt(nPrevBaseIndex);
						stuPeakDetectPoint objPrevPeak = m_arrPeakDetectPoint.GetAt(m_objPeakInfo->intPeakEndIndex.GetAt(n));

						//Calculate the slope of the line joining the valley and previous base point
						double dblSlopeValleyBase = (objPrevPeak.Y - objPrevBase.Y) /(objPrevPeak.X - objPrevBase.X);

						//Calculate the slope of the line joining the Force base point and Force base point
						double dblSlopeFBB = (objPrevBase.Y - obj.Y) /(objPrevBase.X - obj.X);

						//Check for negative Peak
						if (dblSlopeFBB > dblSlopeValleyBase)
						{
							//Make the base point type as Base 
							m_objPeakInfo->arrEndPointType.SetAt(n, TYPE_BASE);
							//Make the previous end point type as Base 
							if(n < (m_objPeakInfo->arrStartPointType.GetSize()-1))
								m_objPeakInfo->arrStartPointType.SetAt(n+1, TYPE_BASE);
						}
						if(n < (m_objPeakInfo->arrStartPointType.GetSize()-1))
							nPrevBaseIndex = m_objPeakInfo->intPeakStartIndex.GetAt(n+1);
					}
				}				
				//}

				//Set the peak end index, type and point
				m_objPeakInfo->arrEndPointType.SetAt(nFind,TYPE_BASE);
				m_objPeakInfo->intPeakEndIndex.SetAt(nFind,lngFBPIndex);
				m_objPeakInfo->dblPeakEndX.SetAt(nFind,obj.X);
				m_objPeakInfo->dblPeakEndY.SetAt(nFind,obj.Y);
				//Set the next peak start type
				if (nFind != (m_objPeakInfo->arrStartPointType.GetSize()-1))
					m_objPeakInfo->arrStartPointType.SetAt(nFind+1,TYPE_BASE);
			}
			else
			{
				AfxMessageBox(_T("Not a valid base point..."));
				return;
			}
		}
		else if(m_objPeakInfo->dblPeakMaxX.GetAt(nFind)==dblStartTime) 
		{

			AfxMessageBox(_T("Not a valid base point..."));
			return;
		}
	}
}
void CEsdAdvancedGraphCtrl::fncForcedPeak(double dblStartTime, double dblEndTime, double dblValue)
{
	/*long lngPeakNo = m_objPeakInfo->arrStartPointType.GetSize();
	m_objPeakInfo->arrStartPointType.RemoveAll();
	m_objPeakInfo->arrEndPointType.RemoveAll();
	m_objPeakInfo->dblArea.RemoveAll();
	m_objPeakInfo->dblHeight.RemoveAll();
	m_objPeakInfo->dblPeakEndX.RemoveAll();
	m_objPeakInfo->dblPeakEndY.RemoveAll();
	m_objPeakInfo->dblPeakMaxX.RemoveAll();
	m_objPeakInfo->dblPeakMaxY.RemoveAll();
	m_objPeakInfo->dblPeakStartX.RemoveAll();
	m_objPeakInfo->dblPeakStartY.RemoveAll();
	m_objPeakInfo->dblWidth.RemoveAll();
	m_objPeakInfo->intPeakEndIndex.RemoveAll();
	m_objPeakInfo->intPeakMaxIndex.RemoveAll();
	m_objPeakInfo->intPeakStartIndex.RemoveAll();*/
	if(dblStartTime<0.0||dblEndTime<0.0)
	{
		AfxMessageBox(_T("Time cannot be negative."));
		return;
	}
	if((dblStartTime==0.0)&(dblEndTime==0.0))
	{
		AfxMessageBox(L"Enter Start and End Time");
		return;
	}

	if(dblStartTime>=dblEndTime)
	{
		AfxMessageBox(_T("End time should be greater than start time"));
		return;

	}

	stuPeakDetectPoint obj;

	m_intCurrentDataPointIndex = -1;
	int m_intCurrentDataEndPointIndex = -1;

	for (int i=0;i<=m_arrPeakDetectPoint.GetSize()-1;i++)
	{
		obj = m_arrPeakDetectPoint.GetAt(i);
		CString s,s1,s2,s3;
		s.Format(_T("%lf"),obj.X);
		s1=s.Left(4);
		s.Format(_T("%lf"),dblStartTime);
		s2=s.Left(4);
		s.Format(_T("%lf"),dblEndTime);
		s3=s.Left(4);
		if (s1==s2)
		{
			m_intCurrentDataPointIndex = i;

		}
		if (s1==s3)
		{
			m_intCurrentDataEndPointIndex = i;

		}		
	}

	m_dblCurrentX = 0;
	m_dblCurrentY = 0;

	m_dblPreviousDerivativeX = 0;
	m_dblPreviousDerivativeY = 0;

	m_dblSlope = 0;
	m_dblCurve = 0;

	m_intPeakUpCount =0;
	m_intPeakDownCount =0;

	m_intPeakStatus = FLAT;

	m_blnDetectNegativePeaksAlso = FALSE;

	m_dblAvCurve = 0;
	m_dblAverageLength =0;
	m_dblUpCurveLimit = 0;

	m_dblLastPeakEndX =0;




	for (int i= m_intCurrentDataPointIndex+1; i <= m_intCurrentDataEndPointIndex; i++)
	{
		obj=m_arrPeakDetectPoint.GetAt(i);

		m_intCurrentDataPointIndex++;

		m_dblOldX = m_dblCurrentX;
		m_dblOldY = m_dblCurrentY;

		m_dblCurrentX = obj.X;
		m_dblCurrentY = obj.Y;

		m_intDerivativeRetValue = Derivative();

		switch (m_intPeakStatus)
		{     
		case FLAT:

			if(isFlat())
				break;

		case NEGUPCRV:
		case UPCRV:

			if (isFlankNotYetAccepted(m_intPeakStatus == NEGUPCRV))
				break;

		case NEGUP:
		case UP:

			if (isUpHill(m_intPeakStatus == NEGUP))
				break;

		case NEGDOWN:
		case DOWN:

			if (isDownHill(m_intPeakStatus == NEGDOWN))
				break;
		case PKEND:

			bForcedpeak = TRUE;
			StorePeak();
			break;

		}

	}

}
void CEsdAdvancedGraphCtrl::fncBaseAtNextValleyMethod(double dblStartTime, double dblEndTime, double dblValue)
{

	//check the dblStartTime is in which peak
	if(dblStartTime<0.0)
	{
		AfxMessageBox(_T("Time cannot be negative."));
		return;
	}
	if((dblStartTime==0.0)&(dblEndTime==0.0))
	{
		AfxMessageBox(L"Enter Start Time");
		return;
	}
	long lngPeaksCount =(long) m_objPeakInfo->arrStartPointType.GetSize();
	int nBANVisOn = 0;//left side = 0 , right side = 1, else = 2;

	/*if(dblStartTime<m_objPeakInfo->dblPeakStartX.GetAt(0)||(dblStartTime>m_objPeakInfo->dblPeakEndX.GetAt(lngPeaksCount-1)))
	{
	AfxMessageBox(L"Start time is Out of peak detection range.");
	return;
	}*/
	/*if(dblEndTime<m_objPeakInfo->dblPeakStartX.GetAt(0)||(dblEndTime>m_objPeakInfo->dblPeakEndX.GetAt(lngPeaksCount-1)))
	{
	AfxMessageBox(L"End time is Out of peak detection range.");
	return;
	}*/

	for(int nFind=0;nFind<lngPeaksCount;nFind++)
	{
		//Find the peak on which the start point lie
		if( (m_objPeakInfo->dblPeakStartX.GetAt(nFind) <= dblStartTime) && (dblStartTime < m_objPeakInfo->dblPeakEndX.GetAt(nFind) ) )
		{

			if(m_objPeakInfo->arrEndPointType.GetAt(nFind)==TYPE_VALLEY)
			{
				m_objPeakInfo->arrEndPointType.SetAt(nFind,TYPE_BASE);
				if(nFind!=m_objPeakInfo->arrStartPointType.GetSize()-1)
					m_objPeakInfo->arrStartPointType.SetAt(nFind+1,TYPE_BASE);
				break;
			}			
		}
	}	

}

void CEsdAdvancedGraphCtrl::fncValleyToValleyMethod(double dblStartTime, double dblEndTime, double dblValue)
{	
	long lngPeaksCount =(long) m_objPeakInfo->arrStartPointType.GetSize();
	int nStartPeakIndex = -1 , nEndPeakIndex = -1;
	//Start of the Valley-Valley is valid or not
	BOOL blnFound = FALSE;
	if(dblStartTime<0.0||dblEndTime<0.0)
	{
		AfxMessageBox(_T("Time cannot be negative."));
		return;
	}
	if((dblStartTime==0.0)&(dblEndTime==0.0))
	{
		AfxMessageBox(L"Enter Start and End Time");
		return;
	}

	if(dblStartTime>=dblEndTime)
	{
		AfxMessageBox(_T("End time should be greater than start time"));
		return;

	}
	/*if(dblStartTime<m_objPeakInfo->dblPeakStartX.GetAt(0)||(dblStartTime>m_objPeakInfo->dblPeakEndX.GetAt(lngPeaksCount-1)))
	{
	AfxMessageBox(L"Start time is Out of peak detection range.");
	return;
	}
	if(dblEndTime<m_objPeakInfo->dblPeakStartX.GetAt(0)||(dblEndTime>m_objPeakInfo->dblPeakEndX.GetAt(lngPeaksCount-1)))
	{
	AfxMessageBox(L"End time is Out of peak detection range.");
	return;
	}*/
	//Find the peak on which the start time lie
	//Find the peak on which the start point lie
	for(long nFind=0;nFind<lngPeaksCount;nFind++)
	{		
		//if the start time in between any peak's start and end time
		if( (m_objPeakInfo->dblPeakStartX.GetAt(nFind) <= dblStartTime) && (dblStartTime < m_objPeakInfo->dblPeakEndX.GetAt(nFind) ) )
		{
			//if the start time is any peak's start then put it that peak number is start index
			CString strtime,strStartx,strStarttime;
			strtime.Format(_T("%lf"),m_objPeakInfo->dblPeakStartX.GetAt(nFind));
			strStartx=strtime.Left(4);
			strtime.Format(_T("%lf"),dblStartTime);
			strStarttime=strtime.Left(4);
			if (strStartx==strStarttime)
				nStartPeakIndex = nFind;
			else // put the next peak no is start index
			{
				BOOL blnStartFound = FALSE;
				for(int nInd=nFind+1;nInd<lngPeaksCount;nInd++)
				{
					if(m_objPeakInfo->arrStartPointType.GetAt(nInd)==TYPE_BASE || m_objPeakInfo->arrStartPointType.GetAt(nInd)==TYPE_PENETRATION)
					{
						nStartPeakIndex = nInd;
						blnStartFound = TRUE;
						break;
					}
				}
				if(blnStartFound == TRUE)
				{
					break;
				}
			}
		}

	}
	//If the start time does not lie on the peak then get the index of next immediate peak
	if (nStartPeakIndex == -1)
	{
		for(int nFind=0;nFind<lngPeaksCount-1;nFind++)
		{		
			//if the start time is in between any peak end and the next peak start then
			if( (m_objPeakInfo->dblPeakEndX.GetAt(nFind) <= dblStartTime) && (dblStartTime < m_objPeakInfo->dblPeakStartX.GetAt(nFind+1) ) )
			{
				for(int nInd=nFind;nInd<lngPeaksCount;nInd++)
				{
					//check the next base or penetration and put that peak number as start index
					if(m_objPeakInfo->arrStartPointType.GetAt(nInd)==TYPE_BASE || m_objPeakInfo->arrStartPointType.GetAt(nInd)==TYPE_PENETRATION)
					{
						nStartPeakIndex = nInd;
						break;
					}
				}
				break;
			}

		}
	}
	if (nStartPeakIndex==-1)
	{
		nStartPeakIndex=0;
	}

	//Check for End time
	if (dblEndTime != -1.0f)
	{
		//Find the peak on which the End time lie
		for(int nFind=0;nFind<lngPeaksCount;nFind++)
		{
			if( (m_objPeakInfo->dblPeakStartX.GetAt(nFind) <= dblEndTime) && (dblEndTime < m_objPeakInfo->dblPeakEndX.GetAt(nFind) ) )
			{
				nEndPeakIndex = nFind;
				break;
			}
		}
		//If the End time does not lie on the peak then get the index of immediate previous peak
		if (nEndPeakIndex == -1)
		{
			for(int nFind=0;nFind<lngPeaksCount-1;nFind++)
			{		
				if( (m_objPeakInfo->dblPeakEndX.GetAt(nFind) <= dblEndTime) && (dblEndTime < m_objPeakInfo->dblPeakStartX.GetAt(nFind+1) ) )
				{
					nEndPeakIndex = nFind;
					break;
				}
			}
		}
		if (nEndPeakIndex== -1)
		{
			nEndPeakIndex=lngPeaksCount-1;

		}
	}
	else // Find the next peak with base point as end type, if no end time was given
	{
		//Find the next peak with end point type as base point
		for(int nFind=nStartPeakIndex;nFind<lngPeaksCount;nFind++)
		{
			if( ( m_objPeakInfo->arrEndPointType.GetAt(nFind) == TYPE_BASE ) || (m_objPeakInfo->arrEndPointType.GetAt(nFind) == TYPE_PENETRATION) ||m_objPeakInfo->arrEndPointType.GetAt(nFind) == TYPE_HORZ_BASE )
			{
				nEndPeakIndex = nFind;
				break;
			}
		}
	}

	//Apply valley to valley base line correction method
	for(int nFind = nStartPeakIndex; nFind<nEndPeakIndex; nFind++)
	{
		if(m_objPeakInfo->arrEndPointType.GetAt(nFind) == TYPE_VALLEY)
		{
			m_objPeakInfo->arrEndPointType.SetAt(nFind, TYPE_BASE);
			m_objPeakInfo->arrStartPointType.SetAt(nFind+1, TYPE_BASE);
		}
	}
}


FILE* fp1;
void CEsdAdvancedGraphCtrl::fncHorizontalBaselineMethod(double dblStartTime, double dblEndTime, double dblValue)
{

	//Get the number of peaks
	long lngPeaksCount =(long) m_objPeakInfo->arrStartPointType.GetSize();

	int nStartPeakIndex=-1;
	int nEndPeakIndex = -1;

	if(dblStartTime<0.0||dblEndTime<0.0)
	{
		AfxMessageBox(_T("Time Cannot be negative"));
		return;

	}
	if((dblStartTime==0.0)&(dblEndTime==0.0))
	{
		AfxMessageBox(L"Enter Start and End Time");
		return;
	}
	if(dblStartTime>=dblEndTime)
	{
		AfxMessageBox(_T("End time should be greater than start time"));
		return;

	}

	/*if(dblStartTime<m_objPeakInfo->dblPeakStartX.GetAt(0)||(dblStartTime>m_objPeakInfo->dblPeakEndX.GetAt(lngPeaksCount-1)))
	{
	AfxMessageBox(L"Start time is Out of peak detection range.");
	return;
	}
	if(dblEndTime<m_objPeakInfo->dblPeakStartX.GetAt(0)||(dblEndTime>m_objPeakInfo->dblPeakEndX.GetAt(lngPeaksCount-1)))
	{
	AfxMessageBox(L"End time is Out of peak detection range.");
	return;
	}*/

	//Find the peak on which the start point lie
	for(long nFind=0;nFind<lngPeaksCount;nFind++)
	{	
		//if the start time in between any peak's start and end time
		if( (m_objPeakInfo->dblPeakStartX.GetAt(nFind) <= dblStartTime) && (dblStartTime < m_objPeakInfo->dblPeakEndX.GetAt(nFind) ) )
		{

			//if the start time is any peak's start then put it that peak number is start index

			CString strtime,strStartx,strStarttime;
			strtime.Format(_T("%lf"),m_objPeakInfo->dblPeakStartX.GetAt(nFind));
			strStartx=strtime.Left(4);
			strtime.Format(_T("%lf"),dblStartTime);
			strStarttime=strtime.Left(4);
			if (strStartx==strStarttime)
				nStartPeakIndex = nFind;
			else // put the next peak no is start index
			{
				BOOL blnStartFound = FALSE;
				for(int nInd=nFind+1;nInd<lngPeaksCount;nInd++)
				{
					if(m_objPeakInfo->arrStartPointType.GetAt(nInd)==TYPE_BASE || m_objPeakInfo->arrStartPointType.GetAt(nInd)==TYPE_PENETRATION)
					{
						nStartPeakIndex = nInd;
						blnStartFound = TRUE;
						break;
					}
				}
				if(blnStartFound == TRUE)
				{
					break;
				}
			}
		}
	}
	//If the start time does not lie on the peak then get the index of next immediate peak
	if (nStartPeakIndex == -1)
	{
		for(int nFind=0;nFind<lngPeaksCount-1;nFind++)
		{		
			//if the start time is in between any peak end and the next peak start then
			if( (m_objPeakInfo->dblPeakEndX.GetAt(nFind) <= dblStartTime) && (dblStartTime < m_objPeakInfo->dblPeakStartX.GetAt(nFind+1) ) )
			{
				for(int nInd=nFind;nInd<lngPeaksCount;nInd++)
				{
					//check the next base or penetration and put that peak number as start index
					if(m_objPeakInfo->arrStartPointType.GetAt(nInd)==TYPE_BASE || m_objPeakInfo->arrStartPointType.GetAt(nInd)==TYPE_PENETRATION)
					{
						nStartPeakIndex = nInd;
						break;
					}
				}
				break;
			}

		}
	}
	if (nStartPeakIndex==-1)
	{
		nStartPeakIndex=0;

	}


	//Check for End time
	if (dblEndTime != -1.0f)
	{
		//Find the peak on which the End time lie
		for(int nFind=0;nFind<lngPeaksCount;nFind++)
		{
			if((m_objPeakInfo->dblPeakStartX.GetAt(nFind) <= dblEndTime) && (dblEndTime < m_objPeakInfo->dblPeakEndX.GetAt(nFind) ) )
			{
				//if(m_objPeakInfo->arrEndPointType.GetAt(nFind)!=TYPE_VALLEY)
				//{
				nEndPeakIndex = nFind;
				break;
				//break;
				//}
			}
		}
		//If the End time does not lie on the peak then get the index of immediate previous peak
		if (nEndPeakIndex == -1)
		{
			for(int nFind=0;nFind<lngPeaksCount-1;nFind++)
			{		
				if( (m_objPeakInfo->dblPeakEndX.GetAt(nFind) <= dblEndTime) && (dblEndTime < m_objPeakInfo->dblPeakStartX.GetAt(nFind+1) ) )
				{
					nEndPeakIndex = nFind;
					break;
				}
			}
		}
		if (nEndPeakIndex == -1)
		{
			nEndPeakIndex = lngPeaksCount-1;
		}

	}
	else // Find the next peak with base point as end type, if no end time was given
	{
		//Find the next peak with end point type as base point
		for(int nFind=nStartPeakIndex;nFind<lngPeaksCount;nFind++)
		{
			if( ( m_objPeakInfo->arrEndPointType.GetAt(nFind) == TYPE_BASE ) || (m_objPeakInfo->arrEndPointType.GetAt(nFind) == TYPE_PENETRATION) ||m_objPeakInfo->arrEndPointType.GetAt(nFind) == TYPE_HORZ_BASE )
			{
				nEndPeakIndex = nFind;
				break;
			}
		}
	}


	BOOL blnBaseFound = FALSE;

	for(int i=nEndPeakIndex;i>=nStartPeakIndex;i--)
	{
		if((m_objPeakInfo->arrEndPointType.GetAt(i)==TYPE_BASE) ||((m_objPeakInfo->arrEndPointType.GetAt(i)==TYPE_PENETRATION)) ||((m_objPeakInfo->arrEndPointType.GetAt(i)==TYPE_HORZ_BASE)))
		{
			nEndPeakIndex=i;
			blnBaseFound = TRUE;
			break;
		}
	}
	if (blnBaseFound == FALSE)
	{

		AfxMessageBox(_T("Invalid point(s)..."));
		return;
	}



	////Apply Horizontal base line correction method
	BOOL bFlag = FALSE;
	for(int i=nStartPeakIndex;i<=/*lngPeaksCount*/nEndPeakIndex;i++)
	{
		if((m_objPeakInfo->arrStartPointType.GetAt(i)==TYPE_BASE)||(m_objPeakInfo->arrStartPointType.GetAt(i)==TYPE_PENETRATION))
		{
			m_objPeakInfo->arrStartPointType.SetAt(i,TYPE_HORZ_BASE);
		}
		if ((m_objPeakInfo->arrEndPointType.GetAt(i) == TYPE_BASE)|| (m_objPeakInfo->arrEndPointType.GetAt(i) == TYPE_PENETRATION))
		{
			m_objPeakInfo->arrEndPointType.SetAt(i,TYPE_HORZ_BASE);

		}
	}
}


void CEsdAdvancedGraphCtrl::fncPenetrationWithNegativePeakMethod(double dblStartTime, double dblEndTime, double dblValue)
{

	//Get the number of peaks
	long lngPeaksCount =(long) m_objPeakInfo->arrStartPointType.GetSize();
	if((dblStartTime==0.0)&(dblEndTime==0.0))
	{
		AfxMessageBox(L"Enter Start and End Time");
		return;
	}
	if(dblStartTime>=dblEndTime)
	{
		AfxMessageBox(L"start time should be less than end time");
		return;
	}
	if((dblStartTime<0.0)||(dblEndTime<0.0))
	{
		AfxMessageBox(L"Time could not be negative.");
		return;

	}

	/*if(dblStartTime<m_objPeakInfo->dblPeakStartX.GetAt(0)||(dblStartTime>m_objPeakInfo->dblPeakEndX.GetAt(lngPeaksCount-1)))
	{
	AfxMessageBox(L"Start time is Out of peak detection range.");
	return;
	}
	if(dblEndTime<m_objPeakInfo->dblPeakStartX.GetAt(0)||(dblEndTime>m_objPeakInfo->dblPeakEndX.GetAt(lngPeaksCount-1)))
	{
	AfxMessageBox(L"End time is Out of peak detection range.");
	return;
	}*/


	int nStartPeakIndex=-1, nEndPeakIndex = -1;

	//Find the peak on which /the start point lie
	for(int nFind=0;nFind<lngPeaksCount;nFind++)
	{		
		if( (m_objPeakInfo->dblPeakStartX.GetAt(nFind) <= dblStartTime) && (dblStartTime < m_objPeakInfo->dblPeakEndX.GetAt(nFind) ) )
		{
			if (m_objPeakInfo->dblPeakStartX.GetAt(nFind) == dblStartTime)
				nStartPeakIndex = nFind;
			else
				nStartPeakIndex = nFind+1;
			break;
		}
	}

	//If the start time does not lie on the peak then get the index of next immediate peak
	if (nStartPeakIndex == -1)
	{
		for(int nFind=0;nFind<lngPeaksCount-1;nFind++)
		{		
			if( (m_objPeakInfo->dblPeakEndX.GetAt(nFind) <= dblStartTime) && (dblStartTime < m_objPeakInfo->dblPeakStartX.GetAt(nFind+1) ) )
			{
				nStartPeakIndex = nFind+1;
				break;
			}
		}
		if (nStartPeakIndex==-1)
		{
			nStartPeakIndex=0;
		}
	}



	//Check for End time
	if (dblEndTime != -1.0f)
	{
		//Find the peak on which the End time lie
		for(int nFind=0;nFind<lngPeaksCount;nFind++)
		{
			if( (m_objPeakInfo->dblPeakStartX.GetAt(nFind) <= dblEndTime) && (dblEndTime < m_objPeakInfo->dblPeakEndX.GetAt(nFind) ) )
			{
				nEndPeakIndex = nFind;
				break;
			}
		}

		//If the End time does not lie on the peak then get the index of immediate previous peak
		if (nEndPeakIndex == -1)
		{
			for(int nFind=0;nFind<lngPeaksCount-1;nFind++)
			{		
				if( (m_objPeakInfo->dblPeakEndX.GetAt(nFind) <= dblEndTime) && (dblEndTime < m_objPeakInfo->dblPeakStartX.GetAt(nFind+1) ) )
				{
					nEndPeakIndex = nFind;
					break;
				}
			}
		}
	}



	m_arrNegativeStartIndex.Add(nStartPeakIndex);
	int nTempArrIndex =(int) m_arrNegativeEndIndex.Add(nEndPeakIndex);

	//Apply  Base penetration with negative peak ON method
	for (int nFind = nStartPeakIndex; nFind<=nEndPeakIndex/*lngPeaksCount*/; nFind++)
	{
		if(nEndPeakIndex!=-1)
		{

			if (nFind>=nEndPeakIndex)
			{
				break;
			}
			if ((m_objPeakInfo->arrStartPointType.GetAt(nFind)== TYPE_BASE) || (m_objPeakInfo->arrStartPointType.GetAt(nFind)== TYPE_PENETRATION) )
			{

				for (int n=nFind; n<=nEndPeakIndex; n++)
				{

					if((m_objPeakInfo->arrEndPointType.GetAt(n)==TYPE_PENETRATION))
					{
						m_objPeakInfo->arrEndPointType.SetAt(n, TYPE_VALLEY);
						m_objPeakInfo->arrStartPointType.SetAt(n+1, TYPE_VALLEY);
					}
				}
			}
		}
		else
		{

			if( (m_objPeakInfo->arrStartPointType.GetAt(nFind)== TYPE_BASE) ||(m_objPeakInfo->arrStartPointType.GetAt(nFind)== TYPE_HORZ_BASE))
			{
				for (int n=nFind; n<lngPeaksCount; n++)
				{
					if(m_objPeakInfo->arrEndPointType.GetAt(n)==TYPE_PENETRATION)
					{
						m_objPeakInfo->arrEndPointType.SetAt(n, TYPE_VALLEY);
						m_objPeakInfo->arrStartPointType.SetAt(n+1, TYPE_VALLEY);
					}
					else if ( (m_objPeakInfo->arrEndPointType.GetAt(n)==TYPE_BASE) || (m_objPeakInfo->arrEndPointType.GetAt(n)==TYPE_HORZ_BASE) )
					{
						m_arrNegativeEndIndex.SetAt(nTempArrIndex, n);
						break;
					}
				}
				break;
			}
		}
	}


	//fclose(fp1);
}

void CEsdAdvancedGraphCtrl::fncApplyHorizontalBaseMethod(int nStartIndex)
{
	int nPeaksCount =(int) m_objPeakInfo->dblPeakStartX.GetSize();

	double dblStartX = m_objPeakInfo->dblPeakStartX.GetAt(nStartIndex);
	int nEndIndex = 0;
	if (m_objPeakInfo->arrStartPointType.GetAt(nStartIndex) == TYPE_HORZ_BASE)
	{

		for (int j=nStartIndex; j<nPeaksCount; j++)
		{
			if (m_objPeakInfo->arrEndPointType.GetAt(j) == TYPE_HORZ_BASE)
			{
				nEndIndex=j;
				break;
			}
		}

	}

	double dblY  = m_objPeakInfo->dblPeakStartY.GetAt(nStartIndex);
	double dblEndX, dblSLope, YOnBL, dblXValueAtValley;
	int nTempM;
	BOOL blnNegativePeak = FALSE;
	if (m_arrNegativeStartIndex.GetSize()>0)
		blnNegativePeak = TRUE;
	ISeriesPtr pBLSeries,pPLSeries;
	pBLSeries = pPLSeries	=	NULL;
	LPDISPATCH pDisp	=	NULL;
	for (int m= nStartIndex; m<=nEndIndex/*nPeaksCount*/; m++)
	{

		nTempM = m;
		if (m_objPeakInfo->arrStartPointType.GetAt(m) == TYPE_HORZ_BASE)
		{
			long lngSeriesNo	=	m_chart.AddSeries(0); // To hold the Graph ID which is used for BaseLine Drawing
			pDisp	=	m_chart.Series(lngSeriesNo);// Smart pointer for 'Series' interface of series used for Baseline
			pBLSeries	=	pDisp;
			pDisp->Release();
			pBLSeries->put_Color(m_clrBaseLineColor);//RGB(0,0,0));
			pBLSeries->ShowInLegend	=	FALSE;

			for (int n=m; n<=nEndIndex/*nPeaksCount*/; n++)
			{
				if (m_objPeakInfo->arrEndPointType.GetAt(n) == TYPE_HORZ_BASE)
				{
					double dblXTemp;
					dblEndX = m_objPeakInfo->dblPeakEndX.GetAt(n);
					if (m_objPeakInfo->dblPeakStartY.GetAt(m) > m_objPeakInfo->dblPeakEndY.GetAt(n))
					{

						dblY = m_objPeakInfo->dblPeakEndY.GetAt(n);
						dblXTemp = m_objPeakInfo->dblPeakStartX.GetAt(m);
					}
					else
					{

						dblY = m_objPeakInfo->dblPeakStartY.GetAt(m);
						//dblXTemp = m_objPeakInfo->dblPeakStartX.GetAt(n);
						dblXTemp = m_objPeakInfo->dblPeakEndX.GetAt(n);
					}

					//Draw base line
					pBLSeries->AddXY(m_objPeakInfo->dblPeakStartX.GetAt(m),dblY,_bstr_t(_T("")),RGB(255,0,0));
					pBLSeries->AddXY(m_objPeakInfo->dblPeakEndX.GetAt(n),dblY,_bstr_t(_T("")),RGB(255,0,0));

					if (m==n)
					{	
						//Draw the base line
						pBLSeries->AddXY(dblStartX, dblY,_bstr_t(_T("")),RGB(0,0,0));
						pBLSeries->AddXY(dblEndX, dblY,_bstr_t(_T("")),RGB(0,0,0));

						//Calculate the peak Information
						//Get the peak start index
						long lngStartIndex = m_objPeakInfo->intPeakStartIndex.GetAt(m);
						//Get the peak end index
						long lngEndIndex = m_objPeakInfo->intPeakEndIndex.GetAt(n);
						//Get the index of maximum height in the peak
						long lngMaxHeightIndex = m_objPeakInfo->intPeakMaxIndex.GetAt(m);
						//Calculate the number of points on peak
						long lngPointCount = lngEndIndex - lngStartIndex +1;
						long lngTempPeakCount = lngPointCount;
						lngPointCount+=2;
						lngTempPeakCount++;

						long lngPerpendicularNo	=	m_chart.AddSeries(0); // To hold the Graph ID which is used for BaseLine Drawing
						pDisp	=	m_chart.Series(lngPerpendicularNo);// Smart pointer for 'Series' interface of series used for Baseline
						pPLSeries	=	pDisp;
						pPLSeries->put_Color(RGB(0,0,255));
						pPLSeries->ShowInLegend	=	FALSE;

						//perpendicular line draw
						//pPLSeries->AddXY(m_objPeakInfo->dblPeakEndX.GetAt(m+k-1),m_objPeakInfo->dblPeakEndY.GetAt(m+k-1),_bstr_t(_T("")),RGB(0,0,255));
						//pPLSeries->AddXY(m_objPeakInfo->dblPeakEndX.GetAt(m+k-1),YOnBL,_bstr_t(_T("")),RGB(0,0,255));
						//Get the peak data
						double* dblXArr = new double[lngPointCount+1];
						double* dblYArr = new double[lngPointCount+1];

						int y=0;
						if (m_objPeakInfo->dblPeakStartY.GetAt(m) > m_objPeakInfo->dblPeakEndY.GetAt(n))
						{
							dblXArr[y] = dblXTemp;
							dblYArr[y] = dblY;

							pPLSeries->AddXY(m_objPeakInfo->dblPeakStartX.GetAt(m),m_objPeakInfo->dblPeakStartY.GetAt(m),_bstr_t(_T("")),RGB(0,0,255));
							pPLSeries->AddXY(m_objPeakInfo->dblPeakStartX.GetAt(m),dblY,_bstr_t(_T("")),RGB(0,0,255));

							y++;
						}
						else
						{

							dblXArr[y] = m_objPeakInfo->dblPeakStartX.GetAt(m);
							dblYArr[y] = dblY;


							y++;

						}
						for (; y<lngTempPeakCount; y++)
						{
							stuPeakDetectPoint objPeakPoint = m_arrPeakDetectPoint.GetAt(lngStartIndex);
							dblXArr[y] = objPeakPoint.X;
							dblYArr[y] = objPeakPoint.Y;



							lngStartIndex++;
						}
						if (m_objPeakInfo->dblPeakStartY.GetAt(m) <= m_objPeakInfo->dblPeakEndY.GetAt(n))
						{
							dblXArr[y] = dblXTemp;
							dblYArr[y] = dblY;



							pPLSeries->AddXY(m_objPeakInfo->dblPeakEndX.GetAt(m),m_objPeakInfo->dblPeakEndY.GetAt(m),_bstr_t(_T("")),RGB(0,0,255));
							pPLSeries->AddXY(m_objPeakInfo->dblPeakEndX.GetAt(m),dblY,_bstr_t(_T("")),RGB(0,0,255));
						}
						else
						{

							dblXArr[y] = m_objPeakInfo->dblPeakEndX.GetAt(n);
							dblYArr[y] = dblY;

						}


						//Perform Peak calculations
						double dblPeakArea, dblPeakFWHH, dblPeakHeight, dblPeakWidth;
						fncPeakCalculations(lngMaxHeightIndex, dblXArr, dblYArr, lngPointCount,&dblPeakArea, &dblPeakFWHH, &dblPeakHeight, &dblPeakWidth,m);

						m=n++;//added by sivaganesh on 20-06-08

					}
					else
					{
						//Check for Number of valley between the base points

						//calculate the slope of base line
						if ((m_objPeakInfo->dblPeakEndX.GetAt(n) - m_objPeakInfo->dblPeakStartX.GetAt(m)) != 0)
							//dblSLope = (m_objPeakInfo->dblPeakEndY.GetAt(n) - dblY/*m_objPeakInfo->dblPeakStartY.GetAt(m)*/) / (m_objPeakInfo->dblPeakEndX.GetAt(n) - m_objPeakInfo->dblPeakStartX.GetAt(m));
							dblSLope = 0.0f;//Slope of horizontal line = 0


						int nValleyCount = n - m;
						BOOL blnFound = FALSE;

						for(int k=1; k<=(nValleyCount+1);k++)
						{
							//Check for negative peak

							//Get the slope of the line joining the starting base point and current valley end point
							double dblSlopeValley =  (m_objPeakInfo->dblPeakEndY.GetAt(m+k-1)-dblY) / (m_objPeakInfo->dblPeakEndX.GetAt(m+k-1)-m_objPeakInfo->dblPeakStartX.GetAt(m));



							//Compare the slopes 
							if (dblSlopeValley<dblSLope) //Negative peak found
							{

								//Check for Negative Peak ON/OFF
								if (blnNegativePeak == FALSE)  //Negative peak OFF
								{
									m_objPeakInfo->arrStartPointType.SetAt(m+k, TYPE_BASE);
									if (k != 0)
										m_objPeakInfo->arrEndPointType.SetAt(m+k-1, TYPE_BASE);
									//Start the checking for base point from previous position
									if (k!=0)
										n=nTempM-1;
									break;
								}
								else //Negative Peak ON
								{							
									//Check whether  the current peak index is present in negative peak array or not
									int x=-1;
									for (x=0; (x<m_arrNegativeStartIndex.GetSize())&(blnFound == FALSE); x++)
									{
										if (m_arrNegativeStartIndex.GetAt(x) == (m+k-1)/*nCurrentIndex*/)
										{
											blnFound = TRUE;
											break;
										}
									}
									if (blnFound == FALSE)//Peak is not present in Negative peaks list
									{
										m_objPeakInfo->arrStartPointType.SetAt(m+k, TYPE_BASE);
										if (k != 0)
											m_objPeakInfo->arrEndPointType.SetAt(m+k-1, TYPE_BASE);
										//Start the checking for base point from previous position
										if (k!=0)
											n=nTempM-1;
										break;
									}
									else //Peak found in the negative peaks list
									{
										//check for corresponding negative peak end index
										if ( (m+k-1) > m_arrNegativeEndIndex.GetAt(x))
										{
											blnFound = FALSE;
											m_objPeakInfo->arrStartPointType.SetAt(m+k, TYPE_BASE);
											if (k != 0)
												m_objPeakInfo->arrEndPointType.SetAt(m+k-1, TYPE_BASE);
											//Start the checking for base point from previous position
											if (k!=0)
												n=nTempM-1;
											break;
										}
										//Draw the perpendicular line
										dblXValueAtValley = m_objPeakInfo->dblPeakEndX.GetAt(m+k-1);

										YOnBL = dblSLope * (dblXValueAtValley - m_objPeakInfo->dblPeakStartX.GetAt(m)) + (m_objPeakInfo->dblPeakStartY.GetAt(m));

										long lngPerpendicularNo	=	m_chart.AddSeries(0); // To hold the Graph ID which is used for BaseLine Drawing
										pDisp	=	m_chart.Series(lngPerpendicularNo);// Smart pointer for 'Series' interface of series used for Baseline
										pPLSeries	=	pDisp;
										pDisp->Release();
										pPLSeries->put_Color(RGB(0,0,255));
										pPLSeries->ShowInLegend	=	FALSE;

										//perpendicular line draw
										pPLSeries->AddXY(m_objPeakInfo->dblPeakEndX.GetAt(m+k-1),m_objPeakInfo->dblPeakEndY.GetAt(m+k-1),_bstr_t(_T("")),RGB(0,0,255));
										pPLSeries->AddXY(m_objPeakInfo->dblPeakEndX.GetAt(m+k-1),YOnBL,_bstr_t(_T("")),RGB(0,0,255));

										//Do calculations on the peak

										//Get the peak start index
										long lngStartIndex = m_objPeakInfo->intPeakStartIndex.GetAt(m+k-1);
										//Get the peak end index
										long lngEndIndex = m_objPeakInfo->intPeakEndIndex.GetAt(m+k-1);
										//Get the index of maximum height in the peak
										long lngMaxHeightIndex = m_objPeakInfo->intPeakMaxIndex.GetAt(m+k-1);
										//Calculate the number of points on peak
										long lngPointCount = lngEndIndex - lngStartIndex +1;
										long lngTempPeakCount = lngPointCount;
										//Add Valley point(s)
										if (m_objPeakInfo->arrStartPointType.GetAt(m+k-1) == TYPE_VALLEY)
										{
											lngPointCount += 1;
											lngTempPeakCount++;
										}
										if (m_objPeakInfo->arrEndPointType.GetAt(m+k-1) == TYPE_VALLEY)
											lngPointCount += 1;
										//31/5/2008
										if ( (m_objPeakInfo->arrStartPointType.GetAt(m+k-1) == TYPE_HORZ_BASE) && (m_objPeakInfo->dblPeakStartY.GetAt(m+k-1)>dblY) )
											lngPointCount += 1;
										if ( (m_objPeakInfo->arrEndPointType.GetAt(m+k-1) == TYPE_HORZ_BASE) && (m_objPeakInfo->dblPeakEndY.GetAt(m+k-1)>dblY) )
											lngPointCount += 1;
										//31/5/2008
										//Get the peak data
										double* dblXArr = new double[lngPointCount];
										double* dblYArr = new double[lngPointCount];
										int x=0;
										//31/5/2008
										if ( (m_objPeakInfo->arrStartPointType.GetAt(m+k-1) == TYPE_HORZ_BASE) && (m_objPeakInfo->dblPeakStartY.GetAt(m+k-1)>dblY) )
										{
											dblXArr[x] = m_objPeakInfo->dblPeakStartX.GetAt(m+k-1);
											dblYArr[x] = dblY;
											x++;
										}
										//31/5/2008
										//Add the point on Base line on left side of peak
										if (m_objPeakInfo->arrStartPointType.GetAt(m+k-1) == TYPE_VALLEY)
										{
											stuPeakDetectPoint objPeakPoint = m_arrPeakDetectPoint.GetAt(lngStartIndex);
											dblXArr[x] = objPeakPoint.X;
											dblYArr[x] = dblSLope * (objPeakPoint.X - m_objPeakInfo->dblPeakStartX.GetAt(m)) + (m_objPeakInfo->dblPeakStartY.GetAt(m));
											x++;
										}
										for (; x<lngTempPeakCount; x++)
										{
											stuPeakDetectPoint objPeakPoint = m_arrPeakDetectPoint.GetAt(lngStartIndex);
											dblXArr[x] = objPeakPoint.X;
											dblYArr[x] = objPeakPoint.Y;
											lngStartIndex++;
										}
										//Add the point on Base line on right side of peak
										if (m_objPeakInfo->arrEndPointType.GetAt(m+k-1) == TYPE_VALLEY)
										{
											stuPeakDetectPoint objPeakPoint = m_arrPeakDetectPoint.GetAt(lngEndIndex);
											dblXArr[x] = objPeakPoint.X;
											dblYArr[x] = YOnBL;
										}
										//31/5/2008
										if ( (m_objPeakInfo->arrEndPointType.GetAt(m+k-1) == TYPE_HORZ_BASE) && (m_objPeakInfo->dblPeakEndY.GetAt(m+k-1)>dblY) )
										{
											dblXArr[x] = m_objPeakInfo->dblPeakEndX.GetAt(m+k-1);
											dblYArr[x] = dblY;
											x++;
										}


										//31/5/2008
										//Perform Peak calculations
										double dblPeakArea, dblPeakFWHH, dblPeakHeight, dblPeakWidth;
										fncPeakCalculations(lngMaxHeightIndex, dblXArr, dblYArr, lngPointCount,&dblPeakArea, &dblPeakFWHH, &dblPeakHeight, &dblPeakWidth,m+k-1);

									}
								}
								pPLSeries	=	NULL;

							}
							else  //Not a negative peak. Draw the perpendicular line
							{

								long lngPerpendicularNo	=	m_chart.AddSeries(0); // To hold the Graph ID which is used for BaseLine Drawing
								pDisp	=	m_chart.Series(lngPerpendicularNo);// Smart pointer for 'Series' interface of series used for Baseline
								pPLSeries	=	pDisp;
								pDisp->Release();
								pPLSeries->put_Color(RGB(0,0,255));
								pPLSeries->ShowInLegend	=	FALSE;

								//perpendicular line draw
								if(m_objPeakInfo->dblPeakEndY.GetAt(m+k-1)!=dblY && m_objPeakInfo->arrEndPointType.GetAt(m+k-1)!=TYPE_HORZ_BASE)	
								{
									pPLSeries->AddXY(m_objPeakInfo->dblPeakEndX.GetAt(m+k-1),m_objPeakInfo->dblPeakEndY.GetAt(m+k-1),_bstr_t(_T("")),RGB(0,0,255));
									pPLSeries->AddXY(m_objPeakInfo->dblPeakEndX.GetAt(m+k-1),dblY,_bstr_t(_T("")),RGB(0,0,255));
								}

								//Do calculations on the peak
								//Get the peak start index
								long lngStartIndex = m_objPeakInfo->intPeakStartIndex.GetAt(m+k-1);
								//Get the peak end index
								long lngEndIndex = m_objPeakInfo->intPeakEndIndex.GetAt(m+k-1);
								//Get the index of maximum height in the peak
								long lngMaxHeightIndex = m_objPeakInfo->intPeakMaxIndex.GetAt(m+k-1);

								//Calculate the number of points on peak
								long lngPointCount = lngEndIndex - lngStartIndex +1;
								long lngTempPeakCount = lngPointCount;

								lngPointCount+=2;
								lngTempPeakCount++;

								//Get the peak data

								double* dblXArr = new double[lngPointCount];
								double* dblYArr = new double[lngPointCount];

								int x=0;
								if ((m_objPeakInfo->arrStartPointType.GetAt(m+k-1) == TYPE_HORZ_BASE)/*&& (m_objPeakInfo->dblPeakStartY.GetAt(m+k-1)>dblY) */)
								{
									dblXArr[x] = m_objPeakInfo->dblPeakStartX.GetAt(m+k-1);
									dblYArr[x] = dblY;

									if (m_objPeakInfo->dblPeakStartY.GetAt(m+k-1)!=dblY)
									{
										pBLSeries->AddXY(m_objPeakInfo->dblPeakStartX.GetAt(m+k-1),m_objPeakInfo->dblPeakStartY.GetAt(m+k-1),_bstr_t(_T("")),RGB(0,0,255));
										pBLSeries->AddXY(m_objPeakInfo->dblPeakStartX.GetAt(m+k-1),dblY,_bstr_t(_T("")),RGB(0,0,255));
									}

									x++;
								}

								//31/5/2008
								//Add the point on Base line on left side of peak
								if (m_objPeakInfo->arrStartPointType.GetAt(m+k-1) == TYPE_VALLEY)
								{
									stuPeakDetectPoint objPeakPoint = m_arrPeakDetectPoint.GetAt(lngStartIndex);
									dblXArr[x] = objPeakPoint.X;
									dblYArr[x] = dblY;//dblSLope * (objPeakPoint.X - m_objPeakInfo->dblPeakStartX.GetAt(m)) + (m_objPeakInfo->dblPeakStartY.GetAt(m));

									x++;
								}
								for (; x<lngTempPeakCount; x++)
								{
									stuPeakDetectPoint objPeakPoint = m_arrPeakDetectPoint.GetAt(lngStartIndex);
									dblXArr[x] = objPeakPoint.X;
									dblYArr[x] = objPeakPoint.Y;

									lngStartIndex++;
								}
								//Add the point on Base line on right side of peak
								if (m_objPeakInfo->arrEndPointType.GetAt(m+k-1) == TYPE_VALLEY)
								{
									stuPeakDetectPoint objPeakPoint = m_arrPeakDetectPoint.GetAt(lngEndIndex);
									dblXArr[x] = objPeakPoint.X;
									dblYArr[x] = dblY;

								}
								//31/5/2008
								if ( (m_objPeakInfo->arrEndPointType.GetAt(m+k-1) == TYPE_HORZ_BASE) /*&& (m_objPeakInfo->dblPeakEndY.GetAt(m+k)>dblY)*/ )
								{
									dblXArr[x] = m_objPeakInfo->dblPeakEndX.GetAt(m+k-1);
									dblYArr[x] = dblY;

									pBLSeries->AddXY(m_objPeakInfo->dblPeakEndX.GetAt(m+k-1),m_objPeakInfo->dblPeakEndY.GetAt(m+k-1),_bstr_t(_T("")),RGB(0,0,255));
									pBLSeries->AddXY(m_objPeakInfo->dblPeakEndX.GetAt(m+k-1),dblY,_bstr_t(_T("")),RGB(0,0,255));
								}

								//31/5/2008
								//Perform Peak calculations
								double dblPeakArea, dblPeakFWHH, dblPeakHeight, dblPeakWidth;
								fncPeakCalculations(lngMaxHeightIndex, dblXArr, dblYArr, lngPointCount,&dblPeakArea, &dblPeakFWHH, &dblPeakHeight, &dblPeakWidth,m+k-1);

								pPLSeries	=	NULL;
							}
						}
					}
					break;//added by sivaganesh on 20-06-08
				}
			}
		}
		pBLSeries	=	NULL;
	}//'for' loop
}
void CEsdAdvancedGraphCtrl::fncApplyManualSkimming(int nStartIndex)
{
	CString str;
	str.Format(_T("%d"),nStartIndex);
	AfxMessageBox(str);

}
void CEsdAdvancedGraphCtrl::fncStartDetect(double dblStartTime, double dblEndTime, double dblValue)
{
	long lngPeaksCount =(long) m_objTempPeakInfo->arrStartPointType.GetSize();
	if (lngPeaksCount == 0)
	{
		return;
	}
	int nStartPeakIndex=-1, nEndPeakIndex =-1;
	if((dblStartTime==0.0)&(dblEndTime==0.0))
	{
		AfxMessageBox(L"Enter Start and End Time");
		return;
	}
	if(dblStartTime<0.0||dblEndTime<0.0)
	{
		AfxMessageBox(_T("Time cannot be negative."));
		return;
	}
	if(dblStartTime>=dblEndTime)
	{
		AfxMessageBox(_T("End time should be greater than start time"));
		return;

	}

	if(lngPeaksCount == m_objPeakInfo->arrStartPointType.GetSize())
	{
		m_objPeakInfo->arrStartPointType.RemoveAll();
		m_objPeakInfo->arrEndPointType.RemoveAll();
		m_objPeakInfo->dblArea.RemoveAll();
		m_objPeakInfo->dblHeight.RemoveAll();
		m_objPeakInfo->dblPeakEndX.RemoveAll();
		m_objPeakInfo->dblPeakEndY.RemoveAll();
		m_objPeakInfo->dblPeakMaxX.RemoveAll();
		m_objPeakInfo->dblPeakMaxY.RemoveAll();
		m_objPeakInfo->dblPeakStartX.RemoveAll();
		m_objPeakInfo->dblPeakStartY.RemoveAll();
		m_objPeakInfo->dblWidth.RemoveAll();
		m_objPeakInfo->intPeakEndIndex.RemoveAll();
		m_objPeakInfo->intPeakMaxIndex.RemoveAll();
		m_objPeakInfo->intPeakStartIndex.RemoveAll();

	}

	BOOL bPeakCom=FALSE;

	if (m_objPeakInfo->arrStartPointType.GetSize()>0)
	{

		if( (m_objPeakInfo->dblPeakStartX.GetAt(0) <= dblStartTime) && (dblStartTime < m_objPeakInfo->dblPeakEndX.GetAt(m_objPeakInfo->arrStartPointType.GetSize()-1)))
		{
			bPeakCom=TRUE;
		}

		if ((m_objPeakInfo->dblPeakStartX.GetAt(0) <= dblEndTime) && (dblEndTime < m_objPeakInfo->dblPeakEndX.GetAt(m_objPeakInfo->arrStartPointType.GetSize()-1)))
		{
			bPeakCom=TRUE;
		}

	}


	if (bPeakCom==TRUE)
	{
		AfxMessageBox(_T("Cannot Apply Event Between this Range"));
		return;
	}


	//Find the peak on which the start time lie


	for(int nFind=0;nFind<lngPeaksCount;nFind++)
	{	

		if( (m_objTempPeakInfo->dblPeakStartX.GetAt(nFind) <= dblStartTime) && (dblStartTime < m_objTempPeakInfo->dblPeakEndX.GetAt(nFind) ) )
		{

			CString strtime,strStartx,strStarttime;
			strtime.Format(_T("%lf"),m_objTempPeakInfo->dblPeakStartX.GetAt(nFind));
			strStartx=strtime.Left(4);
			strtime.Format(_T("%lf"),dblStartTime);
			strStarttime=strtime.Left(4);

			if (strStartx==strStarttime)
				nStartPeakIndex = nFind;
			else
				nStartPeakIndex = nFind+1;
			break;
		}
	}

	if (nStartPeakIndex==-1)
	{
		for(int nFind=0;nFind<lngPeaksCount-1;nFind++)
		{		
			if( (m_objTempPeakInfo->dblPeakEndX.GetAt(nFind) <= dblStartTime) && (dblStartTime < m_objTempPeakInfo->dblPeakStartX.GetAt(nFind+1) ) )
			{
				nStartPeakIndex = nFind+1;
				break;
			}
		}
	}
	if(nStartPeakIndex==-1)
	{
		nStartPeakIndex=0;

	}
	if(dblEndTime!=0)
	{

		for(int nFind=0;nFind<lngPeaksCount;nFind++)
		{	


			if( (m_objTempPeakInfo->dblPeakStartX.GetAt(nFind) <= dblEndTime) && (dblEndTime < m_objTempPeakInfo->dblPeakEndX.GetAt(nFind) ) )
			{
				CString strtime,strstartx,strEndTime;
				strtime.Format(_T("%lf"),m_objTempPeakInfo->dblPeakStartX.GetAt(nFind));
				strstartx=strtime.Left(4);
				strtime.Format(_T("%lf"),dblEndTime);
				strEndTime=strtime.Left(4);			
				if(strEndTime==strstartx)
					nEndPeakIndex=nFind;			
				else
					nEndPeakIndex = nFind-1;
				break;

			}

		}

		if (nEndPeakIndex==-1)
		{
			for(int nFind=0;nFind<lngPeaksCount-1;nFind++)
			{

				if( (m_objTempPeakInfo->dblPeakEndX.GetAt(nFind) <= dblEndTime) && (dblEndTime < m_objTempPeakInfo->dblPeakStartX.GetAt(nFind+1) ) )
				{
					nEndPeakIndex=nFind;
				}

			}
		}


		if (nEndPeakIndex==-1)
		{
			nEndPeakIndex =lngPeaksCount-1;
		}

	}
	else
		nEndPeakIndex=lngPeaksCount-1;




	m_objTempPeakInfo->arrStartPointType.SetAt(nStartPeakIndex,TYPE_BASE);
	m_objTempPeakInfo->arrEndPointType.SetAt(nEndPeakIndex,TYPE_BASE);

	if(nStartPeakIndex!=0)
	{
		m_objTempPeakInfo->arrEndPointType.SetAt(nStartPeakIndex-1,TYPE_BASE);
	}
	if (nEndPeakIndex!=lngPeaksCount-1)
	{
		m_objTempPeakInfo->arrStartPointType.SetAt(nEndPeakIndex+1,TYPE_BASE);
	}


	for(int nIndex = nStartPeakIndex; nIndex<= nEndPeakIndex;nIndex++)
	{

		m_objPeakInfo->arrStartPointType.Add(m_objTempPeakInfo->arrStartPointType.GetAt(nIndex));
		m_objPeakInfo->arrEndPointType.Add(m_objTempPeakInfo->arrEndPointType.GetAt(nIndex));
		m_objPeakInfo->dblArea.Add(m_objTempPeakInfo->dblArea.GetAt(nIndex));
		m_objPeakInfo->dblHeight.Add(m_objTempPeakInfo->dblHeight.GetAt(nIndex));
		m_objPeakInfo->dblPeakEndX.Add(m_objTempPeakInfo->dblPeakEndX.GetAt(nIndex));
		m_objPeakInfo->dblPeakEndY.Add(m_objTempPeakInfo->dblPeakEndY.GetAt(nIndex));
		m_objPeakInfo->dblPeakMaxX.Add(m_objTempPeakInfo->dblPeakMaxX.GetAt(nIndex));
		m_objPeakInfo->dblPeakMaxY.Add(m_objTempPeakInfo->dblPeakMaxY.GetAt(nIndex));
		m_objPeakInfo->dblPeakStartX.Add(m_objTempPeakInfo->dblPeakStartX.GetAt(nIndex));
		m_objPeakInfo->dblPeakStartY.Add(m_objTempPeakInfo->dblPeakStartY.GetAt(nIndex));
		m_objPeakInfo->dblWidth.Add(m_objTempPeakInfo->dblWidth.GetAt(nIndex));
		m_objPeakInfo->intPeakEndIndex.Add(m_objTempPeakInfo->intPeakEndIndex.GetAt(nIndex));
		m_objPeakInfo->intPeakMaxIndex.Add(m_objTempPeakInfo->intPeakMaxIndex.GetAt(nIndex));
		m_objPeakInfo->intPeakStartIndex.Add(m_objTempPeakInfo->intPeakStartIndex.GetAt(nIndex));

		//added by sirisha on 3/1/2012
		//to solve error while startdetect and stopdetect are fall in common region and stopdetection and before startdetection stopdetection should be carried out.
		//reason:
		//in stopdetection ,all the peakinfo related to the peaks detected in the specified region will be removed from the peakinfo array.
		//and also the values  of different widths related to those peaks will be removed from the   respective arrays.  
		//so here after detecting peak ,along with the peakinfo width at different heights for the respective should also be calculated and stored.
		//for this purpose we called this function for calculating and storing width values for the detected peaks.
		//other wise we will get error while trying to retrieve width values in fncPeakInformation() function CReprocessView class.

		fncWidthAtDiffHeights(m_objTempPeakInfo->intPeakStartIndex.GetAt(nIndex),m_objTempPeakInfo->intPeakEndIndex.GetAt(nIndex),m_objTempPeakInfo->intPeakMaxIndex.GetAt(nIndex));

	}

}
void CEsdAdvancedGraphCtrl::fncStopDetect(double dblStartTime, double dblEndTime, double dblValue)
{

	long lngPeaksCount = (long)m_objPeakInfo->arrStartPointType.GetSize();
	int nStartPeakIndex=-1, nEndPeakIndex = -1;

	if(dblStartTime<0.0||dblEndTime<0.0)
	{
		AfxMessageBox(_T("Time cannot be negative."));
		return;
	}
	if((dblStartTime==0.0)&(dblEndTime==0.0))
	{
		AfxMessageBox(L"Enter start and End Time");
		return;
	}

	if(dblStartTime>=dblEndTime)
	{
		AfxMessageBox(_T("End time should be greater than start time"));
		return;

	}
	try
	{


		//Find the peak on which the start time lie
		for(int nFind=0;nFind<lngPeaksCount;nFind++)
		{			
			if((m_objPeakInfo->dblPeakStartX.GetAt(nFind) <= dblStartTime) && (dblStartTime < m_objPeakInfo->dblPeakEndX.GetAt(nFind) ) )
			{								
				if ((dblStartTime-m_objPeakInfo->dblPeakStartX.GetAt(nFind))<=0.006)
				{								
					nStartPeakIndex = nFind;
				}
				else
					nStartPeakIndex = nFind+1;

				break;
			}

		}
		if (nStartPeakIndex==-1)
		{
			for(int nFind=0;nFind < lngPeaksCount-1;nFind++)
			{
				if( (m_objPeakInfo->dblPeakEndX.GetAt(nFind) <= dblStartTime) && (dblStartTime < m_objPeakInfo->dblPeakStartX.GetAt(nFind+1) ) )
				{
					nStartPeakIndex=nFind+1;
				}

			}
		}

		if (nStartPeakIndex==-1)
		{
			//nStartPeakIndex=lngPeaksCount;
			nStartPeakIndex=0;
		}

		if(dblEndTime != 0)
		{
			for(int nFind=0;nFind < lngPeaksCount;nFind++)
			{	
				if( (m_objPeakInfo->dblPeakStartX.GetAt(nFind) <= dblEndTime) && (dblEndTime <m_objPeakInfo->dblPeakEndX.GetAt(nFind) ) )
				{
					CString strtime,strEndTime,strstartx;
					strtime.Format(_T("%lf"),m_objPeakInfo->dblPeakStartX.GetAt(nFind));
					strstartx=strtime.Left(4);
					strtime.Format(_T("%lf"),dblEndTime);
					strEndTime=strtime.Left(4);
					if (strstartx==strEndTime)
					{								
						nEndPeakIndex = nFind;
					}
					else
						nEndPeakIndex = nFind-1;
					break;
				}
			}


			if (nEndPeakIndex == -1)
			{
				for(int nFind=0;nFind<lngPeaksCount-1;nFind++)
				{

					if( (m_objPeakInfo->dblPeakEndX.GetAt(nFind) <= dblEndTime) && (dblEndTime < m_objPeakInfo->dblPeakStartX.GetAt(nFind+1) ) )
					{
						nEndPeakIndex = nFind;
					}
				}
			}

			if (nEndPeakIndex == -1)
			{
				if( lngPeaksCount>=1 && (dblEndTime>=m_objPeakInfo->dblPeakEndX.GetAt(lngPeaksCount-1)))
					nEndPeakIndex =lngPeaksCount-1;
				else
					return;
			}
		}
		else
			nEndPeakIndex = lngPeaksCount-1;

		if(nStartPeakIndex!=0)
		{
			m_objPeakInfo->arrEndPointType.SetAt(nStartPeakIndex-1,TYPE_BASE);
		}

		if (nEndPeakIndex !=0)
		{
			if(nEndPeakIndex != lngPeaksCount-1)
				m_objPeakInfo->arrStartPointType.SetAt(nEndPeakIndex+1,TYPE_BASE);
		}
		for(int nIndex =  nStartPeakIndex; nIndex <= nEndPeakIndex; nIndex++)
		{
			m_objPeakInfo->arrStartPointType.RemoveAt(nStartPeakIndex,1);
			m_objPeakInfo->arrEndPointType.RemoveAt(nStartPeakIndex,1);
			m_objPeakInfo->dblArea.RemoveAt(nStartPeakIndex,1);
			m_objPeakInfo->dblHeight.RemoveAt(nStartPeakIndex,1);
			m_objPeakInfo->dblPeakEndX.RemoveAt(nStartPeakIndex,1);
			m_objPeakInfo->dblPeakEndY.RemoveAt(nStartPeakIndex,1);
			m_objPeakInfo->dblPeakMaxX.RemoveAt(nStartPeakIndex,1);
			m_objPeakInfo->dblPeakMaxY.RemoveAt(nStartPeakIndex,1);
			m_objPeakInfo->dblPeakStartX.RemoveAt(nStartPeakIndex,1);
			m_objPeakInfo->dblPeakStartY.RemoveAt(nStartPeakIndex,1);
			m_objPeakInfo->dblWidth.RemoveAt(nStartPeakIndex,1);
			m_objPeakInfo->intPeakEndIndex.RemoveAt(nStartPeakIndex,1);
			m_objPeakInfo->intPeakMaxIndex.RemoveAt(nStartPeakIndex,1);
			m_objPeakInfo->intPeakStartIndex.RemoveAt(nStartPeakIndex,1);
			m_dblWidthAt10PercentHeight.RemoveAt(nStartPeakIndex,1);
			m_dblRightWidthAt5PercentHeight.RemoveAt(nStartPeakIndex,1);
			m_dblWidthAtHalfHeight.RemoveAt(nStartPeakIndex,1);
			m_dblRightWidthAtHalfHeight.RemoveAt(nStartPeakIndex,1);
			m_dblRightWidthAt10PercentHeight.RemoveAt(nStartPeakIndex,1);
			m_dblLeftWidthAt10PercentHeight.RemoveAt(nStartPeakIndex,1);
			m_dblLeftWidthAtHalfHeight.RemoveAt(nStartPeakIndex,1);
			m_dblWidthAt5PercentHeight.RemoveAt(nStartPeakIndex,1);
			m_dblLeftWidthAt5PercentHeight.RemoveAt(nStartPeakIndex,1);


		}
	}
	catch (...)
	{
		AfxMessageBox(_T("unable to perform Stop detection Timed Event"));
	}

}


void CEsdAdvancedGraphCtrl::fncHeightReject(double dblStartTime, double dblEndTime, double dblValue)
{
	long lngPeaksCount = (long)m_objPeakInfo->arrStartPointType.GetSize();
	int nStartPeakIndex=-1, nEndPeakIndex = lngPeaksCount-1;


	for(int nFind=0;nFind<lngPeaksCount;nFind++)
	{		
		if( (m_objPeakInfo->dblPeakStartX.GetAt(nFind) <= dblStartTime) && (dblStartTime < m_objPeakInfo->dblPeakEndX.GetAt(nFind) ) )
		{
			if (m_objPeakInfo->dblPeakStartX.GetAt(nFind) == dblStartTime)
				nStartPeakIndex = nFind;
			else
				nStartPeakIndex = nFind+1;
			break;
		}
	}
	//If the start time does not lie on the peak then get the index of next immediate peak
	if (nStartPeakIndex == -1)
	{
		for(int nFind=0;nFind<lngPeaksCount-1;nFind++)
		{		
			if( (m_objPeakInfo->dblPeakEndX.GetAt(nFind) <= dblStartTime) && (dblStartTime < m_objPeakInfo->dblPeakStartX.GetAt(nFind+1) ) )
			{
				nStartPeakIndex = nFind+1;
				break;
			}
		}
	}

}
void CEsdAdvancedGraphCtrl::fncTangentSkiming(double dblStartTime, double dblEndTime, double dblValue)
{
	long lngPeakCount=(long)m_objPeakInfo->arrStartPointType.GetSize();

	int nStartPeakIndex=-1,nEndPeakIndex=-1;

	double dblRHeight,dblHeight,dblSkimRatio;
	if((dblStartTime==0.0)&(dblEndTime==0.0))
	{
		AfxMessageBox(L"Enter Start Time");
		return;
	}

	if(dblStartTime<0.0||dblEndTime<0.0)
	{
		AfxMessageBox(_T("Time cannot be negative."));
		return;
	}
	/*if(dblStartTime<m_objPeakInfo->dblPeakStartX.GetAt(0)||(dblStartTime>m_objPeakInfo->dblPeakEndX.GetAt(lngPeakCount-1)))
	{
	AfxMessageBox(L"Start time is Out of peak detection range.");
	return;
	}*/

	for(int nFind=0;nFind<lngPeakCount;nFind++)
	{
		if ((m_objPeakInfo->dblPeakStartX.GetAt(nFind) <= dblStartTime) && (dblStartTime < m_objPeakInfo->dblPeakEndX.GetAt(nFind)))
		{
			if(m_objPeakInfo->arrStartPointType.GetAt(nFind)==TYPE_VALLEY )
			{
				dblRHeight = m_objPeakInfo->dblPeakMaxY.GetAt(nFind-1)-m_objPeakInfo->dblPeakEndY.GetAt(nFind-1);
				dblHeight= m_objPeakInfo->dblHeight.GetAt(nFind);
				dblSkimRatio=dblHeight/dblRHeight;

				m_objPeakInfo->arrStartPointType.SetAt(nFind,TYPE_BKWSKIMMING);
				m_objPeakInfo->arrEndPointType.SetAt(nFind-1,TYPE_BKWSKIMMING);

				int m=nFind-1;

				for (;m>0;m--)
				{
					if (m_objPeakInfo->arrStartPointType.GetAt(m)==TYPE_VALLEY )
					{
						m_objPeakInfo->arrStartPointType.SetAt(m,TYPE_SkMVALLEY);
						m_objPeakInfo->arrEndPointType.SetAt(m-1,TYPE_SkMVALLEY);
					}
					if (m_objPeakInfo->arrStartPointType.GetAt(m)==TYPE_BASE ||m_objPeakInfo->arrStartPointType.GetAt(m)==TYPE_PENETRATION )
						break;


				}

			}
			if(m_objPeakInfo->arrEndPointType.GetAt(nFind)==TYPE_VALLEY)
			{
				dblRHeight = m_objPeakInfo->dblPeakMaxY.GetAt(nFind+1)-m_objPeakInfo->dblPeakStartY.GetAt(nFind+1);
				dblHeight= m_objPeakInfo->dblHeight.GetAt(nFind);
				dblSkimRatio=dblHeight/dblRHeight;

				

				m_objPeakInfo->arrEndPointType.SetAt(nFind,TYPE_FRWSKIMMING);
				m_objPeakInfo->arrStartPointType.SetAt(nFind+1,TYPE_FRWSKIMMING);


				int m=nFind+1;

				for (;m<lngPeakCount;m++)
				{
					if (m_objPeakInfo->arrEndPointType.GetAt(m)==TYPE_VALLEY)
					{
						m_objPeakInfo->arrEndPointType.SetAt(m,TYPE_SkMVALLEY);
						m_objPeakInfo->arrStartPointType.SetAt(m+1,TYPE_SkMVALLEY);
					}
					if (m_objPeakInfo->arrEndPointType.GetAt(m)==TYPE_BASE || m_objPeakInfo->arrEndPointType.GetAt(m)==TYPE_PENETRATION)
						break;
				}

				break;

			}

		}
	}


}
//added by sirisha on 21/12/2011
//This method gets called when ever user selects manual peak option in timedEvnts tab.
//This Method is used to detect the selected area between given start and end time as a peak.
//The Start and End types of Manual Peak will be set as  BASE Type.
void CEsdAdvancedGraphCtrl::fncManualBaseline(double dblStartTime, double dblEndTime, double dblValue)
{
	//long lngPeaksCount = 0;
	//if(m_objPeakInfo!=NULL)
	//	lngPeaksCount = (long)m_objPeakInfo->arrStartPointType.GetSize();

	//long lngFBSIndex = 0;
	//long lngFBEIndex = 0;



	//LPDISPATCH pDisp =	m_chart.Series(0);
	//ISeriesPtr pSeries	=	pDisp;
	//pDisp->Release();



	////For getting the index of the FBP point
	//lngFBSIndex	=	pSeries->GetXValues()->Locate(dblStartTime);
	//lngFBEIndex = pSeries->GetXValues()->Locate(dblEndTime);

	//pSeries	=	NULL;
	//for(int nFind=0;nFind<lngPeaksCount;nFind++)
	//{
	//	//on left side of the peak
	//	if((m_objPeakInfo->dblPeakStartX.GetAt(nFind) <= dblStartTime) && (dblStartTime < m_objPeakInfo->dblPeakMaxX.GetAt(nFind)))
	//	{
	//		int nMaxInd = m_objPeakInfo->intPeakMaxIndex.GetAt(nFind);
	//		int nStartInd =  m_objPeakInfo->intPeakStartIndex.GetAt(nFind);
	//		int nEndInd = m_objPeakInfo->intPeakEndIndex.GetAt(nFind);

	//		//check the point satisfies the peak criteria or not
	//		if( (nMaxInd - lngFBSIndex) >= 3)
	//		{

	//			stuPeakDetectPoint obj1 = m_arrPeakDetectPoint.GetAt(lngFBSIndex);
	//			stuPeakDetectPoint obj2 = m_arrPeakDetectPoint.GetAt(nEndInd);




	//			stuPeakDetectPoint obj = m_arrPeakDetectPoint.GetAt(lngFBSIndex);;

	//			//FBP is above the end of the peak
	//			if(obj1.Y > obj2.Y)
	//			{					
	//				//if the first peak
	//				m_objPeakInfo->arrEndPointType.SetAt(nFind,TYPE_PENETRATION);
	//				if (nFind != (m_objPeakInfo->arrStartPointType.GetSize()-1))
	//					m_objPeakInfo->arrStartPointType.SetAt(nFind+1,TYPE_PENETRATION);
	//			}


	//			//if the peaks are fused peaks
	//			m_objPeakInfo->arrStartPointType.SetAt(nFind,TYPE_BASE);
	//			if(nFind!=0)
	//				m_objPeakInfo->arrEndPointType.SetAt(nFind-1,TYPE_BASE);

	//			//changing the positions of start point of the peak
	//			m_objPeakInfo->intPeakStartIndex.SetAt(nFind,lngFBSIndex);
	//			m_objPeakInfo->dblPeakStartX.SetAt(nFind,obj.X);
	//			m_objPeakInfo->dblPeakStartY.SetAt(nFind,obj.Y);

	//		}
	//		else
	//		{
	//			AfxMessageBox(_T("Not a valid base point..."));
	//			return;
	//		}


	//	}
	//	if ((m_objPeakInfo->dblPeakMaxX.GetAt(nFind) <= dblEndTime) && (dblEndTime < m_objPeakInfo->dblPeakEndX.GetAt(nFind)))
	//	{


	//		int nMaxInd = m_objPeakInfo->intPeakMaxIndex.GetAt(nFind);

	//		//check the point satisfies the peak criteria or not
	//		if((lngFBEIndex - nMaxInd) >= 3)
	//		{				
	//			int nStartInd=  m_objPeakInfo->intPeakStartIndex.GetAt(nFind);
	//			int nEndInd  =  m_objPeakInfo->intPeakEndIndex.GetAt(nFind);

	//			stuPeakDetectPoint objStart = m_arrPeakDetectPoint.GetAt(nStartInd);

	//			stuPeakDetectPoint obj = m_arrPeakDetectPoint.GetAt(lngFBEIndex);;


	//			if(m_objPeakInfo->arrStartPointType.GetAt(nFind)  == TYPE_VALLEY)
	//			{
	//				//Get the index of previous base point
	//				int nPrevBaseIndex = 0;
	//				int m=nFind-1;						
	//				for (; m>=0; m--)
	//				{
	//					if( (m_objPeakInfo->arrStartPointType.GetAt(m)  == TYPE_BASE) || (m_objPeakInfo->arrStartPointType.GetAt(m)  == TYPE_PENETRATION)|| ((m_objPeakInfo->arrStartPointType.GetAt(m)  == TYPE_HORZ_BASE)) )
	//					{
	//						nPrevBaseIndex = m_objPeakInfo->intPeakStartIndex.GetAt(m);
	//						break;
	//					}
	//				}	
	//				if (m<0)
	//					m=0;						

	//				//Get the previous base point
	//				stuPeakDetectPoint objPrevBase;

	//				for (int n=m; n<nFind; n++)
	//				{
	//					objPrevBase = m_arrPeakDetectPoint.GetAt(nPrevBaseIndex);
	//					stuPeakDetectPoint objPrevPeak = m_arrPeakDetectPoint.GetAt(m_objPeakInfo->intPeakEndIndex.GetAt(n));

	//					//Calculate the slope of the line joining the valley and previous base point
	//					double dblSlopeValleyBase = (objPrevPeak.Y - objPrevBase.Y) /(objPrevPeak.X - objPrevBase.X);

	//					//Calculate the slope of the line joining the Force base point and Force base point
	//					double dblSlopeFBB = (objPrevBase.Y - obj.Y) /(objPrevBase.X - obj.X);

	//					//Check for negative Peak
	//					if (dblSlopeFBB > dblSlopeValleyBase)
	//					{
	//						//Make the base point type as Base 
	//						m_objPeakInfo->arrEndPointType.SetAt(n, TYPE_BASE);
	//						//Make the previous end point type as Base 
	//						if(n < (m_objPeakInfo->arrStartPointType.GetSize()-1))
	//							m_objPeakInfo->arrStartPointType.SetAt(n+1, TYPE_BASE);
	//					}
	//					if(n < (m_objPeakInfo->arrStartPointType.GetSize()-1))
	//						nPrevBaseIndex = m_objPeakInfo->intPeakStartIndex.GetAt(n+1);
	//				}
	//			}				
	//			//}

	//			//Set the peak end index, type and point
	//			m_objPeakInfo->arrEndPointType.SetAt(nFind,TYPE_BASE);
	//			m_objPeakInfo->intPeakEndIndex.SetAt(nFind,lngFBEIndex);
	//			m_objPeakInfo->dblPeakEndX.SetAt(nFind,obj.X);
	//			m_objPeakInfo->dblPeakEndY.SetAt(nFind,obj.Y);
	//			//Set the next peak start type
	//			if (nFind != (m_objPeakInfo->arrStartPointType.GetSize()-1))
	//				m_objPeakInfo->arrStartPointType.SetAt(nFind+1,TYPE_BASE);
	//		}
	//		else
	//		{
	//			AfxMessageBox(_T("Not a valid base point..."));
	//			return;
	//		}
	//	}
	//}


	//long lngStartIndex = 0;
	//long lngEndIndex = 0;
	//LPDISPATCH pDisp =	m_chart.Series(0);
	//ISeriesPtr pSeries	=	pDisp;
	//pDisp->Release();
	//
	////For getting the index of the FBP point
	//lngStartIndex	=	pSeries->GetXValues()->Locate(dblStartTime);
	//lngEndIndex =pSeries->GetXValues()->Locate(lngEndIndex);
	//
	//stuPeakDetectPoint objStartXYPoints = m_arrPeakDetectPoint.GetAt(lngFBPIndex);
	//stuPeakDetectPoint objEndXYPoints = m_arrPeakDetectPoint.GetAt(nEndInd);
	CString str;
	int nStartTimeIndex = -1;//stores the starting index of the peak.
	int nEndTimeIndex = -1;//stores the Ending index of the peak.

	//Time can't't be negative.
	if(dblStartTime<0.0||dblEndTime<0.0)
	{
		AfxMessageBox(_T("Time cannot be negative."));
		return;
	}
	//times should be valid.
	if((dblStartTime==0.0)&&(dblEndTime==0.0))
	{
		AfxMessageBox(_T("Enter Start and End Time"));
		return;
	}
	//end time must be greater than start time
	if(dblStartTime>=dblEndTime)
	{
		AfxMessageBox(_T("End time should be greater than start time"));
		return;
	}
	//find out the index for start time.

	if (!m_arrPeakDetectPoint.GetSize())
	{
		return;
	}
	for (int i=0;i<=m_arrPeakDetectPoint.GetSize()-1;i++)
	{
		stuPeakDetectPoint obj = m_arrPeakDetectPoint.GetAt(i);
		if (obj.X >= dblStartTime)
		{

			nStartTimeIndex = i;	//index at start time.
			break;
		}		
		
	}
	if (nStartTimeIndex==-1)
	{
		//AfxMessageBox(_T("Entered start time is not in the chromatogram"));
		return;
	}
	//find out the index at end time.
	for (int i=nStartTimeIndex;i<=m_arrPeakDetectPoint.GetSize()-1;i++)
	{
		stuPeakDetectPoint obj = m_arrPeakDetectPoint.GetAt(i);
		if (obj.X >= dblEndTime)
		{
			nEndTimeIndex=i;	//index at end time.
			break;
		}
	}
	//start time is not in the chromatogram limits
	if (nStartTimeIndex == -1)
	{
		AfxMessageBox(_T("Entered start time is not in the chromatogram"));
		return;
	}
	//End time is not in the chromatogram limits
	if (nEndTimeIndex == -1)
	{
		AfxMessageBox(_T("Entered End time is not in the chromatogram"));
		return;
	}
	int nFunReturnVal =0;
	nFunReturnVal=fncCheckForPeakRedundancy(dblStartTime,dblEndTime);
	if(nFunReturnVal== MANUALPEAK_NOTPOSSIBLE)
	{
		str.Format(_T("Manual Peak detection is not possible in between %lf and %lf. Event failed to meet baseline conditions."),dblStartTime,dblEndTime);
		AfxMessageBox(str);
		return;
	}	
	
	//finding the peak max index
	stuPeakDetectPoint objStPt = m_arrPeakDetectPoint.GetAt(nStartTimeIndex);
	stuPeakDetectPoint objIterationPt;
	int nPeakMaxIndex=nStartTimeIndex;	
	double dblHeihtMax=objStPt.Y;	
	for (int i=nStartTimeIndex+1;i<=nEndTimeIndex;i++)
	{
		objIterationPt = m_arrPeakDetectPoint.GetAt(i);
		if (dblHeihtMax<objIterationPt.Y)
		{
			dblHeihtMax=objIterationPt.Y;
			nPeakMaxIndex=i;
		}
	}
	int nFailedAtIndex=0;
	while(fncValidateThePoints(nStartTimeIndex,nEndTimeIndex,nPeakMaxIndex,nFailedAtIndex)==FALSE)	//line drawn with start time and end time is unsuccessfull.
	{
		if (nFailedAtIndex<=nPeakMaxIndex)
		{
			nStartTimeIndex=nFailedAtIndex;
		}
		else
		{
			nEndTimeIndex=nFailedAtIndex;
		}
	}
	stuPeakDetectPoint objTemp = m_arrPeakDetectPoint.GetAt(nStartTimeIndex);
	m_dblPeakStartX=objTemp.X;
	m_dblPeakStartY=objTemp.Y;
	// getting  XY values at peak End point, will be stored in respective member variabls.
	objTemp=m_arrPeakDetectPoint.GetAt(nEndTimeIndex);
	m_dblPeakEndX=objTemp.X;
	m_dblPeakEndY=objTemp.Y;
	// getting  XY values at peak Max point ,will be stored in respective member variabls.
	objTemp=m_arrPeakDetectPoint.GetAt(nPeakMaxIndex);
	m_dblPeakMaxX=objTemp.X;
	m_dblPeakMaxY=objTemp.Y;
	// m_nManualPeakindex = nFunReturnVal;

	BOOL bAdjuestPeak=FALSE;
	BOOL bInsertPeak=FALSE;
	if(nFunReturnVal == MANUALPEAK_NEW)
	{
		//Filling the peak structed for the manual peak.
		//int len=m_objPeakInfo->intPeakStartIndex.GetCount();
		//if(m_objPeakInfo->intPeakStartIndex.IsEmpty())
		//{
		//	//nFunReturnVal=MANUALPEAK_REPLACE;
		//	m_nManualPeakindex=0;
		//	m_objPeakInfo->arrStartPointType.InsertAt(m_nManualPeakindex,TYPE_BASE);
		//	m_objPeakInfo->arrEndPointType.InsertAt(m_nManualPeakindex,TYPE_BASE);
		//	m_objPeakInfo->dblArea.InsertAt(m_nManualPeakindex,0.0);
		//	m_objPeakInfo->dblHeight.InsertAt(m_nManualPeakindex,0.0);
		//	m_objPeakInfo->dblPeakEndX.InsertAt(m_nManualPeakindex, m_dblPeakEndX);
		//	m_objPeakInfo->dblPeakEndY.InsertAt(m_nManualPeakindex,m_dblPeakEndY);
		//	m_objPeakInfo->dblPeakMaxX.InsertAt(m_nManualPeakindex,m_dblPeakMaxX);
		//	m_objPeakInfo->dblPeakMaxY.InsertAt(m_nManualPeakindex,m_dblPeakMaxY);
		//	m_objPeakInfo->dblPeakStartX.InsertAt(m_nManualPeakindex,m_dblPeakStartX);
		//	m_objPeakInfo->dblPeakStartY.InsertAt(m_nManualPeakindex,m_dblPeakStartY);
		//	m_objPeakInfo->dblWidth.InsertAt(m_nManualPeakindex,0.0);
		//	m_objPeakInfo->intPeakEndIndex.InsertAt(m_nManualPeakindex,nEndTimeIndex);
		//	m_objPeakInfo->intPeakMaxIndex.InsertAt(m_nManualPeakindex,nPeakMaxIndex);
		//	m_objPeakInfo->intPeakStartIndex.InsertAt(m_nManualPeakindex,nStartTimeIndex);
		//} 
		//else
		//{
			try
			{
				if(m_objPeakInfo!=NULL)
				{
					//find the index number.

					m_objPeakInfo->arrStartPointType.InsertAt(m_nManualPeakindex,TYPE_BASE);
					m_objPeakInfo->arrEndPointType.InsertAt(m_nManualPeakindex,TYPE_BASE);
					m_objPeakInfo->dblArea.InsertAt(m_nManualPeakindex,0.0);
					m_objPeakInfo->dblHeight.InsertAt(m_nManualPeakindex,0.0);
					m_objPeakInfo->dblPeakEndX.InsertAt(m_nManualPeakindex, m_dblPeakEndX);
					m_objPeakInfo->dblPeakEndY.InsertAt(m_nManualPeakindex,m_dblPeakEndY);
					m_objPeakInfo->dblPeakMaxX.InsertAt(m_nManualPeakindex,m_dblPeakMaxX);
					m_objPeakInfo->dblPeakMaxY.InsertAt(m_nManualPeakindex,m_dblPeakMaxY);
					m_objPeakInfo->dblPeakStartX.InsertAt(m_nManualPeakindex,m_dblPeakStartX);
					m_objPeakInfo->dblPeakStartY.InsertAt(m_nManualPeakindex,m_dblPeakStartY);
					m_objPeakInfo->dblWidth.InsertAt(m_nManualPeakindex,0.0);
					m_objPeakInfo->intPeakEndIndex.InsertAt(m_nManualPeakindex,nEndTimeIndex);
					m_objPeakInfo->intPeakMaxIndex.InsertAt(m_nManualPeakindex,nPeakMaxIndex);
					m_objPeakInfo->intPeakStartIndex.InsertAt(m_nManualPeakindex,nStartTimeIndex);	
					bInsertPeak = TRUE;
				}
			}
			catch (CMemoryException* e)
			{
				AfxMessageBox(_T("Exception"));
			}
		/*}*/
	}
	if(nFunReturnVal == MANUALPEAK_REPLACE)
	{
		try
		{
			if(m_objPeakInfo!=NULL)
			{
				//AfxMessageBox(_T("1"));
				m_objPeakInfo->arrStartPointType.SetAt(m_nManualPeakindex,TYPE_BASE);
				m_objPeakInfo->arrEndPointType.SetAt(m_nManualPeakindex,TYPE_BASE);
				m_objPeakInfo->dblArea.SetAt(m_nManualPeakindex,0.0);
				m_objPeakInfo->dblHeight.SetAt(m_nManualPeakindex,0.0);
				m_objPeakInfo->dblPeakEndX.SetAt(m_nManualPeakindex, m_dblPeakEndX);
				m_objPeakInfo->dblPeakEndY.SetAt(m_nManualPeakindex,m_dblPeakEndY);
				m_objPeakInfo->dblPeakMaxX.SetAt(m_nManualPeakindex,m_dblPeakMaxX);
				m_objPeakInfo->dblPeakMaxY.SetAt(m_nManualPeakindex,m_dblPeakMaxY);
				m_objPeakInfo->dblPeakStartX.SetAt(m_nManualPeakindex,m_dblPeakStartX);
				m_objPeakInfo->dblPeakStartY.SetAt(m_nManualPeakindex,m_dblPeakStartY);
				m_objPeakInfo->dblWidth.SetAt(m_nManualPeakindex,0.0);
				m_objPeakInfo->intPeakEndIndex.SetAt(m_nManualPeakindex,nEndTimeIndex);
				m_objPeakInfo->intPeakMaxIndex.SetAt(m_nManualPeakindex,nPeakMaxIndex);
				m_objPeakInfo->intPeakStartIndex.SetAt(m_nManualPeakindex,nStartTimeIndex);

				bAdjuestPeak=TRUE;

			}

		}
		catch (CMemoryException* e)
		{
			AfxMessageBox(_T("4-Exception"));
		}
	}

	//After detecting peak ,widths at different heights has  to be calculated using the following method.	
	fncWidthAtDiffHeights(nStartTimeIndex,nEndTimeIndex,nPeakMaxIndex,bAdjuestPeak,bInsertPeak);
}

BOOL CEsdAdvancedGraphCtrl::fncValidateThePoints( int nStartTimeIndex, int nEndTimeIndex,int nPeakMaxIndex,int& nFailedAtIndex )
{
	//point in the graph at start time of the Manual peak.
	stuPeakDetectPoint objStPt=m_arrPeakDetectPoint.GetAt(nStartTimeIndex);
	//point in the graph at End time of the Manual peak.
	stuPeakDetectPoint objEndPt = m_arrPeakDetectPoint.GetAt(nEndTimeIndex);

	//Manual peak Algorithm is as follows.
	//Draw a line with start point and end point of the manual peak. 
	//Check the in between points are lie only one side of the line.
	//If all the points are lie only one side means baseline didn't cross the chromatogram. which is to be validation for baseline integration.
	//If the condition is success then add peak to the selected start time and end time.
	//If the condition fails then find out the appropriate start and end times for peak.

	//if a point (before the Max.Abs Point) crosses the line, then move the start time to that point. Similarly if the point(After Max.Abs Point Point) and  then cross the line then move the start time to that point

	//Next point to the point at start time in the graph.
	stuPeakDetectPoint objIterationPt = m_arrPeakDetectPoint.GetAt(nStartTimeIndex+1);

	///((x2 - x1)*(y3 - y1)) - ((y2 - y1)*(x3 - x1));

	//The above equation having three points (x1,y1), (x2,y2), (x3,y3).
	//where (x1,y1)-->point at start time of peak
	//(x2,y2)-->Point at end peak
	//(x3,y3)-->point at next to the start time of peak.
	//substitute the points in the equation and find out the result. The result may be negative or positive.
	//Find out the value at remaining points and if the value at all points is same sign as the first point then all points are falling on one side.
	double dblFirstResult = ((objEndPt.X - objStPt.X)*(objIterationPt.Y - objStPt.Y)) - ((objEndPt.Y - objStPt.Y)*(objIterationPt.X - objStPt.X));
	double dblIterationResult=0;
	
	for (int i=nStartTimeIndex+2;i<=nEndTimeIndex;i++)
	{
		objIterationPt = m_arrPeakDetectPoint.GetAt(i);
		dblIterationResult = ((objEndPt.X - objStPt.X)*(objIterationPt.Y - objStPt.Y)) - ((objEndPt.Y - objStPt.Y)*(objIterationPt.X - objStPt.X));

		if (dblFirstResult*dblIterationResult<0)
		{
			if (i<=nPeakMaxIndex)
			{
				//nStartTimeIndex=nFailedAtIndex;
				double dblY=m_arrPeakDetectPoint.GetAt(i-1).Y;
				double dblResult=objIterationPt.Y-dblY;
				nFailedAtIndex=i;
				i--;
				while(--i >= nStartTimeIndex)
				{
					if (dblResult*(dblY-m_arrPeakDetectPoint.GetAt(i).Y)<0)
					{
						nFailedAtIndex=i+1;
						return FALSE;
					}
				}
				
			}
			else
			{
				
				//double dblResult=objIterationPt.Y-dblY;		

				//i++;
				nFailedAtIndex=i;
				double dblY=objIterationPt.Y;
				while(++i < nEndTimeIndex)
				{
					if (dblY>m_arrPeakDetectPoint.GetAt(i).Y)
					{
						//double dblY=m_arrPeakDetectPoint.GetAt(i+1).Y;
						nFailedAtIndex=i;
						return FALSE;
					}

				}	

			}
			return FALSE;
		}		
	}	
	return TRUE;

}

int CEsdAdvancedGraphCtrl::fncCheckForPeakRedundancy(double dblStartTime, double dblEndTime)
{
	int nindex;
	m_nManualPeakindex=0;
	if(m_objPeakInfo->dblPeakStartX.GetSize()>0)
	{
		for(nindex = 0;nindex<=m_objPeakInfo->dblPeakStartX.GetSize()-1;nindex++)
		{
			double dbltempStartTime=m_objPeakInfo->dblPeakStartX.GetAt(nindex);	//start time of the existing peak
			double dbltempEndTime = m_objPeakInfo->dblPeakEndX.GetAt(nindex);	//end time of the existing peak
			//when one of the two times ,lies in the middle of the detected peak range ,return -1 means manual peak is not possible.
			//below if statement commented by arun. since the manual peak check conditions are changed. Allow the peak, even if one time(start time or end time) lie in the detected peaks range.
			/*if(((dblStartTime>dbltempStartTime)&&(dblEndTime>dbltempEndTime)&&(dblStartTime<dbltempEndTime))||((dblEndTime<dbltempEndTime)&&(dblStartTime<dbltempStartTime)&&(dblEndTime>dbltempStartTime)))
				return MANUALPEAK_NOTPOSSIBLE;*/
			//both start and end times lie outside of all other detected peaks, then return 1.
			if(dblStartTime <=dbltempStartTime)	//Manual peak start time is before the existing peak
			{
				if((dblEndTime <= dbltempStartTime))	//Manual peak end time is before the existing peak.
				{
					m_nManualPeakindex=nindex;	//Both conditions are true i.e, Manual peak is newer one.
					return MANUALPEAK_NEW;
				}
			}
			//when start and end times nearer to any one of the detected peak range then return the index of that peak.
			/*if(((dblStartTime <=dbltempStartTime)&&(dblEndTime >= dbltempEndTime))||((dblStartTime >= dbltempStartTime)&&(dblEndTime <= dbltempEndTime)))
			{
				m_nManualPeakindex=nindex;
				return MANUALPEAK_REPLACE;
			}*/

			if ((dblStartTime>=dbltempStartTime && dblStartTime<=dbltempEndTime) || (dblEndTime>=dbltempStartTime && dblEndTime<=dbltempEndTime) ||((dblStartTime <=dbltempStartTime)&&(dblEndTime >= dbltempEndTime))||((dblStartTime >= dbltempStartTime)&&(dblEndTime <= dbltempEndTime)))
			{
				m_nManualPeakindex=nindex;	//peak index for which manual integration is to be applied. 
				return MANUALPEAK_REPLACE;
			}
		}
		m_nManualPeakindex=nindex;
		return MANUALPEAK_NEW;
	}
	return MANUALPEAK_NEW;

}

//This function is written to calculate widths at different heights for the Manual peaks.
//In this width at 5%height ,width at 10% height and width at half height will be calculated.
//for this the following steps are used.
//Height at required position will be calculated from the actual peak height which is stored in dblTmpHeight
//**calculating X1(one end for the required width) value for one side**
//Traverse all the points from the max peak to the peak startpoint.
//take the difference of current data point Y value and start point Y value.
//compare it with the calculated height if it is less than or equal to the height then it is the 
// X1 point of the width.
//**calculating X2(one end for the required width) at other side**
//Traverse all the points from the max peak to the peak End Point.
//take the difference of current data point Y value and End point Y value.
//compare it with the calculated height if it is less than or equal to the height then it is the 
// X2 point of the width.
//Then Calculate the distance between X1 and  X2 points .
//add the calculated width  to its respective Array variable.
void CEsdAdvancedGraphCtrl::fncWidthAtDiffHeights(long lngPeakStartIndex,long lngPeakEndIndex,long lngPeakMaxIndex,BOOL bAdjuestPeak,BOOL bInsertPeak)
{
	double dblTmpHeight = 0;  
	double dblBLSLope;
	double dblYOnBL;
	double dblHalfHeight;
	double dblWidthX1 = 0;
	double dblWidthX2 = 0;
	//calculating height of the peak
	if ((m_dblPeakEndX - m_dblPeakStartX) != 0)
		dblBLSLope = (m_dblPeakEndY - m_dblPeakStartY) / (m_dblPeakEndX - m_dblPeakStartX);
	//calculating y point on the baseline with respetive to the peakmax x value 
	dblYOnBL = dblBLSLope *(m_dblPeakMaxX - m_dblPeakStartX) + m_dblPeakStartY;

	dblTmpHeight = fabs(m_dblPeakMaxY - dblYOnBL);	

	stuPeakDetectPoint obj;

	//width at 5 percent height 
	{
		dblHalfHeight = dblTmpHeight / 20;

		for(int i = lngPeakMaxIndex; i>=lngPeakStartIndex; i--)
		{
			obj = m_arrPeakDetectPoint.GetAt(i);
			if((obj.Y - m_dblPeakStartY) <= dblHalfHeight)
			{
				dblWidthX1 = obj.X;
				break;
			}
		}

		for(int i = lngPeakMaxIndex; i<=lngPeakEndIndex; i++)
		{
			obj = m_arrPeakDetectPoint.GetAt(i);
			if((obj.Y - m_dblPeakEndY) <= dblHalfHeight)
			{

				dblWidthX2 = obj.X;
				break;
			}
		}

		double dblCenterX= m_dblPeakMaxX;

		double dblLeftWidth = dblCenterX - dblWidthX1;
		double dblRightWidth = dblWidthX2 - dblCenterX;



		double dblWidth =(dblWidthX2 - dblWidthX1);

		//modified by arun to replace the Width at different heights member variables when manual peak is selected and the existing peak is replaced with manual peak.
		//index===-1 means new peak is added. if normal peak then m_nManualPeakIndex is -1. if new manual peak then m_nManualIndex is 0.
		if (bAdjuestPeak == FALSE)
		{
			if (bInsertPeak==FALSE)
			{
				m_dblWidthAt5PercentHeight.Add(dblWidth);
				m_dblLeftWidthAt5PercentHeight.Add(dblLeftWidth);
				m_dblRightWidthAt5PercentHeight.Add(dblRightWidth);
			}
			else
			{
				m_dblWidthAt5PercentHeight.InsertAt(m_nManualPeakindex,dblWidth);
				m_dblLeftWidthAt5PercentHeight.InsertAt(m_nManualPeakindex,dblLeftWidth);
				m_dblRightWidthAt5PercentHeight.InsertAt(m_nManualPeakindex,dblRightWidth);
			}
		}		
		else
		{
			m_dblWidthAt5PercentHeight.SetAt(m_nManualPeakindex,dblWidth);
			m_dblLeftWidthAt5PercentHeight.SetAt(m_nManualPeakindex,dblLeftWidth);
			m_dblRightWidthAt5PercentHeight.SetAt(m_nManualPeakindex,dblRightWidth);
		}

		CString s;
		s.Format(_T("width=%d LW=%d RW=%d"),m_dblWidthAt5PercentHeight.GetSize(),m_dblLeftWidthAt5PercentHeight.GetSize(),m_dblRightWidthAt5PercentHeight.GetSize());
		//AfxMessageBox(s);
	}

	//Width at 10 percent height 
	{
		dblWidthX1 = 0;
		dblWidthX2 = 0;
		dblHalfHeight=0;
		dblHalfHeight = dblTmpHeight / 10;

		for(int i = lngPeakMaxIndex; i>=lngPeakStartIndex; i--)
		{
			obj = m_arrPeakDetectPoint.GetAt(i);
			if((obj.Y - m_dblPeakStartY) <= dblHalfHeight)
			{
				dblWidthX1 = obj.X;
				break;
			}
		}

		for(int i = lngPeakMaxIndex; i<=lngPeakEndIndex; i++)
		{
			obj = m_arrPeakDetectPoint.GetAt(i);
			if((obj.Y - m_dblPeakEndY) <= dblHalfHeight)
			{
				dblWidthX2 = obj.X;
				break;
			}
		}

		double dblCenterX= m_dblPeakMaxX;

		double dblLeftWidth = dblCenterX - dblWidthX1;
		double dblRightWidth = dblWidthX2 - dblCenterX;

		double dblWidth =(dblWidthX2 - dblWidthX1);

		if (bAdjuestPeak==FALSE)
		{
			if (bInsertPeak==FALSE)
			{			
				m_dblWidthAt10PercentHeight.Add(dblWidth);
				m_dblLeftWidthAt10PercentHeight.Add(dblLeftWidth);
				m_dblRightWidthAt10PercentHeight.Add(dblRightWidth);
			}
			else
			{
				m_dblWidthAt10PercentHeight.InsertAt(m_nManualPeakindex,dblWidth);
				m_dblLeftWidthAt10PercentHeight.InsertAt(m_nManualPeakindex,dblLeftWidth);
				m_dblRightWidthAt10PercentHeight.InsertAt(m_nManualPeakindex,dblRightWidth);
			}

		}
		else
		{
			m_dblWidthAt10PercentHeight.SetAt(m_nManualPeakindex,dblWidth);
			m_dblLeftWidthAt10PercentHeight.SetAt(m_nManualPeakindex,dblLeftWidth);
			m_dblRightWidthAt10PercentHeight.SetAt(m_nManualPeakindex,dblRightWidth);
		}
	}
	//width at half height
	{
		dblWidthX1 = 0;
		dblWidthX2 = 0;
		dblHalfHeight=0;

		dblHalfHeight = dblTmpHeight / 2;

		for(int i = lngPeakMaxIndex; i>=lngPeakStartIndex; i--)
		{
			obj = m_arrPeakDetectPoint.GetAt(i);
			if((obj.Y - m_dblPeakStartY) <= dblHalfHeight)
			{
				dblWidthX1 = obj.X;
				break;
			}
		}

		for(int i =lngPeakMaxIndex; i<=lngPeakEndIndex; i++)
		{
			obj = m_arrPeakDetectPoint.GetAt(i);
			if((obj.Y - m_dblPeakEndY) <= dblHalfHeight)
			{
				dblWidthX2 = obj.X;
				break;
			}
		}

		double dblCenterX= m_dblPeakMaxX;

		double dblLeftWidth = dblCenterX - dblWidthX1;
		double dblRightWidth = dblWidthX2 - dblCenterX;

		double dblWidth =(dblWidthX2 - dblWidthX1);

		if (bAdjuestPeak==FALSE)
		{
			if (bInsertPeak == FALSE)
			{
				m_dblWidthAtHalfHeight.Add(dblWidth);
				m_dblLeftWidthAtHalfHeight.Add(dblLeftWidth);
				m_dblRightWidthAtHalfHeight.Add(dblRightWidth);
			}
			else
			{
				m_dblWidthAtHalfHeight.InsertAt(m_nManualPeakindex,dblWidth);
				m_dblLeftWidthAtHalfHeight.InsertAt(m_nManualPeakindex,dblLeftWidth);
				m_dblRightWidthAtHalfHeight.InsertAt(m_nManualPeakindex,dblRightWidth);
			}

		}
		else
		{			
			m_dblWidthAtHalfHeight.SetAt(m_nManualPeakindex,dblWidth);
			m_dblLeftWidthAtHalfHeight.SetAt(m_nManualPeakindex,dblLeftWidth);
			m_dblRightWidthAtHalfHeight.SetAt(m_nManualPeakindex,dblRightWidth);
		}
	}
}
DOUBLE CEsdAdvancedGraphCtrl::GetPeakMinTreshold()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here


	return m_dblMinPeakThreshold;
}

void CEsdAdvancedGraphCtrl::SetPeakMinTreshold(DOUBLE newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here


	m_dblMinPeakThreshold=newVal;


	SetModifiedFlag();
}

void CEsdAdvancedGraphCtrl::MarkStartnEndpts(LONG lngGraphIdx)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	LPDISPATCH pDisp =	m_chart.Series(lngGraphIdx);
	ISeriesPtr pSeries	=	pDisp;	// Smart pointer for 'Series' interface of the Specified Graph ID
	pDisp->Release();

	//Validating the Index recieved.{
	if(lngGraphIdx<0 ||lngGraphIdx>=m_chart.get_SeriesCount())
	{
		MessageBox(_T("Graph with this ID doesn't exist"));
		pSeries	=	NULL;
		return;
	}

	_bstr_t bstrGraphName=pSeries->GetName().copy();
	long lIdx=GetLtblIdxFromName(bstrGraphName);
	if(lIdx<0) // IF the specified Graph ID is not the valid ID
	{
		MessageBox(_T("Graph with this ID doesn't exist"));
		//	SysFreeString(bstrGraphName);
		pSeries	=	NULL;
		return;
	}
	//Validating the Index received.}

	m_bMarkStartnEndPoints = TRUE;

	stuPeakInfo *pPeakInfo=NULL; 

	if(m_GraphPeaks.GetSize() == 0)
	{

		return;
	}
	pPeakInfo = m_GraphPeaks.GetAt(lngGraphIdx);
	long size	=(long)pPeakInfo->dblArea.GetSize();

	//LPDISPATCH pDisp	=	m_chart.Series(lngGraphIdx);
	//ISeriesPtr pSeries	=	pDisp;
	//pDisp->Release();
	pDisp	=	m_chart.get_Canvas();
	ICanvasPtr pCanvas  =	pDisp;
	pDisp->Release();
	(pCanvas->Font)->Color = m_clrStartnEndMarking;
	//(pCanvas->Brush)->Color = m_clrStartnEndMarking;


	long lngX,lngY;
	long lngS,lngE;
	for(int i=0;i<size;i++)
	{
		lngS	=	pPeakInfo->intPeakStartIndex.GetAt(i);
		lngE	=	pPeakInfo->intPeakEndIndex.GetAt(i);

		lngX	=	pSeries->CalcXPos(lngS);
		lngY	=	pSeries->CalcYPos(lngS);

		//pCanvas->Line(lngX,lngY,lngX,lngY+10);
		pCanvas->TcTextOut(lngX,lngY,_T("|"));

		lngX	=	pSeries->CalcXPos(lngE);
		lngY	=	pSeries->CalcYPos(lngE);

		//pCanvas->Line(lngX,lngY,lngX,lngY-12);
		pCanvas->TcTextOut(lngX,lngY,_T("|"));

	}

	pSeries	=	NULL;
	pCanvas	=	NULL;

	m_chart.Repaint();



	pSeries = NULL;
}

void CEsdAdvancedGraphCtrl::SetStartnEndptMarkingColor(OLE_COLOR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	OleTranslateColor(newVal,NULL,&m_clrStartnEndMarking);

	SetModifiedFlag(TRUE);

	// TODO: Add your dispatch handler code here
}

OLE_COLOR CEsdAdvancedGraphCtrl::GetStartnEndptMarkingColor(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	return m_clrStartnEndMarking;
}

// Check for the Graph with the given Id
unsigned int CEsdAdvancedGraphCtrl::IsGraphExisting(long lngGraphId)
{
	if(m_chart.Series(lngGraphId)==NULL)
		return 0;
	else
		return 1;
}


// Get the underlying Teechart Interface
LPDISPATCH CEsdAdvancedGraphCtrl::GetTeeChart(void)
{
	return m_chart.GetIDispatch(TRUE);

}

// To interpolate the Data 
double CEsdAdvancedGraphCtrl::InterPolateData(long lngGraphId, double dblXvalue)
{
	if(lngGraphId<0 || lngGraphId >=m_chart.get_SeriesCount())  // Make sure that data point which is to be added to the Graph specified 
	{                                         // GraphID exists or not.
		MessageBox(_T("Graph with specified ID doesn't exists"),NULL,0);
		return 0 ;//Error(_T("Graph with specified ID doesn't exists"));
	} 		
	else
	{		
		LPDISPATCH pDisp	=	NULL;
		pDisp	=	m_chart.Series(lngGraphId);
		//ICurveFittingFunctionPtr	pcurve	=	pDisp;
		ISeriesPtr	pcurve	=	pDisp;
		pDisp->Release();

		_bstr_t bstrGraphName=pSeries->GetName().copy();
		long LTblIdx=GetLtblIdxFromName(bstrGraphName);
		if(LTblIdx<0)
		{
			MessageBox(_T("Graph with this index doesn't exist")); 
			return 0;
		}  
		pcurve->FunctionType->asSmoothing->Interpolate=1;
		//pcurve->put_TypeFitting(cfPolynomial);
		//double y=pcurve->GetCurveYValue(dblXvalue);		
		return 0;
	}	
}

void CEsdAdvancedGraphCtrl::FindArea(LONG lngGraphID, DOUBLE dblStartPointXVal,DOUBLE dblStartPointYVal, DOUBLE dblEndPointXVal,DOUBLE dblEndPointYVal,LONG nStartIndex,LONG nEndIndex,DOUBLE* dblArea)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	LPDISPATCH pDisp;
	pDisp	=	m_chart.Series(lngGraphID);
	ISeriesPtr pSeries	=	pDisp;	// Smart pointer for 'Series' interface of the Specified Graph ID
	pDisp	=	NULL;


	if((lngGraphID < 0) || (lngGraphID >= m_chart.get_SeriesCount()))
	{
		MessageBox(_T("Graph with this ID doesn't exist"));
		return;
	}
	else
	{
		double dblArea;
		//stuPeakDetectPoint obj1;
		//stuPeakDetectPoint obj2;

		//obj1 = m_arrPeakDetectPoint.GetAt(m_intPeakStartIndex);
		//obj2 = m_arrPeakDetectPoint.GetAt(m_intPeakEndIndex);
		//obj1.X = dblStartPointXVal;
		//obj1.Y = dblStartPointYVal;
		//obj2.X = dblEndPointXVal;
		//obj2.Y = dblEndPointYVal;

		double dblBaseLineArea =  0.5 * (dblStartPointYVal + dblEndPointYVal) * (dblEndPointXVal - dblStartPointXVal);

		double dblY0 = dblStartPointYVal;
		double dblYn = dblEndPointYVal;
		double dblY = 0;
		double dblInterval = 0;

		if(nEndIndex > nStartIndex)
		{
			//obj2 = m_arrPeakDetectPoint.GetAt(m_intPeakStartIndex+1);
			
			//dblInterval = fabs(obj2.X - obj1.X);
			dblInterval = fabs(pSeries->GetXValues()->GetValue(nStartIndex+1) - dblStartPointXVal);
		}

		for(int i = nStartIndex+1; i <= nEndIndex-1; i++)
		{
			//obj1 = m_arrPeakDetectPoint.GetAt(i);
			
			//dblY += obj1.Y;
			dblY += pSeries->GetYValues()->GetValue(i);
		}

		dblArea = dblInterval /2 * (dblY0 + dblYn + (2 * dblY));

		dblArea = fabs(dblArea - dblBaseLineArea);
	}	
}
void CEsdAdvancedGraphCtrl::GetArea(LONG lngGraphID, DOUBLE dblStartPointXVal, DOUBLE dblStartPointYVal, DOUBLE dblEndPointXVal, DOUBLE dblEndPointYVal, LONG lngStartPointIndex, LONG lngEndPointIndex, DOUBLE* ptrdblArea)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	LPDISPATCH pDisp;
	pDisp	=	m_chart.Series(lngGraphID);
	ISeriesPtr pSeries	=	pDisp;	// Smart pointer for 'Series' interface of the Specified Graph ID
	pDisp	=	NULL;


	if((lngGraphID < 0) || (lngGraphID >= m_chart.get_SeriesCount()))
	{
		MessageBox(_T("Graph with this ID doesn't exist"));
		return;
	}
	else
	{
		double dblArea;
		//stuPeakDetectPoint obj1;
		//stuPeakDetectPoint obj2;

		//obj1 = m_arrPeakDetectPoint.GetAt(m_intPeakStartIndex);
		//obj2 = m_arrPeakDetectPoint.GetAt(m_intPeakEndIndex);
		//obj1.X = dblStartPointXVal;
		//obj1.Y = dblStartPointYVal;
		//obj2.X = dblEndPointXVal;
		//obj2.Y = dblEndPointYVal;

		double dblBaseLineArea =  0.5 * (dblStartPointYVal + dblEndPointYVal) * (dblEndPointXVal - dblStartPointXVal);

		double dblY0 = dblStartPointYVal;
		double dblYn = dblEndPointYVal;
		double dblY = 0;
		double dblInterval = 0;

		if(lngEndPointIndex > lngStartPointIndex)
		{
			//obj2 = m_arrPeakDetectPoint.GetAt(m_intPeakStartIndex+1);
			
			//dblInterval = fabs(obj2.X - obj1.X);
			dblInterval = fabs(pSeries->GetXValues()->GetValue(lngStartPointIndex+1) - dblStartPointXVal);
		}

		for(int i = lngStartPointIndex+1; i <= lngEndPointIndex-1; i++)
		{
			//obj1 = m_arrPeakDetectPoint.GetAt(i);
			
			//dblY += obj1.Y;
			dblY += pSeries->GetYValues()->GetValue(i);
		}

		dblArea = dblInterval /2 * (dblY0 + dblYn + (2 * dblY));

		dblArea = fabs(dblArea - dblBaseLineArea);
		*ptrdblArea = dblArea;
	}
}
