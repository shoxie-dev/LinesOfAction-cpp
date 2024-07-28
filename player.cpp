#include <iostream>
#include "constants.h"
#include "player.h"
#include "board.h"

void play_game(){
    char board_p[ROWS][COLS] = {                  //board to print final moves onto
        {'.','b','b','b','b','b','b','.'},
        {'w','.','.','.','.','.','.','w'},
        {'w','.','.','.','.','.','.','w'},
        {'w','.','.','.','.','.','.','w'},
        {'w','.','.','.','.','.','.','w'},
        {'w','.','.','.','.','.','.','w'},
        {'w','.','.','.','.','.','.','w'},
        {'.','b','b','b','b','b','b','.'}
    };
    char board_d[ROWS][COLS] = {                  //board to print test moves
        {'.','b','b','b','b','b','b','.'},
        {'w','.','.','.','.','.','.','w'},
        {'w','.','.','.','.','.','.','w'},
        {'w','.','.','.','.','.','.','w'},
        {'w','.','.','.','.','.','.','w'},
        {'w','.','.','.','.','.','.','w'},
        {'w','.','.','.','.','.','.','w'},
        {'.','b','b','b','b','b','b','.'}
    };
    int piecex{};
    int piecey{};
    int posx{};
    int posy{};
    print_board(board_p);

    bool isWin1 = false;
    bool isWin2 = false;
    bool isDraw = false;

    //add an option to change a piece, probably just a while loop
    
    while(isDraw == false && isWin1 == false && isWin2 ==false){
        //player b
        get_player_move(board_p, board_d,posx,posy,piecex,piecey,'b');
        isDraw = check_draw(board_p);
        if(isDraw == true){
                break;
        } 
        isWin1 = are_all_pieces_adjacent(board_p,'b');
        if(isWin1 == true){
            std::cout << "b wins" << std::endl;
            break;
        }
        posx = 0;
        posy = 0;
        piecex = 0;
        piecey = 0;
        
        //player w
        get_player_move(board_p, board_d,posx,posy,piecex,piecey,'w');
        isDraw = check_draw(board_p); 
        if(isDraw == true){
            break;
        } 
        isWin2 = check_win(board_p, 'w');
        if(isWin2 == true){
            std::cout << "w wins" << std::endl;
            break;
        }
        posx = 0;
        posy = 0;
        piecex = 0;
        piecey = 0;
          
    }
    

    return;
}

void get_possible_moves(char board_f[ROWS][COLS],char board_t[ROWS][COLS], int pieceX, int pieceY, char player){
    //this function gets all the possible moves on the vertical, horizontal and diagonals.
    int vertC{};
    int horC{};
    int odiagC{};
    int diagC{};
    int newXb{};
    int newYb{};

    if(player == 'b'){
        countbw(board_t, pieceX, pieceY, player , vertC, horC, odiagC, diagC);
        
        if(vertC >= 1){ //final
            newXb = pieceX + vertC;
            if(newXb >= 0 && newXb < 8){
                if(board_t[newXb][pieceY] != 'b') { // so that it overwrites only w's and .'s
                    board_t[newXb][pieceY] = '*'; 
                }
                for(int i{pieceX}; i < newXb; ++i){
                    if(board_t[i][pieceY] == 'w'){
                        if(newXb >= 0 && newXb < 8){
                            for(int i{pieceX}; i <= newXb; ++i){
                                board_t[i][pieceY] = board_f[i][pieceY];
                            }
                            break;
                        }
                    }   
                } 
            }
            newXb = 0;     

            newXb = pieceX - vertC;
            if(newXb >= 0 && newXb < 8){
                if(board_t[newXb][pieceY] != 'b'){
                    board_t[newXb][pieceY] = '*'; 
                }
                
                for(int i{newXb}; i < pieceX; ++i){
                    if(board_t[i][pieceY] == 'w'){
                        if(newXb >= 0 && newXb < 8){
                            for(int i{newXb}; i <= pieceX; ++i){
                                board_t[i][pieceY] = board_f[i][pieceY];
                            }
                            break;
                        }
                    }   
                }
            }
            newXb = 0;   
        }
        

        if(horC >= 1){
            newYb = pieceY + horC;
            if(newYb >= 0 && newYb < 8){
                if(board_t[pieceX][newYb] != 'b'){
                    board_t[pieceX][newYb] = '*';
                }
                
                for(int j{pieceY}; j < newYb; ++j){
                    if(board_t[pieceX][j] == 'w'){
                        if(newYb >= 0 && newYb < 8){
                             for(int j{pieceY}; j <= newYb; ++j){
                                board_t[pieceX][j] = board_f[pieceX][j];
                             }
                            break;
                        }
                    }   
                }   
            }
            newYb = 0;

            newYb = pieceY - horC;
            if(newYb >= 0 && newYb < 8){
                if(board_t[pieceX][newYb] != 'b'){
                        board_t[pieceX][newYb] = '*';
                }
    
                for(int j{newYb}; j < pieceY; ++j){
                    if(board_t[pieceX][j] == 'w'){
                        if(newYb >= 0 && newYb < 8){
                            for(int j{newYb}; j <= pieceY; ++j){
                                board_t[pieceX][j] = board_f[pieceX][j];
                            }
                            break;
                        }
                    }   
                }
            }
            newYb = 0;
        }

        
        if(odiagC >= 1){
           newYb = pieceY + odiagC;
           newXb = pieceX + odiagC;
           if((newYb >= 0 && newYb < 8) && (newXb >= 0 && newXb < 8)){
                if(board_t[newXb][newYb] != 'b'){
                    board_t[newXb][newYb] = '*';
                }
           
            int odc = pieceY - pieceX;
            int j{};
            for(int i{pieceX}; i < newXb; ++i){
                    j = i + odc;
                    if(board_t[i][j] == 'w'){ 
                        for(int i{pieceX}; i <= newXb; ++i){
                            j = i + odc;
                            board_t[i][j] = board_f[i][j];
                        }    
                        break;
                    }               
                }
            }
            newYb = 0;
            newXb = 0;

            newYb = pieceY - odiagC;
            newXb = pieceX - odiagC;
            if((newYb >= 0 && newYb < 8) && (newXb >= 0 && newXb < 8)){ 
                if(board_t[newXb][newYb] != 'b'){
                    board_t[newXb][newYb] = '*';
                }
            
                int odc = pieceY - pieceX;
                int j{};
                for(int i{newXb+1}; i < pieceX ;++i){
                    j = i + odc;             
                    if(board_t[i][j] == 'w'){
                        for(int i{newXb}; i <= pieceX ;++i){
                            j = i + odc;
                            board_t[i][j] = board_f[i][j];        
                        } 
                        break;
                    }
                    
                }
            }
            newYb = 0;
            newXb = 0;

        }

        if(diagC >= 1){
            newXb = pieceX + diagC;
            newYb = pieceY - diagC;
            if((newYb >= 0 && newYb < 8) && (newXb >= 0 && newXb < 8)){
                if(board_t[newXb][newYb] != 'b'){
                    board_t[newXb][newYb] = '*';
                }
            
                int dc = pieceY + pieceX;
                int j{};
                for(int i{pieceX}; i < newXb ;++i){
                    j = -i + dc;
                    if(board_t[i][j] == 'w'){
                        for(int i{pieceX}; i <= newXb ;++i){
                            j = -i + dc;
                            board_t[i][j] = board_f[i][j];        
                        }      
                        break;
                    }
                }
            }
            newYb = 0;
            newXb = 0;

            newXb = pieceX - diagC;
            newYb = pieceY + diagC;
            if((newYb >= 0 && newYb < 8) && (newXb >= 0 && newXb < 8)){
                if(board_t[newXb][newYb] != 'b'){
                    board_t[newXb][newYb] = '*';
                }
            
                int dc = pieceX + pieceY;
                int j{};
                for(int i{newXb}; i < pieceX ;++i){
                    j = -i + dc; 
                    if(board_t[i][j] == 'w'){
                        for(int i{newXb}; i <= pieceX ;++i){
                            j = -i + dc;
                            board_t[i][j] = board_f[i][j];        
                        }  
                        break;
                    }
                }
            } 
            newXb = 0;
            newYb = 0;   
        }

        print_board(board_t);
    }

    if(player == 'w'){
        countbw(board_t, pieceX, pieceY, player , vertC, horC, odiagC, diagC);
        
        if(vertC >= 1){ //final
            newXb = pieceX + vertC;
            if(newXb >= 0 && newXb < 8){
                if(board_t[newXb][pieceY] != 'w') { // so that it overwrites only b's and .'s
                    board_t[newXb][pieceY] = '*'; 
                }
                // can probably add a conditional so that it doesnt get evaluated for no reason :v
                for(int i{pieceX}; i < newXb; ++i){
                    if(board_t[i][pieceY] == 'b'){
                        if(newXb >= 0 && newXb < 8){
                            for(int i{pieceX}; i <= newXb; ++i){
                                board_t[i][pieceY] = board_f[i][pieceY];
                            }
                            break;
                        }
                    }   
                } 
            }     
            newXb = 0;

            newXb = pieceX - vertC;
            if(newXb >= 0 && newXb < 8){
                if(board_t[newXb][pieceY] != 'w'){
                    board_t[newXb][pieceY] = '*'; 
                }
                
                for(int i{newXb}; i < pieceX; ++i){
                    if(board_t[i][pieceY] == 'b'){
                        if(newXb >= 0 && newXb < 8){
                            for(int i{newXb}; i <= pieceX; ++i){
                                board_t[i][pieceY] = board_f[i][pieceY];
                            }
                            break;
                        }
                    }   
                }
            } 
            newXb = 0;  
        }

        if(horC >= 1){
            newYb = pieceY + horC;
            if(newYb >= 0 && newYb < 8){
                if(board_t[pieceX][newYb] != 'w'){
                    board_t[pieceX][newYb] = '*';
                }
                
                for(int j{pieceY}; j < newYb; ++j){
                    if(board_t[pieceX][j] == 'b'){
                        if(newYb >= 0 && newYb < 8){
                             for(int j{pieceY}; j <= newYb; ++j){
                                board_t[pieceX][j] = board_f[pieceX][j];
                             }
                            break;
                        }
                    }   
                }   
            }
            newYb = 0;

            newYb = pieceY - horC;
            if(newYb >= 0 && newYb < 8){
                if(board_t[pieceX][newYb] != 'w'){
                        board_t[pieceX][newYb] = '*';
                }
    
                for(int j{newYb}; j < pieceY; ++j){
                    if(board_t[pieceX][j] == 'b'){
                        if(newYb >= 0 && newYb < 8){
                            for(int j{newYb}; j <= pieceY; ++j){
                                board_t[pieceX][j] = board_f[pieceX][j];
                            }
                            break;
                        }
                    }   
                }
            }
            newYb = 0;
        }
        
        if(odiagC >= 1){
           newYb = pieceY + odiagC;
           newXb = pieceX + odiagC;
           if((newYb >= 0 && newYb < 8) && (newXb >= 0 && newXb < 8)){
                if(board_t[newXb][newYb] != 'w'){
                    board_t[newXb][newYb] = '*';
                }
           
            int odc = pieceY - pieceX;
            int j{};
            for(int i{pieceX}; i < newXb; ++i){
                    j = i + odc;
                    if(board_t[i][j] == 'b'){ 
                        for(int i{pieceX}; i <= newXb; ++i){
                            j = i + odc;
                            board_t[i][j] = board_f[i][j];
                        }    
                        break;
                    }               
                }
            }       
            newYb = 0;
            newXb = 0;

            newYb = pieceY - odiagC;
            newXb = pieceX - odiagC;
            if((newYb >= 0 && newYb < 8) && (newXb >= 0 && newXb < 8)){ 
                if(board_t[newXb][newYb] != 'w'){
                    board_t[newXb][newYb] = '*';
                }
            
                int odc = pieceY - pieceX;
                int j{};
                for(int i{newXb+1}; i < pieceX ;++i){
                    j = i + odc;                
                    if(board_t[i][j] == 'b'){
                        for(int i{newXb}; i <= pieceX ;++i){
                            j = i + odc;
                            board_t[i][j] = board_f[i][j];        
                        } 
                        break;
                    }
                    
                }
            }
            newYb = 0;
            newXb = 0;

        }

        if(diagC >= 1){
            newXb = pieceX + diagC;
            newYb = pieceY - diagC;
            if((newYb >= 0 && newYb < 8) && (newXb >= 0 && newXb < 8)){
                if(board_t[newXb][newYb] != 'w'){
                    board_t[newXb][newYb] = '*';
                }
            
                int dc = pieceY + pieceX;
                int j{};
                for(int i{pieceX}; i < newXb ;++i){
                    j = -i + dc;
                    if(board_t[i][j] == 'b'){
                        for(int i{pieceX}; i <= newXb ;++i){
                            j = -i + dc;
                            board_t[i][j] = board_f[i][j];        
                        }      
                        break;
                    }
                }
            }
            newYb = 0;
            newXb = 0;

            newXb = pieceX - diagC;
            newYb = pieceY + diagC;

            if((newYb >= 0 && newYb < 8) && (newXb >= 0 && newXb < 8)){
                if(board_t[newXb][newYb] != 'w'){
                    board_t[newXb][newYb] = '*';
                }
            
                int dc = pieceX + pieceY;
                int j{};
                for(int i{newXb}; i < pieceX ;++i){
                    j = -i + dc;
                    if(board_t[i][j] == 'b'){
                        for(int i{newXb}; i <= pieceX ;++i){
                            j = -i + dc;
                            board_t[i][j] = board_f[i][j];        
                        }  
                        break;
                    }
                }
            }    
        }
        newXb = 0;
        newYb = 0;
        print_board(board_t);
    }

}

//code should be fine after this. emphasis on should
void countbw(char board_t[ROWS][COLS], int pieceX, int pieceY, char player, int& vertMove, int& horMove, int& odMove, int& diagMove) {
    int countV{};//upwards vertical
    int countH{};// right horizontal
    int countod{};//d for diagonal
    int countd{};  
    for(size_t i{}; i < ROWS; ++i){
        if(board_t[i][pieceY] == 'b' || board_t[i][pieceY] == 'w'){
            ++countV;
        }
    }
    vertMove = countV;
    
                      
    for(size_t j{}; j < COLS; ++j){ //horizontal count
        if(board_t[pieceX][j] == 'b'|| board_t[pieceX][j] == 'w'){
            ++countH;
        }
    }
    horMove = countH;

    
    int odc = pieceY - pieceX;// using y = mx formula to calcuate
    size_t y{};

    for(size_t i{}; i < ROWS; ++i){
        y = i + odc;
        if(is_valid(i, y)){
            if(board_t[i][y] == 'b' || board_t[i][y] == 'w'){
                   ++countod;
            }
        }    
    }
    odMove = countod; //off diagonal 


    int dc = pieceY + pieceX;   //diag
    y = 0;
    for(size_t i{}; i < ROWS; ++i){
        y = -i + dc;
        if(is_valid(i, y)){
            if(board_t[i][y] == 'b' || board_t[i][y] == 'w'){
                ++countd;
            }
        } 
    }
    diagMove = countd;

} 

//if you dont give appropriate inputs the program breaks. dont know how to force a certain input.
void get_player_move(char board_f[ROWS][COLS],char board_t[ROWS][COLS], int row, int col, int pieceX, int pieceY, char player){
    char cont{'y'};

    if(player){
        while(cont == 'y'){
            std::cout << "Choose piece. Player: " << player << std::endl;
            std::cin >> pieceX;
            std::cin >> pieceY;
            if(board_t[pieceX][pieceY] == player){
                std::cout << "Valid piece selected." << std::endl;
                get_possible_moves(board_f, board_t, pieceX, pieceY, player);
            }else{
                for(size_t i{}; i < ROWS; ++i){
                    for(size_t j{}; j < COLS; ++j){
                        board_t[i][j] = board_f[i][j];
                    }
                }
                std::cout << "Invalid piece selected, try again." << std::endl;
                bool pieceCheck = false;
                while(pieceCheck == false){
                    pieceX = 0;
                    pieceY = 0;
                    std::cin >> pieceX;
                    std::cin >> pieceY;
                    pieceCheck = isPiece(board_t,pieceX,pieceY, player);
                }
                get_possible_moves(board_f, board_t, pieceX, pieceY, player);
            }
            std::cout << "Choose another piece? y/n" << std::endl;
            std::cin >> cont;
            if(cont == 'y'){
                pieceX = 0;
                pieceY = 0;
                for(size_t i{}; i < ROWS; ++i){
                    for(size_t j{}; j < COLS; ++j){
                        board_t[i][j] = board_f[i][j];
                    }
                }
                print_board(board_t);
            }
        }
        std::cout << "Input a position to move the piece to." << std::endl;
        print_possible_moves(board_t);
        std::cin >> row;
        std::cin >> col;
        bool valid_mv = valid_move(board_t, row, col, pieceX, pieceY, player);
        if(valid_mv){
            add_move(board_f, row, col, pieceX, pieceY, player);
            //clear();
            for(size_t i{}; i < ROWS; ++i){
                for(size_t j{}; j < COLS; ++j){
                    board_t[i][j] = board_f[i][j];
                }
            }
            print_board(board_f);
        }else{
            while(valid_mv == false){
                row = 0;
                col = 0;
                std::cout << "Input valid a move: " << std::endl;
                std::cin >> row;
                std::cin >> col;
                valid_mv = valid_move(board_t, row, col, pieceX, pieceY, player);
                
            }
            add_move(board_f, row, col, pieceX, pieceY, player);
            //clear();
            for(size_t i{}; i < ROWS; ++i){
                for(size_t j{}; j < COLS; ++j){
                    board_t[i][j] = board_f[i][j];
                }
            }
            print_board(board_f);
        
        }
    }
}

bool valid_move(char board_t[ROWS][COLS], int row, int col, int pieceX, int pieceY, char player){
    bool vali = false;
    if(player){
        if(board_t[row][col] == '*'){
            vali = true;
        }else{
            vali = false;
        }
    }
    return vali;
    
}

void add_move(char board_f[ROWS][COLS], int row, int col, int pieceX, int pieceY, char player){
    if(player){
        board_f[pieceX][pieceY] = '.';
        board_f[row][col] = player;
    }
}

bool isPiece(char board_t[ROWS][COLS] ,int pieceX,int pieceY,char player){
    bool piece = false;
    if(player){
        if(board_t[pieceX][pieceY] == player){
            std::cout << "Valid piece selected." << std::endl;
            piece = true;
        }else{
            std::cout << "Invalid piece selected, try again." << std::endl;
            piece = false;
        }
    }
    return piece;
}

void print_possible_moves(char board_t[ROWS][COLS]){
    for(size_t i{}; i < ROWS; ++i){
        for(size_t j{}; j < COLS; ++j){
            if(board_t[i][j] == '*'){
                std::cout << "* @ " << i << " " << j << '\n';
            }
        }
    }
}
