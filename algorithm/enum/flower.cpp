// Mon Dec  8 11:37:52 2014
// george@NOSPAM.Phycles

/*
 * A enum problem
 * a three digits integer that the sum of 
 * each digit's v equals itself
*/

#include <iostream>
#include <math.h>

using namespace std;

int main(int argc, char *argv[])
{
    int hund, ten, dig;

    for (int i = 100; i < 999; ++i) {
	dig = i % 10;
	ten = (i / 10) % 10;
	hund = i / 100;

	if (i == (pow(dig, 3) + pow(ten, 3) + pow(hund, 3))) {
	    cout << i << endl;
	}
	
    }
    return 0;
}
