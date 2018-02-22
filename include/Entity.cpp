//
// Created by Kike Piera Serra on 22/02/2018.
//

#include "Entity.h"
#include "Game.h"

Entity::Entity() {
    xSpeed = 0;
    ySpeed = 0;

    xPosition = 0;
    yPosition = 0;

    lastXMovement = 0;
    lastYMovement = 0;
}

Entity::Entity(int xS, int yS, int xP, int yP) {
    if (xS <= 0) xSpeed = 0;
    else xSpeed = 3600/xS;

    if (yS <= 0) ySpeed = 0;
    else ySpeed = 3600/yS;

    xPosition = xP;
    yPosition = yP;

    lastXMovement = 0;
    lastYMovement = 0;
}

void Entity::update() {
    if (xPosition < 0){
        xPosition = 0;
    }
    else if (xPosition > Game::WIDTH-1){
        xPosition = Game::WIDTH-1;
    }

    if (yPosition < 0){
        yPosition = 0;
    }
    else if (yPosition > Game::HEIGHT-1){
        yPosition = Game::HEIGHT-1;
    }
}


//GETTERS

int Entity::getXSpeed() const {
    return xSpeed;
}

int Entity::getYSpeed() const {
    return ySpeed;
}

int Entity::getXPosition() const {
    return xPosition;
}

int Entity::getYPosition() const {
    return yPosition;
}


//SETTERS

void Entity::setXSpeed(int xSpeed) {
    Entity::xSpeed = xSpeed;
}

void Entity::setYSpeed(int ySpeed) {
    Entity::ySpeed = ySpeed;
}

void Entity::setXPosition(int xPosition) {
    Entity::xPosition = xPosition;
}

void Entity::setYPosition(int yPosition) {
    Entity::yPosition = yPosition;
}
