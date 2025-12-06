#include "Query.hpp"
#include <iostream>
#include <cmath>
#include <cstring>
#include <iomanip>

// Construtor
Query::Query() : originLat(0.0), originLon(0.0), maxResults(10) {
}

// Setters
void Query::setOrigin(double lat, double lon) {
    originLat = lat;
    originLon = lon;
}

void Query::setMaxResults(int max) {
    if (max > 0) maxResults = max;
}

void Query::addTerm(const std::string& term) {
    termos.insert(term);
}

void Query::clearTerms() {
    termos.clear();
}

// Getters
double Query::getOriginLat() const { return originLat; }
double Query::getOriginLon() const { return originLon; }
int Query::getMaxResults() const { return maxResults; }
int Query::getTermCount() const { return termos.getSize(); }

void Query::toUpperString(std::string& str) {
    for (char& c : str) {
        if (c >= 'a' && c <= 'z') c = c - 'a' + 'A';
    }
}

double Query::calculateDistance(double lat1, double lon1, double lat2, double lon2) const {
    double dx = lat2 - lat1;
    double dy = lon2 - lon1;
    return sqrt(dx * dx + dy * dy);
}

// Interseção de listas ordenadas O(N+M)
ListaEncadeada<Street*> Query::intersecaoListas(
    const ListaEncadeada<Street*>& lista1, 
    const ListaEncadeada<Street*>& lista2) {
    
    ListaEncadeada<Street*> resultado;
    
    auto it1 = lista1.getIterator();
    auto it2 = lista2.getIterator();
    
    if (!it1.hasNext() || !it2.hasNext()) {
        return resultado;
    }
    
    Street* s1 = it1.next();
    Street* s2 = it2.next();
    
    while (s1 != nullptr && s2 != nullptr) {
        if (s1->getId() < s2->getId()) {
            s1 = it1.hasNext() ? it1.next() : nullptr;
        } else if (s1->getId() > s2->getId()) {
            s2 = it2.hasNext() ? it2.next() : nullptr;
        } else {
            resultado.insert(s1);
            s1 = it1.hasNext() ? it1.next() : nullptr;
            s2 = it2.hasNext() ? it2.next() : nullptr;
        }
    }
    
    return resultado;
}

// Merge para ordenação estável (por distância, depois por ID se empate)
void Query::merge(ResultadoQuery* arr, ResultadoQuery* temp, int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;
    
    while (i <= mid && j <= right) {
        // Ordena por distância crescente
        // Se distância igual, ordena por ID crescente
        if (arr[i].distancia < arr[j].distancia ||
            (arr[i].distancia == arr[j].distancia && arr[i].id < arr[j].id)) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    
    while (j <= right) {
        temp[k++] = arr[j++];
    }
    
    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
}

// MergeSort recursivo
void Query::mergeSort(ResultadoQuery* arr, ResultadoQuery* temp, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, temp, left, mid);
        mergeSort(arr, temp, mid + 1, right);
        merge(arr, temp, left, mid, right);
    }
}

// Método principal - processa consulta e retorna resultados ordenados por distância
void Query::processarComResultados(AVL& indice, ResultadoQuery** resultadosPtr, int& numResultados) {
    numResultados = 0;
    *resultadosPtr = nullptr;
    
    if (termos.isEmpty()) {
        return;
    }
    
    // Obtém lista do primeiro termo
    auto it = termos.getIterator();
    std::string primeiroTermo = it.next();
    
    Word* palavra = indice.buscar(primeiroTermo);
    if (!palavra) {
        return;
    }
    
    ListaEncadeada<Street*> listaResultados = palavra->getLogradouros();
    
    // Interseção com os demais termos
    while (it.hasNext()) {
        std::string termo = it.next();
        
        Word* proxPalavra = indice.buscar(termo);
        if (!proxPalavra) {
            return;
        }
        
        ListaEncadeada<Street*> intersecao = intersecaoListas(
            listaResultados, proxPalavra->getLogradouros()
        );
        
        listaResultados = intersecao;
        
        if (listaResultados.isEmpty()) {
            return;
        }
    }
    
    // Conta resultados
    int n = listaResultados.getSize();
    if (n == 0) {
        return;
    }
    
    // Aloca array para resultados temporários
    ResultadoQuery* resultadosTemp = new ResultadoQuery[n];
    int idx = 0;
    
    // Preenche array com dados
    auto rit = listaResultados.getIterator();
    while (rit.hasNext()) {
        Street* street = rit.next();
        resultadosTemp[idx].id = street->getId();
        resultadosTemp[idx].nome = street->getName();
        resultadosTemp[idx].distancia = calculateDistance(
            street->getCenterLat(), street->getCenterLon(),
            originLat, originLon
        );
        idx++;
    }
    
    // Ordena por distância usando MergeSort
    if (n > 1) {
        ResultadoQuery* tempArray = new ResultadoQuery[n];
        mergeSort(resultadosTemp, tempArray, 0, n - 1);
        delete[] tempArray;
    }
    
    // Limita ao máximo de resultados
    numResultados = (n < maxResults) ? n : maxResults;
    
    // Cria array final com resultados limitados
    *resultadosPtr = new ResultadoQuery[numResultados];
    for (int i = 0; i < numResultados; i++) {
        (*resultadosPtr)[i] = resultadosTemp[i];
    }
    
    delete[] resultadosTemp;
}