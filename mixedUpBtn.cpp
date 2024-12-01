#include "mixedUpBtn.hpp"
#include "point.hpp"

void mixedUp() {
    if (event.mouseButton.button == sf::Mouse::Left) {
        int x = event.mouseButton.x;
        int y = event.mouseButton.y;
        if (x>=(SQUARE_SIZE*(COLUMN+2))/2-(WIDTH_MIXED_UP_BTN/2) &&
            x<=(SQUARE_SIZE*(COLUMN+2))/2+(WIDTH_MIXED_UP_BTN/2) &&
            y>=SQUARE_SIZE*(ROW+2) &&
            y<=SQUARE_SIZE*(ROW+2)+HEIGHT_MIXED_UP_BTN && second > 5) 
        {
            second-=5;
            score-=5;
            for (int i=1; i<=NUMBER_OF_POKEMON*2; i++) {
                for (int j=0; j<=1; j++) {
                    std::random_device rd;
                    std::mt19937 Row(rd());
                    std::uniform_int_distribution<> distrRow(1, 6);

                    std::random_device cd;
                    std::mt19937 Col(cd());
                    std::uniform_int_distribution<> distrCol(1, 12);

                    messyCouple.push_back({distrCol(Col), distrRow(Row)});
                }
                int temp = BOARD[messyCouple[0].y][messyCouple[0].x];
                BOARD[messyCouple[0].y][messyCouple[0].x] = BOARD[messyCouple[1].y][messyCouple[1].x];
                BOARD[messyCouple[1].y][messyCouple[1].x] = temp;
                messyCouple.clear();
            }
        }
    } 
}

void drawMixedUpBtn() {
    sf::RectangleShape rectangleMixedUp(sf::Vector2f(WIDTH_MIXED_UP_BTN, HEIGHT_MIXED_UP_BTN)); 
    rectangleMixedUp.setPosition((SQUARE_SIZE*(COLUMN+2))/2-(WIDTH_MIXED_UP_BTN/2), SQUARE_SIZE*(ROW+2)); 
    rectangleMixedUp.setFillColor(mixedUpBtnBackground); 
    rectangleMixedUp.setOutlineColor(sf::Color::Black); 
    rectangleMixedUp.setOutlineThickness(1.f); 
    window.draw(rectangleMixedUp); 

    font.loadFromFile("./src/font/arial.ttf");
    sf::Text MixedBtn("Mixed Up", font, 30);
    sf::FloatRect mixedBtnBounds = MixedBtn.getLocalBounds(); 
    MixedBtn.setFillColor(sf::Color::White); 
    float positionX = (SQUARE_SIZE*(COLUMN+2))/2-mixedBtnBounds.width/2;
    float positionY = SQUARE_SIZE*(ROW+2)+HEIGHT_MIXED_UP_BTN/2 - mixedBtnBounds.height/2;
    MixedBtn.setPosition(positionX, positionY);
    window.draw(MixedBtn);
}