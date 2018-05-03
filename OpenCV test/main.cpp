#include <fstream>
#include "tree.hpp"
#include "wizard.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include "imageLoader.hpp"
#include "imageProcessor.hpp"
#include "backgroundSubtractor.hpp"
#include <random>
#include <string>

int main(int argc,const char* argv[]){

	auto par=wizard(argc);

	std::string filename = static_cast<std::string>(par.path2)+".txt";		//train set
	std::string filename2 = static_cast<std::string>(par.path2)+"Test"+".txt";	//test set
	std::string filename3 = static_cast<std::string>(par.path2)+"Results"+".txt";	//results set

	std::ofstream file(filename);
	std::ofstream file2(filename2);

		//Random elements generator for the train/test split
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> dis(1, 10);

		//initialise an imageLoader and load images into a vector
	std::vector<specimenImage> filepaths = filepathVectorCompiler(par.stackOfPathsForClasses, "png", par.stackOfNumberForClasses);

		//initiliase an image processor.
	imageProcessor impro;

	if (file.is_open() && file2.is_open()){

		file << "Data\tClass"<<std::endl;	//headers
		file2 << "Data\tClass"<<std::endl;	//headers

		int split = par.splitRatio * filepaths.size();

		for(auto& specimen:filepaths){

			cv::Mat tempImage=cv::imread(specimen.m_imagePath,1);

				//cv::resize(tempImage,tempImage,cv::Size() ,0.1,0.1); //resizing for testing purposes

			impro.removePadding(tempImage);
			impro.rotateNoCrop(tempImage, tempImage, impro.autoRotationAngle(tempImage));
			cv::resize(tempImage,tempImage,cv::Size(100,100) ,0,0); //resizing for testing purposes
			tempImage=tempImage.reshape(1,1);	//reshaping the image to vector form. (1 row, row*cols columns)

			if (split-->0){	//compare the ratio of the split to a random int generated to decide if this "image" will be on the test or the training set.

					//Access all the elements of the mat.data
				for (int i=0;i<tempImage.cols;i++){
					if(static_cast<int>(*tempImage.data++) > 1){ //pseudo thresholding too.
						file2<<1;
					}else{
						file2<<0;
					}
				}
				file2<<'\t';
				file2<<specimen.m_classOfImage<<"\n";
				file2.flush();

			}
			else{

					//Access all the elements of the mat.data
				for (int i=0;i<tempImage.cols;i++){
					if(static_cast<int>(*tempImage.data++) > 1){ //pseudo thresholding too.
						file<<1;
					}else{
						file<<0;
					}
				}

				file<<'\t';
				file<<specimen.m_classOfImage<<"\n";
				file.flush();

			}
		}
		file.close();
	}
	else{
		std::cout<<"Failed to open file. Please make sure the output file is not open by any other program and try again.\n"<<std::endl;
		exit(-1);
	}

	decTree(filename, filename2, filename3);
}
