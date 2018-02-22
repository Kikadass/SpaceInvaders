//
// Created by Kike Piera Serra on 22/02/2018.
//

#include "Bullet.h"

Bullet::Bullet(int xS, int yS, int xP, int yP) : Entity(xS, yS, xP, yP) {
}

void Bullet::update(int currentFrame) {
    long elapsedY = currentFrame - lastYMovement;


    //move on y
    if (elapsedY > ySpeed){
        yPosition--;

        lastYMovement = currentFrame;
    }

    Entity::update();
}
