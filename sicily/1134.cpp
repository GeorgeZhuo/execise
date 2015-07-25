// Fri Oct 24 16:30:01 2014
// george@NOSPAM.Phycles

#include <iostream>
#include <algorithm>

using namespace std;
struct node {
    
    long need;
    long hold;
};

bool cmp(node a, node b) {
    return a.need < b.need;
}

int main () {

    int number;
    int total;
    while (cin >> number >> total && number) {
	node children[10001];
	bool flag = true;
	for (int i = 0; i < number; i++ ) {
	
	    cin >> children[i].hold >> children[i].need;
	}

	sort(children, children + number, cmp);

	for (int i = 0; i < number; i++) {

	    if (total >= children[i].need) {
		total += children[i].hold;
	    } else {
		flag = false;
	    }
	}

	if (flag) {
	    cout << "YES" << endl;
	 } else {
	    cout << "NO" << endl;
	}
    }
}
