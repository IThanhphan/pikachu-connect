#include <SFML/Graphics.hpp>
#include <string>
#include <random>
#include <iostream>
#include <stack>
#include <vector>
#include <queue>
#include <cmath>
#include <thread>
#include <chrono>
#include <atomic>

const int WIDTH_WINDOW = 1400;
const int HEIGHT_WINDOW = 700;
const int ROW = 6;
const int COLUMN = 12;
const int NUMBER_OF_POKEMON = 18;
const int NUMBER_OF_EACH_POKEMON = 4;
const int DELAY_TIME_LINE = 20;
const int SQUARE_SIZE = 60.f;
const int WIDTH_RECTANGLE_TIMER = WIDTH_WINDOW - 2 * SQUARE_SIZE;
const int HEIGHT_RECTANGLE_TIMER = SQUARE_SIZE;
const std::string POKEMONS[NUMBER_OF_POKEMON+1] = {
    "",
    "./src/image/pokemons/1.png",
    "./src/image/pokemons/4.png",
    "./src/image/pokemons/7.png",
    "./src/image/pokemons/8.png",
    "./src/image/pokemons/10.png",
    "./src/image/pokemons/21.png",
    "./src/image/pokemons/25.png",
    "./src/image/pokemons/29.png",
    "./src/image/pokemons/39.png",
    "./src/image/pokemons/50.png",
    "./src/image/pokemons/52.png",
    "./src/image/pokemons/54.png",
    "./src/image/pokemons/94.png",
    "./src/image/pokemons/133.png",
    "./src/image/pokemons/137.png",
    "./src/image/pokemons/150.png",
    "./src/image/pokemons/156.png",
    "./src/image/pokemons/448.png"
};

int BOARD[ROW+2][COLUMN+2] = {};
int couple[2] = {0, 0};
int startFlat = 1;
int endFlat = 0;
int haveLine = 0;
int delay = 0;
int endSearch = 0;
int directionLine = 0;
int preDirectionLine = 0;

double timeLimit = 180;
double second = timeLimit;
double widthRectangleCountDown = WIDTH_RECTANGLE_TIMER;
double heightRectangleCountDown = HEIGHT_RECTANGLE_TIMER;

std::string timeStr;

struct Direction {
    int x, y;
};

Direction start;
Direction end;

sf::RenderWindow window(sf::VideoMode(WIDTH_WINDOW, HEIGHT_WINDOW), "PIKACHU");
sf::RectangleShape rectangleOutLineStart(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
sf::RectangleShape rectangleOutLineEnd(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
sf::Color pokemonBackground(255, 218, 251); 
sf::VertexArray line(sf::Lines);
sf::Texture backgroundTexture;
sf::Sprite backgroundSprite;
sf::Event event;

std::vector<Direction> lines;
std::vector<Direction> corners;

std::atomic<bool> runningTimer(true);

void generateRandomPokemon();
void generateBoard();
void play();
void makeLine(int x, int y);
void drawLine();
void determineDirection(int a, int b);
void timer();
void countdown(int seconds);

int main() {
    generateRandomPokemon();

    if (!backgroundTexture.loadFromFile("./src/image/background/thumb-1920-574726.jpg")) {
        return -1; 
    }

    backgroundSprite.setTexture(backgroundTexture);

    float scaleX = static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y; 
    backgroundSprite.setScale(scaleX, scaleY);
    std::thread countdown_thread(countdown, second);
    while (window.isOpen()) {
        window.clear();
        window.draw(backgroundSprite);
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                runningTimer = false;
                window.close();
            }
            play();
        }

        if (couple[1]) {
            if (couple[0] == couple[1] && (start.x != end.x || start.y != end.y)) {
                endSearch = 0;
                directionLine = 0;
                preDirectionLine = 0;
                corners.clear();
                makeLine(start.x, start.y);
                if (endSearch) {
                    drawLine();
                    BOARD[start.y][start.x] = 0;
                    BOARD[end.y][end.x] = 0;
                }
            }
            couple[0] = 0;
            couple[1] = 0;
            start.x = -1;
            start.y = -1;
            end.x = -1;
            start.y = -1;
        }
        generateBoard();
        timer();
        
        if (couple[0]) {
            window.draw(rectangleOutLineStart); 
        } 
        if (couple[1]) {
            window.draw(rectangleOutLineEnd); 
        }
        if (delay == DELAY_TIME_LINE) {
            line.clear();   
            lines.clear();
            haveLine = 0;
            delay = 0;
        }
        if (haveLine) {
            delay++;
            window.draw(line);
        }

        window.display();
        sf::sleep(sf::seconds(0.01));
    }
    if (countdown_thread.joinable()) {
        countdown_thread.join();
    }
    return 0;
}

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
                float scaleFactor = 60.f / originalSize.x;
                pokemonSprite.setScale(scaleFactor, scaleFactor);
                window.draw(pokemonSprite);  
            }
        }
    }
}

void play() {
    if (event.type == sf::Event::MouseButtonPressed) {
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

