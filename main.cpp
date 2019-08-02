#include "main.h"
#include "colour.h"
#include "board.h"
#include <string>
#include <iostream>

int main(){
    Board board;
    std::string moveEntered;

    while(! board.getGameWon()){
        board.drawBoard();
        if(board.getPlayerTurn() == WHITE){std::cout << "White to move: ";}else{std::cout << "Black to move: ";}
        std::cout << std::endl;
        do{
            std::cout << "Enter move in format: src-dst" << std::endl << "For example: A2-A3" << std::endl;
            getline(std::cin,moveEntered);
        } while (! board.validMove(moveEntered));
        board.nextPlayerTurn();
        board.checkGameWon();
    }
    std::cout << "Game has been won by: ";
    if(board.getPlayerTurn() == WHITE){std::cout << "Black";}else{std::cout << "White";}
    std::cout << '!' << std::endl;

    return 0;
}