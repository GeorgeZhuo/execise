#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/ml/ml.hpp"
#include "BPL.h"

#include <iostream>
#include <stdio.h>

#define FEATURE_NUM 64

using namespace std;
using namespace cv;

void fetchFeature(vector<Mat> &digis_img, 
		  int image_feature[][FEATURE_NUM]);

vector<Mat> detectAndDraw(CascadeClassifier& cascade, 
			  Mat &img, double scale);


int main(int argc, char *argv[]) {

    // BPL bpl;
    Mat image;
    double scale = 1.0;
    vector<Mat> digits_img;
    CascadeClassifier cascade;

    if( !cascade.load("../boostTrain/classfier.xml")) {

	cerr << "ERROR: Could not load classifier cascade" << endl;
	return 0;
    }
    if (argc == 1) {
	cout << "No image" << endl;
    }
    
    image = imread(argv[1]);

    if(!image.empty()) {

	cout << "Detect the image...." << endl;
        digits_img = detectAndDraw(cascade, image, scale);
	
	cout << "Recongnize the digits..." << endl;
	/*
	int image_feature[digits_img.size()][FEATURE_NUM];
	fetchFeature(digits_img, image_feature);

	BPL bpl;
	cout << "Training...." << endl;
	bpl.train("train-file.txt");

	cout << "Training end..." << endl;
	bpl.test(image_feature);
	*/
        waitKey(0);
    }

    return 0;
}

vector<Mat> detectAndDraw(CascadeClassifier& cascade,  
			  Mat &img, double scale) {

    int i = 0;
    vector<Mat> digits_img;
    double t = 0;
    vector<Rect> digits;
    Mat gray, smallImg(cvRound (img.rows/scale), 
		       cvRound(img.cols/scale), CV_8UC1 );

    cvtColor(img, gray, CV_BGR2GRAY);
    resize(gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR);
    equalizeHist( smallImg, smallImg );

    cascade.detectMultiScale( smallImg, digits, 1.1, 2, 
			      0 | CV_HAAR_SCALE_IMAGE, Size(22, 22));

    for( vector<Rect>::const_iterator r = digits.begin(); 
	 r != digits.end(); r++, i++ ) {

        Mat smallImgROI;
	rectangle(img, *r, Scalar(255, 0, 0));

	Mat tmp(img, *r);
	digits_img.push_back(tmp);
        smallImgROI = smallImg(*r);
    }

    namedWindow("result", 0);
    cv::imshow( "result", img);
    imwrite("result.bmp", img);

    return digits_img;
}


void fetchFeature(vector<Mat> &digits_img, 
		  int image_feature[][FEATURE_NUM]) {

    Mat tmp;
    int index;
    for (int i = 0; i < digits_img.size(); i++) {
	resize(digits_img[i], tmp, Size(8, 8), INTER_LINEAR);

	for (int row = 0; row < tmp.rows; ++row) {
	    for (int col = 0;  col < tmp.cols; ++col) {
		index = row * tmp.cols + col;

		if (tmp.at<uchar>(row, col) > 127) {
		    image_feature[i][index] = 0;
		} else {
		    image_feature[i][index] = 255;
		}
	    }
	}
    }
}

