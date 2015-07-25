#########################################################################
# File Name: Makefile
# Author: GoYchen
# mail: GoYchen@foxmail.com
# Created Time: Fri 12 Jun 2015 08:26:42 PM CST
#########################################################################
CC = g++
CFLAGS = -g -pthread -I./include -o
EXE = rf
SOURCE = main.cpp src/node.cpp src/tree.cpp src/forest.cpp src/matrix.cpp src/statistic.cpp src/pthread_pool.c
FILEDIR = /home/eminem/dataMining/project2

Build: compile run
compile:
	$(CC) $(CFLAGS) $(EXE) $(SOURCE)
run:
	time ./$(EXE) -t $(FILEDIR)/train.csv -c $(FILEDIR)/test.csv -o result.csv -p 4 -n 10 -f 10 -g 10 

clean:
	rm -f *.o
debug: compile
	gdb --args ./$(EXE) -t $(FILEDIR)/train.csv -c $(FILEDIR)/test.csv -p 1 -n 1 -f 7
