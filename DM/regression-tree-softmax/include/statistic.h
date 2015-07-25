/*************************************************************************
	> File Name: statistic.h
	> Author: GoYchen
	> Mail: GoYchen@foxmail.com 
	> Created Time: Thu 11 Jun 2015 10:21:43 AM CST
 ************************************************************************/
#ifndef STATISTIC_H
#define STATISTIC_H

#include <algorithm>
#include <map>
#include <iostream>
#include <cstdio>
#include <vector>
#include <cassert>

using namespace std;

float sum(const vector<float> &list);
float sum_squared(const vector<float> &list);
float mean(const vector<float> &list);
float mode(const vector<float> &list);
float variance(const vector<float> &list);
float inner_product(const vector<float> &dist1, const vector<float> &dist2);
void basic_linear_regression(const vector<float> &x, const vector<float> &dist2);
float sum_of_square_error(const vector<float> &x, const vector<float> &y, float m, float b);
//vector<int> list_to_discrete(const vector<float> &list, int num_classes = 2);
vector<float> discrete_p_values(const vector<float> &list, int num_classes);
void add_list(vector<int> &list1, vector<int> &list2);
void test_regression();

template<typename T>
int max_index(vector<T> list) {
	assert(list.size() > 0);
	int index = 0;
	T biggest = list[index];
	for ( int i = 1; i < list.size(); i++){
		T value = list[i];
		if ( value > biggest ) {
			index = i;
			biggest = value;
		}
	}
}
template<typename T>//okay
void sample(vector<T> sampling_list, int n, vector<T> &result_list) {
	assert(n < sampling_list.size());
	random_shuffle(sampling_list.begin(), sampling_list.end());
	result_list.empty();
	for ( int i = 0; i < n; i++ )
		result_list.push_back(sampling_list[i]);
}
template<typename T>//okay
void sample_with_left(vector<T> sampling_list, int n, vector<T> &result_list, vector<T> &left_list) {
	assert(n < sampling_list.size());
	random_shuffle(sampling_list.begin(), sampling_list.end());
	result_list.empty();
	for ( int i = 0; i < n; i++ )
		result_list.push_back(sampling_list[i]);
	for ( int i = n; i < sampling_list.size(); i++ )
		left_list.push_back(sampling_list[i]);
}

template<typename T>
void sample_with_replacement(vector<T> sampling_list, int n, vector<T> &result_list) {
	result_list.empty();
	int size = sampling_list.size();
	for ( int i = 0; i < n; i++ ){
		int index = rand() % size;
		result_list.push_back(sampling_list[index]);
	}
}

#include <algorithm>
#include <functional>
template <typename T>
vector<T> operator+(const vector<T> &a, const vector<T> &b){
	assert(a.size() == b.size());
	vector<T> result;
	result.reserve(a.size());
	transform(a.begin(), a.end(), b.begin(), back_inserter(result), plus<T>());
	return result;
}
#endif

