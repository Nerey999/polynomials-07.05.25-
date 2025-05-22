#include "List.h"

template <typename T>
List<T>::List() : head_(nullptr), last_(nullptr) {}

template <typename T>
List<T>::~List() {
    this->delete_list();
}

template<typename T>
List<T>::Iterator List<T>::begin() {
    return Iterator(head_);
}

template<typename T>
List<T>::Iterator List<T>::end() {
    return Iterator(nullptr);
}

template<typename T>
List<T>::Iterator List<T>::rbegin() {
    return Iterator(last_);
}

template<typename T>
List<T>::Iterator List<T>::rend() {
    return Iterator(nullptr);
}

template <typename T>
void List<T>::clear() {
    while (head_ != nullptr) {
        this->pop_front();
    }
}

template <typename T>
void List<T>::push_back(T data) {
    Node* now = new Node(data);
    size_++;
    if (head_ == nullptr) {
        head_ = now; 
        last_ = now;
        return;
    } 
    now -> prev = last_; 
    last_->next=now;
    last_ = now;
}

template <typename T>
void List<T>::MergeSort() {
    std::tie(head_, last_) = MergeSortHelper(head_, last_);
}

template <typename T>
List<T>::Node::Node(T data) : 
        data(data), next(nullptr), prev(nullptr) {}

template <typename T>
std::tuple<typename List<T>::Node*, typename List<T>::Node*> List<T>::Merge(Node* left_start, Node* left_end, Node* right_start, Node* right_end) {
    if (!left_start) return {right_start, right_end};
    if (!right_start) return {left_start, left_end};

    if (left_start->data < right_start->data) {
        std::tuple grs = Merge(left_start->next, left_end, right_start, right_end);
        left_start->next = std::get<0>(grs);
        left_start->next->prev = left_start;
        left_start->prev = nullptr;
        return {left_start, std::get<1>(grs)};
    } else {
        std::tuple grs = Merge(left_start, left_end, right_start->next, right_end);
        right_start->next = std::get<0>(grs);
        right_start->next->prev = right_start;
        right_start->prev = nullptr;
        return {right_start, std::get<1>(grs)};
    }
}

template <typename T>
std::pair<typename List<T>::Node*, typename List<T>::Node*> List<T>::Split(Node* head) {
    Node* fast = head;
    Node* slow = head;

    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node* temp = slow->next;
    slow->next = nullptr;
    temp->prev = nullptr;

    return {slow, temp};
}

template <typename T>
std::tuple<typename List<T>::Node*, typename List<T>::Node*> List<T>::MergeSortHelper(Node* head, Node* last) {
    if (head == last) {
        return {head, last};
    }

    std::pair<Node*, Node*> grs = Split(head);

    std::tie(head, grs.first) = MergeSortHelper(head, grs.first);
    std::tie(grs.second, last) = MergeSortHelper(grs.second, last);

    return Merge(head, grs.first, grs.second, last);
}

template <typename T>
void List<T>::pop_front() {
    Node* tmp = head_;
    if (head_->next != nullptr) {
        head_->next->prev = nullptr;
    }
    head_ = head_->next;
    delete tmp;
}


int main() {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    list.push_back(7);
    list.push_back(7);
    list.push_back(9);
    for (List<int>::Iterator iterator = list.begin();
            iterator != list.end(); iterator++) {
        std::cout << *iterator << ' ';
    }
    list.MergeSort();
    return 0;
}
