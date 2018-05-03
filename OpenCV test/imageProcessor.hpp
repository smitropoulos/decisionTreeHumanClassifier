
#ifndef imageProcessor_hpp
#define imageProcessor_hpp

#include <stdio.h>
#include "opencv2/opencv.hpp"

class imageProcessor{
public:
	imageProcessor();
	std::vector<cv::KeyPoint> blobDetection(cv::Mat &image , int minArea);
	cv::Mat removePadding(cv::Mat &image);
	int autoRotationAngle(cv::Mat &im);
	void rotateNoCrop(cv::Mat &im, cv::Mat &rotIm, const double angle);	
	void blobExtractor(cv::Mat image,std::vector<cv::KeyPoint> keypoints, std::string pathToSave, std::string naming);

};

#endif /* imageProcessor_hpp */
