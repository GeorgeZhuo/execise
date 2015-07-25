/*************************************************************************
	> File Name: main.cpp
	> Author: GoYchen
	> Mail: GoYchen@foxmail.com 
	> Created Time: Thu 11 Jun 2015 09:47:14 AM CST
 ************************************************************************/

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <unistd.h>

#include "statistic.h"
#include "node.h"
#include "matrix.h"
#include "forest.h"



float MINIMUM_GAIN = 0.1;
int MAX_DEPTH = 10;
int CLASSES_NUM = 27;//26 classes 
using namespace std;

int n_threads = 16;//default parameters
int n_trees = 100;
int n_features = 30;

int main(int argc, char *argv[]){
	//1. get command
	//2. read data
	//3. train
	//4. predict
	string trainfile, testfile, resultfile;
	int c;
	while ( (c = getopt(argc, argv, "t:c:o:p:n:f:j:g:")) != -1 ){
		switch ( c ) {
		case 't': trainfile = optarg; break;
		case 'c': testfile = optarg; break;
		case 'o': resultfile = optarg; break;
		case 'p': n_threads = atoi(optarg);break; 
		case 'n': n_trees = atoi(optarg); 
				  assert(n_trees > 0); break;
		case 'f': n_features = atoi(optarg); 
				  assert(n_features > 0); break;
		case 'g': MINIMUM_GAIN = atof(optarg); 
				  assert(MINIMUM_GAIN > 0.0); break;
		default: printf("invalid parameters!!!!"); exit(1);
		}
	}
	
	Matrix trainDataSet;
	Matrix testDataSet;
	trainDataSet.load(trainfile, true, true);//load data is okay
	testDataSet.load(testfile, true, true);

	if ( n_threads <= 0 ) 
		n_threads = 16;
	printf("using %d threads in pool\n", n_threads);
	printf("train dataset: %d rows and %d columns in matrix\n", trainDataSet.rows(), trainDataSet.columns());
	printf("test dataset: %d rows and %d columns in matrix\n", testDataSet.rows(), testDataSet.columns());

	ParallelForest pf(n_trees, n_features, n_threads);//okay
	pf.train(trainDataSet);
	//pf.predict(testDataSet, resultfile);


	return 0;
}
