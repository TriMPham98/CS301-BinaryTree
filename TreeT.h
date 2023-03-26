//
// Author: Varick Erickson
// Date: 2/18/2021
//

#ifndef TREET_H
#define TREET_H

#include <queue> // stl library
using namespace std;

// Used to identify the order you wish to traverse the tree
enum Order {POST_ORDER, IN_ORDER, PRE_ORDER}; // Used as a flag
            //  0           1          2

template<class T>
class TreeT {
public:
    TreeT();
    // Preconditions: None.
    // Postconditions: A new binary search tree object is created with root pointer set
    // to null and numNodes set to 0.

    ~TreeT();
    //

    TreeT& operator=(const TreeT& otherTree);

    void Add(T value);       // Add value to the tree
    void Remove(T value);    // Remove value from the tree
    bool Contains(T value);  // Determines if value is in the tree

    int Size();     // Number of values in the tree

    // These are used by the iterator
    void ResetIterator(Order traverseOrder);    // Initializes the Iterator
    T GetNextItem();

private:
    struct Node {
        Node* left = nullptr;
        Node* right = nullptr;
        T value;
    };
    
    Node* root;
    int numNodes;

    // Used for de-constructor
    void DestroyTree(Node* node);

    // Used for Node removal
    void RemoveHelper(Node*& subtree, T value);
    void DeleteNode(Node*& subtree);
    void GetPredecessor(Node* curr, T& value);

    void CopyHelper(Node*& thisTree, Node* otherTree);

    // Used for iterator
    queue<T> iterQue;     // queue used for the iterator
    void PlacePreOrder(Node* node);
    void PlacePostOrder(Node* node);
    void PlaceInOrder(Node* node);
};


#include "TreeT.cpp"

#endif //TREET_H
