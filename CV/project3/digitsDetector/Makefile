
###########################################
#Makefile for simple programs
###########################################
CC = g++
CC_FLAG= -g -o
OPENCV_FLAG= `pkg-config --cflags --libs opencv`

PRG = digitsDetector
OBJ = BPL.cpp digitsDetect.cpp

build: compile 

compile:
	$(CC) $(CC_FLAG) $(PRG) $(OBJ) $(OPENCV_FLAG)

clean:
	rm -f *.o
