#ifndef AVL_HPP
#define AVL_HPP

#include "Word.hpp"
#include "AVLNode.hpp"
#include <algorithm>

class AVL {
private:
    AVLNode* root;
    
    // Métodos auxiliares privados
    int height(AVLNode* node);
    int balanceFactor(AVLNode* node);
    AVLNode* rotateRight(AVLNode* y);
    AVLNode* rotateLeft(AVLNode* x);
    AVLNode* insert(AVLNode* node, Word* word);
    AVLNode* search(AVLNode* node, const std::string& termo);
    
public:
    // Construtor e destrutor
    AVL();
    ~AVL();
    
    // Métodos públicos
    void inserir(Word* word);
    Word* buscar(const std::string& termo);
    
    // Getter
    AVLNode* getRoot();
    
private:
    // Método auxiliar para destruir a árvore
    void destroyTree(AVLNode* node);
};

#endif // AVL_HPP