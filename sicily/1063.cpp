// Fri Jan  9 15:21:59 2015

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
struct Emp {
    int id;
    int salary;
    int height;
    int boss;
    int subNum;

};
bool cmp1(const Emp &e1, const Emp &e2) {
    return e1.salary < e2.salary;
}


bool cmp2(const Emp &e1, const Emp &e2) {
    return e1.id < e2.id;
}



int main(int argc, char *argv[])
{
    int T;
    cin >> T;
    int infoNum, queryNum;
    Emp info[30001];
    while (T--) {
	
	cin >> infoNum >> queryNum;
	for (int i = 0; i < infoNum; ++i) {
	    cin >> info[i].id >> info[i].salary >> info[i].height;
	    info[i].boss = 0;
	    info[i].subNum = 0;
	
	}
	sort(info, info + infoNum, cmp1);

	for (int i = 0; i < infoNum; ++i) {
	    for (int j = i + 1; j < infoNum; ++j) {
		if (info[j].height >= info[i].height) {
		    info[i].boss = info[j].id;
		    info[j].subNum += info[i].subNum + 1;
		    break;
		}
	    }
	}

	sort(info, info + infoNum, cmp2);

	for (int i = 0; i < queryNum; ++i) {
	    int query;
	    int find;
	    cin >> query;
	    
	    int r, l;
	    r = infoNum - 1;
	    l = 0;

	    while (l <= r) {

		find =  (l + r) / 2;
		if (info[find].id == query) {
		    break;
		} else if (info[find].id > query) {
		
		    r = find - 1;
		} else {
		    l = find + 1;
		}
	    }
	    
	    cout << info[find].boss << " " << info[find].subNum << endl;
	    
	}
    }
    return 0;
}

