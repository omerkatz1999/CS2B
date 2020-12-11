
//  Created by Omer Katz on 4/10/18.
//
//

#include <string>
#include <iostream>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <ctime>

using namespace std;



// class Card prototype
class Card
{
    
public:
    enum Suit { clubs, diamonds, hearts, spades };

private:
    char value;
    Suit suit;
    bool errorFlag;
    static bool isValid(char value, Suit suit);
    
public:
    Card(char value = 'A', Suit suit = spades);
    string toString();
    bool set(char value = 'A', Suit suit = spades);
    char getValue(){ return value; };
    Suit getSuit(){ return suit; };
    bool getErrorFlag(){ return errorFlag; };
    bool equals(Card card);
    
};

// methods-------------
Card::Card(char value, Suit suit)
{
        set(value, suit);
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
bool Card:: equals(Card card)
{
    if( this->value == value && this->suit == suit)
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
    
    Card errorReturn(0, Card::spades);
    if(numCards > 0)
    {
        numCards --;
        
        return myCards[numCards];
    }
    else return errorReturn;
    
    
}

int Hand::getNumOfCards()
{
    return numCards;
}

Card Hand::inspectCard(int k)
{
    Card errorReturn(0, Card::spades);
    if ( k >= numCards || k < 0)
    {
        return errorReturn;
    }
    return myCards[k];
}
// end of hand methods


//Deck class
class Deck
{
    static const int  MAX_PACKS = 6;
    static const int NUM_CARDS_PER_PACK = 52;
    static const int MAX_CARDS_PER_DECK = MAX_PACKS *NUM_CARDS_PER_PACK;
    static Card masterPack[NUM_CARDS_PER_PACK];
    
private:
    
    static void allocateMasterPack();
    Card cards[MAX_CARDS_PER_DECK];
    int topCard;
    int numPacks;
    static bool allocatedMasterPack ;
    
public:
    Deck(int numPacks = 1);
    
    bool init(int numPacks);
    
    void shuffle();
    
    Card dealCard();
    
    int getTopCard​(){ return topCard; };
    
    Card inspectCard(int k);
    
};

Card Deck::masterPack[NUM_CARDS_PER_PACK];

bool Deck::allocatedMasterPack = false;


Deck::Deck(int numPacks): topCard(-1)
{

    this->numPacks = numPacks;
    
    if(!allocatedMasterPack)
    {
    allocateMasterPack();
    }
  
    if(init(numPacks))
    {
        init(numPacks);
    }
    else
    {
        init(1);
        this->numPacks = 1;
    }
    
}


void Deck::allocateMasterPack()
{
    
    Card::Suit st;
    int k, j;
    char val;
    
    for (k = 0; k < 4; k++)
    {
        st = static_cast< Card::Suit >(k);
        
        // now set all the values for this suit
        masterPack[13*k].set('A', st);
        
        for (val = '2', j = 1; val <= '9'; val++, j++)
            masterPack[13*k + j].set(val, st);
            masterPack[13*k+9].set('T', st);
            masterPack[13*k+10].set('J', st);
            masterPack[13*k+11].set('Q', st);
            masterPack[13*k+12].set('K', st);
       
            
            }
         allocatedMasterPack = true;
    return;
    
}

bool Deck::init(int numPacks)
{
    topCard = (numPacks * NUM_CARDS_PER_PACK) -1;
    
    if ( numPacks > 0 && numPacks <= MAX_PACKS)
    {
        for( int i =  0; i < (numPacks * NUM_CARDS_PER_PACK); i++ )
        {
            
            cards[i] = masterPack[i % NUM_CARDS_PER_PACK];
            
        }
         return true;
    }
    return false;
    
}

void Deck::shuffle()
{
 
    for( int i = 0 ; i < ( NUM_CARDS_PER_PACK * numPacks) -1 ; i++)
    {
      
        int ran = rand() % (NUM_CARDS_PER_PACK * numPacks);
        
       /* original code
        
        Card * cardPtr = new Card;
        Card * cardPtr2 = new Card;
        
        *cardPtr = cards[i];
        *cardPtr2 = cards[ran];
        
        cards[ran] = *cardPtr;
        cards[i] = *cardPtr2;
        */
        
        Card  card1;
        Card  card2;
        
        
        card1 = cards[i];
        card2 = cards[ran];
        
        cards[ran] = card1;
        cards[i] = card2;
        
        
    }
    
}

Card Deck::dealCard()
{
    Card errorReturn(0, Card::spades);
    if( topCard >= 0)
    {
        return cards[topCard--];
    }
    
    return  errorReturn;
    
}

Card Deck::inspectCard(int k)
{
    Card errorReturn(0, Card::spades);
    if ( k >= topCard || k < 0)
    {
        return errorReturn;
    }
    return cards[k];
}


int main(int argc, const char * argv[])
{
    
    srand(time(0));
    
    Deck testTwoPack(2);
    
    for( int i = 0; i < 2*52; i++)
    {
       
        Card dealtCard = testTwoPack.dealCard();
        cout << dealtCard.toString()<< ", ";
        
    }
    
    cout << endl << endl << endl;
    testTwoPack.init(2);
    
    testTwoPack.shuffle();
    
    for( int i = 0; i < 2*52; i++)
    {
        
        Card dealtCard = testTwoPack.dealCard();
        cout << dealtCard.toString()<< ", ";
        
    }
    
   cout << endl << endl << endl;
    
    Deck testOnePack(1);
    
    for( int i = 0; i < 52; i++)
    {
        
        Card dealtCard1 = testOnePack.dealCard();
        cout << dealtCard1.toString()<< ", ";
        
    }
    
    cout << endl << endl << endl;
    
    testOnePack.init(1);
    testOnePack.shuffle();
    
    for( int i = 0; i < 52; i++)
    {
        
        Card dealtCard1 = testOnePack.dealCard();
        cout << dealtCard1.toString()<< ", ";
        
    }
    
   // second part of main
    
    cout << endl << endl << endl << endl << "---------part 2-----------"<< endl;
    
    cout << endl <<  endl <<  endl
         << "How Many Players?(1-10, please)";
    
   
    int numberOfHands;
    
    cin >> numberOfHands;
    
    // creates hands, based on the input
    Hand arrayOfHands[numberOfHands];
    
    Deck normalDeck(1);
    
    cout << "Here are our hands, from unshuffled deck:" << endl << endl << endl;
    
    // prints the hand objects
    for( int i = 0; i < numberOfHands; i++)
    {
        
        //deals the hand objects
        for( int c = 0; c < 52; c++)
        {
            arrayOfHands[c % numberOfHands].takeCard(normalDeck.dealCard());
        }
        
        cout << "hand number " << (i+1) << " = "
        << arrayOfHands[i].toString() << endl << endl;
        
     }
    
   
    Hand arrayOfHands2[numberOfHands];
    
    Deck shuffledDeck(0);
    
    shuffledDeck.shuffle();
    
   
    cout << "Here are our hands, from SHUFFLED deck:" << endl << endl << endl;
    
    // prints the hand objects
    for( int i = 0; i < numberOfHands; i++)
    {
        
        //deals the hand objects
        for( int c = 0; c < 52; c++)
        {
            arrayOfHands2[c % numberOfHands].takeCard(shuffledDeck.dealCard());
        }
        
        cout << "hand number " << (i+1) << " = "
        << arrayOfHands2[i].toString() << endl << endl;
        
    }

}


 
 
 /*
-----------------------output-----------------------------------
K of Spades, Q of Spades, J of Spades, T of Spades, 9 of Spades, 8 of Spades, 7 of Spades, 6 of Spades, 5 of Spades, 4 of Spades, 3 of Spades, 2 of Spades, A of Spades, K of Hearts, Q of Hearts, J of Hearts, T of Hearts, 9 of Hearts, 8 of Hearts, 7 of Hearts, 6 of Hearts, 5 of Hearts, 4 of Hearts, 3 of Hearts, 2 of Hearts, A of Hearts, K of Diamonds, Q of Diamonds, J of Diamonds, T of Diamonds, 9 of Diamonds, 8 of Diamonds, 7 of Diamonds, 6 of Diamonds, 5 of Diamonds, 4 of Diamonds, 3 of Diamonds, 2 of Diamonds, A of Diamonds, K of Clubs, Q of Clubs, J of Clubs, T of Clubs, 9 of Clubs, 8 of Clubs, 7 of Clubs, 6 of Clubs, 5 of Clubs, 4 of Clubs, 3 of Clubs, 2 of Clubs, A of Clubs, K of Spades, Q of Spades, J of Spades, T of Spades, 9 of Spades, 8 of Spades, 7 of Spades, 6 of Spades, 5 of Spades, 4 of Spades, 3 of Spades, 2 of Spades, A of Spades, K of Hearts, Q of Hearts, J of Hearts, T of Hearts, 9 of Hearts, 8 of Hearts, 7 of Hearts, 6 of Hearts, 5 of Hearts, 4 of Hearts, 3 of Hearts, 2 of Hearts, A of Hearts, K of Diamonds, Q of Diamonds, J of Diamonds, T of Diamonds, 9 of Diamonds, 8 of Diamonds, 7 of Diamonds, 6 of Diamonds, 5 of Diamonds, 4 of Diamonds, 3 of Diamonds, 2 of Diamonds, A of Diamonds, K of Clubs, Q of Clubs, J of Clubs, T of Clubs, 9 of Clubs, 8 of Clubs, 7 of Clubs, 6 of Clubs, 5 of Clubs, 4 of Clubs, 3 of Clubs, 2 of Clubs, A of Clubs,


4 of Spades, A of Hearts, 7 of Clubs, K of Clubs, 5 of Clubs, T of Clubs, J of Spades, 5 of Hearts, 6 of Hearts, 3 of Clubs, 2 of Hearts, 6 of Clubs, J of Hearts, J of Clubs, 5 of Diamonds, K of Hearts, 2 of Spades, A of Spades, 8 of Spades, A of Diamonds, 4 of Diamonds, 3 of Diamonds, 6 of Spades, T of Spades, 7 of Diamonds, 7 of Clubs, J of Spades, 3 of Hearts, T of Hearts, 4 of Hearts, T of Hearts, Q of Clubs, 5 of Diamonds, A of Diamonds, T of Diamonds, A of Hearts, 2 of Spades, J of Diamonds, 4 of Hearts, K of Diamonds, K of Spades, Q of Diamonds, 7 of Diamonds, K of Clubs, 8 of Hearts, 9 of Spades, 2 of Diamonds, 3 of Hearts, Q of Hearts, A of Spades, 9 of Clubs, 4 of Diamonds, 5 of Spades, 6 of Clubs, 8 of Clubs, J of Diamonds, K of Spades, 3 of Diamonds, 7 of Hearts, 3 of Spades, 2 of Clubs, 9 of Clubs, A of Clubs, 3 of Clubs, 3 of Spades, 9 of Hearts, 7 of Spades, 6 of Hearts, 9 of Diamonds, T of Clubs, 8 of Hearts, 7 of Spades, Q of Spades, Q of Spades, K of Hearts, 5 of Spades, 4 of Clubs, T of Spades, 8 of Spades, 5 of Clubs, 2 of Hearts, 6 of Spades, Q of Diamonds, 4 of Clubs, 6 of Diamonds, 7 of Hearts, 9 of Diamonds, K of Diamonds, 4 of Spades, 9 of Hearts, Q of Hearts, 6 of Diamonds, J of Hearts, Q of Clubs, 5 of Hearts, 9 of Spades, J of Clubs, 8 of Diamonds, T of Diamonds, 2 of Clubs, 2 of Diamonds, A of Clubs, 8 of Clubs, 8 of Diamonds,


K of Spades, Q of Spades, J of Spades, T of Spades, 9 of Spades, 8 of Spades, 7 of Spades, 6 of Spades, 5 of Spades, 4 of Spades, 3 of Spades, 2 of Spades, A of Spades, K of Hearts, Q of Hearts, J of Hearts, T of Hearts, 9 of Hearts, 8 of Hearts, 7 of Hearts, 6 of Hearts, 5 of Hearts, 4 of Hearts, 3 of Hearts, 2 of Hearts, A of Hearts, K of Diamonds, Q of Diamonds, J of Diamonds, T of Diamonds, 9 of Diamonds, 8 of Diamonds, 7 of Diamonds, 6 of Diamonds, 5 of Diamonds, 4 of Diamonds, 3 of Diamonds, 2 of Diamonds, A of Diamonds, K of Clubs, Q of Clubs, J of Clubs, T of Clubs, 9 of Clubs, 8 of Clubs, 7 of Clubs, 6 of Clubs, 5 of Clubs, 4 of Clubs, 3 of Clubs, 2 of Clubs, A of Clubs,


K of Spades, 9 of Diamonds, J of Diamonds, 4 of Spades, Q of Spades, K of Hearts, 3 of Diamonds, 6 of Diamonds, A of Spades, K of Diamonds, 6 of Clubs, T of Diamonds, 8 of Clubs, 9 of Spades, 9 of Clubs, Q of Hearts, Q of Diamonds, 3 of Clubs, 7 of Spades, 3 of Spades, T of Spades, 5 of Diamonds, A of Clubs, 5 of Spades, J of Clubs, J of Spades, T of Hearts, 8 of Hearts, 8 of Spades, 7 of Clubs, 5 of Clubs, 4 of Clubs, 7 of Diamonds, 7 of Hearts, 9 of Hearts, 2 of Diamonds, 8 of Diamonds, 2 of Spades, T of Clubs, A of Hearts, K of Clubs, Q of Clubs, 4 of Diamonds, J of Hearts, 4 of Hearts, 6 of Hearts, 5 of Hearts, A of Diamonds, 6 of Spades, 2 of Hearts, 3 of Hearts, 2 of Clubs,



---------part 2-----------



How Many Players?(1-10, please)6
Here are our hands, from unshuffled deck:


hand number 1 = (K of Spades , 7 of Spades , A of Spades , 8 of Hearts , 2 of Hearts , 9 of Diamonds , 3 of Diamonds , T of Clubs , 4 of Clubs)

hand number 2 = (Q of Spades , 6 of Spades , K of Hearts , 7 of Hearts , A of Hearts , 8 of Diamonds , 2 of Diamonds , 9 of Clubs , 3 of Clubs)

hand number 3 = (J of Spades , 5 of Spades , Q of Hearts , 6 of Hearts , K of Diamonds , 7 of Diamonds , A of Diamonds , 8 of Clubs , 2 of Clubs)

hand number 4 = (T of Spades , 4 of Spades , J of Hearts , 5 of Hearts , Q of Diamonds , 6 of Diamonds , K of Clubs , 7 of Clubs , A of Clubs)

hand number 5 = (9 of Spades , 3 of Spades , T of Hearts , 4 of Hearts , J of Diamonds , 5 of Diamonds , Q of Clubs , 6 of Clubs)

hand number 6 = (8 of Spades , 2 of Spades , 9 of Hearts , 3 of Hearts , T of Diamonds , 4 of Diamonds , J of Clubs , 5 of Clubs)

Here are our hands, from SHUFFLED deck:


hand number 1 = (K of Spades , 4 of Clubs , 5 of Spades , K of Hearts , T of Hearts , 7 of Diamonds , A of Diamonds , 7 of Hearts , 7 of Clubs)

hand number 2 = (5 of Clubs , T of Diamonds , 8 of Hearts , 2 of Hearts , J of Hearts , A of Clubs , 9 of Diamonds , 8 of Spades , Q of Hearts)

hand number 3 = (8 of Clubs , 3 of Hearts , 4 of Diamonds , J of Diamonds , 3 of Clubs , Q of Spades , 4 of Spades , 6 of Hearts , 8 of Diamonds)

hand number 4 = (K of Clubs , 2 of Diamonds , 5 of Hearts , 6 of Spades , 3 of Diamonds , 4 of Hearts , A of Hearts , 6 of Clubs , 2 of Clubs)

hand number 5 = (9 of Clubs , 6 of Diamonds , J of Clubs , J of Spades , 2 of Spades , 5 of Diamonds , 9 of Hearts , Q of Clubs)

hand number 6 = (T of Spades , 7 of Spades , 9 of Spades , 3 of Spades , A of Spades , Q of Diamonds , T of Clubs , K of Diamonds)

*/













