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
	cv::Mat removePadding(cv::Mat image);


};


#endif /* imageProcessor_hpp */
