#include <iostream>
#include <iomanip>
#include <queue>
#include <cstring> // For memset
#include "constants.h"
#include "board.h"


bool check_win(char board_f[ROWS][COLS], char player){ //player = b or w;
    bool winner{false};
    if(player == 'b'){
        winner = are_all_pieces_adjacent(board_f, 'b');
    }

    if(player == 'w'){
        winner = are_all_pieces_adjacent(board_f, 'w');
    }
    return winner;
}

bool check_draw(char board_f[ROWS][COLS]){
    bool draw{false};
    bool bAdj = are_all_pieces_adjacent(board_f, 'b');
    bool wAdj = are_all_pieces_adjacent(board_f, 'w');
    if(bAdj == true && wAdj == true){
        draw = true;
        std::cout << "Game is a draw." << std::endl;
    }
   return draw;
}

void clear(){
    std::cout << "\x1B[2J\x1B[H";   //clears the terminal and cursor goes top left
}

void print_board(char board[ROWS][COLS]){
    clear();
    for(size_t i{}; i < ROWS; ++i){
        for(size_t j{}; j < COLS; ++j){
            std::cout << std::setw(2) <<board[i][j] ;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;   
}

//adjaceny check

bool is_valid(int x, int y) {
    return x >= 0 && x < ROWS && y >= 0 && y < COLS;
}

void bfs(char board[ROWS][COLS], bool visited[ROWS][COLS], int start_x, int start_y,char player) {
    std::queue<int> q;
    q.push(start_x * COLS + start_y); // Store indices as single integer
    visited[start_x][start_y] = true;

    while (!q.empty()) {
        int idx = q.front();
        q.pop();
        int x = idx / COLS;
        int y = idx % COLS;

        for (int i = 0; i < 8; ++i) {
            int nx = x + directions[i][0];
            int ny = y + directions[i][1];
            if (is_valid(nx, ny) && !visited[nx][ny] && board[nx][ny] == player) {
                visited[nx][ny] = true;
                q.push(nx * COLS + ny);
            }
        }
    }
    
}

bool are_all_pieces_adjacent(char board[ROWS][COLS],char player) {
    bool visited[ROWS][COLS];
    memset(visited, false, sizeof(visited));
    
    bool found_player = false;
    int start_x = 0, start_y = 0;

    // Find the first piece to start BFS
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (board[i][j] == player) {
                if (!found_player) {
                    start_x = i;
                    start_y = j;
                    found_player = true;
                }
            }
        }
    }
    
    if (!found_player) {
        return true;  // No piece on board means they are trivially all adjacent
    }
    
    bfs(board, visited, start_x, start_y,player);

    // Check if all pieces were visited
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (board[i][j] == player && !visited[i][j]) {
                return false;
            }
        }
    }
    
    return true;
}
