#include "stack.hpp"
#include "target9Header.hpp"
#include <iostream>
#include <cstdlib> // For the rand() function and the dynamic memory allocation
#include <ctime> // To seed the rand() function so that it is less predictable
using namespace std;

// Constructor
newGame::newGame(int difficultyLevel) {
    undoStack = new Stack(); // Creating a new object of the Stack class on the heap for the undo stack
    redoStack = new Stack(); // Creating a new object of the Stack class on the heap for the redo stack
    newGame::initialize(difficultyLevel);
}

// Destructor to delete objects (moves) that have no pointer pointing to them and are lost / out of scope
newGame::~newGame() {
    delete undoStack;
    delete redoStack;
}

void newGame::initialize(int difficultyLevel) {

    // Making sure not to allocate double the memory for the stacks if it already exists
    if (!undoStack) {
        undoStack = new Stack();
    }
    if (!redoStack) {
        redoStack = new Stack();
    }
    
    // Seed the random number generator with the current time so as to be less predictable than using a constant to seed it
    srand(static_cast<unsigned>(time(nullptr)));

    // Set all cells to 9
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = 9;
        }
    }

    for (int i = 0; i < difficultyLevel; i++) {
        
        // Selecting a random row and column, % keeps the random number below 3
        int row = rand() % 3;
        int col = rand() % 3;

        // Subtract 1 from the randomly selected cell
        board[row][col] = (board[row][col] + 9) % 10;

        // Subtract 1 from all cells in the same row
        for (int k = 0; k < 3; ++k) {
            if (k != col) {
                board[row][k] = (board[row][k] + 9) % 10;
            }
        }

        // Subtract 1 from all cells in the same column
        for (int k = 0; k < 3; ++k) {
            if (k != row) {
                board[k][col] = (board[k][col] + 9) % 10;
            }
        }
    }
    undoStack->initialize(); // To empty the undo stack, sets count to 0
}

void newGame::displayBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool newGame::userWon() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 9) {
                return false;
            }
        }
    }
    return true;
}

void newGame::play(int row, int col) {
    
    // Creating a new object of the class Move to store the user moves and be able to send them to the stacks of undo and redo
    Move move;
    move.row = row;
    move.col = col;

    // Anouncing the last played move
    cout << "Playing move: (" << move.row << ", " << move.col << ")" << endl;

    // Add 1 to the selected cell
    board[row][col] = (board[row][col] + 1) % 10;

    // Add 1 to all cells in the same row
    for (int i = 0; i < 3; ++i) {
        if (i != col) {
            board[row][i] = (board[row][i] + 1) % 10;
        }
    }

    // Add 1 to all cells in the same column
    for (int j = 0; j < 3; ++j) {
        if (j != row) {
            board[j][col] = (board[j][col] + 1) % 10;
        }
    }
    // Add the move to the undo stack before making the move
    undoStack->push(move);

    cout << "Moves available for undo: ";
    undoStack->print(); 
}

void newGame::undo() {
    if (undoStack->empty()) {
        cout << "Cannot undo further." << endl;
        return;
    }

    // Get the move from the undo stack
    Move move;
    undoStack->top(move);

    // Pop the move from the undo stack
    undoStack->pop();

    cout << "Undo Stack contents after undo: ";
    undoStack->print();

    // Undo the move on the selected cell
    board[move.row][move.col] = (board[move.row][move.col] + 9) % 10;
    
    // Undo the changes in the same row
    for (int i = 0; i < 3; ++i) {
        if (i != move.col) {
            board[move.row][i] = (board[move.row][i] + 9) % 10;
        }
    }

    // Undo the changes in the same column
    for (int j = 0; j < 3; ++j) {
        if (j != move.row) {
            board[j][move.col] = (board[j][move.col] + 9) % 10;
        }
    }

    // Push the move to the redo stack
    redoStack->push(move);
}

void newGame::redo() {
    cout << "Redo Stack contents: ";
    redoStack->print();

    if (!redoStack->empty()) {
        // Get the move from the redo stack
        Move move;
        redoStack->top(move);

        // Redo the move
        play(move.row, move.col);

        // Pop the move from the redo stack
        redoStack->pop();
    } else {
        cout << "Cannot redo further." << endl;
    }
}