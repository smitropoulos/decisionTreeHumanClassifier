
#ifndef wizard_hpp
#define wizard_hpp

#include <stdio.h>
#include <iostream>
#include <stack>

static std::string path1,path2;
static std::stack<std::string> stackOfPathsForClasses;
static std::stack<int> stackOfNumberForClasses;
static int classes=1;
static int inputSelection=0;
static float splitRatio=0.25;

bool wizard(int argc);


#endif /* wizard_hpp */
