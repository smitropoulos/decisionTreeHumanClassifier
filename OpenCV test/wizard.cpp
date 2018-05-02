
#include "wizard.hpp"
#include <iostream>
#include <stack>

bool wizard(int arg){

	int argc = arg;
	bool wizardReturnvalue = false;

if(argc<6 && argc>1) {


	std::cerr << "Provide no arguments for a guide or "
	<< "follow this format [path to images] [extension of images] [class number] [results file name] [test/train ration split (0...1) ] \n";
	return 0;
	}else if (argc==1){
		std::cout<<"#- Welcome to the GMM supervised classifier -#\n"<<
		"* To enter the blob extractor from video please press 1\n"<<
		"* To enter the classifier please press 2"<<std::endl;

		std::cin.ignore(INT_MAX);	//clearing the cin
		std::cin>>inputSelection;

		while (std::cin.fail()) {	//check for type correctness.
			std::cerr<<"You did not make a vaild choice. Please try again."<<std::endl;
		}
	}
	if (inputSelection==1){
		std::cout<<"Please provide the path to your video. "<<std::endl;
		std::cin.ignore(INT_MAX);	//clearing the cin
		std::cin >> path1;
		if (std::cin.fail()) {	//check for type correctness.
			std::cerr<<"You did not make a vaild choice. This programme will now exit."<<std::endl;
			exit(EXIT_FAILURE);
		}
		std::cout<<"Please provide the output location. "<<std::endl;
		std::cin.ignore(INT_MAX);	//clearing the cin
		std::cin >> path2;
		if (std::cin.fail()) {	//check for type correctness.
			std::cerr<<"You did not make a vaild choice. This programme will now exit."<<std::endl;
			exit(EXIT_FAILURE);
		}
	}else if (inputSelection==2){
		std::cout<< "How many classes will there be? " <<std::endl;
		std::cin.ignore(INT_MAX);	//clearing the cin
		std::cin >> classes;
		while (std::cin.fail()) {	//check for type correctness.
			std::cerr<<"You did not make a vaild choice. Please try again.\n"<<std::endl;
			std::cin.ignore(INT_MAX);	//clearing the cin
			std::cin >> classes;
			if (classes>1){
				std::cout<< "Class numbers will begin with "<<classes<<"\n" <<std::endl;

			}
		}
			//Populate a container with the paths of the various classes the user will input.
		while (classes-->0){
			std::cout<< "Please input the path for images of class "<<classes<<"\n" <<std::endl;
			std::cin.ignore(INT_MAX);	//clearing the cin
			std::cin >> path1;
			while (std::cin.fail()) {	//check for type correctness.
				std::cerr<<"You did not make a vaild choice. Please try again.\n"<<std::endl;
				std::cin.ignore(INT_MAX);	//clearing the cin
				std::cin >> path1;
			}
			stackOfPathsForClasses.push(path1);
			stackOfNumberForClasses.push(classes);	//push the class number.
		}
		std::cout<< "Where should the results be stored? " <<std::endl;
		std::cin.ignore(INT_MAX);	//clearing the cin
		std::cin >> path2;
		while (std::cin.fail()) {	//check for type correctness.
			std::cerr<<"You did not make a vaild choice. Please try again.\n"<<std::endl;
			std::cin.ignore(INT_MAX);	//clearing the cin
			std::cin >> path2;
		}
		std::cout<<"Please provide test to train ratio (0..1) . "<<std::endl;
		std::cin.ignore(INT_MAX);	//clearing the cin
		std::cin >> splitRatio;
		if (std::cin.fail()) {	//check for type correctness.
			std::cerr<<"You did not make a vaild choice. This programme will now exit."<<std::endl;
			exit(EXIT_FAILURE);
			}
	}
	wizardReturnvalue=true;
	return wizardReturnvalue;
}
