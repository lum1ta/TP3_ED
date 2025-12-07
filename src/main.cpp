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


// Função auxiliar para converter string para maiúsculo
void toUpperString(string& str) {
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 'a' + 'A';
        }
    }
}

// ==========================================
// Nova Função Auxiliar: Buscar Rua na Lista
// ==========================================
// Como não usamos mais vetor, precisamos percorrer a lista para achar a rua pelo ID
Street* buscarRuaPorId(const ListaEncadeada<Street*>& lista, int id) {
    auto it = lista.getIterator();
    while (it.hasNext()) {
        Street* s = it.next();
        if (s->getId() == id) {
            return s;
        }
    }
    return nullptr;
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
    
    // SUBSTITUIÇÃO: Array fixo removido
    // const int MAX_STREETS = 200000;
    // Street* streets[MAX_STREETS] = {nullptr};
    
    // NOVA ESTRUTURA: Lista Encadeada para armazenar as ruas
    ListaEncadeada<Street*> listaRuas;
    
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
        
        // Verifica se a rua já existe na lista (busca linear)
        Street* ruaAtual = buscarRuaPorId(listaRuas, idLog);
        
        // Se não existe, cria e insere
        if (ruaAtual == nullptr) {
            ruaAtual = new Street(idLog, addr.getLog());
            listaRuas.insert(ruaAtual);
        }
        
        // Adiciona o endereço à rua
        ruaAtual->addAdd(addr);
            
        // Indexar palavras do nome (Lógica mantida, apenas usando ruaAtual)
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
                // Adiciona o ponteiro da rua atual à palavra
                w->adicionarLogradouro(ruaAtual);
            }
            
            pos = next + 1;
        }
    }
    
    // Calcular centros
    // Agora iteramos sobre a lista em vez do array
    auto itRuas = listaRuas.getIterator();
    while (itRuas.hasNext()) {
        itRuas.next()->calculateCenter();
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
        
        if (!lonStr.empty() && lonStr.back() == '\r') lonStr.pop_back();
        
        int idConsulta = atoi(idStr.c_str());
        double lat = atof(latStr.c_str());
        double lon = atof(lonStr.c_str());
        
        string termosArray[20]; 
        int numTermos = 0;
        
        size_t start = 0;
        size_t end = 0;
        
        while (numTermos < 20 && start < termosStr.length()) {
            while (start < termosStr.length() && termosStr[start] == ' ') start++;
            if (start >= termosStr.length()) break;
            
            end = termosStr.find(' ', start);
            if (end == string::npos) end = termosStr.length();
            
            termosArray[numTermos] = termosStr.substr(start, end - start);
            toUpperString(termosArray[numTermos]);
            numTermos++;
            
            start = end + 1;
        }
        
        Query q;
        q.setOrigin(lat, lon);
        q.setMaxResults(R);
        
        for (int j = 0; j < numTermos; j++) {
            q.addTerm(termosArray[j]);
        }
        
        ResultadoQuery* resultados = nullptr;
        int numResultados = 0;
        
        q.processarComResultados(indice, &resultados, numResultados);
        
        cout << idConsulta << ";" << numResultados << endl;
        for (int j = 0; j < numResultados; j++) {
            cout << resultados[j].id << ";" << resultados[j].nome << endl;
        }
        
        if (resultados != nullptr) {
            delete[] resultados;
        }
    }
    
    // Limpeza de Memória
    if (file.is_open()) file.close();
    
    // DELETAR OS OBJETOS STREET
    // A ListaEncadeada deleta os NÓS, mas não o conteúdo (Street*) se for ponteiro.
    // Precisamos deletar manualmente os objetos criados com 'new Street'
    auto itLimpeza = listaRuas.getIterator();
    while (itLimpeza.hasNext()) {
        Street* s = itLimpeza.next();
        delete s;
    }
    // A listaRuas será destruída automaticamente ao sair do escopo
    
    return 0;
}