#include "Resultados.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string getCurrentDate() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d");
    return ss.str();
}

void Resultados::writeResultToCSV(const std::string& filename, const GameResult& result) {
    std::ofstream file(filename, std::ios::app); // Abre el archivo en modo append
    if (!file) {
        std::cerr << "No se pudo abrir el archivo para escribir: " << filename << std::endl;
        return;
    }

    file << result.date << ","
         << result.moves << ","
         << result.gameType << ","
         << result.difficulty << ","
         << result.executionTime << ","
         << (result.alphaBetaPruning ? "Sí" : "No") << ","
         << result.winner
         << "\n";
}

void Resultados::readResultsFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "No se pudo abrir el archivo para leer: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
}
