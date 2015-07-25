// Tue Jan  6 11:20:58 2015
// george@NOSPAM.Phycles

#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

vector<long long> result;

void compute(long long menNum) {

    long long most = pow(menNum, 0.5) + 1;
    bool flag = true;

    for (long long i = 2; i < most; ++i) {
	if (menNum % i == 0) {

	    flag = false;
	    compute(i);
	    compute(menNum / i);
	    break;
	}
	
    }
    if (flag) {
	result.push_back(menNum);
    }
}

int main(int argc, char *argv[])
{
    int prime[9] = {11, 23, 29, 37, 41, 43, 47, 53, 59};
    int k;
    long long number;

    cin >> k;
    for (int i = 0; i < 9 && prime[i] < k; ++i) {
	number =(long long)(pow(2, prime[i]) -1);

	result.clear();
	compute(number);

	if (result.size() == 1) {
	    continue;
	}

	sort(result.begin(), result.end());
	cout << result[0];
	for (int j = 1; j < result.size(); ++j) {
	    cout << " * " << result[j];
	}
	cout << " = " << number << " = ( 2 ^ " << prime[i] << " ) - 1" << endl;
	
    }

    return 0;
}
