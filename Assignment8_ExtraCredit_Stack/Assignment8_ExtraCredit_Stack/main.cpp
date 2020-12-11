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
    bool pop();
    
    
    // demonstrating difference between having tail pointer or not
   
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
void LinkedList::push(int data) {// adding tail functionality
   bool firstNode = false;
    if (head==nullptr)
    {
        firstNode = true;
    }
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = head;
    head = newNode;
    if (firstNode)
    {
        tail = head;
    }
    
}
bool LinkedList::pop()
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


int main(int argc, const char * argv[]) {
    
    LinkedList myList;
    cout << "case 1(empty):" << endl;
    myList.printAllNodes();
    cout << "case 2(1 node):" << endl;
    myList.push(5);
    myList.printAllNodes();
    cout << "case 3( >1 node):" << endl;
    myList.push(4);
    myList.printAllNodes();
    myList.push(3);
    myList.printAllNodes();
    
    cout << "test dequeue" << endl;
    
    myList.pop();
    myList.printAllNodes();
    
    cout << "test dequeue" << endl;
    
    myList.pop();
    myList.printAllNodes();
    
    cout << "test dequeue" << endl;
    
    myList.pop();
    myList.printAllNodes();
    
   
    cout << "case 1(empty):" << endl;
    myList.printAllNodes();
    cout << "test enqueue :" << endl;
    myList.push(11);
    myList.printAllNodes();
    cout << "test enqueue :" << endl;
    cout << "case 2(1 node):" << endl;
    myList.push(10);
    myList.printAllNodes();
    cout << "test enqueue :" << endl;
    cout << "case 3( >1 node):" << endl;
    myList.push(9);
    myList.printAllNodes();
    cout << "test enqueue :" << endl;
    myList.push(8);
    myList.printAllNodes();
    
    cout << "test dequeue" << endl;
    
    myList.pop();
    myList.printAllNodes();
    
    cout << "test dequeue" << endl;
    
    myList.pop();
    myList.printAllNodes();
    
    cout << "test dequeue" << endl;
    
    myList.pop();
    myList.printAllNodes();
    cout << "test dequeue" << endl;
    myList.pop();
    myList.printAllNodes();
    cout<< "try dequeue on empty list" << endl;
    
    myList.pop();
    myList.printAllNodes();
    
    
    LinkedList myList2;
    cout << "print case 1(empty):" << endl;
    myList2.printAllNodes();
    cout << " print case 2(1 node):" << endl;
    myList2.push(5);
    myList2.printAllNodes();
    cout << "print case 3( >1 node):" << endl;
    myList2.push(4);
    myList2.printAllNodes();
    myList2.push(3);
    myList2.printAllNodes();
    
    cout << "testing copy constructor" << endl;
    LinkedList myList3(myList2);
    myList3.printAllNodes();
    
    
}

