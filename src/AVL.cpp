#include "AVL.hpp"
#include <iostream>

// Construtor
AVL::AVL() : root(nullptr) {}

// Destrutor
AVL::~AVL() {
    destroyTree(root);
}

// Destrói a árvore recursivamente
void AVL::destroyTree(AVLNode* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node->word; // Deleta o objeto Word
        delete node;
    }
}

// Calcula altura
int AVL::height(AVLNode* node) {
    return node ? node->height : 0;
}

// Calcula fator de balanceamento
int AVL::balanceFactor(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// Rotação à direita
AVLNode* AVL::rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    
    x->right = y;
    y->left = T2;
    
    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;
    
    return x;
}

// Rotação à esquerda
AVLNode* AVL::rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    
    y->left = x;
    x->right = T2;
    
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;
    
    return y;
}

// Inserção recursiva
AVLNode* AVL::insert(AVLNode* node, Word* word) {
    if (!node) return new AVLNode(word);
    
    if (word->getTermo() < node->word->getTermo()) {
        node->left = insert(node->left, word);
    } else if (word->getTermo() > node->word->getTermo()) {
        node->right = insert(node->right, word);
    } else {
        // Palavra já existe, adiciona logradouro
        return node;
    }
    
    // Atualiza altura
    node->height = 1 + std::max(height(node->left), height(node->right));
    
    // Verifica balanceamento
    int balance = balanceFactor(node);
    
    // Casos de desbalanceamento
    // Esquerda-Esquerda
    if (balance > 1 && word->getTermo() < node->left->word->getTermo()) {
        return rotateRight(node);
    }
    
    // Direita-Direita
    if (balance < -1 && word->getTermo() > node->right->word->getTermo()) {
        return rotateLeft(node);
    }
    
    // Esquerda-Direita
    if (balance > 1 && word->getTermo() > node->left->word->getTermo()) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    
    // Direita-Esquerda
    if (balance < -1 && word->getTermo() < node->right->word->getTermo()) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    
    return node;
}

// Busca recursiva
AVLNode* AVL::search(AVLNode* node, const std::string& termo) {
    if (!node || node->word->getTermo() == termo) {
        return node;
    }
    
    if (termo < node->word->getTermo()) {
        return search(node->left, termo);
    }
    
    return search(node->right, termo);
}

// Inserir palavra
void AVL::inserir(Word* word) {
    root = insert(root, word);
}

// Buscar palavra
Word* AVL::buscar(const std::string& termo) {
    AVLNode* node = search(root, termo);
    return node ? node->word : nullptr;
}

// Getter da raiz
AVLNode* AVL::getRoot() { 
    return root; 
}