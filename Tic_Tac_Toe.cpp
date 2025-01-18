#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

const char PLAYER = 'X';
const char AI = 'O';

// Display the board
void printBoard(const vector<char>& board) {
    for (int i = 0; i < 9; i++) {
        cout << board[i] << ((i % 3 == 2) ? "\n" : " | ");
        if (i % 3 == 2 && i != 8) cout << "---------\n";
    }
}

// Check for winner
char checkWinner(const vector<char>& board) {
    const int winCombos[8][3] = {{0,1,2}, {3,4,5}, {6,7,8}, {0,3,6}, {1,4,7}, {2,5,8}, {0,4,8}, {2,4,6}};
    for (auto combo : winCombos) {
        if (board[combo[0]] == board[combo[1]] && board[combo[1]] == board[combo[2]] && board[combo[0]] != ' ')
            return board[combo[0]];
    }
    return ' ';
}

// Check if moves are left
bool isMovesLeft(const vector<char>& board) {
    return find(board.begin(), board.end(), ' ') != board.end();
}

// Minimax Algorithm
int minimax(vector<char>& board, bool isMax) {
    char winner = checkWinner(board);
    if (winner == AI) return 10;
    if (winner == PLAYER) return -10;
    if (!isMovesLeft(board)) return 0;
    
    int bestScore = isMax ? -1000 : 1000;
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            board[i] = isMax ? AI : PLAYER;
            int score = minimax(board, !isMax);
            board[i] = ' ';
            bestScore = isMax ? max(score, bestScore) : min(score, bestScore);
        }
    }
    return bestScore;
}

// Find the best move for AI
int findBestMove(vector<char>& board) {
    int bestMove = -1, bestScore = -1000;
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            board[i] = AI;
            int moveScore = minimax(board, false);
            board[i] = ' ';
            if (moveScore > bestScore) {
                bestMove = i;
                bestScore = moveScore;
            }
        }
    }
    return bestMove;
}

// Main Game Loop
int main() {
    vector<char> board(9, ' ');
    int move;
    cout << "Tic Tac Toe (You: X, AI: O)\n";
    printBoard(board);
    
    while (isMovesLeft(board) && checkWinner(board) == ' ') {
        cout << "Enter your move (1-9): ";
        while (!(cin >> move)) {  // Input validation
            cout << "Invalid input. Please enter a number between 1 and 9: ";
            cin.clear();  // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore bad input
        }
        move--; // Adjust for 0-based indexing
        
        if (move >= 0 && move < 9 && board[move] == ' ') {
            board[move] = PLAYER;
            printBoard(board);
            
            if (checkWinner(board) != ' ' || !isMovesLeft(board)) break;
            
            int aiMove = findBestMove(board);
            board[aiMove] = AI;
            cout << "AI has made its move:\n";
            printBoard(board);
        } else {
            cout << "Invalid move. Try again.\n";
        }
    }
    
    char winner = checkWinner(board);
    if (winner == PLAYER) cout << "You win!\n";
    else if (winner == AI) cout << "AI wins!\n";
    else cout << "It's a draw!\n";
    
    return 0;
}
