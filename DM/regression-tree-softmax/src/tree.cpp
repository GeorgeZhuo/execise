/*************************************************************************
	> File Name: tree.cpp
	> Author: GoYchen
	> Mail: GoYchen@foxmail.com 
	> Created Time: Thu 11 Jun 2015 10:05:06 AM CST
 ************************************************************************/

#include "tree.h"
using namespace std;

Tree::Tree(){
	root = NULL;
}
Tree::~Tree(){
	if ( root != NULL )
		delete root;
}
void Tree::buildTree(Matrix &dataSet, vector<float> &labels, vector<int> featIndex, int n_columns){
	printf("building the tree\n");
	int depth = 1;
	root = buildTree_recursive(dataSet, labels, featIndex, n_columns, depth);
}

bool Tree::allTheSame(vector<float> &labels) {
	for ( int i = 0; i < labels.size() - 1; i++ ) {
		if ( labels[i] != labels[i+1] )
			return false;
	}
	return true;
}
BaseNode* Tree::buildTree_recursive(Matrix &dataSet, vector<float> &labels, vector<int> featIndex, int n_columns, int depth) {
	printf("recursively build the tree, *depth*: %d ", depth);
	assert(dataSet.rows() > 0);
	assert(dataSet.columns() >0);
	
	if ( allTheSame(labels) == true || depth >= MAX_DEPTH) {//if leaf
		float distribution = mean(labels);
		printf("is leaf! distribution is %f \n", distribution);	
		return new LeafNode(distribution, dppepth);
	}

	vector<int> columns = featIndex;	
	random_shuffle(featIndex.begin(), featIndex.end());
	featIndex.resize(n_columns);

	float maxGain = -1000.0;
	int splitIndex = 0;
	float splitThreshold = 0;

	chooseBestSplit_reg(dataSet, labels, featIndex, maxGain, splitIndex, splitThreshold);	

	printf("%f, %d, %f ", maxGain, splitIndex, splitThreshold );

	Matrix lM, rM;
	vector<float> lLabel, rLabel;
	if ( maxGain > MINIMUM_GAIN )
		dataSet.splitRowAndLabel(splitIndex, splitThreshold,lM, rM, labels, lLabel, rLabel);

	if ( maxGain < MINIMUM_GAIN || lM.rows() == 0 || rM.rows() == 0) {
		float distribution = mean(labels);
		printf("maxGain < minimumGain, is leaf! distribution is %f \n", distribution);	
		return new LeafNode(distribution, depth);
	}
	BaseNode *left = buildTree_recursive(lM, lLabel, columns, n_columns, depth + 1);	
	BaseNode *right = buildTree_recursive(rM, rLabel, columns, n_columns, depth + 1);
	return new BranchNode(maxGain, splitIndex, splitThreshold, depth, left, right);
}

void Tree::chooseBestSplit_reg(Matrix &dataSet, vector<float> &labels, vector<int> &featIndex, float &maxGain, int &splitIndex, float &splitThreshold) {
	cout << "choosing best split" ;
	
	for ( int i = 0; i < featIndex.size(); i++ ) {
		int columnIndex = featIndex[i];
		printf("in columnIndex: %d %f ", columnIndex, maxGain);
		vector<float> curColumn = dataSet.column(columnIndex);
		vector<float> split_values = findPotentialSplit(curColumn, labels);

		float preMean = 0, preVar = 0;
		for( int k = 0; k < curColumn.size(); k++ )
			preMean += curColumn[k];
		preMean /= curColumn.size();
		for (int k = 0; k < curColumn.size(); k++ )
			preVar += (curColumn[k] - preMean) * (curColumn[k]- preMean);
		preVar *= curColumn.size(); 

		for ( int j = 0; j < split_values.size(); j++ ) {
			float value = split_values[j];
			vector<float> left, right;
			splitByThreshold(curColumn, labels, left, right, value);
			//get the lowest variance
			//float curGain = variance(labels) - variance(left) - variance(right);
			float curGain = calcGain(preVar, left, right);
			if ( curGain >  maxGain) {
				maxGain = curGain;
				splitIndex = columnIndex;
				splitThreshold = value;
			}
		}
	}
}

vector<float> Tree::findPotentialSplit(vector<float> &X, vector<float> &Y) {
	//cout << "before find: " << X.size();
	vector<float> split_values;
	vector<pair<float, float> > zipped(X.size());
	for ( int i = 0; i < X.size(); i++ ) {
		zipped[i] = make_pair(X[i], Y[i]);
	}
	sort(zipped.begin(), zipped.end(), pairCompare<float>);
	for ( int i = 0; i < zipped.size() - 1; i++ ){
		float class1 = zipped[i].second;
		float class2 = zipped[i+1].second;
		if (zipped[i].first != zipped[i+1].first) {
			float midpoint = (zipped[i].first + zipped[i+1].first) / 2;
			split_values.push_back(midpoint);
		}
	}
	//cout <<" after find: "<< split_values.size() << endl;
	return split_values;
}

void Tree::splitByThreshold(vector<float> &curColumn, vector<float> &labels, vector<float> &left, vector<float> &right, float value){
	for ( int i = 0; i < curColumn.size(); i++ ) {
		//cout << i << ' ' ;
		if ( curColumn[i] < value ) {
			left.push_back(labels[i]);
		}
		else {
			right.push_back(labels[i]);
		}
	}
}

float Tree::calcGain(float preVar, vector<float> &left, vector<float> &right) {
	float mean1 = 0; float mean2 = 0; 
	float var1 = 0; float var2 = 0;
	//calculate the variance and find the smallest 
	for( int k = 0; k < left.size(); k++ )
		mean1 += left[k];
	mean1 /= left.size();
	for (int k = 0; k < left.size(); k++ )
		var1 += (left[k] - mean1) * (left[k] - mean1);
	var1 *= left.size(); 
	for (int k = 0; k < right.size(); k++)
		mean2 += right[k];
	mean2 /= right.size();
	for ( int k = 0; k < right.size(); k++ )
		var2 += (right[k] - mean2) * (right[k] - mean2);
	var2 *= right.size();
	return (preVar - var1 - var2);
}

int Tree::getCount(){
	return root->count();
}
float Tree::predict(vector<float> &row){
	return root->predict(row);
}
