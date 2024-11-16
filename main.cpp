#include <SFML/Graphics.hpp>
#include <string>
#include <random>
#include <iostream>
#include <stack>
#include <vector>
#include <queue>
#include <cmath>

const int ROW = 6;
const int COLUMN = 12;
const int NUMBER_OF_POKEMON = 18;
const int NUMBER_OF_EACH_POKEMON = 4;
const int EMPTY = 0;
const int SQUARE_SIZE = 60.f;
const int delayTimeLine = 50;
const int dx[] = {-1, 0, 1, 0}; 
const int dy[] = {0, -1, 0, 1};
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
int visited[ROW+2][COLUMN+2] = {};
int couple[2] = {0, 0};
int startFlat = 1;
int endFlat = 0;
int canConnect = 0;
int haveLine = 0;
int delay = 0;
int endSearch = 0;
int directionLine = 0;
int preDirectionLine = 0;

struct Direction {
    int x, y;
};

Direction start;
Direction end;

sf::RenderWindow window(sf::VideoMode(1000, 700), "PIKACHU");
sf::RectangleShape rectangleOutLineStart(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
sf::RectangleShape rectangleOutLineEnd(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
sf::Color pokemonBackground(255, 218, 251); 
sf::VertexArray line(sf::Lines);
sf::Texture backgroundTexture;
sf::Sprite backgroundSprite;
sf::Event event;

std::vector<Direction> lines;
std::vector<Direction> corners;

void generateRandomPokemon();
void generateBoard();
void play();
void BFS();
void makeLine(int x, int y);
void drawLine();
void determineDirection(int a, int b);

int main() {
    generateRandomPokemon();

    if (!backgroundTexture.loadFromFile("./src/image/background/thumb-1920-574726.jpg")) {
        return -1; 
    }

    backgroundSprite.setTexture(backgroundTexture);

    float scaleX = static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y; 
    backgroundSprite.setScale(scaleX, scaleY);

    while (window.isOpen())
    {
        window.clear();
        window.draw(backgroundSprite);
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            play();
        }

        if (couple[1]) {
            canConnect = 0;
            BFS();
            if (couple[0] == couple[1] && (start.x != end.x || start.y != end.y) && canConnect) {
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
        
        if (couple[0]) {
            window.draw(rectangleOutLineStart); 
        } 
        if (couple[1]) {
            window.draw(rectangleOutLineEnd); 
        }
        if (delay == delayTimeLine) {
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
            } while (BOARD[randomRow][randomCol] != EMPTY);
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

void BFS() {
    std::queue<Direction> q;

    for (int i=0; i<ROW+2; i++) {
        for (int j=0; j<COLUMN+2; j++) {
            visited[i][j] = 0;
        }
    }

    q.push(start);
    visited[start.y][start.x] = 1;
    while (!q.empty()) {
        Direction cell = q.front();
        q.pop();

        if (cell.x == end.x && cell.y == end.y) {
            canConnect = 1;
            break;
        }

        for (int i=0; i<4; i++) {
            int nx = cell.x + dx[i];
            int ny = cell.y + dy[i];      
            if (nx>=0 && nx<COLUMN+2 && ny>=0 && ny<ROW+2 &&
                !BOARD[ny][nx] && !visited[ny][nx] || (nx==end.x && ny==end.y)) {
                    visited[ny][nx] = 1;
                    q.push({nx, ny});
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
    if (!endSearch && x>=0 && x<COLUMN+2 && y>=0 && y<ROW+2 && visited[y][x]>0) {
        for (int i=0; i<lines.size(); i++) {
            if (x == lines[i].x && y == lines[i].y) {
                return;
            }
        }
        lines.push_back({x, y});
        visited[y][x] = 2;
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
        int cx = end.x - x;
        int cy = end.y - y;
        if ((cx>0 && cy>0) || (cx==0 && cy>0)) {
            makeLine(x, y+1); //xuống
            makeLine(x+1, y); //phải
            makeLine(x, y-1); //lên
            makeLine(x-1, y); //trái
        } else if ((cx>0 && cy<0) || (cx>0 && cy==0)) {
            makeLine(x+1, y); //phải
            makeLine(x, y-1); //lên
            makeLine(x-1, y); //trái
            makeLine(x, y+1); //xuống
        } else if ((cx<0 && cy<0) || (cx==0 && cy<0)) {
            makeLine(x, y-1); //lên
            makeLine(x-1, y); //trái
            makeLine(x, y+1); //xuống
            makeLine(x+1, y); //phải
        } else if ((cx<0 && cy>0) || (cx<0 && cy==0)) {
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
