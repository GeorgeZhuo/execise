// Sat Dec  6 17:06:52 2014
// george@NOSPAM.Phycles

/*
 * this the dynamic programming problem of 
 * the longest increasing subsequence
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int Number;
    int sequence[200];
    int d[200];
    int max = 1;
    cin >> Number;
    
    for (int i = 0; i < Number; ++i) {
	cin >> sequence[i];

    }
        
    for (int i = 0; i < Number; ++i) {
	d[i] = 1;

	for (int j = 0; j < i; ++j) {
	    if (sequence[i] >= sequence[j] && d[j] + 1 > d[i] )
		d[i] = d[j] + 1;
	}
	if (d[i] > max) {
	    max = d[i];
	}
    }

    cout << max << endl;
    return 0;
}

