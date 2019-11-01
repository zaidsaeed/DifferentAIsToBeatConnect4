#include <iostream>
#include "connect4.h"
#include <vector>
#include <limits>
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
        score = score + 5;
    }else if (turnCount == 3 && zeroCount == 1){
        score = score + 3;
    }else if (turnCount == 2 && zeroCount == 2){
        score = score + 1;
    }

    if(oppCount == 3 && zeroCount == 1){
        score = score - 10;
    }

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

int Connect4::insertIntoBoardForScore(int board[6][7], int turn, vector<int> valid_locations){
    int maxScore = 0;
    int maxColNum = 0;
    int newScore;
    for (int columnNumber = 0; columnNumber < valid_locations.size(); columnNumber++){
        //make copy of the board
        int newBoard[6][7];
        for (int i = 0; i < 6; i++){
            for (int j = 0; j < 7; j++) {
                newBoard[i][j] = board[i][j];
            }
        }
        insertIntoBoard(valid_locations[columnNumber], newBoard, turn);
        // cout << "testBoard is" << endl;
        // printBoard(newBoard);
        newScore = scorePosition(newBoard, turn);
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
    
    //Check horizontal
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

bool Connect4::isValidLocation(int board[6][7], int col){
    return board[5][col] == 0;
};

vector<int> Connect4::getValidLocations(int board[6][7]){
    vector<int> validLocations;
    for (int i = 0; i<7; i++){
        if (isValidLocation(board, i)){
            validLocations.push_back(i);
        }
    }
    return validLocations;
};

bool Connect4::isTerminalNode(int board[6][7]){
    return determineWinner(board, 1) != -1 || determineWinner(board, 2) != -1 || getValidLocations(board).size() == 0;
}

pair<int, int> Connect4::minimax(int board[6][7], int depth, int alpha, int beta, int maximizingPlayer){
    vector<int> valid_locations = getValidLocations(board);
	bool is_terminal = isTerminalNode(board);
	if (depth == 0 or is_terminal){
        if (is_terminal){
            if (determineWinner(board, 2) == 2){
                return pair<int, int>(NULL, 100000000000000);
            }
			else if (determineWinner(board, 1) == 1){
                return pair<int, int>(NULL, -10000000000000);
            }	
            else{
                //Game is over cant do anything from here
                return pair<int, int>(NULL, 0);
            }
        
		}else{ //depth is zero
			return pair<int, int>(NULL, scorePosition(board, 2));
        } 
    }
    if (maximizingPlayer){
        int maxCol = 0;
        int maxScore = numeric_limits<int>::min();
        vector<pair<int,int>> toprint;
        for (int columnNumber = 0; columnNumber < valid_locations.size(); columnNumber++){
            //make copy of the board
            int newBoard[6][7];
            for (int i = 0; i < 6; i++){
                for (int j = 0; j < 7; j++) {
                    newBoard[i][j] = board[i][j];
                }
            }
            insertIntoBoard(valid_locations[columnNumber], newBoard, 2);
            pair<int, int> pair1 = minimax(newBoard, depth-1, alpha, beta, false);
            cout << "testBoard is" << endl;
            printBoard(newBoard);
            // toprint.push_back(pair<int, int>(valid_locations[columnNumber], pair1.second));
            int currentBoardScore = pair1.second;
            cout << "col : " << valid_locations[columnNumber] << "score " << currentBoardScore << "depth " << depth << endl;
            if(maxScore < currentBoardScore){
                maxScore = currentBoardScore;
                maxCol = valid_locations[columnNumber];
            }
            if (alpha < maxScore){
                alpha = maxScore;
            }
            if (alpha >= beta){
                break;
            }

        }
        // for(int i =0; i<=6; i++){
        //     cout << "col : " << toprint[i].first << "score " << toprint[i].second << "depth " << depth << endl;
        // }
        cout << "To maximize: " << maxCol << "was chosen. ";
        return pair<int, int>(maxCol, maxScore);
    }else{
        //minimizing player
        int minScore = numeric_limits<int>::max();
        int minCol = 0;
        vector<pair<int,int>> toprint;
        for (int columnNumber = 0; columnNumber < valid_locations.size(); columnNumber++){
            
            //make copy of the board
            int newBoard[6][7];
            for (int i = 0; i < 6; i++){
                for (int j = 0; j < 7; j++) {
                    newBoard[i][j] = board[i][j];
                }
            }
            insertIntoBoard(valid_locations[columnNumber], newBoard, 1);
            // cout << "testBoard is" << endl;
            // printBoard(newBoard);
            pair<int, int> pair1 = minimax(newBoard, depth -1, alpha, beta, true);
            // toprint.push_back(pair<int, int>(valid_locations[columnNumber], pair1.second));
            int currentBoardScore = pair1.second;
            cout << "testBoard is" << endl;
            printBoard(newBoard);
            cout << "col : " << valid_locations[columnNumber] << "score " << currentBoardScore << "depth " << depth << endl;
            if(minScore > currentBoardScore){
                minScore = currentBoardScore;
                minCol = valid_locations[columnNumber];
            }
            if(beta > minScore){
                beta = minScore;
            }
            if(alpha >= beta){
                break;
            }
        }
        cout << "To minimize: " << minCol << "was chosen. ";
        return pair<int, int>(minCol, minScore);
    }

}