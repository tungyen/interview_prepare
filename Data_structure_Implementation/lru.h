#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <iostream>
#include <unordered_map>
using namespace std;

class LRUCache
{
    class Node{
        public:
            int key;
            Node* prev;
            Node* next;
            Node(int key){
                this->key = key;
                prev = nullptr;
                next = nullptr;
            }
    };

    public:
        int cap;
        int cnt;
        Node* head;
        Node* tail;
        unordered_map<int, pair<int ,Node*>> mp;
        LRUCache(int capacity);
        ~LRUCache();
        int get(int key);
        void put(int key, int value);
    private:
        void addNode(int key, int value);
        void deleteNode(Node* node);
};

#endif // LRUCACHE_H
