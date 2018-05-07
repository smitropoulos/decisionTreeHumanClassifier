#include "classifierTrain.hpp"
#include "wizard.hpp"
#include "backgroundSubtractor.hpp"
#include "tree.hpp"

int main(int argc,const char* argv[]){

	auto par=wizard(argc);

	if(par.inputSelection==1){
		backgroundSubtractorProcessor(par.path1, par.path2,par);
	}
	else if (par.inputSelection==2){
		classifierTrain(par);
	}
	else if (par.inputSelection==3){
		std::cout<<"Live demo engaged"<<std::endl;
		backgroundSubtractorProcessor(0);

	}

		//simple tree -overfitting to 100%
	if (par.delimeter=='\t'){
		std::cout<<"\n\nSimple decision tree algorithm - tendency to overfit\n"<<std::endl;
		decTree(par.completeFilename, par.completeFilename2, par.completeFilename3);
	}

	std::cout<<"\nNow the optimized CART algorithm from scikit-learn"<<std::endl;
		//Running a python classifier as a script

	std::string filename = "pythonClassifier.py "+par.completeFilename2;
	std::string command = "./";
	std::string str = command+filename;
	const char *cstr = str.c_str();
	system(cstr);


}

