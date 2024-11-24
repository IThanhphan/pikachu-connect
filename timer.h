#ifndef TIMER
#define TIMER

#include "main.h"
const int WIDTH_RECTANGLE_TIMER = WIDTH_WINDOW - 2 * SQUARE_SIZE;
const int HEIGHT_RECTANGLE_TIMER = SQUARE_SIZE;

double timeLimit = 180;
double second = timeLimit;
double widthRectangleCountDown = WIDTH_RECTANGLE_TIMER;
double heightRectangleCountDown = HEIGHT_RECTANGLE_TIMER;

std::string timeStr;

void countdown(int seconds);
void timer();

#endif