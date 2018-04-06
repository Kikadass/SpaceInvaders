#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv/cv.hpp>
#include <fstream>
#include <unistd.h>
#include "include/Game.h"


using namespace std;
using namespace cv;

//scale up image and show
void scaleUp(Mat image, int scale){
    resize(image, image, image.size()*scale, 0, 0, INTER_AREA);   //resize image
    imshow("Space Invaders", image);                   // Show our image inside it.
}

Mat initializeTiles(int height, int width){
    // initial Game screen. 0.3 are enemies 1.0 is the player, 0.5 would be bullets
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


    // put enemies and player into the Mat
    Mat tiles = Mat(height, width, CV_32F);
    for (int i = 0; i < tilesV.size(); i++){
        for (int j = 0; j < tilesV.at(i).size(); j++){
            tiles.at<float>(i, j) = tilesV.at(i).at(j);
        }
    }

    return tiles;
}

void writeTiles(Mat tiles){
    ofstream myfile;
    string file = "../../AI-SpaceInvaders/tiles.txt";
    myfile.open (file);
    if (!myfile.is_open()){
        throw runtime_error("Unable to open the file: "+ file);
    }

    myfile << tiles;
    myfile << "\n";
    myfile << "Finished!";
    myfile.close();
}

void openFileCheck(string file){
    ifstream myfile;
    int maxTime = 10*CLOCKS_PER_SEC; //10s
    clock_t start = clock();
    string line = "";

    do {
        do {
            myfile.open(file);
            if (clock() - start > maxTime) {
                throw runtime_error(
                        "The file has not appeared in 10s. Game is going to end here. File location: " + file);
            }

        } while (!myfile.is_open());


        // get the last line
        while (getline(myfile, line));

        myfile.close();
// if line == Finished! compare will return false (0)
    }while (line.compare("Finished!"));
}

void getButtonsPressed(vector<bool*> pressed){
    string file = "../../AI-SpaceInvaders/Buttons.txt";
    ifstream myfile;
    string line;


    // check if file can be oppened
    openFileCheck(file);

    myfile.open(file);
    for (int i = 0; i < 3; i++) {
        getline(myfile, line);
        try {
            if (stoi(line) == 0) *pressed[i] = false;
            else if (stoi(line) == 1) *pressed[i] = true;
            else throw runtime_error("Invalid boolean" + stoi(line));
        }catch(invalid_argument e){
            cout << "invalid_argument: stoi: no conversion in Line: " << line << endl;
            *pressed[i] = false;
            throw runtime_error("invalid_argument: stoi: no conversion in Line: " + line);
        }


    }

    myfile.close();

    //delete file
    std::remove(file.c_str());
}

int main() {
    //initialize variables
    int gamesPlayed = 0;
    bool aiTraining = false;
    bool showScreen = true;
    bool efficientShooting = true;
    int height = 16;
    int width = 20;
    float fps = 60;         // if FPS is larger the game goes faster
    float clocksPerUpdate;

    // if the program is running for aiTraining, the quicker the better.
    if (aiTraining && !showScreen) {
        fps = CLOCKS_PER_SEC;
    }
    clocksPerUpdate = (float) CLOCKS_PER_SEC / fps;
    Mat tiles;

    while(true) {
        int currentFrame = 0;

        bool gameRunning = true;
        tiles = initializeTiles(height, width);
        Game game = Game(height, width, tiles, efficientShooting);
        clock_t lastFrame = clock();

        while (gameRunning) {
            clock_t now = clock();

            // if statement to limit updates to have the right amount of updates per frame
            if ((now - lastFrame) > clocksPerUpdate) {
                currentFrame++;
                lastFrame = now;

                // initialize variables
                Mat showTiles = tiles;
                vector<bool*> pressed;
                for (int i = 0; i < 3; i++) {
                    pressed.push_back(new bool(false));
                }

                int keyPressed;


                // if the player is real, wait for a keypress and show screen
                if (!aiTraining || showScreen) {
                    scaleUp(showTiles, 20);

                    keyPressed = waitKeyEx(1);

                }
                if (aiTraining) {

                    //write tiles into file
                    writeTiles(tiles);

                    //read buttons to press from file
                    getButtonsPressed(pressed);
                }

                else {
                    // if pressed ESC it closes the program  (ESC = 27 ASCII)
                    if (keyPressed == 27) {
                        return 0;
                    }

                    if (keyPressed == 32) {  // space
                        *pressed[0] = true;
                    } else
                        *pressed[0] = false;


                    if (keyPressed == 63235) {  // right
                        *pressed[1] = true;
                    } else
                        *pressed[1] = false;


                    if (keyPressed == 63234) {  // left
                        *pressed[2] = true;
                    } else
                        *pressed[2] = false;

                }


                //check if buttons were pressed
                game.update(currentFrame, pressed);

                tiles = game.getGrid();


                // if player killed all the enemies or is Game Over: end game
                if (game.getScore() == 108 || game.isGameOver()) {
                    gameRunning = false;
                }
            }
        }


        if (game.isGameOver()) cout << "GAME OVER! Score: " << game.getScore() << endl;
        else cout << "YOU WIN! Score: " << game.getScore() << endl;

        ofstream myfile;
        string file = "../../AI-SpaceInvaders/Score.txt";

        myfile.open(file);
        if (!myfile.is_open()) {
            throw runtime_error("Unable to open the file: " + file);
        }

        myfile << game.getScore();
        myfile << "\n";
        myfile << "Finished!";
        myfile.close();

        gamesPlayed++;
        showScreen = (gamesPlayed %100 == 0);
    }

    return 0;
}