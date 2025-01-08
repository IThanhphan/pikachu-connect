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
        sf::Vector2f worldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
        int x = worldPos.x;
        int y = worldPos.y;
        if (x>=WIDTH_WINDOW-SQUARE_SIZE && x<=WIDTH_WINDOW &&
            y>=0 && y<=SQUARE_SIZE) {
                isPlaying = 0;
                isOnMenuScreen = 1;
        }
    }
}