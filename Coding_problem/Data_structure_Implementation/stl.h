#ifndef STL_H
#define STL_H

#include <iostream>
using namespace std;

class vector{
public:
    vector():data(nullptr), size(0), capacity(0){}
    ~vector();

    size_t getSize() const;
    size_t getCapacity() const;

    void push_back(int val);
    void pop_back();
    void erase(size_t index);
    void print();
    int& operator[](size_t index);

private:
    int* data;
    int size;
    int capacity;
    void resize(size_t new_capacity);
};

class queue{

public:
    queue():front(nullptr), rear(nullptr){}
    ~queue();

    struct Node{
        int val;
        Node* next;
        Node(int v):val(v), next(nullptr){}
    };

    void push(int val);
    void pop();
    bool empty() const;
    int top();
private:
    Node* front;
    Node* rear;
};

class stack{
private:
    int* data;
    int capacity;
    int idx;

public:
    stack(int size = 1000);
    ~stack();

    void push(int val);
    void pop();
    bool empty() const;
    bool isFull();
    int top();
};


#endif // STL_H
