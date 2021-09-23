// FitAlgorithms.h : Declaration of the CFitAlgorithms

#ifndef __FITALGORITHMS_H_
#define __FITALGORITHMS_H_

#include "resource.h"       // main symbols
#define	MAX_GROUPSIZE	25

const int gArrGroup[MAX_GROUPSIZE]={-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10,11,12};

/////////////////////////////////////////////////////////////////////////////
#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

// CFitAlgorithms
class ATL_NO_VTABLE CFitAlgorithms : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFitAlgorithms, &CLSID_FitAlgorithms>,
	public IConnectionPointContainerImpl<CFitAlgorithms>,
	public IDispatchImpl<IFitAlgorithms, &IID_IFitAlgorithms, &LIBID_CURVEFITALGORITHMSLib>
{
public:
	CFitAlgorithms()
	{
		blnFail	=	FALSE;
	}
#ifndef _CE_DCOM
	DECLARE_REGISTRY_RESOURCEID(IDR_FITALGORITHMS)
#endif
//DECLARE_REGISTRY_RESOURCEID(IDR_FITALGORITHMS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFitAlgorithms)
	COM_INTERFACE_ENTRY(IFitAlgorithms)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CFitAlgorithms)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IFitAlgorithms
public:
	STDMETHOD(SmoothData)(LONG lngSmoothType, VARIANT* varYData, LONG lngSpectrumCount, LONG lngDataCount, LONG lngSmoothSize, LONG lngOrderOfDer, LONG lngPolyDegree);
	STDMETHOD(FindQuadraticFitXValues)(LONG lngDataCount,DOUBLE dblA0,DOUBLE dblA1,DOUBLE dblA2,VARIANT *varXVals, VARIANT varYVals);
	STDMETHOD(FindLinearFitXValues)(LONG lngDataCount,DOUBLE dblSlope,DOUBLE dblIntercept,VARIANT *varXVals,VARIANT varYVals);
	STDMETHOD(FindQuadraticFitCoefficients)(LONG lngDataCount,VARIANT varDblXVals,VARIANT varDblYVals,DOUBLE *dblA0,DOUBLE *dblA1,DOUBLE *dblA2, BOOL *pVal);
	STDMETHOD(FindLinearFitCoefficients)(LONG lngDataCount,VARIANT varDblXVals,VARIANT varDblYVals,double *dblSlope, double *dblIntercept, BOOL *pVal);
	STDMETHOD(DerivateData)(LONG lngDerivativeType,VARIANT* varYData,int nDataCount,int nGroupSize,int intOrderOfDer,int intPolyDegree);


	long fncGetDoubleValuesFromSafeArray(VARIANT &varSource, DOUBLE * dblArrResult);
	bool SmoothBoxCar(double **dblArrYdata, long lngSpectrumCount, long lngDataCount, long lngGroupSize);
	bool SmoothMovingBoxCar(double **dblArrYData, long lngSpectrumCount, long lngDataCount, long lngGroupSize);
	bool SmoothSavitzkyGolay(double ** dblArrYdata, long lngSpectrumCount, long lngDataCount, long lngGroupSize, long lngFilterOrder,long lngOrderOfDeri);
	bool GetSavitzkyCoefficients(int nSmoothSize, int nFilterOrder,int nOrderOfDeri, double *dblCoefficients);
		
	BOOL DerivatePointDiff(double *m_rArrYData, int nDataCount,int nGroupSize,int nOrderOfDerivative);

	BOOL SmoothDerivateSavitGolay(double *m_rArrYData,int nDataCount,int nGroupSize,int nOrderOfDerivative,int nPolynomialDegree);
	void For3rdDer5thPolynomial(double rCoeff[], int nGroupSize);
	void GetAbscissaPoints(int nGroupSize, int nArrRange[]);
	int GetNormalizedCoeff(int nGroupSize, int nArrRange[], double rCoeff[], int nOrderDer, int nPolyDegree);





private:
	BOOL blnFail;	
};

#endif //__FITALGORITHMS_H_
	