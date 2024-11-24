#ifndef MAIN 
#define MAIN

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
const int WIDTH_RESULT_TABLE = 300;
const int HEIGHT_RESULT_TABLE = WIDTH_RESULT_TABLE;
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
int isLose = 0;

std::string resultText;

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
void drawResultTable(std::string result);

bool isWin();

#endif