#include <iostream>
#include <fstream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/stitching/stitcher.hpp"

using namespace std;
using namespace cv;

bool try_use_gpu = false;

string result_name = "result.jpg";

int main(int argc, char* argv[])
{
    vector<Mat> imgs;

    cout << "reading image" << endl;
    for (int i = 1; i < argc; ++i) {
	Mat img = imread(argv[i]);
	if (!img.empty()) {
	    imgs.push_back(img);
	}
    }
    cout << "finishing read" << endl;
    cout << "starting stitch" << endl;

    Mat pano;
    Stitcher stitcher = Stitcher::createDefault(try_use_gpu);
    Stitcher::Status status = stitcher.stitch(imgs, pano);

    if (status != Stitcher::OK)
    {
        cout << "Can't stitch images, error code = " << int(status) << endl;
        return -1;
    }

    imwrite(result_name, pano);
    namedWindow("test", 0);
    imshow("test", pano);
    waitKey();

    return 0;
}

