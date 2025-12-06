#include "Street.hpp"
#include <iostream>
#include <cmath>

// Construtor
Street::Street(int id, const std::string& name) 
    : id(id), name(name), sumLat(0.0), sumLon(0.0), 
      addressCount(0), centerLat(0.0), centerLon(0.0) {
}

// Getters
int Street::getId() const { return id; }
std::string Street::getName() const { return name; }
double Street::getCenterLat() const { return centerLat; }
double Street::getCenterLon() const { return centerLon; }
int Street::getAddressCount() const { return addressCount; }

// Setters
void Street::setId(int newId) { id = newId; }
void Street::setName(const std::string& newName) { name = newName; }
void Street::setCenter(double lat, double lon) { 
    centerLat = lat; 
    centerLon = lon; 
}

// Adiciona um endereço à rua - MANTIDO COMO addAdd
void Street::addAdd(const Address& address) {
    addresses.insert(address);
    sumLat += address.getLat();
    sumLon += address.getLong();
    addressCount++;
    calculateCenter(); // Recalcula centro automaticamente
}

// Calcula o centro de gravidade - MANTIDO COMO calculateCenter
void Street::calculateCenter() {
    if (addressCount == 0) {
        centerLat = 0.0;
        centerLon = 0.0;
        return;
    }
    
    centerLat = sumLat / addressCount;
    centerLon = sumLon / addressCount;
}

// Calcula distância até um ponto
double Street::getDistanceTo(double lat, double lon) const {
    double dx = centerLat - lat;
    double dy = centerLon - lon;
    return sqrt(dx * dx + dy * dy);
}

// Remove todos os endereços
void Street::clearAddresses() {
    addresses.clear();
    sumLat = 0.0;
    sumLon = 0.0;
    addressCount = 0;
    centerLat = 0.0;
    centerLon = 0.0;
}

// Verifica se a rua tem endereços
bool Street::hasAddresses() const { 
    return addressCount > 0; 
}

// Operador < para ordenação
bool Street::operator<(const Street& other) const {
    return id < other.id;
}

// Imprime informações da rua
void Street::printInfo() const {
    std::cout << "Street ID: " << id 
              << ", Name: " << name 
              << ", Addresses: " << addressCount
              << ", Center: (" << centerLat << ", " << centerLon << ")"
              << std::endl;
}