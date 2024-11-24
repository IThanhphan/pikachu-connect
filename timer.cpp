#include "timer.h"

void countdown(int seconds) {
    while (seconds > 0 && runningTimer) {
        int minutes = seconds / 60;
        int secs = seconds % 60;

        timeStr = (minutes < 10 ? "0" : "")+std::to_string(minutes)+":"+(secs < 10 ? "0" : "")+std::to_string(secs);

        std::this_thread::sleep_for(std::chrono::seconds(1));
        seconds--;
        second--;
    }
    if (runningTimer) {
        resultText = "You Lose!!!";
        isLose = 1;
        timeStr = "Time's up!";
    } 
}


void timer() {
    sf::RectangleShape rectangleTimer(sf::Vector2f(WIDTH_RECTANGLE_TIMER, HEIGHT_RECTANGLE_TIMER));
    rectangleTimer.setPosition(SQUARE_SIZE, HEIGHT_WINDOW - 2 * SQUARE_SIZE); 
    rectangleTimer.setFillColor(sf::Color::Transparent);
    rectangleTimer.setOutlineColor(sf::Color::Black);
    rectangleTimer.setOutlineThickness(1.f);
    window.draw(rectangleTimer);

    double dt = second/timeLimit;
    sf::RectangleShape rectangleCountDown(sf::Vector2f(widthRectangleCountDown*dt, heightRectangleCountDown));
    rectangleCountDown.setPosition(SQUARE_SIZE, HEIGHT_WINDOW - 2 * SQUARE_SIZE); 
    rectangleCountDown.setFillColor(sf::Color::Red);
    window.draw(rectangleCountDown);

    sf::Font font;
    int FontSize = 30;
    font.loadFromFile("./src/font/arial.ttf");
    sf::Text Time(timeStr, font, FontSize);
    sf::FloatRect timeBounds = Time.getLocalBounds();
    Time.setFillColor(sf::Color::White);
    Time.setPosition(WIDTH_WINDOW/2 - timeBounds.width/2, HEIGHT_WINDOW - (3*SQUARE_SIZE)/2 - timeBounds.height);
    window.draw(Time);
}