// Fri Dec 19 19:25:34 2014
// george@NOSPAM.Phycles

#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;
int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int *)b);
}

int main(int argc, char *argv[])
{
    
    int T;
    cin >> T;
    
    int A[100001];
    while (T--) {
	size_t N;
	cin >> N;
	for (int i = 0; i < N; ++i) {
	    scanf("%d\n", &A[i]);
	}

	qsort(A, N, sizeof(int), cmp);

	for (int i = 0; i < N; ++i) {
	    printf("%d\n", A[i]);
	}
    }
    return 0;
}
