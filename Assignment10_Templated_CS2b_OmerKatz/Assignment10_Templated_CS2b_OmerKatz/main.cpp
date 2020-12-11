/*
 
 a. Binary Search Tree does have a root because it extends binary tree. The root is initialized through binary tree's constructor during the constructor chaining.

 b. Since there is already a destructor, the two methods that are missing are an overloaded  assignment operator and copy constructed. It would break if you tried to make a tree equal to another tree or if you tried to initialize a tree using another tree.
 
 c. The first contains should call the public function (wrapper function) contains in binary search tree, and the second contain statement should call the public function contains in binary tree. It knows to call the function from the correct class by looking at the calling object. Additionally the key word virtual should be added in order to call the functiont that corresponds rather then the contains associated with the pointer type.
 
 d. The order that the tree is being printed is left side, root, right side. This is known as an inorder transversal. The reason it is being printed in this order is because in the print method it is defined that the node's left child is printed first then the node itself and then the node's right child; using this order and recursion every subtree is printed which by the end prints out the entire tree.
 
 e. The contains for binary tree will take longer then binary search tree. This is because binary search tree is sorted meaning the contains function does not have to check every single node because it can compare if the string is larger or smaller than the data in the nodes, and go left and right depending on that. Basically since the Binary search tree is sorted the contains method always goes toward the node with string that it is looking for where in binary tree it has to check every single node until it finds the string it is looking for.
 

 
 */

#include <iostream>

#include <string>
using namespace std;

template <class T>
struct Node {
    T data;
    Node<T>* left;
    Node<T>* right;
    Node<T>(T data, Node<T>* left = NULL, Node<T>* right = NULL)
    {
        this->data = data;
        this->left = left;
        this->right = right;
        
    }
    
};

template <class T>
class BinaryTree {
public:
    BinaryTree(T rootNodeValue);
    virtual ~BinaryTree();
    void print() const;
    virtual bool contains(T searchValue);
    void insert(T data);
    T getSmallestValue();
protected:
    void deleteSubtree(Node<T> *& subTreeRoot);
    
private:
    void print(Node<T>* root) const;
    virtual bool contains(Node<T>* root, T searchValue);
    void insert(T data, Node<T> *& subtree);
    bool isEmpty();
    T getSmallestValue( Node<T> *& subtree);
    
protected:
    Node<T>* root;
    
};

template <class T>
BinaryTree<T>:: BinaryTree(T rootNodeValue)
{
    root = new Node<T>(rootNodeValue);
    
}

template <class T>
BinaryTree<T>::~BinaryTree( )
{
    this->deleteSubtree(this->root);
    
}
template <class T>
void BinaryTree<T>::deleteSubtree(Node<T> *& subTreeRoot)
{
    if (subTreeRoot != NULL) {
        deleteSubtree(subTreeRoot->left);
        deleteSubtree(subTreeRoot->right);
        //subTreeRoot now points to a one node tree.
        delete subTreeRoot;
        subTreeRoot = NULL;
        
    }
    
}

template <class T>
void BinaryTree<T>::print(Node<T>* node) const
{
    if (node != NULL) {
        print(node->left);
        cout << node->data << endl;
        print(node->right);
        
    }
    
}
template <class T>
void BinaryTree<T>::print() const {
    print(this->root);
    
}

template <class T>
bool BinaryTree<T>::contains(Node<T>* node, T value)
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

template <class T>
bool BinaryTree<T>::contains(T value) {
    
    return contains(this->root, value);
}
template <class T>
bool BinaryTree<T>::isEmpty() {
    return (this->root == nullptr);
    
}
template <class T>
void BinaryTree<T>::insert(T data) {
    
    insert(data, this->root);
    
}
template <class T>
void BinaryTree<T>::insert(T data, Node<T>*& subtree) {
    if (subtree==nullptr)
    { // base case
        Node<T>* newNode = new Node<T>(data);
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

template <class T>
T BinaryTree<T>::getSmallestValue( Node<T>*& subtree)
{
    
    if (subtree == nullptr)
    {
        return T();
    }
    
    T smallestValue = subtree->data;
    T leftChild;
    if(subtree->left != nullptr)
    {
        leftChild = getSmallestValue(subtree->left);
    }
    
    T rightChild;
    if( subtree->right != nullptr)
    {
        rightChild = getSmallestValue(subtree->right);
    }
    
    if(subtree->left != nullptr && smallestValue > leftChild )
    {
            smallestValue = leftChild;
        
    }
    if(subtree->right != nullptr && smallestValue > rightChild )
    {
        smallestValue = rightChild;
    }
    
    return smallestValue;
    
}

template <class T>
T BinaryTree<T>::getSmallestValue()
{
    return getSmallestValue( root);
}


template <class T>
class BinarySearchTree : public BinaryTree<T> {
    
private:
    void insert(T item, Node<T>*& subTreeRoot);
    T getSmallestValue(Node<T>*& subTreeRoot);
    bool contains(T searchValue, Node<T>*& subTreeRoot);
    
public:
    BinarySearchTree(T rootNodeValue);
    virtual ~BinarySearchTree();
    void insert(T item);
    T getSmallestValue();
    bool contains(T searchValue);
    
    
};

template <class T>
BinarySearchTree<T>::BinarySearchTree(T rootNodeValue):
BinaryTree<T>(rootNodeValue)
{
    // intentionally empty
    
}

template <class T>
BinarySearchTree<T>::~BinarySearchTree( ){
    this->deleteSubtree(this->root);
    
}

template <class T>
void BinarySearchTree<T>::insert(T item, Node<T>*& subTreeRoot){
    if (subTreeRoot == NULL)
        subTreeRoot = new Node<T>(item, NULL, NULL);
    else if (item < subTreeRoot->data)
        insert(item, subTreeRoot->left);
    else //item >= subTreeRoot->data
        insert(item, subTreeRoot->right);
    
}

template <class T>
void BinarySearchTree<T>::insert(T item)
{
    insert(item, this->root);
    
}

template <class T>
T BinarySearchTree<T>::getSmallestValue( Node<T>*& subtree)
{
    
    
    if(subtree-> left != nullptr)
        return getSmallestValue(subtree-> left );
    else return subtree->data;
    
}

template <class T>
T BinarySearchTree<T>::getSmallestValue()
{
    return getSmallestValue(this->root);
}

template <class T>
bool BinarySearchTree<T>::contains(T searchValue, Node<T> *&subtree)
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

template <class T>
bool BinarySearchTree<T>::contains(T searchValue)
{
    return contains( searchValue, this->root);
}




int main(int argc, const char * argv[]) {
    srand(time(NULL));
    int initialValue = 16;
    BinaryTree<int> myTree(initialValue);
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
    
    BinarySearchTree<int> myBST(initialValue);
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
    
    // testing the provided "contains" method with pointers
    BinarySearchTree<int> *myBstPointer = new BinarySearchTree<int>(4);
    myBstPointer->insert(64);
    myBstPointer->insert(-256);
    myBstPointer->insert(-1024);
    myBstPointer->insert(2048);
    
    // This code relates to question 4c.
    // statement 1:
    cout << "myBstPointer tree contains 10: " << myBstPointer->contains(10) << endl;
    BinaryTree<int>* myTreePointer = myBstPointer;
    
    // statement 2:
    cout << "myTreePointer tree contains 10: " << myTreePointer->contains(10) << endl;
    // Use this code to test both of your trees as string trees
    
    
    
    string listOfStrings[] = {"ingredient","furniture","gallon","meter","zebra","penguin","rockhopper","sixty","holiday","rather","particular","anymore","happiness","oxygen","imagination","phrase","tired","paid","length","probably","mixture","electricity","extra","piano","monkey","shampoo","million","newspaper","health","anyway","library","favorite","opposite","penguin","guest","harvest","penguin","elevator","energy","penguin","garden","sidewalk","squirrel","government","pencil","interesting"};
    int listLength = 46;
    
    BinaryTree<string> stringTree(listOfStrings[0]);
    
    for( int i = 1; i < listLength; i++)
    {
        stringTree.insert(listOfStrings[i]);
    }
    
    cout<< "smallest value: " << stringTree.getSmallestValue() << endl;
    stringTree.print();
    /*
    for (int i = 0; i < listLength; i++)
        cout << listOfStrings[i] << endl;
    return 0;
    */
    
    cout << endl << endl;
    
    BinarySearchTree<string> stringSearchTree(listOfStrings[1]);
    for( int i = 1; i < listLength; i++)
    {
        stringSearchTree.insert(listOfStrings[i]);
    }
    
    stringSearchTree.print();
    
    cout<< "smallest value: " << stringSearchTree.getSmallestValue() << endl;
}


/*
 printing my tree
 16
 adding five numbers to my tree
 8
 -64
 16
 -512
 2
 32
 smallest number in my tree: -512
 printing my BST
 16
 adding five numbers to my tree
 -512
 -64
 2
 8
 16
 32
 smallest value in my BST: -512
 myBstPointer tree contains 10: 0
 myTreePointer tree contains 10: 0
 length
 government
 particular
 health
 rather
 anyway
 happiness
 penguin
 anymore
 electricity
 furniture
 squirrel
 interesting
 paid
 guest
 zebra
 mixture
 opposite
 tired
 shampoo
 probably
 monkey
 ingredient
 penguin
 oxygen
 harvest
 sidewalk
 penguin
 phrase
 sixty
 pencil
 elevator
 energy
 gallon
 penguin
 piano
 library
 holiday
 garden
 million
 meter
 favorite
 extra
 rockhopper
 newspaper
 imagination
 
 
 anymore
 anyway
 electricity
 elevator
 energy
 extra
 favorite
 furniture
 furniture
 gallon
 garden
 government
 guest
 happiness
 harvest
 health
 holiday
 imagination
 interesting
 length
 library
 meter
 million
 mixture
 monkey
 newspaper
 opposite
 oxygen
 paid
 particular
 pencil
 penguin
 penguin
 penguin
 penguin
 phrase
 piano
 probably
 rather
 rockhopper
 shampoo
 sidewalk
 sixty
 squirrel
 tired
 zebra
 Program ended with exit code: 0
 */








