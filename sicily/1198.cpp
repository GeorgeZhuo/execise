// Mon Sep 29 15:37:03 2014
// george@NOSPAM.Phycles

/*
 * sicily 1198
*/

#include <iostream>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

bool comp(string a, string b) {
    
    for (int i = 0; i < a.size(); i++) {
	
	if (a[i] < b[i]) {
	    return true;
	} else if (a[i] > b[i]) {
	    return false;
	}
    }
}

int main () {

    int cases;
    int number;
    cin >> cases;

    while (cases--) {
	
	cin >> number;
	string subStr[number];
	string mini = "z";

	for (int i = 0; i < number; i++) {
	    cin >> subStr[i];
	}
	int index = 0;
	sort(subStr, subStr + number, comp);

	do {
	    string temp;
	    for (int i = 0; i < number; i++) {
		temp += subStr[i];
	    }
	    if (comp(temp, mini)) {
		mini = temp;
	    }
		
	} while (next_permutation(subStr, subStr + number));
	
	cout << mini << endl;
    }
}
