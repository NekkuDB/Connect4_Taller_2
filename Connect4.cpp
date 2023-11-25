// Connect4.cpp
#include "Connect4.h"
#include "GameState.h"
#include "Resultados.h" 
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>

Connect4::Connect4(int gameMode, int difficulty, bool useAlphaBeta) 
    : gameMode(gameMode), difficulty(difficulty), useAlphaBetaPruning(useAlphaBeta), currentPlayer('X'), movesCount(0) {
    initializeBoard();
    startTime = std::chrono::system_clock::now(); // Iniciar el temporizador
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

void Connect4::endGame() {
    endTime = std::chrono::system_clock::now();
    GameResult result;
    result.date = getCurrentDate();
    result.moves = movesCount; // Asegúrate de que movesCount tenga el número correcto de movimientos
    result.gameType = (gameMode == 1 ? "Player vs Player" : "Player vs AI");
    result.difficulty = std::to_string(difficulty); // Asegúrate de que difficulty tenga el nivel de dificultad
    result.executionTime = calculateExecutionTime(); // Implementa esta función según sea necesario
    result.alphaBetaPruning = useAlphaBetaPruning;
    result.winner = determineWinner(); // Implementa esta función para determinar el ganador
    // Guardar el resultado en el archivo CSV
    Resultados::writeResultToCSV("resultados.csv", result);
    // ... código existente para finalizar el juego y guardar resultados ...

    // Mostrar opciones al usuario
    std::cout << "Partida finalizada. Elige una opción:" << std::endl;
    std::cout << "1. Volver a jugar" << std::endl;
    std::cout << "2. Volver al menú principal" << std::endl;

    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            // Iniciar un nuevo juego
            startNewGame();
            break;
        case 2:
            // Regresar al menú principal
            showMainMenu();
            break;
        default:
            std::cout << "Opción no válida. Regresando al menú principal." << std::endl;
            showMainMenu();
    }
}

void Connect4::startNewGame() {
    // Reiniciar el tablero a su estado inicial (vacío)
    initializeBoard();

    // Establecer el jugador inicial, por ejemplo, 'X'
    currentPlayer = 'X';

    // Reiniciar el contador de movimientos
    movesCount = 0;

    // Reiniciar el modo de juego y la dificultad si es necesario
    // gameMode = ...; // Si deseas cambiar el modo de juego
    // difficulty = ...; // Si deseas cambiar la dificultad

    // Reiniciar el uso de poda alfa-beta si es necesario
    // useAlphaBetaPruning = ...; // Si deseas cambiar esta configuración

    // Iniciar el temporizador para el nuevo juego
    startTime = std::chrono::system_clock::now();

    // Mostrar el tablero inicial
    displayBoard();

    // Iniciar el juego
    playGame();
}


void Connect4::showMainMenu() {
    int choice = 0;

    while (choice != 4) { // Suponiendo que 4 es la opción para salir
        std::cout << "\n==== Menú Principal de Connect4 ====\n";
        std::cout << "1. Jugar nuevo juego\n";
        std::cout << "2. Cargar juego guardado\n";
        std::cout << "3. Cambiar configuración\n";
        std::cout << "4. Salir\n";
        std::cout << "Elige una opción: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                // Iniciar un nuevo juego
                startNewGame();
                break;
            case 2:
                // Cargar un juego guardado
                {
                    std::string filename;
                    std::cout << "Ingresa el nombre del archivo para cargar: ";
                    std::cin >> filename;
                    loadGame(filename);
                }
                break;
            case 3:
                // Cambiar configuración (dificultad, modo de juego, etc.)
                changeSettings();
                break;
            case 4:
                std::cout << "Saliendo del juego...\n";
                break;
            default:
                std::cout << "Opción no válida. Por favor, intenta de nuevo.\n";
        }
    }
}

void Connect4::changeSettings() {
    int newGameMode, newDifficulty;
    char useAlphaBetaChoice;

    std::cout << "Configuración actual: " << std::endl;
    std::cout << "Modo de juego: " << (gameMode == 1 ? "Jugador vs Jugador" : "Jugador vs IA") << std::endl;
    std::cout << "Dificultad: " << difficulty << " (1=Fácil, 2=Medio, 3=Difícil)" << std::endl;
    std::cout << "Poda alfa-beta: " << (useAlphaBetaPruning ? "Sí" : "No") << std::endl;

    std::cout << "\nNueva configuración:" << std::endl;

    // Cambiar modo de juego
    std::cout << "Elige el modo de juego (1=Jugador vs Jugador, 2=Jugador vs IA): ";
    std::cin >> newGameMode;
    if (newGameMode == 1 || newGameMode == 2) {
        gameMode = newGameMode;
    } else {
        std::cout << "Modo de juego no válido. Manteniendo configuración actual." << std::endl;
    }

    // Cambiar dificultad
    std::cout << "Elige la dificultad (1=Fácil, 2=Medio, 3=Difícil): ";
    std::cin >> newDifficulty;
    if (newDifficulty >= 1 && newDifficulty <= 3) {
        difficulty = newDifficulty;
    } else {
        std::cout << "Dificultad no válida. Manteniendo configuración actual." << std::endl;
    }

    // Cambiar uso de poda alfa-beta
    std::cout << "¿Usar poda alfa-beta? (s/n): ";
    std::cin >> useAlphaBetaChoice;
    useAlphaBetaPruning = (useAlphaBetaChoice == 's' || useAlphaBetaChoice == 'S');
}

std::string Connect4::getCurrentDate() {
    auto now = std::chrono::system_clock::now(); // Obtener el tiempo actual
    auto in_time_t = std::chrono::system_clock::to_time_t(now); // Convertir a time_t

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d"); // Formatear la fecha
    return ss.str(); // Devolver la fecha como string
}

long Connect4::calculateExecutionTime() {
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();
    return static_cast<long>(duration);
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

std::string Connect4::determineWinner() {
    if (checkWin('X')) {
        return "Jugador X";
    } else if (checkWin('O')) {
        return "Jugador O";
    } else {
        return "Empate";
    }
}


// Otros métodos que puedas necesitar