// Sat Dec  6 17:48:31 2014
// george@NOSPAM.Phycles

/*
 * shortest path problem
*/

#include <iostream>

using namespace std;

#define INF 1000000

int main(int argc, char *argv[])
{
    int Number;
    int graph[1000][1000];
    int path[1000];

    cin >> Number;
    for (int i = 0; i < Number; ++i) {
	for (int j = 0; j < Number; ++j) {
	    cin >> graph[i][j];
	}
    }
    
    for (int i = 0; i < Number; ++i) {
	if (graph[0][i] != 0)
	    path[i] = graph[0][i];
	else
	    path[i] = INF;
    }

    for (int i = 1; i < Number; ++i) {
	for (int j = i + 1; j < Number; ++j) {
	    
	    // there is a edge
	    if (graph[i][j] != 0 && path[i] != INF) {
		
		if (graph[i][j] + path[i] < path[j])
		    path[j] = graph[i][j] + path[i];
	    }
		
	}
	
    }
    for (int i = 0; i < Number; ++i) {
	cout << path[i] << " ";
	
    }
    return 0;
}

