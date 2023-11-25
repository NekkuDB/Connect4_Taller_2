#include "Connect4.h"
#include <iostream>

void displayMenu();
int getGameMode();
int getDifficultyChoice();
bool getAlphaBetaChoice();

int main() {
    displayMenu();
    int choice = getGameMode();

    if (choice == 1 || choice == 2) {
        bool useAlphaBetaPruning = true; // Valor por defecto
        int difficulty = 1; // Valor por defecto para el modo jugador vs jugador

        if (choice == 2) {
            difficulty = getDifficultyChoice();
            useAlphaBetaPruning = getAlphaBetaChoice();
        }

        Connect4 game(choice, difficulty, useAlphaBetaPruning);
        game.playGame();
    } else if (choice == 3) {
        std::string filename;
        std::cout << "Ingresa el nombre del archivo de partida guardada: ";
        std::cin >> filename;

        Connect4 game(1, 1, true); // Crear un juego con valores por defecto
        game.loadGame(filename);
        game.playGame();
    }

    return 0;
}

void displayMenu() {
    std::cout << "¡Bienvenido a Conecta 4!" << std::endl;
    std::cout << "1. Jugar contra otro jugador" << std::endl;
    std::cout << "2. Jugar contra la IA" << std::endl;
    std::cout << "3. Cargar partida guardada" << std::endl;
    std::cout << "Ingresa tu elección (1-3): ";
}

int getGameMode() {
    int choice;
    std::cin >> choice;
    while (choice < 1 || choice > 3) {
        std::cout << "Elección inválida. Por favor ingresa un número entre 1 y 3: ";
        std::cin >> choice;
    }
    return choice;
}

int getDifficultyChoice() {
    std::cout << "Selecciona el nivel de dificultad:" << std::endl;
    std::cout << "1. Fácil" << std::endl;
    std::cout << "2. Medio" << std::endl;
    std::cout << "3. Difícil" << std::endl;
    std::cout << "Ingresa tu elección (1-3): ";
    int difficulty;
    std::cin >> difficulty;
    while (difficulty < 1 || difficulty > 3) {
        std::cout << "Elección inválida. Por favor ingresa un número entre 1 y 3: ";
        std::cin >> difficulty;
    }
    return difficulty;
}

bool getAlphaBetaChoice() {
    int choice;
    std::cout << "¿Activar poda alfa-beta? (1: Sí, 0: No): ";
    std::cin >> choice;
    while (choice != 0 && choice != 1) {
        std::cout << "Elección inválida. Por favor ingresa 1 o 0: ";
        std::cin >> choice;
    }
    return choice == 1;
}
