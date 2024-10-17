
#include "cMain.h"


cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Lines of Action",wxPoint(30, 30), wxSize(1024, 768), wxCAPTION | wxCLOSE_BOX | wxMINIMIZE_BOX)
{
    //player stuff 
    player1 = 'b';
    player2 = 'w';
    currentPlayer = &player1;
    isWin = false;
    isDraw = false;
    wxGridSizer* grid = new wxGridSizer(8,8, 0, 0); 

    for(int i{}; i < 8; ++i){
        for(int j{}; j < 8; ++j){
            int id = 1000 + (i*8 + j);
            squares[i][j] = new wxButton(this, id, "",wxDefaultPosition, wxSize(64,64) );
            grid -> Add(squares[i][j],1, wxEXPAND|wxALL);
            squares[i][j] ->Bind(wxEVT_BUTTON,  &cMain::OnButtonPress, this);
        }
    }

    wxBitmap black_piece("./pieces/black.png");
    wxBitmap white_piece("./pieces/white.png");

    for(int j{}; j < 6; ++j){
        squares[0][j+1]->SetBitmap(black_piece);
        squares[7][j+1]->SetBitmap(black_piece);
        squares[j+1][0]->SetBitmap(white_piece);
        squares[j+1][7]->SetBitmap(white_piece);
    }
    
    CreateStatusBar();
    SetSizer(grid, true);
}

cMain::~cMain()
{
    
}

void cMain::OnButtonPress(wxCommandEvent& event){
    wxButton* btn = dynamic_cast<wxButton*> (event.GetEventObject());

    if(!btn) return;

    if(btn){
        int id = event.GetId();
        int x = (id - 1000) / 8;
        int y = (id - 1000) % 8;
        wxLogStatus("Player: %c", *currentPlayer);

        if(isDraw || isWin){
            wxExit();
        }

        if(!selectedPiece){
            valid_piece = isPiece(board_p, x, y, *currentPlayer);
            if(valid_piece){
                selectedPiece = true;
                selectedX = x;
                selectedY = y;
            }
        }else{
            get_possible_moves(board_p, board_t, selectedX, selectedY, *currentPlayer);
            printBoard(board_t);
            validMove = valid_move(board_t, x, y, selectedX, selectedY, *currentPlayer);
            if(validMove){
                add_move(board_p, x, y, selectedX, selectedY, *currentPlayer);
                addMoveGUI(selectedX, selectedY, x, y, *currentPlayer);
                resetBoard(board_t, board_p);//update possible moves board.
                
                isDraw = check_draw(board_p);
                if(isDraw == true){
                    std::string message = "Game is a draw";
                    ResultAnnouncement(message);
                } 
                isWin = are_all_pieces_adjacent(board_p,*currentPlayer);
                if(isDraw == false){
                    if(isWin == true){
                        std::string Player{};
                        std::string x_wins = " wins";
                        if(*currentPlayer == 'b'){
                            Player = "Black";
                        }else if(*currentPlayer == 'w'){
                            Player = "White";
                        }
                        std::string message = Player + x_wins;
                        ResultAnnouncement(message);
                    }
                }
                
                //update         
                squares[selectedX][selectedY]->Refresh();
                squares[selectedX][selectedY]->Update();
                squares[x][y]->Refresh();
                squares[x][y]->Update();
                //reset
                valid_piece = false;
                selectedPiece = false;
                validMove = false;
                selectedX = -1;
                selectedY = -1;
                SwitchTurn();
            }else if(selectedPiece){
                valid_piece = isPiece(board_p, x, y, *currentPlayer);
                if(valid_piece){
                    resetBoard(board_t, board_p);
                    selectedPiece = true;
                    selectedX = x;
                    selectedY = y;
                }

            }

        }
    }

}

void cMain::SwitchTurn(){
    if(currentPlayer == &player1){
        currentPlayer = &player2;
    }else if(currentPlayer == &player2){
        currentPlayer = &player1;
    }
}

void cMain::resetBoard(char board_t[8][8], char board_p[8][8]){
    for(int i{}; i < 8; ++i){
        for(int j{}; j < 8; ++j){
            board_t[i][j] = board_p[i][j];
        }
    }
}

void cMain::addMoveGUI(int pieceX, int pieceY, int moveX, int moveY, char colour){
    wxBitmap empty_square("./pieces/empty_block.png");
    squares[pieceX][pieceY]->SetBitmap(empty_square);
    wxBitmap piece = getPieceBitmap(colour);
    squares[moveX][moveY]->SetBitmap(piece);

}

wxBitmap cMain::getPieceBitmap(char square){
    wxBitmap piece;
    if(square == 'b'){
        wxBitmap black_piece("./pieces/black.png");
        return black_piece;
    }else if(square == 'w'){
        wxBitmap white_piece("./pieces/white.png");
        return white_piece;
    }

    return wxNullBitmap;
}

