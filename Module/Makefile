# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Wno-sign-compare
LDFLAGS = 

# Цели по умолчанию
all: lab2_test test_errors

# Основная тестирующая программа
lab2_test: module.o main.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Тестирование обработки ошибок
test_errors: module.o test_errors.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Объектные файлы
module.o: module.cpp module.h
	$(CXX) $(CXXFLAGS) -c module.cpp

main.o: main.cpp module.h
	$(CXX) $(CXXFLAGS) -c main.cpp

test_errors.o: test_errors.cpp module.h
	$(CXX) $(CXXFLAGS) -c test_errors.cpp

# Запуск тестов
test: lab2_test test_errors
	@echo "=== ЗАПУСК ОСНОВНЫХ ТЕСТОВ ==="
	./lab2_test
	@echo ""
	@echo "=== ЗАПУСК ТЕСТОВ ОШИБОК ==="
	./test_errors

# Запуск только основных тестов
run: lab2_test
	./lab2_test

# Запуск только тестов ошибок
run_errors: test_errors
	./test_errors

# Очистка
clean:
	rm -f *.o lab2_test test_errors

# Показать помощь
help:
	@echo "Доступные команды:"
	@echo "  make all      - скомпилировать все программы"
	@echo "  make test     - скомпилировать и запустить все тесты"
	@echo "  make run      - скомпилировать и запустить основные тесты"
	@echo "  make run_errors - скомпилировать и запустить тесты ошибок"
	@echo "  make clean    - удалить скомпилированные файлы"
	@echo "  make help     - показать эту справку"

.PHONY: all test run run_errors clean help
