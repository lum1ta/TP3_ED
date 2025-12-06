#include "./include/Address.hpp"
#include <iostream>
#include <sstream>

//Destructor
Address::~Address() {}

//Ler no formato de entrada
void Address::ReadAdd(std::string linha){
    std::stringstream(ss);
    std::string temp;

    std::getline(ss, idAdd, ';');

    std::getline(ss, temp, ';');
    idLog = std::stoi(temp);

    std::getline(ss, typeLog,';');
    std::getline(ss, Log, ';');

    std::getline(ss,temp,';');
    num = std::stoi(temp);

    std::getline(ss,neigh,';');
    std::getline(ss,region,';');

    std::getline(ss,temp,';');
    CEP = std::stoi(temp);

    std::getline(ss, temp, ';');
    Lat = std::stod(temp);

    std::getline(ss, temp, ';');
    Long = std::stod(temp);
}

//Getters
std::string Address::getidAdd() { return idAdd; }
int Address::getidLog() { return idLog; }
std::string Address::gettypeLog() { return typeLog; }
std::string Address::getLog() { return Log; }
int Address::getnum() { return num; }
std::string Address::getneigh() { return neigh; }
std::string Address::getregion() { return region; }
int Address::getCEP() { return CEP; }
double Address::getLat() { return Lat; }
double Address::getLong() { return Long; }
