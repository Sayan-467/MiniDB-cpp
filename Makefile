# Makefile
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude

SRC = src/main.cpp src/parser.cpp src/db.cpp src/table.cpp
OUT = minidb

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)
