#include "AVL.hpp"
#include <iostream>

// Construtor do nó
AVL::Node::Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}

// Funções auxiliares
int AVL::height(Node* n) {
    return n ? n->height : 0;
}

int AVL::maxLocal(int a, int b) {
    return (a > b ? a : b);
}

int AVL::getBalance(Node* n) {
    if (!n) return 0;
    return height(n->left) - height(n->right);
}

// Rotações
AVL::Node* AVL::rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = maxLocal(height(y->left), height(y->right)) + 1;
    x->height = maxLocal(height(x->left), height(x->right)) + 1;

    return x;
}

AVL::Node* AVL::leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = maxLocal(height(x->left), height(x->right)) + 1;
    y->height = maxLocal(height(y->left), height(y->right)) + 1;

    return y;
}

// Inserção
void AVL::insert(int key) {
    root = insertNode(root, key);
}

AVL::Node* AVL::insertNode(Node* node, int key) {
    if (!node) return new Node(key);

    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else
        return node; // repetido

    node->height = 1 + maxLocal(height(node->left), height(node->right));

    int balance = getBalance(node);

    // 4 casos de desbalanceamento
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Remoção
void AVL::remove(int key) {
    root = removeNode(root, key);
}

AVL::Node* AVL::removeNode(Node* node, int key) {
    if (!node) return node;

    if (key < node->key)
        node->left = removeNode(node->left, key);
    else if (key > node->key)
        node->right = removeNode(node->right, key);
    else {
        // nó encontrado
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;

            if (!temp) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }

            delete temp;
        } else {
            // sucessor
            Node* temp = node->right;
            while (temp->left)
                temp = temp->left;

            node->key = temp->key;
            node->right = removeNode(node->right, temp->key);
        }
    }

    if (!node) return nullptr;

    node->height = 1 + maxLocal(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0)
        return rightRotate(node);

    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && getBalance(node->right) <= 0)
        return leftRotate(node);

    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}


// Busca
bool AVL::search(int key) {
    return searchNode(root, key);
}

bool AVL::searchNode(Node* node, int key) {
    if (!node) return false;
    if (key == node->key) return true;
    if (key < node->key) return searchNode(node->left, key);
    return searchNode(node->right, key);
}

// Impressão
void AVL::printInOrder() {
    inOrder(root);
    std::cout << std::endl;
}

void AVL::inOrder(Node* node) {
    if (!node) return;
    inOrder(node->left);
    std::cout << node->key << " ";
    inOrder(node->right);
}
