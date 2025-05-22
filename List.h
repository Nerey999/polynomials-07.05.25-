#pragma once
#include <iostream>
#include <functional>
#include <list>

#include "Polynomial.h"
#include "Monomial.h"


template<typename T>
struct is_pointer{
    static const bool value = false;
};

template<typename T>
struct is_pointer<T*>{
    static const bool value = true;
};

template <bool, class T = void> 
struct enable_if 
{};

template <class T> 
struct enable_if<true, T> 
{ 
  typedef T type; 
};

template <bool, class T = void> 
struct disable_if 
{};

template <class T> 
struct disable_if<false, T> 
{ 
  typedef T type; 
};

template <typename T>
class List{
    struct Node;
public:
    List();
    List(List&);
    ~List();

    class Iterator;
    Iterator begin();
    Iterator end();
    Iterator rbegin();
    Iterator rend();

    class Iterator {
     public:
        Iterator() noexcept :
            currentNode (head_) { }

        Iterator(const Node* pNode) noexcept :
            currentNode (pNode) { }

        Iterator& operator=(Node* pNode) {
            this->currentNode = pNode;
            return *this;
        }

        Iterator& operator++() {
            if (currentNode)
                currentNode = currentNode->next;
            return *this;
        }

        Iterator operator++(int) {
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }

        Iterator& operator--() {
            if (currentNode)
                currentNode = currentNode->prev;
            return *this;
        }

        Iterator operator--(int) {
            Iterator iterator = *this;
            --*this;
            return iterator;
        }

        bool operator!=(const Iterator& iterator) {
            return currentNode != iterator.currentNode;
        }

        T operator*() {
            return currentNode->data;
        }

        friend Iterator List<T>::erase(Iterator);
        friend Iterator List<T>::rerase(Iterator);
    private:
        const Node* currentNode;
    };

    int size();
    void clear();
    void push_back(T);
    Iterator erase(Iterator);
    Iterator rerase(Iterator);
    void pop_front();
    void pop_back();
    void MergeSort(const std::function <bool (T, T)>& lower = [](T a, T b) {return a < b;});

private:
    template<class U>
    void free_helper( typename enable_if< is_pointer<U>::value >::type *dummy=0 ){
        delete dummy;
    }

    template<class U>
    void free_helper( typename disable_if< is_pointer<U>::value >::type *dummy=0 ){

    }

    struct Node{
        Node(T);
        T data;
        Node* next;
        Node* prev;
    };

    std::tuple<Node*, Node*> Merge(Node*, Node*,
                                   Node*, Node*, const std::function <bool (T, T)>&);
    std::pair<Node*, Node*> Split(Node*);
    std::tuple<Node*, Node*> MergeSortHelper(Node*, Node*, const std::function <bool (T, T)>&);

    static Node* head_;
    static Node* last_;
    int size_ = 0;
};

template <typename T>
/*static*/ typename List<T>::Node* List<T>::head_ = nullptr;

template <typename T>
/*static*/ typename List<T>::Node* List<T>::last_ = nullptr;
