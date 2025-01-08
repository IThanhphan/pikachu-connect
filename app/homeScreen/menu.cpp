#include "menu.hpp"

void drawPlayBtn() {
    sf::RectangleShape rectanglePlayBtn(sf::Vector2f(WIDTH_PLAY_BTN, HEIGHT_PLAY_BTN)); 
    rectanglePlayBtn.setPosition(SQUARE_SIZE, SQUARE_SIZE*ROW); 
    rectanglePlayBtn.setFillColor(sf::Color::White); 
    rectanglePlayBtn.setOutlineColor(sf::Color::Black); 
    rectanglePlayBtn.setOutlineThickness(1.f); 
    window.draw(rectanglePlayBtn); 

    font.loadFromFile("./src/font/arial.ttf");
    sf::Text playBtn("Play", font, 40);
    sf::FloatRect playBtnBounds = playBtn.getLocalBounds(); 
    playBtn.setFillColor(sf::Color::Black); 
    float positionX = SQUARE_SIZE + WIDTH_PLAY_BTN/2 - playBtnBounds.width/2;
    float positionY = SQUARE_SIZE*ROW + HEIGHT_PLAY_BTN/2 - playBtnBounds.height/2 - 10;
    playBtn.setPosition(positionX, positionY);
    window.draw(playBtn);
}

void drawHighScoreBtn() {
    sf::RectangleShape rectangleHighScoreBtn(sf::Vector2f(WIDTH_PLAY_BTN, HEIGHT_PLAY_BTN)); 
    rectangleHighScoreBtn.setPosition(SQUARE_SIZE, SQUARE_SIZE*(ROW+2)); 
    rectangleHighScoreBtn.setFillColor(sf::Color::White); 
    rectangleHighScoreBtn.setOutlineColor(sf::Color::Black); 
    rectangleHighScoreBtn.setOutlineThickness(1.f); 
    window.draw(rectangleHighScoreBtn); 

    font.loadFromFile("./src/font/arial.ttf");
    sf::Text highScoreBtn("High Score", font, 40);
    sf::FloatRect highScoreBtnBounds = highScoreBtn.getLocalBounds(); 
    highScoreBtn.setFillColor(sf::Color::Black); 
    float positionX = SQUARE_SIZE + WIDTH_PLAY_BTN/2 - highScoreBtnBounds.width/2;
    float positionY = SQUARE_SIZE*(ROW+2) + HEIGHT_PLAY_BTN/2 - highScoreBtnBounds.height/2 - 10;
    highScoreBtn.setPosition(positionX, positionY);
    window.draw(highScoreBtn);
}

void drawHighScoreBoard() {
    font.loadFromFile("./src/font/arial.ttf");
    sf::Text highScore("High Score", font, 60);
    sf::FloatRect highScoreBounds = highScore.getLocalBounds(); 
    highScore.setFillColor(sf::Color::Red); 
    highScore.setStyle(sf::Text::Bold);
    float positionX = WIDTH_WINDOW/2 - highScoreBounds.width/2;
    float positionY = SQUARE_SIZE;
    highScore.setPosition(positionX, positionY);
    window.draw(highScore);

    sf::RectangleShape rectangleHighScoreBoard(sf::Vector2f(WIDTH_HIGH_SCORE_BOARD, HEIGHT_HIGH_SCORE_BOARD)); 
    rectangleHighScoreBoard.setPosition(positionXBoard, positionYBoard); 
    rectangleHighScoreBoard.setFillColor(sf::Color::White); 
    rectangleHighScoreBoard.setOutlineColor(sf::Color::Black); 
    rectangleHighScoreBoard.setOutlineThickness(1.f); 
    window.draw(rectangleHighScoreBoard); 

    for (int i=0; i<levels.size(); i++) {
        font.loadFromFile("./src/font/arial.ttf");
        sf::Text eachHighScore(levels[i] + " " + std::to_string(highScores[i]), font, 40);
        sf::FloatRect eachHighScoreBounds = eachHighScore.getLocalBounds(); 
        eachHighScore.setFillColor(sf::Color::Black); 
        float positionXLevel = positionXBoard + SQUARE_SIZE;
        float positionYLevel = positionYBoard + SQUARE_SIZE*i + eachHighScoreBounds.height;
        eachHighScore.setPosition(positionXLevel, positionYLevel);
        window.draw(eachHighScore);
    }
}

void play() {
    if (event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f worldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
        int x = worldPos.x;
        int y = worldPos.y;
        if (x>=SQUARE_SIZE && x<=SQUARE_SIZE+WIDTH_PLAY_BTN &&
            y>=SQUARE_SIZE*ROW && y<=SQUARE_SIZE*ROW+HEIGHT_PLAY_BTN) {
            reset();
            isPlaying = 1;
            isOnMenuScreen = 0;
        }
    }
}

void showHighScore() {
    if (event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f worldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
        int x = worldPos.x;
        int y = worldPos.y;
        if (isShowHighScore==1 && ((x<positionXBoard || x>positionXBoard+WIDTH_HIGH_SCORE_BOARD) ||
            (y<positionYBoard || y>positionYBoard+HEIGHT_HIGH_SCORE_BOARD))) {
            isShowHighScore = 0;
            backgroundMenuSprite.setColor(sf::Color(255, 255, 255, 255));
        }
        if (x>=SQUARE_SIZE && x<=SQUARE_SIZE+WIDTH_PLAY_BTN &&
            y>=SQUARE_SIZE*(ROW+2) && y<=SQUARE_SIZE*(ROW+2)+HEIGHT_PLAY_BTN) {
            isShowHighScore = 1;
            backgroundMenuSprite.setColor(sf::Color(255, 255, 255, 128));
        }
    }
}