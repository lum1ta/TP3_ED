#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <sstream>

#include "AVL.hpp"
#include "Street.hpp"
#include "Address.hpp"
#include "Query.hpp"
#include "Word.hpp"
#include "ListaEncadeada.hpp"

using namespace std;

void toUpperString(string& str) {
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 'a' + 'A';
        }
    }
}

int main(int argc, char *argv[]) {
    // Entrada
    istream* input = &cin;
    ifstream file;
    
    if (argc == 2) {
        file.open(argv[1]);
        if (!file.is_open()) {
            cerr << "Erro ao abrir " << argv[1] << endl;
            return 1;
        }
        input = &file;
    }
    
    // 1. PROCESSAMENTO DOS ENDEREÇOS
    
    AVL indice;
    const int MAX_STREETS = 200000;
    Street* streets[MAX_STREETS] = {nullptr};
    int maxId = 0;
    
    int N;
    *input >> N;
    input->ignore();
    
    // Ler N endereços
    for (int i = 0; i < N; i++) {
        string linha;
        if (!getline(*input, linha)) break;
        if (linha.empty()) continue;
        
        Address addr;
        addr.ReadAdd(linha);
        
        int idLog = addr.getIdLog();
        
        // Criar/atualizar rua
        if (idLog >= 0 && idLog < MAX_STREETS) {
            if (!streets[idLog]) {
                streets[idLog] = new Street(idLog, addr.getLog());
                if (idLog > maxId) maxId = idLog;
            }
            streets[idLog]->addAdd(addr);
            
            // Indexar palavras do nome
            string nome = addr.getLog();
            size_t pos = 0;
            
            while (pos < nome.length()) {
                size_t next = nome.find(' ', pos);
                if (next == string::npos) next = nome.length();
                
                if (next > pos) {
                    string palavra = nome.substr(pos, next - pos);
                    toUpperString(palavra);
                    
                    Word* w = indice.buscar(palavra);
                    if (!w) {
                        w = new Word(palavra);
                        indice.inserir(w);
                    }
                    w->adicionarLogradouro(streets[idLog]);
                }
                
                pos = next + 1;
            }
        }
    }
    
    // Calcular centros
    for (int i = 0; i <= maxId; i++) {
        if (streets[i]) {
            streets[i]->calculateCenter();
        }
    }
    
    // 2. PROCESSAMENTO DAS CONSULTAS
    
    int M, R;
    *input >> M >> R;
    input->ignore();
    
    // Saída: número de consultas
    cout << M << endl;
    
    for (int i = 0; i < M; i++) {
        string linha;
        if (!getline(*input, linha)) break;
        if (linha.empty()) continue;
        
        // Parse consulta: Id;Termos;Lat;Lon
        stringstream ss(linha);
        string idStr, termosStr, latStr, lonStr;
        
        getline(ss, idStr, ';');
        getline(ss, termosStr, ';');
        getline(ss, latStr, ';');
        getline(ss, lonStr);
        
        // Limpar \r
        if (!lonStr.empty() && lonStr.back() == '\r') lonStr.pop_back();
        
        int idConsulta = atoi(idStr.c_str());
        double lat = atof(latStr.c_str());
        double lon = atof(lonStr.c_str());
        
        // Separar termos (sem vector, usando array)
        string termosArray[20]; // Máximo de 20 termos por consulta
        int numTermos = 0;
        
        // Parsing manual
        size_t start = 0;
        size_t end = 0;
        
        while (numTermos < 20 && start < termosStr.length()) {
            // Pula espaços
            while (start < termosStr.length() && termosStr[start] == ' ') start++;
            if (start >= termosStr.length()) break;
            
            // Encontra próximo espaço
            end = termosStr.find(' ', start);
            if (end == string::npos) end = termosStr.length();
            
            // Extrai termo
            termosArray[numTermos] = termosStr.substr(start, end - start);
            toUpperString(termosArray[numTermos]);
            numTermos++;
            
            start = end + 1;
        }
        
        // Criar query
        Query q;
        q.setOrigin(lat, lon);
        q.setMaxResults(R);
        
        for (int j = 0; j < numTermos; j++) {
            q.addTerm(termosArray[j]);
        }
        
        // Executar consulta - CORREÇÃO AQUI
        ResultadoQuery* resultados = nullptr;
        int numResultados = 0;
        
        q.processarComResultados(indice, &resultados, numResultados);
        
        // Saída no formato especificado
        cout << idConsulta << ";" << numResultados << endl;
        for (int j = 0; j < numResultados; j++) {
            cout << resultados[j].id << ";" << resultados[j].nome << endl;
        }
        
        // Liberar memória
        if (resultados != nullptr) {
            delete[] resultados;
        }
    }
    
    // Limpeza
    if (file.is_open()) file.close();
    for (int i = 0; i <= maxId; i++) {
        if (streets[i]) delete streets[i];
    }
    
    return 0;
}