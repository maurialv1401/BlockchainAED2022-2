#ifndef PRAED_NODE_H
#define PRAED_NODE_H

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node(){ 
        this->next = nullptr;
        this->prev = nullptr;
    }

    Node(T value){
        this->data = value;
        this->next = nullptr;
        this->prev = nullptr;
    }

    Node<T>(const Node<T>& other){
        this->data = other.data;
        this->next = other.next;
        this->prev =  other.prev;
    }

     Node<T>& operator=(const Node<T>& other) {
        this->data = other.data;
        this->next = other.next;
        this->prev =  other.prev;
        return *this;
    }

    void killSelf(){
        if(this->next != nullptr){
            this->next->killSelf();
        }
        delete this;
    }    
};

#endif