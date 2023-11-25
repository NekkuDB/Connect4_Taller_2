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

    file << result.date << ","
         << result.moves << ","
         << result.gameType << ","
         << result.difficulty << ","
         << result.executionTime << ","
         << (result.alphaBetaPruning ? "Sí" : "No") << ","
         << result.winner
         << "\n";

    file.close();
}

void Resultados::readResultsFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    file.close();
}