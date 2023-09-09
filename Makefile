# Makefile for a simple GTK4 project

# Compiler and flags
CC = gcc
CFLAGS = -Wall `pkg-config --cflags gtk4`
LDFLAGS = `pkg-config --libs gtk4`

# Source files and output executable
SRC = main.c calculator.c
OBJ = $(SRC:.c=.o)
EXEC = calculator

# Bear commands
BEAR = bear --

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

%.o: %.c
	$(BEAR) $(CC) -c $< $(CFLAGS) -o $@

run: $(EXEC)
	./$(EXEC)

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean
