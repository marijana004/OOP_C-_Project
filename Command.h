#ifndef COMMAND_H
#define COMMAND_H

#pragma warning (disable : 4996);
#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <istream>
using namespace std;


class Command {
private:
	string CommandName;


public:
	Command(string commandName) : CommandName(commandName) {}
	virtual void processOneCommand() = 0;

};

class Echo :public Command {
private:
	string Argument;
public:
	Echo(string argument) :Command("echo"), Argument(argument) {}

	void processOneCommand();
};


class Prompt :public Command {
private:
	string Argument;
public:

	Prompt(string argument) :Command("prompt"), Argument(argument) {}

	void processOneCommand();
};

class Time :public Command {
private:

public:
	Time() :Command("time") {}

	void processOneCommand();
};

class Date :public Command {
private:

public:
	Date() :Command("date") {}

	void processOneCommand();
};


class Touch :public Command {
private:
	string Argument;
public:
	Touch(string argument) :Command("touch"), Argument(argument) {}

	void processOneCommand();
};

class Truncate :public Command {
private:
	string Argument;
public:
	Truncate(string argument) :Command("truncate"), Argument(argument) {}

	void processOneCommand();
};

class RM :public Command {
private:
	string Argument;
public:
	RM(string argument) :Command("rm"), Argument(argument) {}

	void processOneCommand();
};

class WC :public Command {
private:
	string Option;
	string Argument;
public:
	WC(string option, string argument) :Command("wc"), Option(option), Argument(argument) {}

	void processOneCommand();
};

class TR :public Command {
private:
	string Argument;
	string What;
	string With;
public:
	TR(string argument, string what, string with) :Command("tr"), Argument(argument), What(what), With(with) {}

	void processOneCommand();
};

class Head :public Command {
private:
	string Option;
	string Argument;
public:
	Head(string option, string argument) :Command("head"), Option(option), Argument(argument) {}

	void processOneCommand();
};

#endif
