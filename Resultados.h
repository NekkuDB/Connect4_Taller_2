#ifndef RESULTADOS_H
#define RESULTADOS_H

#include <string>
#include <vector>

// Estructura para almacenar los resultados de un juego
struct GameResult {
    std::string date;          // Fecha del juego
    int moves;                 // Número de movimientos
    std::string gameType;      // Tipo de juego (por ejemplo, "Player vs AI")
    std::string difficulty;    // Dificultad del juego (si aplica)
    double executionTime;      // Tiempo de ejecución del juego
    bool alphaBetaPruning;     // Indica si se utilizó poda alfa-beta
    std::string winner;               // Ganador del juego ('X', 'O', o algún otro indicador)
};

class Resultados {
public:
    // Escribe un resultado de juego en un archivo CSV
    static void writeResultToCSV(const std::string& filename, const GameResult& result);

    // Lee y muestra los resultados de un archivo CSV
    static void readResultsFromCSV(const std::string& filename);
};

#endif // RESULTADOS_H
