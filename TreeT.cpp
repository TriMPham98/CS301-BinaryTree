// Define a binary search tree class template with a type parameter T
template<class T>
TreeT<T>::TreeT() {
    // Initialize the root pointer to null
    root = nullptr;
    // Initialize the number of nodes as 0
    numNodes = 0;
}

template<class T>
TreeT<T>::~TreeT() {
    // Call DestroyTree method to delete the tree
    DestroyTree(root);
}

template<class T>
TreeT<T> &TreeT<T>::operator=(const TreeT &otherTree) {
    // Check if the current object is not the same as the other object
    if (this != &otherTree) {
        // Destroy the current tree
        DestroyTree(root);
        // Copy the other tree using CopyHelper method
        CopyHelper(root, otherTree.root);
        // Assign the number of nodes from the other tree
        numNodes = otherTree.numNodes;
    }
    // Return the reference to the current object
    return *this;
}

template<class T>
void TreeT<T>::Add(T value) {
    // Create a new node with the given value
    Node *newChild = new Node;
    newChild->left = nullptr;
    newChild->right = nullptr;
    newChild->value = value;

    // Check if the tree is empty
    if (root == nullptr) {
        // Set the new node as the root
        root = newChild;
        // Increment the number of nodes
        numNodes++;
        return;
    }

    // Start at the root node
    Node *curr = root;

    // Traverse the tree to find the correct position for the new node
    while (true) {
        if (value < curr->value) {
            if (curr->left == nullptr) {
                // Insert the new node as the left child
                curr->left = newChild;
                break;
            }
            // Move to the left child
            curr = curr->left;
        } else {
            if (value > curr->value) {
                if (curr->right == nullptr) {
                    // Insert the new node as the right child
                    curr->right = newChild;
                    break;
                }
                // Move to the right child
                curr = curr->right;
            }
        }
    }
    // Incrememnt the number of nodes
    numNodes++;
}

template<class T>
void TreeT<T>::Remove(T value) {
    // Call the RemoveHelper method to remove the node with the given value
    RemoveHelper(root, value);
}

template<class T>
bool TreeT<T>::Contains(T value) {
    // Start at the root node
    Node *curr = root;
    // Traverse the tree to search for the given value
    while (curr != nullptr) {
        if (value < curr->value) {
            // Move to the left child
            curr = curr->left;
        } else if (value > curr->value) {
            // Move to the right child
            curr = curr->right;
        } else {
            // Value found
            return true;
        }
    }
    // Value not found
    return false;
}

template<class T>
int TreeT<T>::Size() {
    // Return the number of nodes in the tree
    return numNodes;
}

template<class T>
void TreeT<T>::ResetIterator(Order traverseOrder) {
    // Clear the iterator queue
    while (!iterQue.empty()) {
        iterQue.pop();
    }
    // Call the appropriate traversal method based on the given order
    if (traverseOrder == IN_ORDER) {
        PlaceInOrder(root);
    } else if (traverseOrder == PRE_ORDER) {
        PlacePreOrder(root);
    } else if (traverseOrder == POST_ORDER) {
        PlacePostOrder(root);
    }
}

template<class T>
T TreeT<T>::GetNextItem() {
    // Get the next item from the iterator queue
    T nextItem = iterQue.front();
    iterQue.pop();

    // Return the next item
    return nextItem;
}

template<class T>
void TreeT<T>::DestroyTree(TreeT::Node *node) {
    // Recursively delete the nodes in the tree using post-order traversal
    if (node != nullptr) {
        DestroyTree(node->left);
        DestroyTree(node->right);
        delete node;
    }
}

template<class T>
void TreeT<T>::RemoveHelper(TreeT::Node *&subtree, T value) {
    // Recursive method to find and remove the node with the given value

    // Base case: if the subtree is null, the value isn't found and there's nothing to remove
    if (subtree == nullptr) {
        return;
    }

    // If the value is less than the current subtree's value,
    // search the left subtree
    if (value < subtree->value) {
        RemoveHelper(subtree->left, value);
    // If the value is greater than the current subtree's value,
    // search the right subtree
    } else if (value > subtree->value) {
        RemoveHelper(subtree->right, value);
    // If the value matches the current subtree's value,
    // delete the node and decrement the number of nodes
    // after removal
    } else {
        DeleteNode(subtree);
        numNodes--;
    }
}

template<class T>
void TreeT<T>::DeleteNode(TreeT::Node *&subtree) {
    // Helper method to delete a node and maintain the BST property

    Node *temp;

    // If the node has no left child, replace the node with its right subtree
    if (subtree->left == nullptr) {
        temp = subtree;
        subtree = subtree->right;
        delete temp;
    // If the node has no right child, replace the node with its left subtree
    } else if (subtree->right == nullptr) {
        temp = subtree;
        subtree = subtree->left;
        delete temp;
   // If the node has both left and right children, replace the node's value
   // with its predecessor's value
    } else {
        GetPredecessor(subtree->left, subtree->value);
        RemoveHelper(subtree->left, subtree->value);
    }
}

template<class T>
void TreeT<T>::GetPredecessor(TreeT::Node *curr, T &value) {
    // Find the maximum value in the left subtree
    while (curr->right != nullptr) {
        // Move right until the rightmost node is found
        curr = curr->right;
    }
    // Set the value to the rightmost node's value
    value = curr->value;
}

template<class T>
void TreeT<T>::CopyHelper(TreeT::Node *&thisTree, TreeT::Node *otherTree) {
    // Recursive method to copy the structure and values of otherTree to thisTree

    // Base case: if otherTree is null, set thisTree to null
    if (otherTree == nullptr) {
        thisTree = nullptr;
    // General case: Create a new node in thisTree with the value from otherTree
    } else {
        thisTree = new Node;
        thisTree->value = otherTree->value;
        // Recursively copy the left and right subtrees
        CopyHelper(thisTree->left, otherTree->left);
        CopyHelper(thisTree->right, otherTree->right);
    }
}

template<class T>
void TreeT<T>::PlacePreOrder(TreeT::Node *node) {
    // Recursively traverse the tree in pre-order (root, left, right)
    // and push node values into the iterator queue

    // Base case: if the node is null, return
    if (node == nullptr) {
        return;
    }

    // Push the current node's value to the iterator queue
    iterQue.push(node->value);
    // Recursively traverse the left subtree
    PlacePreOrder((node->left));
    // Recursively traverse the right subtree
    PlacePreOrder(node->right);
}

template<class T>
void TreeT<T>::PlacePostOrder(TreeT::Node *node) {
    // Recursively traverse the tree in post-order (left, right, root)
    // and push node values into the iterator queue

    // Base case: if the node is null, return
    if (node == nullptr) {
        return;
    }

    // Recursively traverse the left subtree
    PlacePostOrder((node->left));
    // Recursively traverse the right subtree
    PlacePostOrder(node->right);
    // Push the current node's value to the iterator queue
    iterQue.push(node->value);
}

template<class T>
void TreeT<T>::PlaceInOrder(TreeT::Node *node) {
    if (node == nullptr) {
        return;
    }

    PlaceInOrder((node->left));
    iterQue.push(node->value);
    PlaceInOrder(node->right);
}
