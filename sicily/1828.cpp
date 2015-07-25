// Tue Dec 23 10:05:16 2014
// george@NOSPAM.Phycles

#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>

#define IF 1000010
using namespace std;

int main(int argc, char *argv[])
{
    int S1[510];
    int S2[510];
    int dp[510][510];
    int dis[510][510];
    int T, N, M;
    cin >> T;
    while(T--) {
	cin >> N >> M;
	for (int i = 0; i < N; ++i) {
	    cin >> S1[i];
	}
	for (int i = 0; i < M; ++i) {
	    cin >> S2[i];
	}
	
	sort(S1, S1 + N);
	sort(S2, S2 + M);

	for (int i = 0; i < N; ++i) {
	    for (int j = 0; j < M; ++j) {
		dp[i][j] = IF;
	    }
	
	}
	for (int i = 0; i < N; ++i) {
	    for (int j = 0; j < M; ++j) {
		dis[i][j] = abs(S1[i] - S2[j]);
	    }
	}

	for (int i = 0; i < N; ++i) {
	    if (i == 0) {
		dp[i][i] = dis[0][0];
	    } else {
	    
		dp[i][i] = dp[i - 1][i - 1] + dis[i][i];
	    }
	}
	
	for (int i = 0; i < N; ++i) {
	    for (int j = i + 1; j < M; ++j) {
		dp[i][j] = min(dp[i][j - 1], (dp[i -1][j -1] + dis[i][j]));
	    }
	}

	cout << dp[N - 1][M -1] << endl;
    }
    
    return 0;
}

