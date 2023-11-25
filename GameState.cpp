#include "GameState.h"
#include <fstream>
#include <iostream>

void GameStateHandler::saveGameState(const std::string& filename, const GameState& state) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo para guardar." << std::endl;
        return;
    }

    // Guardar el tablero
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            file.write(reinterpret_cast<const char*>(&state.board[i][j]), sizeof(char));
        }
    }

    // Guardar información adicional
    file.write(reinterpret_cast<const char*>(&state.currentPlayer), sizeof(char));
    file.write(reinterpret_cast<const char*>(&state.movesCount), sizeof(int));
    file.write(reinterpret_cast<const char*>(&state.gameMode), sizeof(int));
    file.write(reinterpret_cast<const char*>(&state.difficulty), sizeof(int));
    file.write(reinterpret_cast<const char*>(&state.useAlphaBetaPruning), sizeof(bool));

    file.close();
}

bool GameStateHandler::loadGameState(const std::string& filename, GameState& state) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo para cargar." << std::endl;
        return false;
    }

    // Cargar el tablero
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (file.read(reinterpret_cast<char*>(&state.board[i][j]), sizeof(char)).eof()) {
                std::cerr << "Error de lectura: archivo incompleto o corrupto." << std::endl;
                return false;
            }
        }
    }

    // Cargar información adicional
    if (file.read(reinterpret_cast<char*>(&state.currentPlayer), sizeof(char)).eof() ||
        file.read(reinterpret_cast<char*>(&state.movesCount), sizeof(int)).eof() ||
        file.read(reinterpret_cast<char*>(&state.gameMode), sizeof(int)).eof() ||
        file.read(reinterpret_cast<char*>(&state.difficulty), sizeof(int)).eof() ||
        file.read(reinterpret_cast<char*>(&state.useAlphaBetaPruning), sizeof(bool)).eof()) {
        std::cerr << "Error de lectura: archivo incompleto o corrupto." << std::endl;
        return false;
    }

    file.close();
    return true;
}