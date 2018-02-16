################################
## Makefile for tic-tac-toe
##
## Javier Lombillo <javier@asymptotic.org>
## 2013-04-25
##

CC	   = gcc
CFLAGS = -W -Wall

SRCS 	= main.c init.c board.c moves.c winner.c help.c
OBJECTS = $(SRCS:.c=.o)
EXE 	= tic-tac-toe

all: $(EXE)

$(EXE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXE)
	@strip $(EXE)
	@echo "Build complete."

main.o: tic-tac-toe.h
init.o: tic-tac-toe.h
board.o: tic-tac-toe.h
moves.o: tic-tac-toe.h
winner.o: tic-tac-toe.h

.PHONY: clean mrproper rebuild

# clean up object files
clean:
	rm -f $(OBJECTS)

# sparkly clean
mrproper: clean
	rm -f tic-tac-toe

# erase everyhing and start over
rebuild: mrproper all
