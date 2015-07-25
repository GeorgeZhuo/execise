#include <fstream>
#include "opencv2/opencv.hpp"
#include <vector>

using namespace std;
using namespace cv;

class NumTrainData
{
public:
    NumTrainData()
	{
	    memset(data, 0, sizeof(data));
	    result = -1;
	}
public:
    double data[64];
    int result;
};


vector<NumTrainData> buffer;
int featureLen = 64;

void swapBuffer(char* buf)
{
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
    for(int i=0; i<src.rows; i++)
    {
	for(int j=0; j<src.cols; j++)
	{
	    if(src.at<uchar>(i, j) > 0)
	    {
		if(j<left) left = j;
		if(j>right) right = j;
		if(i<top) top = i;
		if(i>bottom) bottom = i;
	    }
	}
    }

    //Point center;
    //center.x = (left + right) / 2;
    //center.y = (top + bottom) / 2;

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

int ReadTrainData(int maxCount)
{
    //Open image and label file
    const char fileName[] = "train-images.idx3-ubyte";
    const char labelFileName[] = "train-labels.idx1-ubyte";

    ifstream lab_ifs(labelFileName, ios_base::binary);
    ifstream ifs(fileName, ios_base::binary);

    if( ifs.fail() == true )
	return -1;

    if( lab_ifs.fail() == true )
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

    char label = 0;
    Scalar templateColor(255, 0, 255 );

    NumTrainData rtd;

    //int loop = 1000;
    int total = 0;

    while(!ifs.eof())
    {
	if(total >= count)
	    break;
		
	total++;
	cout << total << endl;
		
	//Read label
	lab_ifs.read(&label, 1);
	label = label + '0';

	//Read source data
	ifs.read((char*)src.data, rows * cols);
	GetROI(src, dst);

	//Too small to watch
	img = Mat::zeros(28, 28, CV_8UC1);
	resize(dst, img, img.size());

	stringstream ss;
	ss << total << ".bmp";
	string text = ss.str();
	imwrite(text, img);

	rtd.result = label;
	resize(dst, temp, temp.size());
	//threshold(temp, temp, 10, 1, CV_THRESH_BINARY);

	for(int i = 0; i<8; i++)
	{
	    for(int j = 0; j<8; j++)
	    {
		rtd.data[ i*8 + j] = temp.at<uchar>(i, j);
	    }
	}

	buffer.push_back(rtd);

	//if(waitKey(0)==27) //ESC to quit
	//	break;

	maxCount--;
		
	if(maxCount == 0)
	    break;
    }

    ifs.close();
    lab_ifs.close();

    return 0;
}

int main( int argc, char *argv[] ) {

    int maxCount = 10000;
    ReadTrainData(maxCount);

    return 0;
}
