#include "connect4.h"
using namespace std;
#include <iostream>
#include <vector>
#include <limits>

int main(){
    int board[6][7] = {0};
    Connect4 c4 = Connect4();
    bool gameOver = false;
    int turn = 1;
    int columnNumber;
    int winner;
    while(!gameOver){
        cout << "The current board is: " << endl;
        c4.printBoard(board);
        if (turn == 1){
            cout << "Player " << turn << ". Please select a number between 0 and 6" << endl;
            cin >> columnNumber;
            while (c4.insertIntoBoard(columnNumber, board, turn) == 1){
                columnNumber = columnNumber + 1;
                cout << "Column chosen is full, the following column has been selected for you. Column " << columnNumber << endl;
            }
            cout << "After player " << turn << "'s move, the board is now:" << endl;
            c4.printBoard(board);
        }
        else if (turn == 2){
            // vector<int> valid_locations = c4.getValidLocations(board);
            // int colNum = c4.insertIntoBoardForScore(board, turn, valid_locations);
            pair<int, int> choice = c4.minimax(board, 5, numeric_limits<int>::min(), numeric_limits<int>::max(), true);
            cout << "Computer has chosen " << choice.first << endl;
            cout << "After computer " << turn << "'s move, the board is now:" << endl;
            c4.insertIntoBoard(choice.first, board, turn);
            c4.printBoard(board);
        }


        winner = c4.determineWinner(board, turn);
        if (winner != -1){
            gameOver = true;
        }else{
            if (turn == 1) {
                turn = 2;
            }else{
                turn = 1;
            }
        }
    }
    cout << "The winner is : " << turn << endl;
    return 0;

}