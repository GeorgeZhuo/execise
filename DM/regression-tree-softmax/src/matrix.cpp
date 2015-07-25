/*************************************************************************
	> File Name: dataMatrix.cpp
	> Author: GoYchen
	> Mail: GoYchen@foxmail.com 
	> Created Time: Thu 11 Jun 2015 10:17:25 AM CST
 ************************************************************************/

#include "matrix.h"

using namespace std;

Matrix::Matrix(){
}

void Matrix::load(string filename, bool has_column_labels, bool has_row_labels){//okay
	ifstream infile(filename.c_str());
	string line;
	int lineNumber = 0;
	while(getline(infile, line)) {
		vector<string> lineArr = split_string(line, ",");
		if ( lineArr.size() == 0 ){
			printf("Matrix.load(): skipping blank line on line #%d!\n", lineNumber);
			lineNumber++; 
			continue;
		}
		if ( has_column_labels && lineNumber == 0 ) {
			columnLabels = lineArr; 
			lineNumber++; 
			continue;
		}
		else {
			//lineArr.erase(lineArr.begin()); //remove ID
			if ( has_row_labels ) {
				int rowSize = lineArr.size();
				rowLabels.push_back(lineArr[0]);
				lineArr.erase(lineArr.begin());
			}
			vector<float> row;
			for ( int i = 0; i < lineArr.size(); i++ ) {
				float element = atof(lineArr[i].c_str());
				row.push_back(element);
			}
			elements.push_back(row);
		}
		lineNumber++;
	}
	for ( int i = 0; i < 5; i++)
		cout << elements[i][elements[0].size() - 1] << ' ';
	cout << endl;
	infile.close();
}

int Matrix::columns() {//okay
	if ( (int)elements.size() == 0 )
		return 0;
	else
		return elements[0].size();
}

int Matrix::rows() {//okay
	return elements.size();
}

vector<float>& Matrix::operator[](int i) {//okay
	assert( i < elements.size() );
	return elements[i];
}

vector<float> Matrix::column(int index) {//okay
	vector<float> result;
	if ( index < 0 )
		index += columns();
	//assert( index < columns() );
	for ( int i = 0; i < rows(); i++ ) {
		float element = elements[i][index];
		result.push_back(element);
	}
	return result;
}

Matrix Matrix::submatrix(vector<int> rows, vector<int> columns){//okay
	Matrix subMat;
	for ( int j = 0; j < columns.size(); j++ )
		subMat.columnLabels.push_back(columnLabels[j]);
	for ( int i = 0; i < rows.size(); i ++ ) {
		int y = rows[i];
		subMat.rowLabels.push_back(rowLabels[y]);
		vector<float> row;
		for ( int j = 0; j < columns.size(); j++ ) {
			int x = columns[j];
			row.push_back(elements[y][x]);
		}
		subMat.elements.push_back(row);
	}
	return subMat;
}

void Matrix::split(int columnIndex, float value, Matrix &subm1, Matrix &subm2) {
	vector<int> m1RowIndex;
	vector<int> m2RowIndex;
	for ( int i = 0; i < elements.size(); i++ ) {
		float element = elements[i][columnIndex];
		if ( element < value)
			m1RowIndex.push_back(i);
		else
			m2RowIndex.push_back(i);
	}
	subm1 = submatrix(m1RowIndex, range(columns()));
	subm2 = submatrix(m2RowIndex, range(columns()));
}

void Matrix::splitRowAndLabel(int columnIndex, float value, Matrix &subm1, Matrix &subm2, vector<float> &labels, vector<float> &l1, vector<float> &l2) {
	if  ( columnIndex < 0 )
		printf("bad features!..\n");
	for ( int i = 0; i < elements.size(); i++ ) {
		if ( elements[i][columnIndex] < value ) {
			subm1.elements.push_back(elements[i]);	
			l1.push_back(labels[i]);
		}
		else {
			subm2.elements.push_back(elements[i]);
			l2.push_back(labels[i]);
		}
	}	

}
Matrix Matrix::shuffled() {
	vector<int> rowIndices = range(rows());
	random_shuffle(rowIndices.begin(), rowIndices.end());
	return submatrix(rowIndices, range(columns()));
}

void Matrix::merge_rows(Matrix &otherMat) {
	if ( columns() == 0 )
		columnLabels = otherMat.columnLabels;
	assert( columns() == otherMat.columns() || rows() == 0 );
	for ( int i = 0; i < otherMat.rows(); i++ ) {
		vector<float> row = otherMat.elements[i];
		elements.push_back(row);
		rowLabels.push_back(otherMat.rowLabels[i]);
	}
}
