#ifndef LIST_HPP
#define LIST_HPP

class List{
private:
struct Node {
int data;
Node* ant;
Node* next;
Node(int v) : data(v), ant(nullptr), next(nullptr) {}
};

Node* start;
Node* end;
int size;

public:
List();
~List();

void insertStart(int v);
void insertEnd(int v);
bool remove(int v);
bool search(int v) const;
void print() const;
int getsize() const;
};

#endif

