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
    // Postconditions: A new binary search tree object is created
    // with root pointer set to null and numNodes set to 0.

    ~TreeT();
    // Preconditions: None.
    // Postconditions: A new binary search tree object is
    // created with root pointer set to null and numNodes
    // set to 0.

    TreeT& operator=(const TreeT& otherTree);
    // Precondition: A valid TreeT object exists,
    // and another valid TreeT object is provided.
    // Postcondition: The current tree is destroyed and replaced with
    // a deep copy of the provided tree.

    void Add(T value);       // Add value to the tree
    // Precondition: A valid TreeT object exists,
    // and a value of type T is provided.
    // Postcondition: A new node with the provided value is added
    // to the tree while maintaining the BST property.
    // The number of nodes in the tree is incremented by 1.

    void Remove(T value);    // Remove value from the tree
    // Precondition: A valid TreeT object exists,
    // and a value of type T is provided.
    // Postcondition: If a node with the provided value is found in the tree,
    // the node is removed while maintaining the BST property, and the number
    // of nodes is decremented by 1. If the value is not found, the tree
    // remains unchanged.

    bool Contains(T value);  // Determines if value is in the tree
    // Precondition: A valid TreeT object exists, and a value of type T is provided.
    // Postcondition: Returns true if the provided value is found in the tree,
    // and false otherwise. The tree remains unchanged.

    int Size();     // Number of values in the tree
    // Precondition: A valid TreeT object exists.
    // Postcondition: Returns the number of nodes in the tree.
    // The tree remains unchanged.

    // These are used by the iterator
    void ResetIterator(Order traverseOrder);    // Initializes the Iterator
    // Precondition: A valid TreeT object exists, and a valid traverse
    // order is provided.
    // Postcondition: The iterator queue is cleared and filled with node values
    // based on the given traverse order. The tree remains unchanged.

    T GetNextItem();
    // Precondition: A valid TreeT object exists, and ResetIterator has
    // been called with a valid traverse order.
    // Postcondition: Returns the next item from the iterator queue and
    // removes it from the queue. The tree remains unchanged.

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
