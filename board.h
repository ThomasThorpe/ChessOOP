#ifndef BOARD_H
#define BOARD_H

#include "colour.h"
#include "playertype.h"
#include "piecetype.h"
#include "player.h"
#include "piece.h"
#include <string>

class Board{
    private:
        Piece board[8][8];
        Player players[2];
        Colour playerTurn;
        bool gameWon;
    public:
        Board();
        void initBoard();
        void drawBoard();
        bool checkGameWon();
        bool validMove(std::string move);
        bool checkPawnMove(int,int,int,int);
        bool checkPawnAttack(int,int,int,int);
        bool checkRookMove(int,int,int,int);
        bool checkKnightMove(int,int,int,int);
        bool checkBishopMove(int,int,int,int);
        bool checkQueenMove(int,int,int,int);
        bool checkKingMove(int,int,int,int);
        bool checkIfCheck(int,int,Colour);
        void executeMove(int,int,int,int);
        int columnLetterToIndex(char);
        Piece getPieceAtLocation(int,int);
        Player getPlayer(int);
        Colour getPlayerTurn();
        void nextPlayerTurn();
        bool getGameWon();
        void setGameWon(bool);
};

#endif