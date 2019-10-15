#include "connect4.h"
using namespace std;
#include <iostream>    
    
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
        cout << "Player " << turn << ". Please select a number between 0 and 6" << endl;
        cin >> columnNumber;
        c4.insertIntoBoard(columnNumber, board, turn);
        cout << "After player " << turn << "'s move, the board is now:" << endl;
        c4.printBoard(board);
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