#include "returnHomeBtn.hpp"

void drawHomeIcon() {
    sf::Texture homeTexture;
    homeTexture.loadFromFile("./src/image/icons/home.png");
    sf::Sprite homeSprite;
    homeSprite.setTexture(homeTexture);
    homeSprite.setPosition(WIDTH_WINDOW-SQUARE_SIZE, 0);
    sf::Vector2u originalSize = homeTexture.getSize();
    float scaleFactor = SQUARE_SIZE / originalSize.x;
    homeSprite.setScale(scaleFactor, scaleFactor);
    window.draw(homeSprite);
}

void returnHome() {
    if (event.mouseButton.button == sf::Mouse::Left) {
        int x = event.mouseButton.x;
        int y = event.mouseButton.y;
        if (x>=WIDTH_WINDOW-SQUARE_SIZE && x<=WIDTH_WINDOW &&
            y>=0 && y<=SQUARE_SIZE) {
                isPlaying = 0;
                isOnMenuScreen = 1;
        }
    }
}