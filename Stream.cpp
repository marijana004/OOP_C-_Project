#include "Stream.h"
#include "Command.h"
#include "Interpreter.h"

string Stream::readOneCommandLine()
{
	string line;
	getline(cin, line);
	return line;

}
