// Tue Jan  6 09:49:37 2015
// george@NOSPAM.Phycles

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{
    int T;
    string vote, s;
    string rank[120];

    s = "ABCDE";
    rank[0] = s;
    for (int i = 1; next_permutation(s.begin(), s.end()); ++i) {
	rank[i] = s;
    }

    while (cin >> T && T) {
	int value[120] = {0};
	while (T--) {
	    cin >> vote;
	    for (int i = 0; i < 120; ++i) {

		for (int j = 0; j < 5; j++) {
		    for (int k = j + 1; k < 5; ++k) {
			if (vote.find(rank[i][j]) > vote.find(rank[i][k])) {
			    value[i]++;
			}
			
		    }
		}
	    }
	}
	
	int min = 0;
	for (int i = 1; i < 120; ++i) {

	    if (value[i] < value[min]) {
		min = i;
	    }
	}

	cout << rank[min] << " is the median ranking with value "
	     << value[min] << "." << endl;
    }
}
