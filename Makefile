CFLAGS = -Wall -Wno-unused-command-line-argument -std=c++11 -Iinclude -lGL -lglfw -lGLEW -lstdc++
CC = clang

SRC_DIR = src
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(SRC_DIR)/%.o, $(SOURCES))

OUT_DIR = bin

.PHONY: all clean

all: $(OBJS)
	if [ ! -d "bin" ]; then mkdir bin; fi
	$(CC) $(CFLAGS) $^ -o $(OUT_DIR)/fluid_sim

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f bin/* src/*.o
