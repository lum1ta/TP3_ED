#define ADDRESS.H
#if"ndef ADDRESS.H

#include <string>

struct Address{
    //Código alfanumérico unico para cada endereço
    std::string idAdd;
    //Id unico numerico para cada logradouro
    int idLog;
    std::string typeLog;
    std::string Log;
    int num;
    std::string neigh;
    std::string region;
    int CEP;
    double Lat;
    double Long;
}

#endif"