
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


cv::Mat imageProcessor::removePadding(cv::Mat im){

	int xsum=0;
	int top=0;
	int bot=im.rows;
	int left=0;
	int right=im.cols;

	bool flag=false;

	for (int i=0;i<im.rows;++i){
		for (int j=0;j<im.cols;++j){
			xsum+=im.at<uchar>(i,j);
			if (xsum>0){
				top = i;
				flag = true;
				break;
			}
		}
		if (flag){
			break;
		}
	}

	for (int i=0;i<im.rows;++i){
		for (int j=0;j<im.cols;++j){
			xsum+=im.at<uchar>(j,i);
			if (xsum>0){
				left = i;
				flag = true;
				break;
			}
		}
		if (flag){
			break;
		}
	}

	for (int i=im.rows;i>0;--i){
		for (int j=im.cols;j>0;--j){
			xsum+=im.at<uchar>(i,j);
			if (xsum>0){
				bot = i;
				flag = true;
				break;
			}
		}
		if (flag){
			break;
		}
	}

	for (int i=im.rows;i>0;--i){
		for (int j=im.cols;j>0;--j){
			xsum+=im.at<uchar>(j,i);
			if (xsum>0){
				right = i;
				flag = true;
				break;
			}
		}
		if (flag){
			break;
		}
	}

	cv::Rect myROI( left, top, im.cols-left - (im.cols-right) , im.rows-top - (im.rows-bot) );
	cv::Mat croppedImage = im (myROI);

	return croppedImage;
}
