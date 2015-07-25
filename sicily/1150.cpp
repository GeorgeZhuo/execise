// Mon Oct 13 13:08:26 2014
// george@NOSPAM.Phycles

/*
 * sicily 1150
*/

#include <iostream>
#include <string>
#include <queue>
#include <vector>

using namespace std;
struct node {

    vector<int> status;
    string path;
};

vector<int> opA(vector<int> status) {
    
    vector<int> result(8, 0);
    for (int i = 0; i < 4; i++) {
	result[i + 4] = status[i];
    }
    for (int i = 4; i < 8; i++) {
	result[i - 4] = status[i];
    }
    return result;
}

vector<int> opB(vector<int> status) {
    
    vector<int> result(8, 0);
    result[0] = status[3];
    result[1] = status[0];
    result[2] = status[1];
    result[3] = status[2];
    result[4] = status[7];
    result[5] = status[4];
    result[6] = status[5];
    result[7] = status[6];

    return result;
}

vector<int> opC(vector<int> status) {
    
    vector<int> result(8, 0);
    
    result[0] = status[0];
    result[1] = status[5];
    result[2] = status[1];
    result[3] = status[3];
    result[4] = status[4];
    result[5] = status[6];
    result[6] = status[2];
    result[7] = status[7];

    return result;
}

node BFS(int target[], int N) {

    queue<node> list;
    node original;
    int temp[] = {1, 2, 3, 4, 8, 7, 6, 5};
    vector<int> origin(temp, temp + 8);
    original.status = origin;
    original.path = "";

    list.push(original);

    while (!list.empty()) {
	
	node current = list.front();
	
	if (equal(current.status.begin(), current.status.end(), target)) {
	    return current;
	}
	if (current.path.size() > N) {
	    current.path = "";
	    return current;
	}

	node temp;
	// A operation
	temp.status = opA(current.status);
	temp.path = current.path + "A";
	list.push(temp);
	
	// B operation
	temp.status = opB(current.status);
	temp.path = current.path + "B";
	list.push(temp);

	// C operation
	temp.status = opC(current.status);
	temp.path = current.path + "C";
	list.push(temp);

	list.pop();
    }
    
}

int main () {

    int N;
    int target[8];
    
    while (cin >> N, N!= -1) {

	for (int i = 0; i < 8; i++) {
	    
	    cin >> target[i];
	}

	node final = BFS(target, N);
	if (equal(final.status.begin(), final.status.end(), target)) {
	    cout << final.path.size() << " " << final.path << endl;
	} else {
	    cout << -1 << endl;
	}
    }

    return 0;
}
