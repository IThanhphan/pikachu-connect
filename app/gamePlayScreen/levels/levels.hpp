#ifndef LEVELS 
#define LEVELS

#include "../gamePlay/game.hpp"

const int NUMBER_OF_LEVEL = 5;
const float SIZE_LEVEL_REC = SQUARE_SIZE*4;

int levelOnOff = 0;
int levelSelected = 1;

int levelPassed[NUMBER_OF_LEVEL] = {1, 0, 0, 0, 0}; 

sf::Color notPassColor(192, 192, 192);

sf::RectangleShape blackOverlay(sf::Vector2f(WIDTH_WINDOW, HEIGHT_WINDOW));

void drawBarsIcon();
void drawLevels();
void drawCurrentLevel();
void selectLevelBtn();
void selectLevel();
void level2();
void level3();
void level4();
void level5();

#endif