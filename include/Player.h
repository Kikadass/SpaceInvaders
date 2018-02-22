//
// Created by Kike Piera Serra on 22/02/2018.
//

#ifndef SPACEINVADERS_PLAYER_H
#define SPACEINVADERS_PLAYER_H


#include "Entity.h"

class Player : public Entity{
public:
    Player();

    Player(int xS, int yS, int xP, int yP);

    void update(int currentFrame, bool right, bool left);

    int getLives() const;

    void setLives(int lives);

private:
    int lives;

    bool rightPressed;
    bool leftPressed;

    void initializeVariables();
};


#endif //SPACEINVADERS_PLAYER_H
