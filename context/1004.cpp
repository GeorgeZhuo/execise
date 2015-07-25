// Fri Dec 19 19:45:21 2014
// george@NOSPAM.Phycles

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int N;
    long long temp;
    long long max;
    while (cin >> N &&  N != 0) {
	cin >> max;
	for (int i = 1; i < N; ++i) {
	    cin >> temp;
	    if (temp > max) {
		max = temp;
	    }
	}
	cout << max << endl;
    }

    return 0;
}

