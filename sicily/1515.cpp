
// Mon Oct 13 13:08:26 2014
// george@NOSPAM.Phycles

/*
 * sicily 1515
*/

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <memory.h>

using namespace std;

bool isVisited[40320];
int factory[] = {1, 1, 2, 6, 24, 120, 720, 5040};

struct node {

    vector<int> status;
    string path;
};

// operation A
vector<int> opA(vector<int> status) {
    
     vector<int> result(8, 0);
    result[0] = status[2];
    result[1] = status[3];
    result[2] = status[0];
    result[3] = status[1];
    result[4] = status[6];
    result[5] = status[7];
    result[6] = status[4];
    result[7] = status[5];
    return result;
}

// operation B
vector<int> opB(vector<int> status) {
    
    vector<int> result(8, 0);
     result[0] = status[1];
    result[1] = status[2];
    result[2] = status[3];
    result[3] = status[0];
    result[4] = status[5];
    result[5] = status[6];
    result[6] = status[7];
    result[7] = status[4];


    return result;
}

// operation C
vector<int> opC(vector<int> status) {
    
    vector<int> result(8, 0);
    
    result[0] = status[0];
    result[1] = status[2];
    result[2] = status[6];
    result[3] = status[3];
    result[4] = status[4];
    result[5] = status[1];
    result[6] = status[5];
    result[7] = status[7];
    return result;
}

// cantor 
int cantor(vector<int> status) {

    int couter;
    int result = 0;
    
    for (int i = 0; i < 7; i++) {
	couter = 0;
	for (int j = i + 1; j < 8; j++) {
	    if (status[i] < status[j]) {
	
		couter++;
	    }
	}

	result += couter * factory[7 - i];
    }

    return result;
}
node BFS(int target[], int N) {

    queue<node> list;
    node original;
    int temp[] = {1, 2, 3, 4, 5, 6, 7, 8};
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
	int index;
	// A operation
	temp.status = opA(current.status);
	temp.path = current.path + "A";
	index = cantor(temp.status);
	if (!isVisited[index]) {
	    list.push(temp);
	    isVisited[index] = true;
	}
	
	// B operation
	temp.status = opB(current.status);
	temp.path = current.path + "B";
	index = cantor(temp.status);
	if (!isVisited[index]) {
	    list.push(temp);
	    isVisited[index] = true;
	}

	// C operation
	temp.status = opC(current.status);
	temp.path = current.path + "C";
	index = cantor(temp.status);
	if (!isVisited[index]) {
	    list.push(temp);
	    isVisited[index] = true;
	}

	list.pop();
    }
    
}

int main () {

    int N;
    int target[8];
    
    while (cin >> N, N!= -1) {

	memset(isVisited, false, sizeof(isVisited));

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
