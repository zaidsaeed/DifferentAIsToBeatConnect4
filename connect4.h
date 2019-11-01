#include <iostream>
#include <vector>
using namespace std;

class Connect4{
    public:
        void printBoard(int board[6][7]);
        int insertIntoBoard(int columnNumber, int board[6][7], int turn);
        int determineWinner(int board[6][7], int turn);
        int scorePosition(int board[6][7], int turn);
        int insertIntoBoardForScore(int board[6][7], int turn, vector<int> valid_locations);
        pair<int,int> minimax(int board[6][7], int depth, int alpha, int beta, int maximizingPlayer);
        int evaluateWindow(int window[4]);
        bool isValidLocation(int board[6][7], int col);
        vector<int> getValidLocations(int board[6][7]);
        bool isTerminalNode(int board[6][7]);
};






