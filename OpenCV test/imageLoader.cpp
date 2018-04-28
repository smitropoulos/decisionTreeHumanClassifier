
#include "opencv2/opencv.hpp"
#include "imageLoader.hpp"

imageLoader::imageLoader(std::string folder_path,std::string ext, char classNumber):m_path(""),m_classNumber(-1){
	m_classNumber=classNumber;
	m_path = folder_path + "*." + ext;	//Concatenate strings to form the full path.
}

std::stack<cv::Mat> imageLoader::load(imageLoaderOptions opt){

	std::vector<cv::String> nameVector;
	std::stack<cv::Mat> dataStack;

	try{
		cv::glob(m_path,nameVector,true); // recurse
		for (size_t k=0; k<nameVector.size(); ++k)
			{
			cv::Mat im = cv::imread(nameVector[k],1);

			cv::resize(im, im,cv::Size(),0.1,0.1);

			if (im.empty()) continue; //only proceed if sucsessful

			if (opt==0){
				dataStack.push(im);
			}
			else if(opt==1){
					// you probably want to do some preprocessing. Don't know if it's a good idea to summon the imageprocessor here.
				dataStack.push(im);
			}
			}
	}
	catch( cv::Exception& e ){	//wrong path exception
		std::cerr << e.what() << std::flush;
		std::cout << "Make sure you input a correct path."<< std::endl;
	}

	return dataStack;
}
