#include "player.h"
#include "colour.h"
#include "playertype.h"
#include <iostream>
#include <string>

Player::Player(){}
Player::Player(PlayerType t, Colour c){
    setType(t);
    setColour(c);
}
PlayerType Player::getType(){return type;}
Colour Player::getColour(){return colour;}
void Player::setType(PlayerType t){type = t;}
void Player::setColour(Colour c){colour = c;}
void Player::toString(){
    std::string t, c;
    switch (type)
    {
    case HUMAN:
        t = "human";
        break;
    case COMPUTER:
        t = "computer";
    }
    switch (colour)
    {
    case WHITE:
        c = "white";
        break;
    case BLACK:
        c = "black";
    }
    std::cout << "This player is type " << t << " and colour " << c << std::endl;
}