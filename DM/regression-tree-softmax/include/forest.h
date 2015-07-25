/*************************************************************************
	> File Name: forest.h
	> Author: GoYchen
	> Mail: GoYchen@foxmail.com 
	> Created Time: Thu 11 Jun 2015 10:05:43 AM CST
 ************************************************************************/
#ifndef FOREST_H
#define FOREST_H

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <pthread.h>
#include <vector>

#include "matrix.h"
#include "node.h"
#include "tree.h"
#include "pthread_pool.h"
#include "utility.h"
#include "statistic.h"

using namespace std;

class Forest{
public:
	Forest();
	Forest(int n_trees, int n_features);
	void init(int n_trees, int n_features);

	virtual void train(Matrix &dataSet);
	virtual vector<int> predict(Matrix &dataSet, string outfile);
protected:
	//helper function
	virtual int predictRow(vector<float> &row);
	int n_trees;
	int n_features;
	bool REGRESSION;
	vector<vector<Tree> > trees;
};

class ParallelForest: public Forest{
public:
	ParallelForest();
	ParallelForest(int n_trees, int n_features, int n_threads);
	virtual void train(Matrix &dataSet);
	vector<vector<float> > softMax(Matrix &dataSet);
	void train_regression(Matrix &dataSet, vector<float> &labels, int class_num);
	void crossPredict(Matrix &trainDataSet, Matrix &testDataSet, vector<float> &labels);
protected:
	int n_threads;
};
#endif

