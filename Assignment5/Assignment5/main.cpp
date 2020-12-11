//
//  main.cpp
//  Assignment5
//
//  Created by Omer Katz on 5/7/18.
//  Copyright © 2018 Omer Katz. All rights reserved.
//

#include <iostream>
#include <string>
#include <iostream>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include<iomanip>
#include <math.h>

using namespace std;

class Complex{

    static const int DEFAULT_REAL = 0;
    static const int DEFAULT_IMAG = 0;
    
private:
    double real;
    double imaginary;

public :
   
    Complex(double real = DEFAULT_REAL, double imaginary = DEFAULT_IMAG);
    double getReal();
    double getImag();
    bool setReal(double d);
    bool setImag(double d);
    double modulus() const;
    Complex reciprocal()const;
    string toString();
    
    friend Complex operator+ (const Complex& a, const Complex& b);
    friend Complex operator- (const Complex& a, const Complex& b);
    friend Complex operator* (const Complex& a, const Complex& b);
    friend Complex operator/ (const Complex& a, const Complex& b);
    friend ostream & operator<< (ostream& stream, const Complex& a);
    friend bool operator== (const Complex& a, const Complex& b);
    friend bool operator< (const Complex& a, const Complex& b);
    Complex &operator= (const Complex& a);
    
    class DivByZero{};
    
};


Complex:: Complex(double real, double imaginary)
{
    if(setReal(real))
    {
        this-> real = real;
    }
    else
    {
        this-> real = 0;
    }
    
    if(setImag(real))
    {
         this-> imaginary = imaginary;
    }
    else
    {
        this-> imaginary = 0;
    }
   
}


double Complex:: getReal()
{
    return real;
}

double Complex:: getImag()
{
    return imaginary;
}

bool Complex:: setReal(double d)
{
 
    this-> real = d;
    return true;
    
}

bool Complex:: setImag(double d)
{

    this-> imaginary = d;
    return true;
    
}

string Complex:: toString()
{
    string s;
    
    ostringstream realString;
    realString << real;
    string realString1 = realString.str();
    
    ostringstream imaginaryString;
    imaginaryString << imaginary;
    string imaginaryString1 = imaginaryString.str();
    
    
    s = "(" + realString1 + " , " + imaginaryString1 + ")";
    
    return s;
}

double Complex:: modulus() const
{
    double c = real*real + imaginary*imaginary;
    double modulus = sqrt(c);
    return modulus;
}

Complex Complex:: reciprocal() const
{
    Complex returnedObject;
    
    if((real*real + imaginary*imaginary) < .00000001)
    {
        returnedObject.real = 0;
        returnedObject.imaginary = 1;
        throw Complex::DivByZero();
        
        return returnedObject;
    }
        
    returnedObject.real = real / (real*real + imaginary*imaginary);
    returnedObject.imaginary = -imaginary / (real*real + imaginary*imaginary);
    
    return returnedObject;
}

Complex operator+ (const Complex& a, const Complex& b)
{
    Complex resultant;
    
    resultant.real = a.real + b.real;
    resultant.imaginary = a.imaginary + b.imaginary;
    
    return resultant;
}

Complex operator- (const Complex& a, const Complex& b)
{
    Complex resultant;
    
    resultant.real = a.real - b.real;
    
    resultant.imaginary = a.imaginary - b.imaginary;
    
    return resultant;
}

Complex operator* (const Complex& a, const Complex& b)
{
    Complex resultant;
    
    resultant.real = a.real * b.real - a.imaginary * b.imaginary;
    
    resultant.imaginary = a.real * b.imaginary + a.imaginary * b.real;
  
    return resultant;
    
}

Complex operator/ (const Complex& a, const Complex& b)
{
    Complex resultant;
    Complex bReciprocal = b.reciprocal();
    
    resultant = a * bReciprocal;
    
    return resultant;
}


ostream & operator<< (ostream& stream, const Complex& c)
{
    stream << "(" << c.real << " , " << c.imaginary << ")";
    
    return stream;
}

Complex& Complex:: operator=( const Complex& a)
{
    this->real = a.real;
    this->imaginary = a.imaginary;
    
    return *this;
   
}
bool operator==( const Complex& a, const Complex& b)
{
   if( a.real == b.real && a.imaginary == b.imaginary)
   {
       return true;
   }
   else return false;
}

bool operator<( const Complex& a, const Complex& b)
{
    if( a.modulus() < b.modulus())
    {
        return true;
    }
    else return false;
}

int main(int argc, const char * argv[]) {

    try
    {
     
        Complex a, b(1), c(-1,2), d(0,2);
        
        cout << "complex a: " << a << endl;
        
        cout << "complex b: " << b << endl;
        
        cout << "complex c: " << c << endl;
        
        cout << "complex d: " << d << endl;
        
        cout << "c + b: " << (c+b) << endl;
        
        cout << "d + c: " << (d+c) << endl;
        
        cout << "b + d: " << (d+b) << endl;
        
        cout << "a * b: " << (a*b) << endl;
        
        cout << "b * c: " << (b*c) << endl;
        
        cout << "b * d: " << (b*d) << endl;
        
        cout << "a / b: " << (a/b) << endl;
        
        cout << "b / c: " << (b/c) << endl;
        
        bool test = a < b ;
        cout << "is a < b: " << test << endl;
        
        bool test1 = b < a ;
        cout << "is b < a: " << test1 << endl;
        
        bool test2 = a == b ;
        cout << "is a == b: " << test2 << endl;
        
        Complex e;
        bool test3 = a == e ;
        cout << "is a == e: " << test3 << endl;
        
        a = c;
        cout << "testing a = c, print a: " << a << endl;
        
        d = b = a;
        
        cout << "testing = operator, print d and b: " << d << " ," << b << endl;
        
        c = d;
        
        cout << "testing = operator, print c: " << c << endl;
        
        a.setReal(0);
        a.setImag(0);
      
       
       
       
        
        Complex a1(1,2), b1(3, 4), c1;
        //double x=2, y= -1.7;
        
        c1 = a1 + b1;
        
        cout << " c1 is:" << c1 << endl;
        c1 = a1 - b1;
        cout << " c1 is:" << c1 << endl;
        c1 = a1* b1;
        cout << " c1 is:" << c1 << endl;
        
        c1 = a1/ b1;
        cout << " c1 is:" << c1 << endl;
        
        // and also:
        c1 =  a1 + 10;
        cout << " c1 is:" << c1 << endl;
        
        c1 = 10 / b1;
        cout << " c1 is:" << c1 << endl;
        
        cout << "b / a: " << (b/a).toString() << endl;
        
        cout << "exception did not work";
        
       
    }

    catch (Complex::DivByZero)
    {
        cout << "*** You are not allowed to divide by zero ***"  << endl;
        
    }
}

