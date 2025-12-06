#ifndef QUERY_HPP
#define QUERY_HPP

#include "AVL.hpp"
#include "Street.hpp"
#include "ListaEncadeada.hpp"
#include <string>

// Estrutura para resultados
struct ResultadoQuery {
    int id;
    std::string nome;
    double distancia;
};

class Query {
private:
    double originLat;
    double originLon;
    int maxResults;
    ListaEncadeada<std::string> termos;
    
public:
    Query();
    
    void setOrigin(double lat, double lon);
    void setMaxResults(int max);
    void addTerm(const std::string& term);
    void clearTerms();
    
    // Processa e retorna resultados via array (sem vector)
    void processarComResultados(AVL& indice, ResultadoQuery** resultados, int& numResultados);
    
    double getOriginLat() const;
    double getOriginLon() const;
    int getMaxResults() const;
    int getTermCount() const;
    
private:
    void toUpperString(std::string& str);
    double calculateDistance(double lat1, double lon1, double lat2, double lon2) const;
    
    ListaEncadeada<Street*> intersecaoListas(
        const ListaEncadeada<Street*>& lista1, 
        const ListaEncadeada<Street*>& lista2);
    
    // MergeSort para ordenar por distância
    void mergeSort(ResultadoQuery* arr, ResultadoQuery* temp, int left, int right);
    void merge(ResultadoQuery* arr, ResultadoQuery* temp, int left, int mid, int right);
};

#endif // QUERY_HPP