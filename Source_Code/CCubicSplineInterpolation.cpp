#include "stdafx.h"
#include <math.h>
#include "CubicSplineInterpolation.h"


CCubicSplineInterpolation::CCubicSplineInterpolation()
{

}
CCubicSplineInterpolation::~CCubicSplineInterpolation()
{

}

void CCubicSplineInterpolation::fncFindCubicPloynomial(int Datacount,double *XArr,double *YArr,double &A0,double &A1,double &A2,double &constant)
{
	double dblSum_X=0.0,dblSum_Y=0.0,dblSum_XY=0.0,dblSum_X2=0.0,dblSum_X3=0.0,dblSum_X4=0.0,dblSum_X5=0.0,dblSum_X6=0.0,dblSum_X2Y=0.0,dblSum_X3Y=0.0;

	double dblAArr[4][4];
	double dblInvMatrix[4][4];
	double dblBArr[4];
	double dblCArr[4];


	for (int i=0;i<Datacount;i++)
	{
		dblSum_X=dblSum_X+XArr[i];
		dblSum_Y=dblSum_Y+YArr[i];

		dblSum_X2=dblSum_X2+(XArr[i]*XArr[i]);
		dblSum_X3=dblSum_X3+(XArr[i]*XArr[i]*XArr[i]);
		dblSum_X4=dblSum_X4+(XArr[i]*XArr[i]*XArr[i]*XArr[i]);
		dblSum_X5=dblSum_X5+(XArr[i]*XArr[i]*XArr[i]*XArr[i]*XArr[i]);
		dblSum_X6=dblSum_X6+(XArr[i]*XArr[i]*XArr[i]*XArr[i]*XArr[i]*XArr[i]);

		dblSum_XY=dblSum_XY+(XArr[i]*YArr[i]);
		dblSum_X2Y=dblSum_X2Y+(XArr[i]*XArr[i]*YArr[i]);
		dblSum_X3Y=dblSum_X3Y+(XArr[i]*XArr[i]*XArr[i]*YArr[i]);
	}

	dblAArr[0][0] = dblSum_X3; dblAArr[0][1] = dblSum_X2; dblAArr[0][2] = dblSum_X;  dblAArr[0][3] = Datacount;
	dblAArr[1][0] = dblSum_X4; dblAArr[1][1] = dblSum_X3; dblAArr[1][2] = dblSum_X2; dblAArr[1][3] = dblSum_X;
	dblAArr[2][0] = dblSum_X5; dblAArr[2][1] = dblSum_X4; dblAArr[2][2] = dblSum_X3; dblAArr[2][3] = dblSum_X2;
	dblAArr[3][0] = dblSum_X6; dblAArr[3][1] = dblSum_X5; dblAArr[3][2] =dblSum_X4; dblAArr[3][3] = dblSum_X3;

	MatrixInversion(dblAArr,4,dblInvMatrix);

	dblBArr[0] = dblSum_Y;
	dblBArr[1] = dblSum_XY;
	dblBArr[2] = dblSum_X2Y;
	dblBArr[3] = dblSum_X3Y;

	dblCArr[0]=dblInvMatrix[0][0]*dblBArr[0]+dblInvMatrix[0][1]*dblBArr[1]+dblInvMatrix[0][2]*dblBArr[2]+dblInvMatrix[0][3]*dblBArr[3];
	dblCArr[1]=dblInvMatrix[1][0]*dblBArr[0]+dblInvMatrix[1][1]*dblBArr[1]+dblInvMatrix[1][2]*dblBArr[2]+dblInvMatrix[1][3]*dblBArr[3];
	dblCArr[2]=dblInvMatrix[2][0]*dblBArr[0]+dblInvMatrix[2][1]*dblBArr[1]+dblInvMatrix[2][2]*dblBArr[2]+dblInvMatrix[2][3]*dblBArr[3];
	dblCArr[3]=dblInvMatrix[3][0]*dblBArr[0]+dblInvMatrix[3][1]*dblBArr[1]+dblInvMatrix[3][2]*dblBArr[2]+dblInvMatrix[3][3]*dblBArr[3];

	A0=dblCArr[0];
	A1=dblCArr[1];
	A2=dblCArr[2];
	constant=dblCArr[3];
}

// matrix inversioon

// the result is put in Y

void CCubicSplineInterpolation::MatrixInversion(double A[][4], int order, double Y[][4])
{
	/// get the determinant of a
	double det = 1.0/CalcDeterminant(A,order);

	/// memory allocation
	double *temp = new double[(order-1)*(order-1)];

	double minor[4][4];// = new double*[order-1];

	for(int j=0;j<order;j++)
	{
		for(int i=0;i<order;i++)
		{
			/// get the co-factor (matrix) of A(j,i)
			GetMinor(A,minor,j,i,order);

			Y[i][j] = det*CalcDeterminant(minor,order-1);

			if( (i+j)%2 == 1)
			{
				Y[i][j] = -Y[i][j];
			}
		}
	}
	if(temp!=NULL)
		delete []temp;
	temp=NULL;
}

/// calculate the cofactor of element (row,col)

int CCubicSplineInterpolation::GetMinor(double src[][4], double dest[][4], int row, int col, int order)
{
	/// indicate which col and row is being copied to dest
	int colCount=0,rowCount=0;

	for(int i = 0; i < order; i++ )
	{
		if( i != row )
		{
			colCount = 0;
			for(int j = 0; j < order; j++ )
			{
				/// when j is not the element
				if( j != col )
				{
					dest[rowCount][colCount] = src[i][j];
					colCount++;
				}
			}
			rowCount++;
		}
	}
	return 1;
}

/// Calculate the determinant recursively.

double CCubicSplineInterpolation::CalcDeterminant( double mat[][4], int order)
{
	/// order must be >= 0
	/// stop the recursion when matrix is a single element
	if( order == 1 )
		return mat[0][0];

	/// the determinant value
	double det = 0;

	/// allocate the cofactor matrix
	double minor[4][4];

	for(int i = 0; i < order; i++ )
	{
		/// get minor of element (0,i)
		GetMinor( mat, minor, 0, i , order);

		/// the recusion is here!
		det += pow( -1.0, (double)i ) * mat[0][i] * CalcDeterminant( minor,order-1 );
	}
	return det;
}

void CCubicSplineInterpolation::FindQuadraticFitCoefficients(LONG lngDataCount, double dblXVals[], double dblYVals[], double *dblA0, double *dblA1, double *dblA2, BOOL *pVal)
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
	
	
	

	double *dblArrX	=dblXVals;
	

	double *dblArrY	=dblYVals;

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
	
	*pVal = TRUE;
	
	
}



