#include "piece.h"
#include "colour.h"
#include "piecetype.h"
#include <iostream>
#include <string>

Piece::Piece(){}
Piece::Piece(int x,int y,PieceType t,Colour c){
    setXpos(x);
    setYpos(y);
    setColour(c);
    setType(t);
}
int Piece::getXpos(){return xpos;}
int Piece::getYpos(){return ypos;}
void Piece::setXpos(int x){
    if(x < 0 || x > 7){throw std::domain_error("X posititon has to be within 0-7!");}
    xpos = x;
}
void Piece::setYpos(int y){
    if(y < 0 || y > 7){throw std::domain_error("Y posititon has to be within 0-7!");}
    ypos = y;
}
PieceType Piece::getType(){return type;}
void Piece::setType(PieceType t){
    type = t;
    //update character used as representation
    switch (type)
    {
    case PAWN:
        if(colour == WHITE){symbol = 'P';}else{symbol = 'p';}
        break;
    case ROOK:
        if(colour == WHITE){symbol = 'R';}else{symbol = 'r';}
        break;
    case KNIGHT:
        if(colour == WHITE){symbol = 'H';}else{symbol = 'h';}
        break;
    case BISHOP:
        if(colour == WHITE){symbol = 'B';}else{symbol = 'b';}
        break;
    case QUEEN:
        if(colour == WHITE){symbol = 'Q';}else{symbol = 'q';}
        break;
    case KING:
        if(colour == WHITE){symbol = 'K';}else{symbol = 'k';}
        break;
    case NOTYPE:
        symbol = ' ';
    }
}
Colour Piece::getColour(){return colour;}
void Piece::setColour(Colour c){colour = c;}
char Piece::getSymbol(){return symbol;}
void Piece::toString(){
    std::string t, c;
    switch (type)
    {
    case PAWN:
        t = "pawn";
        break;
    case ROOK:
        t = "rook";
        break;
    case KNIGHT:
        t = "knight";
        break;
    case BISHOP:
        t = "bishop";
        break;
    case QUEEN:
        t = "queen";
        break;
    case KING:
        t = "king";
        break;
    case NOTYPE:
        t = "empty";
    }
    switch (colour)
    {
    case WHITE:
        c = "white";
        break;
    case BLACK:
        c = "black";
        break;
    case NOCOLOUR:
        c = "empty";
    }
    std::cout << "This piece is a " << t << " and is colour " << c << " at position " << xpos << "x" << ypos << "y" << std::endl;
}