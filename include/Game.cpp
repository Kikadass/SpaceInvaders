//
// Created by Kike Piera Serra on 22/02/2018.
//

#include "Game.h"

int Game::HEIGHT = 16;
int Game::WIDTH = 20;

Game::Game() {
    HEIGHT = 0;
    WIDTH = 0;
    initializeVariables();
}

Game::Game(int h, int w, Mat g) {
    HEIGHT = h;
    WIDTH = w;
    grid = g;
    for (int y = 0; y < grid.cols; y++){
        for (int x = 0; x < grid.rows; x++){

            //if found an enemy in the grid
            if (grid.at<float>(y,x) == 0.3f){
                enemies.push_back(Enemy(240, 10, x, y));
            }
            //if found player in the grid
            else if (grid.at<float>(y,x) == 1){
                player = Player(360, 0, x, y);
            }
        }
    }

    initializeVariables();
}

void Game::initializeVariables(){
    score = 0;
    shootingRate = 3600/180;
    lastShot = 0;
    gameOver = false;
    movingRight = true;
    changingDirection = false;
}

void Game::update(int currentFrame, bool pressed[]){

    // space pressed
    if (pressed[0] && currentFrame - lastShot > shootingRate) {
        bullets.push_back(Bullet(0, 360, player.getXPosition(), player.getYPosition()-1));
        lastShot = currentFrame;
    }
    player.update(currentFrame, pressed[1], pressed[2]);

    for (int i = 0; i < bullets.size(); i++) {
        //remove bullets if they go off the screen
        if (bullets.at(i).getYPosition() == 0) {
            bullets.erase(bullets.begin() + i);
            i--;
            continue;
        }
        bullets.at(i).update(currentFrame);
    }

    bool changeDirection = false;
    for (Enemy &e: enemies){
        e.update(currentFrame, movingRight);

        if (e.getXPosition() == 0 || e.getXPosition() == Game::WIDTH-1){
            changeDirection = true;
        }
    }

    if (changeDirection && !changingDirection) {
        movingRight = !movingRight;
        changingDirection = true;
    }
    if (!changeDirection && changingDirection){
        changingDirection = false;
    }


    updateGrid();
}

void Game::updateGrid(){
    grid = Scalar::all(0);

    grid.at<float>(player.getYPosition(), player.getXPosition()) = 1.0f;

    for (Bullet b: bullets){
        grid.at<float>(b.getYPosition(), b.getXPosition()) = 0.5f;
    }

    for (int i = 0; i < enemies.size(); i++){
        // check if its game over
        if (enemies.at(i).getYPosition() >= player.getYPosition()) gameOver = true;

        //check for bullets hitting enemies
        if (grid.at<float>(enemies.at(i).getYPosition(), enemies.at(i).getXPosition()) == 0.5f){
            score++;

            //delete bullet that collided with enemy
            for (int j = 0; j < bullets.size(); j++){
                if (bullets.at(j).getYPosition() == enemies.at(i).getYPosition()
                        && bullets.at(j).getXPosition() == enemies.at(i).getXPosition()) {
                    bullets.erase(bullets.begin() + j);
                }
            }

            //delete enemy
            enemies.erase(enemies.begin() + i);
        }
        else grid.at<float>(enemies.at(i).getYPosition(), enemies.at(i).getXPosition()) = 0.3f;


    }

}


//GETTERS

const Mat &Game::getGrid() const {
    return grid;
}

int Game::getScore() const {
    return score;
}

const vector<Enemy> &Game::getEnemies() const {
    return enemies;
}

const vector<Bullet> &Game::getBullets() const {
    return bullets;
}

const Player &Game::getPlayer() const {
    return player;
}

bool Game::isGameOver() const {
    return gameOver;
}

//SETTERS

void Game::setGrid(const Mat &grid) {
    Game::grid = grid;
}

void Game::setScore(int score) {
    Game::score = score;
}

void Game::setEnemies(const vector<Enemy> &enemies) {
    Game::enemies = enemies;
}

void Game::setBullets(const vector<Bullet> &bullets) {
    Game::bullets = bullets;
}

void Game::setPlayer(const Player &player) {
    Game::player = player;
}

void Game::setGameOver(bool gameOver) {
    Game::gameOver = gameOver;
}
