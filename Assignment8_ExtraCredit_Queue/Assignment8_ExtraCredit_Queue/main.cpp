//
//  main.cpp
//  Assignment8_CS2b
//
//  Created by Omer Katz on 6/5/18.
//  Copyright © 2018 Omer Katz. All rights reserved.
//

#include <iostream>

using namespace std;

struct Node {
    int data;
    Node *next;
    
    
};

class LinkedList {
    
private:
    Node* head;
    Node* tail;
    void deleteAllNodes();
    
public:LinkedList();
    virtual ~LinkedList();
    LinkedList& operator=(const LinkedList& rhs);
    LinkedList(const LinkedList& listToCopy);
    void printAllNodes() const;
    void push(int data);
    bool dequeue();
    
    
    // demonstrating difference between having tail pointer or not
    void enqueue(int data);
    //bool removeAtEnd();
    void cleanList();
    
    
};

LinkedList::LinkedList()
{
    head = nullptr;
    tail = nullptr;
    
    
}
LinkedList::~LinkedList() {
    deleteAllNodes();
    
}

void LinkedList::deleteAllNodes() {
    Node* curr = head;
    Node* tmp;
    while (curr != nullptr)
    {
        tmp = curr->next;
        delete curr;
        curr = tmp;
    }
    head = nullptr;
    tail = nullptr;
}
LinkedList& LinkedList::operator=(const LinkedList& rhs)
{
    if (head != rhs.head)
    {
        deleteAllNodes();
        Node* rhsCurr = rhs.head;
        while (rhsCurr != nullptr) {
            Node* newNode = new Node;
            newNode->data = rhsCurr->data;
            newNode->next = nullptr;
            if (head==nullptr) // empty list case
                head = newNode;
            if (tail!=nullptr) //
                tail->next = newNode;
            tail = newNode;;
            rhsCurr = rhsCurr -> next;
            
        }
        
    }return *this;
}
LinkedList::LinkedList(const LinkedList& listToCopy)
{//  deleteAllNodes is safe for empty lists
    head = nullptr;
    tail = nullptr;
    * this = listToCopy;
    
}

bool LinkedList::dequeue()
{
    if (head==nullptr)
    {
        return false;
    }
    Node* tmp;
    tmp = head;
    head = head -> next;
    if (tmp==tail) // length is one Node
    {
        tail = nullptr;
    }
    delete tmp;
    return true;
}

 void LinkedList::enqueue(int data)
 {
 Node* newNode = new Node;
 newNode->data = data;
 newNode->next = nullptr;
 if (head==nullptr) // empty list case
 head = newNode;
 if (tail!=nullptr) //
 tail->next = newNode;
 tail = newNode;
 
 
 }

void LinkedList::printAllNodes() const {
    cout << "printing list: " << endl;
    Node* current = head;
    if (head!=nullptr)
    {
        cout << "head node is: " << head->data << endl;
        while(current != nullptr)
        {
            cout << current->data << " ";
            current = current->next;
            
        }
        cout << endl;
        
    }
    else
    {
        cout << "head is null" << endl;
    }
    if (tail!=nullptr)
    {
        cout << "tail node is: " << tail->data << endl;
    }
    else
    {
        cout << "tail is null" << endl;
    }
    cout << endl;
    
}



/*
int main(int argc, const char * argv[]) {
    LinkedList myList;
    cout << "print case 1(empty):" << endl;
    myList.printAllNodes();
    cout << " print case 2(1 node):" << endl;
    myList.enqueue(5);
    myList.printAllNodes();
    cout << "print case 3( >1 node):" << endl;
    myList.enqueue(4);
    myList.printAllNodes();
    myList.enqueue(3);
    myList.printAllNodes();
    
    cout << "test dequeue" << endl;
    
    myList.dequeue();
    myList.printAllNodes();
    
    cout << "test dequeue" << endl;
    
    myList.dequeue();
    myList.printAllNodes();
    
    cout << "test dequeue" << endl;
    
    myList.dequeue();
    myList.printAllNodes();
    

   
    cout << "test enqueue :" << endl;
    myList.enqueue(11);
    myList.printAllNodes();

    cout << "test enqueue :" << endl;
    myList.enqueue(10);
    myList.printAllNodes();
    
    cout << "test enqueue :" << endl;
    
    myList.enqueue(9);
    myList.printAllNodes();
    
    cout << "test enqueue :" << endl;
    myList.enqueue(8);
    myList.printAllNodes();

    cout << "test dequeue" << endl;
    
    myList.dequeue();
    myList.printAllNodes();
    
    cout << "test dequeue" << endl;
    
    myList.dequeue();
    myList.printAllNodes();
    
    cout << "test dequeue" << endl;
    
    myList.dequeue();
    myList.printAllNodes();
    
    cout << "test dequeue" << endl;
    
    myList.dequeue();
    myList.printAllNodes();

    cout<< "try dequeue on empty list" << endl;
    
    myList.dequeue();
    myList.printAllNodes();
    
    LinkedList myList2;
    cout << "print case 1(empty):" << endl;
    myList2.printAllNodes();
    cout << " print case 2(1 node):" << endl;
    myList2.enqueue(5);
    myList2.printAllNodes();
    cout << "print case 3( >1 node):" << endl;
    myList2.enqueue(4);
    myList2.printAllNodes();
    myList2.enqueue(3);
    myList2.printAllNodes();
    
    cout << "testing copy constructor" << endl;
    LinkedList myList3(myList2);
    myList3.printAllNodes();
 

}
*/

