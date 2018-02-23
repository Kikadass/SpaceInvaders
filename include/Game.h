//
// Created by Kike Piera Serra on 22/02/2018.
//

#ifndef SPACEINVADERS_GAME_H
#define SPACEINVADERS_GAME_H

#include <vector>
#include <opencv/cv.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

using namespace cv;

class Game {
public:
    static int HEIGHT;
    static int WIDTH;

    Game();

    Game(int h, int w, Mat g);

    void update(int currentFrame, bool pressed[]);


    //GETTERS

    const Mat &getGrid() const;

    int getScore() const;

    const vector<Enemy> &getEnemies() const;

    const vector<Bullet> &getBullets() const;

    const Player &getPlayer() const;

    bool isGameOver() const;


    //SETTERS

    void setGrid(const Mat &grid);

    void setScore(int score);

    void setEnemies(const vector<Enemy> &enemies);

    void setBullets(const vector<Bullet> &bullets);

    void setPlayer(const Player &player);

    void setGameOver(bool gameOver);


private:
    Mat grid;
    int score;
    int shootingRate;
    int lastShot;
    vector<Enemy> enemies;
    vector<Bullet> bullets;
    Player player;
    bool gameOver;
    bool movingRight;
    bool changingDirection;

    void updateGrid();

    void initializeVariables();
};


#endif //SPACEINVADERS_GAME_H
