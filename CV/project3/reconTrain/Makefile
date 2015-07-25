
###########################################
#Makefile for simple programs
###########################################
CC = g++
CC_FLAG= -g -o
OPENCV_FLAG= `pkg-config --cflags --libs opencv`
PRG = digitsRecon
OBJ = BPL.cpp digitsRecTrain.cpp

build: compile test

compile:
	$(CC) $(CC_FLAG) $(PRG) $(OBJ) $(OPENCV_FLAG)

test: clean
	./digitsRecon
clean:
	rm -f *.o
