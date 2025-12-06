#pragma once
#include <string>

class Address {
private:
    std::string idAdd;
    int idLog;
    std::string typeLog;
    std::string Log;
    int num;
    std::string neigh;
    std::string region;
    int CEP;
    double Lat;
    double Long;
    
public:
    // Construtor que corresponde ao uso no main
    Address(std::string idAdd, int idLog, std::string typeLog,
            std::string Log, int num, std::string neigh,
            std::string region, int CEP, double Lat, double Long)
        : idAdd(idAdd), idLog(idLog), typeLog(typeLog),
          Log(Log), num(num), neigh(neigh), region(region),
          CEP(CEP), Lat(Lat), Long(Long) {}
    
    // Construtor padrão
    Address() = default;
    
    // Destrutor
    ~Address() {}
    
    // Método de leitura (opcional)
    void ReadAdd(std::string linha);
    
    // Getters (APENAS UMA VERSÃO DE CADA)
    std::string getidAdd() const { return idAdd; }
    int getidLog() const { return idLog; }
    std::string gettypeLog() const { return typeLog; }
    std::string getLog() const { return Log; }
    int getnum() const { return num; }
    std::string getneigh() const { return neigh; }
    std::string getregion() const { return region; }
    int getCEP() const { return CEP; }
    double getLat() const { return Lat; }
    double getLong() const { return Long; }
    
    // REMOVA estas linhas duplicadas da linha 39-40
};