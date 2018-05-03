
#include "wizard.hpp"
#include <iostream>
#include <stack>


params wizard(int arg){

	int inputSelection=0;
	params par;


//	//debugging purposes
//	par.path2 = "/Users/stefanosmitropoulos/Developer/Python/OpenCvTest/set";
//
//	par.stackOfPathsForClasses.push("/Users/stefanosmitropoulos/Developer/Python/OpenCvTest/car/");
//	par.stackOfPathsForClasses.push("/Users/stefanosmitropoulos/Developer/Python/OpenCvTest/human/");
//
//	par.stackOfNumberForClasses.push(1);
//	par.stackOfNumberForClasses.push(0);
//
//	par.splitRatio = .2;
//
//	return par;
//


	try{
		std::cout<<"#- Welcome to the GMM supervised classifier -#\n"<<
		"* To enter the blob extractor from video please press 1\n"<<
		"* To enter the classifier please press 2"<<std::endl;

		std::cin >> std::ws;
		std::cin>>inputSelection;

		if (inputSelection==1){
			std::cout<<"Please provide the path to your video. "<<std::endl;
			std::cin >> std::ws;
			std::cin >> par.path1;

			std::cout<<"Please provide the output location. "<<std::endl;
			std::cin >> std::ws;
			std::cin >> par.path2;


		}else if (inputSelection==2){
			std::cout<< "How many classes will there be? " <<std::endl;
			std::cin >> std::ws;
			std::cin >> par.numberOfClasses;
			while (std::cin.fail()) {	//check for type correctness.
				std::cerr<<"You did not make a vaild choice. Please try again.\n"<<std::endl;
				std::cin >> std::ws;
				par.numberOfClasses=getchar();
//				std::cin >> par.numberOfClasses;
				if (par.numberOfClasses>1){
					std::cout<< "Class numbers will begin with "<<par.numberOfClasses<<"\n" <<std::endl;
				}
			}
				//Populate a container with the paths of the various classes the user will input.
			while (par.numberOfClasses-->0){
				std::cout<< "Please input the path for images of class "<<par.numberOfClasses<<"\n" <<std::endl;
				std::cin >> std::ws;
				std::cin >> par.path1;

				par.stackOfPathsForClasses.push(par.path1);
				par.stackOfNumberForClasses.push(par.numberOfClasses);	//push the class number.
				std::cout<<"So far there are "<<par.stackOfNumberForClasses.size()<<" classes in our buffer"<<std::endl;
			}
			std::cout<< "Where should the results be stored? " <<std::endl;
			std::cin >> std::ws;
			std::cin >> par.path2;

			std::cout<<"Please provide test to train ratio (0..1). "<<std::endl;

			std::cin >> std::ws;

			std::string temp{};
			std::getline(std::cin, temp);
			par.splitRatio = std::stof(temp);


		}
		else{std::cerr<<"Not valid input. Programme will now exit."<<std::endl;
			exit(1);
}
	}
	catch(...){
		std::cerr<<"An exception has been caught. The programme will now exit"<<std::endl;
	}
	return par;

}
