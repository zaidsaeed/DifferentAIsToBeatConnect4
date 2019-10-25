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

int Connect4::evaluateWindow(int window[4]){
    int turnCount = 0;
    int zeroCount = 0;
    int oppCount = 0;
    int score = 0;
    for (int i = 0; i < 4; i++){
        if(window[i] == 0){
            zeroCount = zeroCount + 1;
        }else if(window[i] == 2){
            turnCount = turnCount + 1;
        }else{
            oppCount = oppCount + 1;
        }
    }

    if(turnCount == 4){
        score = score + 100;
    }else if (turnCount == 3 && zeroCount == 1){
        score = score + 3;
    }else if (turnCount == 2 && zeroCount == 2){
        score = score + 2;
    }

    if(oppCount == 3 && zeroCount == 1){
        score = score - 4;
    }

    // cout << "score is now : " << score << endl;

    return score;
    
}

int Connect4::insertIntoBoard(int columnNumber, int board[6][7], int turn){
    if (board[5][columnNumber] != 0){
        return 1;
    }
    for (int i = 0; i < 6; i++ ){
        if (board[i][columnNumber] == 0){
            board[i][columnNumber] = turn;
            return 0;
        }
    }
    cout << "Nothing was added" << endl;
}

int Connect4::insertIntoBoardForScore(int board[6][7], int turn){
    int maxScore = 0;
    int maxColNum = 0;
    int newScore;
    for (int columnNumber = 0; columnNumber < 7; columnNumber++){
        //make copy of the board
        int newBoard[6][7];
        for (int i = 0; i < 6; i++){
            for (int j = 0; j < 7; j++) {
                newBoard[i][j] = board[i][j];
            }
        }
        insertIntoBoard(columnNumber, newBoard, turn);
        cout << "testBoard is" << endl;
        printBoard(newBoard);
        newScore = scorePosition(newBoard, turn);
        // cout << "Column Number: " << columnNumber << " , yields the score : " << newScore << endl;
        if(maxScore < newScore){
            maxScore = newScore;
            maxColNum = columnNumber;
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
    

    // Preference center (Domain knowledge)
    // for(int i = 0; i<7; i++){
    //     if (board[i][3] == 0) {
    //         break;
    //     }else if (board[i][3] == turn){
    //         score = score + 6;
    //     }
    // }
    
    // Check horizontal
    for(int i = 0; i<6; i++){
        for (int j =0; j<4; j++){
            int hwindow[4] = {board[i][j], board[i][j+1], board[i][j+2], board[i][j+3]};
            score = score + evaluateWindow(hwindow);
        }
    }

    //Check vertical
    for(int i = 0; i< 3; i++){
        for(int j = 0; j < 7; j++){
            int vwindow[4] = {board[i][j], board[(i+1)][j], board[i+2][j], board[i+3][j]};
            score = score + evaluateWindow(vwindow);
        }
    }

    //Check diagonal up
    for (int i=0; i<3; i++) {
        for (int j=0; j<4; j++) {
            int dwup[4] = {board[i][j], board[i+1][j+1], board[i+2][j+2], board[i+3][j+3]};
            score = score + evaluateWindow(dwup);
        }
    }

    //Check diagonal down
    for(int i=0; i<5; i++){
        for(int j=3; j<6; j++){
            int dwDn[4] = {board[i][j], board[i+1][j-1], board[i+2][j-2], board[i+3][j-3]};
            score = score + evaluateWindow(dwDn);
        }
    }
    return score;
}

int Connect4::minimax(int board[6][7], int depth, int maximizingPlayer){
//     if (depth == 0 || determineWinner(board, turn) != -1){
//         return scorePosition(board, turn);
//     }
// }
}