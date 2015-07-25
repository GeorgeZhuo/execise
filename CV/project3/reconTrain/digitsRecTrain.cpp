#include <fstream>
#include "opencv2/opencv.hpp"
#include <vector>
#include "BPL.h"

#define DATASET_NUM 60000
#define FEATURE_NUM 66

using namespace std;
using namespace cv;

void swapBuffer(char* buf) {

    char temp;
    temp = *(buf);
    *buf = *(buf+3);
    *(buf+3) = temp;

    temp = *(buf+1);
    *(buf+1) = *(buf+2);
    *(buf+2) = temp;
}

void GetROI(Mat& src, Mat& dst)
{
    int left, right, top, bottom;
    left = src.cols;
    right = 0;
    top = src.rows;
    bottom = 0;

    //Get valid area
    for (int i=0; i<src.rows; i++) {
	for (int j=0; j<src.cols; j++) {
	    if (src.at<uchar>(i, j) > 0) {

		if (j < left) left = j;
		if (j > right) right = j;
		if (i < top) top = i;
		if (i > bottom) bottom = i;
	    }
	}
    }

    int width = right - left;
    int height = bottom - top;
    int len = (width < height) ? height : width;

    //Create a squre
    dst = Mat::zeros(len, len, CV_8UC1);

    //Copy valid data to squre center
    Rect dstRect((len - width)/2, (len - height)/2, width, height);
    Rect srcRect(left, top, width, height);
    Mat dstROI = dst(dstRect);
    Mat srcROI = src(srcRect);
    srcROI.copyTo(dstROI);
}

int ReadTrainData(int maxCount) {

    //Open image and label file
    const char fileName[] = "train-images.idx3-ubyte";
    const char labelFileName[] = "train-labels.idx1-ubyte";

    ifstream lab_ifs(labelFileName, ios_base::binary);
    ifstream ifs(fileName, ios_base::binary);
    fstream trainFile;
    trainFile.open("train-file.txt", ios::out);

    if ( ifs.fail() == true )
	return -1;

    if ( lab_ifs.fail() == true )
	return -1;

    //Read train data number and image rows / cols
    char magicNum[4], ccount[4], crows[4], ccols[4];
    ifs.read(magicNum, sizeof(magicNum));
    ifs.read(ccount, sizeof(ccount));
    ifs.read(crows, sizeof(crows));
    ifs.read(ccols, sizeof(ccols));

    int count, rows, cols;
    swapBuffer(ccount);
    swapBuffer(crows);
    swapBuffer(ccols);

    memcpy(&count, ccount, sizeof(count));
    memcpy(&rows, crows, sizeof(rows));
    memcpy(&cols, ccols, sizeof(cols));

    //Just skip label header
    lab_ifs.read(magicNum, sizeof(magicNum));
    lab_ifs.read(ccount, sizeof(ccount));

    //Create source and show image matrix
    Mat src = Mat::zeros(rows, cols, CV_8UC1);
    Mat temp = Mat::zeros(8, 8, CV_8UC1);
    Mat img, dst;

    char _label = 0;
    Scalar templateColor(255, 0, 255 );

    int index = 0;

    while (!ifs.eof()) {

	if (index >= count)
	    break;
		
	//Read label
	lab_ifs.read(&_label, 1);
	// _label = _label + '0';

	//Read source data
	ifs.read((char*)src.data, rows * cols);
	GetROI(src, dst);

	resize(dst, temp, temp.size());

	trainFile << index << ",";
	for (int i = 0; i < 8; i++) {
	    for (int j = 0; j < 8; j++) {

		trainFile << (int)temp.at<uchar>(i, j) << ",";
	    }
	}
	trainFile << (int)_label << endl;
	maxCount--;
	// cout << index << "  lable " << (int)_label << endl;
	index++;

	if(maxCount == 0)
	    break;

    }

    ifs.close();
    lab_ifs.close();
    trainFile.close();

    return 0;
}

int main( int argc, char *argv[] ) {

    int maxCount = 60000;
    ReadTrainData(maxCount);

    BPL bpl;
    
    bpl.train("train-file.txt");

    return 0;
}
