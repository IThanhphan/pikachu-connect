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
#include <fstream>
#include <unistd.h>

const float WIDTH_WINDOW = 1400; //chiều rộng cửa sổ trò chơi
const float HEIGHT_WINDOW = 700; //chiều cao cửa sổ trò chơi
const float SQUARE_SIZE = 60; //kích thước hình vuông chứa mỗi pokemon
const float WIDTH_RESULT_TABLE = 400; //chiều rộng bảng kết quả
const float HEIGHT_RESULT_TABLE = WIDTH_RESULT_TABLE; //chiều cao bảng kết quả

const int ROW = 6; //số hàng của ma trận hiện pokemon
const int COLUMN = 12; //số cột của ma trận hiện pokemon
const int NUMBER_OF_POKEMON = 18; //số lượng pokemon
const int NUMBER_OF_EACH_POKEMON = 4; //số lượng mỗi loại pokemon
const int DELAY_TIME_LINE = 20; //thời gian xuất hiện của đường nối 2 pokemon
//mảng chứa các pokemon, mỗi vị trí của pokemon trong mảng là id của pokemon đó trong ma trận, vị trí đầu tiên để trống để chỉ định đó là vị trí rỗng id=0
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

int BOARD[ROW+2][COLUMN+2] = {}; //ma trận hiển thị pokemon có thêm khung viền để trống ở ngoài
int couple[2] = {0, 0}; //mảng chứa 1 cặp pokemon
int startFlat = 1; //cờ hiệu đánh dấu đã đánh vào ô bắt đầu
int endFlat = 0; //cờ hiệu đánh dấu đã đánh vào ô kết thúc
int haveLine = 0; //biến xác định có thể vẽ ra được đường thẳng hay không
int delay = 0; //biến có thể tăng đến thời gian giới hạn đường đi (DELAY_TIME_LINE)
int endSearch = 0;// biến xác định đã có được đường đi đúng
int directionLine = 0; //hướng đi hiện tại của đường thẳng
int preDirectionLine = 0; //hướng đi trước đó của đường thẳng
int isEnd = 0; //biến xác định đã thắng thua hay chưa
int isPlaying = 0;
int newHighScore = 0;

float plgPosX;
float plgPosY;
float widthPlg;
float heightPlg;

std::string resultText;// biến chuỗi in ra kết quả
//struct chứa tọa độ x, y trên ma trận
struct Direction {
    int x, y;
};

Direction start; //tọa độ ô đầu tiên
Direction end; //tọa độ ô kết thúc

sf::RenderWindow window(sf::VideoMode(WIDTH_WINDOW, HEIGHT_WINDOW), "PIKACHU"); //đối tượng chứa kích thước cửa sổ
sf::RectangleShape rectangleOutLineStart(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE)); //đối tượng viền hình vuông khi người dùng nhấn vào ô đầu tiên
sf::RectangleShape rectangleOutLineEnd(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE)); //đối tượng viền hình vuông khi người dùng nhấn vào ô kết thúc
sf::Color pokemonBackground(255, 218, 251); // màu hình nền của mỗi pokemon
sf::VertexArray line(sf::Lines); //đối tượng một mảng các đường thẳng
sf::Texture backgroundTexture;  //kết cấu hình nền trò chơi
sf::Sprite backgroundSprite;
sf::Event event; //đối tượng chứa các sự kiện trong quá trình chơi
sf::Font font;
sf::RectangleShape blackOverlay(sf::Vector2f(WIDTH_WINDOW, HEIGHT_WINDOW));

std::vector<Direction> lines; //mảng chứa cấu hình đường đi
std::vector<Direction> corners; //mảng chứa các góc khi đương đi rẽ
std::vector<std::string> levels;
std::vector<int> highScores;

void generateRandomPokemon(); //hàm tạo ra một ma trận pokemon một cách ngẫu nhiên
void generateBoard(); //hàm in ra ma trận pokemon lên màn hình
void clickPokemon(); //hàm chứa sự kiện khi chơi trò chơi
void makeLine(int x, int y); //hàm tạo ra cấu hình đường đi đúng
void drawLine(); //hàm vẽ ra đường đi đúng
void determineDirection(int a, int b); //hàm xác định đường đi đang đi hướng nào
void drawResultTable(std::string result); //hàm vẽ ra bảng kết quả
void playAgainOrNext();
void reset();
void closeWindow();

bool isWin(); //hàm xác định đã chiến thắng hay chưa

#endif