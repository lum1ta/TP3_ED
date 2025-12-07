#include "Word.hpp"
#include "ListaEncadeada.hpp"
template<>
bool ListaEncadeada<Street*>::lessOrEqual(Street* const& a, Street* const& b) {
    return a->getId() <= b->getId();
}


Word::Word(const std::string& termo) : termo(termo) {}

std::string Word::getTermo() const {
    return termo;
}

const ListaEncadeada<Street*>& Word::getLogradouros() const {
    return logradouros;
}

void Word::adicionarLogradouro(Street* street) {
    auto it = logradouros.getIterator();
    while (it.hasNext()) {
        Street* s = it.next();
        if (s->getId() == street->getId()) {
            return; // já existe, não insere
        }
    }

    logradouros.insert(street);
    logradouros.sort();  // mantém ordenado por ID
}

bool Word::operator<(const Word& other) const {
    return termo < other.termo;
}

bool Word::operator==(const Word& other) const {
    return termo == other.termo;
}
