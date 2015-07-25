/*************************************************************************
	> File Name: utility.h
	> Author: GoYchen
	> Mail: GoYchen@foxmail.com 
	> Created Time: Thu 11 Jun 2015 10:27:33 AM CST
 ************************************************************************/

#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector<string> inline split_string(const string &source, const char *delimiter = ",", bool keepEmpty = false) {
	vector<string> results;
	size_t prev = 0;
	size_t next = 0;
	while ( (next = source.find_first_of(delimiter, prev)) != string::npos ){
		if ( keepEmpty || (next - prev != 0) )
			results.push_back(source.substr(prev, next - prev));	
		prev = next + 1;
	}
	if ( prev < source.size() )
		results.push_back(source.substr(prev));
	return results;
}

template<typename T>
string inline join(vector<T> &list, const char delimiter) {
	stringstream ss;
	for ( int i = 0; i < list.size(); i++ ) {
		ss << list[i];
		if ( i < list.size() -1) {
			ss << delimiter;
		}
	}
	return ss.str();
}

vector<int> inline merge(vector<int> a, vector<int> b) {
	for ( int i = 0; i < b.size(); i++ ) {
		a.push_back(b[i]);
	}
	return a;
}

vector<int> inline range(int start, int stop = -1, int step = 1) {
	vector<int> result;
	if ( stop == -1 ) {
		stop = start;
		start = 0;
	}
	for (int i = start; i < stop; i += step)
		result.push_back(i);
	return result;
}

#include <cassert>
template<typename T>
vector<T> inline slice(vector<T> list, int start = 0, int end = -1, int step = 1) {
	vector<T> result;
	start = (start > 0)? start: start + list.size();
	end = (end > 0)? end: end + list.size();
	assert(start <= end);
	for ( int i = start; i < end; i += step ){
		T element = list[i];
		result.push_back(element);
	}
	return result;
}

#include <algorithm>
#include <utility>

template<typename T>
void zip(vector<T> &A, vector<T> &B, vector<pair<T, T> > &zipped) {
	for (unsigned int i = 0; i < A.size(); i++ ) {
		zipped.push_back( make_pair(A[i], B[i]));
	}
}

template<typename T>
void unzip(vector<pair<T, T> > &zipped, vector<T> &A, vector<T> &B) {
	for ( unsigned int i = 0; i < A.size(); i++ ) {
		A[i] = zipped[i].first;
		B[i] = zipped[i].second;
	}
}

template<typename T>
bool pairCompare(const pair<T, T> &firstElem, const pair<T, T> &secondElem) {
	return firstElem.first < secondElem.first;
}
#endif
