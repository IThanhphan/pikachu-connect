#include <SFML/Graphics.hpp>
#include <string>
#include <random>
#include <iostream>

const int ROW = 6;
const int COLUMN = 12;
const int NUMBER_OF_POKEMON = 18;
const int NUMBER_OF_EACH_POKEMON = 4;
const int EMPTY = 0;
const int SQUARE_SIZE = 60.f;
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

int BOARD[ROW+2][COLUMN+2];
int couple[2] = {0, 0};
int startFlat = 1;
int endFlat = 0;

struct Direction {
    int x, y;
};

Direction start;
Direction end;

sf::RenderWindow window(sf::VideoMode(1000, 700), "PIKACHU");
sf::RectangleShape rectangleOutLineStart(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
sf::RectangleShape rectangleOutLineEnd(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
sf::Color pokemonBackground(255, 218, 251); 
sf::Texture backgroundTexture;
sf::Sprite backgroundSprite;
sf::Event event;

void generateRandomPokemon();
void generateBoard();
void play();

int main() {
    for (int i=0; i<ROW+2; i++) {
        for (int j=0; j<COLUMN+2; j++) {
            BOARD[i][j] = 0;
        }
    }

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
            if (couple[0] == couple[1]) {
                BOARD[start.y][start.x] = 0;
                BOARD[end.y][end.x] = 0;
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
            std::cout << "Start " << couple[0] << " " << couple[1] << std::endl;
            window.draw(rectangleOutLineStart); 
        } 
        if (couple[1]) {
            std::cout << "End " << couple[0] << " " << couple[1] << std::endl;
            window.draw(rectangleOutLineEnd); 
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