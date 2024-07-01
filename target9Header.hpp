#ifndef TARGET9HEADER_HPP // Header guard to check if the header file is already included
#define TARGET9HEADER_HPP

#include <iostream>
using namespace std;

class Stack; // Declared to be able to use my custom Stack class in the newGame class's data members

// To save each move so it can be put into the undo and redo stacks
class Move {
public:
    int row, col;
};

class newGame {
    public:
        newGame(int difficultyLevel);
        ~newGame();
        void initialize(int difficultyLevel);
        void displayBoard();
        bool userWon();
        void play(int row, int col);
        void undo();
        void redo();
    
    private:
        int board[3][3];
        Stack* undoStack; // Pointer that can point to an object of the Stack class
        Stack* redoStack; // Pointer that can point to an object of the Stack class
};

#endif
