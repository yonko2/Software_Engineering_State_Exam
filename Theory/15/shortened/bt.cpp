#pragma once
#include <iostream>
#include <queue>

template<typename T>
class BinaryTree {
private:
    T data;
    BinaryTree* left = nullptr;
    BinaryTree* right = nullptr;

    void _print(BinaryTree* n, int order) { // 0: Pre, 1: In, 2: Post
        if (!n) return;
        if (order == 0) std::cout << n->data << " ";
        _print(n->left, order);
        if (order == 1) std::cout << n->data << " ";
        _print(n->right, order);
        if (order == 2) std::cout << n->data << " ";
    }

    bool _search(const BinaryTree* n, const T& val) const {
        if (!n) return false;
        return n->data == val || _search(n->left, val) || _search(n->right, val);
    }

public:
    BinaryTree(const T& val, BinaryTree* l = nullptr, BinaryTree* r = nullptr)
        : data(val), left(l), right(r) {}

    bool search(const T& val) const { return _search(this, val); }
    void printInOrder()   { _print(this, 1); }
    void printPreOrder()  { _print(this, 0); }
    void printPostOrder() { _print(this, 2); }

    void add(const T& val) {
        std::queue<BinaryTree*> q;
        q.push(this);
        while (!q.empty()) {
            BinaryTree* curr = q.front(); q.pop();
            
            if (!curr->left)  { 
                curr->left = new BinaryTree(val); return; 
            } 
            else q.push(curr->left);

            if (!curr->right) { 
                curr->right = new BinaryTree(val); return; 
            } 
            else q.push(curr->right);
        }
    }

    void printLevelOrder() {
        std::queue<BinaryTree*> q;
        q.push(this);
        while (!q.empty()) {
            BinaryTree* curr = q.front(); q.pop();
            std::cout << curr->data << " ";
            if (curr->left)  q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }
};
