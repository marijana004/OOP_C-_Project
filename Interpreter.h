#ifndef INTERPRETER_H
#define INTERPRETER_H


#include <iostream>
#include <string>
using namespace std;

class Interpreter {

private:
	int LimitLength;
public:

	Interpreter(int limitLength = 512) :LimitLength(limitLength) {}


	string limitCommandLineLenght(string commandLine);
	string removeWhitespaces(string commandLine);
	void runOneCommandLine(string commandLine);
	string readOneWord(string commandLine);
	string deleteFirstWord(string commandLine);

};

#endif