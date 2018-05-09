
#ifndef imageLoader_hpp
#define imageLoader_hpp

#include <string>
#include <stack>
#include "opencv2/opencv.hpp"

class specimenImage{
public:
	specimenImage(std::string imagePath, int classOfImage);
	std::string m_imagePath;
	int m_classOfImage;
};

class imageLoader
{
public:
	imageLoader(std::string folder_path,std::string ext,int classNumber);

	std::vector<specimenImage> loadSpecimens();
private:

	int m_classNumber;
	std::string m_path;
	std::string m_ext;
};

std::vector<specimenImage> filepathVectorCompiler(std::stack<std::string> stackOfPathsForClasses,std::string ext, std::stack<int> stackOfNumberForClasses);

#endif /* imageLoader_hpp */
