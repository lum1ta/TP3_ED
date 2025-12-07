#ifndef LISTAENCADEADA_HPP
#define LISTAENCADEADA_HPP

#include <iostream>

template <typename T>
class ListaEncadeada {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

    Node* mergeSort(Node* start);
    Node* getMiddle(Node* start);
    Node* sortedMerge(Node* a, Node* b);

    // ✅ comparação genérica (fallback)
    bool lessOrEqual(const T& a, const T& b) {
        return a <= b;
    }

public:
    ListaEncadeada();
    ~ListaEncadeada();

    ListaEncadeada(const ListaEncadeada& other);
    ListaEncadeada& operator=(const ListaEncadeada& other);

    void insert(const T& value);
    void clear();
    int getSize() const;
    bool isEmpty() const;

    class Iterator {
    private:
        Node* current;
    public:
        Iterator(Node* node);
        bool hasNext() const;
        T& next();
    };

    Iterator getIterator() const;
    void sort();
};

// ================= IMPLEMENTAÇÃO =================

template <typename T>
ListaEncadeada<T>::ListaEncadeada() : head(nullptr), tail(nullptr), size(0) {}

template <typename T>
ListaEncadeada<T>::ListaEncadeada(const ListaEncadeada& other)
    : head(nullptr), tail(nullptr), size(0) {
    Node* cur = other.head;
    while (cur) {
        insert(cur->data);
        cur = cur->next;
    }
}

template <typename T>
ListaEncadeada<T>& ListaEncadeada<T>::operator=(const ListaEncadeada& other) {
    if (this != &other) {
        clear();
        Node* cur = other.head;
        while (cur) {
            insert(cur->data);
            cur = cur->next;
        }
    }
    return *this;
}

template <typename T>
ListaEncadeada<T>::~ListaEncadeada() {
    clear();
}

template <typename T>
void ListaEncadeada<T>::insert(const T& value) {
    Node* n = new Node(value);
    if (!head) {
        head = tail = n;
    } else {
        tail->next = n;
        tail = n;
    }
    size++;
}

template <typename T>
void ListaEncadeada<T>::clear() {
    Node* cur = head;
    while (cur) {
        Node* nxt = cur->next;
        delete cur;
        cur = nxt;
    }
    head = tail = nullptr;
    size = 0;
}

template <typename T>
int ListaEncadeada<T>::getSize() const { return size; }

template <typename T>
bool ListaEncadeada<T>::isEmpty() const { return size == 0; }

template <typename T>
ListaEncadeada<T>::Iterator::Iterator(Node* node) : current(node) {}

template <typename T>
bool ListaEncadeada<T>::Iterator::hasNext() const {
    return current != nullptr;
}

template <typename T>
T& ListaEncadeada<T>::Iterator::next() {
    T& val = current->data;
    current = current->next;
    return val;
}

template <typename T>
typename ListaEncadeada<T>::Iterator ListaEncadeada<T>::getIterator() const {
    return Iterator(head);
}

template <typename T>
void ListaEncadeada<T>::sort() {
    if (!head || !head->next) return;
    head = mergeSort(head);
    Node* t = head;
    while (t && t->next) t = t->next;
    tail = t;
}

template <typename T>
typename ListaEncadeada<T>::Node*
ListaEncadeada<T>::mergeSort(Node* start) {
    if (!start || !start->next) return start;

    Node* mid = getMiddle(start);
    Node* right = mid->next;
    mid->next = nullptr;

    Node* leftSorted = mergeSort(start);
    Node* rightSorted = mergeSort(right);

    return sortedMerge(leftSorted, rightSorted);
}

template <typename T>
typename ListaEncadeada<T>::Node*
ListaEncadeada<T>::getMiddle(Node* start) {
    Node* slow = start;
    Node* fast = start->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

template <typename T>
typename ListaEncadeada<T>::Node*
ListaEncadeada<T>::sortedMerge(Node* a, Node* b) {
    if (!a) return b;
    if (!b) return a;

    Node* result;
    if (lessOrEqual(a->data, b->data)) {
        result = a;
        result->next = sortedMerge(a->next, b);
    } else {
        result = b;
        result->next = sortedMerge(a, b->next);
    }
    return result;
}

#endif
