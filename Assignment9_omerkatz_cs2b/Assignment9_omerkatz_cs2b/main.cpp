// required includes
#include <iostream>
#include <string>
#include <ctime>
#include <list>
#include <sstream>
#include <cctype>
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
    static char DEFAULT_VAL;
    static Suit DEFAULT_SUIT;
    static bool isValid(char value, Suit suit);
    
public:
    Card(char value = 'A', Suit suit = spades);
    string toString();
    bool set(char value = 'A', Suit suit = spades);
    char getVal();
    Suit getSuit();
    bool getErrorFlag();
    bool equals(Card card);
    
public:
    // if not already symbolized, use consts
    static const int NUM_CARD_VALS = 13;
    static const int NUM_CARD_SUITS = 4;
    
public:
    // comparison members and methods
    const static char valueRanks[NUM_CARD_VALS];
    const static Suit suitRanks[NUM_CARD_SUITS];
    
    int compareTo(Card &other);
    static int getSuitRank(Suit st);
    static int getValueRank(char val);
  
    
    
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

Card::Suit Card::getSuit()
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




 


// for easy comparisons
int operator==(Card first, Card other)
{ return first.compareTo(other) == 0; }

// overloaded the operator to be used in other methods later
bool operator< (Card &card1, Card &card2)
{
    if(card1.compareTo(card2) < 0)
    {
        return true;
    }
    return false;
}
// for client Card generation
Card generateRandomCard();

char Card::DEFAULT_VAL = 'A';
Card::Suit Card::DEFAULT_SUIT = Card::spades;



// for comparisons -- ordering values and ranks
const char Card::valueRanks[NUM_CARD_VALS]   // const forces correct # initializers
= { '2', '3', '4', '5', '6', '7', '8', '9', 'T',
    'J', 'Q', 'K', 'A'};
const Card::Suit Card::suitRanks[NUM_CARD_SUITS] = {Card::clubs, Card::diamonds,
    Card::hearts, Card::spades};






// new global scope method -------------------------------------------
Card generateRandomCard()
{
    Card::Suit suit;
    char val;
    
    suit = (Card::Suit) ( rand() % Card::NUM_CARD_SUITS );
    val = Card::valueRanks[ rand() % Card::NUM_CARD_VALS ];
    
    return Card(val, suit);
}

// Card comparison method definitions -------------------------------------------
int Card::compareTo(Card &other)
{
    if (this->value == other.value)
        return ( getSuitRank(this->suit) - getSuitRank(other.suit) );
    // else
    return getValueRank(this->value) - getValueRank(other.value) ;
}

int Card::getSuitRank(Suit st)
{
    int k;
    
    for (k = 0; k < NUM_CARD_SUITS; k++)
        if (suitRanks[k] == st)
            return k;
    
    // should not happen
    return 0;
}

int Card::getValueRank(char val)
{
    int k;
    
    for (k = 0; k < NUM_CARD_VALS; k++)
        if (valueRanks[k] == val)
            return k;
    
    // should not happen
    return 0;
}


// global scope method prototypes
typedef list<Card> CardList;

void showList(CardList &myList);
void insert(CardList &myList, Card &x);
bool remove(CardList &myList, Card &x);
bool removeAll(CardList &myList, Card &x);


// Global method definitions --------------------------
void insert(CardList &myList, Card &x)
{
    list<Card>::iterator iter;
    
    // loop until we find a Card > x
    for (iter = myList.begin() ; iter != myList.end() ; iter++ )
    {
        if ( x < *iter )
            break;
    }
    // found the exact place for this float
    myList.insert(iter, x);
}

bool remove(CardList &myList, Card &x)
{
    list<Card>::iterator iter;
    
    // loop until we find or exhaust list
    for (iter = myList.begin() ; iter != myList.end() ; iter++ )
        if ( x == *iter )
        {
            myList.erase(iter);
            return true;
        }
    return false;
}

 bool removeAll(CardList &myList, Card &x)
{
 list<Card>::iterator iter;

 
 bool xInList = false;
    for(  iter = myList.begin(); iter != myList.end(); iter++ )
    {
        if(*iter == x)
        {
            remove(myList, *iter);
            xInList = true;
        }
    }

 return xInList;
 
 }

void showList(CardList &myList)
{
    list<Card>::iterator iter;
    
    cout << endl << "_____Here's the List_______" << endl;
    for( iter = myList.begin(); iter != myList.end(); iter++)
    {
        cout.setf(ios::fixed);
        cout.precision(3);
        cout << "[" << (*iter).toString() << "] ";
    }
    cout << endl << "_____That's all!_______" << endl << endl;
}

// main to test comparison mechanism and random card generation
int main()
{
    
    CardList testList;
    
    Card cards[10];
    
    for( int i = 0; i < 10; i++)
    {
        Card random = generateRandomCard();
        cards[i] = random;
        
    }
    
    
    for( int x = 0; x < 30; x++)
    {
        insert(testList,cards[(x % 10)]);
    }
    

    showList(testList);
    
    list<Card>::iterator iter;
    
  
    cout << "remove all " << cards[0].toString() << " and " << cards[2].toString()
         << " and " << cards[5].toString() << " (using remove): "  <<  endl;
    
    for(  iter = testList.begin(); iter != testList.end(); iter++ )
    {
        if(*iter ==  cards[0] )
        {
            remove(testList, *iter);
        }
        else if(*iter == cards[2])
        {
            remove(testList, *iter);
        }
        else if(*iter == cards[5])
        {
            remove(testList, *iter);
        }
      
    }
    
    showList(testList);
    

    cout << "removeAll should return 1 and remove " << cards[1].toString() << " : " << removeAll(testList, cards[1]) << endl;
    showList(testList);
    
    cout << "removeAll should return 0: ";
    cout << removeAll(testList, cards[1]) << endl;
    
}

/*
 _____Here's the List_______
 [2 of Spades] [2 of Spades] [2 of Spades] [5 of Clubs] [5 of Clubs] [5 of Clubs] [5 of Clubs] [5 of Clubs] [5 of Clubs] [6 of Spades] [6 of Spades] [6 of Spades] [7 of Clubs] [7 of Clubs] [7 of Clubs] [8 of Spades] [8 of Spades] [8 of Spades] [J of Spades] [J of Spades] [J of Spades] [Q of Clubs] [Q of Clubs] [Q of Clubs] [Q of Diamonds] [Q of Diamonds] [Q of Diamonds] [K of Hearts] [K of Hearts] [K of Hearts]
 _____That's all!_______
 
 remove all 6 of Spades and K of Hearts and Q of Clubs (using remove):
 
 _____Here's the List_______
 [2 of Spades] [2 of Spades] [2 of Spades] [5 of Clubs] [5 of Clubs] [5 of Clubs] [5 of Clubs] [5 of Clubs] [5 of Clubs] [7 of Clubs] [7 of Clubs] [7 of Clubs] [8 of Spades] [8 of Spades] [8 of Spades] [J of Spades] [J of Spades] [J of Spades] [Q of Diamonds] [Q of Diamonds] [Q of Diamonds]
 _____That's all!_______
 
 removeAll should return 1 and remove Q of Diamonds : 1
 
 _____Here's the List_______
 [2 of Spades] [2 of Spades] [2 of Spades] [5 of Clubs] [5 of Clubs] [5 of Clubs] [5 of Clubs] [5 of Clubs] [5 of Clubs] [7 of Clubs] [7 of Clubs] [7 of Clubs] [8 of Spades] [8 of Spades] [8 of Spades] [J of Spades] [J of Spades] [J of Spades]
 _____That's all!_______
 
 removeAll should return 0: 0
 Program ended with exit code: 0
 */









