
#ifndef backgroundSubtractor_hpp
#define backgroundSubtractor_hpp

#include <stdio.h>
#include "wizard.hpp"
#include "opencv2/opencv.hpp"

void backgroundSubtractorProcessor(const std::string& videoFilename, const std::string& savePath, params par);

void backgroundSubtractorProcessor(const int& camera);
void live(cv::Mat& tempImage);


#endif /* backgroundSubtractor_hpp */
