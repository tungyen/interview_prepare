#include <iostream>
using namespace std;

struct Node{
    int val;
    Node* next;

    Node(int v):val(v), next(nullptr){}
};

class vector{
public:
    vector():data(nullptr), size(0), capacity(0){}
    ~vector(){
        delete[] data;
    }

    size_t getSize()const{
        return size;
    }

    size_t getCapacity()const{
        return capacity;
    }

    void push_back(int val){
        if (size == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[size++] = val;
    }

    void pop_back(){
        if(size == 0){
            return;
        }
        size--;
    }

    void erase(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        for (size_t i = index; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        size--;
    }

    void print(){
        for(int i = 0;i<size;i++){
            if(i == 0){
                cout<<data[i];
            }
            else{
                cout<<" "<<data[i];
            }
        }
        cout<<endl;
    }

    int& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

private:
    int* data;
    int size;
    int capacity;

    void resize(size_t new_capacity){
        int* new_data = new int[new_capacity];
        for(int i = 0;i<size;i++){
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }
};

class queue{
private:
    Node* front;
    Node* rear;

public:
    queue():front(nullptr), rear(nullptr){}
    ~queue(){
        while(!empty()){
            pop();
        }
    }

    void push(int val){
        Node* newNode = new Node(val);
        if(empty()){
            front = rear = newNode;
        }
        else{
            rear->next = newNode;
            rear = rear->next;
        }
    }

    void pop(){
        if(empty()){
            return;
        }
        Node* tmp = front;
        front = front->next;
        if(front == nullptr){
            rear = nullptr;
        }
        delete tmp;
    }

    bool empty() const {
        return front == nullptr;
    }

    int top(){
        return front->val;
    }
};

class stack{
private:
    int* data;
    int capacity;
    int idx;

public:
    stack(int size = 1000){
        capacity = size;
        data = new int[size];
        idx = -1;
    }
    ~stack(){
        delete data;
    }

    void push(int val){
        if(isFull()){
            return;
        }
        data[++idx] = val;
    }

    void pop(){
        if(empty()){
            return;
        }
        idx--;
    }

    bool empty() const {
        return idx == -1;
    }

    bool isFull(){
        return idx == capacity-1;
    }

    int top(){
        if(empty()){
            cout << "Stack is empty." << endl;
            return -1;
        }
        else{
            return data[idx];
        }
    }
};
