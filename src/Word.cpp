#include "Word.hpp"

Word::Word(const std::string& termo) : termo(termo) {
}

std::string Word::getTermo() const { 
    return termo; 
}

const ListaEncadeada<Street*>& Word::getLogradouros() const { 
    return logradouros; 
}

void Word::adicionarLogradouro(Street* street) {
    logradouros.insert(street);
    // Ordena após inserir
    logradouros.sort();
}

void Word::ordenarLogradouros() {
    logradouros.sort();
}

bool Word::operator<(const Word& other) const {
    return termo < other.termo;
}

bool Word::operator==(const Word& other) const {
    return termo == other.termo;
}