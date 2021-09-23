/********************************************************************************************
                               
             A C++  Class for Least Squares Regression for Quadratic Curve Fitting
                                    
 ********************************************************************************************/
#include <stdafx.h>
#include"quadraticfit.h"
#include <stdlib.h>
#include <math.H>


  
CQuadraticFit:: CQuadraticFit()
    {
        numOfEntries = 0;
        pointpair = new double[2];
    }

CQuadraticFit:: ~CQuadraticFit()
    {
      
		for(int i=0;i<pointArray.GetCount();i++)
		{
		   double * p=pointArray[i];
           delete [] p;
		}
    }



    /*instance methods */
    
    
    /// <summary>
    /// add point pairs
    /// </summary>
    /// <param name="x">x value</param>
    /// <param name="y">y value</param>
void CQuadraticFit:: AddPoints(double x, double y) 
    {
        pointpair = new double[2]; 
        numOfEntries +=1; 
        pointpair[0] = x; 
        pointpair[1] = y;
        pointArray.Add(pointpair);
    }

    /// <summary>
    /// returns the a term of the equation ax^2 + bx + c
    /// </summary>
    /// <returns>a term</returns>
  double CQuadraticFit::aTerm()
    {
       /* if (numOfEntries < 3)
        {
            throw new InvalidOperationException("Insufficient pairs of co-ordinates");
        }*/
        //notation sjk to mean the sum of x_i^j*y_i^k. 
        double s40 = getSx4(); //sum of x^4
        double s30 = getSx3(); //sum of x^3
        double s20 = getSx2(); //sum of x^2
        double s10 = getSx();  //sum of x
        double s00 = numOfEntries;  //sum of x^0 * y^0  ie 1 * number of entries

        double s21 = getSx2y(); //sum of x^2*y
        double s11 = getSxy();  //sum of x*y
        double s01 = getSy();   //sum of y

        //a = Da/D
        return (s21*(s20 * s00 - s10 * s10) - s11*(s30 * s00 - s10 * s20) + s01*(s30 * s10 - s20 * s20))
                /
                (s40*(s20 * s00 - s10 * s10) - s30*(s30 * s00 - s10 * s20) + s20*(s30 * s10 - s20 * s20));
    }

    /// <summary>
    /// returns the b term of the equation ax^2 + bx + c
    /// </summary>
    /// <returns>b term</returns>
 double CQuadraticFit::bTerm()
    {
        /*if (numOfEntries < 3)
        {
            throw new InvalidOperationException("Insufficient pairs of co-ordinates");
        }*/
        //notation sjk to mean the sum of x_i^j*y_i^k.  
        double s40 = getSx4(); //sum of x^4
        double s30 = getSx3(); //sum of x^3
        double s20 = getSx2(); //sum of x^2
        double s10 = getSx();  //sum of x
        double s00 = numOfEntries;  //sum of x^0 * y^0  ie 1 * number of entries

        double s21 = getSx2y(); //sum of x^2*y
        double s11 = getSxy();  //sum of x*y
        double s01 = getSy();   //sum of y

        //b = Db/D
        return (s40*(s11 * s00 - s01 * s10) - s30*(s21 * s00 - s01 * s20) + s20*(s21 * s10 - s11 * s20))
                /
                (s40 * (s20 * s00 - s10 * s10) - s30 * (s30 * s00 - s10 * s20) + s20 * (s30 * s10 - s20 * s20));
    }

    /// <summary>
    /// returns the c term of the equation ax^2 + bx + c
    /// </summary>
    /// <returns>c term</returns>
    double CQuadraticFit::cTerm()
    {
        /*if (numOfEntries < 3)
        {
            throw new InvalidOperationException("Insufficient pairs of co-ordinates");
        }*/
        //notation sjk to mean the sum of x_i^j*y_i^k.  
        double s40 = getSx4(); //sum of x^4
        double s30 = getSx3(); //sum of x^3
        double s20 = getSx2(); //sum of x^2
        double s10 = getSx();  //sum of x
        double s00 = numOfEntries;  //sum of x^0 * y^0  ie 1 * number of entries

        double s21 = getSx2y(); //sum of x^2*y
        double s11 = getSxy();  //sum of x*y
        double s01 = getSy();   //sum of y

        //c = Dc/D
        return (s40*(s20 * s01 - s10 * s11) - s30*(s30 * s01 - s10 * s21) + s20*(s30 * s11 - s20 * s21))
                /
                (s40 * (s20 * s00 - s10 * s10) - s30 * (s30 * s00 - s10 * s20) + s20 * (s30 * s10 - s20 * s20));
    }
    
 double  CQuadraticFit::rSquare() // get r-squared
    {
       /* if (numOfEntries < 3)
        {
            throw new InvalidOperationException("Insufficient pairs of co-ordinates");
        }*/
        // 1 - (total sum of squares / residual sum of squares)
        return 1 - getSSerr() / getSStot();
    }
   

    /*helper methods*/
double CQuadraticFit:: getSx() // get sum of x
    {
        double Sx = 0;
        for (int i=0;i<pointArray.GetCount();i++)
        {
            Sx += *(pointArray[i]);
        }
        return Sx;
    }

double CQuadraticFit:: getSy() // get sum of y
    {
        double Sy = 0;
        for(int i=0;i<pointArray.GetCount();i++)
        {
            Sy += *(pointArray[i]+1);
        }
        return Sy;
    }

double CQuadraticFit::getSx2() // get sum of x^2
    {
        double Sx2 = 0;
		double d;
        for (int i=0;i<pointArray.GetCount();i++)
        {
			d=*(pointArray[i]);
            Sx2 += pow(d, 2); // sum of x^2
        }
        return Sx2;
    }

double CQuadraticFit::getSx3() // get sum of x^3
    {
        double Sx3 = 0;
		double d;
        for (int i=0;i<pointArray.GetCount();i++)
        {
			d=*(pointArray[i]);
            Sx3 += pow(d, 3); // sum of x^3
        }
        return Sx3;
    }

double CQuadraticFit::getSx4() // get sum of x^4
    {
        double Sx4 = 0;
		double d;
        for (int i=0;i<pointArray.GetCount();i++)
        {
			d=*(pointArray[i]);
            Sx4 += pow(d, 4); // sum of x^4
        }
        return Sx4;
    }

double CQuadraticFit:: getSxy() // get sum of x*y
    {
        double Sxy = 0;
        for (int i=0;i<pointArray.GetCount();i++)
        {
            Sxy += (*(pointArray[i])) * (*(pointArray[i]+1)); // sum of x*y
        }
        return Sxy;
    }

 double CQuadraticFit:: getSx2y() // get sum of x^2*y
    {
        double Sx2y = 0;
        for (int i=0;i<pointArray.GetCount();i++)
        {
            Sx2y +=pow(*(pointArray[i]), 2) * (*(pointArray[i]+1)); // sum of x^2*y
        }
        return Sx2y;
    }

 double CQuadraticFit:: getYMean() // mean value of y
    {
        double y_tot = 0;
        for(int i=0;i<pointArray.GetCount();i++)
        {
            y_tot += *(pointArray[i]+1); 
        }
        return y_tot/numOfEntries;
    }

 double CQuadraticFit::getSStot() // total sum of squares
    {
        //the sum of the squares of the differences between 
        //the measured y values and the mean y value
        double ss_tot = 0;
        for (int i=0;i<pointArray.GetCount();i++)
        {
            ss_tot += pow((*(pointArray[i]+1) - getYMean()), 2);
        }
        return ss_tot;
    }

 double CQuadraticFit:: getSSerr() // residual sum of squares
    {
        //the sum of the squares of te difference between 
        //the measured y values and the values of y predicted by the equation
        double ss_err = 0;
		double d,d1;
        for (int i=0;i<pointArray.GetCount();i++)
        {
			d=getPredictedY(*(pointArray[i]));
			d1=*(pointArray[i]+1);
            ss_err += pow((d1- d), 2);
        }
        return ss_err;
    }

 double CQuadraticFit:: getPredictedY(double x)
    {
        //returns value of y predicted by the equation for a given value of x
        return aTerm() * pow(x, 2) + bTerm() * x + cTerm();
    }

