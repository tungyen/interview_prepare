#include "stl.h"

// Vector Class
vector::~vector(){
    delete[] data;
}

size_t vector::getSize()const{
    return size;
}

size_t vector::getCapacity()const{
    return capacity;
}

void vector::push_back(int val){
    if (size == capacity) {
        resize(capacity == 0 ? 1 : capacity * 2);
    }
    data[size++] = val;
}

void vector::pop_back(){
    if(size == 0){
        return;
    }
    size--;
}

void vector::erase(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    for (size_t i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
}

void vector::print(){
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

int& vector::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

void vector::resize(size_t new_capacity){
    int* new_data = new int[new_capacity];
    for(int i = 0;i<size;i++){
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
}

// Queue class
queue::~queue(){
    while(!empty()){
        pop();
    }
}

void queue::push(int val){
    queue::Node* newNode = new queue::Node(val);
    if(empty()){
        front = rear = newNode;
    }
    else{
        rear->next = newNode;
        rear = rear->next;
    }
}

void queue::pop(){
    if(empty()){
        return;
    }
    queue::Node* tmp = front;
    front = front->next;
    if(front == nullptr){
        rear = nullptr;
    }
    delete tmp;
}

bool queue::empty() const {
    return front == nullptr;
}

int queue::top(){
    return front->val;
}

// Class stack
stack::stack(int size){
    capacity = size;
    data = new int[size];
    idx = -1;
}
stack::~stack(){
    delete data;
}

void stack::push(int val){
    if(isFull()){
        return;
    }
    data[++idx] = val;
}

void stack::pop(){
    if(empty()){
        return;
    }
    idx--;
}

bool stack::empty() const {
    return idx == -1;
}

bool stack::isFull(){
    return idx == capacity-1;
}

int stack::top(){
    if(empty()){
        cout << "Stack is empty." << endl;
        return -1;
    }
    else{
        return data[idx];
    }
}
