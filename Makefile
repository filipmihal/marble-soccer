CC = gcc
CFLAGS = -Wall -Wextra -g $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs)

# Name of the output executable
OUTPUT = app

# Source files and object files
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:.c=.o)
HEADERS = $(wildcard $(SRC_DIR)/*.h)


all: $(OUTPUT)

$(OUTPUT): $(OBJ) $(HEADERS)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(OBJ) $(LDFLAGS)

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and the executable
clean:
	rm -f $(OBJ) $(OUTPUT)
