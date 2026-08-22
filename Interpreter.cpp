#include "Interpreter.h"
#include "Command.h"
#include "Stream.h"
#include <cctype>





string Interpreter::limitCommandLineLenght(string commandLine)
{
    if (commandLine.length() > LimitLength) {
        commandLine.resize(LimitLength);
    }

    return commandLine;
}

string Interpreter::removeWhitespaces(string commandLine)
{
    size_t strBegin = commandLine.find_first_not_of(" \t");
    size_t strEnd = commandLine.find_last_not_of(" \t");
    size_t strRange = strEnd - strBegin + 1;
    return commandLine.substr(strBegin, strRange);
}

string Interpreter::readOneWord(string commandLine)
{
    return commandLine.substr(0, commandLine.find(" "));
}

string Interpreter::deleteFirstWord(string commandLine)
{
    commandLine = removeWhitespaces(commandLine);
    string commandLineDeleted = commandLine.substr(commandLine.find_first_of(" \t") + 1);
    if (commandLine == commandLineDeleted) return "";
    commandLineDeleted = removeWhitespaces(commandLineDeleted);
    return commandLineDeleted;
}

void Interpreter::runOneCommandLine(string commandLine)
{
	commandLine = limitCommandLineLenght(commandLine);
	commandLine = removeWhitespaces(commandLine);

	string commandName = readOneWord(commandLine);
	commandLine = deleteFirstWord(commandLine);

	Command* command = nullptr;

	if (commandName == "echo") {
		string argument = commandLine;
		command = new Echo(argument);
	}

	else if (commandName == "prompt") {
		string argument = commandLine;
		command = new Prompt(argument);
	}

	else if (commandName == "time") {
		if (commandLine == "") {
			command = new Time();
		}
		else {
			cout << "Error. Invalid Command Time Input!" << endl;
		}
	}

	else if (commandName == "date") {
		if (commandLine == "") {
			command = new Date();

		}
		else {
			cout << "'" << commandLine << "'" << endl;
			cout << "Error. Invalid Command Date Input!" << endl;
		}
	}

	else if (commandName == "touch") {
		string argument = commandLine;
		command = new Touch(argument);
	}

	else if (commandName == "truncate") {
		string argument = commandLine;
		command = new Truncate(argument);
	}

	else if (commandName == "rm") {
		string argument = commandLine;
		command = new RM(argument);
	}

	else if (commandName == "wc") {
		string option = readOneWord(commandLine);
		commandLine = deleteFirstWord(commandLine);

		string argument = commandLine;

		command = new WC(option, argument);
	}

	else if (commandName == "tr") {
		string what, with;
		int positionOfLine = commandLine.find('-');
		if (commandLine[positionOfLine + 1] == '"')
		{//
			string argument = commandLine.substr(0, positionOfLine);
			if (argument == "") {

				commandLine = commandLine.substr(argument.length() + 2, commandLine.length());

				what = commandLine.substr(0, commandLine.find_first_of('"'));
				with = commandLine.substr(what.length() + 1, commandLine.length());
			}

			else {
				argument = argument.substr(0, argument.length() - 1);
				commandLine = commandLine.substr(argument.length() + 3, commandLine.length());

				what = commandLine.substr(0, commandLine.find_first_of('"'));
				with = commandLine.substr(what.length() + 1, commandLine.length());

			}
			
			if (!(argument == ""))
			{
				argument = removeWhitespaces(argument);
			}
			else argument = "";

			if (!(with == ""))
			{
			with = removeWhitespaces(with);
			}
			else with = "";
			
			what = removeWhitespaces(what);


			if (with.length() > 0) {
			with = with.substr(1, with.length() - 2);
			}


			command = new TR(argument, what, with);
		}

		else { cout << "Error!" << endl; }


	}







	else if (commandName == "head") {
		string option = readOneWord(commandLine);
		commandLine = deleteFirstWord(commandLine);

		string argument = commandLine;

		command = new Head(option, argument);
	}
	else {
		cout << "Error! Invalid command name." << endl;
	}

	if (command) {
		command->processOneCommand();
		delete command;
	}


}