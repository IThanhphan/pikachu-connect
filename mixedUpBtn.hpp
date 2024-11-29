#ifndef MIXED_UP 
#define MIXED_UP

#include "game.hpp"

const float WIDTH_MIXED_UP_BTN = 200; //Chiều rộng nút làm xáo trộn các pokemon
const float HEIGHT_MIXED_UP_BTN = 70; //Chiều cao nút làm xáo trộn các pokemon

std::vector<Direction> messyCouple; //cặp làm xáo trộn các pokemon

sf::Color mixedUpBtnBackground(201, 171, 125); //màu nút làm xáo trộn

void mixedUp(); //hàm làm xáo trộn các pokemon
void drawMixedUpBtn(); //vẽ nút làm xáo trộn các pokemon

#endif