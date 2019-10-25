#include <iostream>
class Connect4{
    public:
        void printBoard(int board[6][7]);
        int insertIntoBoard(int columnNumber, int board[6][7], int turn);
        int determineWinner(int board[6][7], int turn);
        int scorePosition(int board[6][7], int turn);
        int insertIntoBoardForScore(int board[6][7], int turn);
        int minimax(int board[6][7], int depth, int turn);
        int evaluateWindow(int window[4]);
};






