#include "game.cpp"

int main() {
    //khang
    push(10);
    for(int x:v) {
		std::cout << x << ' ';
	}std::cout << std::endl;
    heapSort();
    for(int x:v) {
		std::cout << x << ' ';
	}std::cout << std::endl;
    //
    
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
                isCountDown = 0;
                window.close();
            }
            //sự kiện chơi trò chơi khi chưa thua
            if (!isEnd) {
                play();
                mixedUp();
            } else {
                playAgain();
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
                    //khang
                    score ++;
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
        drawScoreTable(); //vẽ thanh điểm
        
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
        if (isWin() || isEnd) {
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



