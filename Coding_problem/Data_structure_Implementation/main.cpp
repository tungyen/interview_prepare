#include <iostream>
#include <stl.h>
#include <tree.h>
using namespace std;

void vectorTest(){
    cout<<"Vector Test!"<<endl;
    vector vec = vector();
    for(int i = 0;i<5;i++){
        vec.push_back(i);
    }
    vec.print();
    vec.pop_back();
    vec.print();
    vec.erase(2);
    vec.print();
}

void queueTest(){
    cout<<"Queue Test!"<<endl;
    queue q = queue();
    for(int i = 0;i<5;i++){
        q.push(i);
    }
    cout<<q.top()<<endl;
    q.pop();
    q.pop();
    cout<<q.top()<<endl;
}

void stackTest(){
    cout<<"Stack Test!"<<endl;
    stack st = stack();
    for(int i = 0;i<5;i++){
        st.push(i);
    }
    cout<<st.top()<<endl;
    st.pop();
    st.pop();
    cout<<st.top()<<endl;
}

void splayTreeTest(){
    SplayTree::Node* root = nullptr;
    SplayTree splay = SplayTree(root);
    root = splay.insert(root, 100);
    root = splay.insert(root, 50);
    root = splay.insert(root, 200);
    root = splay.insert(root, 40);
    root = splay.insert(root, 60);
    cout << "Preorder traversal of the modified Splay tree:" << endl;
    splay.preOrder(root);
}

int main()
{
    vectorTest();
    queueTest();
    stackTest();
    splayTreeTest();
    return 0;
}
