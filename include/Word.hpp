#pragma once
#include "AVL.hpp"
#include "List.hpp"
//includes aqui que eu talvez precise
//TAD MAIS IMPORTANTE!!Mapeia as palavras para os logradouros

class Word{
    private:
        //Atributos no nó da arvore 
        std::string termo; //primary key
        List<Street*> logra; //lista para os logardouros que contenham essa palavra
    public:
        void addOcc(std::string termo,Street* log); 
        void searchLog(std::string termo); //lista para a palavra
};