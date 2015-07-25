// Sun Sep 28 14:19:06 2014
// george@NOSPAM.Phycles

#include <iostream>
#include <map>
#include <string>

using namespace std;

int main () {

    int N;
    string ID;
    string IP;
    
    while (cin >> N, N != 0) {

	map<string, string> record;
	map<string, string>:: iterator it;
	for (int i = 0; i < N; i++) {

	    cin >> ID >> IP;
	    it = record.find(IP);

	    if (it == record.end()) {
		record[IP] = ID;
	    } else {

		cout << ID << " is the MaJia of " << it->second << endl;
	    }
	}
	cout << endl;
    }

    return 0;
}

