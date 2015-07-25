/*************************************************************************
	> File Name: dataMatrix.h
	> Author: GoYchen
	> Mail: GoYchen@foxmail.com 
	> Created Time: Thu 11 Jun 2015 10:16:59 AM CST
 ************************************************************************/
#ifndef MATRIX_H
#define MATRIX_H

#include <algorithm>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cassert>

#include "utility.h"
#include "statistic.h"

using namespace std;

class Matrix{
public:
	Matrix();
	void load(string filename, bool has_column_title = true, bool has_row_labels = true);
	//void save(string filename);

	int columns();
	int rows();
	vector<float> column(int index);
	Matrix submatrix(vector<int> rows, vector<int> columns);
	Matrix shuffled();
	void split(int columnIndex, float value, Matrix &subm1, Matrix &subm2);
	void splitRowAndLabel(int columnIndex, float value, Matrix &subm1, Matrix &subm2,vector<float> &labels, vector<float> &l1, vector<float> &l2);
	vector<float>& operator[](int i);
	//void append_column(vector<float> &col, string name = "");
	void merge_rows(Matrix &otherMat);
private:
	vector< vector<float> > elements;
	vector<string> columnLabels;
	vector<string> rowLabels;
};

#endif
