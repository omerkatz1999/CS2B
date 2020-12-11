/*
 //  main.cpp
 //  Assignment8_CS2b
 //
 //  Created by Omer Katz on 6/5/18.
 //  Copyright © 2018 Omer Katz. All rights reserved.
 //
 // The remove function with the tail is much more useful during soft
 // delete because all it has to do is
 // mark the boolean deleted true, where in hard delete when actually removing we need to
 // track with another pointer the location of the second to
 // last node by going through every node in the
 // list (until the second to last one) in order
 // to set it to become the new tail and its next to be null
 */

#include <iostream>

using namespace std;

struct Node {
    int data;
    Node *next;
    bool deleted = false;
    
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
    void insertAtFront(int data);
    bool removeAtFront();
    
    
    // demonstrating difference between having tail pointer or not
    void insertAtEnd(int data);
    bool removeAtEnd();
    void cleanList();
    int numNodes;
    int numNodesExisting;
    
};
LinkedList::LinkedList()
{
    head = nullptr;
    tail = nullptr;
    numNodes = 0;
    numNodesExisting = 0;
    
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
        while (rhsCurr != nullptr)
        {
            insertAtEnd(rhsCurr->data);
            tail->deleted = rhsCurr->deleted; // added code check later
            rhsCurr = rhsCurr -> next;
            
        }
        
    }
    numNodes = rhs.numNodes;
    numNodesExisting = rhs.numNodesExisting;
    return *this;
    
}
LinkedList::LinkedList(const LinkedList& listToCopy)
{//  deleteAllNodes is safe for empty lists
    head = nullptr;
    tail = nullptr;
    * this = listToCopy;
    
}
void LinkedList::insertAtFront(int data) {// adding tail functionality
    bool firstNode = false;
    if (head==nullptr)
    {
        firstNode = true;
    }
    Node* newNode = new Node;
    newNode->data = data;
    newNode-> deleted = false;
    newNode->next = head;
    head = newNode;
    if (firstNode)
    {
        tail = head;
    }
    
    numNodesExisting++;
    numNodes++;
    
}
bool LinkedList::removeAtFront()
{
    if (head == nullptr || (head->deleted) == true)
    {
        return false;
    }
  
    if (head == tail) // length is one Node
    {
        head->deleted = true;
    }
    head->deleted = true;
    numNodes--;
    return true;
    
}

void LinkedList::insertAtEnd(int data)
{
    Node* newNode = new Node;
    newNode->data = data;
    newNode-> deleted = false;
    newNode->next = nullptr;
    if (head==nullptr) // empty list case
        head = newNode;
    if (tail!=nullptr) //
        tail->next = newNode;
    tail = newNode;
    numNodesExisting++;
    numNodes++;
    
}
// This method makes use of tail
bool LinkedList::removeAtEnd()
{
    // not much difference; we still have to get the second to last node
    if( head == nullptr)
    {
        return false;
    }
    else if(tail->deleted == true)
    {
        return false;
    }
    else if (head->next == nullptr)
    { // length 1
        head-> deleted = true;
        tail = nullptr;
        numNodes--;
        
    }
    else
    { // definitely 2 or more Nodes
        tail->deleted = true;
        numNodes--;
        
    }
    return true;
    
}
void LinkedList::printAllNodes() const {
    cout << "printing list with numNodes " << numNodes << " and numNodesExisting " << numNodesExisting << endl;
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


void LinkedList:: cleanList()
{
    if(head == nullptr) //case 0 nodes
    {
        return;
    }
    else if(head->next == nullptr ) // case 1 node
    {
        if(head-> deleted == true)
        {
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            tail = head;
        }
        
    }
    else //more than 1
    {
        Node* tmp = head;
        Node* tmpNext = head->next;
        
        while(head->deleted == true)
        {
            if(tmpNext != nullptr)
            {
                delete head;
                head = tmpNext;
                tmp = tmpNext;
                tmpNext = tmpNext->next;
            }
            else
            {
                head = nullptr;
                tail = nullptr;
            }
                
        }
        
        while(tmpNext-> next != nullptr )
        {
            if(tmpNext-> deleted == true)
            {
                Node * newtmpNext = tmpNext->next;
                delete tmpNext;
                tmp->next = newtmpNext;
                tmpNext = newtmpNext;
                //delete newtmpNext;
              
            }
            else
            {
                tmp = tmpNext;
                tmpNext = tmpNext->next;
            }
            
        }
        if( tmpNext-> deleted == true)
        {
            delete tmpNext;
            tmp->next = nullptr;
            tail = tmp;
        }
        else
        {
            tail = tmpNext;
        }
    }
    
    numNodesExisting = numNodes;
}

/*
int main(int argc, const char * argv[]) {
   
    
    
    LinkedList emptyList;
    emptyList.removeAtFront();
    emptyList.removeAtEnd();
    emptyList.cleanList();
    cout << "empty list:" << endl;
    emptyList.printAllNodes();
    
    emptyList.insertAtFront(5);
    emptyList.removeAtFront();
    emptyList.removeAtEnd();
    emptyList.cleanList();
    cout << "empty list:" << endl;
    emptyList.printAllNodes();
    
    LinkedList myList;
    cout << "1number of nodes: " << myList.numNodes <<endl;
    cout << "number of existing nodes: " << myList.numNodesExisting <<endl;
    myList.insertAtFront(1);
    myList.insertAtFront(2);
    myList.insertAtFront(3);
    myList.insertAtFront(4);
    myList.insertAtFront(5);
    myList.insertAtFront(6);
    myList.printAllNodes();
    cout << "2number of nodes: " << myList.numNodes <<endl;
    cout << "number of existing nodes: " << myList.numNodesExisting <<endl << endl;
    
    
    myList.removeAtFront();
    myList.removeAtFront();
    myList.printAllNodes();
    
    cout << "3number of nodes: " << myList.numNodes <<endl;
    cout << "number of existing nodes: " << myList.numNodesExisting <<endl;
    
    myList.cleanList();
    myList.printAllNodes();
    
    cout << "4number of nodes: " << myList.numNodes <<endl;
    cout << "number of existing nodes: " << myList.numNodesExisting <<endl;

    myList.removeAtEnd();
  
    myList.insertAtEnd(20);
    
    myList.removeAtEnd();

    myList.insertAtEnd(19);
    myList.removeAtFront();
    myList.insertAtFront(8);
    
    myList.removeAtFront();
    myList.insertAtFront(11);
   
    
    cout << "5number of nodes: " << myList.numNodes <<endl;
    cout << "number of existing nodes: " << myList.numNodesExisting <<endl;
    myList.printAllNodes();
    myList.cleanList();
    myList.printAllNodes();
    
    cout << "6number of nodes: " << myList.numNodes <<endl;
    cout << "number of existing nodes: " << myList.numNodesExisting <<endl;
    cout << "here" << endl;
   
    myList.printAllNodes();
    
    myList.insertAtEnd(-19);
    myList.cleanList();
    myList.printAllNodes();
    
    myList.insertAtFront(17);
    myList.cleanList();
    myList.printAllNodes();
    
    LinkedList mySecondList(myList);
    
    mySecondList.printAllNodes();
    
    LinkedList thirdList;
    
    
    cout << "number of nodes: " << thirdList.numNodes <<endl;
    cout << "number of existing nodes: " << thirdList.numNodesExisting <<endl;
    
    
    
    thirdList.insertAtFront(5);
    thirdList.insertAtFront(3);
    thirdList.insertAtFront(0);
    thirdList.insertAtEnd(5);
    thirdList.insertAtEnd(-1);
    thirdList.insertAtEnd(19);
    
    thirdList.printAllNodes();
    
    cout << "number of nodes: " << thirdList.numNodes <<endl;
    cout << "number of existing nodes: " << thirdList.numNodesExisting <<endl;
    
    
    
    thirdList = myList;
    
    cout << "myList number of nodes: " << myList.numNodes <<endl;
    cout << "myList number of existing nodes: " << myList.numNodesExisting <<endl;
    
    cout << "number of nodes: " << thirdList.numNodes <<endl;
    cout << "number of existing nodes: " << thirdList.numNodesExisting <<endl;
   
    
    thirdList.printAllNodes();
    
    cout << "number of nodes: " << thirdList.numNodes <<endl;
    cout << "number of existing nodes: " << thirdList.numNodesExisting <<endl;
    
    
    thirdList.cleanList();
    
    thirdList.printAllNodes();
   
    cout << "number of nodes: " << thirdList.numNodes <<endl;
    cout << "number of existing nodes: " << thirdList.numNodesExisting <<endl;
    
    
    thirdList.removeAtEnd();
    thirdList.removeAtFront();
    
    thirdList.printAllNodes();
  
    thirdList.cleanList();
    thirdList.printAllNodes();
 
    thirdList.insertAtFront(-100);
    thirdList.cleanList();
    thirdList.printAllNodes();
    
    thirdList.removeAtEnd();
    thirdList.removeAtEnd();
    thirdList.printAllNodes();
    thirdList.cleanList();
    thirdList.printAllNodes();
    
    

}
*/




 
 
 












