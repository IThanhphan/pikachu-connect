#ifndef POINT
#define POINT

#include "../gamePlay/game.hpp"

const float WIDTH_POINT_TABLE = WIDTH_WINDOW - SQUARE_SIZE*(COLUMN+2) - SQUARE_SIZE;
const float HEIGHT_POINT_TABLE = SQUARE_SIZE;

int score=0;

std::vector<int> v;

sf::Color scoreTableBackground(224, 194, 154);

struct Node{
	int data;
	Node* left;
	Node* right;
	Node(int value){
		data = value;
		left = right = NULL;
	}
};

int rd();

Node* build(int start, int end);
Node* search(Node* root, int key);

void push(int k);
void bubble_sort();
void heapify(int n, int i);
void heapSort();
void in(Node* root);
void drawScoreTable();

#endif