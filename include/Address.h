#define ADDRESS.H
#ifndef ADDRESS.H

#include <string>

class Address{
    private:
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
    public:
        //Constructor
        Address();
        ~Addres();

        //Ler os dados de entrada
        void ReadAdd(string linha);

        //Getters
        std::string getidLog();
        id getidLog();
        std::string gettypeLog();
        std::string getLog();
        int getnum();
        std::string getneigh();
        std::string getregion();
        int getCEP();
        double getLat();
        double getLong();
}
#endif