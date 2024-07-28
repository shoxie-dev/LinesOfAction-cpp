#include "constants.h"

#ifndef _PLAYER_
#define _PLAYER_
bool valid_move(char board_t[ROWS][COLS], int row, int col, int pieceX, int pieceY, char player);
void add_move(char board_f[ROWS][COLS], int row, int col, int pieceX, int pieceY, char player);
void get_player_move(char board_f[ROWS][COLS],char board_t[ROWS][COLS], int row, int col, int pieceX, int pieceY, char player);
bool isPiece(char board_t[ROWS][COLS],int pieceX,int pieceY,char player);
void get_possible_moves(char board_f[ROWS][COLS],char board_t[ROWS][COLS], int pieceX, int pieceY, char player);
void countbw(char board_t[ROWS][COLS], int pieceX, int pieceY, char player, int& vertMove, int& horMove, int& odMove, int& diagMove);
void print_possible_moves(char board_t[ROWS][COLS]);
void play_game();
#endif