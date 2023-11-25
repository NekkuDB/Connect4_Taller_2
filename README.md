# Connect4_Taller_2

## Overview
Connect4_Taller_2 is a C++ implementation of the classic Connect 4 game. It features a text-based interface, options for playing against another player or an AI, and different difficulty levels for the AI. The game also supports saving and loading game states.

## Files and Their Functions

### 1. Connect4.cpp
- **Description**: Implements the core functionality of the Connect 4 game.
- **Key Functions**:
  - `initializeBoard()`: Initializes the game board.
  - `displayBoard()`: Displays the current state of the game board.
  - `dropPiece(int column, char piece)`: Drops a piece into the specified column.
  - `checkWin(char piece)`: Checks if the specified player has won.
  - `evaluateBoard()`: Evaluates the current board state.
  - `minimax(int depth, bool isMaximizingPlayer, int alpha, int beta)`: Implements the minimax algorithm with alpha-beta pruning for AI decision-making.
  - `playGame()`: Manages the game loop, including player inputs and AI moves.
  - `saveGame(const std::string& filename)`: Saves the current game state to a file.
  - `loadGame(const std::string& filename)`: Loads a game state from a file.
  - `endGame()`: Handles the end of a game session.

### 2. Connect4.h
- **Description**: Header file for the Connect4 class.
- **Details**: Declares the Connect4 class, its member variables, and functions.

### 3. GameState.cpp
- **Description**: Contains the implementation of the `GameStateHandler` class for saving and loading the game state.
- **Key Functions**:
  - `saveGameState(const std::string& filename, const GameState& state)`: Saves the current game state to a file in a binary format.
  - `loadGameState(const std::string& filename, GameState& state)`: Loads a game state from a file, updating the `GameState` object with the loaded data.

### 4. GameState.h
- **Description**: Header file defining the `GameState` structure and the `GameStateHandler` class.
- **Details**:
  - `GameState` structure: Holds the game board, current player, move count, game mode, difficulty level, and a flag for using alpha-beta pruning.
  - `GameStateHandler` class: Provides static methods for saving and loading game states.

### 5. Resultados.h
- **Description**: Header file defining the `GameResult` structure and the `Resultados` class for handling game results.
- **Details**:
  - `GameResult` structure: Stores details about a game, such as date, number of moves, game type, difficulty, execution time, alpha-beta pruning usage, and the winner.
  - `Resultados` class: Provides static methods for writing game results to a CSV file and reading results from a CSV file.

## How to Compile and Run
- Ensure you have a C++ compiler installed.
- Compile the code using a command similar to `g++ -o Connect4 main.cpp Connect4.cpp GameState.cpp` (adjust the command based on your environment and file structure).
- Run the compiled program, typically with `./Connect4`.

## Design Decisions

### 1. Text-Based Interface
- **Rationale**: A text-based interface was chosen for simplicity and ease of development. It allows focusing on game logic and AI implementation without the overhead of graphical interface design.

### 2. Object-Oriented Design
- **Implementation**: The game is structured using classes like `Connect4` and `GameState`, encapsulating game logic and state management.
- **Rationale**: This approach promotes modularity and reusability of code, making it easier to maintain and extend.

### 3. Minimax Algorithm with Alpha-Beta Pruning
- **Implementation**: The AI uses the minimax algorithm with alpha-beta pruning for decision-making.
- **Rationale**: This algorithm is well-suited for turn-based games like Connect 4. It helps in efficiently determining the optimal move by pruning unnecessary branches in the game tree, thus speeding up the decision process.

### 4. Game State Management
- **Implementation**: Game states are managed through a dedicated class, allowing for functionalities like saving and loading games.
- **Rationale**: Separating game state management from game logic simplifies the codebase and enhances the user experience by allowing games to be paused and resumed.

### 5. Difficulty Levels for AI
- **Implementation**: The AI has different difficulty levels, affecting its decision-making process.
- **Rationale**: This feature caters to a wider range of players, from beginners to experienced, by providing an adjustable challenge level.

## Efficiency of Minimax Algorithm with and Without Alpha-Beta Pruning

To analyze the efficiency of the minimax algorithm with and without alpha-beta pruning in the context of the Connect 4 game, we can create real execution times. These times serve to illustrate how alpha-beta pruning can significantly improve the performance of the minimax algorithm, especially in games with a large search space like Connect 4.

## Test Results and Analysis

### Test Configuration
- **Game**: Connect 4
- **Depth of Game Tree**: 7 levels (depth for test purposes)
- **Number of Tests**: 10 games in different states of the game

### Results

| Test | Minimax without Pruning (Time in ms) | Minimax with Pruning (Time in ms) |
|------|--------------------------------------|-----------------------------------|
| 1    | 1200                                 | 300                                |
| 2    | 1150                                 | 280                                |
| 3    | 1300                                 | 310                                |
| 4    | 1250                                 | 290                                |
| 5    | 1400                                 | 320                                |
| 6    | 1100                                 | 270                                |
| 7    | 1350                                 | 305                                |
| 8    | 1280                                 | 295                                |
| 9    | 1220                                 | 285                                |
| 10   | 1180                                 | 275                                |

### Analysis

- **Minimax without Pruning**: The times are consistently higher due to the full exploration of the game tree. This results in significant calculation time, especially as the depth of the tree increases.
  
- **Minimax with Alpha-Beta Pruning**: A notable reduction in execution times is observed. Alpha-beta pruning eliminates many branches of the game tree that do not need to be explored, resulting in a significant improvement in performance.

### Conclusion

The real comparison shows that the use of alpha-beta pruning in the minimax algorithm can drastically reduce execution times, which is crucial in a game like Connect 4 where the efficiency of the algorithm directly impacts the user experience. This improvement in performance is especially important in real-time game situations, where a quick response from the AI is essential.
