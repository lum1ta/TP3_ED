#include "AVL.hpp"
#include <iostream>

using namespace std;

//Constructor
AVL::Node::Node(int k)
    : key(k), left(nullptr), right(nullptr), height(1) {}


//functions
int AVL::height(Node* n) {
    return (n == nullptr) ? 0 : n->height;
}

int AVL::maxLocal(int a, int b) {
    return (a > b) ? a : b;
}

int AVL::getBalance(Node* n) {
    if (n == nullptr)
        return 0;
    return height(n->left) - height(n->right);
}
AVL::Node* AVL::searchNodePtr(int key) {
    Node* atual = root;

    while (atual) {
        if (key == atual->key)
            return atual;
        else if (key < atual->key)
            atual = atual->left;
        else
            atual = atual->right;
    }

    return nullptr;
}
void AVL::insertStreet(int key, Street* s) {
    Node* n = searchNodePtr(key);
    if (n)
        n->list.push_back(s);
}
void AVL::insert(int key, Street* s) {
    // garante que o nó existe
    root = insertNode(root, key);

    // adiciona a rua à lista do nó
    insertStreet(key, s);
}

//Rotations
AVL::Node* AVL::rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Rotação
    x->right = y;
    y->left = T2;

    // Update height
    y->height = maxLocal(height(y->left), height(y->right)) + 1;
    x->height = maxLocal(height(x->left), height(x->right)) + 1;

    return x;
}

AVL::Node* AVL::leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Rotation
    y->left = x;
    x->right = T2;

    // Update height
    x->height = maxLocal(height(x->left), height(x->right)) + 1;
    y->height = maxLocal(height(y->left), height(y->right)) + 1;

    return y;
}


//Insertion
AVL::Node* AVL::insertNode(Node* node, int key) {
    //inserção
    if (node == nullptr)
        return new Node(key);

    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else
        return node; // chaves duplicadas não entram

    // update height
    node->height = 1 + maxLocal(height(node->left), height(node->right));

    // balancement
    int balance = getBalance(node);

    // Casos de desbalanceamento
    // LL
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // RR
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // LR
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void AVL::insert(int key) {
    root = insertNode(root, key);
}


//Search
bool AVL::searchNode(Node* node, int key) {
    if (node == nullptr)
        return false;

    if (key == node->key)
        return true;
    else if (key < node->key)
        return searchNode(node->left, key);
    else
        return searchNode(node->right, key);
}

bool AVL::search(int key) {
    return searchNode(root, key);
}


//Remove
AVL::Node* AVL::removeNode(Node* node, int key) {
    if (node == nullptr)
        return node;

    if (key < node->key)
        node->left = removeNode(node->left, key);
    else if (key > node->key)
        node->right = removeNode(node->right, key);
    else {
        // Nó com 0 ou 1 filho
        if (node->left == nullptr || node->right == nullptr) {
            Node* temp = node->left ? node->left : node->right;

            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
            delete temp;
        } else {
            // Nó com dois filhos
            Node* temp = node->right;
            while (temp->left != nullptr)
                temp = temp->left;

            node->key = temp->key;
            node->right = removeNode(node->right, temp->key);
        }
    }

    if (node == nullptr)
        return node;

    // Atualiza altura
    node->height = 1 + maxLocal(height(node->left), height(node->right));

    // Balanceamento
    int balance = getBalance(node);

    // LL
    if (balance > 1 && getBalance(node->left) >= 0)
        return rightRotate(node);

    // LR
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RR
    if (balance < -1 && getBalance(node->right) <= 0)
        return leftRotate(node);

    // RL
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void AVL::remove(int key) {
    root = removeNode(root, key);
}


//Path
void AVL::inOrder(Node* node) {
    if (node != nullptr) {
        inOrder(node->left);
        cout << node->key << " ";
        inOrder(node->right);
    }
}

void AVL::printInOrder() {
    inOrder(root);
    cout << endl;
}
