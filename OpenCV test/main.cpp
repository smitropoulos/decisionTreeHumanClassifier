#include "opencv2/opencv.hpp"
#include <iostream>
#include "imageLoader.hpp"
#include "imageProcessor.hpp"
#include "backgroundSubtractor.hpp"
#include <iostream>
#include <fstream>
#include <random>
#include <string>

#include "tree.hpp"
#include "wizard.hpp"


using namespace std;

int main(int argc,const char* argv[]){

	wizard(argc);
		//Random elements generator for the train/test split
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> dis(1, 10);


		//initialise an imageLoader and load images into a stack
	imageLoader images(argv[1] , argv[2],1);
	std::stack<cv::Mat>  carImagesStack = images.load(justLoad);

		//initiliase an image processor.
	imageProcessor impro;

	std::string filename = static_cast<std::string>(argv[4])+".txt";
	std::string filename2 = static_cast<std::string>(argv[4])+"Test"+".txt";

	std::ofstream file(filename);
	std::ofstream file2(filename2);

	if (file.is_open() && file2.is_open()){

		file << "Data\tClass"<<std::endl;	//headers
		file2 << "Data\tClass"<<std::endl;	//headers

		while(!carImagesStack.empty()){

			auto tempImage=carImagesStack.top();	//clarity mostly. Eitherway there is no data copy here

			impro.removePadding(tempImage);
			impro.rotateNoCrop(tempImage, tempImage, impro.autoRotationAngle(tempImage));
			tempImage=tempImage.reshape(1,1);	//reshaping the image to vector form. (1 row, row*cols columns)

			if (dis(gen) < 10 * strtod(argv[5], NULL)){	//compare the ratio of the split to a random int generated to decide if this "image" will be on the test or the training set.

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
				file<<std::endl;

			}
			else{
					//Access all the elements of the mat.data
				for (int i=0;i<tempImage.cols;i++){
					if(static_cast<int>(*carImagesStack.top().data++) > 1){ //pseudo thresholding too.
						file2<<1;
					}else{
						file2<<0;
					}
				}
				file2<<'\t';
				file2<<images.m_classNumber;
				file2<<std::endl;
			}
			carImagesStack.pop();
		}
		file.close();
	}
	else{
		std::cout<<"Failed to open file. Please make sure the output file is not open by any other program and try again.\n"<<std::endl;
		exit(-1);
	}

	decTree(filename, filename2, "results.txt");
}



