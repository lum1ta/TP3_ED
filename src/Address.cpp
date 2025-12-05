#include "Address.h"
#include <iostream>
#include <fstream>
#include <string>   // se for usar string

// Leitura do arquivo de entrada
void Ler() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::ifstream file("input.txt");

    if (!file.is_open()) {
        std::cerr << "Erro ao abrir input.txt\n";
        return;
    }

    std::string linha;
    while (getline(file, linha)) {
        std::cout << linha << "\n";
    }

//Cálculo coordenadas médias
}
