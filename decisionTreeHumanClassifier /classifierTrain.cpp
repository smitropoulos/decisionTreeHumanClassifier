#include <random>
#include <string>
#include <iostream>
#include <fstream>

#include "wizard.hpp"
#include "opencv2/opencv.hpp"
#include "imageLoader.hpp"
#include "imageProcessor.hpp"
#include "backgroundSubtractor.hpp"

#include "classifierTrain.hpp"

	//#include <ctime>	//time measeurement

	//Check for open file inline function
inline bool file_exists (const std::string& name) {
	if (FILE *file = fopen(name.c_str(), "r")) {
		fclose(file);
		return true;
	} else {
		return false;
	}
}


void classifierTrain(params& par){

	bool openFile=false;
		//	double g=0;	//time counter

	par.completeFilename = static_cast<std::string>(par.path2)+".txt";		//train set
	par.completeFilename2 = static_cast<std::string>(par.path2)+"Test"+".txt";	//test set
	par.completeFilename3 = static_cast<std::string>(par.path2)+"Results"+".txt";	//results set


		//Random elements generator for the train/test split
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> dis(1, 10);

		//initialise an imageLoader and load images into a vector
	std::vector<specimenImage> filepaths = filepathVectorCompiler(par.stackOfPathsForClasses, "png", par.stackOfNumberForClasses);

		//initiliase an image processor.
	imageProcessor impro;

	if (file_exists(par.completeFilename) || file_exists(par.completeFilename2)){
		std::cout<<"Some of the file paths you entered are already in use by other files.\nDo you want to overwrite those files? [Y/n]";
		std::string temp{};
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, temp);
		if ( temp =="yes" || temp=="Yes"||temp=="y"||temp=="Y"){
			openFile=false;
		}
	}

	std::ofstream file(par.completeFilename);
	std::ofstream file2(par.completeFilename2);

	
	if (file.is_open() && file2.is_open() && !openFile){

			//		//Debugging info
			//cv::namedWindow("imageviewer");

		if(par.classifier.compare("python")){
			file << "Data"<<par.delimeter<<"Class"<<std::endl;	//headers
			file2 << "Data"<<par.delimeter<<"Class"<<std::endl;	//headers
		}
		int split = par.splitRatio * filepaths.size();

		int processingIntervalsCounter=0;


		for(auto& specimen:filepaths){	//loop through the images.

				//double start_s=clock();

			if (++processingIntervalsCounter%100==0){		//output processing to the screen to show it's running
				std::cout<<"Processing...\r";
			}
			cv::Mat tempImage=cv::imread(specimen.m_imagePath);

				//cv::resize(tempImage,tempImage,cv::Size() ,0.1,0.1); //resizing for testing purposes

			impro.removePadding(tempImage);
			impro.rotateNoCrop(tempImage, tempImage, impro.autoRotationAngle(tempImage));
			cv::resize(tempImage,tempImage,cv::Size(150,150) ,0,0); //resizing as for all the rows to have the same size.

				//			//Debugging info
				//			cv::imshow("imageviewer", tempImage);
				//			cv::waitKey(25);

			tempImage=tempImage.reshape(0,1);	//reshaping the image to vector form. (1 row, row*cols columns) keeping the same colour scheme.

			if (split-->0){

					//Access all the elements of the mat.data
				for (int i=0;i<tempImage.cols;i++){
					if(static_cast<int>(*tempImage.data++) > 1){ //pseudo thresholding too.
						file2<<1;
					}else{
						file2<<0;
					}
				}
				file2<<par.delimeter;
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

				file<<par.delimeter;
				file<<specimen.m_classOfImage<<"\n";
				file.flush();

			}

				//			double stop_s=clock();
				//			g+=(stop_s-start_s)/double(CLOCKS_PER_SEC)*1000;
		}

		file.close();
		file2.close();

	}
	else{
		if (!openFile){
			std::cerr<<"Failed to open file. Please make sure the output file is not open by any other program and try again.\n"<<std::endl;
			exit(-1);
		}
		else{
			std::cout<<"The programme will continue to the classifiers now\n"<<std::endl;

		}
	}
		// //Time output for the loop
		//	g=g/filepaths.size();
		//	std::cout<<"Average time of loop: "<<g<<std::endl;



}

void classifierLive(cv::Mat tempImage2){
	
	/*
	 takes an image, extracts its blobs, and then creates a text file with the processed blobs.
	 */

	std::string filename = "pythonClassifier.py live";
	std::string command = "./";
	std::string str = command+filename;
	const char *cstr = str.c_str();


	auto tempImage=cv::imread("/Users/stefanosmitropoulos/Developer/C++ Programming/decisionTreeHumanClassifier /build/Debug/demo_real_time/temp.png",1);
	
	imageProcessor impro;

	cv::SimpleBlobDetector::Params params;


	params.filterByArea = true;
	params.minArea = 300;
	params.maxArea = 300000000;
	params.filterByCircularity = true;
	params.minCircularity=0;
	params.maxCircularity=1;

	params.filterByColor = true;
	params.blobColor = 255;

	params.filterByConvexity = true;
	params.minConvexity=0;
	params.maxConvexity=1;


		// Set up detector with the above parameters. As of now there is not need to alter them.
	cv::Ptr<cv::SimpleBlobDetector> blobDetector = cv::SimpleBlobDetector::create(params);

		// Detect blobs.
	std::vector<cv::KeyPoint> keypoints;

	std::string completeFilename = static_cast<std::string>("/Users/stefanosmitropoulos/Developer/C++ Programming/decisionTreeHumanClassifier /build/Debug/demo_real_time/ouput")+".txt";		//train set
	std::ofstream file(completeFilename);  //output text file

	blobDetector->detect(tempImage, keypoints);

	for (int i=0;i<keypoints.size();++i){
		int size = keypoints[i].size;

		int leftestX = keypoints[i].pt.x - size;
		int uppermostY= keypoints[i].pt.y - size;
		int rightestX = keypoints[i].pt.x + size;
		int bottomY= keypoints[i].pt.y + size;

		if (leftestX < 0)
			leftestX =0;

		if(rightestX > tempImage.cols)
			rightestX = tempImage.cols;

		if (uppermostY<0)
			uppermostY = 0;

		if (bottomY>tempImage.rows)
			bottomY   = tempImage.rows;

		int rectWidth = (rightestX - leftestX);
		int rectHeight = (bottomY - uppermostY);

		cv::Rect myRect= cvRect(leftestX,uppermostY,rectWidth,rectHeight);
		cv::Mat croppedImage = tempImage(myRect);		//blob is created

		impro.removePadding(croppedImage);
		impro.rotateNoCrop(croppedImage, croppedImage, impro.autoRotationAngle(croppedImage));
		cv::resize(croppedImage,croppedImage,cv::Size(150,150) ,0,0); //resizing as for all the rows to have the same size.
		croppedImage=croppedImage.reshape(0,1);	//reshaping the image to vector form. (1 row, row*cols columns) keeping the same colour scheme.

			//Access all the elements of the mat.data
		for (int i=0;i<tempImage.cols;i++){
			if(static_cast<int>(*tempImage.data++) > 1){ //pseudo thresholding too.
				file<<1;
			}else{
				file<<0;
			}
		}

		system(cstr);

	}

	//file.flush();
}
