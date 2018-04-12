

#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main(){
		// Read image
	Mat im = imread( "474.png", IMREAD_GRAYSCALE );

		// Setup SimpleBlobDetector parameters.
	SimpleBlobDetector::Params params;

		// Change thresholds
//	params.minThreshold = 0;
//	params.maxThreshold = 1;

		// Filter by Area.
	params.filterByArea = true;
	params.minArea = 5;

		// Filter by Circularity
	params.filterByCircularity = false;
	params.minCircularity = 0.1;

		// Filter by Convexity
	params.filterByConvexity = false;
	params.minConvexity = 0.87;

		// Filter by Inertia
	params.filterByInertia = false;
	params.minInertiaRatio = 0.01;


		// Storage for blobs
	vector<KeyPoint> keypoints;


#if CV_MAJOR_VERSION < 3   // If you are using OpenCV 2

		// Set up detector with params
	SimpleBlobDetector detector(params);

		// Detect blobs
	detector.detect( im, keypoints);
#else

		// Set up detector with params
	Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

		// Detect blobs
	detector->detect( im, keypoints);
#endif

		// Draw detected blobs as red circles.
		// DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures
		// the size of the circle corresponds to the size of blob

	Mat im_with_keypoints;
	drawKeypoints( im, keypoints, im_with_keypoints, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );

		// Show blobs
	imshow("keypoints", im_with_keypoints );
	waitKey(0);
	return 0;
}
