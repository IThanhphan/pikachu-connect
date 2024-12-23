#include "point.hpp"

int rd(){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 36);
	int random_number = dist(gen);
	return random_number;
}

void push(int k) {
	while (v.size() < k) { 
		int num = rd();
		bool exists = false;
		
		for (int j = 0; j < v.size(); j++) {
			if (v[j] == num) {
				exists = true;
				break;
			}
		}
		
		if (!exists) {
			v.push_back(num);
		}
	}
}

void bubble_sort(){
	for(int i=0; i<v.size(); i++){
		int min =v[i];
		int m_pos = i;
		for(int j=i; j<v.size(); j++){
			if(min>v[j]){
				min = v[j];
				m_pos = j;
			}
		}
		std::swap(v[i], v[m_pos] );
	}
}

void heapify(int n, int i){
	int max = i;
	int left = 2*i +1;
	int right = 2*i +2;
	
	if(left<n && v[left] > v[max]){
		max = left;
	}
	if(right<n && v[right] > v[max]){
		max = right;
	}
	if(max !=i){
		std::swap(v[i], v[max]);
		heapify(n, max);
	}
}

void heapSort(){
	int n= v.size();
	
	for(int i=n/2-1; i>=0; i-- ){
		heapify(n,i);
	}
	for (int i = n - 1; i > 0; i--) {
	
		std::swap(v[0], v[i]);

		heapify(i, 0);
	}
}

Node* build(int start, int end){
	if(start>end){
		return NULL;
	}
	int mid = start +(end-start) / 2;
	Node* node = new Node(v[mid]);
	node->left= build(start, mid-1);
	node->right = build(mid+1,end);
	
	return node;
	
}

Node* search(Node* root, int key) {
	if (root == NULL || root->data == key) {
		return root; 
	}
	if(key<root->data){
		return search(root->left, key);
	}
	else if(key>root->data){
		return search(root->right, key);	
	}	
	return NULL;
}

void in(Node* root){
	if(root==NULL) return;
	in(root->left);
	std:: cout << root->data << ' ';
	in(root->right);
}

void drawScoreTable() {
	font.loadFromFile("./src/font/arial.ttf");
	sf::Text scoreTitle("Score", font, 30);
	sf::FloatRect scoreTitleBounds = scoreTitle.getLocalBounds();
	scoreTitle.setFillColor(sf::Color::Black);
	float positionX1 = SQUARE_SIZE * (COLUMN + 2) + WIDTH_POINT_TABLE / 2 - scoreTitleBounds.width / 2;
	float positionY1 = scoreTitleBounds.height / 2;
	scoreTitle.setPosition(positionX1, positionY1);
	window.draw(scoreTitle);

	sf::RectangleShape rectangleScore(sf::Vector2f(WIDTH_POINT_TABLE, HEIGHT_POINT_TABLE));
	rectangleScore.setPosition(SQUARE_SIZE * (COLUMN + 2), SQUARE_SIZE);
	rectangleScore.setFillColor(scoreTableBackground);
	rectangleScore.setOutlineColor(sf::Color::Black);
	rectangleScore.setOutlineThickness(1.f);
	window.draw(rectangleScore);

	std::string scoreText = std::to_string(score);
	sf::Text score(scoreText, font, 30);
	sf::FloatRect scoreBounds = scoreTitle.getLocalBounds();
	score.setFillColor(sf::Color::White);
	float positionX2 = SQUARE_SIZE * (COLUMN + 2) + WIDTH_POINT_TABLE / 2 - scoreBounds.width / 2;
	float positionY2 = SQUARE_SIZE + scoreBounds.height / 2;
	score.setPosition(positionX2, positionY2);
	window.draw(score);
}