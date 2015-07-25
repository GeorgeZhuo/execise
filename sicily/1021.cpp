// Sun Sep 28 11:21:08 2014 george@NOSPAM.Phycles

/*
 * sicily 1021 couples  
 * 对于stack栈的清空非常重要，由于没有对栈进行清空
 * 导致多次提交都显示wrong answer.
*/

#include <iostream>
#include <stack>

using namespace std;

int main () {

    int couples[200100];
   
    int w, h;
    int number;
    cin >> number;
    while (number != 0) {
	 stack<int> circle;
	for (int i = 0; i < number; i++) {

	    cin >> w >> h;
	    couples[w] = h;
	    couples[h] = w;
	}

	for (int i = 1; i < number * 2 + 1; i++) {

	    if (circle.empty()) {
		circle.push(i);
	    } else if (i == couples[circle.top()]) {
		circle.pop();
	    } else {
		circle.push(i);
	    }
	}
	
	if (circle.empty()) {
	    cout << "Yes"<< endl;
	} else {
	    cout << "No" << endl;
	}
	cin >> number;
    }

    return 0;
}
