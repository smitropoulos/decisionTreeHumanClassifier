

#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main(){

	cv::String path("/Users/stefanosmitropoulos/Developer/Python/OpenCvTest/car/*.png"); //select only jpg
	vector<cv::String> fn;
	vector<cv::Mat> data;
	cv::glob(path,fn,true); // recurse
	for (size_t k=0; k<fn.size(); ++k)
		{
		cv::Mat im = cv::imread(fn[k]);
		if (im.empty()) continue; //only proceed if sucsessful
								  // you probably want to do some preprocessing
		data.push_back(im);
		}
	cout<<data.size()<<endl;


}

