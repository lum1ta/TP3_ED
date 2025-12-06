#pragma once
#include <string>
#include "List.hpp"
#include "AVL.hpp"
#include "Street.hpp"

class Query {
private:
    std::string idQuery;
    List<std::string> termo;
    double LatOrigin;
    double LongOrigin;
    int Maxresults;

public:
    void process(AVL& indice);

private:
    // Interseção entre listas de Street*
    List<Street*> intersection(List<Street*>& A, List<Street*>& B);

    // Ordena pelo menor valor de distância
    void OrderResults(List<Street*>& results);
};
