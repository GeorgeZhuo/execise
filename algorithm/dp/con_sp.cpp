// Sat Dec  6 20:30:59 2014
// george@NOSPAM.Phycles

/*
 * the shortest path problem with the 
 * condition
*/

#include <iostream>
#define INF 100000

using namespace std;

int main(int argc, char *argv[])
{
    bool state[100][100];
    int Min[100][100];
    int graph[100][100];
    int s[100];

    int money;
    int size;

    cin >> size >> money;

    for (int i = 0; i < size; ++i) {
	cin >> s[i];
	
    }
    for (int i = 0; i < size; ++i) {
	for (int j = 0; j < size; ++j) {
	    cin >> graph[i][j];
	    Min[i][j] = INF;
	    state[i][j] = false;
	}
	
    }
    
    int min = INF;
    int k = INF;
    int l = INF;
    while (true) {
	
	for (int i = 0; i < size; ++i) {
	    for (int j = 0; j < size; ++j) {
		if ((!state[i][j]) && Min[i][j] < min) {
		    min = Min[i][j];
		    k = i;
		    l = j;
		}
	    }
	}
	if (k == INF) {
	    break;
	}

	state[k][l] = true;
	for (int i = 0; i < size; ++i) {
	    if (graph[k][i] != 0) {
		if ((l - s[i] >= 0) && 
		    (Min[i][l - s[i]] > Min[k][l] + graph[k][i])) {
		    Min[i][l - s[i]] = Min[k][l] + graph[k][i];
		}
	    }
	}
    }
    
    for (int i = 0; i < size; ++i) {
	cout << Min[size - 1][i] << " ";
    }
    return 0;
}

