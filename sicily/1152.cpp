// Mon Oct 20 15:17:11 2014
// george@NOSPAM.Phycles

/*
 * sicily 1152
*/

#include <iostream>
#include <memory.h>

using namespace std;

struct node {
    int x, y;
    node (int a = 0, int b = 0) {
	x = a;
	y = b;
    }
    node (const node &position) {
	x = position.x;
	y = position.y;
    }
};

bool isVisited[5][6];
node path[30];
bool isEnd;
int count;

const node direction[8] = {
    node(1, -2), node(2, -1), node(2, 1), node(1, 2),
    node(-1, 2), node(-2, 1), node(-2, -1), node(-1, -2)
};

bool isValid(const node &position) {
    return position.x >= 0 && position.x < 5
	&& position.y >= 0 && position.y < 6;
}

void dfs(node start) {
    
    if (count >= 29) {
	isEnd = true;
	return;
    }

    for (int i = 0; i < 8; i++) {
	
	node temp(start.x + direction[i].x, start.y + direction[i].y);
	if (isValid(temp) && !isVisited[temp.x][temp.y]) {

	    path[++count] = temp;
	    isVisited[temp.x][temp.y] = true;
	
	    dfs(temp);

	    if (isEnd) {
		return;
	    } else {
		isVisited[temp.x][temp.y] = false;
		--count;
	    }
	}
    }
    
}

int main () {
    
    int source;
    
    while (cin >> source, source != -1) {

	memset(isVisited, false, sizeof(isVisited));
	isEnd = false;
	count = 0;
	node start((source - 1) / 6, (source - 1) % 6);
	path[0] = start;
	isVisited[start.x][start.y] = true;

	dfs(start);

	cout << path[0].x * 6 + path[0].y + 1;
	for (int i = 1; i < 30; i++) {
	    
	    cout << " " << path[i].x * 6 + path[i].y + 1;
	}
	
	cout << endl;
    }

}
