/*************************************************************************
	> File Name: statistic.cpp
	> Author: GoYchen
	> Mail: GoYchen@foxmail.com 
	> Created Time: Thu 11 Jun 2015 10:23:37 AM CST
 ************************************************************************/


#include "statistic.h"

using namespace std;

float sum(const vector<float> &list){
	float result = 0.0;
	for ( int i = 0; i < list.size(); i++ ) {
		result += list[i];
	}
	return result;
}

float sum_squared(const vector<float> &list) {
	float result = 0.0;
	for ( int i = 0; i < list.size(); i++ ) {
		result += list[i] * list[i];
	}
	return result;
}
float mean(const vector<float> &list) {
	return sum(list) / list.size();
}

float variance(const vector<float> &list) {
	float meanVal = mean(list);
	float var = 0;
	for ( int i = 0; i < list.size(); i++ ){
		var+= (list[i] - meanVal) * (list[i] - meanVal);
	}
	return var * list.size();
}

float mode(const vector<float> &array) {
	int arraySize = array.size();
	int* repetition = new int[arraySize];
	for ( int i = 0; i < arraySize; i++ ) {
		repetition[i] = 0;
		int j = 0;
		while ( (j < i) && (array[i] != array[j]) ) {
				if ( array[i] != array[j] )
					j++;
		}	
		repetition[i]++;
	}
	int maxIndex = 0;
	for ( int i = 1; i < arraySize; i++ ) {
		if ( repetition[i] > repetition[maxIndex] )
			maxIndex = i;
	}
	delete [] repetition;
	return array[maxIndex];
}
float inner_product(const vector<float>& list1, const vector<float> &list2) {
	float result = 0.0;
	for ( int i = 0; i < list1.size(); i++)
		result += list1[i] * list2[i];
	return result;
}

void basic_linear_regression(const vector<float> &x, const vector<float> &y, float &m, float &b) {
	int num = x.size();
	float sumX = sum(x);
	float sumY = sum(y);
	float sumXSquared = sum_squared(x);
	float XY = inner_product(x, y);
	float numerator = (XY - (sumX * sumY) / num);
	float denominator = (sumXSquared - ((sumX * sumX) / num));
	if ( denominator == 0.0 ) 
		m = 0.0;
	else
		m = numerator / denominator;
	b = (sumY - m * sumX) / num;
}

float sum_of_square_error(const vector<float> &x, const vector<float> &y, float m, float b) {
	float result = 0.0;
	for ( int i = 0; i < x.size(); i++ ) {
		float predict = m * x[i] + b;
		result += (y[i] - predict) * (y[i] - predict);
	}
	return result;
}

void test_regression() {
	vector<float> x;
	vector<float> y;
	x.push_back(0.0); x.push_back(1.0); x.push_back(2.0);
	y.push_back(3.0); y.push_back(5.0); y.push_back(8.0);
	float m, b;
	basic_linear_regression(x, y, m, b);
	printf ("y = %f * x + %f \n", m, b);
}

/*vector<int> list_to_discrete(const vector<float> &list, int num_classes) {
	vector<int> classes(num_classes, 0);
	for ( int i = 0; i < list.size(); i++) {
		int cls = (int)list[i];
		assert(cls >= 0 && cls < num_classes);
		classes[cls]++;
	}
	return classes;
}*/

vector<float> discrete_p_values(const vector<float> &list, int num_classes) {//okay
	vector<int> classes(num_classes, 0);
	for ( int i = 0; i < list.size(); i++) {
		int label = (int)list[i];
		assert(label >= 0 && label < num_classes);
		classes[label]++;
	}
	vector<float> p_values(num_classes, 0);
	for ( int i = 0; i < num_classes; i++ ) {
		int count = classes[i];
		float p = ((float)count) / list.size();
		p_values[i] = p;
		//printf(" class: %d, frequency: %f", i, p);
	}
	return p_values;
}

void add_list(vector<int> &list1, vector<int> &list2) {
	if ( list1.size() == 0 ) {
		for ( int i = 0; i < list2.size(); i++ ) {
			list1.push_back(0);
		}
	}
	assert(list1.size() == list2.size());
	for ( int i = 0; i < list1.size(); i++ ) {
		list1[i] += list2[i];
	}
}
