
#ifndef wizard_hpp
#define wizard_hpp

#include <stdio.h>
#include <iostream>
#include <stack>

class params{
public:
	std::string path1,path2;
	std::stack<std::string> stackOfPathsForClasses{};
	std::stack<int> stackOfNumberForClasses{};
	int numberOfClasses=1;
	float splitRatio=0.3;
	char delimeter='\t';
	std::string classifier;
	int inputSelection{};
	bool watchOutputvideo{};
	std::string completeFilename,completeFilename2,completeFilename3;

};

params wizard(int argc);

#endif /* wizard_hpp */
