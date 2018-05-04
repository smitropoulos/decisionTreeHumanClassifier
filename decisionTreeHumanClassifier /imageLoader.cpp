#include "wizard.hpp"
#include "opencv2/opencv.hpp"
#include "imageLoader.hpp"
#include <algorithm>
#include <random>

specimenImage::specimenImage(std::string imagePath, int classOfImage):m_imagePath(imagePath),m_classOfImage(classOfImage){}

imageLoader::imageLoader(std::string folder_path,std::string ext, int classNumber):m_path(""),m_classNumber(-1),m_ext(".png"){
	m_path = folder_path + "*." + ext;	//Concatenate strings to form the full path.
	m_classNumber = classNumber;
	if (!ext.size()){
		m_ext = ext;
	}
}

std::vector<specimenImage> imageLoader::loadSpecimens(){

	std::vector<cv::String> nameVector;
	std::vector<specimenImage> specimenVector;

	try{
		cv::glob(m_path,nameVector,true); // recurse
		for (int k=0;k<nameVector.size();++k){
			specimenImage spk(nameVector[k],m_classNumber);
			specimenVector.push_back(spk);

		}
	}
	catch( cv::Exception& e ){	//wrong path exception
		std::cerr << e.what() << std::flush;
		std::cout << "Make sure you input a correct path."<< std::endl;
	}

	return specimenVector;
}


std::vector<specimenImage> filepathVectorCompiler(std::stack<std::string> stackOfPathsForClasses,std::string ext, std::stack<int> stackOfNumberForClasses){

	std::vector<specimenImage> filePaths;

	while (stackOfNumberForClasses.size()>0){

		imageLoader imgLoader(stackOfPathsForClasses.top(), ext, stackOfNumberForClasses.top() );
		std::vector<specimenImage>  toAdd = imgLoader.loadSpecimens();

		filePaths.insert(filePaths.end(), toAdd.begin(), toAdd.end());	//append to the big vector the filenames we just read.
		stackOfPathsForClasses.pop();
		stackOfNumberForClasses.pop();
	}

	auto rng = std::default_random_engine {};
	std::shuffle(std::begin(filePaths), std::end(filePaths), rng);

	return filePaths;
}




