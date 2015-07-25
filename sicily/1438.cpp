// Fri Oct 24 17:05:52 2014
// george@NOSPAM.Phycles

#include <iostream>
#include <algorithm>

using namespace std;

bool cmp(int a, int b) {
    return a > b;
}

int main(int argc, char *argv[]) {
     
    int scenario;
    cin >> scenario;
    
    while (scenario--) {

	int number;
	int items[20001];
	int discount = 0;

	cin >> number;
	for (int i = 0; i < number; i++) {
	    cin >> items[i];
	}

	sort(items, items + number, cmp);

	for (int i = 2; i < number; i += 3) {
	    discount += items[i];
	}

	cout << discount << endl;
    }
    
    return 0;
}
