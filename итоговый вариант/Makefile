# Компилятор
CXX = g++

# Флаги компиляции
CXXFLAGS = -Wall -Wextra -std=c++17

# Имена исполняемых файлов
LN_EXEC = ln
PI_EXEC = pi_exec
TEST_EXEC = test_exec

# Цель по умолчанию
all: $(LN_EXEC) $(PI_EXEC) $(TEST_EXEC)

# Сборка LongNumber/ln.cpp
$(LN_EXEC): LongNumber/ln.cpp
	$(CXX) $(CXXFLAGS) -o $(LN_EXEC) LongNumber/ln.cpp

# Сборка pi.cpp
$(PI_EXEC): pi.cpp
	$(CXX) $(CXXFLAGS) -o $(PI_EXEC) pi.cpp

# Сборка test.cpp
$(TEST_EXEC): test.cpp
	$(CXX) $(CXXFLAGS) -o $(TEST_EXEC) test.cpp

# Запуск тестов
test: $(TEST_EXEC)
	./$(TEST_EXEC)

# Запуск вычисления 100 знаков числа Пи
pi: $(PI_EXEC)
	./$(PI_EXEC)

# Очистка сборочных файлов
clean:
	rm -f $(LN_EXEC) $(PI_EXEC) $(TEST_EXEC)

.PHONY: all test pi clean
