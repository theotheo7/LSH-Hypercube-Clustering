# Compiler and compiler flags
CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -O3

# Directories
SRC = src/
INCLUDE = include/
RESOURCES = resources/
BUILD = build/

OBJS_LSH = $(BUILD)main_lsh.o $(BUILD)parser.o $(BUILD)utils.o $(BUILD)image.o $(BUILD)hash_function.o $(BUILD)hash_table.o $(BUILD)lsh.o
SRCS_LSH = $(SRC)main_lsh.cpp $(SRC)parser.cpp $(SRC)utils.cpp $(SRC)image.cpp $(SRC)hash_function.cpp $(SRC)hash_table.cpp $(SRC)lsh.cpp

OBJS_CUBE = $(BUILD)main_cube.o $(BUILD)parser.o $(BUILD)utils.o $(BUILD)image.o $(BUILD)hash_function.o $(BUILD)hash_table.o $(BUILD)cube.o
SRCS_CUBE = $(SRC)main_cube.cpp $(SRC)parser.cpp $(SRC)utils.cpp $(SRC)image.cpp $(SRC)hash_function.cpp $(SRC)hash_table.cpp $(SRC)cube.cpp

LSH = $(BUILD)lsh

CUBE = $(BUILD)cube

# Objects
$(BUILD)main_lsh.o: $(SRC)main_lsh.cpp
	$(CC) -o $(BUILD)main_lsh.o $(CFLAGS) -c $(SRC)main_lsh.cpp

$(BUILD)main_cube.o: $(SRC)main_cube.cpp
	$(CC) -o $(BUILD)main_cube.o $(CFLAGS) -c $(SRC)main_cube.cpp

$(BUILD)parser.o: $(SRC)parser.cpp $(INCLUDE)parser.hpp
	$(CC) -o $(BUILD)parser.o $(CFLAGS) -c $(SRC)parser.cpp

$(BUILD)utils.o: $(SRC)utils.cpp $(INCLUDE)utils.hpp
	$(CC) -o $(BUILD)utils.o $(CFLAGS) -c $(SRC)utils.cpp

$(BUILD)image.o: $(SRC)image.cpp $(INCLUDE)image.hpp
	$(CC) -o $(BUILD)image.o $(CFLAGS) -c $(SRC)image.cpp

$(BUILD)hash_function.o: $(SRC)hash_function.cpp $(INCLUDE)hash_function.hpp
	$(CC) -o $(BUILD)hash_function.o $(CFLAGS) -c $(SRC)hash_function.cpp

$(BUILD)hash_table.o: $(SRC)hash_table.cpp $(INCLUDE)hash_table.hpp
	$(CC) -o $(BUILD)hash_table.o $(CFLAGS) -c $(SRC)hash_table.cpp

$(BUILD)cube.o: $(SRC)cube.cpp $(INCLUDE)cube.hpp
	$(CC) -o $(BUILD)cube.o $(CFLAGS) -c $(SRC)cube.cpp

$(BUILD)lsh.o: $(SRC)lsh.cpp $(INCLUDE)lsh.hpp
	$(CC) -o $(BUILD)lsh.o $(CFLAGS) -c $(SRC)lsh.cpp

# Executables
$(LSH): $(OBJS_LSH)
	$(CC) $(OBJS_LSH) $(CFLAGS) -o $(LSH)

$(CUBE): $(OBJS_CUBE)
	$(CC) $(OBJS_CUBE) $(CFLAGS) -o $(CUBE)

all: $(LSH) $(CUBE)

clean:
	rm -f $(OBJS_LSH) $(OBJS_CUBE) $(LSH) $(CUBE)

lsh: $(LSH)
	./$(LSH)

cube: $(CUBE)
	./$(CUBE)