/*************************************************************************
	> File Name: node.h
	> Author: GoYchen
	> Mail: GoYchen@foxmail.com 
	> Created Time: Thu 11 Jun 2015 10:04:29 AM CST
 ************************************************************************/
#ifndef	NODE_H 
#define NODE_H 

#include <iostream>
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <string>

#include "matrix.h"
#include "statistic.h"
#include "utility.h"

using namespace std;

extern float MINIMUM_GAIN;
extern int CLASSES_NUM;
extern int MAX_DEPTH;

class BaseNode{
public:
	virtual float predict(vector<float> &row) = 0;
	virtual int count() = 0;
};

class BranchNode: public BaseNode{
public:
	BranchNode();
	BranchNode(float gain, int featIndex, float value, int depth, BaseNode *left, BaseNode *right);
	~BranchNode();
	float predict(vector<float> &row);	
	int count();
protected:
	BaseNode *left;
	BaseNode *right;
	int featIndex;
	float value;
	float gain;
	int depth;
};

class LeafNode: public BaseNode{
public:
	LeafNode();
	LeafNode(float distribution, int depth);
	~LeafNode();
	float  predict(vector<float> &row);
	int count();
protected:
	int depth;
	float distribution;
};
#endif
