#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>

// Estructura para representar el estado del juego
struct GameState {
    char board[6][7]; // Tablero de 6 filas por 7 columnas
    char currentPlayer; // 'X' o 'O'
    int movesCount; // Contador de movimientos
    int gameMode; // Modo de juego
    int difficulty; // Nivel de dificultad
    bool useAlphaBetaPruning; // Uso de poda alfa-beta
};

// Clase para manejar el estado del juego
class GameStateHandler {
public:
    // Guardar el estado del juego en un archivo
    static void saveGameState(const std::string& filename, const GameState& state);
    // Cargar el estado del juego desde un archivo
    static bool loadGameState(const std::string& filename, GameState& state);
};

#endif // GAMESTATE_H