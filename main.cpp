#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv/cv.hpp>
#include "include/Game.h"

using namespace std;
using namespace cv;

void scaleUp(Mat image, int scale){
    resize(image, image, image.size()*scale, 0, 0, INTER_AREA);   //resize image
    imshow("Space Invaders", image);                   // Show our image inside it.
}


int main() {
    int height = 16;
    int width = 20;

    vector<vector<float>> tilesV = {{0.0, 0.0, 0.0, 0.0 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3, 0.0, 0.0, 0.0, 0.0},
                                    {0.0, 0.0, 0.0, 0.0 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3, 0.0, 0.0, 0.0, 0.0},
                                    {0.0, 0.0, 0.0, 0.0 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3, 0.0, 0.0, 0.0, 0.0},
                                    {0.0, 0.0, 0.0, 0.0 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3, 0.0, 0.0, 0.0, 0.0},
                                    {0.0, 0.0, 0.0, 0.0 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3, 0.0, 0.0, 0.0, 0.0},
                                    {0.0, 0.0, 0.0, 0.0 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3, 0.0, 0.0, 0.0, 0.0},
                                    {0.0, 0.0, 0.0, 0.0 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3, 0.0, 0.0, 0.0, 0.0},
                                    {0.0, 0.0, 0.0, 0.0 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3, 0.0, 0.0, 0.0, 0.0},
                                    {0.0, 0.0, 0.0, 0.0 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3 ,0.3, 0.0, 0.0, 0.0, 0.0},
                                    {0.0, 0.0, 0.0, 0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0, 0.0, 0.0, 0.0, 0.0},
                                    {0.0, 0.0, 0.0, 0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0, 0.0, 0.0, 0.0, 0.0},
                                    {0.0, 0.0, 0.0, 0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0, 0.0, 0.0, 0.0, 0.0},
                                    {0.0, 0.0, 0.0, 0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0, 0.0, 0.0, 0.0, 0.0},
                                    {0.0, 0.0, 0.0, 0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0, 0.0, 0.0, 0.0, 0.0},
                                    {0.0, 0.0, 0.0, 0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,1.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0, 0.0, 0.0, 0.0, 0.0},
                                    {0.0, 0.0, 0.0, 0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0, 0.0, 0.0, 0.0, 0.0},
    };

    Mat tiles = Mat(height, width, CV_32F);
    for (int i = 0; i < tilesV.size(); i++){
        for (int j = 0; j < tilesV.at(i).size(); j++){
            tiles.at<float>(i, j) = tilesV.at(i).at(j) ;
        }
    }


    Game game = Game(height, width, tiles);
    float fps = 60;
    float clocksPerUpdate = (float)CLOCKS_PER_SEC/fps;
    int currentFrame = 0;

    cout << clocksPerUpdate << endl;

    clock_t lastFrame = clock();
    while (!game.isGameOver()) {
        clock_t now = clock();
        //cout << (now - lastFrame) <<  endl;
        if ((now - lastFrame) > clocksPerUpdate) {
            currentFrame++;
            lastFrame = now;

            Mat showTiles = tiles;
            scaleUp(showTiles, 20);
            bool pressed[3];

            int keyPressed = waitKeyEx(1);

            // if pressed ESC it closes the program  (ESC = 27 ASCII)
            if (keyPressed == 27) {
                return 0;
            }

            if (keyPressed == 32) {  // space
                pressed[0] = true;
            } else pressed[0] = false;

            if (keyPressed == 63235) {  // right
                pressed[1] = true;
            } else pressed[1] = false;

            if (keyPressed == 63234) {  // left
                pressed[2] = true;
            } else pressed[2] = false;

            //check if buttons were pressed
            game.update(currentFrame, pressed);

            tiles = game.getGrid();
        }
    }

    game.getScore();
    cout << "GAME OVER! Score: " << game.getScore() << endl;

    return 0;
}