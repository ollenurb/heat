CXX       := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb

BIN     := bin
SRC     := src
INCLUDE := include
LIB     := SDL2
LIBRARIES   :=
EXECUTABLE  := main


all: $(BIN)/$(EXECUTABLE)

run: clean all
		clear
		./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
		$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -l$(LIB) -lSDL2_ttf $^ -o $@ $(LIBRARIES)

clean:
		-rm $(BIN)/*
