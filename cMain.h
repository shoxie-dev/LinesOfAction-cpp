
#pragma once

#include "wx/wx.h"
#include "player.h"
#include "board.h"
#include <iomanip>

class cMain : public wxFrame//start of our GUI
{
    public:
        cMain();
        void resetBoard(char board_t[8][8], char board_p[8][8]);
        void addMoveGUI(int pieceX, int pieceY, int moveX, int moveY, char colour);
        wxBitmap getPieceBitmap(char square);
        ~cMain();
        wxButton* squares[8][8];
        bool selectedPiece{false};
        bool valid_piece{false};
        bool validMove{false};
        int selectedX{};
        int selectedY{};
        void SwitchTurn();

        bool isWin{false};
        bool isDraw{false};

        char player1;
        char player2;
        char* currentPlayer;

        
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
        char board_t[ROWS][COLS] = {                  //board to print test moves
            {'.','b','b','b','b','b','b','.'},
            {'w','.','.','.','.','.','.','w'},
            {'w','.','.','.','.','.','.','w'},
            {'w','.','.','.','.','.','.','w'},
            {'w','.','.','.','.','.','.','w'},
            {'w','.','.','.','.','.','.','w'},
            {'w','.','.','.','.','.','.','w'},
            {'.','b','b','b','b','b','b','.'}
        };
        
        void printBoard(char board[ROWS][COLS]){
            for(size_t i{}; i < ROWS; ++i){
                for(size_t j{}; j < COLS; ++j){
                    std::cout << std::setw(2) <<board[i][j] ;
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;   
        }

        void OnButtonPress(wxCommandEvent& event);

        void ResultAnnouncement(std::string message){
            wxMessageDialog* dialog = new wxMessageDialog(nullptr, message, "Game Over", wxOK);
            dialog->ShowModal();  // Show the dialog
            dialog->Destroy(); 
            wxExit();
        }


};  
