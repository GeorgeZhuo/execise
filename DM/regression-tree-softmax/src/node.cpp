/*************************************************************************
	> File Name: node.cpp
	> Author: GoYchen
	> Mail: GoYchen@foxmail.com 
	> Created Time: Thu 11 Jun 2015 10:04:39 AM CST
 ************************************************************************/


#include "node.h"

using namespace std;

BranchNode::BranchNode(){
	this->left = this->right = NULL;
	this->featIndex = -1;
}

BranchNode::BranchNode(float gain, int featIndex, float value,int depth, BaseNode *left, BaseNode *right){
	this->gain = gain;
	this->featIndex = featIndex;
	this->value = value;
	this->left = left;
	this->right = right;
	this->depth = depth;
}

BranchNode::~BranchNode(){
	if ( this->left != NULL )
		delete this->left;
	if ( this->right != NULL )
		delete this->right;
}
	
LeafNode::LeafNode(){
}

LeafNode::LeafNode(float distribution, int depth){
	this->distribution = distribution;
	this->depth = depth;
}

LeafNode::~LeafNode(){
}

float BranchNode::predict(vector<float> &row){
	if ( row[this->featIndex] < this->value ){
		return this->left->predict(row);
	}
	else{
		return this->right->predict(row);
	}
}

float LeafNode::predict(vector<float> &row){
	return this->distribution;
}

int BranchNode::count(){
	int nodeCount = 1;
	nodeCount += this->left->count();
	nodeCount += this->right->count();
	return nodeCount;
} 

int LeafNode::count(){
	return 1;
}

