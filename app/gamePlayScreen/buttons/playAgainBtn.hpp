#ifndef PLAY_AGAIN_BTN 
#define PLAY_AGAIN_BTN

#include "../gamePlay/game.hpp"
#include "../status/point.hpp"

const float WIDTH_PLAY_AGAIN_BTN = SQUARE_SIZE * 4;
const float HEIGHT_PLAY_AGAIN_BTN = SQUARE_SIZE;

float positionX1 = SQUARE_SIZE*(COLUMN+2) + WIDTH_POINT_TABLE/2 - WIDTH_PLAY_AGAIN_BTN/2;
float positionY1 = SQUARE_SIZE*ROW;

void drawPlayAgainBtn();
void playAgain();

#endif