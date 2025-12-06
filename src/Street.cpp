#include "Street.hpp"
#include <cmath>     // para sqrt()
#include <string>

//Inicializa cosntrutor
Street::Street(int id,const std::string& nome)
    :   idLog(id), NC(nome),
        SomaLat(0), SomaLong(0),
    qtdaddress(0), LatM(0), LongM(0) {}

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
