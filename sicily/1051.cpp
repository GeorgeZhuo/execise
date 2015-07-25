// Mon Sep 29 15:14:07 2014
// george@NOSPAM.Phycles

/**
 * sicily 1051 bike trip
 */

#include <iostream>
#include <iomanip>

using namespace std;
int main () {

    double diameter;
    int revolution;
    double time;
    int counter = 0;

    while (cin >> diameter >> revolution >> time, revolution != 0) {

	double distance;
	double hour;
	distance = diameter * 3.1415927 * revolution / (12 * 5280);
	hour = time / (60 * 60);

	cout << "Trip #" << ++counter << ": "
	     << fixed << setprecision(2) << distance << " " 
	     << setprecision(2) << (distance / hour)
	     << endl;
	
    }
}
