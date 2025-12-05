#include "List.hpp"
#include <iostream>


List::List() : start(nullptr), end(nullptr), size(0) {}


List::~List() {
Node* atual = start;
while (atual) {
Node* temp = atual->next;
delete atual;
atual = temp;
}
}

void List::insertStart(int v) {
Node* novo = new Node(v);
if (!start) {
start = end = novo;
} else {
novo->next = start;
start->ant = novo;
start = novo;
}
size++;
}

void List::insertEnd(int v) {
Node* novo = new Node(v);
if (!end) {
start = end = novo;
} else {
end->next = novo;
novo->ant = end;
end = novo;
}
size++;
}

bool List::remove(int v) {
Node* atual = start;
while (atual) {
if (atual->data == v) {
if (atual->ant)
atual->ant->next = atual->next;
else
start = atual->next;

if (atual->next)
atual->next->ant = atual->ant;
else
end = atual->ant;

delete atual;
size--;
return true;
}
atual = atual->next;
}
return false;
}

bool List::search(int v) const {
Node* atual = start;
while (atual) {
if (atual->data == v) return true;
atual = atual->next;
}
return false;
}

void List::print() const {
Node* atual = start;
while (atual) {
std::cout << atual->data << " <-> ";
atual = atual->next;
}
std::cout << "NULL" << std::endl;
}

int List::getsize() const {
return size;
}