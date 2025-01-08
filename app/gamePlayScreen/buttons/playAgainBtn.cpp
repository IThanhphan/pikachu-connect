#include "playAgainBtn.hpp"

void drawPlayAgainBtn() {
    sf::RectangleShape playAgainBtn(sf::Vector2f(WIDTH_PLAY_AGAIN_BTN, HEIGHT_PLAY_AGAIN_BTN));
    playAgainBtn.setPosition(positionX1, positionY1); 
    playAgainBtn.setFillColor(sf::Color::White);
    playAgainBtn.setOutlineColor(sf::Color::Black);
    playAgainBtn.setOutlineThickness(1.f);
    window.draw(playAgainBtn);

    font.loadFromFile("./src/font/arial.ttf");
    sf::Text playAgain("Play Again", font, 30);
    sf::FloatRect playAgainBounds = playAgain.getLocalBounds();
    playAgain.setFillColor(sf::Color::Black);
    float positionX2 = positionX1 + WIDTH_PLAY_AGAIN_BTN/2 - playAgainBounds.width/2;
    float positionY2 = positionY1 + HEIGHT_PLAY_AGAIN_BTN/2 - playAgainBounds.height/2;
    playAgain.setPosition(positionX2, positionY2);
    window.draw(playAgain);
}

void playAgain() {
    if (event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f worldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
        int x = worldPos.x;
        int y = worldPos.y;
        if (x>=positionX1 && x<=positionX1+WIDTH_PLAY_AGAIN_BTN &&
            y>=positionY1 && y<=positionY1+HEIGHT_PLAY_AGAIN_BTN) {
            reset();
        }
    } 
}