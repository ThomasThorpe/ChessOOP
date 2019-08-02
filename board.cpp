#include "board.h"
#include "colour.h"
#include "playertype.h"
#include "piecetype.h"
#include <iostream>
#include <string>

Board::Board(){
    players[0] = Player(HUMAN,WHITE);
    players[1] = Player(HUMAN,BLACK);
    playerTurn = WHITE;
    gameWon = false;
    initBoard();
}
void Board::initBoard(){
    board[0][0] = Piece(0,0,ROOK,WHITE);
    board[0][1] = Piece(1,0,KNIGHT,WHITE);
    board[0][2] = Piece(2,0,BISHOP,WHITE);
    board[0][3] = Piece(3,0,QUEEN,WHITE);
    board[0][4] = Piece(4,0,KING,WHITE);
    board[0][5] = Piece(5,0,BISHOP,WHITE);
    board[0][6] = Piece(6,0,KNIGHT,WHITE);
    board[0][7] = Piece(7,0,ROOK,WHITE);

    board[7][0] = Piece(0,7,ROOK,BLACK);
    board[7][1] = Piece(1,7,KNIGHT,BLACK);
    board[7][2] = Piece(2,7,BISHOP,BLACK);
    board[7][3] = Piece(3,7,QUEEN,BLACK);
    board[7][4] = Piece(4,7,KING,BLACK);
    board[7][5] = Piece(5,7,BISHOP,BLACK);
    board[7][6] = Piece(6,7,KNIGHT,BLACK);
    board[7][7] = Piece(7,7,ROOK,BLACK);

    for(int col = 0; col < 8; col++){
        board[1][col] = Piece(col,1,PAWN,WHITE);
        board[6][col] = Piece(col,6,PAWN,BLACK);
    }

    for(int row = 2; row < 6; row++){
        for(int col = 0; col < 8; col++){
            board[row][col] = Piece(col,row,NOTYPE,NOCOLOUR);
        }
    }
}
void Board::drawBoard(){
    std::cout << ' ';
    for(int i = 0; i < 17; i++){
        std::cout << '-';
    }
    std::cout << std::endl;
    for(int row = 7; row >= 0; row--){
        std::cout << row + 1 << '|';
        for(int col = 0; col < 8; col++){
            std::cout << board[row][col].getSymbol() << '|';
        }
        std::cout << std::endl << ' ';
        for(int i = 0; i < 17; i++){
            std::cout << '-';
        }
        std::cout << std::endl;
    }
    std::cout << "  A B C D E F G H" << std::endl;
}
bool Board::checkGameWon(){
    //get king position
    int kingX, kingY;
    for(int row = 0; row < 8; row++){
        for(int col = 0; col < 8; col++){
            if(board[row][col].getColour() == playerTurn && board[row][col].getType() == KING){
                kingX = col; kingY = row;
            }
        }
    }

    //check if currently in check
    if(!checkIfCheck(kingX,kingY,playerTurn)){return false;}

    //check if king can move out of check
    for(int x = -1; x < 2; x++){
        for(int y = -1; y < 2; y++){
            if(checkKingMove(kingX,kingY,kingX+x,kingY+y)){return false;}
        }
    }

    //check if other pieces can move in the way
    //TODO
    setGameWon(true);
    return true;
}
bool Board::validMove(std::string move){
    std::string cols = "ABCDEFGH";
    std::string rows = "12345678";

    //check input is correct format
    if((cols.find(move[0]) == std::string::npos) || (rows.find(move[1]) == std::string::npos) || (move[2] != '-') || (cols.find(move[3]) == std::string::npos) || (rows.find(move[4]) == std::string::npos)){
        std::cout << "You didn't enter in the correct format!" << std::endl;
        return false;
    }

    //convert to indexes
    int srcX,srcY,dstX,dstY;
    srcX = columnLetterToIndex(move[0]);
    srcY = (int)move[1] - '0' - 1;
    dstX = columnLetterToIndex(move[3]);
    dstY = (int)move[4] - '0' - 1;

    //check selected position is a valid piece
    if(board[srcY][srcX].getColour() != playerTurn){
        std::cout << "That piece isn't the correct colour!" << std::endl;
        return false;
    }
    //check final position is not own piece
    if(board[dstY][dstX].getColour() == playerTurn){
        std::cout << "You cannot move to a square with your own piece!" << std::endl;
        return false;
    }

    //hand over to function based on piece type
    bool valid;
    switch (board[srcY][srcX].getType())
    {
    case PAWN:
        valid = checkPawnMove(srcX,srcY,dstX,dstY);
        break;
    case ROOK:
        valid = checkRookMove(srcX,srcY,dstX,dstY);
        break;
    case KNIGHT:
        valid = checkKnightMove(srcX,srcY,dstX,dstY);
        break;
    case BISHOP:
        valid = checkBishopMove(srcX,srcY,dstX,dstY);
        break;
    case QUEEN:
        valid = checkQueenMove(srcX,srcY,dstX,dstY);
        break;
    case KING:
        valid = checkKingMove(srcX,srcY,dstX,dstY);
        break;
    default:
        valid = false;
    }

    if(valid){ //execute move, check if in check, if so reverse
        Piece tmp1 = board[srcY][srcX];
        Piece tmp2 = board[dstY][dstX];
        int kingX, kingY;
        executeMove(srcX,srcY,dstX,dstY);
        for(int row = 0; row < 8; row++){
            for(int col = 0; col < 8; col++){
                if(board[row][col].getColour() == playerTurn && board[row][col].getType() == KING){
                    kingX = col; kingY = row;
                }
            }
        }
        if(checkIfCheck(kingX,kingY,playerTurn)){
            board[srcY][srcX] = tmp1;
            board[dstY][dstX] = tmp2;
            std::cout << "You are in check doing that move!" << std::endl;
            return false;
        } else {return true;}
    } else {return false;}
}
bool Board::checkPawnMove(int srcX, int srcY, int dstX, int dstY){
    if(board[srcY][srcX].getColour() == WHITE){
        //normal move forward
        if(dstX == srcX && dstY == srcY + 1 && board[dstY][dstX].getColour() == NOCOLOUR){return true;}
        //move forward twice first move only
        if(dstX == srcX && dstY == srcY + 2 && srcY == 1 && board[dstY][dstX].getColour() == NOCOLOUR && board[dstY-1][dstX].getColour() == NOCOLOUR){return true;}
        //capture diagonally
        if((dstX == srcX - 1 || dstX == srcX + 1) && dstY == srcY + 1 && board[dstY][dstX].getColour() == BLACK){return true;}
        //TODO En Passant
        return false;
    } else {
        //normal move forward
        if(dstX == srcX && dstY == srcY - 1 && board[dstY][dstX].getColour() == NOCOLOUR){return true;}
        //move forwrad twice first move only
        if(dstX == srcX && dstY == srcY - 2 && srcY == 6 && board[dstY][dstX].getColour() == NOCOLOUR && board[dstY+1][dstX].getColour() == NOCOLOUR){return true;}
        //capture diagonally
        if((dstX == srcX - 1 || dstX == srcX + 1) && dstY == srcY - 1 && board[dstY][dstX].getColour() == WHITE){return true;}
        //TODO En Passant
        return false;
    }
}
bool Board::checkPawnAttack(int srcX, int srcY, int dstX, int dstY){
    if(board[srcY][srcX].getColour() == WHITE){
        if((dstX == srcX - 1 || dstX == srcX + 1) && dstY == srcY + 1){return true;}
    } else {
        if((dstX == srcX - 1 || dstX == srcX + 1) && dstY == srcY - 1){return true;}
    }
    return false;
}
bool Board::checkRookMove(int srcX, int srcY, int dstX, int dstY){
    if(srcX == dstX && srcY != dstY){ //going vertical
        int increment = (dstY-srcY)/abs(dstY-srcY);
        for(int y = srcY + increment; y != dstY; y += increment){
            if(board[y][srcX].getColour() != NOCOLOUR){
                return false;
            }
        }
        return true;
    } else if(srcY == dstY && srcX != dstX){ //going horizontal
        int increment = (dstX-srcX)/abs(dstX-srcX);
        for(int x = srcX + increment; x != dstX; x += increment){
            if(board[srcY][x].getColour() != NOCOLOUR){
                return false;
            }
        }
        return true;
    } else {return false;} //not going in cardinal directions
}
bool Board::checkKnightMove(int srcX, int srcY, int dstX, int dstY){
    if((abs(srcX - dstX) == 2 && abs(srcY - dstY) == 1) || (abs(srcX - dstX) == 1 && abs(srcY - dstY) == 2)){
        return true;
    } else {return false;}
}
bool Board::checkBishopMove(int srcX, int srcY, int dstX, int dstY){
    if(abs(srcX-dstX) == abs(srcY-dstY)){
        int yincrement = (dstY-srcY)/abs(dstY-srcY);
        int xincrement = (dstX-srcX)/abs(dstX-srcX);
        for(int x = srcX + xincrement, y = srcY + yincrement; x != dstX; x += xincrement, y += yincrement){
            if(board[y][x].getColour() != NOCOLOUR){
                return false;
            }
        }
        return true;
    } else {return false;} //not going diagonally
}
bool Board::checkQueenMove(int srcX, int srcY, int dstX, int dstY){
    if(abs(srcX-dstX) == abs(srcY-dstY)){
        return checkBishopMove(srcX,srcY,dstX,dstY);
    } else if((srcX == dstX && srcY != dstY) || (srcY == dstY && srcX != dstX)){
        return checkRookMove(srcX,srcY,dstX,dstY);
    } else {return false;}
}
bool Board::checkKingMove(int srcX, int srcY, int dstX, int dstY){
    if(abs(srcX-dstX) > 1 || abs(srcY-dstY) > 1){
        return false;
    } else {
        return !checkIfCheck(dstX,dstY,playerTurn);
    }
}
bool Board::checkIfCheck(int dstX, int dstY, Colour c){
    bool check = false;
    for(int row = 0; row < 8; row++){
        for(int col = 0; col < 8; col++){
            if(board[row][col].getColour() == NOCOLOUR || board[row][col].getColour() == c ){
                continue;
            } else {
                switch (board[row][col].getType())
                {
                case KING:
                    continue;
                    break;
                case PAWN:
                    check = checkPawnAttack(col,row,dstX,dstY);
                    break;
                case ROOK:
                    check = checkRookMove(col,row,dstX,dstY);
                    break;
                case KNIGHT:
                    check = checkKnightMove(col,row,dstX,dstY);
                    break;
                case BISHOP:
                    check = checkBishopMove(col,row,dstX,dstY);
                    break;
                case QUEEN:
                    check = checkQueenMove(col,row,dstX,dstY);
                }
                if(check){return true;}
            }
        }
    }
    return false;
}
void Board::executeMove(int srcX, int srcY, int dstX, int dstY){
    board[dstY][dstX] = board[srcY][srcX];
    board[srcY][srcX] = Piece(srcX,srcY,NOTYPE,NOCOLOUR);
    
    board[dstY][dstX].setXpos(dstX);
    board[dstY][dstX].setYpos(dstY);
    //check if pawn needs promotion
    if(board[dstY][dstX].getType() == PAWN){
        char selection;
        if(playerTurn == WHITE && dstY == 7){
            std::string symbols = "PRHBQ";
            selection = 'Q';
            do{
                std::cout << "Please enter a character from {P,R,H,B,Q}" << std::endl;
                std::cin >> selection;
            } while (symbols.find(selection) == std::string::npos);
            switch (selection)
            {
            case 'P':
                board[dstY][dstX].setType(PAWN);
                break;
            case 'R':
                board[dstY][dstX].setType(ROOK);
                break;
            case 'H':
                board[dstY][dstX].setType(KNIGHT);
                break;
            case 'B':
                board[dstY][dstX].setType(BISHOP);
                break;
            case 'Q':
                board[dstY][dstX].setType(QUEEN);
            }
        } else if(playerTurn == BLACK && dstY == 0){
            std::string symbols = "prhbq";
            selection = 'q';
            do{
                std::cout << "Please enter a character from {p,r,h,b,q}" << std::endl;
                std::cin >> selection;
            } while (symbols.find(selection) == std::string::npos);
            switch (selection)
            {
            case 'p':
                board[dstY][dstX].setType(PAWN);
                break;
            case 'r':
                board[dstY][dstX].setType(ROOK);
                break;
            case 'h':
                board[dstY][dstX].setType(KNIGHT);
                break;
            case 'b':
                board[dstY][dstX].setType(BISHOP);
                break;
            case 'q':
                board[dstY][dstX].setType(QUEEN);
            }
        }
    }
}
int Board::columnLetterToIndex(char letter){
    switch (letter)
    {
    case 'A':
        return 0;
    case 'B':
        return 1;
    case 'C':
        return 2;
    case 'D':
        return 3;
    case 'E':
        return 4;
    case 'F':
        return 5;
    case 'G':
        return 6;
    case 'H':
        return 7;
    default:
        throw std::domain_error("Column character has to be between A-H!");
    }
}
Piece Board::getPieceAtLocation(int x, int y){
    if(x < 0 || x > 7){throw std::domain_error("X position has to be within 0-7!");}
    if(y < 0 || y > 7){throw std::domain_error("Y position has to be within 0-7!");}
    return board[y][x];
}
Player Board::getPlayer(int i){
    if(i < 0 || i > 1){throw std::domain_error("Player ID has to be 0 or 1!");}
    return players[i];
}
Colour Board::getPlayerTurn(){return playerTurn;}
void Board::nextPlayerTurn(){
    if(playerTurn == WHITE){playerTurn = BLACK;}else{playerTurn = WHITE;}
}
bool Board::getGameWon(){return gameWon;}
void Board::setGameWon(bool b){gameWon = b;}