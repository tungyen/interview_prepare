#include <iostream>
#include <STL.cpp>
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

int main()
{
    vectorTest();
    queueTest();
    stackTest();
    return 0;
}
