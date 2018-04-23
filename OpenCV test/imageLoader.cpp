//
//  imageLoader.cpp
//  OpenCV test
//
//  Created by Stefanos Mitropoulos on 23/04/2018.
//  Copyright © 2018 Stefanos Mitropoulos. All rights reserved.
//
#include "opencv2/opencv.hpp"
#include "imageLoader.hpp"

imageLoader::imageLoader(std::string folder_path,std::string ext):m_path(""){
	m_path = folder_path + "*." + ext;	//Concatenate strings to form the full path.
}

std::vector<cv::Mat> imageLoader::load(){

	std::vector<cv::String> nameVector;
	std::vector<cv::Mat> dataVector;

	cv::glob(m_path,nameVector,true); // recurse
	for (size_t k=0; k<nameVector.size(); ++k)
		{
		cv::Mat im = cv::imread(nameVector[k]);
		if (im.empty()) continue; //only proceed if sucsessful
								  // you probably want to do some preprocessing
		dataVector.push_back(im);
		}

	return dataVector;
}
