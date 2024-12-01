#include "levels.hpp"

void drawBarsIcon() {
    sf::Texture barsTexture;
    barsTexture.loadFromFile("./src/image/icons/bars.jpg");
    sf::Sprite barsSprite;
    barsSprite.setTexture(barsTexture);
    barsSprite.setPosition(0, 0);
    sf::Vector2u originalSize = barsTexture.getSize();
    float scaleFactor = SQUARE_SIZE / originalSize.x;
    barsSprite.setScale(scaleFactor, scaleFactor);
    window.draw(barsSprite);
}

void drawLevels() {
    for (int i=1; i<=NUMBER_OF_LEVEL; i++) {
        sf::RectangleShape rectangleLevel(sf::Vector2f(SIZE_LEVEL_REC, SIZE_LEVEL_REC));
        float positionX1 = (i-1)*(WIDTH_WINDOW/NUMBER_OF_LEVEL) + (WIDTH_WINDOW/NUMBER_OF_LEVEL - SIZE_LEVEL_REC)/2;
        float positionY1 = HEIGHT_WINDOW/2 - SIZE_LEVEL_REC/2;
        rectangleLevel.setPosition(positionX1, positionY1);
        if (levelPassed[i-1]) {
            rectangleLevel.setFillColor(sf::Color::White);
        } else {
            rectangleLevel.setFillColor(notPassColor);
        }
        rectangleLevel.setOutlineColor(sf::Color::Black);
        rectangleLevel.setOutlineThickness(1.f);
        window.draw(rectangleLevel);

        font.loadFromFile("./src/font/arial.ttf");
        sf::Text level("level " + std::to_string(i), font, 30);
        sf::FloatRect levelBounds = level.getLocalBounds();
        level.setFillColor(sf::Color::Black);
        float positionX2 = (i-1)*(WIDTH_WINDOW/NUMBER_OF_LEVEL)+(WIDTH_WINDOW/NUMBER_OF_LEVEL-levelBounds.width)/2;
        float positionY2 = HEIGHT_WINDOW/2 - levelBounds.height/2;
        level.setPosition(positionX2, positionY2);
        window.draw(level);
    }
}

void drawCurrentLevel() {
    font.loadFromFile("./src/font/arial.ttf");
    sf::Text currentLevel("level " + std::to_string(levelSelected), font, 40);
    sf::FloatRect currentLevelBounds = currentLevel.getLocalBounds();
    currentLevel.setFillColor(sf::Color::Black);
    float positionX = WIDTH_WINDOW/2 - currentLevelBounds.width/2;
    float positionY = HEIGHT_WINDOW - SQUARE_SIZE + currentLevelBounds.height/2;
    currentLevel.setPosition(positionX, positionY);
    window.draw(currentLevel);
}

void selectLevelBtn() {
    if (event.mouseButton.button == sf::Mouse::Left) {
        int x = event.mouseButton.x;
        int y = event.mouseButton.y;
        if (x>=0 && x<=SQUARE_SIZE &&
            y>=0 && y<=SQUARE_SIZE) {
            if (!levelOnOff) {
                levelOnOff = 1;
            } else {
                levelOnOff = 0;
            }
        }
    } 
}

void selectLevel() {
    if (event.mouseButton.button == sf::Mouse::Left) {
        int x = event.mouseButton.x;
        int y = event.mouseButton.y;
        for (int i=0; i<NUMBER_OF_LEVEL; i++) {
            if (x>=i*(WIDTH_WINDOW/NUMBER_OF_LEVEL)+(WIDTH_WINDOW/NUMBER_OF_LEVEL-SIZE_LEVEL_REC)/2 &&
                x<=i*(WIDTH_WINDOW/NUMBER_OF_LEVEL)+(WIDTH_WINDOW/NUMBER_OF_LEVEL-SIZE_LEVEL_REC)/2+SIZE_LEVEL_REC
                && y>=HEIGHT_WINDOW/2 - SIZE_LEVEL_REC/2 &&
                y<=HEIGHT_WINDOW/2 + SIZE_LEVEL_REC/2 && levelPassed[i]) {
                    reset();
                    levelSelected = i+1;
                    levelOnOff = 0;
            }
        }
    }
}

void level2() {
    for (int i=1; i<=COLUMN; i++) {
        for (int j=ROW-1; j>=1; j--) {
            if (BOARD[j][i] && !BOARD[j+1][i]) {
                int temp = BOARD[j][i];
                BOARD[j][i] = BOARD[j+1][i];
                BOARD[j+1][i] = temp;
                j++;
            }
        }
    }
}

void level3() {
    for (int i=1; i<=COLUMN; i++) {
        for (int j=2; j<=ROW; j++) {
            if (BOARD[j][i] && !BOARD[j-1][i]) {
                int temp = BOARD[j][i];
                BOARD[j][i] = BOARD[j-1][i];
                BOARD[j-1][i] = temp;
                j--;              
            }
        }
    }
}

void level4() {
    for (int i=1; i<=ROW; i++) {
        for (int j=2; j<=COLUMN; j++) {
            if (BOARD[i][j] && !BOARD[i][j-1]) {
                int temp = BOARD[i][j];
                BOARD[i][j] = BOARD[i][j-1];
                BOARD[i][j-1] = temp;
                j--; 
            }
        }
    }
}

void level5() {
    for (int i=i; i<=ROW; i++) {
        for (int j=COLUMN-1; j>=1; j--) {
            if (BOARD[i][j] && !BOARD[i][j+1]) {
                int temp = BOARD[i][j];
                BOARD[i][j] = BOARD[i][j+1];
                BOARD[i][j+1] = temp;
                j++; 
            }
        }
    }
}