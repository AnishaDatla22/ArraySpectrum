// FitAlgorithms.cpp : Implementation of CFitAlgorithms
#include "stdafx.h"
#include "CurveFitAlgorithms.h"
#include "FitAlgorithms.h"

/////////////////////////////////////////////////////////////////////////////
// CFitAlgorithms

STDMETHODIMP CFitAlgorithms::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IFitAlgorithms
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


long CFitAlgorithms::fncGetDoubleValuesFromSafeArray(VARIANT &varSource, DOUBLE *dblArrResult)
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

STDMETHODIMP CFitAlgorithms::FindLinearFitCoefficients(LONG lngDataCount,VARIANT varDblXVals,VARIANT varDblYVals, double *dblSlope, double *dblIntercept, BOOL *pVal)
{
	// TODO: Add your implementation code here

	double dblNumerator;
	double dblDenominator;
	double dblSumXY=0;
	double dblSumX=0;
	double dblSumY=0;
	double dblSumXSquare=0;	

	long lngLBound,lngUBound,lngResultBound;

	// The arrays created must be of the same size as the data count present in VARIANT's
	// If not it will give assertion while retrieving data from VARIANT"s to Double in 'fncGetDoubleValuesFromSafeArry' function

	SafeArrayGetLBound(varDblXVals.parray,1,&lngLBound);
	SafeArrayGetUBound(varDblXVals.parray,1,&lngUBound);
	lngResultBound	=	lngUBound	-	lngLBound;
	double *dblArrX	=	new double[lngResultBound+1];	

	SafeArrayGetLBound(varDblYVals.parray,1,&lngLBound);
	SafeArrayGetUBound(varDblYVals.parray,1,&lngUBound);
	lngResultBound	=	lngUBound	-	lngLBound;

	double *dblArrY	=	new double[lngResultBound+1];

	long lSize=fncGetDoubleValuesFromSafeArray(varDblXVals,dblArrX);
	if(lngDataCount>lSize)
		lngDataCount	=	lSize;


	lSize=fncGetDoubleValuesFromSafeArray(varDblYVals,dblArrY);
	if(lngDataCount>lSize)
		lngDataCount=lSize;
	

	for(int i=0;i<lngDataCount;i++)
	{
		dblSumX += dblArrX[i];
		dblSumY += dblArrY[i];
		dblSumXY += dblArrX[i] * dblArrY[i];
		dblSumXSquare +=pow(dblArrX[i],2);
	}

	dblNumerator	= ((lngDataCount*dblSumXY)-(dblSumX*dblSumY));
	dblDenominator	= ((lngDataCount*dblSumXSquare)-(dblSumX*dblSumX));

	if(dblDenominator!=0)
		*dblSlope = dblNumerator/dblDenominator; // Slope(m) of Linear equation

	dblNumerator = ((dblSumY*dblSumXSquare)-(dblSumX*dblSumXY));
	if(dblDenominator!=0)
		*dblIntercept = dblNumerator/dblDenominator; // Intercept(C) of Linear Equation


	delete [] dblArrX;
	delete [] dblArrY;
	*pVal = TRUE;

	return S_OK;

	return S_OK;
}

STDMETHODIMP CFitAlgorithms::FindQuadraticFitCoefficients(LONG lngDataCount, VARIANT varDblXVals, VARIANT varDblYVals, DOUBLE *dblA0, DOUBLE *dblA1, DOUBLE *dblA2, BOOL *pVal)
{
	// TODO: Add your implementation code here

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
	
	SafeArrayGetLBound(varDblXVals.parray,1,&lngLBound);
	SafeArrayGetUBound(varDblXVals.parray,1,&lngUBound);
	lngResultBound	=	lngUBound	-	lngLBound;
	

	double *dblArrX	=	new double[lngResultBound+1];

	
	SafeArrayGetLBound(varDblYVals.parray,1,&lngLBound);
	SafeArrayGetUBound(varDblYVals.parray,1,&lngUBound);
	lngResultBound	=	lngUBound	-	lngLBound;
	

	double *dblArrY	=	new double[lngResultBound+1];	
	long lSize	=	fncGetDoubleValuesFromSafeArray(varDblXVals,dblArrX);
	

	if(lngDataCount>lSize)
		lngDataCount=lSize;

	lSize=fncGetDoubleValuesFromSafeArray(varDblYVals,dblArrY);

	if(lngDataCount>lSize)
		lngDataCount=lSize;


	for(long i=0;i<lngDataCount;i++)
	{
		dblSumX+= dblArrX[i];
		dblSumY+= dblArrY[i];
		dblSumXY+= dblArrX[i] * dblArrY[i];
		dblSumXSquare += pow(dblArrX[i],2);
		
		dblSumXSquareY += pow(dblArrX[i],2) * dblArrY[i];
		
		dblSumXCube += pow(dblArrX[i],3);
		dblSumXFour += pow(dblArrX[i],4);
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
	
	if(lngDataCount==0)		//08/01/09
		*dblA0	=	0.0;	//08/01/09
	else					//08/01/09
		*dblA0 = (dblSumY-((*dblA1) * dblSumX)-((*dblA2) * dblSumXSquare))/lngDataCount; // Constant value
	
	delete[] dblArrX;
	delete[] dblArrY;


	*pVal = TRUE;
	
	return S_OK;
}


// finds the 'X' coordinate values for the linear equation, if the slope,intercept and 'Y' values for that
// linear equation are given
STDMETHODIMP CFitAlgorithms::FindLinearFitXValues(LONG lngDataCount, DOUBLE dblSlope, DOUBLE dblIntercept, VARIANT *varXVals, VARIANT varYVals)
{
	// TODO: Add your implementation code here

	if(dblSlope == 0)
	{
		//MessageBox(_T("There will be multiple vlaues of X for this Y data set"));
		return S_FALSE;
	}
	else
	{
		long lngLBound,lngUBound,lngResultBound;

		SafeArrayGetLBound(varYVals.parray,1,&lngLBound);
		SafeArrayGetUBound(varYVals.parray,1,&lngUBound);
		lngResultBound	=	lngUBound	-	lngLBound;
		double *dblArrY=new double[lngResultBound+1];
		long lngSize	=	fncGetDoubleValuesFromSafeArray(varYVals,dblArrY);
		if(lngDataCount>lngSize)
			lngDataCount	=	lngSize;

		SAFEARRAYBOUND sab[1];
		sab[0].cElements	=	lngDataCount;
		sab[0].lLbound		=	0;
		SAFEARRAY *pSa	=	SafeArrayCreate(VT_R8,1,sab);
		VariantInit(varXVals);
		(*varXVals).vt	=	VT_ARRAY|VT_R8;

		double dblTempX;
		for(long lngIndex = 0;lngIndex < lngDataCount;lngIndex++)
		{
			//dblArrXData[lngIndex] = (dblArrYData[lngIndex] - dblIntercept)/ dblSlope;
			dblTempX	=	(dblArrY[lngIndex] - dblIntercept)/ dblSlope;
			SafeArrayPutElement(pSa,&lngIndex,&dblTempX);
		}
		(*varXVals) .parray	=	pSa;

		delete []dblArrY;

	}
	return S_OK;
}

STDMETHODIMP CFitAlgorithms::FindQuadraticFitXValues(LONG lngDataCount, DOUBLE dblA0, DOUBLE dblA1, DOUBLE dblA2, VARIANT *varXVals, VARIANT varYVals)
{
	// TODO: Add your implementation code here

	double dblRoot1 = 0;
	double dblRoot2 = 0;
	double dblTempA0;
	long lngLBound,lngUBound,lngResultBound;

	SafeArrayGetLBound(varYVals.parray,1,&lngLBound);
	SafeArrayGetUBound(varYVals.parray,1,&lngUBound);
	lngResultBound	=	lngUBound	-	lngLBound;
	double *dblArrY=new double[lngResultBound+1];
	long lngSize	=	fncGetDoubleValuesFromSafeArray(varYVals,dblArrY);
	if(lngDataCount>lngSize)
		lngDataCount	=	lngSize;

	SAFEARRAYBOUND sab[1];
	sab[0].cElements	=	lngDataCount;
	sab[0].lLbound		=	0;
	SAFEARRAY *pSa	=	SafeArrayCreate(VT_R8,1,sab);
	VariantInit(varXVals);
	(*varXVals).vt	=	VT_ARRAY|VT_R8;

	double dblTempX;

	for(long lngIndex=0;lngIndex<lngDataCount;lngIndex++)
	{
		// y = ax2 + bx + c ==> ax2 + bx + (c-y)= 0 

		dblTempA0 = dblA0 - dblArrY[lngIndex];
		// checking whether the value under root is lees than zero
		if (((dblA1 * dblA1)-(4 * dblTempA0 * dblA2)) < 0)
		{
			dblTempX	=	-1;
			SafeArrayPutElement(pSa,&lngIndex,&dblTempX);
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
				dblTempX	=	-1;
				SafeArrayPutElement(pSa,&lngIndex,&dblTempX);
				continue;
			}  

			// Checking for the second condition when one root is positive and the other is
			// negative discard the negative root
			if (dblRoot1 < 0) 
			{
				if(dblRoot2 >=0) 
				{
					dblTempX	=	dblRoot2;
					SafeArrayPutElement(pSa,&lngIndex,&dblTempX);
					continue;
				} 
			}  

			if (dblRoot2 < 0) 
			{
				if(dblRoot1>=0) 
				{
					dblTempX	=	dblRoot1;
					SafeArrayPutElement(pSa,&lngIndex,&dblTempX);
					continue;
				}
			}
			// Checking for the third condition when both roots are positive
			if (dblA2 == 0)
			{
				MessageBox(NULL,_T("Didision by Zero not permitted"),NULL,MB_OK|MB_ICONWARNING); //String Table
			}
			else
			{
				if ((dblRoot2 >= 0) && (dblRoot1 >= 0))
				{
					if (dblRoot1 < (-dblA1/(2*dblA2)) && dblRoot2 < (-dblA1/(2*dblA2)))
					{
						dblTempX	=	-1;
						SafeArrayPutElement(pSa,&lngIndex,&dblTempX);
						continue;
					}
					else if (dblRoot2 <= (-dblA1/2* dblA2))
					{
						dblTempX	=	dblRoot2;
						SafeArrayPutElement(pSa,&lngIndex,&dblTempX);
						continue;
					}
					else if (dblRoot1 <= (-dblA1/2* dblA2))
					{
						dblTempX	=	dblRoot1;
						SafeArrayPutElement(pSa,&lngIndex,&dblTempX);
						continue; 
					}  
					else
					{
						dblTempX	=	dblRoot1;
						SafeArrayPutElement(pSa,&lngIndex,&dblTempX);
						continue; 
					}
				}                 
			}  
		} 
	}
	(*varXVals).parray	=	pSa;

	delete [] dblArrY;

	return S_OK;
}

STDMETHODIMP CFitAlgorithms::SmoothData(LONG lngSmoothType, VARIANT *varYData, LONG lngSpectrumCount, LONG lngDataCount, LONG lngSmoothSize, LONG lngOrderOfDer, LONG lngPolyDegree)
{
	// TODO: Add your implementation code here
    int i=0;
	long lngUBound,lngLBound, lngResultBound,lngArrayDims;

	lngArrayDims	=	SafeArrayGetDim((*varYData).parray);
	if(lngArrayDims<lngSpectrumCount)
		lngSpectrumCount	=	lngArrayDims;

	SafeArrayGetLBound((*varYData).parray,lngArrayDims,&lngLBound);
	SafeArrayGetUBound((*varYData).parray,lngArrayDims,&lngUBound);
	lngResultBound	=	lngUBound	-	lngLBound;

	double **dblArrData	=	new double*[lngArrayDims];
	for(i=0;i<lngArrayDims;i++)
		dblArrData[i]	=	new double[lngResultBound+1];

	long lngCount	=	fncGetDoubleValuesFromSafeArray((*varYData),*dblArrData);// uncomment '*'before dblArrData
	if(lngCount<lngDataCount)
		lngDataCount	=	lngCount;

	// To put the elements in SafeArray
	long index[2];

	BOOL blnFail	=	FALSE;

	switch(lngSmoothType)
	{
	case 1: //Box Car smoothing
		if(SmoothBoxCar(dblArrData,lngSpectrumCount,lngDataCount,lngSmoothSize)==false)
			blnFail	=	TRUE;
		break;

	case 2: // Moving Box Car Smoothing
		if(SmoothMovingBoxCar(dblArrData,lngSpectrumCount,lngDataCount,lngSmoothSize)==false)
			blnFail	=	TRUE;

		break;
	case 3:  // Savitzky-Golay Smoothing
		if(SmoothSavitzkyGolay(dblArrData,lngSpectrumCount,lngDataCount,lngSmoothSize,lngPolyDegree,lngOrderOfDer)==false)
			blnFail	=	TRUE;
		break;
	default:
		blnFail	=	TRUE;
		break;
	}
	SAFEARRAYBOUND *sab;
	if(!blnFail)// If smoothing process doesn't fail  then store the smoothed data in the i/p variant
	{
		//SafeArrayDestroy((*varYData).parray);
		sab	=	new SAFEARRAYBOUND[2];
		if(lngArrayDims	!=	1)
		{
			sab[0].cElements		=	lngArrayDims;
			sab[1].cElements		=	lngDataCount;
		}
		else
		{
			sab	=	new SAFEARRAYBOUND;
			sab[0].cElements		=	lngDataCount;
		}


		SAFEARRAY *pSa			=	SafeArrayCreate(VT_R8,lngArrayDims,sab);
		index[0]				=	lngArrayDims;
		index[1]				=	lngDataCount;		
		for(long n=0;n<lngArrayDims;n++)
		{
			for(long j=0;j<lngDataCount;j++)
			{
				index[0]		=	n;
				index[1]		=	j;
				if(lngArrayDims>1)
					SafeArrayPutElement(pSa,index,&dblArrData[n][j]);
				else if(lngArrayDims==1)
					SafeArrayPutElement(pSa,&j,&dblArrData[n][j]);
			}
		}
		(*varYData).parray		=	pSa;
	}

	for(i=0;i<lngArrayDims;i++)
		delete []dblArrData[i];
	delete []dblArrData;
	dblArrData = NULL;

	delete []sab;

	if(blnFail)
	{
#ifdef _TESTDBG
		WriteMemoryLog("Smooth data function returns E_FAIL\n\n");
#endif
		return E_FAIL;
	}
	else
	{
#ifdef _TESTDBG
		WriteMemoryLog("Smooth data function returns S_OK\n\n");
#endif
		return S_OK;
	}

	return S_OK;
}

bool CFitAlgorithms::SmoothBoxCar(double **dblArrYdata, long lngSpectrumCount, long lngDataCount, long lngGroupSize)
{
#ifdef _TESTDBG
	WriteMemoryLog("Enetered SmoothBoxCar\n");
#endif
	double rStoreFirst;

	if (lngGroupSize>lngDataCount)
	{
		//Error("GroupSize cannot be Greater than number of points")
#ifdef _TESTDBG
		WriteMemoryLog("entered 11\n");
#endif
		return false;
	}
	//Return to the client ,if Group size is even number.
	if(lngGroupSize%2==0)
	{		
		//Error("GroupSize must be an odd number");		
#ifdef _TESTDBG
		WriteMemoryLog("entered 12\n");
#endif
		return false;
	}//End of if.

	long index	=	0;
	for(long i=0;i<lngSpectrumCount;i++)
	{
		for(long j=0;j<(lngDataCount/lngGroupSize);j++)
		{
			rStoreFirst=0;
			for(int k=(j*lngGroupSize);k<((j*lngGroupSize)+lngGroupSize);k++)
			{
				rStoreFirst=rStoreFirst+dblArrYdata[i][k];
			} //end of inner most for loop
			index	=	(j*lngGroupSize) +(lngGroupSize/2);	
			dblArrYdata[i][index]=rStoreFirst/lngGroupSize;
		
		}  //end of inner for loop
	}  //end of outer for loop
#ifdef _TESTDBG
	WriteMemoryLog("Exited SmoothBoxCar successfully\n");
#endif
	return true;

}

bool CFitAlgorithms::SmoothMovingBoxCar(double **dblArrYData, long lngSpectrumCount, long lngDataCount, long lngGroupSize)
{
#ifdef _TESTDBG
	WriteMemoryLog("Entered SmoothMovingBoxCar\n");
#endif
	if(lngGroupSize%2==0)
	{		
		//Error(_T("GroupSize must be an odd number"));		
#ifdef _TESTDBG
		WriteMemoryLog("entered 8\n");
#endif
		return false;
	}//End of if.

	if (lngGroupSize>lngDataCount)
	{
		//Error(_T("GroupSize cannot be Greater than number of points"));				
#ifdef _TESTDBG
		WriteMemoryLog("entered 9\n");
#endif
		return false;
	}

	for(long i=0;i<lngSpectrumCount;i++)
	{
		for(long j=0;j<(lngDataCount-lngGroupSize+1);j++)
		{
			for(long k=1;k<lngGroupSize;k++)
			{
				dblArrYData[i][j]	=	dblArrYData[i][j]+dblArrYData[i][j+k];
			}  //end of inner most for loop
			dblArrYData[i][j]	=	dblArrYData[i][j]/lngGroupSize;

		} //end of inner for loop
	}  //end of outer for loop 
#ifdef _TESTDBG
	WriteMemoryLog("Exited SmoothMovingBoxCar successfully\n");
#endif
	return true;
}
bool CFitAlgorithms::SmoothSavitzkyGolay(double ** dblArrYdata, long lngSpectrumCount, long lngDataCount, long lngGroupSize, long lngFilterOrder,long lngOrderOfDeri)
{
	//Return to the client ,if Group size is even number.

	if(lngGroupSize%2==0)
	{
		MessageBox(NULL,_T("GroupSize must be an odd number"),NULL,MB_OK);		
		return false;
	}//End of if.

	double rStoreFirst=0; //a temporary variable to store data 

	double *rCoeff	=	new double[lngGroupSize];
	for(long i=0;i<lngSpectrumCount;i++)
	{
		if(GetSavitzkyCoefficients(lngGroupSize,lngFilterOrder,lngOrderOfDeri,rCoeff)==false)
		{
			delete []rCoeff;
			return false;
		}
		for(int j=0;j<(lngDataCount-lngGroupSize+1);j++)
		{
			rStoreFirst	=0;
			for(int k=0;k<lngGroupSize;k++)
			{
				rStoreFirst=rStoreFirst+(rCoeff[k]*dblArrYdata[i][j+k]);
			} //end of most inner for loop

			dblArrYdata[i][j]=rStoreFirst;
		}  //end of inner for loop
	}//

	delete []rCoeff;
	return true;
}


// if   nOrderOfDeri	 =	0	---		Smoothing
//		nOrderOfDeri	 =	1	---		First order derivative
//		nOrderOfDeri	 =	2	---		Second order derivative
bool CFitAlgorithms::GetSavitzkyCoefficients(int nSmoothSize, int nFilterOrder,int nOrderOfDeri, double *dblCoefficients)
{
	//Find the values of Starting and ending points
	int nLeft = nSmoothSize/2;
	int nRight = nLeft;

	//Check for order 
	if (0 >= nFilterOrder )
	{
	//	strWarning.Format(_T("Order should be more than 0"));
	//	AfxMessageBox(strWarning);
		return false;
	} 
	if (nFilterOrder > (nLeft+nRight))
	{
	//	AfxMessageBox(_T("Order should be less than smooth size..."));
		return false;
	}

	//Create Double Array of size nLeft+nRight+1 x m_nOrder+1
	double ** dblA = new double*[nLeft+nRight+1];

	int i;
	for (i=0; i<nLeft+nRight+1; i++)
		dblA[i] = new double[nFilterOrder+1];

	for ( i=(-1*nLeft); i<=nRight; i++)
	{
		for (int j=0; j<nFilterOrder+1; j++)
		{
			dblA[i+nLeft][j] = pow((float)i,j);
		}
	}

	//////////////Find the transpose of A 
	double ** dblATran = new double*[nFilterOrder+1];
	for ( i=0; i<nFilterOrder+1; i++)
		dblATran[i] = new double[nLeft+nRight+1];

	for ( i=0; i<nFilterOrder+1; i++)
	{
		for (int j=0; j<nLeft+nRight+1; j++)
		{
			dblATran[i][j] = dblA[j][i];
		}
	}

	//////////////Perform multiplication of transpose of A and A [A*Transpose(A)
	double ** dblAMul = new double*[nFilterOrder+1];
	for ( i=0; i<nFilterOrder+1; i++)
		dblAMul[i] = new double[nFilterOrder+1];

	for ( i=0; i<nFilterOrder+1; i++)
	{
		for (int j=0; j<nFilterOrder+1; j++)
		{
			dblAMul[i][j] = 0;
			for (int k=0; k<nLeft+nRight+1; k++)
				dblAMul[i][j] += (dblATran[i][k] * dblA[k][j]); 
		}
	}

	//////////////Now Find the inverse of above matrix

	// Create a temporary 2D array
	double **dblArr = new double*[nFilterOrder+1]; 
	for( i=0; i<nFilterOrder+1; ++i)
		dblArr[i]=new double[nFilterOrder+1];

	//Copy the given input matrix to temporary matrix
	for ( i=0; i<nFilterOrder+1; i++)
	{
		for (int j=0; j<nFilterOrder+1; j++)
			dblArr[i][j] = dblAMul[i][j];
	}

	//Create matrix to hold the inverse matrix
	double **dblAInv = new double*[nFilterOrder+1]; 
	for( i=0; i<nFilterOrder+1; ++i)
		dblAInv[i]=new double[nFilterOrder+1];

	//Find the Inverse matrix
	for ( i=0; i<nFilterOrder+1; i++)
		for (int j=0; j<nFilterOrder+1; j++)
		{
			if (i==j)
				dblAInv[i][j] = 1;
			else
				dblAInv[i][j] = 0;
		}

		for ( i=0; i<nFilterOrder+1; i++)
		{
			//Make the diagonal element value unity
			double dblTemp1 = dblArr[i][i];
			for (int j=0; j<nFilterOrder+1; j++)
			{
				dblArr[i][j] /= dblTemp1;
				dblAInv[i][j] /= dblTemp1;
			}
			for (int k=0; k<nFilterOrder+1; k++)
			{
				if (k != i)
				{
					dblTemp1 = dblArr[k][i];
					for (int j=0; j<nFilterOrder+1; j++)
					{
						dblArr[k][j] = dblArr[k][j] - dblTemp1 * dblArr[i][j];
						dblAInv[k][j] = dblAInv[k][j] - dblTemp1 * dblAInv[i][j];
					}    
				}
			}
		}

		// Create H Matrix
		double ** dblH = new double*[nFilterOrder+1];
		for ( i=0; i<nFilterOrder+1; i++)
			dblH[i] = new double[1];

		for ( i=0; i<nFilterOrder+1; i++)
			dblH[i][0] = 0;

		dblH[nOrderOfDeri][0] = 1; 

		//Now perform multiplication of inverse matrix and H matrix
		double ** dblB = new double*[nFilterOrder+1];
		for ( i=0; i<nFilterOrder+1; i++)
			dblB[i] = new double[1];

		for ( i=0; i<nFilterOrder+1; i++)
		{
			for (int j=0; j<1; j++)
			{
				dblB[i][j] = 0;
				for (int k=0; k<nFilterOrder+1; k++)
					dblB[i][j] += (dblAInv[i][k] * dblH[k][j]); 
			}
		}

		//Create an array to hold the filter coefficients
		double ** dblC = new double*[nLeft+nRight+1];
		for ( i=0; i<nLeft+nRight+1; i++)
			dblC[i] = new double[1];

		double * dblNM = new double[nFilterOrder+1];
        int j;
		for ( i= (-1*nLeft); i<=nRight; i++)
		{

			for (j=0; j<nFilterOrder+1; j++)
				dblNM[j] = pow((float)i,j);
			dblC[i+nLeft][0] = 0;
			for (j=0; j<nFilterOrder+1; j++)
				dblC[i+nLeft][0] += (dblNM[j]*dblB[j][0]);
		}

		//Return the coefficients
		for ( i=0; i<nLeft+nRight+1; i++)
		{
			dblCoefficients[i] = dblC[i][0];
		}

		//Clean-up 
		for ( i=0; i<nLeft+nRight+1; i++)
			delete[] dblA[i];
		delete[] dblA;

		for ( i=0; i<nFilterOrder+1; i++)
			delete[] dblATran[i];
		delete[] dblATran;

		for ( i=0; i<nFilterOrder+1; i++)
			delete[] dblAMul[i];
		delete[] dblAMul;

		for( i=0; i<nFilterOrder+1; ++i)
			delete[] dblArr[i];
		delete[] dblArr;

		for( i=0; i<nFilterOrder+1; ++i)
			delete[] dblAInv[i];
		delete[] dblAInv;

		for ( i=0; i<nFilterOrder+1; i++)
			delete[] dblH[i];
		delete[] dblH;

		for ( i=0; i<nFilterOrder+1; i++)
			delete[] dblB[i];
		delete[] dblB;

		for ( i=0; i<nLeft+nRight+1; i++)
			delete[] dblC[i];
		delete[] dblC;

		delete[] dblNM;
		return true;
}

// Function Name: CFitAlgorithms::DerivateData
// Description  : Depending on the user selection corresponding functions will be called
// argument     : double **m_rArrYData
// argument     : int nSpectrums
// argument     : int nDataCount 
// argument     : int *m_nGroupSize
// argument     : int *nIndex

STDMETHODIMP CFitAlgorithms::DerivateData(LONG lngDerivativeType,VARIANT* varYData,int nDataCount,int nGroupSize,int intOrderOfDer,int intPolyDegree)
{
	long lngUBound,lngLBound, lngResultBound;


	SafeArrayGetLBound(varYData->parray,1,&lngLBound);
	SafeArrayGetUBound(varYData->parray,1,&lngUBound);
	lngResultBound	=	lngUBound	-	lngLBound;


	double *dblArrData	=	new double[lngResultBound+1];

	long lngCount	=	fncGetDoubleValuesFromSafeArray((*varYData),dblArrData);// uncomment '*'before dblArrData
	
	if(lngCount<nDataCount)
		nDataCount	=	lngCount;

     
	 if(lngDerivativeType==1)// if Point different method is selected
	 {
         if(DerivatePointDiff(dblArrData,nDataCount,nGroupSize,intOrderOfDer)==E_FAIL)
		 {
			 delete []dblArrData;
			 dblArrData = NULL;
			 return E_FAIL;
		 }
		
	 }
	 else if(lngDerivativeType==2) //if savitzky Golay differentiation method is selected
	 {
         if(SmoothDerivateSavitGolay(dblArrData,nDataCount,nGroupSize,intOrderOfDer,intPolyDegree)== E_FAIL)
		 {
#ifdef _TESTDBG
			 WriteMemoryLog("Derivative data function returns E_FAIL\n\n");
#endif
			 delete []dblArrData;
			 dblArrData = NULL;
			 return E_FAIL;
		 }
		 
	 }
	 SAFEARRAYBOUND sab[1]={0};
	 sab[0].cElements		=	nDataCount;
	 
	 
	 SAFEARRAY *pSa			=	SafeArrayCreate(VT_R8,1,sab);
	 
	 for(long j=0;j<nDataCount;j++)
		 SafeArrayPutElement(pSa,&j,&dblArrData[j]);
	 
	 (*varYData).parray		=	pSa;
	 
	 	 
	 delete []dblArrData;
	 dblArrData = NULL;

#ifdef _TESTDBG
	 WriteMemoryLog("Derivative data function returns S_OK\n\n");
#endif
	return S_OK;
}

// Function name	: CFitAlgorithms::DerivatePointDiff
// Description	    : Finds the differentiation of the array by point difference
//                    method.
// Return type		: void 

// Argument         : double *m_rArrYData
// Argument         : int nSpectrums
// Argument         : int nDataCount

BOOL CFitAlgorithms::DerivatePointDiff(double *m_rArrYData, int nDataCount,int nGroupSize,int nOrderOfDerivative)
{
    //Give an error if the order of derivative is less than one or if greater than
	// data count give an error and do nothing.
	if (nGroupSize>nDataCount)
	{
		TCHAR strBuffer[500];
	//	wvsprintf(strBuffer,_T("%s"),IDS_MAX_GROUPSIZE);		//string table
		Error(strBuffer,IID_IFitAlgorithms);		
		return E_FAIL;
	}

	if((nOrderOfDerivative<1)||(nOrderOfDerivative>=nDataCount))
	{
		TCHAR strBuffer[500];
	//	wvsprintf(strBuffer,_T("%s"),IDS_DERIVATIVE_LIMIT);//string table
		Error(strBuffer,IID_IFitAlgorithms);
		return E_FAIL;
	}
	else 
	{		
	//	int nDataCount1=nDataCount;
	//	nDataCount=nDataCount1;
		for(int j=0;j<nOrderOfDerivative;j++)
		{
			for(int k=0;k<nDataCount-1;k++)
			{
				m_rArrYData[k]=m_rArrYData[k+1]-m_rArrYData[k];
			} //end of inner most for loop
			nDataCount=nDataCount-1;
		}  //end of inner for loop

		return TRUE;	    
	}
}
// Function name	: CFitAlgorithms::SmoothDerivateSavitGolay
// Description	    :
// 
// Return type		: BOOL 
// Argument         : double **m_rArrYData
// Argument         : int nSpectrums
// Argument         : int nDataCount

BOOL CFitAlgorithms::SmoothDerivateSavitGolay(double *m_rArrYData,int nDataCount,int nGroupSize,int nOrderOfDerivative,int nPolynomialDegree)
{
#ifdef _TESTDBG
	WriteMemoryLog("entered SmoothDerivateSavitGolay\n");
#endif
   	TCHAR strBuffer[256];//For storing error message.
	int nArrRange[25];//To store the range like for 5 group size from -2 to +2

	double rCoeff[25];//To store savitGolay convolution factors, we get 
					  //them from the function GetNormalizedCoeff
	double rStoreFirst=0; //a temporary variable to store data 

	if (nGroupSize>nDataCount)
	{
//		wvsprintf(strBuffer,_T("%s"),IDS_MAX_GROUPSIZE);		//string table
#ifdef _TESTDBG
		WriteMemoryLog("entered 1\n");
#endif	
		Error(strBuffer,IID_IFitAlgorithms);		
		return E_FAIL;
	}

	if(nDataCount<nGroupSize)
	{		
//		wvsprintf(strBuffer,_T("%s"),IDS_MIN_GROUPSIZE);//string table		
#ifdef _TESTDBG
		WriteMemoryLog("entered 2\n");
#endif
		Error(strBuffer,IID_IFitAlgorithms);
		return E_FAIL;
	}//end of if statement.


	//Return to the client if group size  is greater than 25 or group size is less than 0 	
	if((nGroupSize>25)||(nGroupSize<5))
	{
//		wvsprintf(strBuffer,_T("%d:"),_T("%s"),IDS_GROUPSIZE_LIMIT,nGroupSize);        //string table
#ifdef _TESTDBG
		WriteMemoryLog("entered 3\n");
#endif
		Error(strBuffer,IID_IFitAlgorithms);
		return E_FAIL;
	}//end of if statement.


	//Return to the client if Order of derivative is greater than 5.	
	if((nOrderOfDerivative>5)||(nOrderOfDerivative<0))
	{
//		wvsprintf(strBuffer,_T("%d"),_T("%s"),IDS_DERIVATIVE_ORDER_LIMIT,nOrderOfDerivative);		//string table
#ifdef _TESTDBG
		WriteMemoryLog("entered 4\n");
#endif
		Error(strBuffer,IID_IFitAlgorithms);
		return E_FAIL;
	}//end of if statement.



	//Return to the client ,if Group size is even number.	
	if(nGroupSize%2==0)
	{
//		wvsprintf(strBuffer,_T("GroupSize must be an odd number"));	
#ifdef _TESTDBG
		WriteMemoryLog("entered 5\n");
#endif
		Error(strBuffer,IID_IFitAlgorithms);
		return E_FAIL;

	}//End of if.

	if(((nPolynomialDegree>=5)&&(nGroupSize<7)) && (nOrderOfDerivative!=4))
	{
//		wvsprintf(strBuffer,_T("%s"),IDS_POLY_GROUP_SIZE,nPolynomialDegree);		//string table
#ifdef _TESTDBG
		WriteMemoryLog("entered 6\n");
#endif
		Error(strBuffer,IID_IFitAlgorithms);
		return E_FAIL;
	}//End of if.
 
#ifdef _TESTDBG
	WriteMemoryLog("B4 Getabscissapoint\n");
#endif
	GetAbscissaPoints(nGroupSize,nArrRange);
#ifdef _TESTDBG
	WriteMemoryLog("after Getabscissapoint\n");
#endif
	//Check whether coefficients exist or not .
	if(GetNormalizedCoeff(nGroupSize,nArrRange,rCoeff,nOrderOfDerivative,nPolynomialDegree)==-1)
	{
		int ime=0;
#ifdef _TESTDBG
		WriteMemoryLog("entered 7\n");
#endif
//		wvsprintf(strBuffer,_T("%s"),IDS_SMOOTHING_ORDER_DEG_ERR,nOrderOfDerivative,nPolynomialDegree);		//string table
		Error(strBuffer,IID_IFitAlgorithms);
		return E_FAIL;
	}//end of inner if statement.
	
	/*	We can test the rCoeff, normalized factors 
		by two theorems, those are given in 
		Reference : Analytical Chem Vol. 50, page no 1383
		The summation of (rCoeff[i]*pow(nArrRange[i],nOrderOfDerivative))
		should be equal to factorial of order of derivative.
		Here  the summation of rCoeff[i] is equal to zero
		except for order of derivative is zero
		we can verify them by the following loop.
	
		Here we prooved the first theorem ,we can proove the second theorem
		by removing the pow function.
		
	for(int i=0;i<nGroupSize;i++)
	{
		rStoreFirst+=rCoeff[i]*pow(nArrRange[i],nOrderOfDerivative);
	}
	
	sprintf(strBuffer,"%f",rStoreFirst);
	Error(strBuffer,IID_ISpSmooth);
	return E_FAIL;
	*/
	
/*
	FILE* fp = fopen("C:\\Golay.txt","w");
	for (int mn=0; mn<nGroupSize; mn++)
		fprintf(fp,"%lf\n",rCoeff[mn]);
	fclose(fp);*/
	for(int j=0;j<(nDataCount-nGroupSize+1);j++)
	{
		rStoreFirst	=0;
		for(int k=0;k<nGroupSize;k++)
		{
			rStoreFirst=rStoreFirst+(rCoeff[k]*m_rArrYData[j+k]);			
		} //end of inner most for loop
		m_rArrYData[j]=rStoreFirst;
	
	}  //end of inner for loop
#ifdef _TESTDBG
	WriteMemoryLog("Exited SmoothDerivateSavitGolay successfully\n");
#endif
    return TRUE;
}
// Function name	: CFitAlgorithms::GetNormalizedCoeff
// Description	    : Gives the convolution integers after the 
//                    applying normalization factor.
// Return type		: int 
// Argument         : int nGroupSize
// Argument         : int nArrRange[]
// Argument         : double rCoeff[]
// Argument         : int nOrderOfDerivative
// Argument         : int nPolynomialDegree

int CFitAlgorithms::GetNormalizedCoeff(int nGroupSize, int nArrRange[], double rCoeff[], int nOrderDer, int nPolyDegree)
{
#ifdef _TESTDBG
	WriteMemoryLog("Entered GetNormalizedCoeff\n");
#endif
    double	rMid=nGroupSize/2;
    int		i=0;

	switch(nOrderDer)
	{
	case 0:

			switch(nPolyDegree)
			{

			case 2:case 3:
	
					for( i=0;i<nGroupSize;i++)
					{
						rCoeff[i]=(3*(3*pow(rMid,2)+3*rMid-1-5*pow(nArrRange[i],2)))/((2*rMid+3)*(2*rMid+1)*(2*rMid-1));
					}//for loop ends
					break;
			case 4:case 5:

					for(i=0;i<nGroupSize;i++)
					{
						rCoeff[i]=(15.0/4.0)*((15*pow(rMid,4)+30*pow(rMid,3)-35*pow(rMid,2)-50*rMid+12)-35*(2*pow(rMid,2)+2*rMid-3)*pow(nArrRange[i],2)+63*pow(nArrRange[i],4))/((2*rMid+5)*(2*rMid+3)*(2*rMid+1)*(2*rMid-1)*(2*rMid-3));
					}//for loop ends
					break;
			default:
				return -1;
				
			}//inner switch ends

			break;
	case 1:

			switch(nPolyDegree)
			{
			case 2:
					for(i=0;i<nGroupSize;i++)
					{
						rCoeff[i]=(3*nArrRange[i])/((2*rMid+1)*(rMid+1)*(rMid));
					}
					break;
			case 3:case 4:
					for(i=0;i<nGroupSize;i++)
					{
                                                                                                                                   
						rCoeff[i]=5*(5*(3*pow(rMid,4)+6*pow(rMid,3)-3*rMid+1)*nArrRange[i]-7*(3*pow(rMid,2)+3*rMid-1)*pow(nArrRange[i],3))/((2*rMid+3)*(2*rMid+1)*(2*rMid-1)*(rMid+2)*(rMid+1)*(rMid)*(rMid-1));
					}
					break;
			case 5:case 6:
					for(i=0;i<nGroupSize;i++)
					{
		      			rCoeff[i]=(21.0/4.0)*(7*(25*pow(rMid,8)+100*pow(rMid,7)-50*pow(rMid,6)-500*pow(rMid,5)-95*pow(rMid,4)+760*pow(rMid,3)+180*pow(rMid,2)-300*rMid+72)*nArrRange[i]  \
									-105*(6*pow(rMid,6)+18*pow(rMid,5)-15*pow(rMid,4)-60*pow(rMid,3)+17*pow(rMid,2)+50*rMid-12)*pow(nArrRange[i],3) \
									+33*(15*pow(rMid,4)+30*pow(rMid,3)-35*pow(rMid,2)-50*rMid+12)*pow(nArrRange[i],5))/  \
									((2*rMid+5)*(2*rMid+3)*(2*rMid+1)*(2*rMid-1)*(2*rMid-3)*(rMid+3)*(rMid+2)*(rMid+1)*(rMid)*(rMid-1)*(rMid-2));
					}
					break;
			default:
				return -1;
			}//inner switch ends
			break;
	case 2:

			switch(nPolyDegree)
			{
			case 2:case 3:
					for(i=0;i<nGroupSize;i++)
					{
						rCoeff[i]=30*(3*pow(nArrRange[i],2)-rMid*(rMid+1))/((2*rMid+3)*(2*rMid+1)*(2*rMid-1)*(rMid+1)*rMid);
					}
				break;
			case 4:case 5:
					for(i=0;i<nGroupSize;i++)
					{
						rCoeff[i]=(-105.0/2.0)*(15*(6*pow(rMid,2)+6*rMid-5)*pow(nArrRange[i],4)-21*(4*pow(rMid,4)+8*pow(rMid,3)-4*pow(rMid,2)-8*rMid+5)*pow(nArrRange[i],2)+5*rMid*(2*pow(rMid,5)+6*pow(rMid,4)-pow(rMid,3)-12*pow(rMid,2)-rMid+6))/  
									((2*rMid+5)*(2*rMid+3)*(2*rMid+1)*(2*rMid-1)*(2*rMid-3)*(rMid+2)*(rMid+1)*(rMid)*(rMid-1));
				
					}
				break;
			default:
				return -1;
			}//inner switch ends
			break;
	case 3:
			switch(nPolyDegree)
			{
			case 3:case 4:
					for(i=0;i<nGroupSize;i++)
					{
						rCoeff[i]=210*(5*pow(nArrRange[i],3)-(3*pow(rMid,2)+3*rMid-1)*nArrRange[i])/((2*rMid+3)*(2*rMid+1)*(2*rMid-1)*(rMid+2)*(rMid+1)*rMid*(rMid-1));
					}
				break;

			case 5:case 6:
					for(i=0;i<nGroupSize;i++)
					{	
						//	The  formula below proved to be wrong , by the use of 
						//  formualae given in 
						// Reference : Analytical Chem Vol. 50, page no 1383
						// Here in the above method , the formaula checking is given
						// after calling the GetNormalizedCoeff function.
						/*rCoeff[i]=(-945.0/2.0)*(7*(6*pow(rMid,6)+18*pow(rMid,5)-15*pow(rMid,4)-60*pow(rMid,3)+17*pow(rMid,2)-50*rMid-12)*nArrRange[i] \
								-15*(12*pow(rMid,4)+24*pow(rMid,3)-28*pow(rMid,2)-40*rMid+39)*pow(nArrRange[i],3)+77*(2*pow(rMid,2)+2*rMid-3)*pow(nArrRange[i],5))/ \
								((2*rMid+5)*(2*rMid+3)*(2*rMid+1)*(2*rMid-1)*(2*rMid-3)*(rMid+3)*(rMid+2)*(rMid+1)*rMid*(rMid-1)*(rMid-2));*/

						// For  this polynomial  we are using , tables given in
						// Reference : Analytical Chem Vol. 44, page no 1908

						For3rdDer5thPolynomial(rCoeff,nGroupSize);

					}
					
				break;
			default:
				return -1;
			}//inner switch ends
			break;
			
	case 4:
			switch(nPolyDegree)
			{
			case 4:case 5:
					for(i=0;i<nGroupSize;i++)
					{
						rCoeff[i]=(1890)*(3*rMid*(pow(rMid,3)+2*pow(rMid,2)-rMid-2)-5*(6*pow(rMid,2)+6*rMid-5)*pow(nArrRange[i],2)+35*pow(nArrRange[i],4))/ \
							((2*rMid+5)*(2*rMid+3)*(2*rMid+1)*(2*rMid-1)*(2*rMid-3)*(rMid+2)*(rMid+1)*rMid*(rMid-1));
					}

				break;
			default:
				return -1;
			}//inner switch ends
			break;
		case 5:
			switch(nPolyDegree)
			{
			case 5:case 6:
					for(i=0;i<nGroupSize;i++)
					{
						rCoeff[i]=(20790)*((15*pow(rMid,4)+30*pow(rMid,3)-35*pow(rMid,2)-50*rMid+12)*nArrRange[i]-35*(2*pow(rMid,2)+2*rMid-3)*pow(nArrRange[i],3)+63*pow(nArrRange[i],5))/ 
									((2*rMid+5)*(2*rMid+3)*(2*rMid+1)*(2*rMid-1)*(2*rMid-3)*(rMid+3)*(rMid+2)*(rMid+1)*rMid*(rMid-1)*(rMid-2));
					}
					
			break;
			default:
				return -1;
			}//inner switch ends
			break;
	default:
		return -1;

	}//outer switch ends

#ifdef _TESTDBG
	WriteMemoryLog("Exited GetNormalizedCoeff successfully\n");
#endif
	return 1; 


}

void CFitAlgorithms::GetAbscissaPoints(int nGroupSize, int nArrRange[])
{
    //To get the offset in the global array , to store into the array nArrRange
	int nMid=(MAX_GROUPSIZE/2)-(nGroupSize/2);
	int i=0;
	for( i=0;i<nGroupSize;i++)
	{
		nArrRange[i]=gArrGroup[nMid+i];//globalarray which stores upto MAX_GROUPSIZE
	
	}//End of first for loop
	
	for(i=nGroupSize;i<25;i++)
	{
		nArrRange[i]=0;
	}//End of second for loop
}

void CFitAlgorithms::For3rdDer5thPolynomial(double rCoeff[], int nGroupSize)
{
     switch(nGroupSize)
	 {
	 case 7:
		{
		double rNorm = 8;		//Normalisatioin factor for this groupsize

		// As we can not assign directly to rCoeff each number , we are storing 
		// them in a temporary array, and after that assigning them to 
		// original array using a loop.

		double rArrStoreCoeff[7] =	{		1/rNorm,	-8/rNorm,	13/rNorm,
											0/rNorm,	-13/rNorm,	8/rNorm,
											-1/rNorm
									};

		for(int i=0;i<7;i++)
		{
			rCoeff[i]=rArrStoreCoeff[i];
		}

		}
		break;

	case 9:
		{
		double rNorm = 1144;	//Normalisatioin factor for this groupsize

		// As we can not assign directly to rCoeff each number , we are storing 
		// them in a temporary array, and after that assigning them to 
		// original array using a loop.

		double rArrStoreCoeff[9] =	{		100/rNorm,-457/rNorm,256/rNorm,
											459/rNorm,0/rNorm,-459/rNorm,
											-256/rNorm,457/rNorm,-100/rNorm
									};

		for(int i=0;i<9;i++)
		{
			rCoeff[i]=rArrStoreCoeff[i];
		}
		
		}
		break;

	case 11:
		{
			double rNorm = 2288;	//Normalisatioin factor for this groupsize
			
			// As we can not assign directly to rCoeff each number , we are storing 
			// them in a temporary array, and after that assigning them to 
			// original array using a loop.
			
			double rArrStoreCoeff[11] =	{		129/rNorm,-402/rNorm,-11/rNorm,340/rNorm,
				316/rNorm,0/rNorm,-316/rNorm,-340/rNorm,
				11/rNorm,402/rNorm,	-129/rNorm
			};
			
			for(int i=0;i<11;i++)
			{
				rCoeff[i]=rArrStoreCoeff[i];
			}
			
		}
		break;

	case 13:
		{
		double rNorm = 38896;	//Normalisatioin factor for this groupsize

		// As we can not assign directly to rCoeff each number , we are storing 
		// them in a temporary array, and after that assigning them to 
		// original array using a loop.

		double rArrStoreCoeff[13] =	{		1430/rNorm,		-3267/rNorm,	-1374/rNorm,
											1633/rNorm,		3050/rNorm,		2252/rNorm,
											0,				-2252/rNorm,	-3050/rNorm,
											-1633/rNorm,	1374/rNorm,		3267/rNorm,	
											-1430/rNorm

									};

		for(int i=0;i<13;i++)
		{
			rCoeff[i]=rArrStoreCoeff[i];
		}

		}
		break;

	case 15:
		{

		double rNorm = 335920;	//Normalisatioin factor for this groupsize

		// As we can not assign directly to rCoeff each number , we are storing 
		// them in a temporary array, and after that assigning them to 
		// original array using a loop.


		double rArrStoreCoeff[15] =	{		8281/rNorm,		-14404/rNorm,	-10379/rNorm,
											1916/rNorm,		11671/rNorm,	14180/rNorm,
											9315/rNorm,		0/rNorm,		-9315/rNorm,
											-14180/rNorm,	-11671/rNorm,	-1916/rNorm,
											10379/rNorm,	14404/rNorm,	-8281/rNorm
									};

		for(int i=0;i<15;i++)
		{
			rCoeff[i]=rArrStoreCoeff[i];
		}

		}

		break;

	case 17:
		{
			
			double rNorm =	67184;	//Normalisatioin factor for this groupsize
			
			// As we can not assign directly to rCoeff each number , we are storing 
			// them in a temporary array, and after that assigning them to 
			// original array using a loop.
			
			double rArrStoreCoeff[17] =	{		1144/rNorm,		-1547/rNorm,	-1508/rNorm,
				-351/rNorm,		876/rNorm,		1595/rNorm,
				1604/rNorm,		983/rNorm,		0/rNorm,
				-983/rNorm,		-1604/rNorm,	-1595/rNorm,
				-876/rNorm,		351/rNorm,		1508/rNorm,
				1547/rNorm,		-1144/rNorm
			};
			
			for(int i=0;i<17;i++)
			{
				rCoeff[i]=rArrStoreCoeff[i];
			}
			
		}

		break;

	case 19:
		{
		double rNorm = 1307504;	//Normalisatioin factor for this groupsize

		// As we can not assign directly to rCoeff each number , we are storing 
		// them in a temporary array, and after that assigning them to 
		// original array using a loop.

		double rArrStoreCoeff[19] =	{		15810/rNorm,	-16796/rNorm,	-20342/rNorm,
											-9818/rNorm,	4329/rNorm,		15546/rNorm,
											20525/rNorm,	18554/rNorm,	10868/rNorm,
											0/rNorm,		-10868/rNorm,	-18554/rNorm,
											-20525/rNorm,	-15546/rNorm,	-4329/rNorm,
											9818/rNorm,		20342/rNorm,	16796/rNorm,
											-15810/rNorm
									};
		
		for(int i=0;i<19;i++)
		{
			rCoeff[i]=rArrStoreCoeff[i];
		}

		}

		break;

	case 21:
		{

		double rNorm =	84987760;	//Normalisatioin factor for this groupsize

		// As we can not assign directly to rCoeff each number , we are storing 
		// them in a temporary array, and after that assigning them to 
		// original array using a loop.

		double rArrStoreCoeff[21] =	{		748068/rNorm,	-625974/rNorm,	-908004/rNorm,
											-598094/rNorm,	-62644/rNorm,	448909/rNorm,
											787382/rNorm,	887137/rNorm,	749372/rNorm,
											425412/rNorm,	0/rNorm,		-425412/rNorm,		
											-749372/rNorm,	-887137/rNorm,	-787382/rNorm,
											-448909/rNorm,	62644/rNorm,	598094/rNorm,
											908004/rNorm,	625974/rNorm,	-748068/rNorm
									};
		for(int i=0;i<21;i++)
		{
			rCoeff[i]=rArrStoreCoeff[i];
		}

		}

		break;

	case 23:
		{

		double rNorm =7498920;	//Normalisatioin factor for this groupsize

		// As we can not assign directly to rCoeff each number , we are storing 
		// them in a temporary array, and after that assigning them to 
		// original array using a loop.

		double rArrStoreCoeff[23] =	{		49115/rNorm,	-32224/rNorm,	-55233/rNorm,
											-43928/rNorm,	-16583/rNorm,	13632/rNorm,
											38013/rNorm,	51684/rNorm,	52959/rNorm,
											42704/rNorm,	23699/rNorm,	0/rNorm,
											-23699/rNorm,	-42704/rNorm,	-52959/rNorm,
											-51684/rNorm,	-38013/rNorm,	-13632/rNorm,
											16583/rNorm,	43928/rNorm,	55233/rNorm,
											32224/rNorm,	-49115/rNorm
									};
		for(int i=0;i<23;i++)
		{
			rCoeff[i]=rArrStoreCoeff[i];
		}

		}

		break;

	case 25:
		{

		double rNorm = 57228600;	//Normalisatioin factor for this groupsize

		// As we can not assign directly to rCoeff each number , we are storing 
		// them in a temporary array, and after that assigning them to 
		// original array using a loop.
		
		double rArrStoreCoeff[25] =	{		284372/rNorm,	-144463/rNorm,	-293128/rNorm,
											-266403/rNorm,	-146408/rNorm,	5131/rNorm,
											144616/rNorm,	244311/rNorm,	290076/rNorm,
											279101/rNorm,	217640/rNorm,	118745/rNorm,
											0/rNorm,		-118745/rNorm,	-217640/rNorm,
											-279101/rNorm,	-290076/rNorm,	-244311/rNorm,
											-144616/rNorm,	-5131/rNorm,	146408/rNorm,
											266403/rNorm,	293128/rNorm,	144463/rNorm,	
											-284372/rNorm
									};
		for(int i=0;i<25;i++)
		{
			rCoeff[i]=rArrStoreCoeff[i];
		}

		}

		break;

	default:

		;
				
	}
}