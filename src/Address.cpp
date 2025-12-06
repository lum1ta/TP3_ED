#include "Address.hpp"
#include <sstream>

// Método ReadAdd - corrigido
void Address::ReadAdd(std::string linha) {
    std::stringstream ss(linha);  // CORREÇÃO: stringstream ss(linha)
    std::string temp;
    
    std::getline(ss, idAdd, ';');
    
    std::getline(ss, temp, ';');
    idLog = std::stoi(temp);
    
    std::getline(ss, typeLog, ';');
    std::getline(ss, Log, ';');
    
    std::getline(ss, temp, ';');
    num = std::stoi(temp);
    
    std::getline(ss, neigh, ';');
    std::getline(ss, region, ';');
    
    std::getline(ss, temp, ';');
    CEP = std::stoi(temp);
    
    std::getline(ss, temp, ';');
    Lat = std::stod(temp);
    
    if (std::getline(ss, temp)) {
        Long = std::stod(temp);
    }
}

// NOTA: Os getters estão implementados inline no header, 
// então não precisam estar aqui