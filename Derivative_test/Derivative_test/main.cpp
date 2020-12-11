//
//  main.cpp
//  Derivative_test
//
//  Created by Omer Katz on 5/25/18.
//  Copyright © 2018 Omer Katz. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

using namespace std;




class FunctionOfX
{

private:
    double *coArray;
    string function;
    double arraySize;
    //double xValue;
    
    
public:
    FunctionOfX(double input);
    bool set(double coefficiants[]);
    void set(string func);
    FunctionOfX( FunctionOfX& rhs);
    virtual ~FunctionOfX(){ delete [] coArray;}
    FunctionOfX &operator= (const  FunctionOfX &rhs);
    double derivative(double x);
    double powerRuleDerivative(double x);
    double definiteIntegral(double lowerBoundery, double upperBoundery);
};

FunctionOfX:: FunctionOfX(double input)
{
    arraySize = input;
    coArray = new double [arraySize];
}

bool FunctionOfX:: set(double coefficiants[] )
{
    
    
    for( int i = 0; i < arraySize; i++)
    {
        coArray[i] = coefficiants[i];
    }
    return true;
    
  
}

double FunctionOfX::derivative(double x)
{
    double xValue = x;
    
    double y = 0;
    double yOfDelta = 0;
    double deltaX = 1e-12;
    double xPlusDelta = xValue+deltaX;
    double yPrime=0;
    
    for( int i = 0; i < arraySize; i++)
    {
        y += coArray[i] * (pow(xValue, i));
    }
    
    for( int i = 0; i < arraySize; i++)
    {
        yOfDelta += coArray[i] * (pow(xPlusDelta, i));
    }
    
    
    yPrime = ((yOfDelta - y)/deltaX);
    
    return yPrime;
}


double FunctionOfX:: powerRuleDerivative(double x)
{
    double xValue = x;
    double y = 0;
    for( int i = 1; i < arraySize; i++)
    {
        y += coArray[i] * i * (pow(xValue, (i-1)));
    }
    
    return y;
    
}

//void FunctionOfX:: set(string func)
//{
 //   function = func;
//}

/*
class stringDerivative
{
    
};
*/

double FunctionOfX:: definiteIntegral(double lowerBoundery, double upperBoundery)
{
    double integralValue = 0;
    
    double evaluatedAtLower = 0;
    double evaluatedAtUpper = 0;
    
    
    for( int i = 0; i < arraySize; i++)
    {
     
        evaluatedAtLower += (coArray[i] / (i+1) ) * (pow(lowerBoundery, i+1));
        
    }
    
    
    for( int i = 0; i < arraySize; i++)
    {
        evaluatedAtUpper += (coArray[i]/(i+1)) * (pow(upperBoundery, i+1));
    }
    
   
    integralValue = evaluatedAtUpper - evaluatedAtLower;
    
    return integralValue;
}



int main(int argc, const char * argv[]) {
   
    int arraySize;
    cout << "enter number of coefficiants:";
    cin >> arraySize;
    cout << endl;
    double  arrayInput[arraySize];
    
    for( int i = 0; i < arraySize; i++)
    {   double x;
        cout << "enter coefficiant for the " << (i+1);
        if(i == 0)
        {
            cout <<"st term:" << endl;
        }
        else if(i==1)
        {
            cout <<"nd term:" << endl;
        }
        else if ( i == 2)
        {
            cout <<"rd term:" << endl;
        }
        else{
            cout << "th term" << endl;
        }
       
        cin >> x;
        arrayInput[i] = x;
        cout << endl;
    }
    
    double xVal;
    cout<< "evaluate derivative at:";
    cin >> xVal;
    
    FunctionOfX function1(arraySize);
   
    function1.set(arrayInput);
    
 //   cout << function1.derivative(xVal) << endl;
    
    cout << function1.powerRuleDerivative(xVal) << endl;
    
    
    cout << "defintie integral from 1 to 4:";
    cout << function1.definiteIntegral(1, 4) << endl;
    
    

}











