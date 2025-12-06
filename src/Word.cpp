#include "Word.hpp"
#include <iostream>

// Adiciona uma ocorrência do termo associando a um logradouro
void Word::addOcc(std::string t, Street* log) {
    // Caso ainda não exista termo definido neste objeto
    if (termo.empty()) {
        termo = t;
    }

    // Só adiciona se o termo bater
    if (termo == t && log != nullptr) {
        logra.push_back(log);
    }
}

// Busca e imprime os logradouros associados ao termo
void Word::searchLog(std::string t) {
    if (termo != t) {
        std::cout << "Termo \"" << t << "\" nao encontrado.\n";
        return;
    }

    if (logra.empty()) {
        std::cout << "Nenhum logradouro associado ao termo \"" << t << "\".\n";
        return;
    }

    std::cout << "Logradouros contendo o termo \"" << t << "\":\n";

    // Percorre a lista
    ListNode<Street*>* aux = logra.getHead();

    while (aux != nullptr) {
        // Aqui você pode ajustar conforme o que Street expõe
        // Exemplo:
        // std::cout << aux->data->getNome() << std::endl;

        aux = aux->next;
    }
}
