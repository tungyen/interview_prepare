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

BST::BST(Node* r){
    root = r;
}

BST::Node* BST::search(int val){
    Node* cur = root;
    while(cur){
        if(cur->val == val){
            return cur;
        }
        else if(cur->val > val){
            cur = cur->left;
        }
        else{
            cur = cur->right;
        }
    }
    return nullptr;
}

void BST::insert(int val){
    Node* newNode = new Node(val);
    Node* cur = root;
    Node* parent;

    if(!root){
        root = newNode;
    }
    else{
        while(cur){
            parent = cur;
            if(cur->val < val){
                cur = cur->right;
            }
            else if(cur->val > val){
                cur = cur->left;
            }
            else{
                return;
            }
        }
        if(parent->val < val){
            parent->right = newNode;
        }
        else{
            parent->left = newNode;
        }
    }
}

void BST::remove(int val){

    // Get the parent node of desire delete node
    Node* cur = root;
    Node* parent = cur;
    Node* child;
    int pos = 0;
    bool find = false;
    while(cur){
        if(cur->val == val){
            find = true;
            break;
        }
        else{
            parent = cur;
            if(cur->val > val){
                cur = cur->left;
                pos = -1;
            }
            else{
                cur = cur->right;
                pos = 1;
            }
        }
    }

    if(!find){cout<<"No such element."<<endl;return;}
    if(parent){
        switch(pos){
        case -1:
            child = parent->left;
            break;
        case 1:
            child = parent->right;
            break;
        case 0:
            child = parent;
            break;
        }

        if(!child->left){
            if(parent == child){
                root = root->right;
            }
            else{
                if(pos == 1){
                    parent->right = child->right;
                }
                else{
                    parent->left = child->right;
                }
            }
        }
        else if(!child->right){
            if(parent == child){
                root = root->left;
            }
            else{
                if(pos == 1){
                    parent->right = child->left;
                }
                else{
                    parent->left = child->left;
                }
            }
        }
        else{
            parent = child;
            Node* next = child->left;
            while(next->right){
                parent = next;
                next = next->right;
            }
            child->val = next->val;
            if(parent == child){
                parent->left = next->left;
            }
            else{
                parent->right = next->left;
            }
            delete next;
        }
    }
}

void BST::helper(BST::Node* root){
    if(!root){
        return;
    }
    helper(root->left);
    cout<<root->val<<" ";
    helper(root->right);
}

void BST::inorder(){
    helper(getRoot());
    cout<<endl;
}

BST::Node* BST::getRoot(){
    return root;
}

// Red Black Tree
RBTree::RBTree(RBTNode* r){
    root = r;
}

void RBTree::preorder(RBTNode* node){
    if(!node){
        return;
    }
    cout<<node->val<<endl;
    preorder(node->left);
    preorder(node->right);
}

void RBTree::inorder(RBTNode* node){
    if(!node){
        return;
    }
    inorder(node->left);
    cout<<node->val<<endl;
    inorder(node->right);
}

void RBTree::postorder(RBTNode* node){
    if(!node){
        return;
    }
    postorder(node->left);
    postorder(node->right);
    cout<<node->val<<endl;
}

void RBTree::insert(int val){
    RBTNode* node = new RBTNode(val, RED);
    RBTNode* parent = nullptr;
    RBTNode* cur = root;

    while(cur){
        parent = cur;
        if(val < cur->val){
            cur = cur->left;
        }
        else if(val == cur->val){
            return;
        }
        else{
            cur = cur->right;
        }
    }
    node->parent = parent;
    if(!parent){
        if(val < parent->val){
            parent->left = node;
        }
        else{
            parent->right = node;
        }
    }
    else{
        root = node;
        return;
    }
    insertFixUp(node);
}

void RBTree::remove(int val){
    RBTNode* node = root;
    bool find = false;
    while(node){
        if(val < node->val){
            node = node->left;
        }
        else if(node->val == val){
            find = true;
            break;
        }
        else if(node->val < val){
            node = node->right;
        }
    }
    if(!find){
        return;
    }

    RBTNode* child;
    RBTNode* parent;

    if(node->left && node->right){
        RBTNode* replace = node;
        replace = node->right;

        while(replace->left){
            replace = replace->left;
        }

        if(node->parent){
            if(node->parent->left == node){
                node->parent->left = replace;
            }
            else{
                node->parent->right = replace;
            }
        }
        else{
            root = replace;
        }
        child = replace->right;
        parent = replace->parent;
        RBTColor c = replace->color;
        if(parent == node){
            parent = replace;
        }
        else{
            if(child){
                child->parent = parent;
            }
            parent->left = child;
            replace->right = node->right;
            node->right->parent = replace;
        }

        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;

        if (c == BLACK)
            removeFixUp(child, parent);

        delete node;
        return;
    }

    if (node->left)
        child = node->left;
    else
        child = node->right;

    parent = node->parent;
    RBTColor c = node->color;

    if(child)
        child->parent = parent;

    if(parent){
        if (parent->left == node)
            parent->left = child;
        else
            parent->right = child;
    }
    else
        root = child;

    if (c == BLACK)
        removeFixUp(child, parent);
    delete node;
}

void RBTree::insertFixUp(RBTNode* node){
    RBTNode* parent;
    RBTNode* gparent;

    while((parent = node->parent) && parent->color == RED){
        gparent = parent->parent;

        if(parent == gparent->left){
            // Case 1: Uncle is Red
            {
                RBTNode* uncle = gparent->right;
                if (uncle && uncle->color == RED)
                {
                    uncle->color = BLACK;
                    parent->color = BLACK;
                    gparent->color = BLACK;
                    node = gparent;
                    continue;
                }
            }

            // Case 2: Uncle is Black, and node is right child
            if (parent->right == node)
            {
                RBTNode *tmp;
                leftRotate(parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }
            // Case 3: Uncle is Black, and node is left child
            parent->color = BLACK;
            gparent->color = RED;
            rightRotate(gparent);
        }
        else{
            // Case 1: Uncle is Red{
            RBTNode *uncle = gparent->left;
            if (uncle && uncle->color == RED){
                uncle->color = BLACK;
                parent->color = BLACK;
                gparent->color = BLACK;
                node = gparent;
                continue;
            }

            // Case 2: Uncle is Black, and node is left child
            if (parent->left == node){
                RBTNode *tmp;
                rightRotate(parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            // Case 3: Uncle is Black, and node is right child
            parent->color = BLACK;
            gparent->color = RED;
            leftRotate(gparent);
        }
    }
    root->color = BLACK;
}

void RBTree::leftRotate(RBTNode* x){
    if(!x){return;}

    RBTNode* y = x->right;
    if(!y){return;}
    x->right = y->left;
    if(!y->left){
        y->left->parent = x;
    }
    y->parent = x->parent;
    if(!x->parent){
        root = y;
    }
    else{
        if(x->parent->left == x){
            x->parent->left = y;
        }
        else{
            x->parent->right = y;
        }
    }
    y->left = x;
    x->parent = y;
}

void RBTree::rightRotate(RBTNode* x){
    if(!x){return;}
    RBTNode* y = x->left;
    if(!y){return;}
    x->left = y->right;
    if(!y->right){
        y->right->parent = x;
    }
    y->parent = x->parent;
    if(!x->parent){
        root = y;
    }
    else{
        if(x->parent->right == x){
            x->parent->right = y;
        }
        else{
            x->parent->left = y;
        }
    }
    y->right = x;
    x->parent = y;
}





