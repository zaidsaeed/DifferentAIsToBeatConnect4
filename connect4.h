#include <iostream>
class Connect4{
    public:
        void printBoard(int board[6][7]);
        void insertIntoBoard(int columnNumber, int board[6][7], int turn);
        int determineWinner(int board[6][7], int turn);
        int scorePosition(int board[6][7], int turn);
        int insertIntoBoardForScore(int board[6][7], int turn);
};






