#include "Command.h"
#include "Interpreter.h"
#include "Stream.h"
#include "Singleton.h"


#include <iostream>
#include <string>
using namespace std;

int main() {
	Singleton* obj = Singleton::getInstance();
	Interpreter i;
	Stream s;
	string commandLine;

	while (true) {
		cout << obj->getReadySign() << " ";

		commandLine = s.readOneCommandLine();
		if (commandLine == "exit") break;
		if (commandLine.empty()) continue;
		i.runOneCommandLine(commandLine);
	}


}