#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "AVL.hpp"
#include "Street.hpp"
#include "Address.hpp"
#include "Query.hpp"

// -----------------------------------------------------
// Hash simples de string
int hashWord(const std::string& s) {
    int h = 0;
    for (char c : s)
        h = h * 31 + c;
    return h < 0 ? -h : h;
}

// -----------------------------------------------------
// Converte string para double
double toDouble(const std::string& s) {
    return std::atof(s.c_str());
}

int toInt(const std::string& s) {
    return std::atoi(s.c_str());
}

// -----------------------------------------------------
// Parsing de linha CSV manual
void parseLine(
    const std::string& line,
    std::string& idEnd,
    int& idLog,
    std::string& tipoLog,
    std::string& log,
    int& num,
    std::string& bairro,
    std::string& regiao,
    int& cep,
    double& lat,
    double& lon
) {
    size_t start = 0;
    size_t end;
    std::string tmp;

    auto nextField = [&](std::string& out) {
        end = line.find(';', start);
        if (end == std::string::npos) {
            out = line.substr(start);
            start = line.size();
        } else {
            out = line.substr(start, end - start);
            start = end + 1;
        }
    };

    nextField(idEnd);
    nextField(tmp); idLog = toInt(tmp);
    nextField(tipoLog);
    nextField(log);
    nextField(tmp); num = toInt(tmp);
    nextField(bairro);
    nextField(regiao);
    nextField(tmp); cep = toInt(tmp);
    nextField(tmp); lat = toDouble(tmp);
    
    if (start < line.size())
        lon = toDouble(line.substr(start));
    else
        lon = 0.0;
}

// -----------------------------------------------------
int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir arquivo\n";
        return 1;
    }

    AVL indice;
    int N;
    file >> N;
    file.ignore(); // quebra de linha

    // -----------------------------
    // Leitura do arquivo
    for (int i = 0; i < N; i++) {
        std::string line;
        std::getline(file, line);

        std::string idEnd, tipoLog, log, bairro, regiao;
        int idLog, num, cep;
        double lat, lon;

        parseLine(line, idEnd, idLog, tipoLog, log, num, bairro, regiao, cep, lat, lon);

        // Criar endereço - AJUSTADO para corresponder ao construtor de Address
        Address adr(
            idEnd,           // idAdd
            idLog,           // idLog  
            tipoLog,         // typeLog
            log,             // Log
            num,             // num
            bairro,          // neigh
            regiao,          // region
            cep,             // CEP
            lat,             // Lat
            lon              // Long
        );

        // Criar / atualizar logradouro
        Street* street = new Street(idLog, log);
        street->addAdd(adr);

        // Separar palavras do nome da rua - CORRIGIDO
        size_t pos = 0;  // Mudei para size_t
        while (true) {
            size_t next = log.find(' ', pos);  // Mudei para size_t
            std::string palavra = log.substr(pos, next - pos);
            
            if (!palavra.empty()) {
                int key = hashWord(palavra);
                // USA APENAS ESTA LINHA (a função pública que faz tudo)
                indice.insert(key, street);
                
                // REMOVA estas linhas:
                // indice.insert(key);
                // indice.insertStreet(key, street);
            }
            
            if (next == std::string::npos)
                break;
            pos = next + 1;
        }
    }

    file.close();

    // -----------------------------
    // Query
    Query q;
    q.setOrigin(-19.92, -43.94); // exemplo
    q.setMaxResults(10);
    q.addTerm("RUA");
    q.addTerm("AFONSO");
    q.process(indice);

    return 0;
}