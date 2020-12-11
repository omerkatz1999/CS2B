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
    static const int RULES_SIZE = 32;
    static const long long MAX_RULE = 4294967295;
    
    bool rule[RULES_SIZE];
    string thisGen;
    string extremeBit; // bit, "*" or " ", implied everywhere "outside"
    int displayWidth;  // an odd number so it can be perfectly centered
    
public:
    static const int MAX_DISPLAY_WIDTH = 121;
    static const int ruleSizeBits = 32;
    
    Automaton(long long rule);
    string toStringCurrentGen();
    bool setRule(long long newRule);      // change rule set
    string convertBase(long long newRule);
    void resetFirstGen();
    bool setDisplayWidth(int width);
    void propagateNewGeneration();
};

Automaton::Automaton(long long rule)
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


bool Automaton::setRule(long long newRule)
{
    
    if( newRule < 0 || newRule > MAX_RULE)
    {
        return false;
    }
    // take binary and the converts to spring
    
    string s = convertBase(newRule);
    
    // adds zeros in front of the binary in to make it the size of 8
    string placeHolder ="";
    
    for( int i = 0; i< ruleSizeBits - s.length(); i++)
    {
        placeHolder += "0";
    }
    
    s = placeHolder + s;
    
    // creates the array and places 0s and 1s according to rule (string)
    bool rule [ruleSizeBits];
    
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

string Automaton::convertBase(long long newRule)
{
    string binary;
    
    do {
        int x = newRule % 2;
        newRule = newRule/2;
        
        ostringstream newString;
        newString << x;
        string s = newString.str();
        
        binary = s + binary;
        
    }
    while( newRule> 0 );
    
    return binary;

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
    thisGen = extremeBit + extremeBit + thisGen +extremeBit + extremeBit;
    int sizeSubstring = 5;
    double amountOfSubstrings = thisGen.length() - 4;
    
    string newString = "";
    
    for( int i = 0; i < amountOfSubstrings; i++)
    {
        string sub = thisGen.substr(i,sizeSubstring);
        
        
        if(sub == "     ")
        {
            if(rule[0] == 1)
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub == "    *")
        {
            if(rule[1])
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub =="   * ")
        {
            if(rule[2] == 1)
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub =="   **")
        {
            if(rule[3] == 1)
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub == "  *  ")
        {
            if(rule[4] == 1)
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub == "  * *")
        {
            if(rule[5] == 1)
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub == "  ** ")
        {
            if(rule[6] == 1)
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub == "  ***")
        {
            if(rule[7] == 1)
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub == " *   ")
        {
            
            if(rule[8])
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub ==" *  *")
        {
            if(rule[9] == 1)
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub ==" * * ")
        {
            if(rule[10] == 1)
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub == " * **")
        {
            if(rule[11] == 1)
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub == " **  ")
        {
            if(rule[12] == 1)
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub == " ** *")
        {
            if(rule[13] == 1)
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub == " *** ")
        {
            if(rule[14] == 1)
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub == " ****")
        {
            
            if(rule[15])
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub =="*    ")
        {
            if(rule[16] == 1)
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub =="*   *")
        {
            if(rule[17] == 1)
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub == "*  * ")
        {
            if(rule[18] == 1)
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub == "*  **")
        {
            if(rule[19] == 1)
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub == "* *  ")
        {
            if(rule[20] == 1)
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub == "* * *")
        {
            if(rule[21] == 1)
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub == "* ** ")
        {
            
            if(rule[22])
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub =="* ***")
        {
            if(rule[23] == 1)
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub =="**   ")
        {
            if(rule[24] == 1)
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub == "**  *")
        {
            if(rule[25] == 1)
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub == "** * ")
        {
            if(rule[26] == 1)
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub == "** **")
        {
            if(rule[27] == 1)
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub == "***  ")
        {
            if(rule[28] == 1)
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub == "*** *")
        {
            
            if(rule[29])
            {
                newString += "*";
            }
            else newString += " ";
        }
        else if(sub =="**** ")
        {
            if(rule[30] == 1)
            {
                newString += "*";
            }
            else newString += " ";
        }
        else
        {
            if(rule[31] == 1)
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
        if(rule[31])
        {
            extremeBit = "*";
        }
        else extremeBit = " ";
    }
    return;
}






int main()
{
    
    long long rule;
    
    // get rule from user
   
    for ( int i = 0 ; i < 4; i++){
        cout << "Enter Rule (0 - 4294967295): ";
        cin >> rule;
   
    
        Automaton aut(rule);
    
        aut.setDisplayWidth(79);
     
    
        for( int i = 0; i < 50; i++)
        {
           cout<<  aut.toStringCurrentGen() <<  endl;
           aut.propagateNewGeneration();
        
        }
    }
    
}
//16, 457716700, 3222257679 , 500426, 3829801
//500426 is cool 3829801 3468999 4783733
