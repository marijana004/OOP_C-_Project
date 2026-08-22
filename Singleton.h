#ifndef SINGLETON_H
#define SINGLETON_H


#include <iostream>
#include <string>
using namespace std;

class Singleton {

protected:
	string ReadySign; //value_

private:
	static Singleton* inst_;
	Singleton() : ReadySign("$") {} // value_
	Singleton(const Singleton&);
	//Singleton& operator=(const Singleton&);


public:
	static Singleton* getInstance();

	void setReadySign(string readySign) { ReadySign = readySign; }
	string getReadySign() { return ReadySign; }

};


#endif