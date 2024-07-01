#include "target9Header.hpp"
#include <iostream>
using namespace std;


int main() {

    int difficultyLevel = 0;

    cout << "Welcome to the Target 9 game" << endl << endl;
    cout << "Enter difficulty level from 1 to 9: ";
    cin >> difficultyLevel;

    newGame g(difficultyLevel);

    while (!g.userWon()) {

        g.displayBoard();

        int row = 0, col = 0;
        cout << "Enter row and column, separated with a space, to make a move: ";
        cin >> row >> col;

        g.play(row, col);

        g.displayBoard();

        // Get user input if they want to undo their last played move
        char undoChoice;
        cout << "Do you want to undo? (y/n)";
        cin >> undoChoice;

        if (undoChoice == 'y') {
            g.undo();
            g.displayBoard();

            // Get user input if they want to redo the move they selected to undo or continue playing
            char redoChoice;
            cout << "Do you want to redo (r) or continue playing (c)? ";
            cin >> redoChoice;

            if (redoChoice == 'r') {
                g.redo();
            }
            else if (redoChoice == 'c'){
                // Code does nothing, exits the loop and enters the while loop again
            }
            else {
                cout << "Invalid choice. Continuing the game." << endl;
            }
        }
    }

    cout << "Congratulations, you have won the game!";

    return 0;
}