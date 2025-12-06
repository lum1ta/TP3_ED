#include "AVLNode.hpp"

// Construtor
AVLNode::AVLNode(Word* w) 
    : word(w), left(nullptr), right(nullptr), height(1) {
}