//
// Created by Kike Piera Serra on 22/02/2018.
//

#ifndef SPACEINVADERS_BULLET_H
#define SPACEINVADERS_BULLET_H


#include "Entity.h"

class Bullet : public Entity{
public:
    Bullet() = default;

    Bullet(int xS, int yS, int xP, int yP);


    void update(int currentFrame);



};


#endif //SPACEINVADERS_BULLET_H
