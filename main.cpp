#include "main.hpp"
#include "timer.cpp"
#include "mixedUpBtn.cpp"

int main() {
    generateRandomPokemon(); //sắp xếp ngẫu nhiên các pokemon trong ma trận

    //nạp hình nền trò chơi
    if (!backgroundTexture.loadFromFile("./src/image/background/thumb-1920-574726.jpg")) {
        return -1; 
    }

    //đặt hình nền
    backgroundSprite.setTexture(backgroundTexture);

    //tỉ lệ co gian hình ảnh nền phù hợp với cửa sổ trò chơi
    float scaleX = static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y; 
    backgroundSprite.setScale(scaleX, scaleY);
    // Tạo một luồng để chạy đồng hồ đếm ngược
    std::thread countdown_thread(countdown, second);
    //vòng lặp in ra màn hình trò chơi
    while (window.isOpen()) {
        //xóa màn hình để chuẩn bị vẽ lại
        window.clear();
        //vẽ hình nền trò chơi
        window.draw(backgroundSprite);
        //vòng lặp sự kiện trong trò chơi
        while (window.pollEvent(event)) {
            //sự kiện nhấn vào nút x trên màn hình trò chơi
            if (event.type == sf::Event::Closed) {
                runningTimer = false;
                window.close();
            }
            //sự kiện chơi trò chơi khi chưa thua
            if (!isLose) {
                play();
                mixedUp();
            }
        }
        //nếu pokemon kết thúc được nhấn vào
        if (couple[1]) {
            //nếu cặp pokemon giống nhau và tọa độ cặp pokemon là khác nhau
            if (couple[0] == couple[1] && (start.x != end.x || start.y != end.y)) {
                endSearch = 0; //khởi tạo biến endSearch để chuẩn bị tìm kiếm đường đi đúng
                directionLine = 0; //khởi tạo hướng đi đầu tiên của đường đi (0=vô hướng)
                preDirectionLine = 0; //khởi tạo hướng đi trước đó của đường đi (0=vô hướng)
                corners.clear(); //xóa mảng chứa các góc của đường đi khi rẽ hướng
                makeLine(start.x, start.y); //tạo cấu hình đường đi từ vị trí bắt đầu
                //nếu tìm thấy đường đi đúng
                if (endSearch) {
                    drawLine(); //vẽ đường đi đúng
                    BOARD[start.y][start.x] = 0; //đặt lại tại vi trí bắt đầu là rỗng (=0)
                    BOARD[end.y][end.x] = 0; //đặt lại tại vi trí kết thúc là rỗng (=0)
                }
            }
            //đặt lại tất cả các biến couple, start, end
            couple[0] = 0;
            couple[1] = 0;
            start.x = -1;
            start.y = -1;
            end.x = -1;
            start.y = -1;
        }
        generateBoard(); //vẽ ma trận pokemon
        drawTimer(); //vẽ thanh thời gian
        drawMixedUpBtn(); //vẽ nút làm xáo trộn các pokemon
        
        //nếu pokemon bắt đầu được nhấn (id pokemon != 0)
        if (couple[0]) {
            window.draw(rectangleOutLineStart);  //vẽ viền xung quanh pokemon
        } 
        //nếu pokemon kết thúc được nhấn (id pokemon != 0)
        if (couple[1]) {
            window.draw(rectangleOutLineEnd); //vẽ viền xung quanh pokemon
        }
        //thời gian xuất hiện của đường thẳng trước khi biến mất
        if (delay == DELAY_TIME_LINE) {
            line.clear(); //xóa mảng chứa các đường thẳng
            lines.clear(); //xóa mảng chứa cấu hình đường đi
            haveLine = 0; //đặt lại biến có đường đi hay không
            delay = 0; //đặt lại biến đếm thời gian delay
        }
        //nếu có đường đi
        if (haveLine) {
            delay++; //biến đếm thời gian +1
            window.draw(line); //vẽ đường đi
        }
        //nếu chiến thắng hoặc thua cuộc
        if (isWin() || isLose) {
            drawResultTable(resultText); //vẽ ra màn hình bảng kết quả thông qua biến toàn cục resultText
        }
        
        window.display(); //hiển thị màn hình trò chơi
        sf::sleep(sf::seconds(0.01)); //ngừng chương trình 0.01 giây trước khi vẽ lại màn hình làm giảm tốc độ xuất màn hình để tối ưu hiệu năng
    }
    //gộp luồng hoạt động của thời gian đếm ngược vào chương trình chính
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
    return true;
}

void drawResultTable(std::string result) {
    sf::RectangleShape resultTable(sf::Vector2f(WIDTH_RESULT_TABLE, HEIGHT_RESULT_TABLE));
    resultTable.setPosition(WIDTH_WINDOW/2 - WIDTH_RESULT_TABLE/2, HEIGHT_WINDOW/2 - HEIGHT_RESULT_TABLE/2); 
    resultTable.setFillColor(sf::Color::White);
    resultTable.setOutlineColor(sf::Color::Black);
    resultTable.setOutlineThickness(1.f);
    window.draw(resultTable);

    sf::Font font;
    int FontSize = 50;
    font.loadFromFile("./src/font/arial.ttf");
    sf::Text Result(result, font, FontSize);
    sf::FloatRect resultBounds = Result.getLocalBounds();
    Result.setFillColor(sf::Color::Black);
    Result.setPosition(WIDTH_WINDOW/2 - resultBounds.width/2, HEIGHT_WINDOW/2 - resultBounds.height/2);
    window.draw(Result);
}

