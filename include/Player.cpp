//
// Created by Kike Piera Serra on 22/02/2018.
//

#include "Player.h"

Player::Player() : Entity() {
    initializeVariables();
}

Player::Player(int xS, int yS, int xP, int yP) : Entity(xS, yS, xP, yP) {
    initializeVariables();
}

void Player::update(int currentFrame, bool right, bool left) {
    if (right) rightPressed = true;
    if (left)  leftPressed = true;

    long elapsedX = currentFrame - lastXMovement;

    //move on x
    if (elapsedX > xSpeed){
        //if both have been pressed, player is not going to move
        if (rightPressed) {
            xPosition++;
            lastXMovement = currentFrame;
            rightPressed = false;
        }
        if (leftPressed) {
            xPosition--;
            lastXMovement = currentFrame;
            leftPressed = false;
        }
    }

    Entity::update();
}


int Player::getLives() const {
    return lives;
}

void Player::setLives(int lives) {
    Player::lives = lives;
}

void Player::initializeVariables(){
    lives = 3;
    rightPressed = false;
    leftPressed = false;
}