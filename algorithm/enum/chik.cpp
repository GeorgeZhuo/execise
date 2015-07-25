// Mon Dec  8 11:53:30 2014
// george@NOSPAM.Phycles

/*
 * one hundred yuan to buy one hundred chicken
*/

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    
    for (int i = 3; i < 100; i += 3) {
	for (int j = 0; j < 50; ++j) {
	    for (int k = 0; k < 34; ++k) {
		
		if (((i + j + k) == 100) && ( i / 3 + 2 * j + 3 * k) == 100)
		    cout << "{"<< k << "," << j << "," << i << "}" << endl;
	    }
	    
	}
	
    }
    return 0;
}

