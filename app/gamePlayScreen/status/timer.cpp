#include "timer.hpp"
#include "point.hpp"
#include "../levels/levels.hpp"

void countdown(int seconds) {
    while (isCountDown) {
        seconds = second;
        while (seconds > 0 && runningTimer) {
            isEnd = 0;
            seconds = second;
            int minutes = seconds / 60;
            int secs = seconds % 60;
            // In định dạng mm:ss
            timeStr = (minutes < 10 ? "0" : "")+std::to_string(minutes)+":"+(secs < 10 ? "0" : "")+std::to_string(secs);
            //ngưng luồng hoạt động của thời gian 1 giây
            std::this_thread::sleep_for(std::chrono::seconds(1));
            seconds--;
            second--; //biến toàn cục để cập nhật lại thời gian in ra màn hình
        }
        if (runningTimer && !isEnd) {
            Node *root = build(0, v.size() - 1);
            Node *result = search(root, score);
            if (result != NULL) {
                resultText = "You Found!!!";
                levelPassed[levelSelected] = 1;
                if (score + (int)second > highScores[levelSelected-1]) newHighScore = 1;
                highScores[levelSelected-1] = newHighScore ? score + (int)second : highScores[levelSelected-1];
            } else {
                resultText = "You Lose!!!"; //in ra màn hình You Lose!!! 
            }
            timeStr = "Time's up!"; //in ra màn hình Time's up!
        }      
        isEnd=1;
    }
    
}


void drawTimer() {
    sf::RectangleShape rectangleTimer(sf::Vector2f(WIDTH_RECTANGLE_TIMER, HEIGHT_RECTANGLE_TIMER)); 
    rectangleTimer.setPosition(SQUARE_SIZE, HEIGHT_WINDOW - 2 * SQUARE_SIZE); 
    rectangleTimer.setFillColor(sf::Color::Transparent); 
    rectangleTimer.setOutlineColor(sf::Color::Black); 
    rectangleTimer.setOutlineThickness(1.f); 
    window.draw(rectangleTimer); 

    float dt = second/timeLimit; 
    sf::RectangleShape rectangleCountDown(sf::Vector2f(widthRectangleCountDown*dt, heightRectangleCountDown)); 
    rectangleCountDown.setPosition(SQUARE_SIZE, HEIGHT_WINDOW - 2 * SQUARE_SIZE); 
    rectangleCountDown.setFillColor(sf::Color::Red);
    window.draw(rectangleCountDown);

    font.loadFromFile("./src/font/arial.ttf");
    sf::Text Time(timeStr, font, 30);
    sf::FloatRect timeBounds = Time.getLocalBounds(); 
    Time.setFillColor(sf::Color::White); 
    Time.setPosition(WIDTH_WINDOW/2 - timeBounds.width/2, HEIGHT_WINDOW - (3*SQUARE_SIZE)/2 - timeBounds.height);
    window.draw(Time);
}