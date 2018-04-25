
#include "opencv2/opencv.hpp"
#include <iostream>
#include "imageLoader.hpp"
#include "imageProcessor.hpp"

using namespace std;
using namespace cv;

using namespace std;
int main(){

	imageLoader jpgImages("/Users/stefanosmitropoulos/Developer/Python/OpenCvTest/car/" , "png");
	std::stack<cv::Mat>  carImages = jpgImages.load(justLoad);

	imageProcessor impro;
	impro.blobDetection(carImages.top());

	cv::Mat image = imread("sample.jpg",0);

	cv::Mat im;
	cv::threshold(image,im,0, 255, cv::THRESH_OTSU);

	auto angle=impro.autoRotationAngle(im);

	cv::Mat rotIm;
	impro.rotateNoCrop(im, rotIm, angle );

	std::cout<<angle<<std::endl;

	namedWindow( "Display window", WINDOW_AUTOSIZE );	// Create a window for display.
	imshow( "Display window", rotIm);                   // Show our image inside it.
	waitKey(0);                                      	// Wait for a keystroke in the window

}

