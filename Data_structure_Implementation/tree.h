#ifndef TREE_H
#define TREE_H

#include <iostream>
using namespace std;


class SplayTree{
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

class BST{
public:
    class Node{
    public:
        int val;
        Node *left, *right;
        Node(int v):val(v), left(nullptr), right(nullptr){}
    };
    BST(Node* r);
    Node* search(int val);
    void insert(int val);
    void remove(int val);
    void inorder();
    Node* getRoot();
private:
    Node* root;
    void helper(Node* root);
};


// RBTree
enum RBTColor{RED, BLACK};
class RBTNode{
public:
    int val;
    RBTColor color;
    RBTNode* left;
    RBTNode* right;
    RBTNode* parent;
    RBTNode(int v, RBTColor c) : val(v), color(c){}
};

class RBTree{
public:
    RBTree(RBTNode* r);
    ~RBTree();

    // Traversal
    void preorder(RBTNode* node);
    void inorder(RBTNode* node);
    void postorder(RBTNode* node);

    RBTNode* search(int val);
    RBTNode* successor(RBTNode* node);
    RBTNode* predecessor(RBTNode* node);

    void insert(int val);
    void remove(int val);

private:
    RBTNode* root;
    void leftRotate(RBTNode* x);
    void rightRotate(RBTNode* x);
    void insertFixUp(RBTNode* node);
    void removeFixUp(RBTNode* child, RBTNode* parent);
};

#endif // TREE_H
