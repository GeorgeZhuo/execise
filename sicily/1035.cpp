// Sun Sep 28 14:49:35 2014
// george@NOSPAM.Phycles

#include <iostream>
#include <set>
#include <string>

using namespace std;

int main () {

    int cases;
    int number;
    string dna;
    cin >> cases;
    while (cases--) {
	
	set<string> container;
	set<string> :: iterator it;
	string dna_pair;
	int counter = 0;
	cin >> number;
	for (int i = 0; i < number; i++) {
	    cin >> dna;
	    dna_pair = dna;
	    for (int i = 0; i < dna.size(); i++) {
		
		if (dna[i] == 'A') dna_pair[i] = 'T';
		else if (dna[i] == 'T') dna_pair[i] = 'A';
		else if (dna[i] == 'G') dna_pair[i] = 'C';
		else dna_pair[i] = 'G';
	    }
	    it = container.find(dna_pair);
	    if (it != container.end()) {
		counter++;
		container.erase(it);
	    } else {
		container.insert(dna);
	    }
	}
	cout << counter << endl;
    }

}
