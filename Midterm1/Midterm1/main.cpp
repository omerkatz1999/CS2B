//
//  main.cpp
//  Midterm1
//
//  Created by Omer Katz on 5/11/18.
//  Copyright © 2018 Omer Katz. All rights reserved.
//

#include <iostream>
#include <string>
#include <iostream>
#include <sstream>
#include <cctype>




using namespace std;


class Furniture {
public:
    static const string DFLT_NAME;
    static const string DFLT_MATERIAL;
    Furniture(const string& name = DFLT_NAME, const string& material = DFLT_MATERIAL);
    string toString() const;
protected:
    string name;
    
private:
    string material;
};

const string Furniture::DFLT_NAME = "generic furniture";
const string Furniture::DFLT_MATERIAL = "polymer";

class Table: public Furniture {
    
public:
    Table(int legs, const string& material);
    Table(int legs);
    string toString() const;
    
protected:
    int numLegs;
    
    
    
};


string Furniture::toString() const {
    string result = "Furniture called " + name + " made of " + material;
    return result;
}


Table:: Table(int legs, const string& material):
   Furniture(  name , material )
{
    this-> name = "table";
    numLegs = legs;
}

Table:: Table(int legs):
   Furniture( name,  material )
{
    this-> name = "table";
    numLegs = legs;
}




int main(int argc, const char * argv[]) {
    // insert code here...
    
}
