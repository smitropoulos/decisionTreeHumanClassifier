
#include "imageProcessor.hpp"

imageProcessor::imageProcessor(){}

std::vector<cv::KeyPoint> imageProcessor::blobDetection(cv::Mat &image){
		// Setup SimpleBlobDetector parameters.
	cv::SimpleBlobDetector::Params params;

	params.filterByArea = true;
	params.minArea = 300;
	params.maxArea = 300000;

	params.filterByCircularity = true;
	params.minCircularity=0;
	params.maxCircularity=1;

	params.filterByColor = true;
	params.blobColor = 255;

	params.filterByConvexity = true;
	params.minConvexity=0;
	params.maxConvexity=1;


		// Set up detector with params
	cv::Ptr<cv::SimpleBlobDetector> blobDetector = cv::SimpleBlobDetector::create(params);

		// Detect blobs.
	std::vector<cv::KeyPoint> keypoints;
	blobDetector->detect( image, keypoints);

	return keypoints;
}


cv::Mat imageProcessor::removePadding(cv::Mat image){



	return image;
}
