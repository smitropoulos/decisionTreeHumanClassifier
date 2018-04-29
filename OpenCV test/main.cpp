#include "opencv2/opencv.hpp"
#include <iostream>
#include "imageLoader.hpp"
#include "imageProcessor.hpp"
#include "backgroundSubtractor.hpp"
#include <iostream>
#include <fstream>
#include <random>
#include <string>

using namespace std;
using namespace cv;



int main(int argc,const char* argv[]){

	if(argc!=6) {
		cout << "Please follow this format. @args [path to images] [extension of images] [class number] [results file name] [test/train ration split (0...1) ]\n";
		return 0;
	}


		//Random elements generator for the train/test split
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> dis(1, 10);



		//initialise an imageLoader and load images into a stack
	imageLoader images(argv[1] , argv[2], *argv[3]);
	std::stack<cv::Mat>  carImagesStack = images.load(justLoad);

		//counters for train/test split.
	int trainRatio = carImagesStack.size() * strtod(argv[5], NULL);
	int testRatio = 1 - trainRatio;



		//initiliase an image processor.
	imageProcessor impro;

	std::string filename = argv[4];

	ofstream file(filename+".txt");
	ofstream file2(filename+"Test"+".txt");

	if (file.is_open() && file2.is_open()){

		file << "Data\tClass"<<endl;	//headers
		file2 << "Data\tClass"<<endl;	//headers

		while(!carImagesStack.empty()){

			auto tempImage=carImagesStack.top();	//clarity mostly. Eitherway there is no data copy here

			impro.removePadding(tempImage);
			impro.rotateNoCrop(tempImage, tempImage, impro.autoRotationAngle(tempImage));
			tempImage=tempImage.reshape(1,1);	//reshaping the image to vector form. (1 row, row*cols columns)

			if (dis(gen) < 10 * strtod(argv[5], NULL)){

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
			}
			carImagesStack.pop();
		}
		file.close();
	}
	else{
		cout<<"Failed to open file. Please make sure the output file is not open by any other program and try again.\n"<<endl;
		exit(-1);
	}
}
