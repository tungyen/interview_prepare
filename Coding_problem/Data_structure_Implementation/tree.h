#ifndef TREE_H
#define TREE_H

#include <iostream>
using namespace std;



class SplayTree
{
public:
    class Node {
    public:
        int val;
        Node *left, *right;
        Node(int v):val(v), left(nullptr), right(nullptr){}
    };

    SplayTree(Node* r);
    Node* rightRotate(Node* x);
    Node* leftRotate(Node* x);
    Node* splay(Node* root, int key);
    Node* insert(Node* root, int key);
    void preOrder(Node* node);
    void getRes();

private:
    Node* root;
};

#endif // TREE_H
