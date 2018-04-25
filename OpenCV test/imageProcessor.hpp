//
//  imageProcessor.hpp
//  OpenCV test
//
//  Created by Stefanos Mitropoulos on 24/04/2018.
//  Copyright © 2018 Stefanos Mitropoulos. All rights reserved.
//

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
	void rotate2D(const cv::Mat & src, cv::Mat & dst, const double degrees);

};

#endif /* imageProcessor_hpp */
