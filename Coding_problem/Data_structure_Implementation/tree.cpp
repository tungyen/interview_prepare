#include "tree.h"

SplayTree::SplayTree(SplayTree::Node* r){
    root = r;
}

SplayTree::Node* SplayTree::rightRotate(SplayTree::Node* x) {
    SplayTree::Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

SplayTree::Node* SplayTree::leftRotate(SplayTree::Node* x) {
    SplayTree::Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

SplayTree::Node* SplayTree::splay(SplayTree::Node* root, int key) {
    if (root == nullptr || root->val == key)
        return root;

    if (root->val > key) {
        if (root->left == nullptr)
            return root;
        if (root->left->val > key) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        }
        else if (root->left->val < key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right != nullptr)
                root->left = leftRotate(root->left);
        }
        return (root->left == nullptr) ? root : rightRotate(root);
    }
    else {
        if (root->right == nullptr)
            return root;
        if (root->right->val > key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != nullptr)
                root->right = rightRotate(root->right);
        }
        else if (root->right->val < key) {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }
        return (root->right == nullptr) ? root : leftRotate(root);
    }
}

SplayTree::Node* SplayTree::insert(SplayTree::Node* root, int key) {
    if (root == nullptr)
        return new Node(key);

    root = splay(root, key);

    if (root->val == key)
        return root;

    SplayTree::Node* node = new Node(key);
    if (root->val > key) {
        node->right = root;
        node->left = root->left;
        root->left = nullptr;
    }
    else {
        node->left = root;
        node->right = root->right;
        root->right = nullptr;
    }
    return node;
}

void SplayTree::preOrder(SplayTree::Node* node) {
    if (node != nullptr) {
        cout << node->val<< " "<<endl;
        preOrder(node->left);
        preOrder(node->right);
    }
}

void SplayTree::getRes(){
    preOrder(root);
}


