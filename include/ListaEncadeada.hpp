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
    
    // Métodos privados para MergeSort
    Node* mergeSort(Node* start);
    Node* getMiddle(Node* start);
    Node* sortedMerge(Node* a, Node* b);
    
public:
    ListaEncadeada();
    ~ListaEncadeada();
    
    // Construtor de cópia
    ListaEncadeada(const ListaEncadeada& other);
    
    // Operador de atribuição
    ListaEncadeada& operator=(const ListaEncadeada& other);
    
    void insert(const T& value);
    void clear();
    int getSize() const;
    bool isEmpty() const;
    
    // Para iteração
    class Iterator {
    private:
        Node* current;
    public:
        Iterator(Node* node);
        bool hasNext() const;
        T& next();
    };
    
    Iterator getIterator() const;
    void sort(); // Ordena usando MergeSort
    
    // Método para mover dados (transferência de propriedade)
    void moveFrom(ListaEncadeada& other);
};

// Implementação do template inline no header
template <typename T>
ListaEncadeada<T>::ListaEncadeada() : head(nullptr), tail(nullptr), size(0) {}

template <typename T>
ListaEncadeada<T>::ListaEncadeada(const ListaEncadeada& other) 
    : head(nullptr), tail(nullptr), size(0) {
    // Copia os elementos
    Node* current = other.head;
    while (current) {
        insert(current->data);
        current = current->next;
    }
}

template <typename T>
ListaEncadeada<T>& ListaEncadeada<T>::operator=(const ListaEncadeada& other) {
    if (this != &other) {
        clear();
        // Copia os elementos
        Node* current = other.head;
        while (current) {
            insert(current->data);
            current = current->next;
        }
    }
    return *this;
}

template <typename T>
ListaEncadeada<T>::~ListaEncadeada() { clear(); }

template <typename T>
void ListaEncadeada<T>::insert(const T& value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

template <typename T>
void ListaEncadeada<T>::clear() {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
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
bool ListaEncadeada<T>::Iterator::hasNext() const { return current != nullptr; }

template <typename T>
T& ListaEncadeada<T>::Iterator::next() { 
    T& value = current->data;
    current = current->next;
    return value;
}

template <typename T>
typename ListaEncadeada<T>::Iterator ListaEncadeada<T>::getIterator() const { 
    return Iterator(head); 
}

template <typename T>
void ListaEncadeada<T>::sort() {
    if (!head || !head->next) return;
    
    head = mergeSort(head);
    
    // Atualiza tail
    Node* temp = head;
    while (temp && temp->next) {
        temp = temp->next;
    }
    tail = temp;
}

template <typename T>
void ListaEncadeada<T>::moveFrom(ListaEncadeada& other) {
    clear();
    head = other.head;
    tail = other.tail;
    size = other.size;
    
    other.head = nullptr;
    other.tail = nullptr;
    other.size = 0;
}

template <typename T>
typename ListaEncadeada<T>::Node* ListaEncadeada<T>::mergeSort(Node* start) {
    if (!start || !start->next) return start;
    
    Node* middle = getMiddle(start);
    Node* nextOfMiddle = middle->next;
    middle->next = nullptr;
    
    Node* left = mergeSort(start);
    Node* right = mergeSort(nextOfMiddle);
    
    return sortedMerge(left, right);
}

template <typename T>
typename ListaEncadeada<T>::Node* ListaEncadeada<T>::getMiddle(Node* start) {
    if (!start) return start;
    
    Node* slow = start;
    Node* fast = start->next;
    
    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    return slow;
}

template <typename T>
typename ListaEncadeada<T>::Node* ListaEncadeada<T>::sortedMerge(Node* a, Node* b) {
    if (!a) return b;
    if (!b) return a;
    
    Node* result = nullptr;
    
    // Ordena por ID (para interseção eficiente)
    if (a->data <= b->data) {
        result = a;
        result->next = sortedMerge(a->next, b);
    } else {
        result = b;
        result->next = sortedMerge(a, b->next);
    }
    
    return result;
}

#endif // LISTAENCADEADA_HPP