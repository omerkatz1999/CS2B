/*
 
  main.cpp
  CS2b_Assignment4_Omer

  Created by Omer Katz on 4/30/18.

 a. yes a retailer account does have a name, because it is the child of
       the bank account class, which has a name. However it cannot call it because
       it is private.
 
 b. yes a retailer account does have a balance data member, because it is the child of
 the bank account class, which has a balance.

 c. protected members can be called directly, but private data members can only be called using an accessor.
 
 d. if the BuyerAccount’s purchase method had the seller parameter passed by value rather than by reference
       then the seller accounts balance would not have changed because it would only make a copy of the object.

 e. chaining constructors allows us to initialize every parameter just once. The entire reason to chain constructors
    is to not need to repeat every constructor method when we can just apply the parent's constructor to the child class'
    constructor.
 
 */

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// prototypes ----------------------------------------------------
class BankAccount
{
public:
    static const  int MIN_BALANCE = 0;
    static const string DEFAULT_NAME;
    BankAccount(int balance = MIN_BALANCE, string name = DEFAULT_NAME);
    string getName() const;
    int getBalance() const;
    bool setName(const string& name);
    bool deposit(int amount);
    bool withdraw(int amount);
    string toString();
    
protected:
    int balance;
    bool isValidName(const string& name);
    bool isValidAmount(int amount);
    
private:
    string name;
    
};
const string BankAccount:: DEFAULT_NAME = "undefined";

BankAccount::BankAccount(int balance, string name)
{
    if( isValidAmount(balance))
    {
        this-> balance = balance;
    }
    else
    {
        this-> balance = MIN_BALANCE;
    }
    
    setName(name);
    
}



string BankAccount:: getName() const
{
    return name;
}



int BankAccount:: getBalance() const
{
    return balance;
}



bool BankAccount:: setName(const string& name)
{
  if(isValidName(name))
  {
    this-> name = name;
    return true;
  }
  else
  {
    this-> name = DEFAULT_NAME;
    return false;
  }
  
}



bool BankAccount:: isValidName(const string& name)
{
    if( name.length() >=2 && name.length() <= 50 )
    {
        return true;
    }
    else
    {
        return false;
    }
    
}



bool BankAccount:: deposit(int amount)
{
    if(isValidAmount(amount))
    {
        balance += amount;
        return true;
    }
    else
    {
        return false;
    }
}



bool BankAccount:: withdraw(int amount)
{
    if(isValidAmount(amount))
    {
        balance -= amount;
        return true;
    }
    return false;
}



bool BankAccount:: isValidAmount(int amount)
{
    if( amount <= balance && amount > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}



string BankAccount:: toString()
{
    ostringstream balanceString;
    balanceString << balance;
    string balanceS = balanceString.str();
    string s = "My name is " + name + " and my balance is " + balanceS + " dollars.";
    return s;
}



class RetailerAccount;


class BuyerAccount : public BankAccount
{
    
public:
    BuyerAccount(int balance = MIN_BALANCE, string name = DEFAULT_NAME);
    bool purchase(int price, RetailerAccount& seller);
    string toString();
    
};

class RetailerAccount : public BankAccount
{
public:
    static const string DEFAULT_NAME;
    RetailerAccount(int balance = MIN_BALANCE, string name = DEFAULT_NAME, string product = DEFAULT_NAME);
    string getProduct()const;
    bool setProduct(string product);
    bool sale(int price, BuyerAccount& buyer);
    string toString();
    
private:
    string product;
    
};

BuyerAccount:: BuyerAccount(int balance , string name)
: BankAccount(balance , name)
{
    
}



string BuyerAccount:: toString()
{
    string s = "Buyer: ";
    string s2 = BankAccount:: toString();
    return  s+s2;
}



bool BuyerAccount:: purchase(int price, RetailerAccount &seller)
{
    if( balance > price && price > 0)
    {
        withdraw(price);
        seller.deposit(price);
        return true;
    }
    else
    {
        return false;
    }
}



const string RetailerAccount:: DEFAULT_NAME = "undefined";

RetailerAccount:: RetailerAccount(int balance , string name, string product)
: BankAccount(balance , name)
{
    this-> product = product;
}



bool RetailerAccount:: setProduct(string product)
{
    if( product.length() >= 2 && product.length() <= 50)
    {
        this-> product = product;
        return true;
    }
    else
    {
        return false;
    }
}


string RetailerAccount:: getProduct() const
{
    return product;
}



bool RetailerAccount:: sale(int price, BuyerAccount& buyer)
{
    if( buyer.getBalance() > price && price > 0)
    {
        buyer.withdraw(price);
        deposit(price);
        return true;
    }
    else
    {
        return false;
    }
}



string RetailerAccount:: toString()
{
    ostringstream balanceString;
    balanceString << balance;
    string balanceS = balanceString.str();
    
    string s = "Retailer: The name of our Business is " + getName() + ", we sell ";
    
    string s2 = product + " and our balance is " + balanceS + " dollars.";
    
    return s + s2;
    
}




int main(int argc, const char * argv[]) {
    
    
    BankAccount b1(35);
    cout << b1.getName() << endl;
    cout << b1.getBalance() << endl;
    b1.setName("Carlos");
    b1.deposit(15);
    b1.withdraw(5);
    cout << b1.toString() << endl << endl;
    
    BuyerAccount buyer(500, "Phuong");
    cout << buyer.toString() << endl << endl;
    RetailerAccount retailer(0, "Chocolate Shop", "chocolate");
    cout << retailer.toString() << endl << endl;
    buyer.purchase(50, retailer);
    cout << "After a purchase: " << endl;
    cout << buyer.toString() << endl;
    cout << retailer.toString() << endl << endl;
    retailer.sale(100, buyer);
    cout << "After a sale: " << endl;
    cout << buyer.toString() << endl;
    cout << retailer.toString() << endl << endl;
    buyer.withdraw(350);
    cout << "After withdrawal: " << endl;
    cout << buyer.toString() << endl << endl;
    retailer.sale(50, buyer);
    cout << "After attempted sale: " << endl;
    cout << buyer.toString() << endl;
    cout << retailer.toString() << endl << endl;
    
    b1.deposit(1000);
    cout << b1.toString() << endl;
    
    b1.deposit(-1);
    cout << "After a deposit of -1: " << endl;
    cout << b1.toString() << endl << endl;
    
    
    b1.withdraw(-1);
    cout << "After a withdraw of -1: " << endl;
    cout << b1.toString() << endl << endl;
    
    
    cout << buyer.toString() << endl;
    
    
    retailer.sale(-1, buyer);
    cout << "After a sale of -1: " << endl;
    cout << buyer.toString() << endl;
    cout << retailer.toString() << endl;
    
    buyer.purchase(-1, retailer);
    cout << "After a purchase of -1: " << endl;
    cout << retailer.toString() << endl;
    cout << buyer.toString() << endl << endl;
    
    BankAccount bank(-1, "i");
    cout << bank.getName() << endl;
    cout << bank.getBalance() << endl;
    
    BankAccount bank2( 0, "ii");
    cout << bank2.getName() << endl;
    cout << bank2.getBalance() << endl;
 
    BankAccount b4;
    cout << b4.getName() << endl;
    cout << b4.getBalance() << endl;
    
  
    
}

