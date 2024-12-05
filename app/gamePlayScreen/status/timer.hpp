#ifndef TIMER
#define TIMER

#include "../gamePlay/game.hpp"

const float WIDTH_RECTANGLE_TIMER = WIDTH_WINDOW - 2 * SQUARE_SIZE; //chiều rộng thanh thời gian
const float HEIGHT_RECTANGLE_TIMER = SQUARE_SIZE; //chiều cao thanh thời gian

float timeLimit = 180; //thời gian giới hạn
float second = timeLimit; //thời gian đếm ngươc
float widthRectangleCountDown = WIDTH_RECTANGLE_TIMER; //chiều rông thanh thời gian đếm ngược
float heightRectangleCountDown = HEIGHT_RECTANGLE_TIMER; //chiều cao thanh thời gian đếm ngược

int isCountDown = 1;

std::string timeStr; //chuỗi hiển thị thời gian ra màn hình

std::atomic<bool> runningTimer(true); // Biến toàn cục để kiểm soát trạng thái của đồng hồ đếm ngược

void countdown(int seconds); //hàm đếm ngược
void drawTimer(); //hàm vẽ thanh thời gian đếm ngược

#endif