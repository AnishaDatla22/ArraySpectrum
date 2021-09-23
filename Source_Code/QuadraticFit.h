#pragma once


class CQuadraticFit
{
	/* instance variables */
	CArray<double*,double*> pointArray;

	int numOfEntries; 
	double * pointpair;          



	/*instance methods */
public:
   CQuadraticFit();
   CQuadraticFit:: ~CQuadraticFit();

	/// <summary>
	/// add point pairs
	/// </summary>
	/// <param name="x">x value</param>
	/// <param name="y">y value</param>
	void AddPoints(double x, double y);


	/// <summary>
	/// returns the a term of the equation ax^2 + bx + c
	/// </summary>
	/// <returns>a term</returns>
	double aTerm();

	/// <summary>
	/// returns the b term of the equation ax^2 + bx + c
	/// </summary>
	/// <returns>b term</returns>
	double bTerm();


	/// <summary>
	/// returns the c term of the equation ax^2 + bx + c
	/// </summary>
	/// <returns>c term</returns>
	double cTerm();

	double rSquare(); // get r-squared

	/*helper methods*/

private:
	double getSx(); // get sum of x


	double getSy(); // get sum of y

	double getSx2(); // get sum of x^2


	double getSx3(); // get sum of x^3


	double getSx4(); // get sum of x^4


	double getSxy(); // get sum of x*y


	double getSx2y(); // get sum of x^2*y


	double getYMean(); // mean value of y


	double getSStot(); // total sum of squares


	double getSSerr(); // residual sum of squares

	double getPredictedY(double x);

};
