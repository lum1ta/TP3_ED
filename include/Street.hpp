#ifndef STREET_HPP
#define STREET_HPP

#include "Address.hpp"
#include "ListaEncadeada.hpp"
#include <string>

class Street {
private:
    int id;
    std::string name;
    ListaEncadeada<Address> addresses;
    double sumLat;
    double sumLon;
    int addressCount;
    double centerLat;
    double centerLon;
    
public:
    Street(int id = 0, const std::string& name = "");
    
    int getId() const;
    std::string getName() const;
    double getCenterLat() const;
    double getCenterLon() const;
    int getAddressCount() const;
    
    void setId(int newId);
    void setName(const std::string& newName);
    void setCenter(double lat, double lon);
    
    void addAdd(const Address& address);
    void calculateCenter();
    
    // Calcula distância até um ponto
    double getDistanceTo(double lat, double lon) const;
    
    void clearAddresses();
    bool hasAddresses() const;
    
    bool operator<(const Street& other) const;
    
    void printInfo() const;
};

#endif // STREET_HPP