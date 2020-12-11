//
//  main.cpp
//  Assignment10_omerkatz_cs2b
//
//  Created by Omer Katz on 6/20/18.
//  Copyright © 2018 Omer Katz. All rights reserved.
//

#include <iostream>

#include <string>
using namespace std;
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int data,Node* left = NULL,Node* right = NULL)
    {
        this->data = data;
        this->left = left;
        this->right = right;
        
    }
    
};
class BinaryTree {
    public:
        BinaryTree(int rootNodeValue);
        virtual ~BinaryTree();
        void print() const;
        bool contains(int searchValue);
        void insert(int data);
        int getSmallestValue();
    protected:
        void deleteSubtree(Node*& subTreeRoot);
    
    private:
        void print(Node* root) const;
        bool contains(Node* root, int searchValue);
        void insert(int data, Node*& subtree);
        bool isEmpty();
        int getSmallestValue( Node*& subtree);
   
    protected:
        Node* root;
    
};

BinaryTree::BinaryTree(int rootNodeValue)
{
    root = new Node(rootNodeValue);
    
}

BinaryTree::~BinaryTree( )
{
    this->deleteSubtree(this->root);
    
}

void BinaryTree::deleteSubtree(Node*& subTreeRoot)
{
    if (subTreeRoot != NULL) {
        deleteSubtree(subTreeRoot->left);
        deleteSubtree(subTreeRoot->right);
        //subTreeRoot now points to a one node tree.
        delete subTreeRoot;
        subTreeRoot = NULL;
        
    }
    
}

void BinaryTree::print(Node* node) const
{
    if (node != NULL) {
        print(node->left);
        cout << node->data << endl;
        print(node->right);
        
    }
    
}
void BinaryTree::print() const {
    print(root);
    
}

bool BinaryTree::contains(Node* node, int value)
{
    if (node == NULL) {
        return false;
        
    }
    else if (node->data == value) {
        return true;
        
    }
    else {
        return contains(node->left, value) || contains(node->right, value);
        
    }
    
}

bool BinaryTree::contains(int value) {
    
        return contains(root, value);
    }
bool BinaryTree::isEmpty() {
    return (root == nullptr);
    
}
void BinaryTree::insert(int data) {
    
    insert(data, root);
    
}
void BinaryTree::insert(int data, Node*& subtree) {
    if (subtree==nullptr)
    { // base case
        Node* newNode = new Node(data);
        subtree = newNode;
        return;
        
    }
    if (subtree->left == nullptr && subtree->right != nullptr)
    {
        insert(data, subtree->left);
        
    }
    else if (subtree->right == nullptr && subtree->left != nullptr)
    {
        insert(data, subtree->right);
        
    }
    else { // either both are null or neither are
        bool addToLeft = rand() % 2;
        if (addToLeft) {
            insert(data, subtree->left);
            
        }
        else {insert(data, subtree->right);
            
        }
        
    }
    
}


int BinaryTree::getSmallestValue( Node*& subtree)
{
    
    if (subtree == nullptr)
    {
        return 0;
    }
    
    int smallestValue = subtree->data;
    int leftChild;
    if(subtree->left != nullptr)
    {
         leftChild = getSmallestValue(subtree->left);
    }
    
    int rightChild;
    if( subtree->right != nullptr)
    {
        rightChild = getSmallestValue(subtree->right);
    }
    
    if(subtree->left != nullptr )
    {
        if(smallestValue > leftChild)
        {
            smallestValue = leftChild;
        }
    }
    if(subtree->right != nullptr )
    {
        if(smallestValue > rightChild)
        {
            smallestValue = rightChild;
        }
    
    }
    
    return smallestValue;

}

int BinaryTree::getSmallestValue()
{
    return getSmallestValue( root);
}


class BinarySearchTree: public BinaryTree {
    
    private:
        void insert(int item, Node*& subTreeRoot);
        int getSmallestValue(Node*& subTreeRoot);
        int getMaxValue(Node*& subTreeRoot);
        bool contains(int searchValue, Node*& subTreeRoot);
    
    public:
        BinarySearchTree(int rootNodeValue);
        virtual ~BinarySearchTree();
        void insert(int item);
        int getSmallestValue();
        int getMaxValue();
        bool contains(int searchValue);
    
    
};


BinarySearchTree::BinarySearchTree(int rootNodeValue):
BinaryTree(rootNodeValue)
{
    // intentionally empty
    
}

BinarySearchTree::~BinarySearchTree( ){
    this->deleteSubtree(this->root);
    
}

void BinarySearchTree::insert(int item, Node*& subTreeRoot){
    if (subTreeRoot == NULL)
        subTreeRoot = new Node(item, NULL, NULL);
    else if (item < subTreeRoot->data)
        insert(item, subTreeRoot->left);
    else //item >= subTreeRoot->data
        insert(item, subTreeRoot->right);
    
}

void BinarySearchTree::insert(int item)
{
    insert(item, root);
    
}

int BinarySearchTree::getSmallestValue( Node*& subtree)
{
  // return BinaryTree:: getSmallestValue();
    
  if(subtree-> left != nullptr)
      return getSmallestValue(subtree-> left );
  else return subtree->data;
    
}

int BinarySearchTree::getMaxValue()
{
    return getMaxValue(root);
}

int BinarySearchTree::getMaxValue( Node*& subtree)
{
    // return BinaryTree:: getSmallestValue();
    
    if(subtree->right != nullptr)
        return getMaxValue(subtree-> right );
    else return subtree->data;
    
}



int BinarySearchTree::getSmallestValue()
{
    return getSmallestValue(root);
}



bool BinarySearchTree::contains(int searchValue, Node *&subtree)
{
    if(subtree == nullptr)
    {
        return false;
    }
    
    if(subtree-> data == searchValue)
        return true;
    
    if( searchValue < subtree->data)
        
        return contains(searchValue, subtree->left);
        
    
    if( searchValue > subtree->data)
    
        return contains(searchValue, subtree->right);

    return true;
    
}

bool BinarySearchTree::contains(int searchValue)
{
    return contains( searchValue, root);
}




int main(int argc, const char * argv[]) {
    srand(time(NULL));
    int initialValue = 16;
    BinaryTree myTree(initialValue);
    cout << "printing my tree" << endl;
    myTree.print();
    cout << "adding five numbers to my tree" << endl;
    myTree.insert(2);
    myTree.insert(8);
    myTree.insert(-64);
    myTree.insert(-512);
    myTree.insert(32);
    myTree.print();
    
   
    // comment the following in after writing your code
    cout << "smallest number in my tree: " << myTree.getSmallestValue() << endl;
    
    BinarySearchTree myBST(initialValue);
    cout << "printing my BST" << endl;
    myBST.print();
    cout << "adding five numbers to my tree" << endl;
    myBST.insert(2);
    myBST.insert(8);
    myBST.insert(-64);
    myBST.insert(-512);
    myBST.insert(32);
    myBST.print();
    
    // comment the following in after writing your code
    cout << "smallest value in my BST: " << myBST.getSmallestValue() << endl;
    
    cout << "max value in my BST: " << myBST.getMaxValue() << endl;
    // testing the provided "contains" method with pointers
    BinarySearchTree* myBstPointer = new BinarySearchTree(4);
    myBstPointer->insert(64);
    myBstPointer->insert(-256);
    myBstPointer->insert(-1024);
    myBstPointer->insert(2048);
    
    // This code relates to question 4c.
    // statement 1:
    cout << "myBstPointer tree contains 10: " << myBstPointer->contains(10) << endl;
    BinaryTree* myTreePointer = myBstPointer;
    
    // statement 2:
    cout << "myTreePointer tree contains 10: " << myTreePointer->contains(10) << endl;
    // Use this code to test both of your trees as string trees
    string listOfStrings[] = {"ingredient","furniture","gallon","meter","zebra","penguin","rockhopper","sixty","holiday","rather","particular","anymore","happiness","oxygen","imagination","phrase","tired","paid","length","probably","mixture","electricity","extra","piano","monkey","shampoo","million","newspaper","health","anyway","library","favorite","opposite","penguin","guest","harvest","penguin","elevator","energy","penguin","garden","sidewalk","squirrel","government","pencil","interesting"};
    int listLength = 46;
    for (int i = 0; i < listLength; i++)
        cout << listOfStrings[i] << endl;
    return 0;
    
}
    
    








