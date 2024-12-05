#ifndef MENU 
#define MENU

#include "../gamePlayScreen/gamePlay/game.hpp"

const float WIDTH_PLAY_BTN = SQUARE_SIZE*4;
const float HEIGHT_PLAY_BTN = SQUARE_SIZE;

int isOnMenuScreen = 1;

sf::Texture backgroundMenuTexture;  
sf::Sprite backgroundMenuSprite;

void drawPlayBtn();
void play();

#endif