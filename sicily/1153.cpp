// Mon Oct 20 15:17:11 2014
// george@NOSPAM.Phycles

/*
 * sicily 1153
 */

#include <iostream>
#include <memory.h>
#include <vector>
#include <algorithm>

using namespace std;

bool isVisited[8][8];
bool isEnd;
int counter;
int direction[8][2] = {
    -1,-2,-1,2,-2,1,-2,-1,1,2,1,-2,2,1,2,-1};


bool isValid(int x, int y) {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

int calDegree(int x, int y) {
    
    int deg = 0;
    for (int i = 0; i < 8; ++i) {
	
	int X = x + direction[i][0];
	int Y = y + direction[i][1];
	if (isValid(X, Y) && !isVisited[X][Y]) {
	    deg++;
	}
    } 
    
    return deg;
}

struct node {
    int x, y;
    int degree;
    node (int a = 0, int b = 0, int c = 0) {
	x = a;
	y = b;
	degree = calDegree(x, y);
    }
    node (const node &position) {
	x = position.x;
	y = position.y;
	degree = calDegree(x, y);
    }
};

node path[64];

bool cmp(node a, node b) {
    
    return a.degree < b.degree;
}
void dfs(node start) {
    
    vector<node> coodr;

    if (counter >= 63) {
	isEnd = true;
	return;
    }

    for (int i = 0; i < 8; i++) {
	
	node temp(start.x + direction[i][0], start.y + direction[i][1]);
	
	if (isValid(temp.x, temp.y) && !isVisited[temp.x][temp.y]) {
	    
	    coodr.push_back(temp);
	}
    }
	
    sort(coodr.begin(), coodr.end(), cmp);
    for (int i = 0; i < coodr.size(); i++) {
	path[++counter] = coodr[i];
	isVisited[coodr[i].x][coodr[i].y] = true;
	
	dfs(coodr[i]);

	if (isEnd) {
	    return;
	} else {
	    isVisited[coodr[i].x][coodr[i].y] = false;
	    --counter;
	}
    }
}

int main () {
    
    int source;
    
    while (cin >> source, source != -1) {

	memset(isVisited, false, sizeof(isVisited));
	isEnd = false;
	counter = 0;
	node start((source - 1) / 8, (source - 1) % 8);
	path[0] = start;
	isVisited[start.x][start.y] = true;

	dfs(start);

	cout << path[0].x * 8 + path[0].y + 1;
	for (int i = 1; i < 64; i++) {
	    
	    cout << " " << path[i].x * 8 + path[i].y + 1;
	}
	
	cout << endl;
    }
}
