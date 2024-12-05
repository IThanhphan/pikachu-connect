#include "menu.hpp"

void drawPlayBtn() {
    sf::RectangleShape rectanglePlayBtn(sf::Vector2f(WIDTH_PLAY_BTN, HEIGHT_PLAY_BTN)); 
    rectanglePlayBtn.setPosition(SQUARE_SIZE, SQUARE_SIZE*(ROW+2)); 
    rectanglePlayBtn.setFillColor(sf::Color::White); 
    rectanglePlayBtn.setOutlineColor(sf::Color::Black); 
    rectanglePlayBtn.setOutlineThickness(1.f); 
    window.draw(rectanglePlayBtn); 

    font.loadFromFile("./src/font/arial.ttf");
    sf::Text playBtn("Play", font, 45);
    sf::FloatRect playBtnBounds = playBtn.getLocalBounds(); 
    playBtn.setFillColor(sf::Color::Black); 
    float positionX = SQUARE_SIZE + WIDTH_PLAY_BTN/2 - playBtnBounds.width/2;
    float positionY = SQUARE_SIZE*(ROW+2) + HEIGHT_PLAY_BTN/2 - playBtnBounds.height/2;
    playBtn.setPosition(positionX, positionY);
    window.draw(playBtn);
}

void play() {
    if (event.mouseButton.button == sf::Mouse::Left) {
        int x = event.mouseButton.x;
        int y = event.mouseButton.y;
        if (x>=SQUARE_SIZE && x<=SQUARE_SIZE+WIDTH_PLAY_BTN &&
            y>=SQUARE_SIZE*(ROW+2) && y<=SQUARE_SIZE*(ROW+2)+HEIGHT_PLAY_BTN) {
                reset();
                isPlaying = 1;
                isOnMenuScreen = 0;
        }
    }
}