// Fri Jan  9 16:26:29 2015

#include <iostream>
#include <queue>

using namespace std;

struct q {
    int pos;
    int prio;
    q (int a, int b) {
	pos = a;
	prio = b;
    }
};

bool highPri(queue<q> A,int a) {

    while (!A.empty()) {
	q top = A.front();
	A.pop();
	if (top.prio > a)
	    return true;
    }
    
    return false;
    
    
}
int main(int argc, char *argv[])
{
    int T;
    cin >> T;
    int position;
    int queueNum;
    int temp;

    while (T--) {

	queue<q> Q;
	int time = 1;
	cin >> queueNum >> position;
	for (int i = 0; i < queueNum; ++i) {
	    cin >> temp;
	    q a(i, temp);
	    Q.push(a);
	}
	
	while (!Q.empty()) {

	    q top = Q.front();
	    Q.pop();
	   
	    if (highPri(Q, top.prio)) {
		Q.push(top);
	    } else {

		if (top.pos == position) {
		    break;
		} else {
		    time++;
		}
	    }
	}
	cout << time << endl;
    }
    return 0;
}
