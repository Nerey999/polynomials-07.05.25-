#include <iostream>
#include <ctime>

template <typename T>
class List{
public:
    List();
    ~List();

    void delete_list();
    void add(T);
    void MergeSort();

private:
    struct Node{
        T data;
        Node* next;
        Node* prev;
        Node(T);
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
