//
//  main.cpp
//  Asignment1
//
//  Created by Omer Katz on 4/10/18.
//  Copyright © 2018 Omer Katz. All rights reserved.
//

#include <string>
#include <iostream>
#include <sstream>
#include <cctype>


using namespace std;

enum Suit { clubs, diamonds, hearts, spades };

// class Card prototype
class Card
{
   
private:
   char value;
   Suit suit;
   bool errorFlag;
   static bool isValid(char value, Suit suit);
   
public:
   Card(char value = 'A', Suit suit = spades);
   string toString();
   bool set(char value = 'A', Suit suit = spades);
   char getVal();
   Suit getSuit();
   bool getErrorFlag();
   bool equals(Card card);
   
};

// methods-------------
Card::Card(char value, Suit suit)
{
   errorFlag = isValid(value, suit);
   if(!errorFlag)//{
     // if ( !set(value, suit) )
       //  set('A', spades);}
       set(value, suit);
   else
   {
      errorFlag = true;
   }
}


bool Card::isValid(char value, Suit suit)
{
    char upVal;
    upVal = toupper((int)value);
    
    if ( upVal == 'A' || upVal == 'K'|| upVal == 'Q' || upVal == 'J'
        || upVal == 'T'|| (upVal >= '2' && upVal <= '9')){
        
        return false;
        
    }
    else
    {
        return true;
    }
}



// stringizer
string Card::toString()
{
   if(!errorFlag){
      string retVal;
      char strVal[2];
   
      // convert char to a CString
      strVal[0] = value;
      strVal[1] = '\0';
   
      // convert from CString to s-c string
      retVal = string(strVal);
   
      if (suit == spades)
         retVal += " of Spades";
      else if (suit == hearts)
         retVal += " of Hearts";
      else if (suit == diamonds)
         retVal += " of Diamonds";
      else if (suit == clubs)
         retVal += " of Clubs";
         return retVal;}
   else{
     return "invalid";
   }
}

// set
bool Card::set(char value, Suit suit)
{
   char upVal;
   
   upVal = toupper((int)value);
   
    if( !isValid(value, suit)){
      this->suit = suit;
      this->value = upVal;
      errorFlag = false;
      return true;
   }
   else
   {
      errorFlag = true;
      return false;
    
   }
}

// accessors
char Card::getVal()
{
   return value;
}

Suit Card::getSuit()
{
   return suit;
}

bool Card::getErrorFlag()
{
   return errorFlag;
}

bool Card:: equals(Card card)
{
   if( this->value == card.getVal() && this->suit == card.getSuit())
   {
      return true;
   }
   else
   {
      return false;
   }
}
// end of card methods-------------------------------------------------------


class Hand
{

static const int MAX_CARDS = 50;
   
private:
   int numCards;
   Card myCards[MAX_CARDS];
   
public:
   Hand();
   void resetHand();
   bool takeCard(Card card);
   Card playCard();
   string toString();
   int getNumOfCards();
   Card inspectCard(int k);
   
};

Hand::Hand(){
     numCards =0;
}


bool Hand::takeCard(Card card)
{
   
   if(numCards >= MAX_CARDS) return false;
   
   else if(!card.getErrorFlag())
   {
      myCards[numCards] = card;
      numCards++;
   }
   
   return true;

}

void Hand::resetHand()
{
   numCards = 0;
}

string Hand::toString()
{
   string cardString = "(";
   for(int i = 0; i<numCards; i++)
   {
      if(i < numCards-1)
      {
         cardString += myCards[i].toString()+" , ";
      }
      else
      {
         cardString += myCards[i].toString();
      }
   }
   cardString += ")";
   return cardString;
}

Card Hand::playCard()
{
    
    
    if(numCards > 0)
    {
        numCards --;
        
        return myCards[numCards];
    }
    else return myCards[numCards];
    
   
}

int Hand::getNumOfCards()
{
   return numCards;
}

Card Hand::inspectCard(int k)
{
    Card INVALID_CARD( '0',hearts );
    if ( k >= numCards || k < 0)
    {
        return INVALID_CARD;
    }
    return myCards[k];
}



int main(int argc, const char * argv[]) {
   // test phase 1
   
   Card card1, card2('k',hearts);
   Card card3('t',spades), card4('q',hearts), card5('j',spades);
   Card card6('x', clubs);
   
   cout << card1.toString()<< endl;
   cout << card2.toString() << endl;
   cout << card3.toString() << endl;
   cout << card6.toString() << endl;
   card2.set('A',spades);
   
   cout << "Test is equal method: ";
   
   cout << card1.equals(card2) << endl;

   card2.set('k',hearts);
   
   // test of phase 2
   Hand hand1;
   
   hand1.takeCard(card1);
   hand1.takeCard(card2);
   hand1.takeCard(card3);
   hand1.takeCard(card4);
   hand1.takeCard(card5);
   
   for (int i = 0; i< 50;i++){
    
      hand1.takeCard(hand1.inspectCard(i));
   
   }
   
   hand1.takeCard(card2);
   
    
   
   cout << "Hand full"<< endl;
   cout << "After deal Hand = " << endl;
   cout << hand1.toString() << endl;
   
   cout << "Testing inspectCard()" << endl;
   
   
   Hand hand2;
   
   hand2.takeCard(card3);
   
   Card cardTest = hand2.inspectCard(0);
   
   cout << cardTest.toString() << endl;
   
   Card cardInvalid('z', hearts);

   Hand hand3;
   hand3.takeCard(cardInvalid);
   
   Card cardTest2 = hand3.inspectCard(0);
   
   cout << cardTest2.toString() << endl;
   
   for (int i = 0; i< 50;i++){
    
      Card cardPlayed = hand1.playCard();
    
     if (i<49)
     {
      cout<< "playing " + cardPlayed.toString() <<  endl;
     }
     else
      {
         cout << "After playing all cards" <<endl;
         cout << "Hand = ";
      
      }
    
   }
   
   cout<< hand1.toString();
   
   
}


/* ------------------output for phase 1 and 2--------------
 
 A of Spades
 K of Hearts
 T of Spades
 invalid
 Test is equal method: 1
 Hand full
 After deal Hand =
 (A of Spades , K of Hearts , T of Spades , Q of Hearts , J of Spades , A of Spades , K of Hearts , T of Spades , Q of Hearts , J of Spades , A of Spades , K of Hearts , T of Spades , Q of Hearts , J of Spades , A of Spades , K of Hearts , T of Spades , Q of Hearts , J of Spades , A of Spades , K of Hearts , T of Spades , Q of Hearts , J of Spades , A of Spades , K of Hearts , T of Spades , Q of Hearts , J of Spades , A of Spades , K of Hearts , T of Spades , Q of Hearts , J of Spades , A of Spades , K of Hearts , T of Spades , Q of Hearts , J of Spades , A of Spades , K of Hearts , T of Spades , Q of Hearts , J of Spades , A of Spades , K of Hearts , T of Spades , Q of Hearts , J of Spades)
 Testing inspectCard()
 T of Spades
 invalid
 playing J of Spades
 playing Q of Hearts
 playing T of Spades
 playing K of Hearts
 playing A of Spades
 playing J of Spades
 playing Q of Hearts
 playing T of Spades
 playing K of Hearts
 playing A of Spades
 playing J of Spades
 playing Q of Hearts
 playing T of Spades
 playing K of Hearts
 playing A of Spades
 playing J of Spades
 playing Q of Hearts
 playing T of Spades
 playing K of Hearts
 playing A of Spades
 playing J of Spades
 playing Q of Hearts
 playing T of Spades
 playing K of Hearts
 playing A of Spades
 playing J of Spades
 playing Q of Hearts
 playing T of Spades
 playing K of Hearts
 playing A of Spades
 playing J of Spades
 playing Q of Hearts
 playing T of Spades
 playing K of Hearts
 playing A of Spades
 playing J of Spades
 playing Q of Hearts
 playing T of Spades
 playing K of Hearts
 playing A of Spades
 playing J of Spades
 playing Q of Hearts
 playing T of Spades
 playing K of Hearts
 playing A of Spades
 playing J of Spades
 playing Q of Hearts
 playing T of Spades
 playing K of Hearts
 After playing all cards
 Hand = ()Program ended with exit code: 0
 */




