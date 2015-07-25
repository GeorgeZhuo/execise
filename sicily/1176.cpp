// Mon Sep 29 16:48:23 2014
// george@NOSPAM.Phycles

/*
 * sicily 1176
*/
#include <iostream>
#include <algorithm>
#include <memory.h>

int card[1001];
int record[1001][1001];

using namespace std;

int dy(int left, int right) {

    if (record[left][right] == 0) {
	// only two numbers
	if (left + 1 == right) {
	    
	    return max(card[left], card[right]);
	} else {
	    
	    // first player choose the left number
	    int leftNum = card[left];
	    if (card[left + 1] >= card[right]) {
		leftNum += dy(left + 2, right);
	    } else {
		leftNum += dy(left + 1, right - 1);
	    }

	    // first player choose the right number
	    int rightNum = card[right];
	    if (card[left] >= card[right - 1]) {
		rightNum += dy(left + 1, right - 1);
	    } else {
		rightNum += dy(left, right - 2);
	    }
	    
	    record[left][right] = max(leftNum, rightNum);
	}
    }

    return record[left][right];
}
int main () {

    int N;
    int gameNum = 1;
    while (cin >> N, N != 0) {
	
	memset(card, 0, sizeof(card));
	memset(record, 0, sizeof(record));

	int sum = 0;
	for (int i = 0; i < N; i++) {
	    
	    cin >> card[i];
	    sum += card[i];
	}
	
	int largest = dy(0, N - 1);
	
	cout << "In game " << gameNum 
	     << ", the greedy strategy might lose by as many as "
	     << largest - (sum - largest) << " points." << endl;

	gameNum++;
    }

    return 0;
}
