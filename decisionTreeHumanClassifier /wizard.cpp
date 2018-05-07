
#include "wizard.hpp"
#include <iostream>
#include <stack>
#include <string>

params wizard(int arg){

	params par;
	std::string temp{};


		//DEBUGGING
		//
		//	par.path1 = "/Users/stefanosmitropoulos/Developer/Python/OpenCvTest/human2/";
		//	par.stackOfPathsForClasses.push(par.path1);
		//
		//	par.path1 = "/Users/stefanosmitropoulos/Developer/Python/OpenCvTest/car2/";
		//	par.stackOfPathsForClasses.push(par.path1);
		//
		//	par.numberOfClasses=0;
		//	par.stackOfNumberForClasses.push(par.numberOfClasses);	//push the class number.
		//	par.numberOfClasses=1;
		//	par.stackOfNumberForClasses.push(par.numberOfClasses);	//push the class number.
		//
		//
		//	par.path2 = "/Users/stefanosmitropoulos/Developer/Python/OpenCvTest/results";
		//
		//	par.splitRatio = 0.25;
		//	par.delimeter = '\t';
		//	par.inputSelection = 2;



	try{
		std::cout<<"#- Welcome to the GMM supervised classifier -#\n"<<
		"* To enter the blob extractor from video please press 1\n"<<
		"* To enter the classifier please press 2\n"<<
		"* To enter the demo please press 3"<<std::endl;

		std::getline(std::cin, temp);
		par.inputSelection = std::stoi(temp);

		if (par.inputSelection==1){
			std::cout<<"Please provide the path to your video. "<<std::endl;
			std::getline(std::cin, par.path1);

			std::cout<<"Please provide the output location. "<<std::endl;
			std::getline(std::cin, par.path2);

			std::cout<<"Do you want to watch the video too? [Y/n]";
			std::getline(std::cin, temp);
			if ( temp =="yes" || temp=="Yes"||temp=="y"||temp=="Y"){
				par.watchOutputvideo=true;
			}
			return par;

		}else if (par.inputSelection==2){
			std::cout<< "How many classes will there be? " <<std::endl;
			std::getline(std::cin, temp);
			par.numberOfClasses = std::stoi(temp);
			while (std::cin.fail()) {	//check for type correctness.
				std::cerr<<"You did not make a vaild choice. Please try again.\n"<<std::endl;

				std::getline(std::cin, temp);
				par.numberOfClasses = std::stoi(temp);

				if (par.numberOfClasses>1){
					std::cout<< "Class numbers will begin with "<<par.numberOfClasses<<"\n" <<std::endl;
				}
			}
				//Populate a container with the paths of the various classes the user will input.
			while (par.numberOfClasses-->0){
				std::cout<< "Please input the path for images of class "<<par.numberOfClasses<<" (remember to add / in the end to indicate it is a dir)\nSeriously, don't forget." <<std::endl;
				std::getline(std::cin, par.path1);

				par.stackOfPathsForClasses.push(par.path1);
				par.stackOfNumberForClasses.push(par.numberOfClasses);	//push the class number.
				std::cout<<"So far there are "<<par.stackOfNumberForClasses.size()<<" classes in our buffer"<<std::endl;
			}
			std::cout<< "Where should the results be stored? (Enter a file path without extension) " <<std::endl;

			std::getline(std::cin, par.path2);

			std::cout<<"Please provide test to train ratio (0..1). "<<std::endl;

			std::getline(std::cin, temp);
			par.splitRatio = std::stof(temp);

			std::cout<<"Do you want a csv file as the output?"<<std::endl;

			std::getline(std::cin, temp);
			if ( temp =="yes" || temp=="Yes"){
				par.delimeter = ',';
			}else{
				par.delimeter = '\t';
			}

		}else if (par.inputSelection==3){
			par.inputSelection=3;
		}
		else{
			std::cerr<<"Not valid input. Programme will now exit."<<std::endl;
			exit(1);
		}
	}
	catch(...){
		std::cerr<<"An exception has been caught. The programme will now exit"<<std::endl;
	}
	return par;
}
