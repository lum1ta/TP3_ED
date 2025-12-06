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
    //Construtor
    Query();

    //Setters
    void setOrigin(double lat,double lon);
    void setMaxResults(int m);
    void addTerm(const std::string& t);

    //Functions
    void process(AVL& indice);
    // Interseção entre listas de Street*
    List<Street*> intersection(List<Street*>& A, List<Street*>& B);
    // Ordena pelo menor valor de distância
    void OrderResults(List<Street*>& results);
};
