//
// Created by Kike Piera Serra on 22/02/2018.
//

#ifndef SPACEINVADERS_ENTITY_H
#define SPACEINVADERS_ENTITY_H

#include <iostream>

using namespace std;

class Entity {
public:
    Entity();

    Entity(int xS, int yS, int xP, int yP);

    void update();


    //GETTERS

    int getXSpeed() const;

    int getYSpeed() const;

    int getXPosition() const;

    int getYPosition() const;


    //SETTERS

    void setXSpeed(int xSpeed);

    void setYSpeed(int ySpeed);

    void setXPosition(int xPosition);

    void setYPosition(int yPosition);

protected:
    //TODO:: change speed to how often to move
    int xSpeed;
    int ySpeed;

    int xPosition;
    int yPosition;

    int lastXMovement;
    int lastYMovement;

};


#endif //SPACEINVADERS_ENTITY_H
