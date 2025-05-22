#include <iostream>

template <typename T>
class List{
    class Node;
public:
    List();
    ~List();

    class Iterator;

    Iterator begin() {
        return Iterator(head_);
    }

    Iterator end() {
        return Iterator(nullptr);
    }

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

        // Prefix ++ overload
        Iterator& operator++() {
            if (currentNode)
                currentNode = currentNode->next;
            return *this;
        }

        // Postfix ++ overload
        Iterator operator++(int) {
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }

        bool operator!=(const Iterator& iterator) {
            return currentNode != iterator.currentNode;
        }

        T operator*() {
            return currentNode->data;
        }

    private:
        const Node* currentNode;
    };

    void delete_list();
    void push_back(T);
    void MergeSort();

private:
    struct Node{
        Node(T);
        T data;
        Node* next;
        Node* prev;
    };

    std::tuple<Node*, Node*> Merge(Node*, Node*,
                                   Node*, Node*);
    std::pair<Node*, Node*> Split(Node*);
    std::tuple<Node*, Node*> MergeSortHelper(Node*, Node*);
    void pop_front();

    Node* head_;
    Node* last_;
    int size_ = 0;
};
