/*************************************************************************
	> File Name: tree.h
	> Author: GoYchen
	> Mail: GoYchen@foxmail.com 
	> Created Time: Thu 11 Jun 2015 10:04:46 AM CST
 ************************************************************************/

#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <cmath>
#include <algorithm>
#include <stdio.h>
#include <string.h>

#include "node.h"
#include "utility.h"
#include "statistic.h"
#include "matrix.h"

using namespace std;

class Tree{
public:
	Tree();
	~Tree();
	void buildTree(Matrix &dataSet, vector<float> &labels, vector<int> featIndex, int n_columns);
	float predict(vector<float> &row);
	int getCount();

protected:
	//helper function in buildtree
	BaseNode* buildTree_recursive(Matrix &dataSet, vector<float> &labels, vector<int> featIndex, int n_columns, int depth);
	bool allTheSame(vector<float> &labels);
	//helper function in find the best split feature and values
	void chooseBestSplit_reg(Matrix &dataSet, vector<float> &labels, vector<int> &featIndex, float &maxGain, int &splitIndex, float &splitThreshold);
	vector<float> findPotentialSplit(vector<float> &X, vector<float> &Y);
	void splitByThreshold(vector<float> &curColumn, vector<float> &labels, vector<float> &left, vector<float> &right, float value);
	float calcGain(float preVar, vector<float> &left, vector<float> &right);

private:
	BaseNode *root;
};
#endif
