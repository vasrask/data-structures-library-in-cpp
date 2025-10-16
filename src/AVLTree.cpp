#include "AVLTree.h"
#include <iostream>

// Constructor to initialize the root of the AVL tree
AVLTree::AVLTree() : root(nullptr) {}

// Returns the height of a node
int AVLTree::height(AVLNode* node) {
    return node ? node->height : 0;
}

// Returns the balance factor of a node
int AVLTree::getBalance(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// Returns the maximum of two integers
int AVLTree::max(int a, int b) const {
    return (a > b) ? a : b;
}

// Performs a right rotation around the given node
AVLNode* AVLTree::rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Performs a left rotation around the given node
AVLNode* AVLTree::rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y;
}

// Inserts a key into the AVL tree and returns the new root
AVLNode* AVLTree::insert(AVLNode* node, int key) {
    if (!node)
        return new AVLNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + std::max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rotateRight(node);

    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);

    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Inserts a key into the AVL tree
void AVLTree::insert(int key) {
    root = insert(root, key);
}

// Deletes a node from the AVL tree and returns the new root
AVLNode* AVLTree::deleteNode(AVLNode* node, int key) {
    if (!node) {
        return node;
    }

    if (key < node->key) {
        node->left = deleteNode(node->left, key);
    } else if (key > node->key) {
        node->right = deleteNode(node->right, key);
    } else {
        if (!node->left || !node->right) {
            AVLNode* temp = node->left ? node->left : node->right;
            if (!temp) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
            delete temp;
        } else {
            AVLNode* successor = findMinNode(node->right);
            node->key = successor->key;
            node->right = deleteNode(node->right, successor->key);
        }
    }

    if (!node) {
        return node;
    }

    node->height = 1 + std::max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0) {
        return rotateRight(node);
    }
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && getBalance(node->right) <= 0) {
        return rotateLeft(node);
    }
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Deletes a node from the AVL tree
void AVLTree::deleteNode(int key) {
    root = deleteNode(root, key);
}

// Builds the AVL tree from an array of elements
void AVLTree::buildTree(int* elements, int size) {
    for (int i = 0; i < size; ++i) {
        insert(elements[i]);
    }
}

// Returns the size of the AVL tree from node to leaves
int AVLTree::size(AVLNode* node) const {
    return node ? 1 + size(node->left) + size(node->right) : 0;
}

// Returns the total size of the AVL tree (from root to leaves)
int AVLTree::getSize() const { return size(root); }

// Prints an AVL node
void AVLTree::printAVLNode(AVLNode* node, std::ofstream& output) {
    if (node) {
        printAVLNode(node->left, output);
        output << node->key << " ";
        printAVLNode(node->right, output);
    }
}

// Prints the AVL tree to a file
void AVLTree::printAVLTree(std::ofstream& output) {
    output << "AVL Tree: ";
    printAVLNode(root, output);
    output << std::endl;
}

// Finds the minimum node in the AVL tree
AVLNode* AVLTree::findMinNode(AVLNode* node) const {
    AVLNode* current = node;
    while (current && current->left) {
        current = current->left;
    }
    return current;
}

// Finds the minimum key in the AVL tree
int AVLTree::findMin() const {
    AVLNode* minNode = findMinNode(root);
    return minNode ? minNode->key : -1;
}

// Searches for a key in the AVL tree
AVLNode* AVLTree::searchNode(AVLNode* node, int key) const {
    if (!node || node->key == key) {
        return node;
    }

    if (key < node->key) {
        return searchNode(node->left, key);
    } else {
        return searchNode(node->right, key);
    }
}

// Searches for a key in the AVL tree
std::string AVLTree::search(int key) const {
    AVLNode* foundNode = searchNode(root, key);
    return foundNode ? "SUCCESS" : "FAILURE";
}
