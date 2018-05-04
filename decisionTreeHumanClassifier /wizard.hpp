
#ifndef wizard_hpp
#define wizard_hpp

#include <stdio.h>
#include <iostream>
#include <stack>

class params{
public:
	std::string path1,path2;
	std::stack<std::string> stackOfPathsForClasses;
	std::stack<int> stackOfNumberForClasses;
	int numberOfClasses=1;
	float splitRatio;
	char delimeter;
	std::string classifier;
	int inputSelection;
	bool watchOutputvideo;
};

params wizard(int argc);

#endif /* wizard_hpp */
