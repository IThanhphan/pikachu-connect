#include "game.hpp"
#include "timer.cpp"
#include "mixedUpBtn.cpp"
#include "point.cpp"
#include "levels.cpp"

void generateRandomPokemon() {
    std::random_device rd; 
    std::mt19937 genRow(rd()); 
    std::uniform_int_distribution<> distrRow(1, 6);

    std::random_device cd; 
    std::mt19937 genCol(cd()); 
    std::uniform_int_distribution<> distrCol(1, 12);

    for (int i=1; i<=NUMBER_OF_POKEMON; i++) {
        for (int j=1; j<=NUMBER_OF_EACH_POKEMON; j++) {
            int randomRow;
            int randomCol;
            do {
                randomRow = distrRow(genRow);
                randomCol = distrCol(genCol);
            } while (BOARD[randomRow][randomCol] != 0);
            BOARD[randomRow][randomCol] = i;
        }
    }
}

void generateBoard() {
    for (int i=1; i<=ROW; i++) {
        for (int j=1; j<=COLUMN; j++) {
            if (BOARD[i][j]) {
                sf::RectangleShape rectangle(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE)); 
                rectangle.setPosition(SQUARE_SIZE*j, SQUARE_SIZE*i); 
                rectangle.setFillColor(pokemonBackground);
                rectangle.setOutlineColor(sf::Color::Black);
                rectangle.setOutlineThickness(1.f);
                window.draw(rectangle);

                sf::Texture pokemonTexture;
                pokemonTexture.loadFromFile(POKEMONS[BOARD[i][j]]);
                sf::Sprite pokemonSprite;
                pokemonSprite.setTexture(pokemonTexture);
                pokemonSprite.setPosition(SQUARE_SIZE*j, SQUARE_SIZE*i);
                sf::Vector2u originalSize = pokemonTexture.getSize();
                float scaleFactor = SQUARE_SIZE / originalSize.x;
                pokemonSprite.setScale(scaleFactor, scaleFactor);
                window.draw(pokemonSprite);  
            }
        }
    }
}

void play() {
    if (event.mouseButton.button == sf::Mouse::Left) {
        int x = event.mouseButton.x;
        int y = event.mouseButton.y;
        for (int i=1; i<=ROW; i++) {
            for (int j=1; j<=COLUMN; j++) {
                if (x>=SQUARE_SIZE*j && x<=(SQUARE_SIZE*j)+SQUARE_SIZE && 
                    y>=SQUARE_SIZE*i && y<=(SQUARE_SIZE*i)+SQUARE_SIZE) {  
                    if (startFlat && !endFlat) {
                        rectangleOutLineStart.setPosition(SQUARE_SIZE*j, SQUARE_SIZE*i); 
                        rectangleOutLineStart.setFillColor(sf::Color::Transparent);
                        rectangleOutLineStart.setOutlineColor(sf::Color::Red);
                        rectangleOutLineStart.setOutlineThickness(3.f);  
                        couple[0] = BOARD[i][j];
                        start.x = j;
                        start.y = i;
                        startFlat = 0;
                        endFlat = 1;
                    } else if (endFlat && !startFlat) {
                        rectangleOutLineEnd.setPosition(SQUARE_SIZE*j, SQUARE_SIZE*i); 
                        rectangleOutLineEnd.setFillColor(sf::Color::Transparent);
                        rectangleOutLineEnd.setOutlineColor(sf::Color::Red);
                        rectangleOutLineEnd.setOutlineThickness(3.f);
                        couple[1] = BOARD[i][j]; 
                        end.x = j;
                        end.y = i;
                        startFlat = 1;
                        endFlat = 0;
                    }             
                }
            }
        }
    }
}

void determineDirection(int a, int b) {
    if (a==-1 && b==0) {
        directionLine = 1;
    } else if (a==0 && b==-1) {
        directionLine = 2;
    } else if (a==1 && b==0) {
        directionLine = 3;
    } else if (a==0 && b==1) {
        directionLine = 4;
    }
}

void makeLine(int x, int y) {
    if (!endSearch && x>=0 && x<COLUMN+2 && y>=0 && y<ROW+2 && 
        (BOARD[y][x]==0 || (x==end.x && y==end.y) || (x==start.x && y==start.y))) {
        for (int i=0; i<lines.size(); i++) {
            if (x == lines[i].x && y == lines[i].y) {
                return;
            }
        }
        lines.push_back({x, y});
        if (lines.size() >= 2) {
            preDirectionLine = directionLine;
            determineDirection(lines.back().x-lines[lines.size()-2].x, lines.back().y-lines[lines.size()-2].y);

            if (directionLine != preDirectionLine && preDirectionLine && abs(directionLine-preDirectionLine)%2!=0) {
                corners.push_back({lines[lines.size()-2].x, lines[lines.size()-2].y});  
            }
            if (corners.size() > 2) {  
                corners.pop_back();
                lines.pop_back();
                return;
            }
        }
        if (x == end.x && y == end.y && corners.size() <= 2) {
            endSearch = 1;
            return;
        }
        int dx = end.x - x;
        int dy = end.y - y;
        if ((dx>0 && dy>0) || (dx==0 && dy>0)) {
            makeLine(x, y+1); //xuống
            makeLine(x+1, y); //phải
            makeLine(x, y-1); //lên
            makeLine(x-1, y); //trái
        } else if ((dx>0 && dy<0) || (dx>0 && dy==0)) {
            makeLine(x+1, y); //phải
            makeLine(x, y-1); //lên
            makeLine(x-1, y); //trái
            makeLine(x, y+1); //xuống
        } else if ((dx<0 && dy<0) || (dx==0 && dy<0)) {
            makeLine(x, y-1); //lên
            makeLine(x-1, y); //trái
            makeLine(x, y+1); //xuống
            makeLine(x+1, y); //phải
        } else if ((dx<0 && dy>0) || (dx<0 && dy==0)) {
            makeLine(x-1, y); //trái
            makeLine(x, y+1); //xuống
            makeLine(x+1, y); //phải
            makeLine(x, y-1); //lên
        }
        if (!endSearch) {
            if (!lines.empty()) {
                lines.pop_back();
                if (!corners.empty()) {
                    if (corners.back().x == lines.back().x && corners.back().y == lines.back().y) {
                        corners.pop_back();
                    }
                }
                if (lines.size() >= 2) {
                    determineDirection(lines.back().x-lines[lines.size()-2].x, lines.back().y-lines[lines.size()-2].y);
                } else {
                    directionLine = 0;
                }
            }
        }
    }
}

void drawLine() {
    for (int i=0; i<lines.size()-1; i++) {
        int xStart = SQUARE_SIZE*lines[i].x + SQUARE_SIZE/2;
        int yStart = SQUARE_SIZE*lines[i].y + SQUARE_SIZE/2;
        int xEnd = SQUARE_SIZE*lines[i+1].x + SQUARE_SIZE/2;
        int yEnd = SQUARE_SIZE*lines[i+1].y + SQUARE_SIZE/2;
        line.append(sf::Vertex(sf::Vector2f(xStart, yStart), sf::Color::Red)); 
        line.append(sf::Vertex(sf::Vector2f(xEnd, yEnd), sf::Color::Red));
    }
    haveLine = 1;
}

bool isWin() {
    for (int i=1; i<=ROW; i++) {
        for (int j=1; j<=COLUMN; j++) {
            if (BOARD[i][j]) {
                return false;
            }
        }
    }
    resultText = "You Win!!!";
    runningTimer = false;
    isEnd = 1;
    levelPassed[levelSelected] = 1;
    return true;
}

void drawResultTable(std::string result) {
    sf::RectangleShape resultTable(sf::Vector2f(WIDTH_RESULT_TABLE, HEIGHT_RESULT_TABLE));
    resultTable.setPosition(WIDTH_WINDOW/2 - WIDTH_RESULT_TABLE/2, HEIGHT_WINDOW/2 - HEIGHT_RESULT_TABLE/2); 
    resultTable.setFillColor(sf::Color::White);
    resultTable.setOutlineColor(sf::Color::Black);
    resultTable.setOutlineThickness(1.f);
    window.draw(resultTable);

    font.loadFromFile("./src/font/arial.ttf");
    sf::Text Result(result, font, 50);
    sf::FloatRect resultBounds = Result.getLocalBounds();
    Result.setFillColor(sf::Color::Black);
    Result.setPosition(WIDTH_WINDOW/2 - resultBounds.width/2, HEIGHT_WINDOW/2 - 3*resultBounds.height);
    window.draw(Result);

    sf::Text ResultPoint("Your point: " + std::to_string(score + (int)second), font, 40);
    sf::FloatRect ResultPointBounds = ResultPoint.getLocalBounds();
    ResultPoint.setFillColor(sf::Color::Black);
    ResultPoint.setPosition(WIDTH_WINDOW/2 - ResultPointBounds.width/2, HEIGHT_WINDOW/2-ResultPointBounds.height/2);
    window.draw(ResultPoint);

    std::string nextOrAgain;
    if (levelPassed[levelSelected-1] && levelSelected!=NUMBER_OF_LEVEL && levelPassed[levelSelected]) {
        nextOrAgain = "Next level";
    } else {
        nextOrAgain = "Play again";
    }
    sf::Text plg(nextOrAgain, font, 40);
    sf::FloatRect plgBounds = plg.getLocalBounds();
    plg.setFillColor(sf::Color::Red);
    plgPosX = WIDTH_WINDOW/2 - plgBounds.width/2;
    plgPosY = HEIGHT_WINDOW/2 + 2*plgBounds.height;
    widthPlg = plgBounds.width;
    heightPlg = plgBounds.height;
    plg.setPosition(plgPosX, plgPosY);
    window.draw(plg);
}

void reset() {
    for (int i=0; i<ROW+2; i++) {
        for (int j=0; j<COLUMN+2; j++) {
            BOARD[i][j] = 0;
        }
    }
    generateRandomPokemon();
    isEnd = 0;
    score = 0;
    second = timeLimit;
    runningTimer = true;
}

void playAgainOrNext() {
    if (event.mouseButton.button == sf::Mouse::Left) {
        int x = event.mouseButton.x;
        int y = event.mouseButton.y;
        if (x>=plgPosX && x<=plgPosX+widthPlg &&
            y>=plgPosY && y<=plgPosY+heightPlg) {
            reset();
            if (levelPassed[levelSelected-1] && levelSelected!=NUMBER_OF_LEVEL && levelPassed[levelSelected]) {
                levelSelected++;
            }
        }
    } 
}