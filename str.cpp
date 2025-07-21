#include <iostream>
#include <fstream>      // Para ifstream
#include <sstream>      // Para stringstream
#include <string>       // Para string
#include <vector>       // Para armazenar os campos

int main() {
    // 1. Abrir o arquivo
    std::ifstream arquivo("dados.txt");

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }

    std::string linha;
    int numeroDaLinha = 1;

    // 2. Ler o arquivo linha por linha
    while (std::getline(arquivo, linha)) {
        // Ignora linhas vazias
        if (linha.empty()) {
            continue;
        }

        // 3. Colocar a linha em um stringstream para facilitar a extração
        std::stringstream ss(linha);
        std::string campo;
        std::vector<std::string> campos;

        // 4. Extrair cada campo da linha usando ';' como delimitador
        while (std::getline(ss, campo, ';')) {
            campos.push_back(campo);
        }

        // Agora o vetor 'campos' contém todos os dados da linha atual
        std::cout << "Linha " << numeroDaLinha++ << " | " << campos.size() << " campos: " << std::endl;
        for (size_t i = 0; i < campos.size(); ++i) {
            // Adiciona aspas para ver campos vazios claramente
            std::cout << "  Campo " << i << ": \"" << campos[i] << "\"" << std::endl;
        }
        std::cout << "------------------------" << std::endl;
    }

    arquivo.close();

    return 0;
}