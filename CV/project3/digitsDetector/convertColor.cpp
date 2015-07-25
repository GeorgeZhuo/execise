#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main( int argc, char *argv[] ) {

    if (argc != 3) {
	cout << argv[0] << " <src images>  <dst images>" << endl;
    }
    
    Mat img, tmp;
    img = imread(argv[1]);

    if (!img.empty()) {
	
	for (int row = 0; row < img.rows; row++) {
	    for (int col = 0; col < img.cols * 3; col++) {

		if (img.at<uchar>(row, col) > 127) {

		    img.at<uchar>(row, col) = 0;

		} else {
		    img.at<uchar>(row, col) = 255;

		}
	    }
	}

	imwrite(argv[2], img);
    }


    return 0;
}
