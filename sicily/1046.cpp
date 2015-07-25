// Mon Sep 29 13:54:03 2014
// george@NOSPAM.Phycles

/**
 * sicily 1046 plane spotting
 */

#include <iostream>
#include <algorithm>

using namespace std;

struct node {
    
    int start;
    int end;
    double average;
};

bool cmp(node a, node b) {
    
    if (a.average > b.average) {
	return true;
    } else if (a.average < b.average) {
	return false;
    } else {
	if ((a.end - a.start) > (b.end - b.start)) {
	    return true;
	} else if ((a.end - a.start) < (b.end - b.start)) {
	    return false;
	} else {
	    return (a.end < b.end);
	}
	
    }
}

int main () {

    int runs;
    int quarNum;
    int perNum;
    int minQuar;
    int quarter[301];
    cin >> runs;
    
    for (int run = 1; run <= runs; run++) {
	cin >> quarNum >> perNum >> minQuar;

	for (int i = 1; i <= quarNum; i++) {
	    cin >> quarter[i];
	}
	node period[46000];
	int index = 0;
	for (int i = 1; i <= quarNum - minQuar + 1; i++) {
	    
	    for (int j = minQuar + i - 1; j <= quarNum; j++) {

		double sum = 0;
		for (int k = i; k <= j; k++) {
		    sum += quarter[k];
		}
		period[index].start = i;
		period[index].end = j;
		period[index++].average =(double)(sum / (j - i + 1));
				
	    }
	}
	
	sort(period, period + index, cmp);

	cout << "Result for run " << run << ":" << endl;
	for (int i = 0; i < perNum && i < index; i++) {
	    cout << period[i].start << "-"
		 << period[i].end << endl;

	}
    }
    return 0;
}
