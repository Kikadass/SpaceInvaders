//
// Created by Kike Piera Serra on 22/02/2018.
//

#include "Enemy.h"

Enemy::Enemy(int xS, int yS, int xP, int yP) : Entity(xS, yS, xP, yP) {
}

void Enemy::update(int currentFrame, bool movingRight) {
    int elapsedX = currentFrame - lastXMovement;
    int elapsedY = currentFrame - lastYMovement;


    //move on x
    if (elapsedX > xSpeed){
        if (movingRight) xPosition++;
        else xPosition--;

        lastXMovement = currentFrame;
    }

    //move on y
    if (elapsedY > ySpeed){
        yPosition++;
        lastYMovement = currentFrame;
    }


    Entity::update();
}
