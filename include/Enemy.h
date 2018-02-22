//
// Created by Kike Piera Serra on 22/02/2018.
//

#ifndef SPACEINVADERS_ENEMY_H
#define SPACEINVADERS_ENEMY_H


#include "Entity.h"

class Enemy : public Entity{
public:
    Enemy() = default;

    Enemy(int xS, int yS, int xP, int yP);

    void update(int currentFrame, bool movingRight);


};


#endif //SPACEINVADERS_ENEMY_H
