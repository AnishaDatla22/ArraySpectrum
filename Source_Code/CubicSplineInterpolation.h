class CCubicSplineInterpolation
{
public:
	CCubicSplineInterpolation();
	~CCubicSplineInterpolation();
	void fncFindCubicPloynomial(int Datacount,double *XArr,double *YArr,double &A0,double &A1,double &A2,double &constant);
private:
	double CalcDeterminant( double mat[][4], int order);
	int GetMinor(double src[][4], double dest[][4], int row, int col, int order);
	void MatrixInversion(double A[][4], int order, double Y[][4]);
public:
	void FindQuadraticFitCoefficients(LONG lngDataCount, double dblXVals[], double dblYVals[], double *dblA0, double *dblA1, double *dblA2, BOOL *pVal);
};