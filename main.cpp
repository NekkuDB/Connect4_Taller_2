#include "Connect4.h"
#include <iostream>


void displayMenu();
int getGameMode();
int getDifficultyChoice();
int main() {
    displayMenu();
    int gameMode = getGameMode();

    if (gameMode == 2) {
        int difficulty = getDifficultyChoice();
        Connect4 game(gameMode, difficulty);
        game.playGame();
    } 
    else {
        Connect4 game(gameMode);
        game.playGame();
    }

    return 0;
}

void displayMenu() {
    std::cout << "¡Bienvenido a Conecta 4!" << std::endl;
    std::cout << "1. Jugar contra otro jugador" << std::endl;
    std::cout << "2. Jugar contra la IA" << std::endl;
    std::cout << "Ingresa tu elección (1-2): ";
}

int getGameMode() {
    int choice;
    std::cin >> choice;
    while (choice < 1 || choice > 2) {
        std::cout << "Elección inválida. Por favor ingresa 1 o 2: ";
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
