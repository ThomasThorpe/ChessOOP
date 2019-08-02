#ifndef PIECE_H
#define PIECE_H

#include "colour.h"
#include "piecetype.h"

class Piece{
    private:
        int xpos, ypos;
        char symbol;
        PieceType type;
        Colour colour;
    public:
        Piece();
        Piece(int x,int y,PieceType t,Colour c);
        int getXpos();
        int getYpos();
        void setXpos(int);
        void setYpos(int);
        PieceType getType();
        void setType(PieceType);
        Colour getColour();
        void setColour(Colour);
        char getSymbol();
        void toString();
};

#endif