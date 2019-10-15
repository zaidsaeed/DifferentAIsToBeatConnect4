#include <iostream>
#include "connect4.h"
using namespace std;

int Connect4::determineWinner(int board[6][7], int turn){
    //determine horizontal
    for (int i=0; i<6; i++){
        for (int j=0; j<4; j++) {
            if (board[i][j] == turn && board[i][j+1] == turn && board[i][j+2] == turn && board[i][j+3] == turn){
                cout << turn << " is the winner of the game. Horizontally" << endl;
                return turn;
            } 
        }
    }

    // determine vertically
    for (int j=0; j< 7; j++) {
        for (int i=0; i<3; i++) {
            if (board[i][j] == turn && board[i+1][j] == turn && board[i+2][j] == turn && board[i+3][j] == turn) {
                cout << turn << " is the winner of the game. Vertically" << endl;
                return turn;
            }
        }   
    }

    // //determine diagonal up
    for (int i=0; i<3; i++) {
        for (int j=0; j<4; j++) {
            if (board[i][j] == turn && board[i+1][j+1] == turn && board[i+2][j+2] == turn && board[i+3][j+3] == turn){
                cout << turn << " is the winner of the game. Diagnoally upwards." << endl;
                return turn;
            }
        }
    }

    //determine diagonal down
    for(int i=0; i<5; i++){
        for(int j=3; j<6; j++){
            if (board[i][j] == turn && board[i+1][j-1] == turn && board[i+2][j-2] == turn && board[i+3][j-3] == turn){
                cout << turn << " is the winner of the game. Diagnoally downward." << endl;
                return turn;
            }
        }
    }

    return -1;

}

void Connect4::insertIntoBoard(int columnNumber, int board[6][7], int turn){
    for (int i = 0; i < 6; i++ ){
        if (board[i][columnNumber] == 0){
            board[i][columnNumber] = turn;
            return;
        }
    }
    cout << "This column is all full" << endl;
}

int Connect4::insertIntoBoardForScore(int board[6][7], int turn){
    int maxScore = 0;
    int maxColNum = 0;
    for (int columnNumber = 0; columnNumber < 7; columnNumber++){
        //make copy of the board
        int newBoard[6][7];
        for (int i = 0; i < 6; i++){
            for (int j = 0; j < 7; j++) {
                newBoard[i][j] = board[i][j];
            }
        }
        insertIntoBoard(columnNumber, newBoard, turn);
        if(maxScore < scorePosition(newBoard, turn)){
            
            maxScore = scorePosition(newBoard, turn);
            maxColNum = columnNumber;

            printBoard(newBoard);
            cout << "maxScore is" << maxScore << endl;
            cout << "maxColNum is" << maxColNum << endl;
        }
    }
    return maxColNum;
    
}

void Connect4::printBoard(int board[6][7]){
    for (int i=5; i>=0; i--) {
        for (int j=0; j<7; j++) {
            cout << board[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

int Connect4::scorePosition(int board[6][7], int turn){
    int score = 0;
    //Check horizontal
    for(int i = 0; i< 6; i++){
        for (int j =0; j<4; j++){
            if (board[i][j] == turn && board[i][j+1] == turn && board[i][j+2] == turn && board[i][j+3] == turn){
                score = score + 100;
            }else if (board[i][j] == turn && board[i][j+1] == turn && board[i][j+2] == turn){
                score = score + 75;
            }else if (board[i][j] == turn && board[i][j+1] == turn){
                score = score + 50;
            }
        }
    }
    return score;
}