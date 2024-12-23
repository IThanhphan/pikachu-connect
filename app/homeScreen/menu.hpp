#ifndef MENU 
#define MENU

#include "../gamePlayScreen/gamePlay/game.hpp"

const float WIDTH_PLAY_BTN = SQUARE_SIZE*4;
const float HEIGHT_PLAY_BTN = SQUARE_SIZE;
const float WIDTH_HIGH_SCORE_BTN = WIDTH_PLAY_BTN;
const float HEIGHT_HIGH_SCORE_BTN = HEIGHT_PLAY_BTN;
const float WIDTH_HIGH_SCORE_BOARD = SQUARE_SIZE*6;
const float HEIGHT_HIGH_SCORE_BOARD = WIDTH_HIGH_SCORE_BOARD;

float positionXBoard = WIDTH_WINDOW/2 - WIDTH_HIGH_SCORE_BOARD/2;
float positionYBoard = HEIGHT_WINDOW/2 - HEIGHT_HIGH_SCORE_BOARD/2;

int isOnMenuScreen = 1;
int isShowHighScore = 0;

sf::Texture backgroundMenuTexture;  
sf::Sprite backgroundMenuSprite;

void drawPlayBtn();
void drawHighScoreBtn();
void drawHighScoreBoard();
void play();
void showHighScore();

#endif