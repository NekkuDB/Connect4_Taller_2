#ifndef RESULTADOS_H
#define RESULTADOS_H

#include <string>
#include <vector>

struct GameResult {
    std::string date;
    int moves;
    std::string gameType;
    std::string difficulty;
    double executionTime;
    bool alphaBetaPruning;
    char winner;
};

class Resultados {
public:
    static void writeResultToCSV(const std::string& filename, const GameResult& result);
    static void readResultsFromCSV(const std::string& filename);
};

#endif // RESULTADOS_H