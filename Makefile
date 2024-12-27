# Biến
# CXX = g++
# CXXFLAGS = -c -I"D:\library\game\c_c++\SFML\SFML-2.6.1\include" -DSFML_STATIC
# LDFLAGS = -L"D:\library\game\c_c++\SFML\SFML-2.6.1\lib" -lsfml-graphics -lsfml-window -lsfml-system -lopenal32 -lfreetype -lwinmm -lgdi32

CXX = g++
CXXFLAGS = -c -I"src\include" -DSFML_STATIC
LDFLAGS = -L"src\lib" -lsfml-graphics -lsfml-window -lsfml-system -lopenal32 -lopengl32 -lws2_32 -lfreetype -lwinmm -lgdi32 -static

# Tệp thực thi
TARGET = main

# Tệp nguồn
SOURCES = main.cpp

# Tệp đối tượng
OBJECTS = main.o

# Quy tắc chính
$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Quy tắc biên dịch từng tệp nguồn
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Quy tắc clean để xóa tệp đối tượng và tệp thực thi
clean:
	del /Q $(OBJECTS) $(TARGET)

# Quy tắc chạy chương trình
run: $(TARGET)
	./$(TARGET)
