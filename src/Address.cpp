#include "Address.hpp"
#include <sstream>
#include <iostream>
#include <cstdlib>

// Construtor
Address::Address(const std::string& idAdd, int idLog, 
                 const std::string& typeLog, const std::string& Log,
                 int num, const std::string& neigh, 
                 const std::string& region, int CEP,
                 double Lat, double Long)
    : idAdd(idAdd), idLog(idLog), typeLog(typeLog), Log(Log),
      num(num), neigh(neigh), region(region), CEP(CEP),
      Lat(Lat), Long(Long) {
}

// Getters
std::string Address::getIdAdd() const { return idAdd; }
int Address::getIdLog() const { return idLog; }
std::string Address::getTypeLog() const { return typeLog; }
std::string Address::getLog() const { return Log; }
int Address::getNum() const { return num; }
std::string Address::getNeigh() const { return neigh; }
std::string Address::getRegion() const { return region; }
int Address::getCEP() const { return CEP; }
double Address::getLat() const { return Lat; }
double Address::getLong() const { return Long; }

// Setters
void Address::setLat(double lat) { Lat = lat; }
void Address::setLong(double lon) { Long = lon; }

// Método ReadAdd
void Address::ReadAdd(const std::string& linha) {
    std::stringstream ss(linha);
    std::string temp;
    
    std::getline(ss, idAdd, ';');
    
    std::getline(ss, temp, ';');
    idLog = std::atoi(temp.c_str());
    
    std::getline(ss, typeLog, ';');
    std::getline(ss, Log, ';');
    
    std::getline(ss, temp, ';');
    num = std::atoi(temp.c_str());
    
    std::getline(ss, neigh, ';');
    std::getline(ss, region, ';');
    
    std::getline(ss, temp, ';');
    CEP = std::atoi(temp.c_str());
    
    std::getline(ss, temp, ';');
    Lat = std::atof(temp.c_str());
    
    if (std::getline(ss, temp)) {
        Long = std::atof(temp.c_str());
    }
}

// Imprime informações
void Address::printInfo() const {
    std::cout << "Address ID: " << idAdd 
              << ", Street: " << Log 
              << " " << num
              << ", Location: (" << Lat << ", " << Long << ")"
              << std::endl;
}