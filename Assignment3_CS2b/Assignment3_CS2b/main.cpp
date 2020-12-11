//
//  main.cpp
//  Assignment3_CS2b
//
//  Created by Omer Katz on 4/20/18.
//  Copyright © 2018 Omer Katz. All rights reserved.
//

#include <iostream>
#include <string>
#include <iostream>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include<iomanip>

using namespace std;

class Automaton
{
private:
    static const int RULES_SIZE = 8;
    static const int MAX_NUM = 255;

    bool rule[RULES_SIZE];
    string thisGen;
    string extremeBit; // bit, "*" or " ", implied everywhere "outside"
    int displayWidth;  // an odd number so it can be perfectly centered
    
public:
    static const int MAX_DISPLAY_WIDTH = 121;
    static const int ruleSizeBits = 8;
    
    Automaton(int rule);
    string toStringCurrentGen();
    bool setRule(int newRule);      // change rule set
    int convertBase(int newRule);
    void resetFirstGen();
    bool setDisplayWidth(int width);
    void propagateNewGeneration();
};

Automaton::Automaton(int rule)
{
    thisGen = "*";
    extremeBit = " ";
    if(!setRule(rule))
    {
        setRule(0);
    }
    else
    {
        setRule(rule);
    }
    
}


bool Automaton::setRule(int newRule)
{
    if( newRule < 0 || newRule > MAX_NUM)
    {
        return false;
    }
    
    // take binary and the converts to spring
    int binary = convertBase(newRule);
    ostringstream newString;
    newString << binary;
    string s = newString.str();
    
    // adds zeros in front of the binary in to make it the size of 8
    string placeHolder ="";
    
    for( int i = 0; i< ruleSizeBits - s.length(); i++)
    {
        placeHolder += "0";
    }
    
    s = placeHolder + s;

    // creates the array and places 0s and 1s according to rule (string)
    bool rule [8];

    for( int i = 0; i < ruleSizeBits; i++)
    {
        rule [i] = false;
    }
    
    for( int i = 1; i < s.length()+1; i++)
    {
        if (s.at(i-1) == '0')
        {
            rule [s.length()-i] = false;
        }
        else  rule [s.length()-i] = true;
    }
    
    for(int i = 0; i < ruleSizeBits; i++)
    {
        this-> rule[i] = rule[i];
    }
    
    return true;
}

void Automaton::resetFirstGen()
{
    extremeBit = " ";
    thisGen = "*";
    
}

int Automaton::convertBase(int newRule)
{
    if(newRule == 0)
    {
        return 0;
    }
    
    else
    {
        return (newRule % 2 + 10*convertBase(newRule/2));
    }
}

bool Automaton::setDisplayWidth( int width )
{
    
    if( width <= MAX_DISPLAY_WIDTH && width > 0
       && width % 2 == 1)
    {
        displayWidth = width;
        return true;
    }
    return false;
}


string Automaton::toStringCurrentGen()
{
    
    
    if( thisGen.length() < displayWidth)
    {
        double difference =  displayWidth - thisGen.length();
        int extremeBitPerSide = difference/2;
        
        string filler = extremeBit;
        
        for( int i = 1; i < extremeBitPerSide; i++)
        {
            
            filler += extremeBit;
        }
        
       
        string returnString = filler + thisGen + filler;
        
        return returnString;
    }
    else if (thisGen.length() > displayWidth)
    {
        double difference =  thisGen.length() - displayWidth;
        int reduce = difference/2;
        string returnString;
        returnString = thisGen.substr(reduce, displayWidth);
        return returnString;
    }
    else return thisGen;
    
}

void Automaton::propagateNewGeneration()
{
    thisGen = extremeBit + extremeBit +thisGen + extremeBit + extremeBit;
    int sizeSubstring = 3;
    double amountOfSubstrings = thisGen.length() - 2;
    
    string newString = "";
  
    for( int i = 0; i < amountOfSubstrings; i++)
    {
        string sub = thisGen.substr(i,sizeSubstring);
        
        if(sub == "   ")
        {
            if(rule[0] == 1)
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub == "  *")
        {
            
            if(rule[1])
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub ==" * ")
        {
            if(rule[2] == 1)
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub ==" **")
        {
            if(rule[3] == 1)
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub == "*  ")
        {
            if(rule[4] == 1)
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub == "* *")
        {
            if(rule[5] == 1)
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub == "** ")
        {
            if(rule[6] == 1)
            {
                newString += "*";
            }
            else newString += " ";
        }
        else
        {
            if(rule[7] == 1)
            {
                newString += "*";
            }
            else newString += " ";
        }
        
    }
    thisGen = newString;
    
    
    if(extremeBit == " ")
    {
        if(rule[0])
        {
            extremeBit = "*";
        }
        else extremeBit = " ";
    }
    else
    {
        if(rule[7])
        {
            extremeBit = "*";
        }
        else extremeBit = " ";
    }
    return;
}






int main()
{

    int rule;
    
    for ( int i = 0 ; i < 4; i++){
        cout << "Enter Rule (0 - 255): ";
        cin >> rule;
        
        
        Automaton aut(rule);
        
        aut.setDisplayWidth(79);
        
        
        
        cout << "start" << endl;
        for( int i = 0; i < 99; i++)
        {
            cout<<  aut.toStringCurrentGen() <<  endl;
            aut.propagateNewGeneration();
            
        }
        cout << "end" << endl << endl;
    }
    
}
//78 and 45 are cool

 