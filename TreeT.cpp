template<class T>
TreeT<T>::TreeT() {
    root = nullptr;
    numNodes = 0;
}

template<class T>
TreeT<T>::~TreeT() {

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
    return 0;
}

template<class T>
void TreeT<T>::ResetIterator(Order traverseOrder) {
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

}

template<class T>
void TreeT<T>::RemoveHelper(TreeT::Node *&subtree, T value) {

}

template<class T>
void TreeT<T>::DeleteNode(TreeT::Node *&subtree) {

}

template<class T>
void TreeT<T>::GetPredecessor(TreeT::Node *curr, T &value) {

}

template<class T>
void TreeT<T>::CopyHelper(TreeT::Node *&thisTree, TreeT::Node *otherTree) {

}

template<class T>
void TreeT<T>::PlacePreOrder(TreeT::Node *node) {

}

template<class T>
void TreeT<T>::PlacePostOrder(TreeT::Node *node) {

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
