#ifndef _CONSTANTS_
#define _CONSTANTS_
const int ROWS = 8;
const int COLS = 8;
const int directions[8][2] = {     {0, 1},   // right
    {1, 0},   // down
    {0, -1},  // left
    {-1, 0},  // up
    {1, 1},   // down-right
    {1, -1},  // down-left
    {-1, 1},  // up-right
    {-1, -1} }; 
#endif