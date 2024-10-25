#include <iostream>
#include <stl.h>
#include <tree.h>
#include <lru.h>
using namespace std;

//void vectorTest(){
//    cout<<"Vector Test!"<<endl;
//    Vector vec = Vector();
//    for(int i = 0;i<5;i++){
//        vec.push_back(i);
//    }
//    vec.print();
//    vec.pop_back();
//    vec.print();
//    vec.erase(2);
//    vec.print();
//}

//void queueTest(){
//    cout<<"Queue Test!"<<endl;
//    queue q = queue();
//    for(int i = 0;i<5;i++){
//        q.push(i);
//    }
//    cout<<q.top()<<endl;
//    q.pop();
//    q.pop();
//    cout<<q.top()<<endl;
//}

//void stackTest(){
//    cout<<"Stack Test!"<<endl;
//    stack st = stack();
//    for(int i = 0;i<5;i++){
//        st.push(i);
//    }
//    cout<<st.top()<<endl;
//    st.pop();
//    st.pop();
//    cout<<st.top()<<endl;
//}

//void splayTreeTest(){
//    SplayTree::Node* root = nullptr;
//    SplayTree splay = SplayTree(root);
//    root = splay.insert(root, 100);
//    root = splay.insert(root, 50);
//    root = splay.insert(root, 200);
//    root = splay.insert(root, 40);
//    root = splay.insert(root, 60);
//    cout << "Preorder traversal of the modified Splay tree:" << endl;
//    splay.preOrder(root);
//}

//void bstTest(){
//    BST::Node* root = nullptr;
//    BST bst = BST(root);
//    bst.insert(5);
//    bst.insert(6);
//    bst.insert(1);
//    bst.insert(10);
//    bst.insert(4);
//    bst.insert(2);
//    bst.inorder();
//    BST::Node* cur = bst.search(8);
//    BST::Node* cur2 = bst.search(4);
//    if(cur){cout<<"Found val: "<<cur->val<<endl;}
//    if(cur2){cout<<"Found val: "<<cur2->val<<endl;}
//    bst.remove(100);
//    bst.inorder();
//    bst.remove(4);
//    bst.inorder();
//}

void LRUCacheTest(){
    LRUCache lRUCache = LRUCache(2);
    lRUCache.put(1, 1); // cache is {1=1}
    lRUCache.put(2, 2); // cache is {1=1, 2=2}
    cout<<lRUCache.get(1)<<endl;    // return 1
    lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
    cout<<lRUCache.get(2)<<endl;    // returns -1 (not found)
    lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
    cout<<lRUCache.get(1)<<endl;    // return -1 (not found)
    cout<<lRUCache.get(3)<<endl;    // return 3
    cout<<lRUCache.get(4)<<endl;    // return 4
}

int main()
{
//    vectorTest();
//    queueTest();
//    stackTest();
//    splayTreeTest();
//    bstTest();
    LRUCacheTest();
    return 0;
}
