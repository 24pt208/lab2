# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2
LDFLAGS = 

# Имена файлов
SOURCES = main.cpp modAlphaCipher.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = cipher

# Правило по умолчанию
all: $(TARGET)

# Сборка основной программы
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Компиляция main.cpp
main.o: main.cpp modAlphaCipher.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# Компиляция modAlphaCipher.cpp
modAlphaCipher.o: modAlphaCipher.cpp modAlphaCipher.h
	$(CXX) $(CXXFLAGS) -c modAlphaCipher.cpp

# Очистка
clean:
	rm -f $(OBJECTS) $(TARGET)

# Пересборка
rebuild: clean all

# Запуск программы
run: $(TARGET)
	./$(TARGET)

# Отладочная сборка
debug: CXXFLAGS += -g -DDEBUG
debug: rebuild

.PHONY: all clean rebuild run debug
