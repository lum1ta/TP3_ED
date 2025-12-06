#include "Street.hpp"
#include <cmath>      // para sqrt()

// Adiciona endereço: soma latitude e longitude e aumenta contador
void Street::addAdd(Address adr) {
    SomaLat  += adr.getLat();
    SomaLong += adr.getLong();
    qtdaddress++;
}

// Calcula a média das coordenadas
void Street::calcCenter() {
    if (qtdaddress > 0) {
        LatM  = SomaLat  / qtdaddress;
        LongM = SomaLong / qtdaddress;
    }
}

// Distância euclidiana simples até o centro calculado
double Street::getDist(double LatOrigin, double LongOrigin) {
    double dx = LatOrigin - LatM;
    double dy = LongOrigin - LongM;
    return std::sqrt(dx * dx + dy * dy);
}
