#ifndef AVL_HPP
#define AVL_HPP
#include "Street.hpp"
#include "List.hpp"

class AVL {
public:
    struct Node {
        int key;
        List<Street*> list;
        Node* left;
        Node* right;
        int height;
        Node(int k);
    };

    AVL() : root(nullptr) {}
    Node* searchNodePtr(int key);
    void insert(int key);
    void remove(int key);
    bool search(int key);
    void printInOrder();

private:
    Node* root;

    // Auxiliares
    int height(Node* n);
    int getBalance(Node* n);
    int maxLocal(int a, int b);

    Node* insertNode(Node* node, int key);
    Node* removeNode(Node* node, int key);
    bool searchNode(Node* node, int key);

    // Rotações
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);

    // Print
    void inOrder(Node* node);
};

#endif
