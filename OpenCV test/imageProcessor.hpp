
#ifndef imageProcessor_hpp
#define imageProcessor_hpp

#include <stdio.h>
#include "opencv2/opencv.hpp"

class imageProcessor{
public:
	imageProcessor();
	std::vector<cv::KeyPoint> blobDetection(cv::Mat &image);
	cv::Mat removePadding(cv::Mat &image);
	int autoRotationAngle(cv::Mat &im);
	void rotateNoCrop(cv::Mat &im, cv::Mat &rotIm, double angle);

};

#endif /* imageProcessor_hpp */
