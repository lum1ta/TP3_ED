#pragma once 
#include "Address.hpp"

#include <string>

class Street{
    private:
    //Primary key
        int idLog;
        std::string NC;
        //Calculo da media
        double SomaLat;
        double SomaLong;
        //Contador
        int qtdaddress;
        double LatM;
        double LongM;
    public:
        //Constructor
        Street(int id, const std::string& nome);
        //Soma as coordenadas e implementa contador
        void addAdd(Address adr);
        //Divide a soma pela quantidade
        void calcCenter();
        double getDist(double LatOrigin, double LongOrigin);
};