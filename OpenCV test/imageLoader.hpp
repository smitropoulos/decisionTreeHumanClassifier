//
//  imageLoader.hpp
//  OpenCV test
//
//  Created by Stefanos Mitropoulos on 23/04/2018.
//  Copyright © 2018 Stefanos Mitropoulos. All rights reserved.
//

#ifndef imageLoader_hpp
#define imageLoader_hpp

#include <stdio.h>
#include <string>
#include "opencv2/opencv.hpp"

class imageLoader
{
public:
	imageLoader(std::string folder_path,std::string ext);
	std::vector<cv::Mat> load();
private:
	std::string m_path;
	std::string m_ext;
};

#endif /* imageLoader_hpp */
