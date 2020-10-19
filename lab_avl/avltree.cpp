/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    if (t == NULL) {
        return;
    }
    Node* new_top = t -> right;
    if (new_top != NULL) {
        t -> right = new_top -> left;
        t -> height = 1 + std::max(heightOrNeg1(t -> left), heightOrNeg1(t -> right));
        new_top -> left = t;
        t = new_top;
    }
    t -> height = 1 + std::max(heightOrNeg1(t -> left), heightOrNeg1(t -> right));
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    if (t == NULL) {
        return;
    }
    Node* new_top = t -> left;
    if (new_top != NULL) {
        t -> left = new_top -> right;
        t -> height = 1 + std::max(heightOrNeg1(t -> left), heightOrNeg1(t -> right));
        new_top -> right = t;
        t = new_top;
    }
    t -> height = 1 + std::max(heightOrNeg1(t -> left), heightOrNeg1(t -> right));
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t -> right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if (subtree == NULL) {
        return;
    }
    int balance_factor = heightOrNeg1(subtree -> right) - heightOrNeg1(subtree -> left);
    if ((balance_factor <= 1 && balance_factor >= -1)) {
        return;
    }
    if (subtree -> right != NULL && balance_factor > 1) {
        int right_balance = heightOrNeg1(subtree -> right -> right) - heightOrNeg1(subtree -> right -> left);
        if (right_balance == 1) {
            rotateLeft(subtree);
        } else if (right_balance == -1) {
            rotateRightLeft(subtree);
        }
    }
    if (subtree -> left != NULL && balance_factor < 1) {
        int left_balance = heightOrNeg1(subtree -> left -> right) - heightOrNeg1(subtree -> left -> left);
        if (left_balance == 1) {
            rotateLeftRight(subtree);
        } else if (left_balance == -1) {
            rotateRight(subtree);
        }
    }
    subtree -> height = 1 + std::max(heightOrNeg1(subtree -> left), heightOrNeg1(subtree -> right));
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL) {
        subtree = new Node(key, value);
        return;
    } else if (subtree -> key < key) {
        insert(subtree -> right, key, value);
        int balance = heightOrNeg1(subtree -> right) - heightOrNeg1(subtree -> left);
        if (balance >= 2) {
            rebalance(subtree);
        }
    } else if (subtree -> key > key) {
        insert(subtree -> left, key, value);
        int balance = heightOrNeg1(subtree -> right) - heightOrNeg1(subtree -> left);
        if (balance <= -2) {
            rebalance(subtree);
        }
    }
    subtree -> height = 1 + std::max(heightOrNeg1(subtree -> left), heightOrNeg1(subtree -> right));
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove (subtree -> left, key);
    } else if (key > subtree->key) {
        // your code here
        remove (subtree -> right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* iop = subtree -> left;
            while (iop -> right != NULL) {
                iop = iop -> right;
            }
            swap(iop, subtree);
            remove(subtree -> left, key);
        } else {
            /* one-child remove */
            // your code here
            if (subtree -> left != NULL) {
                Node* temp = subtree;
                subtree = subtree -> left;
                delete temp;
            } else if (subtree -> right != NULL) {
                Node* temp = subtree;
                subtree = subtree -> right;
                delete temp;
            }
        }
        // your code here
    }
    if (subtree != NULL) {
        subtree -> height = 1 + std::max(heightOrNeg1(subtree -> left), heightOrNeg1(subtree -> right));
        rebalance(subtree);
    }
}
