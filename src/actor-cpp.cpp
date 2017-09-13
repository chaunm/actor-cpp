//============================================================================
// Name        : actor-cpp.cpp
// Author      : ChauNM
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
extern "C" {
#include "ActorParser.h"
#include "universal.h"
#include <string.h>
}
using namespace std;

int main() {
	char* destString;
	char testString[50] = "hello C++";
	destString = StrDup(testString);
	std::cout << "!!!Hello World!!!" << std::endl; // prints !!!Hello World!!!
	std::cout << "\n" << testString << "\n" << std::endl;
	std::cout << destString<< std::endl;
	return 0;
}
