#include "lru.h"


LRUCache::LRUCache(int capacity){
    cap = capacity;
    head = nullptr;
    tail = nullptr;
    cnt = 0;
}

LRUCache::~LRUCache(){

}

int LRUCache::get(int key){

    // If not in the cache
    if(!mp[key].second){
        return -1;
    }

    // If in the cache
    int value = mp[key].first;
    Node* node = mp[key].second;

    // Update it to the front of cache
    addNode(key, value);
    deleteNode(node);
    return value;
}

void LRUCache::put(int key, int value){

    // If the cache is not full
    if(cnt < cap){
        // Check if the key exist
        if(mp[key].second){
            Node* node = mp[key].second;
            deleteNode(node);
        }
        addNode(key, value);
        cnt++;
    }
    else{
        deleteNode(tail);
        addNode(key, value);
    }
}

void LRUCache::addNode(int key, int value){
    if(!head && !tail){
        head = tail = new Node(key);
        mp[key] = {value, head};
    }
    else{
        Node* node = new Node(key);
        node->next = head;
        head->prev = node;
        head = node;
        mp[key] = {value, node};
    }
}

void LRUCache::deleteNode(Node* node){
    if(!node){return;}
    int key = node->key;
    mp[key] = {INT_MIN, nullptr};
    if(node == tail){
        tail = tail->prev;
        tail->next = nullptr;
        delete node;
        return;
    }

    Node* next = node->next;
    node->prev->next = next;
    next->prev = node->prev;
    delete node;
}


