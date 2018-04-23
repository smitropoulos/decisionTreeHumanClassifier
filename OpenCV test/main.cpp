

#include "opencv2/opencv.hpp"
#include <iostream>
#include "imageLoader.hpp"
using namespace std;
using namespace cv;

int main(){

	imageLoader jpgImages("/Users/stefanosmitropoulos/Developer/Python/OpenCvTest/car/" , "png");
	auto images = jpgImages.load();
}

