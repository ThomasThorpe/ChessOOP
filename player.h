#ifndef PLAYER_H
#define PLAYER_H

#include "colour.h"
#include "playertype.h"

class Player{
    private:
        PlayerType type;
        Colour colour;
    public:
        Player();
        Player(PlayerType,Colour);
        PlayerType getType();
        Colour getColour();
        void setType(PlayerType);
        void setColour(Colour);
        void toString();
};

#endif