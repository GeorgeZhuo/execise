
###########################################
#Makefile for simple programs
###########################################
CC = g++
CC_FLAG= -g -o

PRG = bpl
OBJ = BPL.cpp main.cpp

build: compile test

compile:
	$(CC) $(CC_FLAG) $(PRG) $(OBJ)

test: clean
	./bpl
clean:
	rm -f *.o
