#pragma once
#include <iostream>
#include <stdexcept>

template <typename T>
class ListNode {
public:
    T data;
    ListNode<T>* prev;
    ListNode<T>* next;

    ListNode(const T& value)
        : data(value), prev(nullptr), next(nullptr) {}
};

template <typename T>
class List {
protected:
    ListNode<T>* head;
    ListNode<T>* tail;

public:
    // Construtor
    List() : head(nullptr), tail(nullptr) {}
    ListNode<T>* getHead() const{
        return head;
    }

    // Destrutor
    ~List() {
        while (!empty())
            pop_front();
    }

    // Verifica se a lista está vazia
    bool empty() const {
        return head == nullptr;
    }

    // Insere no início
    void push_front(const T& data) {
        ListNode<T>* node = new ListNode<T>(data);

        if (empty()) {
            head = tail = node;
        } else {
            node->next = head;
            head->prev = node;
            head = node;
        }
    }

    // Insere no final
    void push_back(const T& data) {
        ListNode<T>* node = new ListNode<T>(data);

        if (empty()) {
            head = tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }

    // Remove do início
    void pop_front() {
        if (empty())
            throw std::runtime_error("Lista vazia");

        ListNode<T>* temp = head;

        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }

        delete temp;
    }

    // Remove do final
    void pop_back() {
        if (empty())
            throw std::runtime_error("Lista vazia");

        ListNode<T>* temp = tail;

        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }

        delete temp;
    }

    // Impressão
    friend std::ostream& operator<<(std::ostream& out, const List<T>& list) {
        ListNode<T>* current = list.head;
        while (current) {
            out << current->data;
            if (current->next)
                out << " <-> ";
            current = current->next;
        }
        return out;
    }
};
