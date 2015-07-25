// Fri Dec 19 19:54:14 2014
// george@NOSPAM.Phycles

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int T;
    int N;
    int A[1002];
    int a, b;

    cin >> T;
    while (T--) {

	cin >> N;
	for (int i = 1; i <= N; ++i) {
	    cin >> A[i];
	}
	cin >> a >> b;
	cout << A[a] + A[b] << endl;
    }
    return 0;
}
