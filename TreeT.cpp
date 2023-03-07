template<class T>
TreeT<T>::TreeT() {
    root = nullptr;
    numNodes = 0;
}

template<class T>
TreeT<T>::~TreeT() {
    DestroyTree(root);
}

template<class T>
TreeT<T> &TreeT<T>::operator=(const TreeT &otherTree) {
    return TreeT<T>();
}

template<class T>
void TreeT<T>::Add(T value) {

    Node *newChild = new Node;
    newChild->left = nullptr;
    newChild->right = nullptr;
    newChild->value = value;

    if (root == nullptr) {
        root = newChild;
        numNodes++;
        return;
    }
    Node *curr = root;

    while (true) {
        if (value < curr->value) {
            if (curr->left == nullptr) {
                curr->left = newChild;
                break;
            }
            // Move curr left
            curr = curr->left;
        } else {
            if (value > curr->value) {
                if (curr->right == nullptr) {
                    curr->right = newChild;
                    break;
                }
                // Move curr right
                curr = curr->right;
            }
        }
    }
    numNodes++;
}

template<class T>
void TreeT<T>::Remove(T value) {
    RemoveHelper(root, value);
}

template<class T>
bool TreeT<T>::Contains(T value) {
    Node *curr = root;
    while (curr != nullptr) {
        if (value < curr->value) {
            curr = curr->left;
        } else if (value > curr->value) {
            curr = curr->right;
        } else {
            return true;
        }
    }
    return false;
}

template<class T>
int TreeT<T>::Size() {
    return numNodes;
}

template<class T>
void TreeT<T>::ResetIterator(Order traverseOrder) {
    while (!iterQue.empty()) {
        iterQue.pop();
    }

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
    T nextItem = iterQue.front();
    iterQue.pop();

    return nextItem;
}

template<class T>
void TreeT<T>::DestroyTree(TreeT::Node *node) {
    if (node != nullptr) {
        DestroyTree(node->left);
        DestroyTree(node->right);
        delete node;
    }
}

template<class T>
void TreeT<T>::RemoveHelper(TreeT::Node *&subtree, T value) {
    if (subtree == nullptr) {
        return;
    }
    if (value < subtree->value) {
        RemoveHelper(subtree->left, value);
    } else if (value > subtree->value) {
        RemoveHelper(subtree->right, value);
    } else {
        DeleteNode(subtree);
        numNodes--;
    }
}

template<class T>
void TreeT<T>::DeleteNode(TreeT::Node *&subtree) {
    Node *temp;
    if (subtree->left == nullptr) {
        temp = subtree;
        subtree = subtree->right;
        delete temp;
    } else if (subtree->right == nullptr) {
        temp = subtree;
        subtree = subtree->left;
        delete temp;
    } else {
        GetPredecessor(subtree->left, subtree->value);
        RemoveHelper(subtree->left, subtree->value);
    }
}

template<class T>
void TreeT<T>::GetPredecessor(TreeT::Node *curr, T &value) {
    while (curr->right != nullptr) {
        curr = curr->right;
    }
    value = curr->value;
}

template<class T>
void TreeT<T>::CopyHelper(TreeT::Node *&thisTree, TreeT::Node *otherTree) {
    if (otherTree == nullptr) {
        thisTree = nullptr;
    } else {
        thisTree = new Node;
        thisTree->value = otherTree->value;
        CopyHelper(thisTree->left, otherTree->left);
        CopyHelper(thisTree->right, otherTree->right);
    }
}

template<class T>
void TreeT<T>::PlacePreOrder(TreeT::Node *node) {
    if (node == nullptr) {
        return;
    }

    iterQue.push(node->value);
    PlacePreOrder((node->left));
    PlacePreOrder(node->right);
}

template<class T>
void TreeT<T>::PlacePostOrder(TreeT::Node *node) {
    if (node == nullptr) {
        return;
    }

    PlacePostOrder((node->left));
    PlacePostOrder(node->right);
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
