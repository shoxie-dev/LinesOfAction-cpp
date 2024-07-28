#include "constants.h"

#ifndef _BOARD_
#define _BOARD_
void print_board(char board[ROWS][COLS]);
bool check_win(char board[ROWS][COLS], char player);
bool check_draw(char board[ROWS][COLS]);
void clear();
bool is_valid(int x, int y);
void bfs(char board[ROWS][COLS], bool visited[ROWS][COLS], int start_x, int start_y,char player);
bool are_all_pieces_adjacent(char board[ROWS][COLS],char player);
#endif