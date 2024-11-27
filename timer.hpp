#ifndef TIMER
#define TIMER

#include "main.hpp"
const int WIDTH_RECTANGLE_TIMER = WIDTH_WINDOW - 2 * SQUARE_SIZE; //chiều rộng thanh thời gian
const int HEIGHT_RECTANGLE_TIMER = SQUARE_SIZE; //chiều cao thanh thời gian

double timeLimit = 180; //thời gian giới hạn
double second = timeLimit; //thời gian đếm ngươc
double widthRectangleCountDown = WIDTH_RECTANGLE_TIMER; //chiều rông thanh thời gian đếm ngược
double heightRectangleCountDown = HEIGHT_RECTANGLE_TIMER; //chiều cao thanh thời gian đếm ngược

std::string timeStr; //chuỗi hiển thị thời gian ra màn hình

std::atomic<bool> runningTimer(true); // Biến toàn cục để kiểm soát trạng thái của đồng hồ đếm ngược

void countdown(int seconds); //hàm đếm ngược
void drawTimer(); //hàm vẽ thanh thời gian đếm ngược

#endif