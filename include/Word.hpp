#ifndef WORD_HPP
#define WORD_HPP

#include "ListaEncadeada.hpp"
#include "Street.hpp"
#include <string>

class Word {
private:
    std::string termo;
    ListaEncadeada<Street*> logradouros;
    
public:
    Word(const std::string& termo = "");
    
    std::string getTermo() const;
    const ListaEncadeada<Street*>& getLogradouros() const;
    
    void adicionarLogradouro(Street* street);
    
    // Ordena a lista por ID (para interseção eficiente)
    void ordenarLogradouros();
    
    bool operator<(const Word& other) const;
    bool operator==(const Word& other) const;
};

#endif // WORD_HPP