#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "cv.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <stdio.h>

using namespace cv;
using namespace std;

Mat houghTransform(Mat src) {

    int thl = 125;
    int thh = thl * 4;
    int th = 115;

    Mat dst, grayImage, binImage;
    cvtColor(src, grayImage, CV_BGR2GRAY);
    blur( grayImage, grayImage, Size(3,3) );
    Canny(grayImage, dst, thl, thh, 3);

    Mat cdst;
    cvtColor(dst, cdst, CV_GRAY2BGR);
    cdst.setTo(0);
    
    vector<Vec2f> lines;
    vector<Vec2f> lines_2;
    while (true) {
	HoughLines( dst, lines, 1, CV_PI/180, th );

	if (lines.size() > 9) {
	    th += 5;
	} else if (lines.size() < 4) {
	    th -= 5;
	} else {
	    break;
	}
    }

    vector<int> dup;
    for (size_t i = 0; i < lines.size(); ++i) {

	for (size_t j = i + 1; j < lines.size(); ++j) {
	    if (abs(abs(lines[i][0]) - abs(lines[j][0])) < 50 &&
		(abs(lines[i][1] - lines[j][1]) < 0.25 * CV_PI || 
		 abs(lines[i][1] - lines[j][1]) > 0.75 * CV_PI))
		dup.push_back(j);

	}
    }

    for( size_t i = 0; i < lines.size(); i++ ) {

	if (find(dup.begin(), dup.end(), i) == dup.end()) {
	    
	    lines_2.push_back(lines[i]);
   	}
    }
    dup.clear();

    if (lines_2.size() > 4) {
	for (size_t i = 0; i < lines_2.size(); ++i) {
	    for (size_t j = i + 1; j < lines_2.size(); ++j) {
		
		if (abs(lines_2[i][1] - lines_2[j][1]) < 0.05 * CV_PI || 
		    abs(lines_2[i][1] - lines_2[j][1]) > 0.95 * CV_PI) {

		    dup.push_back(i);
		    dup.push_back(j);
		}
	    }
	}
    } else {
	for (int i = 0; i < lines_2.size(); ++i) {
	    dup.push_back(i);
	}
    }

    for( size_t i = 0; i < lines_2.size(); i++ ) {

	if (find(dup.begin(), dup.end(), i) != dup.end()) {

	    float rho = lines_2[i][0];
	    float theta = lines_2[i][1];
	    double a = cos(theta), b = sin(theta);
	    double x0 = a*rho, y0 = b*rho;
	    Point pt1(cvRound(x0 + 1000*(-b)),
		      cvRound(y0 + 1000*(a)));
	    Point pt2(cvRound(x0 - 1000*(-b)),
		      cvRound(y0 - 1000*(a)));
	    line( cdst, pt1, pt2, Scalar(0,0,255), 1, 8 );
   	}
    }
    /*
    namedWindow("canny", 0);
    imshow("canny", dst);
    namedWindow("hough", 0);
    imshow("hough", cdst);
    */
    return cdst;
}

vector<Point> cornerDetect(Mat srcImage) {

    Mat grayImage, cornerStrength;
    cvtColor(srcImage, grayImage, CV_BGR2GRAY);
    cornerHarris(grayImage, cornerStrength, 2, 3, 0.01);
	
    Mat harrisCorner;  
    threshold(cornerStrength, harrisCorner, 0.0001, 255, THRESH_BINARY); 
    
    vector<Point> points;
    goodFeaturesToTrack(harrisCorner, points, 5, 0.01, 10);

    if (points.size() > 4) {
	for (int i = 0; i < points.size(); ++i) {
	    if(points[i].x <= 2 || points[i].y <= 2) {
		points.erase(points.begin() + i);
		break;
	    }
	}
    }
    for (int i = 0; i < points.size(); ++i) {
	cout << points[i].x << " " << points[i].y << endl;
    }
    return points;
}

bool cmp(Point a, Point b) {
    
    return a.y < b.y;
}

void warping(Mat src, vector<Point> points) {

    imwrite("temp.jpg", src);
   
    CvMat* warp_mat = cvCreateMat( 3, 3, CV_32FC1);
    CvPoint2D32f srcTri[4], dstTri[4]; 
    IplImage *warpImg = cvLoadImage("temp.jpg"),
	*srcImage = cvLoadImage("temp.jpg");

    cvZero(warpImg);
    sort(points.begin(), points.end(), cmp);

    if (points[0].x > points[1].x)
	swap(points[0], points[1]);
   
    if (points[2].x > points[3].x)
	swap(points[2], points[3]);

    double r1 = pow((points[0].x - points[1].x), 2) +
	pow((points[0].y - points[1].y), 2);
    double r2 = pow((points[0].x - points[2].x), 2) +
	pow((points[0].y - points[2].y), 2);

    int height , width;
    if (r1 > r2) {
	width = (int)sqrt(r1);
	height = width * 210 / 297;

    } else {	
	height = (int)sqrt(r2);
	width = height * 210 / 297;
    }
/*
    line( src, points[0], points[1], Scalar(0,0,255), 1, 8 );
    line( src, points[0], points[2], Scalar(0,255,0), 1, 8 );
    line( src, points[1], points[3], Scalar(255,0,0), 1, 8 );
    line( src, points[2], points[3], Scalar(255,0,255), 1, 8 );
*/
    srcTri[0].x = points[0].x;
    srcTri[1].x = points[1].x;
    srcTri[2].x = points[2].x;
    srcTri[3].x = points[3].x;
    srcTri[0].y = points[0].y;
    srcTri[1].y = points[1].y;
    srcTri[2].y = points[2].y;
    srcTri[3].y = points[3].y;

    dstTri[0].x = 0;
    dstTri[0].y = 0;
    dstTri[1].x = width;
    dstTri[1].y = 0;
    dstTri[2].x = 0;
    dstTri[2].y = height;
    dstTri[3].x = width;
    dstTri[3].y = height;

    cvGetPerspectiveTransform(srcTri, dstTri, warp_mat);
    cvWarpPerspective(srcImage, warpImg, warp_mat);
    
    Mat warp(warpImg);
    /*
    namedWindow("warp", 0);
    imshow("warp", warp);
    namedWindow("test", 0);
    imshow("test", src);
    */
    Rect rec(0, 0, width, height);
    Mat img(warp, rec);
    
    namedWindow("cutting", 0);
    imshow("cutting", img);   
}

int main(int argc, char** argv)
{
    const char* filename;
    Mat src, src_resize;

    if (argc < 2)
	return 0;

    filename = argv[1];
    src = imread(filename, 1);
    if(src.empty())
    {
        cout << "can not open " << filename << endl;
        return -1;
    }
    resize(src, src_resize, Size(), 0.2, 0.2, CV_INTER_LINEAR);

    namedWindow("src ", 0);
    imshow("src ", src_resize);

    Mat cdst = houghTransform(src_resize);
    
    vector<Point> points  = cornerDetect(cdst);

    warping(src_resize, points);

    waitKey();
    return 0;
}
