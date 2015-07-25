
###########################################
#Makefile for simple programs
###########################################
CC = g++
CC_FLAG= -g -o

PRG = lr
OBJ = LR.cpp main.cpp

build: compile test

compile:
	$(CC) $(CC_FLAG) $(PRG) $(OBJ)

test: clean
	./lr
clean:
	rm -f *.o
