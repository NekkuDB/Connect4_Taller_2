// Connect4.cpp
#include "Connect4.h"
#include "GameState.h"
#include <iostream>
#include <fstream>
#include <sstream>

Connect4::Connect4(int gameMode, int difficulty, bool useAlphaBeta) 
    : gameMode(gameMode), difficulty(difficulty), useAlphaBetaPruning(useAlphaBeta) {
    initializeBoard();
}


void Connect4::initializeBoard() {
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            board[i][j] = ' ';
        }
    }
}

void Connect4::displayBoard() {
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            std::cout << "[" << board[i][j] << "]";
        }
        std::cout << std::endl;
    }
}

bool Connect4::dropPiece(int column, char piece) {
    if (column < 0 || column >= 7) {
        return false; // Columna fuera de rango
    }

    // Buscar la fila más baja disponible en la columna
    for (int i = 5; i >= 0; --i) {
        if (board[i][column] == ' ') {
            board[i][column] = piece;
            return true; // Pieza colocada con éxito
        }
    }

    return false; // Columna llena, no se puede colocar la pieza
}


bool Connect4::checkWin(char piece) {
    // Revisar horizontalmente
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 4; ++col) {
            if (board[row][col] == piece && 
                board[row][col + 1] == piece && 
                board[row][col + 2] == piece && 
                board[row][col + 3] == piece) {
                return true;
            }
        }
    }

    // Revisar verticalmente
    for (int col = 0; col < 7; ++col) {
        for (int row = 0; row < 3; ++row) {
            if (board[row][col] == piece && 
                board[row + 1][col] == piece && 
                board[row + 2][col] == piece && 
                board[row + 3][col] == piece) {
                return true;
            }
        }
    }

    // Revisar diagonalmente (ascendente)
    for (int row = 3; row < 6; ++row) {
        for (int col = 0; col < 4; ++col) {
            if (board[row][col] == piece && 
                board[row - 1][col + 1] == piece && 
                board[row - 2][col + 2] == piece && 
                board[row - 3][col + 3] == piece) {
                return true;
            }
        }
    }

    // Revisar diagonalmente (descendente)
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 4; ++col) {
            if (board[row][col] == piece && 
                board[row + 1][col + 1] == piece && 
                board[row + 2][col + 2] == piece && 
                board[row + 3][col + 3] == piece) {
                return true;
            }
        }
    }

    return false; // No se encontró ganador
}


/*void Connect4::playGame() {
    char currentPlayer = 'X'; // Alternar entre 'X' y 'O'
    bool gameEnded = false;
    int column;
    int movesCount = 0; // Contador para el número total de movimientos

    while (!gameEnded && movesCount < 42) { // 6 filas * 7 columnas = 42 posiciones
        displayBoard();

        // Obtener la columna del jugador actual
        std::cout << "Jugador " << currentPlayer << ", elige una columna (0-6): ";
        std::cin >> column;

        // Validar y realizar el movimiento
        if (column >= 0 && column < 7 && dropPiece(column, currentPlayer)) {
            movesCount++; // Incrementar el contador de movimientos
            // Verificar si el movimiento actual lleva a una victoria
            if (checkWin(currentPlayer)) {
                displayBoard();
                std::cout << "Jugador " << currentPlayer << " gana!" << std::endl;
                gameEnded = true;
            } else if (movesCount == 42) { // Verificar si el tablero está lleno
                std::cout << "Empate!" << std::endl;
                gameEnded = true;
            } else {
                // Cambiar de jugador
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
        } else {
            std::cout << "Movimiento inválido. Inténtalo de nuevo." << std::endl;
        }
    }
}
*/


int Connect4::evaluateBoard() {
    // Retorna un valor alto si 'X' gana, bajo si 'O' gana, y 0 para empate o juego no terminado
    if (checkWin('X')) {
        return 1000;
    } else if (checkWin('O')) {
        return -1000;
    } else {
        return 0; // Empate o juego no terminado
    }
}

int Connect4::minimax(int depth, bool isMaximizingPlayer, int alpha, int beta) {
    int maxDepth;
    switch (difficulty) {
        case 1: // Fácil
            maxDepth = 2;
            break;
        case 2: // Medio
            maxDepth = 4;
            break;
        case 3: // Difícil
            maxDepth = 5;
            break;
        default:
            maxDepth = 6; // Valor por defecto
    }
    if (depth >= maxDepth) {
        return evaluateBoard();
    }

    int score = evaluateBoard();
    if (score == 1000 || score == -1000) return score;
    if (!isMovesLeft()) return 0;
    

    if (score == 1000 || score == -1000) return score;
    if (!isMovesLeft()) return 0;

   if (isMaximizingPlayer) {
        int best = -10000;
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    int val = minimax(depth + 1, false, alpha, beta);
                    board[i][j] = ' ';
                    best = std::max(best, val);
                    if (useAlphaBetaPruning) {
                        alpha = std::max(alpha, best);
                        if (beta <= alpha)
                            break;
                    }
                }
            }
        }
        return best;
    } else {
        int best = 10000;
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    int val = minimax(depth + 1, true, alpha, beta);
                    board[i][j] = ' ';
                    best = std::min(best, val);
                    if (useAlphaBetaPruning) {
                        beta = std::min(beta, best);
                        if (beta <= alpha)
                            break;
                    }
                }
            }
        }
        return best;
    }

}


bool Connect4::isMovesLeft() {
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 7; j++)
            if (board[i][j] == ' ')
                return true;
    return false;
}


int Connect4::findBestMove() {
    int bestVal = -10000;
    int bestMove = -1;

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'X';
                int moveVal = minimax(0, false, -10000, 10000); // Incluye alpha y beta
                board[i][j] = ' ';
                if (moveVal > bestVal) {
                    bestMove = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}



void Connect4::enableAlphaBetaPruning(bool enable) {
    useAlphaBetaPruning = enable;
}



void Connect4::playGame() {
    char currentPlayer = 'X'; // El jugador humano comienza
    bool gameEnded = false;
    int column;
    std::string input; // Para manejar entradas del usuario
    int movesCount = 0; // Contador para el número total de movimientos

    while (!gameEnded && movesCount < 42) { // 6 filas * 7 columnas = 42 posiciones
        displayBoard();

        if (gameMode == 1 || (gameMode == 2 && currentPlayer == 'X')) {
            // Jugador humano
            std::cout << "Jugador " << currentPlayer << ", elige una columna (0-6) o escribe 'guardar' para guardar la partida: ";
            std::cin >> input;

            if (input == "guardar") {
                std::string filename;
                std::cout << "Ingresa el nombre del archivo para guardar: ";
                std::cin >> filename;
                saveGame(filename);
                std::cout << "Partida guardada. Saliendo del juego..." << std::endl;
                return; // Salir del juego después de guardar
            } else {
                // Convertir la entrada a un número de columna
                std::stringstream ss(input);
                ss >> column;

                if (ss.fail() || column < 0 || column >= 7 || !dropPiece(column, currentPlayer)) {
                    std::cout << "Movimiento inválido. Inténtalo de nuevo." << std::endl;
                    continue; // Salta al siguiente ciclo del bucle si el movimiento es inválido
                }
                movesCount++;
            }
        } else if (gameMode == 2 && currentPlayer == 'O') {
            // IA (Minimax)
            std::cout << "Turno de la IA." << std::endl;
            column = findBestMove();
            dropPiece(column, currentPlayer);
            movesCount++;
        }

        // Verificar si el movimiento actual lleva a una victoria
        if (checkWin(currentPlayer)) {
            displayBoard();
            std::cout << "Jugador " << currentPlayer << " gana!" << std::endl;
            gameEnded = true;
        } else if (movesCount == 42) { // Verificar si el tablero está lleno
            std::cout << "Empate!" << std::endl;
            gameEnded = true;
        } else {
            // Cambiar de jugador
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
}



void Connect4::saveGame(const std::string& filename) {
    // Preparar el estado del juego para guardar
    GameState gameState;
    // Copiar el tablero y otros estados relevantes a gameState
    std::copy(&board[0][0], &board[0][0] + 6*7, &gameState.board[0][0]);
    gameState.currentPlayer = currentPlayer;
    gameState.movesCount = movesCount;
    gameState.gameMode = gameMode;
    gameState.difficulty = difficulty;
    gameState.useAlphaBetaPruning = useAlphaBetaPruning;

    // Guardar el estado del juego
    GameStateHandler::saveGameState(filename, gameState);
}

void Connect4::loadGame(const std::string& filename) {
    // Preparar un estado de juego para cargar
    GameState gameState;

    // Cargar el estado del juego
    if (!GameStateHandler::loadGameState(filename, gameState)) {
        std::cerr << "Error al cargar el juego." << std::endl;
        return;
    }

    // Copiar el estado cargado al juego actual
    std::copy(&gameState.board[0][0], &gameState.board[0][0] + 6*7, &board[0][0]);
    currentPlayer = gameState.currentPlayer;
    movesCount = gameState.movesCount;
    gameMode = gameState.gameMode;
    difficulty = gameState.difficulty;
    useAlphaBetaPruning = gameState.useAlphaBetaPruning;
}



// Otros métodos que puedas necesitar