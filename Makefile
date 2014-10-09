.PHONY: main Doxyfile html test judge clean
SRC_DIR = ./source
TOOLS_DIR = $(SRC_DIR)/tools
JUDGE_DIR = ./judge

all: main

Doxyfile:
	doxygen -g

html: Doxyfile $(SRC_DIR)/Node.h $(SRC_DIR)/Node.cpp $(SRC_DIR)/main.cpp $(SRC_DIR)/UnitTests.cpp
	doxygen Doxyfile

main: $(SRC_DIR)/Node.h $(SRC_DIR)/Node.cpp $(SRC_DIR)/main.cpp
	g++ -pedantic -std=c++11 -Wall $(filter %.cpp, $^) -o main

test: $(SRC_DIR)/Node.h $(SRC_DIR)/Node.cpp $(SRC_DIR)/UnitTests.cpp
	g++ -pedantic -std=c++11 -Wall $(filter %.cpp, $^) -o test -lgtest -lgtest_main -lpthread

judge: $(SRC_DIR)/main.cpp $(SRC_DIR)/Node.cpp
	@mkdir -p judge
	@sed -e '/#include "prints.h"/d' $(SRC_DIR)/Node.cpp > $(JUDGE_DIR)/Node.cpp
	@grep -A500 "int main" $(SRC_DIR)/main.cpp >> $(JUDGE_DIR)/Node.cpp

clean:
	rm -f main
	rm -f test
	rm -f -r ./judge
