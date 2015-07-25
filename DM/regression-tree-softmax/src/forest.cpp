/*************************************************************************
	> File Name: forest.cpp
	> Author: GoYchen
	> Mail: GoYchen@foxmail.com 
	> Created Time: Thu 11 Jun 2015 10:05:51 AM CST
 ************************************************************************/

#include "forest.h"

#define e 2.7182
using namespace std;

Forest::Forest() {//okay
	printf("forest has been build\n");
	//init(100, 10);
}
Forest::Forest(int n_trees, int n_features) {//okay
	printf("forest has been build with %d trees %d features\n", n_trees, n_features);
	init(n_trees, n_features);
}

void Forest::init(int n_trees, int n_features) {//okay
	this->n_trees = n_trees;
	this->n_features = n_features;
	for ( int i = 0; i < CLASSES_NUM -1; i++ ) {
		vector<Tree> row;
		for ( int j = 0; j < n_trees; j++ ) 
			row.push_back(Tree());	
		trees.push_back(row);
	}
}

void Forest::train(Matrix &dataSet) {//fix me !!!
	printf("forest training");
	vector<int> all_columns = range(dataSet.columns() -1);
	for ( int i = 0; i < trees.size(); i++ ) {
		Tree &tree = trees[0][i];
		random_shuffle(all_columns.begin(), all_columns.end());
		vector<int> subset = slice(all_columns, 0, n_features);
		//tree.buildTree(dataSet, subset);
	}
}

int Forest::predictRow(vector<float> &row) { //okay
	//printf("predicting row!\n");
	float maxSum = 0;
	int label = 1;	
	for ( int i = 0; i < CLASSES_NUM - 1; i++ ){
		float sum = 0;;
		for ( int treeIndex = 0; treeIndex < n_trees; treeIndex++ ){
			Tree &tree = trees[i][treeIndex];
			float distribution = tree.predict(row);
			sum += distribution;
		}
		if ( sum > maxSum ) {
			maxSum = sum;
			label = i + 1;
		}
	}
	return label;
}

vector<int> Forest::predict(Matrix &dataSet, string resultfile) {//okay
	ofstream outfile;
	outfile.open(resultfile.c_str());
	outfile << "Id,label" << endl;

	cout << "*************Predicting********" << endl;
	vector<int> results(dataSet.rows(), 0);
	int errCount = 0;
	for ( int i = 0; i < dataSet.rows(); i++ ){
		int predictVal = predictRow(dataSet[i]);
		results[i] = predictVal;
	}

	printf("*******train number: %d\n", dataSet.rows());
	for ( int i = 0; i < results.size(); i++ )
		outfile << i << ',' << results[i] << endl;
	return results;
}
//***********parallelforest**********************************
ParallelForest::ParallelForest() {//okay
	init(100, 10);
	n_threads = 4;
}

ParallelForest::ParallelForest(int n_trees, int n_features, int n_threads) {
	printf("parallel forest has been build with %d trees,  %d features, %d threads \n", n_trees, n_features, n_threads);
	this->n_threads = n_threads;
	init(n_trees, n_features);
}

struct Args {//okay
	Matrix *matrix;
	vector<float> *labels;
	Tree *tree;
	vector<int> *subset;
	int *n_columns;
};

void *training_thread(void* void_ptr) {// okay
	Args *args = (Args*)void_ptr;
	args->tree->buildTree(*args->matrix, *args->labels, *args->subset, *args->n_columns);
	return NULL;
}
void ParallelForest::train(Matrix &dataSet) {//okay
	printf("parallel forest training with %zu trees and %d threads\n", trees[0].size(), n_threads);
	vector<int> subsetsRow;
	vector<int> testRow;

	sample_with_left(range(dataSet.rows()), int(0.9 * dataSet.rows()), subsetsRow, testRow);
	Matrix subDataSet = dataSet.submatrix(subsetsRow, range(dataSet.columns()));//for training 
	Matrix crossTestSet = dataSet.submatrix(testRow, range(dataSet.columns()));// for testing 

	Matrix crossTestLabel = dataSet.submatrix(testRow, range(dataSet.columns() - 1, dataSet.columns()));
	vector<float> testLabel = crossTestLabel.column(-1);

	vector<vector<float> >softmax = softMax(subDataSet);

	for ( int i = 0; i < CLASSES_NUM - 1; i++ ) {//26
		printf("******in class_num %d ********\n\n", i);
		train_regression(subDataSet, softmax[i], i);
	}
	printf("all tree build**************\n\n");
	printf("90%% data for cross validation");

	crossPredict(subDataSet, crossTestSet, testLabel);
}

vector<vector<float> > ParallelForest::softMax(Matrix &trainData) {//okay
	printf("softmax!....................\n");
	vector<vector<float> > softmax;
	for ( int i = 0; i < CLASSES_NUM - 1; i ++ ) {
		vector<float> row(trainData.rows());
		for ( int j = 0; j < trainData.rows(); j++ ) {
			int label = trainData[j][trainData[0].size() - 1];
			if ( label - 1 == i )
				row[j] = e / ( e + CLASSES_NUM - 2);
			else
				row[j] = 1 / ( e + CLASSES_NUM - 2);
		}
		softmax.push_back(row);
	}
	for ( int i = 0; i < CLASSES_NUM -1; i++ )
		cout << softmax[i][0] << ' ';
	cout << endl;
	return softmax;
}

void ParallelForest::train_regression(Matrix &dataSet, vector<float> &labels, int class_num) {//okay
    printf("train with regression tree!\n");
	void *pool = pool_start(&training_thread, n_threads);
	vector<int> all_columns = range(dataSet.columns() - 1);
	vector<vector<int> > subsetsCol(n_trees);
	for ( int j = 0; j < n_trees; j++ ) {
		cout << j << "tree" << endl;
		Tree &tree = trees[class_num][j];	
		//sample(all_columns, n_features, subsetsCol[j]);
		subsetsCol[j] = all_columns;
		struct Args *args = new struct Args;
		args->matrix = &dataSet;//the same in all tree
		args->labels = &labels;
		args->tree = &tree;
		args->subset = &subsetsCol[j];//all_columns
		args->n_columns = &n_features;
		pool_enqueue(pool,args, true);
	}
	pool_wait(pool);
	pool_end(pool);
}
void ParallelForest::crossPredict(Matrix &trainDataSet, Matrix &testDataSet, vector<float> &labels) {
	int errCount = 0;
	for ( int i = 0; i < trainDataSet.rows(); i++ ) {
		int label = predictRow(trainDataSet[i]);
		int real = trainDataSet[i][trainDataSet[0].size()-1];
		if ( label != real)
			errCount++;
	}
	float errRate = float(errCount) / trainDataSet.rows();
	errCount = 0;
	printf("cross test number: %d, error rate: %f\n", trainDataSet.rows(), errRate);
	for ( int i = 0; i < testDataSet.rows(); i++ ) {
		int label = predictRow(testDataSet[i]);		
		if ( label != int(labels[i]))
			errCount++;
	}
	errRate = float(errCount) / testDataSet.rows();
	printf("cross test number: %d, error rate: %f\n", testDataSet.rows(), errRate);
}

