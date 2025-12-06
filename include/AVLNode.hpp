#ifndef AVLNODE_HPP
#define AVLNODE_HPP

#include "Word.hpp"

class AVLNode {
public:
    Word* word;
    AVLNode* left;
    AVLNode* right;
    int height;
    
    // Construtor
    AVLNode(Word* w);
};

#endif // AVLNODE_HPP