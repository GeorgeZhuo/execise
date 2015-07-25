#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <stdio.h>

#include "opencv2/opencv.hpp"

#define ROW 150
#define COL 150

using namespace std;
using namespace cv;

int genNegImages(int maxCount) {

    srand(time(NULL));
    int tmp;
    Mat src = Mat::zeros(ROW, COL, CV_8UC1);

    //Create source and show image matrix
    for (int i = 0; i < maxCount; i++) {
	
	cout << "number" << i << endl;
	src.setTo(0);
	for (int r = 0; r < src.rows; r += 2) {
	    for (int c = 0; c < src.cols; c += 2) {
		
		tmp = rand() % 10;
		if (tmp > 4) {
		    src.at<uchar>(r, c) = 255;
		    src.at<uchar>(r, c + 1) = 255;
		}
	    }
	}
	
	stringstream ss;
	ss << i << ".bmp";
	string text = ss.str();

	imwrite(text, src);
	
    }
        
}

int main( int argc, char *argv[] ) {

    int maxCount = 30000;
    genNegImages(maxCount);

    return 0;
}
