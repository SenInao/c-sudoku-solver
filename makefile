CC = gcc
CFLAGS = -lncurses -I$(IDIR)
SRCDIR = ./src/
IDIR = ./include/

SOURCES = $(SRCDIR)*.c

all: sudoku run clean

sudoku:
	$(CC) $(SOURCES) $(CFLAGS) -o $@

run:
	./sudoku

clean:
	rm sudoku
