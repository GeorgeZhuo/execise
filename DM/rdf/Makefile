
###########################################
#Makefile for simple programs
###########################################
CC = g++
CC_FLAG= -g -o

PRG = rdf
OBJ = RegTree.cpp Forest.cpp main.cpp

build: compile test

compile:
	$(CC) $(CC_FLAG) $(PRG) $(OBJ)

test: clean
	./rdf
clean:
	rm -f *.o
