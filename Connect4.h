#ifndef CONNECT4_H
#define CONNECT4_H

#include <string> // Para manejar strings

class Connect4 {
public:
    Connect4(); // Constructor
    void playGame(); // Método para iniciar el juego
    void setDifficulty(int level); // Establecer la dificultad del juego
    void saveGame(const std::string& filename); // Guardar el estado del juego
    void loadGame(const std::string& filename); // Cargar el estado del juego

private:
    char board[6][7]; // Tablero de 6x7
    int difficulty; // Nivel de dificultad (1=fácil, 2=medio, 3=difícil)
    void initializeBoard(); // Inicializar el tablero
    void displayBoard(); // Mostrar el tablero
    bool dropPiece(int column, char piece); // Colocar una pieza en el tablero
    bool checkWin(char piece); // Verificar si hay un ganador
    int evaluateBoard();
    int minimax(int depth, bool isMaximizingPlayer, int alpha, int beta); // Minimax con poda alfa-beta
    bool isMovesLeft();
    int findBestMove();
    // Otros métodos que puedas necesitar
};

#endif // CONNECT4_H
