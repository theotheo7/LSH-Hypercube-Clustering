# Compiler and compiler flags
CC = g++
CFLAGS = -std=c++17

# Directories
SRC = src/
INCLUDE = include/
RESOURCES = resources/
BUILD = build/

OBJS = $(BUILD)main.o $(BUILD)parser.o

LSH = $(BUILD)lsh

$(BUILD)main.o: $(SRC)main.cpp
	$(CC) -o $(BUILD)main.o $(CFLAGS) -c $(SRC)main.cpp

$(BUILD)parser.o: $(SRC)parser.cpp $(INCLUDE)parser.hpp
	$(CC) -o $(BUILD)parser.o $(CFLAGS) -c $(SRC)parser.cpp

$(LSH): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(LSH)

all: $(LSH)

clean:
	rm -f $(OBJS) $(LSH)

lsh: $(LSH)
	./$(LSH)