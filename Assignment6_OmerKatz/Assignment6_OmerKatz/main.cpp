//
//  main.cpp
//  Assignment6_OmerKatz
//
//  Created by Omer Katz on 5/15/18.
//  Copyright © 2018 Omer Katz. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <ctype.h>
using namespace std;



class BooleanFunc{
    
   static const int MAX_TABLE_FOR_CLASS = 65536;
   static const int DEFAULT_TABLE_SIZE = 16;
    
private:
    
    int tableSize;
    bool *truthTable;
    bool evalReturnIfError;
    bool evalTrack = false;
    bool state;
    void initializeTable(bool initialValue);
    bool isValidInput(int input);
public:
    
    BooleanFunc( int tableSize = DEFAULT_TABLE_SIZE, bool evalReturnIfError = false );
    BooleanFunc( const BooleanFunc & copyObject);
    virtual ~BooleanFunc();
    bool setTruthTableUsingTrue( int inputsThatProduceTrue[], int arraySize );
    bool setTruthTableUsingFalse( int inputsThatProduceFalse[], int arraySize );
    bool eval(int input);
    bool getState();
    BooleanFunc &operator= (const BooleanFunc& a);
   
    
};

 



//constructor
BooleanFunc:: BooleanFunc(int tableSize, bool evalReturnIfError)
{
    if( tableSize <= MAX_TABLE_FOR_CLASS && tableSize >= 0)
    {
        this->tableSize = tableSize;
    }
    else
    {
        this->tableSize = DEFAULT_TABLE_SIZE;
    }
    
    this->evalReturnIfError = evalReturnIfError;
    
    truthTable = new bool[tableSize];

  
}

//copy constructor
BooleanFunc:: BooleanFunc( const BooleanFunc & copyObject)
{
    truthTable = NULL;
    *this = copyObject;
}


//destructor
BooleanFunc:: ~BooleanFunc()
{
    delete [] truthTable;
}

//assignment operator
BooleanFunc & BooleanFunc:: operator=( const BooleanFunc& original)
{
    if( this == &original)
    {
        return *this;
    }
  
    delete [] truthTable;
   
    this->tableSize = original.tableSize;
    this->evalReturnIfError = original.evalReturnIfError;
    
    truthTable = new bool[tableSize];
    for (int i = 0; i < tableSize; i++)
    {
        truthTable[i] = original.truthTable[i];
    }
    
    return *this;
    
}


bool BooleanFunc:: setTruthTableUsingTrue( int inputsThatProduceTrue[], int arraySize )
{
    if( !isValidInput(arraySize-1))
    {
        return false;
    }
    initializeTable(false);
    
    for (int i = 0; i < arraySize; i++)
    {
        if(isValidInput(inputsThatProduceTrue[i]) )
        {
            truthTable[inputsThatProduceTrue[i]] = true;
        }
    }
    return true;
    
    
}


bool BooleanFunc:: setTruthTableUsingFalse( int inputsThatProduceTrue[], int arraySize )
{
    if( !isValidInput(arraySize-1))
    {
        return false;
    }
    
    initializeTable(true);
    
    for (int i = 0; i < arraySize; i++)
    {
        if(isValidInput(inputsThatProduceTrue[i]) )
        {
            truthTable[inputsThatProduceTrue[i]] = false;
        }
    }
    return true;
    
}


bool BooleanFunc:: eval(int input)
{
    
    if(isValidInput(input))
    {
      evalTrack = true;
      state = truthTable[input];
    }
    else
    {
        evalTrack = false;
        return evalReturnIfError;
    }
    return state;
    
}


bool BooleanFunc:: getState()
{
    if(!evalTrack)
    {
        return evalReturnIfError;
    }
    return state;
}

void BooleanFunc::initializeTable(bool initialValue)
{
    for (int i = 0; i<tableSize; i++)
    {
        truthTable[i] = initialValue;
    }
}

bool BooleanFunc::isValidInput(int input)
{
    if (input < tableSize && input>= 0)
    {
         return true;
    }
    
    return false;
}


class MultiSegmentLogic {
    
protected:
    int numSegs;
    BooleanFunc *segs;
    static bool greaterThanZero(int num);
    
public:
    MultiSegmentLogic( int numSegs = 0);
    bool setNumSegs(int numSegs);
    bool setSegment( int segNum, BooleanFunc &funcForThisSeg);
    void eval( int input);
    MultiSegmentLogic( const MultiSegmentLogic & objectCopied);
    virtual ~MultiSegmentLogic();
    MultiSegmentLogic &operator= (const MultiSegmentLogic& rightSide);
    
};

//constructor
MultiSegmentLogic:: MultiSegmentLogic(int numSegs)
{
    if( setNumSegs(numSegs))
    {
        this-> numSegs = numSegs;
    }
    else
    {
        numSegs = 0;
        segs = new BooleanFunc[numSegs];
    }
    
    
    
}

//equals overloaded
MultiSegmentLogic & MultiSegmentLogic:: operator= ( const MultiSegmentLogic & rightSide)
{
    if( this == & rightSide)
    {
        return *this;
    }
    
    delete [] segs;
    this-> numSegs = rightSide.numSegs;
    
    segs = new BooleanFunc[numSegs];
    for (int i = 0; i < numSegs; i++)
    {
        segs[i] = rightSide.segs[i];
    }
    
    return *this;
    
}

//copyConstructor
MultiSegmentLogic:: MultiSegmentLogic( const MultiSegmentLogic & copy)
{
    segs = NULL;
    *this = copy;
}

//destructor
MultiSegmentLogic:: ~MultiSegmentLogic()
{
    delete [] segs;
}


//helper function
bool MultiSegmentLogic:: greaterThanZero( int num)
{
    if ( num >= 0)
    {
        return true;
    }
    else return false;
}

//setters
bool MultiSegmentLogic:: setNumSegs(int numSegs)
{
    if ( greaterThanZero(numSegs))
    {
        
        this->numSegs = numSegs;
        
    
        delete [] segs;
        
        segs = new BooleanFunc[numSegs];
        return true;
    }
    else return false;

}

bool MultiSegmentLogic:: setSegment(int segNum, BooleanFunc &funcForThisSeg)
{
    if( greaterThanZero(segNum))
    {
        segs[segNum] = funcForThisSeg;
        return true;
    }
    else return false;
    
}

void MultiSegmentLogic:: eval(int input)
{
    for( int i = 0 ; i < numSegs; i++)
    {
        segs[i].eval(input);
    }
}


class SevenSegmentLogic : public MultiSegmentLogic{
    
public:
    SevenSegmentLogic();
    bool getValOfSeg( int seg );
    
private:
    void setSegment( int k, const BooleanFunc & bFunc);
    void loadBoolFunc();
    bool loadFunc = false;
   
    
};


SevenSegmentLogic:: SevenSegmentLogic(): MultiSegmentLogic(7)
{
    if(!loadFunc)
    {
        loadBoolFunc();
    }
    
}

bool SevenSegmentLogic:: getValOfSeg( int seg)
{
    if( seg >= 0 && seg < 7)
    {
        return segs[seg].getState();
    }
    else
    {
        return false;
    }
}

void SevenSegmentLogic:: setSegment( int k, const BooleanFunc & bFunc)
{
    segs[k] = bFunc;
}




void SevenSegmentLogic:: loadBoolFunc()
{
    loadFunc = true;
    BooleanFunc arrayBoolFunc[7];
    
   static int A[] = { 0, 2,3,5,6,7,8,9,10,12,14,15};
   static int B[] = { 0,1,2,3,4,7,8,9,10,13};
   static int C[] = { 0,1,3,4,5,6,7,8,9,10,11,13};
   static int D[] = { 0,2,3,5,6,8,11,12,13,14};
   static int E[] = { 0,2,6,8,10,11,12,13,14,15};
   static int F[] = { 0,4,5,6,8,9,10,11,12,14,15};
   static int G[] = { 2,3,4,5,6,8,9,10,11,13,14,15};
    
    
    
    arrayBoolFunc[0].setTruthTableUsingTrue(A, 12);
    arrayBoolFunc[1].setTruthTableUsingTrue(B, 10);
    arrayBoolFunc[2].setTruthTableUsingTrue(C, 12);
    arrayBoolFunc[3].setTruthTableUsingTrue(D, 10);
    arrayBoolFunc[4].setTruthTableUsingTrue(E, 10);
    arrayBoolFunc[5].setTruthTableUsingTrue(F, 11);
    arrayBoolFunc[6].setTruthTableUsingTrue(G, 12);
    
    for(int i = 0; i < numSegs; i++ )
    {
        setSegment(i, arrayBoolFunc[i]);
    }
}


class SevenSegmentImage
{
    
public:
    static const int MIN_HEIGHT = 5;
    static const int MIN_WIDTH = 5;
    static const int MAX_HEIGHT = 65;
    static const int MAX_WIDTH = 41;
    static const string DRAW_CHAR;
    static const string BLANK_CHAR;
    
private:
    bool **data;
    int topRow, midRow, bottomRow, leftCol, rightCol;
    
public:
    SevenSegmentImage( int width = MIN_WIDTH, int height = MIN_HEIGHT );
    virtual ~SevenSegmentImage()
    {
        deallocateArray();
    }
    void clearImage();
    bool turnOnCellsForSegment( char segment );
    bool setSize( int width, int height );
    void display();
    
    // deep copy stuff
    SevenSegmentImage( const SevenSegmentImage &tdi );
    const SevenSegmentImage &operator=(const SevenSegmentImage &rhs);
    
private:
    static bool validateSize( int width, int height );
    void allocateCleanArray();
    void deallocateArray();
    
   
};
const string SevenSegmentImage::DRAW_CHAR = "*";
const string SevenSegmentImage::BLANK_CHAR = " ";



 SevenSegmentImage:: SevenSegmentImage( int width , int height )
{
    if(validateSize(width, height))
    {
        setSize(width, height);
       
    }
    else
    {
        setSize(MIN_WIDTH, MIN_HEIGHT);
        
        topRow = MIN_WIDTH;
        midRow = MIN_WIDTH;
        bottomRow = MIN_WIDTH;
        leftCol = MIN_HEIGHT;
        rightCol = MIN_HEIGHT;
        
        data = new bool* [MIN_HEIGHT];
        
        for( int i = 0; i < MIN_HEIGHT; i++)
        {
            data[i] =  new bool [MIN_WIDTH];
        }
        
    }
    
   
    
}

SevenSegmentImage:: SevenSegmentImage(SevenSegmentImage const &original)
{
    data = NULL;
    *this = original;
}


const SevenSegmentImage & SevenSegmentImage:: operator= (const SevenSegmentImage &rhs)
{
    if( this != &rhs)
    {
    
        deallocateArray();
        
        this->topRow = rhs.topRow;
        this->midRow = rhs.midRow;
        this->bottomRow = rhs.topRow;
        this->leftCol = rhs.leftCol;
        this->rightCol = rhs.rightCol;
        
        allocateCleanArray();
    }
    
    return *this;
}

void SevenSegmentImage:: clearImage()
{
    for (int row = 0; row < leftCol; row++)
    {
        for (int col = 0; col < topRow; col++)
        {
            data[row][col] = false;
            
        }
        
    }
}


bool SevenSegmentImage:: setSize( int width, int height )
{
    if(!validateSize(width, height) || height % 2 == 0)
    {
        return false;
    }
    
   
    delete[] data;
    
    
    
    topRow = width;
    midRow = width;
    bottomRow = width;
    leftCol = height;
    rightCol = height;
    
    data = new bool* [leftCol];
    
    for( int i = 0; i < leftCol; i++)
    {
        data[i] =  new bool [topRow];
    }
    clearImage();
    
    return true;
}


bool SevenSegmentImage:: turnOnCellsForSegment( char segment )
{
    char x = toupper(segment);
    
    if(!( x == 'A' || x == 'B' || x == 'C' || x == 'D' ||
         x == 'E' || x == 'F' || x == 'G' ))
    {
        return false;
    }
    
    if( x == 'A' )
    {
        for(int col = 0; col < topRow; col++ )
        {
            data [0][col] = true;
        }
    }
    
    else if ( x == 'B' )
    {
        for(int row = 0; row < int(rightCol/2)+1; row++ )
        {
            data [row][topRow-1] = true;
        }
    }
    else if ( x == 'C' )
    {
        for(int row = int((rightCol/2)+1); row < rightCol; row++ )
        {
            data [row][topRow-1] = true;
        }
    }
    else if( x == 'D' )
    {
        for(int col = 0; col < bottomRow; col++ )
        {
            data [leftCol-1][col] = true;
        }
    }
    else if( x == 'E' )
    {
        for(int row = int((rightCol/2)); row < leftCol; row++ )
        {
            data [row][0] = true;
        }
    }
    if( x == 'F' )
    {
        for(int row = 0; row < int(rightCol/2)+1; row++ )
        {
            data [row][0] = true;
        }
    }
    else if( x == 'G' )
    {
        for(int col = 0; col <= topRow; col++ )
        {
            data [int(leftCol/2)][col] = true;
        }
        
    }
    
    return true;
    
}

void SevenSegmentImage:: display()
{
    for (int row = 0; row < leftCol; row++)
    {
        for (int col = 0; col < topRow; col++)
        {
           if( data[row][col])
           {
            cout << DRAW_CHAR<< " " ;
           }
            else
                cout << BLANK_CHAR<< " " ;
            
        }
        
        cout << endl;
        
    }
}



bool SevenSegmentImage:: validateSize( int width, int height )
{
    if( width >=MIN_WIDTH && width <= MAX_WIDTH && height>=MIN_HEIGHT && height <= MAX_HEIGHT  )
    {
        return true;
    }
    else return false;

}


void SevenSegmentImage:: allocateCleanArray()
{
    data = new bool* [rightCol];
    
    for( int i = 0; i < rightCol; i++)
    {
        data[i] = new bool [topRow];
    }
}


void SevenSegmentImage:: deallocateArray()
{
    for(int i = 0; i < rightCol; i++)
    {
        delete [] data[i];
    }
    delete data;
}






class SevenSegmentDisplay
{
private:
    SevenSegmentImage theImage;
    SevenSegmentLogic theDisplay;
    
public:
    SevenSegmentDisplay(
                        int width = SevenSegmentImage::MIN_WIDTH,
                        int height = SevenSegmentImage::MIN_HEIGHT
                        );
    bool setSize( int width, int height );
    void loadConsoleImage();
    void consoleDisplay();
    void eval( int input );
};

SevenSegmentDisplay:: SevenSegmentDisplay(int width , int height)
{
    if(!setSize(width, height))
    {
        setSize(theImage.MIN_WIDTH, theImage.MIN_HEIGHT);
    }
    else{
        theImage.setSize( width,  height);
    }
}

bool SevenSegmentDisplay:: setSize( int width, int height)
{
    return theImage.setSize( width, height);
    
}

void SevenSegmentDisplay:: loadConsoleImage()
{
    theImage.clearImage();
    
    char segmentLetter [7] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    
    for( int i = 0; i < 7; i++)
    if( theDisplay.getValOfSeg(i))
    {
        theImage.turnOnCellsForSegment(segmentLetter[i]);
    }
}

void SevenSegmentDisplay:: consoleDisplay()
{
    theImage.display();
}

void SevenSegmentDisplay:: eval(int input)
{
    
        theDisplay.eval( input );
    
}






int main(int argc, const char * argv[]) {
  

    
    
    SevenSegmentDisplay my7SegForCon( 15, 13 );
    

    
    my7SegForCon.setSize( 5, 5 );
    for ( int j = 0; j < 16; j++ )
    {
        my7SegForCon.eval( j );
        my7SegForCon.loadConsoleImage();
        my7SegForCon.consoleDisplay();
        cout << endl << endl << endl;
    }
    
    my7SegForCon.setSize( 11, 11 );
    for ( int j = 0; j < 16; j++ )
    {
        my7SegForCon.eval( j );
        my7SegForCon.loadConsoleImage();
        my7SegForCon.consoleDisplay();
        cout << endl << endl << endl;
    }
    
    my7SegForCon.setSize( 5, 5 );
    for ( int j = 0; j < 16; j++ )
    {
        my7SegForCon.eval( j );
        my7SegForCon.loadConsoleImage();
        my7SegForCon.consoleDisplay();
        cout << endl << endl << endl;
    }
    
    my7SegForCon.setSize( 18, 12 );
    for ( int j = 0; j < 16; j++ )
    {
        my7SegForCon.eval( j );
        my7SegForCon.loadConsoleImage();
        my7SegForCon.consoleDisplay();
        cout << endl << endl << endl;
    }
    
    my7SegForCon.setSize( 18, 13 );
    for ( int j = 0; j < 16; j++ )
    {
        my7SegForCon.eval( j );
        my7SegForCon.loadConsoleImage();
        my7SegForCon.consoleDisplay();
        cout << endl << endl << endl;
    }
    
    my7SegForCon.setSize( 0, 0 );
    for ( int j = 0; j < 16; j++ )
    {
        my7SegForCon.eval( j );
        my7SegForCon.loadConsoleImage();
        my7SegForCon.consoleDisplay();
        cout << endl << endl << endl;
    }
    cout << "copy" << endl;
    
    SevenSegmentDisplay myCopy(my7SegForCon );
    for ( int j = 0; j < 16; j++ )
    {
        myCopy.eval( j );
        myCopy.loadConsoleImage();
        myCopy.consoleDisplay();
        cout << endl << endl << endl;
    }
    
    
   SevenSegmentDisplay test( 7, 7 );

   
  
    
    for ( int j = 0; j < 16; j++ )
    {
        test.eval( j );
        test.loadConsoleImage();
        test.consoleDisplay();
        cout << endl << endl << endl;
    }
    
    SevenSegmentDisplay test1(6);
    cout << "test = test" << endl;
    for ( int j = 0; j < 16; j++ )
    {
        test1.eval( j );
        test1.loadConsoleImage();
        test1.consoleDisplay();
        cout << endl << endl << endl;
    }
    test1 = test;
    
    for ( int j = 0; j < 16; j++ )
    {
        test1.eval( j );
        test1.loadConsoleImage();
        test1.consoleDisplay();
        cout << endl << endl << endl;
    }
    
    
}










