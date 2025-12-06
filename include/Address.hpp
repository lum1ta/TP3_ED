#ifndef ADDRESS_HPP
#define ADDRESS_HPP

#include <string>

class Address {
private:
    std::string idAdd;      // ID do endereço
    int idLog;              // ID do logradouro
    std::string typeLog;    // Tipo do logradouro
    std::string Log;        // Nome do logradouro
    int num;                // Número
    std::string neigh;      // Bairro
    std::string region;     // Região
    int CEP;                // CEP
    double Lat;             // Latitude
    double Long;            // Longitude

public:
    // Construtor
    Address(const std::string& idAdd = "", int idLog = 0, 
            const std::string& typeLog = "", const std::string& Log = "",
            int num = 0, const std::string& neigh = "", 
            const std::string& region = "", int CEP = 0,
            double Lat = 0.0, double Long = 0.0);
    
    // Getters
    std::string getIdAdd() const;
    int getIdLog() const;
    std::string getTypeLog() const;
    std::string getLog() const;
    int getNum() const;
    std::string getNeigh() const;
    std::string getRegion() const;
    int getCEP() const;
    double getLat() const;
    double getLong() const;
    
    // Setters
    void setLat(double lat);
    void setLong(double lon);
    
    // Método para ler de string
    void ReadAdd(const std::string& linha);
    
    // Imprime informações
    void printInfo() const;
};

#endif // ADDRESS_HPP