#include "Query.hpp"

// Executa a query e gera o ranking
void Query::process(AVL& indice) {

    List<Street*> resultadoFinal;
    bool primeiro = true;

    ListNode<std::string>* t = termo.getHead();

    while (t) {

        int key = std::stoi(t->data); // hash / chave

        AVL::Node* no = indice.searchNodePtr(key);

        if (!no) return; // termo não encontrado

        if (primeiro) {
            resultadoFinal = no->list;
            primeiro = false;
        } else {
            resultadoFinal = intersection(resultadoFinal, no->list);
        }

        t = t->next;
    }

    OrderResults(resultadoFinal);
}

// Interseção entre duas listas
List<Street*> Query::intersection(List<Street*>& A, List<Street*>& B) {

    List<Street*> inter;

    ListNode<Street*>* a = A.getHead();

    while (a) {

        ListNode<Street*>* b = B.getHead();

        while (b) {

            if (a->data == b->data) {   // comparação 
                inter.push_back(a->data);
                break;
            }

            b = b->next;
        }

        a = a->next;
    }

    return inter;
}

// Ordenação por distância
void Query::OrderResults(List<Street*>& results) {

    if (results.empty()) return;

    bool trocou;

    do {
        trocou = false;

        ListNode<Street*>* atual = results.getHead();

        while (atual && atual->next) {

            double d1 = atual->data->getDist(LatOrigin, LongOrigin);
            double d2 = atual->next->data->getDist(LatOrigin, LongOrigin);

            if (d1 > d2) {
                Street* tmp = atual->data;
                atual->data = atual->next->data;
                atual->next->data = tmp;
                trocou = true;
            }

            atual = atual->next;
        }

    } while (trocou);
}
