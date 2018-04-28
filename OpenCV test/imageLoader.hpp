
#ifndef imageLoader_hpp
#define imageLoader_hpp

#include <string>
#include <stack>
#include "opencv2/opencv.hpp"

enum imageLoaderOptions {justLoad, process};

class imageLoader
{
public:
	imageLoader(std::string folder_path,std::string ext,char classNumber);
	std::stack<cv::Mat> load(imageLoaderOptions opt);
	char m_classNumber;

private:
	std::string m_path;
	std::string m_ext;
};

#endif /* imageLoader_hpp */
