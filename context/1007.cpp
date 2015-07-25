// Fri Dec 19 20:23:27 2014
// george@NOSPAM.Phycles

#include <iostream>
#include <algorithm>

using namespace std;

int N;

void travel(const int Tree[][3], int index) {
    
    int node;
    for (int i = 0; i < N; ++i) {
	if (Tree[i][0] == index) {
	    node = i;
	}
    }

    if (Tree[node][1] != 0) {

	travel(Tree, Tree[node][1]);
    }
    if (Tree[node][2] != 0) {

	travel(Tree, Tree[node][2]);
    } 
    
    cout << Tree[node][0] << endl;
    return;
    
}

int main(int argc, char *argv[])
{

    int A[101][3];

    while (cin >> N && N) {

	for (int i = 0; i < N; ++i) {
	    cin >> A[i][0] >> A[i][1] >> A[i][2];
	}
	
	travel(A, A[0][0]);
    }
    return 0;
}

