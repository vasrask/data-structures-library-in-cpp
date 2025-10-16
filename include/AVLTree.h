#ifndef AVLTREE_H
#define AVLTREE_H

#include <fstream>

struct AVLNode {
    int key;
    int height;
    AVLNode* left;
    AVLNode* right;
    AVLNode(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    AVLNode* root;

    int height(AVLNode* node);
    int getBalance(AVLNode* node);
    AVLNode* rotateRight(AVLNode* y);
    AVLNode* rotateLeft(AVLNode* x);
    AVLNode* insert(AVLNode* node, int key);
    void printAVLNode(AVLNode* node, std::ofstream& output);
    int max(int a, int b) const;
    int size(AVLNode* node) const;
    AVLNode* findMinNode(AVLNode* node) const;
    AVLNode* searchNode(AVLNode* node, int key) const;
    AVLNode* deleteNode(AVLNode* node, int key);

public:
    AVLTree();
    void insert(int key);
    void buildTree(int* elements, int size);
    int getSize() const;
    int findMin() const;
    std::string search(int key) const;
    void deleteNode(int key);
    void printAVLTree(std::ofstream& output);
};

#endif // AVLTREE_H
