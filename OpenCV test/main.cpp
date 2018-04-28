#include "opencv2/opencv.hpp"
#include <iostream>
#include "imageLoader.hpp"
#include "imageProcessor.hpp"
#include "backgroundSubtractor.hpp"
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;


int main(int argc,const char* argv[]){

	if(argc!=5) {
		cout << "Please follow this format. @args [path to images] [extension of images] [class number] [results file name]\n";
		return 0;
	}

		//initialise an imageLoader and load images into a stack
	imageLoader images(argv[1] , argv[2], *argv[3]);
	std::stack<cv::Mat>  carImagesStack = images.load(justLoad);
		//initiliase an image processor.
	imageProcessor impro;

	ofstream file(argv[4]);
	if (file.is_open()){

		file << "Data\tClass"<<endl;	//headers

		while(!carImagesStack.empty()){

			auto tempImage=carImagesStack.top();	//clarity mostly. Eitherway there is no data copy here

			impro.removePadding(tempImage);
			impro.rotateNoCrop(tempImage, tempImage, impro.autoRotationAngle(tempImage));
			tempImage=tempImage.reshape(1,1);	//reshaping the image to vector form. (1 row, row*cols columns)

				//Access all the elements of the mat.data
			for (int i=0;i<tempImage.cols;i++){
				if(static_cast<int>(*carImagesStack.top().data++) > 1){ //pseudo thresholding too.
					file<<1;
				}else{
					file<<0;
				}
			}
			file<<'\t';
			file<<images.m_classNumber;
			
			carImagesStack.pop();
		}
		file.close();
	}
	else{
		cout<<"Failed to open file. Please make sure the output file is not open by any other program and try again.\n"<<endl;
		exit(-1);
	}
}
