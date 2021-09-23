#pragma once

// AxWrapper1Ctrl.h : Declaration of the CEsdAdvancedGraphCtrl ActiveX Control class.

#include "tchart.h"
#include"AxWrapper1idl.h"



// CEsdAdvancedGraphCtrl : See AxWrapper1Ctrl.cpp for implementation.


// Various States that a curve will be in
const int FLAT		= 1;
const int NEGUPCRV	= 2;
const int UPCRV		= 3;
const int NEGUP		= 4;
const int UP		= 5;
const int NEGDOWN	= 6;
const int NEGBCKDN	= 7;
const int DOWN		= 8;
const int BCKDN		= 9;
const int PKEND		= 10;
const int INTEG		= 11;
const int INHIBITINTEG = 12;
//Minimum Criterion for Peak Determination
const int NUP = 3;
const int NPE = 3;
const int NDO = 3;
const int STEPLIMIT = 2;

const double PACURVE = 0.001;
const double BLLIMIT = 0.2;
const double MAXAVLENGTH = 3000;
const double LARGELONG = 2147483647;
const double LARGEFLOAT = 1E+100;

const double MINENDPROZ = 0.02;
const double PAPEfak = 10;

const double MINPESLOPE = 0.00035963;
const double MAXPESLOPE = 0.0035963;
const double MINPECURVE = 2.157782528E-07;
const double MAXPECURVE = 0.02157782528;
const double PESLOPEproz = 0.1;
const double PECURVEproz = 0.1;

typedef struct 
{
	double X;
	double Y;
}stuPeakDetectPoint;


typedef enum {
	TYPE_BASE = 0,
	TYPE_VALLEY = 1,
	TYPE_PENETRATION = 2,
	TYPE_HORZ_BASE = 3,
	TYPE_FRWSKIMMING = 4,
	TYPE_BKWSKIMMING =5,
	TYPE_SkMVALLEY =6
}ePointType;


typedef struct 
{
	CArray<double, double> dblPeakStartX;//stores the peak's start X value
	CArray<double, double> dblPeakStartY;//stores the peak's start Y value

	CArray<double, double> dblPeakMaxX;//stores the peak's Max X value
	CArray<double, double> dblPeakMaxY;//stores the peak's Max Y value

	CArray<double, double> dblPeakEndX;//stores the peak's End X value
	CArray<double, double> dblPeakEndY;//stores the peak's end Y value

	CArray<int, int> intPeakStartIndex;//stores the index of the peak's start point
	CArray<int, int> intPeakMaxIndex;//stores the index of the peak's Max point
	CArray<int, int> intPeakEndIndex;//stores the index of the peak's End  point

	CArray<int,int> arrStartPointType;//type of the peak start means BasePoint,PenetrationPoint,Valley point or HorizontalBasePoint
	CArray<int,int> arrEndPointType;

	CArray<double, double> dblArea;
	CArray<double, double> dblHeight;
	CArray<double, double> dblWidth;
	_bstr_t strGraphName; // Silpa.S To store the name of the graph for which these peak parameters are to be stored
	// this will be useful at the time of retrieving peak parameter values

}stuPeakInfo;
///////////////////////////////////////////////////////////////////////////////////

// on 05/09
typedef struct
{
	long lngAddGraphIdx;
}stuGraphdata;

// on 05/09
typedef struct 
{
	BSTR bstrGraphName;
	BSTR bstrBaseLinename;
	BSTR bstrFillName;
	BSTR bsrLinearfitName;
	BSTR bstrQuadraticFitName;
	BSTR bstrLogFit;
	BSTR bstrPowerFit;
	BSTR bstrExpFit;
	BSTR bstrCustomTrendLineName;
	BOOL bShowPeaks;
	int intPeakLevel;
}stuRemovableGraphData;

// Structure which holds the Custom text information which got to be displayed at particular data point in the
// region where plotting will be performed.
struct EsdPLOTAREATEXT_STRUCT
{
	BSTR				bstrGraphName;      //Graph name 
	CArray<CString,CString>		strPlotAreaText;	//	Holds the Plot Area Custom text.
	COLORREF					clrTextColor;		//	Holds the Custom text color.
	//	int			intToolIdx;		    //	To Store the index of TeeChart tool Added
	//double		dblXval;			//	X coord of data point.
	//double		dblYval;			//	Y coord of data point.
	CArray<double,double>		dblXVal;			// X Coord	of data point		
	CArray<double ,double>		dblYVal; 			// Y coord of Data point
};
//Added by Silpa on 04/10/07
// When Manual Cursor is added to a graph this info is stored in this structure
// it will be used to remove these added cursors when the graph deleted.
struct EsdDATUMLINEINFO_STRUCT
{
	_bstr_t bstrGraphName;				//Name of the Graph for which Datum line is Drawing
	_bstr_t	bstrFixedDatumLineName[2];		// Name of the Fixed Datum line drawn(Reference cursor)
	long	lngDatumLineToolType;		// Type of the TeeChart Tool used to draw movable datum line(Used While Removing)
	long	lngTextDisplayToolType;		// Type of the TeeChart Tool used to display text .
	double	dblXVal;					//	X Coord value where to Start Datum line
	double	dblYVal;					//	Y coord	  "		"	"	"		"	"
	COLORREF clrDatumLineColor;			//  Color of the Datum Line
};

// Structure which holds the Custom text information.This text  can be displayed at where on the total chart area.
struct EsdCUSTOMTEXT_STRUCT
{
	_bstr_t strCustomText;		//	Holds the Custom text.
	COLORREF clrTextColor;		//	Holds the Custom text color.
	long     lngXmargin;			//	X location where text to be displayed.
	long     lngYmargin;			//	Y location where text to be displayed.
};


// Structure which holds the 
struct EsdPeakInfoDisplay_Struct
{
	long lngGraphIdx;
	CArray<long,long>lngvalueIdx;
	CArray<_bstr_t,_bstr_t> strPeakInfo;
};
////////////////////////////////////
class CEsdAdvancedGraphCtrl : public COleControl
{
	DECLARE_DYNCREATE(CEsdAdvancedGraphCtrl)

	// Constructor
public:
	CEsdAdvancedGraphCtrl();

	// Overrides
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual DWORD GetControlFlags();

	// Implementation
protected:
	~CEsdAdvancedGraphCtrl();

	DECLARE_OLECREATE_EX(CEsdAdvancedGraphCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CEsdAdvancedGraphCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CEsdAdvancedGraphCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CEsdAdvancedGraphCtrl)		// Type name and misc status

	// Message maps
	DECLARE_MESSAGE_MAP()

	// Dispatch maps
	DECLARE_DISPATCH_MAP()

	// Event maps
	DECLARE_EVENT_MAP()

	// Dispatch and event IDs
public:
	enum {
		dispidGetArea = 151L,
		eventidOnPeakDetected = 30L,
		//dispidGetThresholdSlope = 137L,
		//dispidSetThresholdSlope = 136L,
		dispidFindArea = 136L,
		dispidGetStartnEndptMarkingColor = 135L,
		dispidSetStartnEndptMarkingColor = 134L,
		dispidMarkStartnEndpts = 133L,
		dispidPeakMinTreshold = 132,
		dispidDoGraphReprocess = 131L,
		dispidCustomAxisTitleAngle = 130L,
		dispidCustomAxisGrids = 129L,
		dispidCustomAxisMinimum = 128L,
		dispidCustomAxisMaximum = 127L,
		dispidCustomAxisTitle = 126L,
		dispidAddCustomAxis = 125L,
		dispidRemoveAllCustomAxes = 124L,
		dispidRemoveCustomAxis = 123L,
		dispidAssignAxesForGraph = 122L,
		dispidChangeAxisEndPosition = 121L,
		dispidChangeAxisStartPosition = 120L,
		dispidMoveAxisFromBasePosition = 119L,
		//dispidAddCustomAxis = 118L,
		dispidWidthAtHalfHeight = 117L,
		dispidWidthAt10PercentHeight = 116L,
		dispidWidthAt5PercentHeight = 115L,
		dispidPeakWidthCalculationType = 114,
		dispidClearCustomText = 113L,
		dispidDisplayText = 112L,
		dispidSetAxesTitlesFont = 111L,
		dispidSetHeaderFont = 110L,
		dispidZoomOut = 109L,
		dispidZoomIn = 108L,
		dispidYGrids = 107,
		dispidXGrids = 106,
		dispidSetCustomTextFont = 105L,
		dispidSetXYMarkingFont = 104L,
		dispidSetLegendFont = 103L,
		dispidShowYTitle = 102,
		dispidShowXTitle = 101,
		dispidShowConcAtPeaks = 100,
		dispidPerConc = 99,
		dispidAutoRange = 98,
		dispidSort = 97,
		dispidCrossWireDataPointIndex = 96,
		dispidSetCustomCrosswireText = 95L,
		dispidDisplayCrossWireAt = 94L,
		dispidMoveCrossWireToPrev = 93L,
		dispidMoveCrossWireToNext = 92L,
		dispidMoveCrossWireToLast = 91L,
		dispidMoveCrossWireToFirst = 90L,
		dispidCrossWire = 89,
		dispidShowDataAtPeak = 88,
		dispidHidePeaks = 87L,
		dispidShowPeaks = 86L,
		dispidAxisGridStyle = 85,
		dispidAxisGridColor = 84,
		dispidAxisMinimum = 83,
		dispidAxesTitlesColor = 82,
		dispidAxisMaximum = 81,
		dispidEntireGraph = 80L,
		dispidAxestitle = 78,
		dispidAxesMarkingPrecision = 77,
		dispidAxesPresition = 76,
		dispidHeader = 73,
		dispidShowHeader = 72,
		dispidFindPeaks = 70L,
		dispidMouseButtonForScroll = 68,
		dispidScrollDirection = 67,
		dispidMinimumPixelsForZoom = 66,
		dispidMouseButtonForZoom = 65,
		dispidEnableZoom = 64,
		dispidZoomDirection = 63,
		eventidOnGetLegendRect = 29L,
		eventidOnPageChange = 28L,
		eventidOnGraphBeforeDrawValues = 27L,
		eventidOnGraphBeforeAdd = 26L,
		eventidOnGraphAfterDrawValues = 25L,
		eventidOnGraphAfterAdd = 24L,
		eventidOnUndoZoom = 23L,
		eventidOnZoom = 22L,
		eventidOnTimer = 21L,
		eventidOnScroll = 20L,
		eventidOnResize = 19L,
		eventidOnMouseLeaveGraph = 18L,
		eventidOnMouseEnterGraph = 17L,
		eventidOnMouseUp = 16L,
		eventidOnMouseMove = 15L,
		eventidOnMouseDown = 14L,
		eventidOnKeyUp = 13L,
		eventidOnKeyDown = 12L,
		eventidOnCursorToolChange = 11L,
		eventidOnEnter = 10L,
		eventidOnDblClick = 9L,
		eventidOnClickSeries = 8L,
		eventidOnClickLegend = 7L,
		eventidOnClickBackground = 6L,
		eventidOnClickAxis = 5L,
		eventidOnClick = 4L,
		eventidOnBeforeDrawAxes = 3L,
		eventidOnBeforeDrawSeries = 2L,
		eventidOnAfterDraw = 1L,
		dispidDrawDatumLine = 62L,
		dispidEnableVericalDatumLine = 61,
		dispidEnableHorzDatumLine = 60,
		dispidPrintPreview = 59L,
		dispidPrintGraph = 58L,
		dispidGetGraphPeaksCount = 57L,
		dispidAddPoints1 = 56L,
		dispidAddPoints = 55L,
		dispidBackImage = 54,
		dispidGetGraphMinMax = 53L,
		dispidGetGraphDataCont = 52L,
		dispidGetGraphDataAt = 51L,
		dispidGetGraphData = 50L,
		dispidShowLegend = 49,
		dispidAxesMarkingColor = 48,
		dispidAverageNoise = 47,
		dispidCustomTextBackColor = 46,
		dispidCustomTextColor = 45,
		dispidBackGroundColor = 44,
		dispidDisplayTextAt = 43L,
		dispidGetPeaksCount = 42L,
		dispidGraphColor = 42,
		dispidPeakMinWidth = 41,
		dispidPeakMinHeight = 40,
		dispidPeakMinArea = 39,
		dispidPeakFillColor = 38,
		dispidGetAllGraphIDs = 37L,
		dispidGetNumberOfGraphs = 36L,
		dispidBaseLineColor = 35,
		dispidBaseLineType = 34,
		dispidDrawBaseLine = 33L,
		dispidPeakFillArea = 32L,
		dispidGetPeakIndexes = 30L,
		dispidGetPeakInfo = 29L,
		dispidQuadraticFitX = 28L,
		dispidLinearFitX = 27L,
		dispidQuadraticCoefficients = 26L,
		dispidLinearCoefficients = 25L,
		dispidFindQuadraticCoefficients = 24L,
		dispidFindLinearCoefficients = 23L,
		dispidCalculateTrendLine = 22L,
		dispidExportGraphData = 21L,
		dispidCopyData = 20L,
		dispidCopyGraph = 19L,
		dispidGetControlUnknown = 18L,
		dispidStartAnimation = 17L,
		dispidStopOfflinePeakDetection = 16L,
		dispidStartOfflinePeakDetection = 15L,
		dispidStopOnlinePeakDetection = 14L,
		dispidStartOnlinePeakDetection = 13L,
		dispidModifyLegends = 12L,
		dispidSetGraphVisible = 11L,
		dispidSetGraphtype = 10L,
		dispidRemoveAllGraphs = 9L,
		dispidRemoveGraph = 8L,
		dispidRemoveDataPoint = 7L,
		dispidSetGraphPointColor = 6L,
		dispidDrawMultiColorGraph = 5L,
		dispidModifyDataPoint = 4L,
		dispidAddDataPoints = 3L,
		dispidAddDataPoint = 2L,
		dispidAddGraph = 1L,
		dispidInterPolateData=150L

	};
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);

public:
	CTChart m_chart;

	long m_lngNoOfDataPoints;//for storing the total data points in AddDataPoints()AND IsDownHill()
	ISeriesPtr	pSeries;

	/// Variables for All Peak related values

	double m_dblXmin;		// Holds the X - Axis minimum value.
	double m_dblXmax;		// Holds the X - Axis maximum value.
	double m_dblYmin;		// Holds the Y - Axis minimum value.
	double m_dblYmax;		// Holds the Y - Axis maximum value.
	double m_dblMinOfXmin;	// Keeps track of least X value of all the Graph(s).
	double m_dblMaxOfXmax;	// Keeps track of highest X value of all the Graph(s).
	double m_dblMinOfYmin;	// Keeps track of least Y value of all the Graph(s).
	double m_dblMaxOfYmax;	// Keeps track of highest Y value of all the Graph(s).

	double m_dblXCurPos;	// Used in exposing the X value when mouse pointer is moved on the Graph Control.
	double m_dblYCurPos;	// Used in exposing the Y value when mouse pointer is moved on the Graph Control.		//Commented on 23/11 by Silpa


	// As it is not possible to represent the decimal values on the screen,
	// double values are converted to long values.
	long m_lngXmin;			
	long m_lngXmax;
	long m_lngYmin;
	long m_lngYmax;


	/*// Holds the print area locations where Graph Control is to be rendered.
	long m_lngPrintAreaLeft;
	long m_lngPrintAreaTop;
	long m_lngPrintAreaRight;
	long m_lngPrintAreaBottom;*/	//Commented On 23/11/07 by Silpa


	int m_intGraphType;			// Holds the Graph Type value( 1 - Point  2 - Line).	
	int m_intXPrecision;		// Holds the X - Axis precision value.
	int m_intYPrecision;		// Holds the Y - Axis precision value.
	int m_intXNumOfGrids;		// Holds the number of Grids to be drawn along X - Axis.	
	int m_intYNumOfGrids;		// Holds the number of Grids to be drawn along Y - Axis.

	/*	int m_intGridStyle;			// Holds the Grid Style value(i.e. Pen Style).	// Commented on 23/11/07 by Silpa			
	int m_intZeroAxesStyle;		// Holds the Zero Axes Pen Style value.
	int m_intBackgroundStyle;	// Holds the Background style value(0 - TRANSPARENT 1 - OPAQUE) for entire Graph control.
	int m_intPlotAreaStyle;		// Holds the Background style value(0 - TRANSPARENT 1 - OPAQUE) for entire plot area only.
	int m_intBorderStyle;		// Holds the pen style value for Graph control border.
	int m_intPlotAreaBorderStyle;	// Holds the pen style value for plot area border.
	int m_intDefaultPointStyle;		// If pen style is not set for any Graph then this default pen style will be used. 
	CString m_strHeader;		// Hold the Graph Header.
	*/	//Commented on 23/11/07 by Silpa

	CString m_strXAxisTitle;	// Holds the X - Axis Title.	
	CString m_strYAxisTitle;	// Holds the Y - Axis Title.


	int m_intCounterForGraphsPeaks;	// Used to avoid unnecessary invoking prcDisplayPeaks method in OnAfterDraw even though there are no Peaks to display.
	int	m_intCrossWireGraphID;		// It contains the ID of the Graph for which the Cross wire is existed currently

	COLORREF m_clrBackColor;	//	Holds the Graph Control Background color value.
	COLORREF m_clrCustomTextBackColor;//	Holds the Plot Area Background color value. 
	COLORREF m_clrZeroAxesColor;//	Holds the Zero Axes color value.
	COLORREF m_clrGridColor;	//	Holds the Grids color value.
	COLORREF m_clrCustomTextColor;// Holds the Custom Text color value.
	COLORREF m_clrTitlesColor;	//	Holds the Titles color value.
	COLORREF m_clrMarkingColor;	//	Holds the X-Y Axes color value.
	COLORREF m_clrBaseLineColor; // Holds the Color for a baseline.	
	COLORREF m_clrPeakFillColor; // Holds the color for the Peak Area Filling
	COLORREF m_clrStartnEndMarking; // Holds the color for the marking of start and End points of a peak.

	BOOL m_bShowLegends;		// Decides whether Legends to be displayed or not.
	BOOL m_bSortPoints;			// Decides whether Graph(s) to be displayed by sorting the data points or not.
	BOOL m_bFirstXYvalue;		// Used in storing least and highest X & Y values of all the Graph(s).
	/*	BOOL m_bZoomRestore;		// Used in updating the ptArrayLeft and ptArrayRight variables zeroth location whenever there is a change in min. & max. values.
	BOOL m_bIsZoomable;			// Zooming is done when Mouse LButton is clicked within the Plot Area only.
	BOOL m_bLockZoom;			// Used in Locking / Unlocking the Zoom.
	BOOL m_bShowZeroAxes;		// Whether or not to display the Zero Axes.
	BOOL m_bTrackingZoomArea;	// Used in displaying the rubber band while performing the zooming.
	BOOL m_bShowHeader;			// Whether or not to display the Header.
	BOOL m_bShowMarking;		// Whether or not to display the XY - Marking.	
	BOOL m_bIsPrinting;			// Enabled when Graph control is to be printed.
	BOOL m_bCopyGraph;			// Enabled when Graph control is to be copied onto Clipboard.
	BOOL m_bHasMoreThanTwoPoints;// Used along with the AutoRange Property. 
	//	It will indicate that Graph Control has aquired more than two points and can turn on the Auto Range.	
	BOOL m_bSaveLockZoomStateForAutoRange; // Zooming is locked when Auto range is enabled
	//	and this will be used to store the Lock Zoom status.
	BOOL m_bCanRemoveLastZoomState;
	BOOL m_bIsMousePtInGraph;	
	BOOL m_bIsPaning;
	BOOL m_bLButtonPressed;*/	// Commented on 23/11/07 by Silpa

	BOOL m_bAutoRangeEnable;	// Used to enable the AutoRange Property.
	BOOL m_bShowXTitle;			// Whether or not to display the X - Axis Title.	
	BOOL m_bShowYTitle;			// Whether or not to display the Y - Axis Title.
	BOOL m_bFirstTimeCrossWire;
	BOOL m_bClickEvent;         //Used to handle Mouse Clicks for TimedEvents
	BOOL m_bShowDataAtPeak;
	BOOL m_bCanUpdateMinMax;
	BOOL m_bShowCrossWire;
	BOOL m_blnLockBaseLine;
	BOOL bForcedpeak;

	BOOL blnManualPeak;

	CString m_strBackImage;		//holds the image set to the background. //ss 12/09/07
	BOOL m_blnLinearFit;		//ss 12/09/07
	BOOL m_blnQuadraticFit;		//ss 12/09/07
	BOOL m_blnLogFit,m_blnExpFit,m_blnPowerFit;

	//	BOOL m_bPrintMode;	//23/11

	long m_lngCrossWireDataPointIndex;	// Stores the Index of the Point where the Cross wire is existed currently
    long m_lngManualBaselineStartPointIndex;
	long m_lngManualBaselineEndPointIndex;

	POINT m_ptCrossWirePos;		// Stores the X,Y values for the Cross Wire
	POINT m_ptStartEndPos;
	CString	m_strCrosswireText; // to store the Custom text of the Cross wire
	BOOL m_blnHideXYValues;		// To Hide the (X,Y) on peaks when 'ShowPeaks' enabled and to display custom text in that place
	double m_dblconcentration;	// Concentration value to be displayed (SpectraTreatz purpose)


	// Peak Detection Variables 
	double m_dblCurrentX;
	double m_dblCurrentY;

	double m_dblOldX;
	double m_dblOldY;

	double m_dblPeakStartX;
	double m_dblPeakStartY;

	double m_dblPeakMaxX;
	double m_dblPeakMaxY;

	double m_dblPeakEndX;
	double m_dblPeakEndY;

	double m_dblPeakLeftWidth;
	double m_dblPeakLeftHeight;

	double m_dblSlope;
	double m_dblOldSlope;
	double m_dblThresholdSlope;
	double m_dblSavedSlopeForDownHill;

	double m_dblCurve;
	double m_dblOldCurve;	

	double m_dblPeakMaximumSlope;
	double m_dblPeakMaximumCurve;

	double m_dblPeakMaxSlopeX;
	double m_dblPeakMaxSlopeY;

	double m_dblPeakMaxCurveX;
	double m_dblPeakMaxCurveY;	

	double m_dblUpCurveLimit;
	double m_dblDownCurveLimit;

	double m_dblPreviousDerivativeX;
	double m_dblPreviousDerivativeY;
	double m_dblPreviousDerivativeXDiffValue;

	double m_dblLastPeakEndX;
	double m_dblAverageNoise;
	double m_dblAverageLength;
	double m_dblMinArea;
	double m_dblMinHeight;
	double m_dblMinWidth;
	double m_dblMinPeakThreshold;
	double m_dblAvCurve;

	int m_intPeakStartIndex;
	int m_intPeakMaxIndex;
	int m_intPeakEndIndex;
	int m_intDownCount;
	int m_intDerivativeRetValue;
	int m_intPeakStatus;
	int m_intPeakUpCount;
	int m_intPeakDownCount;
	int m_intMaxCurveIndex;
	int m_intBaseLineType;
	int m_intCurrentDataPointIndex;

	int m_nManualPeakindex;

	BOOL m_bPerConc;	// For SpectraTreatz Requirement(To show the % Conc value at peaks)
	BOOL m_bShowConcAtPeak; // "

	BOOL m_bMarkStartnEndPoints;

	BOOL m_blnDetectNegativePeaksAlso;

	BOOL m_blnOnlinePeakDetection;
	BOOL m_blnOfflinePeakDetection;


	/*int m_intPeakFillStyle;	//Commented on 23/11 by Silpa
	BOOL m_blnDrawingBaseLine;
	double m_dblBaseLineStartX;
	double m_dblBaseLineStartY;
	double m_dblBaseLineEndX;
	double m_dblBaseLineEndY; 
	BOOL m_blnCustomBaseLineDrawn;	
	BOOL m_blnShowPeakData;	
	BOOL m_blnPeakWindowDisplayed;	*/	//Commented on 23/11 by Silpa

	double m_dblBaseLineLevel;  //fn 4 this	

	stuPeakInfo *m_objPeakInfo;
	stuPeakInfo *m_objTempPeakInfo;
	stuPeakInfo *m_objTangentPeakInfo;
	stuPeakInfo *m_objManualTempPeakInfo;


	int m_intPeakWidthCalType;
	CArray <double,double> m_dblTangentStartPoint;
	CArray <double,double> m_dblTangentEndPoint;

	CArray <double,double> m_dblWidthAtHalfHeight;
	CArray <double,double> m_dblLeftWidthAtHalfHeight;
	CArray <double,double> m_dblRightWidthAtHalfHeight;
	CArray <double,double> m_dblWidthAt5PercentHeight;
	CArray <double,double> m_dblLeftWidthAt5PercentHeight;
	CArray <double,double> m_dblRightWidthAt5PercentHeight;
	CArray <double,double> m_dblWidthAt10PercentHeight;
	CArray <double,double> m_dblLeftWidthAt10PercentHeight;
	CArray <double,double> m_dblRightWidthAt10PercentHeight;

	CArray<stuPeakDetectPoint, stuPeakDetectPoint&> m_arrPeakDetectPoint;
	CArray<stuPeakInfo*, stuPeakInfo*> m_GraphPeaks;
	CArray<stuGraphdata,stuGraphdata&> m_arrGraphData;  //05/09/07
	CArray<stuRemovableGraphData,stuRemovableGraphData&> m_arrGraphRelatedSerieses;
	CArray<struct EsdPLOTAREATEXT_STRUCT*,struct EsdPLOTAREATEXT_STRUCT*> m_objPlotAreaText;// This holds the address of Plot Area Text Objects.
	CArray<struct EsdDATUMLINEINFO_STRUCT,struct EsdDATUMLINEINFO_STRUCT> m_objDatumLineInfo; //Silpa on 04/10/07
	CArray<struct EsdCUSTOMTEXT_STRUCT*, struct EsdCUSTOMTEXT_STRUCT*> m_objCustomText;	// This holds the addresses of Custom Text Objects.

	CArray<EsdPeakInfoDisplay_Struct*,EsdPeakInfoDisplay_Struct*>m_arrPeakInfoIndexes; //Stores the indexes where the peak info will display // Remove it

	//int nCustomTextIdx;   //10/09/07 To store the index of the tool used to display the Text
	BOOL blnCustomText;     // To know weather the Custom Text display is Activated or not
	BOOL blnHorzDatumLine;	// To enable the Horizontal Datum line Drawing //added by Silpa on 04/10/07
	BOOL blnVertDatumLine;	// To enable the Vertical Datum line Drawing   // Added by Silpa on 04/10/07

protected:
	LONG AddGraph(LPCTSTR strName, LONG lngColor);
	void AddDataPoint(LONG lngGraphIdx, DOUBLE dblXVal, DOUBLE dblYVal);
	void AddDataPoints(LONG lngGraphIDx, LONG lngNoOfPoints, VARIANT &varXVals, VARIANT &varYVals);
	void ModifyDataPoint(LONG lngGraphIdx, LONG lngPtIdx, DOUBLE dblXVal, DOUBLE dblYVal);
	void DrawMultiColorGraph(LONG lngGraphIdx, LONG lngNoOfPoints,VARIANT &varLngColors, VARIANT &varDblXVals, VARIANT &varDblYValues, LONG lngPenWdth=3);
	void SetGraphPointColor(LONG lngGraphIdx, LONG lngPtIdx, OLE_COLOR clrColor);
	VARIANT_BOOL RemoveDataPoint(LONG lngGraphIdx, LONG lngPtIdx);
	void RemoveGraph(LONG lngGraphIdx);
	void RemoveAllGraphs(void);
	void SetGraphtype(LONG lngGraphIdx, USHORT unGraphType);
	void SetGraphVisible(LONG lngGraphIdx, VARIANT_BOOL bShowRHide);
	VARIANT_BOOL ModifyLegends(LONG lngGraphIdx, LPCTSTR strGraphName, OLE_COLOR clrGraphColor);
	//	void CalculateTrendLine(LONG lngGraphIdx, LONG lngTendLineType, VARIANT_BOOL bShowTrendline,LONG lngTrendLineColor, VARIANT_BOOL* pVal);
public:
	void InitializePeakDetectionVariables(void);
public:
	void ProcessPtForPeakDetection(double dblXVal, double dblYVal);
public:
	int Derivative(void);
public:
	bool isFlat(void);
public:
	bool isFlankNotYetAccepted(bool  blnNegative);
public:
	bool isUpHill(bool blnNegative);
public:
	bool isDownHill(bool blnNegative);
public:
	bool SearchForPeakStart(bool blnNegative);
public:
	bool StorePeak(void);
public:
	void InitializationsForNextPeak(void);
protected:
	VARIANT_BOOL StartOnlinePeakDetection(void);
	VARIANT_BOOL StopOnlinePeakDetection(void);
	void StartOfflinePeakDetection(void);
	void StopOfflinePeakDetection(void);

	// functions  used to get Graph Indexes (While removing Graphs)
	long GetGraphIdxFromName(BSTR bstrGraphName);
	long GetLtblIdxFromName(BSTR bstrLtblgraphName);
	long GetCutomtextLTblIdxFromName(BSTR bstrLtblGraphName);


protected:
	DECLARE_EVENTSINK_MAP()

	//TeeChart Events
	afx_msg void OnAfterDrawTChart();

	afx_msg void OnBeforeDrawTChartSeries();

	afx_msg void OnBeforeDrawTChartAxes();

	afx_msg void OnClickTChart();

	afx_msg void OnClickTChartAxis(long Axis, long Button, long Shift, long X, long Y);

	afx_msg void OnClickTChartBackground(long Button, long Shift, long X, long Y);

	afx_msg void OnClickTChartLegend(long Button, long Shift, long X, long Y);

	afx_msg void OnClickTChartSeries(long SeriesIndex, long ValueIndex, long Button, long Shift, long X, long Y);

	afx_msg void OnDblClickTChart();

	afx_msg void OnGetTChartAxisLabel(long Axis, long SeriesIndex, long ValueIndex, BSTR FAR* LabelText);

	afx_msg void OnGetTChartLegendRect(long FAR* Left, long FAR* Top, long FAR* Right, long FAR* Bottom);

	afx_msg void OnGetTChartNextAxisLabel(long Axis, long LabelIndex, double FAR* LabelValue, BOOL FAR* MoreLabels);

	afx_msg  void OnTChartMouseDown(long Button, long Shift, long X, long Y) ;

	afx_msg void OnTChartMouseMove(long Shift, long X, long Y);

	afx_msg void OnTChartMouseUp(long Button, long Shift, long X, long Y);

	afx_msg void OnTChartPageChange();

	afx_msg void OnResizeTChart();

	afx_msg void OnScrollTChart();

	afx_msg void OnTChartTimer();

	afx_msg void OnUndoZoomTChart();

	afx_msg void OnZoomTChart();

	afx_msg void OnTChartCursorToolChange(long lTool,long X,long Y,double XVal,double YVal,long lSeries,long ValueIdx );

	afx_msg	void OnTChartKeyDown(long lngKeyCode,long lngShiftstate);

	afx_msg void OnTChartKeyUp(long lngKeyCode, long lngShiftState);

	afx_msg void OnMouseEnterTChartSeries(long lngSeriesIdx);

	afx_msg void OnMouseLeaveTChartSeries(long lngSeriesIdx);

	afx_msg void OnTChartSeriesAfterAdd(long lngSeriesIdx, long lngPointIdx);

	afx_msg void OnTChartSeriesAfterDrawValues(long lngSeriesIdx);

	afx_msg void OnTChartSeriesBeforeAdd(long lngSeriesIdx, VARIANT_BOOL * bMoreValues);

	afx_msg void OnTChartSeriesBeforeDrawValues(long lngSeriesIdx);

	afx_msg void OnGetTChartSeriesMarks(long lngSeriesIdx,long lngValueIdx,BSTR *strMarkText);

	//  End of TeeChart Events 

	void StartAnimation(VARIANT_BOOL bStartRStop);
	IUnknown* GetControlUnknown(void);
	void CopyGraph(void);
	void CopyData(void);
	VARIANT_BOOL ExportGraphData(LONG lngGraphIdx, LONG lngExpType,VARIANT_BOOL bIncludeIndex, VARIANT_BOOL bIncludeHeader, VARIANT_BOOL bIncludeTitle);

private:
	void prcDrawTrendLine(LONG lngCalculationGraphIdx, LONG lngTrendGraphIdx);
	void prcLinearFit(LONG lngGraphIdx, double & dblSlope, double & dblC);
	void prcFitExpCurve(int GraphID, double &dblA, double &dblB);
	void prcFitLogCurve(int GraphID, double &dblA, double &dblB);
	void prcFitPowerCurve(int GraphID,double& dblA, double& dblB);
private:
	void prcQuadraticFit(LONG lngGraphIdx, double & dblA0, double & dblA1, double & dblA2);
protected:
	void CalculateTrendLine(LONG lngGraphIdx, LONG lngTrendLineType, VARIANT_BOOL bShowTrendLine, LONG lngtrendLineColor);
	VARIANT_BOOL FindLinearCoefficients(LONG lngDataCount, VARIANT &varDblArrXData, VARIANT &varDblArrYData, DOUBLE* dblSlope, DOUBLE* dblIntercept);
	VARIANT_BOOL FindQuadraticCoefficients(LONG lngDataCount, VARIANT &varDblArrXData, VARIANT &varDblArrYData, DOUBLE* dblA0, DOUBLE* dblA1, DOUBLE* dblA2);
	VARIANT_BOOL LinearCoefficients(LONG lngGraphIdx, DOUBLE* dblByAddSlope, DOUBLE* dblByAddC);
	VARIANT_BOOL QuadraticCoefficients(LONG lngGraphIdx, DOUBLE* dblByAddA0, DOUBLE* dblByAddA1, DOUBLE* dblByAddA2);
	void LinearFitX(LONG lngDataCount, DOUBLE dblSlope, DOUBLE dblIntercept, DOUBLE* dblArrXdata, DOUBLE* dblArrYData);
	void QuadraticFitX(LONG lngDataCount, DOUBLE dblA0, DOUBLE dblA1, DOUBLE dblA2, DOUBLE* dblArrXData, DOUBLE* dblArrYData);
	void GetPeakInfo(LONG lngGraphIdx, VARIANT* dblHeight, VARIANT* dblWidth, VARIANT* dblArea, VARIANT* lngPeakStartIndex, VARIANT* lngPeakMaxindex, VARIANT* lngPeakEndIndex);
	LONG GetPeakIndexes(LONG lngGraphIdx, LONG lngPeakLevel, VARIANT* varLngPeakIndexes);
	VARIANT_BOOL GetAverageNoise(DOUBLE newValue);
	void SetAverageNoise(DOUBLE newValue, VARIANT_BOOL newVal);

	//  Begin of TeeChart Wrapper Events

	void OnAfterDraw(void)
	{		
		FireEvent(eventidOnAfterDraw, EVENT_PARAM(VTS_NONE));
	}
	void OnBeforeDrawSeries(void)
	{
		FireEvent(eventidOnBeforeDrawSeries, EVENT_PARAM(VTS_NONE));
	}

	void OnBeforeDrawAxes(void)
	{
		FireEvent(eventidOnBeforeDrawAxes, EVENT_PARAM(VTS_NONE));
	}

	void OnClick(void)
	{
		FireEvent(eventidOnClick, EVENT_PARAM(VTS_NONE));
	}

	void OnClickAxis(LONG Axis, LONG lButton, LONG lShift, LONG X, LONG Y)
	{
		FireEvent(eventidOnClickAxis, EVENT_PARAM(VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4), Axis, lButton, lShift, X, Y);
	}

	void OnClickBackground(LONG lButton, LONG Shift, LONG X, LONG Y)
	{
		FireEvent(eventidOnClickBackground, EVENT_PARAM(VTS_I4 VTS_I4 VTS_I4 VTS_I4), lButton, Shift, X, Y);
	}

	void OnClickLegend(LONG lButton, LONG Shift, LONG X, LONG Y)
	{
		FireEvent(eventidOnClickLegend, EVENT_PARAM(VTS_I4 VTS_I4 VTS_I4 VTS_I4), lButton, Shift, X, Y);
	}

	void OnClickSeries(LONG SeriesIndx, LONG ValueIndx, LONG lButton, LONG Shift, LONG X, LONG Y)
	{
		FireEvent(eventidOnClickSeries, EVENT_PARAM(VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4), SeriesIndx, ValueIndx, lButton, Shift, X, Y);
	}

	void OnDblClick(void)
	{
		FireEvent(eventidOnDblClick, EVENT_PARAM(VTS_NONE));
	}

	void OnCursorToolChange(LONG lngTool, LONG lngX, LONG lngY, DOUBLE dblXVal, DOUBLE dblYVal, LONG lngSeries, LONG ValueIdx)
	{
		FireEvent(eventidOnCursorToolChange, EVENT_PARAM(VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_I4 VTS_I4), lngTool, lngX, lngY, dblXVal, dblYVal, lngSeries, ValueIdx);
	}
	void OnKeyDown(LONG lngKeyCode, LONG lngShiftState)
	{
		FireEvent(eventidOnKeyDown, EVENT_PARAM(VTS_I4 VTS_I4), lngKeyCode, lngShiftState);
	}

	void OnKeyUp(LONG lngKeyCode, LONG lngShiftState)
	{
		FireEvent(eventidOnKeyUp, EVENT_PARAM(VTS_I4 VTS_I4), lngKeyCode, lngShiftState);
	}

	void OnMouseDown(LONG lngButton, LONG lngShiftState, LONG X, LONG Y)
	{
		FireEvent(eventidOnMouseDown, EVENT_PARAM(VTS_I4 VTS_I4 VTS_I4 VTS_I4), lngButton, lngShiftState, X, Y);
	}

	void OnMouseMove(LONG lngShiftState, LONG X, LONG Y)
	{
		FireEvent(eventidOnMouseMove, EVENT_PARAM(VTS_I4 VTS_I4 VTS_I4), lngShiftState, X, Y);
	}

	void OnMouseUp(LONG lngButton, LONG lngShiftState, LONG X, LONG Y)
	{
		FireEvent(eventidOnMouseUp, EVENT_PARAM(VTS_I4 VTS_I4 VTS_I4 VTS_I4), lngButton, lngShiftState, X, Y);
	}
	void OnMouseEnterGraph(LONG lngGraphIdx)
	{
		FireEvent(eventidOnMouseEnterGraph, EVENT_PARAM(VTS_I4), lngGraphIdx);
	}

	void OnMouseLeaveGraph(LONG lngGraphIdx)
	{
		FireEvent(eventidOnMouseLeaveGraph, EVENT_PARAM(VTS_I4), lngGraphIdx);
	}

	void OnResize(void)
	{
		FireEvent(eventidOnResize, EVENT_PARAM(VTS_NONE));
	}

	void OnScroll(void)
	{
		FireEvent(eventidOnScroll, EVENT_PARAM(VTS_NONE));
	}

	void OnTimer(void)
	{
		FireEvent(eventidOnTimer, EVENT_PARAM(VTS_NONE));
	}

	void OnZoom(void)
	{
		FireEvent(eventidOnZoom, EVENT_PARAM(VTS_NONE));
	}

	void OnUndoZoom(void)
	{
		FireEvent(eventidOnUndoZoom, EVENT_PARAM(VTS_NONE));
	}

	void OnGraphAfterAdd(LONG lngGraphIdx, LONG lngPointIdx)
	{
		FireEvent(eventidOnGraphAfterAdd, EVENT_PARAM(VTS_I4 VTS_I4), lngGraphIdx, lngPointIdx);
	}

	void OnGraphAfterDrawValues(LONG lngGraphIdx)
	{
		FireEvent(eventidOnGraphAfterDrawValues, EVENT_PARAM(VTS_I4), lngGraphIdx);
	}

	void OnGraphBeforeAdd(LONG lngGraphIdx,VARIANT_BOOL * bMoreValues)
	{
		FireEvent(eventidOnGraphBeforeAdd, EVENT_PARAM(VTS_I4 VTS_PBOOL), lngGraphIdx,bMoreValues);
	}

	void OnGraphBeforeDrawValues(LONG lngGraphIdx)
	{
		FireEvent(eventidOnGraphBeforeDrawValues, EVENT_PARAM(VTS_I4), lngGraphIdx);
	}
	void OnPageChange(void)
	{
		FireEvent(eventidOnPageChange, EVENT_PARAM(VTS_NONE));
	}

	void OnGetLegendRect(LONG* lngLeft, LONG* lngTop, LONG* lngRight, LONG* lngBottom)
	{
		FireEvent(eventidOnGetLegendRect, EVENT_PARAM(VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4), lngLeft, lngTop, lngRight, lngBottom);
	}


	//	End of TeeChart Wrapper Events


	void PeakFillArea(LONG lngGraphIdx);
	void DrawBaseLine(LONG lngGraphIdx);
public:
	void fncPerformIntegration(void);

protected:
	LONG GetBaseLineType(void);
	void SetBaseLineType(LONG newVal);
	OLE_COLOR GetBaseLineColor(void);
	void SetBaseLineColor(OLE_COLOR newVal);
	LONG GetNumberOfGraphs(void);

	LONG GetAllGraphIDs(VARIANT* varLngGraphIndexes);
	OLE_COLOR GetPeakFillColor(void);
	void SetPeakFillColor(OLE_COLOR newVal);
	DOUBLE GetPeakMinArea(void);
	void SetPeakMinArea(DOUBLE newVal);
	DOUBLE GetPeakMinHeight(void);
	void SetPeakMinHeight(DOUBLE newVal);
	DOUBLE GetPeakMinWidth(void);
	void SetPeakMinWidth(DOUBLE newVal);
	void GetPeaksCount(VARIANT* varLngPeaksCount);

	// Method to calculate the Peaks indexes
	long fncCalculatePeakIndexes(long lngGraphIdx, long * lngPeakIndex);
	void DisplayTextAt(LONG lngGraphIdx, LPCTSTR bstrName, DOUBLE dblXVal, DOUBLE dblYVal);
	OLE_COLOR GetBackGroundColor(void);
	void SetBackGroundColor(OLE_COLOR newVal);
	OLE_COLOR GetCustomTextColor(void);
	void SetCustomTextColor(OLE_COLOR newVal);
	OLE_COLOR GetCustomTextBackColor(void);
	void SetCustomTextBackColor(OLE_COLOR newVal);
	DOUBLE GetAverageNoise(void);
	void SetAverageNoise(DOUBLE newVal);
	OLE_COLOR GetAxesMarkingColor(void);
	void SetAxesMarkingColor(OLE_COLOR newVal);
	VARIANT_BOOL GetShowLegends(void);
	void SetShowLegends(VARIANT_BOOL newVal);
	LONG GetGraphData(LONG lngGraphIdx, VARIANT* varDblXval, VARIANT* varDblYval);
	void GetGraphDataAt(LONG lngGraphIdx, LONG lngIndex, DOUBLE* dblXval, DOUBLE* dblYval);
	LONG GetGraphDataCont(LONG lngGraphIdx);
	void GetGraphMinMax(LONG lngGraphIdx, DOUBLE* dblXmin, DOUBLE* dblYmin, DOUBLE* dblXmax, DOUBLE* dblYmax);

public:
	afx_msg void OnDestroy();
protected:
	BSTR GetBackImage(void);
	void SetBackImage(LPCTSTR newVal);
	//void AddPoints(LONG lngGraphId, LONG lngNoOfPoints, VARIANT &varXVal, VARIANT &varYVal);
	//void AddPoints1(LONG lngGraphID, LONG lngNoOfPoints, SAFEARRAY sArrXVals);
public:
	long fncGetDoubleValuesFromSafeArray(VARIANT &varSource, DOUBLE * dblArrResult);
protected:
	//	LONG GetData(LONG lngGraphIdx, VARIANT* varDblXVal, VARIANT* varDblYVal);
	//	void LongReturn(VARIANT* var);
	LONG GetGraphPeaksCount(LONG lngGraphIdx);
	void PrintGraph(LONG lngPrinterDC, LONG lngPageLeft, LONG lngPageTop, LONG lngPageRight, LONG lngPageBottom);
	void PrintPreview(LONG lngDC, LONG lngPageLeft, LONG lngPageTop, LONG lngPageRight, LONG lngPageBottom);
	VARIANT_BOOL GetEnableHorzDatumLine(void);
	void SetEnableHorzDatumLine(VARIANT_BOOL newVal);
	VARIANT_BOOL GetEnableVericalDatumLine(void);
	void SetEnableVericalDatumLine(VARIANT_BOOL newVal);

	void DrawDatumLine(LONG lngGraphIdx, DOUBLE dblXVal, DOUBLE dblYVal, OLE_COLOR clrLineColor);
	void fncDisplayDatumLineText(int nDatumLineIdx,double dblXVal,double dblYVal,long lngGraphIdx);


	LONG GetZoomDirection(void);
	void SetZoomDirection(LONG newVal);
	VARIANT_BOOL GetEnableZoom(void);
	void SetEnableZoom(VARIANT_BOOL newVal);
	LONG GetMouseButtonForZoom(void);
	void SetMouseButtonForZoom(LONG newVal);
	LONG GetMinimumPixelsForZoom(void);
	void SetMinimumPixelsForZoom(LONG newVal);
	LONG GetScrollDirection(void);
	void SetScrollDirection(LONG newVal);
	LONG GetMouseButtonForScroll(void);
	void SetMouseButtonForScroll(LONG newVal);



	LONG FindPeaks(VARIANT &varDblYvals, LONG lngDataPointsCount, LONG lngPeakLevel, VARIANT* varLngPeakIndexes);

	VARIANT_BOOL GetShowHeader(void);
	void ShowHeader(VARIANT_BOOL newVal);
	BSTR GetHeader(void);
	void SetHeader(LPCTSTR newVal);
	OLE_COLOR GetAxisGridColor(LONG lngAxis);
	void SetAxisGridColor(LONG lngAxis,OLE_COLOR newVal);
	//SHORT GetAxesPresition(LONG lngAxis);
	//void SetAxesPresition(LONG lngAxis, SHORT newVal);
	SHORT GetAxesMarkingPrecision(LONG lngAxis);
	void SetAxesMarkingPrecision(LONG lngAxis, SHORT newVal);
	BSTR GetAxestitle(LONG lngAxis);
	void SetAxestitle(LONG lngAxis, LPCTSTR newVal);
	VARIANT_BOOL EntireGraph(LONG lngGraphIdx);
	DOUBLE GetAxisMaximum(LONG lngAxis);
	void SetAxisMaximum(LONG lngAxis, DOUBLE newVal);
	OLE_COLOR GetAxesTitlesColor(LONG lngAxis);
	void SetAxesTitlesColor(LONG lngAxis, OLE_COLOR newVal);
	DOUBLE GetAxisMinimum(LONG lngAxis);
	void SetAxisMinimum(LONG lngAxis, DOUBLE newVal);


	SHORT GetAxisGridStyle(LONG lngAxis);
	void SetAxisGridStyle(LONG lngAxis, SHORT newVal);
private:
	// To set enable/Disable state corresponding to the Variables set for the datum line and to remove the  Info about disabled datum line.
	void fncSetStateForDatumLine(void);
protected:
	VARIANT_BOOL ShowPeaks(LONG lngGraphIdx, SHORT intPeakLevel);
private:	
	void prcDisplayPeaks(void); // Method to display the Peaks.
protected:
	VARIANT_BOOL HidePeaks(LONG lngGraphIdx);
	VARIANT_BOOL GetShowDataAtPeak(void);
	void SetShowDataAtPeak(VARIANT_BOOL newVal);
	VARIANT_BOOL GetCrossWire(void);
	void SetCrossWire(VARIANT_BOOL newVal);
private:
	// To draw the cross wire
	void prcDrawCrossWire(void);
	void prcBaseLine(void);
protected:
	VARIANT_BOOL MoveCrossWireToFirst(LONG* lngGraphID, LONG* lngDataPoint);
	VARIANT_BOOL MoveCrossWireToLast(LONG* lngGraphID, LONG* lngDataPoint);
	VARIANT_BOOL MoveCrossWireToNext(LONG* lngGraphID, LONG* lngDataPoint, SHORT intStepBy);
	VARIANT_BOOL MoveCrossWireToPrev(LONG* lngGraphID, LONG* lngDataPoint, SHORT intStepBy);
	VARIANT_BOOL DisplayCrossWireAt(DOUBLE dblXval, DOUBLE dblYval);
	void SetCustomCrosswireText(LPCTSTR bstrCrosswireText, VARIANT_BOOL blnHideXYValues, DOUBLE Concentration);
	LONG GetCrossWireDataPointIndex(void);
	void SetCrossWireDataPointIndex(LONG newVal);
private:
	// To display the Cross wire corresponding values
	void prcDisplayCrossWireXYValues(void);
protected:
	VARIANT_BOOL GetSort(void);
	void SetSort(VARIANT_BOOL newVal);
public:
	// To clear all the Peak info Stored structures
	void ClearPeakInformation(void);
protected:
	VARIANT_BOOL GetAutoRange(void);
	void SetAutoRange(VARIANT_BOOL newVal);
	VARIANT_BOOL GetPerConc(void);
	void SetPerConc(VARIANT_BOOL newVal);
	VARIANT_BOOL GetShowConcAtPeaks(void);
	void SetShowConcAtPeaks(VARIANT_BOOL newVal);
	VARIANT_BOOL GetShowXTitle(void);
	void SetShowXTitle(VARIANT_BOOL newVal);
	VARIANT_BOOL GetShowYTitle(void);
	void SetShowYTitle(VARIANT_BOOL newVal);
	void SetLegendFont(LPCTSTR strFontName, LONG lngFontSize);
	void SetXYMarkingFont(LPCTSTR strFontName, LONG lngFontSize);
	void SetCustomTextFont(LPCTSTR strFontName, LONG lngFontSize);
	SHORT GetXGrids(void);
	void SetXGrids(SHORT newVal);
	SHORT GetYGrids(void);
	void SetYGrids(SHORT newVal);
	VARIANT_BOOL ZoomIn(DOUBLE dblXMin, DOUBLE dblXMax, DOUBLE dblYMin, DOUBLE dblYMax);
	void ZoomOut(void);
	void SetHeaderFont(LPCTSTR strFontName, LONG lngFontSize);
	void SetAxesTitlesFont(LPCTSTR strFontName, LONG lngFontSize);
	void DisplayText(LPCTSTR bstrText, LONG lngLeftMargin, LONG lngRightMargin);
public:
	// Method to display the custom text at specified location.
	void prcDisplayCustomText(void);
protected:
	void ClearCustomText(void);
	SHORT GetPeakWidthCalculationType(void);
	void SetPeakWidthCalculationType(SHORT newVal);

	void WidthAt5PercentHeight(LONG lngPos, DOUBLE* dblWidth, DOUBLE* dblLeftWidth, DOUBLE* dblRightWidth);
	void WidthAt10PercentHeight(LONG lngPos, DOUBLE* dblWidth, DOUBLE* dblLeftWidth, DOUBLE* dblRightWidth);
	void WidthAtHalfHeight(LONG lngPos, DOUBLE* dblWidth, DOUBLE* dblLeftWidth, DOUBLE* dblRightWidth);
	void prcCalculatePoints(POINT& pt1, POINT & pt2);

	//17/04/08
//	LONG AddCustomAxis(VARIANT_BOOL blnIsHorizontal);
	void MoveAxisFromBasePosition(LONG lngAxisIdx,LONG lngPosition, VARIANT_BOOL blnIsStdAxis=FALSE);
	void ChangeAxisStartPosition(LONG lngAxisIdx, LONG lngPositionInPercent, VARIANT_BOOL blnIsStdAxis);
	void ChangeAxisEndPosition(LONG lngAxisIdx, LONG lngPositionInPercent, VARIANT_BOOL blnIsStdAxis);
	void AssignAxesForGraph(LONG lngGraphIdx, LONG lngCustomHorzAxis, LONG lngCustomVertAxis);
	void RemoveCustomAxis(LONG lngCustomAxisIdx);
	void RemoveAllCustomAxes(void);
	LONG AddCustomAxis(VARIANT_BOOL lbnIsHorizontal);

	BSTR GetCustomAxisTitle(LONG lngAxisIdx);
	void SetCustomAxisTitle(LONG lngAxisIdx, LPCTSTR newVal);
	DOUBLE GetCustomAxisMaximum(LONG lngAxisIdx);
	void SetCustomAxisMaximum(LONG lngAxisIdx, DOUBLE newVal);
	DOUBLE GetCustomAxisMinimum(LONG lngAxisIdx);
	void SetCustomAxisMinimum(LONG lngAxisIdx, DOUBLE newVal);
	LONG GetCustomAxisGrids(LONG lngAxisIdx);
	void SetCustomAxisGrids(LONG lngAxisIdx, LONG newVal);
	LONG GetCustomAxisTitleAngle(LONG lngAxisIdx);
	void SetCustomAxisTitleAngle(LONG lngAxisIdx, LONG newVal);
private:
	// Calculates the rectangle of the graph
	void CalculateGraphRect(long lngGraphIdx,long *lngLeft, long *lngTop, long *lngRight, long *lngBottom);
protected:
	void DoGraphReprocess(BYTE* bytEventInfo, LONG lngNoOfEvents);

public:
	stEventInfo* m_ptrEventInfo;
	LONG m_lngEventCount;

	BOOL blnStopDetect;

	CArray<int, int>m_arrNegativeStartIndex;
	CArray<int, int>m_arrNegativeEndIndex;
    CArray<int, int>m_arrTangentPeakIndex;
	void DefaultBaseLineMethod(double dblStartTime, double dblEndTime, double dblValue);
	BOOL fncPeakCalculations(long lngMaxHeightIndex, double* dblXArr, double* dblYArr, long lngCount, double* dblArea, double* dblFWHH, double* dblHeight, double* dblWidth,int PeakNo);
	void fncForceBaseMethod(double dblStartTime, double dblEndTime, double dblValue);
	void fncForcedPeak(double dblStartTime, double dblEndTime, double dblValue);
	void fncBaseAtNextValleyMethod(double dblStartTime, double dblEndTime, double dblValue);
	void fncValleyToValleyMethod(double dblStartTime, double dblEndTime, double dblValue);
	void fncHorizontalBaselineMethod(double dblStartTime, double dblEndTime, double dblValue);
	void fncPenetrationWithNegativePeakMethod(double dblStartTime, double dblEndTime, double dblValue);
	void fncApplyHorizontalBaseMethod(int nStartIndex);
	void fncApplyManualSkimming(int nStartIndex);
	void fncStartDetect(double dblStartTime, double dblEndTime, double dblValue);
	void fncStopDetect(double dblStartTime, double dblEndTime, double dblValue);
	void fncHeightReject(double dblStartTime, double dblEndTime, double dblValue);
    void fncTangentSkiming(double dblStartTime, double dblEndTime, double dblValue);
	void fncManualBaseline(double dblStartTime, double dblEndTime, double dblValue);
    //To calculate width at half height,width at 10%height and width at 5%height for the Manual peak.

	//added by sirisha on 22/12/2011
	void fncWidthAtDiffHeights(long lngPeakStartIndex,long lngPeakEndIndex,long lngPeakMaxIndex,BOOL bAdjuestPeak=FALSE,BOOL bInsertPeak=FALSE);
   int fncCheckForPeakRedundancy(double dblStartTime, double dblEndTime);

	DOUBLE GetPeakMinTreshold();
	void SetPeakMinTreshold(DOUBLE newVal);



protected:
	void MarkStartnEndpts(LONG lngGraphIdx);
	void SetStartnEndptMarkingColor(OLE_COLOR newVal);
	OLE_COLOR GetStartnEndptMarkingColor(void);

	void PeakDetected(void)
	{
		FireEvent(eventidOnPeakDetected, EVENT_PARAM(VTS_NONE));
	}
public:
	// Check for the Graph with the given Id
	unsigned int IsGraphExisting(long lngGraphId);
public:
	// Get the underlying Teechart Interface
	LPDISPATCH GetTeeChart(void);

	long m_lngSize;
public:
	// To interpolate the Data 
	double InterPolateData(long lngGraphId, double dblXvalue);
	BOOL fncValidateThePoints( int nStartTimeIndex, int nEndTimeIndex,int nPeakMaxIndex,int& nFailedAtIndex );
	void FindArea(LONG lngGraphID, DOUBLE dblStartPointXVal,DOUBLE dblStartPointYVal, DOUBLE dblEndPointXVal,DOUBLE dblEndPointYVal,LONG nStartIndex,LONG nEndIndex,DOUBLE* dblArea);
protected:
	void GetArea(LONG lngGraphID, DOUBLE dblStartPointXVal, DOUBLE dblStartPointYVal, DOUBLE dblEndPointXVal, DOUBLE dblEndPointYVal, LONG lngStartPointIndex, LONG lngEndPointIndex, DOUBLE* ptrdblArea);
};

