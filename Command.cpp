#include "Command.h"
#include "Stream.h"
#include "Interpreter.h"
#include "Singleton.h"

#include <vector>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
using namespace std;

void Echo::processOneCommand()
{
	if (Argument.empty()) {
		string line;
		vector <string> lines;

		while (true) {
			getline(cin, line);

			if (line.empty() && cin.eof()) {
				cin.clear();
				break;
			}
			lines.push_back(line);
		}
		for (const string& l : lines) {
			cout<<l + "\n";
		}
	}

	else if (Argument.front() == '"' && Argument.back() == '"') {
		string content = Argument.substr(1, Argument.size() - 2);
		
		if (content.find('"') != string::npos) {
			cout << "Error! Incorrect character in the argument!" << endl;
		}
		else {
			cout << content << endl;
		}
	
	}
	else if (Argument.front() == '<') {
		string input = Argument.substr(1, Argument.find(" "));
		Argument = Argument.substr(input.length()+1, Argument.length());
		
		size_t strBegin = Argument.find_first_not_of(" \t");
		size_t strEnd = Argument.find_last_not_of(" \t");
		size_t strRange = strEnd - strBegin + 1;
		Argument = Argument.substr(strBegin, strRange);
		if (Argument.front() == '>') {
			Argument = Argument.substr(1, Argument.length());
			if (Argument.front() == '>') {
				Argument = Argument.substr(1, Argument.length());
				
				ofstream outputFile;
				outputFile.open(Argument, std::ios::app);
				if (!outputFile) {
					ofstream outputFile(Argument);
				}

				ifstream inputFile(input);
				if (inputFile.is_open()) {
					string file_contents{ istreambuf_iterator<char>(inputFile), istreambuf_iterator<char>() };
					outputFile << file_contents;

				}
				else {
					cout << "Error! The input file does not exist!" << endl;
				}
				outputFile.close();
				inputFile.close();
			}
			else {

				ofstream outputFile;
				outputFile.open(Argument);
				if (!outputFile) {
					ofstream outputFile(Argument);
				}

				ifstream inputFile(input);
				if (inputFile.is_open()) {
					string file_contents{ istreambuf_iterator<char>(inputFile), istreambuf_iterator<char>() };
					outputFile << file_contents;

				}
				else {
					cout << "Error! The input file does not exist!" << endl;
				}
				outputFile.close();
				inputFile.close();
			}
		}
	}

	else if (Argument.front() == '>') {
		string output = Argument.substr(1, Argument.find(" "));
		Argument = Argument.substr(output.length() + 1, Argument.length());
		size_t strBegin = Argument.find_first_not_of(" \t");
		size_t strEnd = Argument.find_last_not_of(" \t");
		size_t strRange = strEnd - strBegin + 1;
		Argument = Argument.substr(strBegin, strRange);
		if (output.front() == '>') {
			output = output.substr(1, output.length());
			if (Argument.front() == '<') {
				Argument = Argument.substr(1, Argument.length());

				ofstream outputFile;
				outputFile.open(output, std::ios::app);
				if (!outputFile) {
					ofstream outputFile(output);
				}

				ifstream inputFile(Argument);
				if (inputFile.is_open()) {
					string file_contents{ istreambuf_iterator<char>(inputFile), istreambuf_iterator<char>() };
					outputFile << file_contents;

				}
				else {
					cout << "Error! The input file does not exist!" << endl;
				}
				outputFile.close();
				inputFile.close();
			}
			else {
				cout << "Error! The input file does not exist!" << endl;
			}
		}
		else {
			if (Argument.front() == '<') {
				Argument = Argument.substr(1, Argument.length());
				ofstream outputFile;
				outputFile.open(output);
				if (!outputFile) {
					ofstream outputFile(output);
				}

				ifstream inputFile(Argument);
				if (inputFile.is_open()) {
					string file_contents{ istreambuf_iterator<char>(inputFile), istreambuf_iterator<char>() };
					outputFile << file_contents;

				}
				else {
					cout << "Error! The input file does not exist!" << endl;
				}
				outputFile.close();
				inputFile.close();
			}
			else {
				cout << "Error! The input file does not exist!" << endl;
			}
		}
	}

	else if (Argument.front() == '<' && Argument.back() != '"' && !Argument.empty()) {
		string nameFile = Argument.substr(1, Argument.size() - 1);
		ifstream file(nameFile);
		if (file.is_open()) {
			string file_contents{ istreambuf_iterator<char>(file), istreambuf_iterator<char>() };
			cout << file_contents << endl;
		}
		else {
			cout << "Error! The file does not exist!" << endl;
		}
	}

	else if (Argument.front() != '"' && Argument.back() != '"' && !Argument.empty()) {
		ifstream file(Argument);
		if (file.is_open()) {
			string file_contents{ istreambuf_iterator<char>(file), istreambuf_iterator<char>() };
			cout << file_contents << endl;
		}
		else {
			cout<<"Error! The file does not exist!"<<endl;
		}
	
	}

	else if (Argument.front() == '"' && Argument.back() != '"') {
		Argument = Argument.substr(1, Argument.length());
		size_t strEnd = Argument.find_first_of('"');	
		string output = Argument.substr(strEnd+1, Argument.length());

		Argument = Argument.substr(0, strEnd);

		size_t Begin = output.find_first_not_of(" \t");
		size_t End = output.find_last_not_of(" \t");
		size_t Range = End - Begin + 1;
		output = output.substr(Begin+1, Range);

		if (output.front() == '>') {
			output = output.substr(1, output.length());
			ofstream outputFile;
			outputFile.open(output, std::ios::app);
			if (!outputFile) {
				ofstream outputFile(output);
			}
			outputFile << Argument;
		}
		else {
			ofstream outputFile;
			outputFile.open(output);
			if (!outputFile) {
				ofstream outputFile(output);
			}
			outputFile << Argument;
		}

	}

	else {
		cout << "Error! Incorrect input!"<<endl;
	}


}


void Prompt::processOneCommand()
{
	Argument = Argument.substr(1, Argument.size() - 2);

	Singleton* o = Singleton::getInstance();
	o->setReadySign(Argument);
	
}

void Time::processOneCommand()
{
	time_t t = time(&t);
	struct tm datetime = *localtime(&t);

	cout << datetime.tm_hour << ":" << datetime.tm_min << ":" << datetime.tm_sec << endl;
}

void Date::processOneCommand()
{
	time_t t = time(NULL);
	struct tm datetime = *localtime(&t);
	char output[50];

	strftime(output, 50, "%d.%m.20%y.", &datetime);
	cout << output << "\n";
}

void Touch::processOneCommand() {

	ifstream file;
	file.open(Argument);
	if (file) {
		cout << "Greska! Fajl vec postoji!" << endl;
	}
	else {
		ofstream file(Argument);
	}
	file.close();
}

void Truncate::processOneCommand()
{
	ofstream file(Argument, ios::trunc);
}


void RM::processOneCommand()
{
	int status = remove(Argument.c_str());
	if (status != 0) cout << "RM: File does not exist." << endl;

}


void WC::processOneCommand()
{
	if (Option == "-w") {
		//ako je argument prazan
		if (Argument.empty()) {
			int wordCount = 0;

			while (true) {
				string line;
				getline(cin, line);
				if (line.empty() && cin.eof()) {
					cin.clear();
					break;
				}

				stringstream stream(line);
				string word;

				while (stream >> word) {
					wordCount++;
				}
			}
			cout << to_string(wordCount) + "\n";
		}
		//ako je argument pod navodnicima
		else if (!Argument.empty() && Argument.front() == '"' && Argument.back() == '"') {

			string content = Argument.substr(1, Argument.size() - 2);

			if (content.find('"') != string::npos) {
				cout<<"Error! Incorrect character in the argument!\n";
			}
			else {
				stringstream stream(content);
				string word;
				int wordCount = 0;

				while (stream >> word) {
					wordCount++;
				}

				cout<<to_string(wordCount) + "\n";
			}
		}
		

		//ako argument pocinje sa <
		else if (Argument.front() == '<') {
			
			string input = Argument.substr(1, Argument.find(" "));
			string output = Argument.substr(input.length() + 1, Argument.length());


			//ako je argument <input.txt
			if (output == "") {

				ifstream file(input);

				if (file.is_open()) {
					int wordCount = 0;
					string line;

					while (getline(file, line)) {
						stringstream stream(line);
						string word;

						while (stream >> word) {
							wordCount++;
						}
					}
					file.close();

					cout << to_string(wordCount) + "\n";
				}
				else {
					cout << "Error! The file does not exist!\n";
				}

			}

			else {
				size_t strBegin = output.find_first_not_of(" \t");
				size_t strEnd = output.find_last_not_of(" \t");
				size_t strRange = strEnd - strBegin + 1;
				output = output.substr(strBegin, strRange);

				if (output.front() == '>') {
					output = output.substr(1, output.size() - 1);

					//ako je argument <input.txt >>output.txt
					if (output.front() == '>') {
						output = output.substr(1, output.size() - 1);

						ofstream outputFile;
						outputFile.open(output, std::ios::app);
						if (!outputFile) {
							ofstream outputFile(output);
						}

						ifstream inputFile(input);
						if (inputFile.is_open()) {

							int wordCount = 0;
							string line;

							while (getline(inputFile, line)) {
								stringstream stream(line);
								string word;

								while (stream >> word) {
									wordCount++;
								}
							}
							inputFile.close();

							outputFile << to_string(wordCount) + "\n";

						}
						else {
							cout << "Error! The input file does not exist!" << endl;
						}
						outputFile.close();
						inputFile.close();
						//
					}

					//ako je argument <input.txt >output.txt
					else {

						ofstream outputFile;
						outputFile.open(output);
						if (!outputFile) {
							ofstream outputFile(output);
						}

						ifstream inputFile(input);
						if (inputFile.is_open()) {

							int wordCount = 0;
							string line;

							while (getline(inputFile, line)) {
								stringstream stream(line);
								string word;

								while (stream >> word) {
									wordCount++;
								}
							}
							inputFile.close();

							outputFile << to_string(wordCount) + "\n";

						}
						else {
							cout << "Error! The input file does not exist!" << endl;
						}
						outputFile.close();
						inputFile.close();

					}







				}

				else { cout << "Error." << endl; }
			}

			
	
		}


		//ako argument pocinje sa >	
		else if (Argument.front() == '>') {


				string output = Argument.substr(1, Argument.find(" "));
				string input = Argument.substr(output.length() + 1, Argument.length());


				size_t strBegin = input.find_first_not_of(" \t");
				size_t strEnd = input.find_last_not_of(" \t");
				size_t strRange = strEnd - strBegin + 1;
				input = input.substr(strBegin+1, strRange);


				//ako je argument >>output.txt <input.txt
				
				if (output.front() == '>') {
						output = output.substr(1, output.size() - 1);

							ofstream outputFile;
							outputFile.open(output, std::ios::app);
							if (!outputFile) {
								ofstream outputFile(output);
							}

							ifstream inputFile(input);
							if (inputFile.is_open()) {

								int wordCount = 0;
								string line;

								while (getline(inputFile, line)) {
									stringstream stream(line);
									string word;

									while (stream >> word) {
										wordCount++;
									}
								}
								inputFile.close();

								outputFile << to_string(wordCount) + "\n";

							}
							else {
								cout << "Error! The input file does not exist!" << endl;
							}
							outputFile.close();
							inputFile.close();
							//
						}

				//ako je argument >output.txt <input.txt
				else {

							ofstream outputFile;
							outputFile.open(output);
							if (!outputFile) {
								ofstream outputFile(output);
							}

							ifstream inputFile(input);
							if (inputFile.is_open()) {

								int wordCount = 0;
								string line;

								while (getline(inputFile, line)) {
									stringstream stream(line);
									string word;

									while (stream >> word) {
										wordCount++;
									}
								}
								inputFile.close();

								outputFile << to_string(wordCount) + "\n";

							}
							else {
								cout << "Error! The input file does not exist!" << endl;
							}
							outputFile.close();
							inputFile.close();

						}
				

		}



		//ako argument pocinje sa "" a zavrsava se sa >>output.txt ili >output.txt
		else if (Argument.front() == '"' && Argument.back() != '"') {

			string input = Argument.substr(1, Argument.length());
			input = input.substr(1, input.find_first_of('"')-1);
			string output = Argument.substr(input.length() + 3, Argument.length());

			size_t strBegin = output.find_first_not_of(" \t");
			size_t strEnd = output.find_last_not_of(" \t");
			size_t strRange = strEnd - strBegin + 1;
			output = output.substr(strBegin, strRange);


			if (output.front() == '>') {
				output = output.substr(1, output.length());

				//argument se zavrsava sa >>output.txt
				if (output.front() == '>') {
					output = output.substr(1, output.length());

					ofstream outputFile;
					outputFile.open(output, std::ios::app);
					if (!outputFile) {
						ofstream outputFile(output);
					}
					
					stringstream stream(input);
					string word;
					int wordCount = 0;

					while (stream >> word) {
						wordCount++;
					}

					outputFile << to_string(wordCount) + "\n";


				}

				//argument se zavrsava sa >output.txt
				else {
					ofstream outputFile;
					outputFile.open(output);
					if (!outputFile) {
						ofstream outputFile(output);
					}

					stringstream stream(input);
					string word;
					int wordCount = 0;

					while (stream >> word) {
						wordCount++;
					}

					outputFile << to_string(wordCount) + "\n";
				}
			}
			else {
				cout << "Error." << endl;
			}
		}






		//ako je argument input.txt
		else if (Argument[0] != '"' && Argument.back() != '"' && !Argument.empty()) {

			
			ifstream file(Argument);

			if (file.is_open()) {
				int wordCount = 0;
				string line;

				while (getline(file, line)) {
					stringstream stream(line);
					string word;

					while (stream >> word) {
						wordCount++;
					}
				}
				file.close();

				cout<<to_string(wordCount) + "\n";
			}
			else {
				cout<<"Error! The file does not exist!\n";
			}
		}
		//ostalo
		else {
			cout<<"Error! Incorrect input!\n";
		}
	
	}


	else if (Option == "-c") {
		if (Argument.empty()) {
			int charCount = 0;

			while (true) {
				string line;
				getline(cin, line);
				if (line.empty() && cin.eof()) {
					cin.clear();
					break;
				}
				charCount += line.size();
				charCount++;
			}
			cout<<to_string(charCount) + "\n";
		}

		else if (!Argument.empty() && Argument.front() == '"' && Argument.back() == '"') {

			string content = Argument.substr(1, Argument.size() - 2);

			if (content.find('"') != string::npos) {
				cout<<"Error! Incorrect character in the argument!\n";
			}
			else {
				int charCount = content.size();
				cout<<to_string(charCount) + "\n";
			}
		}
		

		else if (Argument.front() == '<') {

			string input = Argument.substr(1, Argument.find(" "));
			string output = Argument.substr(input.length() + 1, Argument.length());


			//ako je argument <input.txt
			if (output == "") {

				ifstream file(input);

				if (file.is_open()) {
					int charCount = 0;
					string line;

					while (getline(file, line)) {
						charCount += line.size();
						charCount++;
					}
					file.close();

					cout << to_string(charCount) + "\n";
				}
				else {
					cout << "Error! The file does not exist!\n";
				}

			}

			else {
				size_t strBegin = output.find_first_not_of(" \t");
				size_t strEnd = output.find_last_not_of(" \t");
				size_t strRange = strEnd - strBegin + 1;
				output = output.substr(strBegin, strRange);

				if (output.front() == '>') {
					output = output.substr(1, output.size() - 1);

					//ako je argument <input.txt >>output.txt
					if (output.front() == '>') {
						output = output.substr(1, output.size() - 1);

						ofstream outputFile;
						outputFile.open(output, std::ios::app);
						if (!outputFile) {
							ofstream outputFile(output);
						}

						ifstream inputFile(input);
						if (inputFile.is_open()) {

							int charCount = 0;
							string line;

							while (getline(inputFile, line)) {
								charCount += line.size();
								charCount++;
							}

							inputFile.close();

							outputFile << to_string(charCount) + "\n";

						}
						else {
							cout << "Error! The input file does not exist!" << endl;
						}
						outputFile.close();
						inputFile.close();
						//
					}

					//ako je argument <input.txt >output.txt
					else {

						ofstream outputFile;
						outputFile.open(output);
						if (!outputFile) {
							ofstream outputFile(output);
						}

						ifstream inputFile(input);
						if (inputFile.is_open()) {

							int charCount = 0;
							string line;

							while (getline(inputFile, line)) {
								charCount += line.size();
								charCount++;
							}

							inputFile.close();

							outputFile << to_string(charCount) + "\n";

						}
						else {
							cout << "Error! The input file does not exist!" << endl;
						}
						outputFile.close();
						inputFile.close();

					}







				}

				else { cout << "Error." << endl; }
			}



		}


		//ako argument pocinje sa >	
		else if (Argument.front() == '>') {


			string output = Argument.substr(1, Argument.find(" "));
			string input = Argument.substr(output.length() + 1, Argument.length());


			size_t strBegin = input.find_first_not_of(" \t");
			size_t strEnd = input.find_last_not_of(" \t");
			size_t strRange = strEnd - strBegin + 1;
			input = input.substr(strBegin + 1, strRange);


			//ako je argument >>output.txt <input.txt

			if (output.front() == '>') {
				output = output.substr(1, output.size() - 1);

				ofstream outputFile;
				outputFile.open(output, std::ios::app);
				if (!outputFile) {
					ofstream outputFile(output);
				}

				ifstream inputFile(input);
				if (inputFile.is_open()) {

					int charCount = 0;
					string line;

					while (getline(inputFile, line)) {
						charCount += line.size();
						charCount++;
					}

					inputFile.close();

					outputFile << to_string(charCount) + "\n";

				}
				else {
					cout << "Error! The input file does not exist!" << endl;
				}
				outputFile.close();
				inputFile.close();
				//
			}

			//ako je argument >output.txt <input.txt
			else {

				ofstream outputFile;
				outputFile.open(output);
				if (!outputFile) {
					ofstream outputFile(output);
				}

				ifstream inputFile(input);
				if (inputFile.is_open()) {

					int charCount = 0;
					string line;

					while (getline(inputFile, line)) {
						charCount += line.size();
						charCount++;
					}

					inputFile.close();

					outputFile << to_string(charCount) + "\n";

				}
				else {
					cout << "Error! The input file does not exist!" << endl;
				}
				outputFile.close();
				inputFile.close();

			}


		}


		//ako argument pocinje sa "" a zavrsava se sa >>output.txt ili >output.txt
		else if (Argument.front() == '"' && Argument.back() != '"') {

			string input = Argument.substr(1, Argument.length());
			input = input.substr(1, input.find_first_of('"') - 1);
			string output = Argument.substr(input.length() + 3, Argument.length());

			size_t strBegin = output.find_first_not_of(" \t");
			size_t strEnd = output.find_last_not_of(" \t");
			size_t strRange = strEnd - strBegin + 1;
			output = output.substr(strBegin, strRange);


			if (output.front() == '>') {
				output = output.substr(1, output.length());

				//argument se zavrsava sa >>output.txt
				if (output.front() == '>') {
					output = output.substr(1, output.length());

					ofstream outputFile;
					outputFile.open(output, std::ios::app);
					if (!outputFile) {
						ofstream outputFile(output);
					}

					stringstream stream(input);
					string word;
					int charCount = 0;

					while (stream >> word) {
						charCount= charCount + word.length();
					}

					outputFile << to_string(charCount) + "\n";


				}

				//argument se zavrsava sa >output.txt
				else {
					ofstream outputFile;
					outputFile.open(output);
					if (!outputFile) {
						ofstream outputFile(output);
					}

					stringstream stream(input);
					string word;
					int charCount = 0;

					while (stream >> word) {
						charCount = charCount + word.length();
					}

					outputFile << to_string(charCount) + "\n";
				}
			}
			else {
				cout << "Error." << endl;
			}
		}



		//ako je argument input.txt
		else if (Argument[0] != '"' && Argument.back() != '"' && !Argument.empty()) {


			ifstream file(Argument);

			if (file.is_open()) {
				int charCount = 0;
				string line;

				while (getline(file, line)) {
					charCount += line.size();
					charCount++;
				}
				file.close();

				cout << to_string(charCount) + "\n";

			}
			else {
				cout << "Error! The file does not exist!\n";
			}
		}
		//ostalo
		else {
			cout << "Error! Incorrect input!\n";
		}
	}


	else { cout << "Unknown option: " + Option + "\n"; }

}






//nije promenjeno
void TR::processOneCommand()
{
	//ako je argument prazan
	if (Argument.empty()) {
		int wordCount = 0;

		while (true) {
			string line;
			getline(cin, line);
			if (line.empty() && cin.eof()) {
				cin.clear();
				break;
			}

			stringstream stream(line);
			string word;

			while (stream >> word) {
				wordCount++;
			}
		}
		cout << to_string(wordCount) + "\n";
	}



















	//ako je argument pod navodnicima
	else if (!Argument.empty() && Argument.front() == '"' && Argument.back() == '"') {

		string content = Argument.substr(1, Argument.size() - 2);

		if (content.find('"') != string::npos) {
			cout << "Error! Incorrect character in the argument!\n";
		}
		else {
			stringstream stream(content);
			string word;
			int wordCount = 0;

			while (stream >> word) {
				wordCount++;
			}

			cout << to_string(wordCount) + "\n";
		}
	}


	//ako argument pocinje sa <
	else if (Argument.front() == '<') {

		string input = Argument.substr(1, Argument.find(" "));
		string output = Argument.substr(input.length() + 1, Argument.length());


		//ako je argument <input.txt
		if (output == "") {

			ifstream file(input);

			if (file.is_open()) {
				int wordCount = 0;
				string line;

				while (getline(file, line)) {
					stringstream stream(line);
					string word;

					while (stream >> word) {
						wordCount++;
					}
				}
				file.close();

				cout << to_string(wordCount) + "\n";
			}
			else {
				cout << "Error! The file does not exist!\n";
			}

		}

		else {
			size_t strBegin = output.find_first_not_of(" \t");
			size_t strEnd = output.find_last_not_of(" \t");
			size_t strRange = strEnd - strBegin + 1;
			output = output.substr(strBegin, strRange);

			if (output.front() == '>') {
				output = output.substr(1, output.size() - 1);

				//ako je argument <input.txt >>output.txt
				if (output.front() == '>') {
					output = output.substr(1, output.size() - 1);

					ofstream outputFile;
					outputFile.open(output, std::ios::app);
					if (!outputFile) {
						ofstream outputFile(output);
					}

					ifstream inputFile(input);
					if (inputFile.is_open()) {

						int wordCount = 0;
						string line;

						while (getline(inputFile, line)) {
							stringstream stream(line);
							string word;

							while (stream >> word) {
								wordCount++;
							}
						}
						inputFile.close();

						outputFile << to_string(wordCount) + "\n";

					}
					else {
						cout << "Error! The input file does not exist!" << endl;
					}
					outputFile.close();
					inputFile.close();
					//
				}

				//ako je argument <input.txt >output.txt
				else {

					ofstream outputFile;
					outputFile.open(output);
					if (!outputFile) {
						ofstream outputFile(output);
					}

					ifstream inputFile(input);
					if (inputFile.is_open()) {

						int wordCount = 0;
						string line;

						while (getline(inputFile, line)) {
							stringstream stream(line);
							string word;

							while (stream >> word) {
								wordCount++;
							}
						}
						inputFile.close();

						outputFile << to_string(wordCount) + "\n";

					}
					else {
						cout << "Error! The input file does not exist!" << endl;
					}
					outputFile.close();
					inputFile.close();

				}







			}

			else { cout << "Error." << endl; }
		}



	}


	//ako argument pocinje sa >	
	else if (Argument.front() == '>') {


		string output = Argument.substr(1, Argument.find(" "));
		string input = Argument.substr(output.length() + 1, Argument.length());


		size_t strBegin = input.find_first_not_of(" \t");
		size_t strEnd = input.find_last_not_of(" \t");
		size_t strRange = strEnd - strBegin + 1;
		input = input.substr(strBegin + 1, strRange);


		//ako je argument >>output.txt <input.txt

		if (output.front() == '>') {
			output = output.substr(1, output.size() - 1);

			ofstream outputFile;
			outputFile.open(output, std::ios::app);
			if (!outputFile) {
				ofstream outputFile(output);
			}

			ifstream inputFile(input);
			if (inputFile.is_open()) {

				int wordCount = 0;
				string line;

				while (getline(inputFile, line)) {
					stringstream stream(line);
					string word;

					while (stream >> word) {
						wordCount++;
					}
				}
				inputFile.close();

				outputFile << to_string(wordCount) + "\n";

			}
			else {
				cout << "Error! The input file does not exist!" << endl;
			}
			outputFile.close();
			inputFile.close();
			//
		}

		//ako je argument >output.txt <input.txt
		else {

			ofstream outputFile;
			outputFile.open(output);
			if (!outputFile) {
				ofstream outputFile(output);
			}

			ifstream inputFile(input);
			if (inputFile.is_open()) {

				int wordCount = 0;
				string line;

				while (getline(inputFile, line)) {
					stringstream stream(line);
					string word;

					while (stream >> word) {
						wordCount++;
					}
				}
				inputFile.close();

				outputFile << to_string(wordCount) + "\n";

			}
			else {
				cout << "Error! The input file does not exist!" << endl;
			}
			outputFile.close();
			inputFile.close();

		}


	}



	//ako argument pocinje sa "" a zavrsava se sa >>output.txt ili >output.txt
	else if (Argument.front() == '"' && Argument.back() != '"') {

		string input = Argument.substr(1, Argument.length());
		input = input.substr(1, input.find_first_of('"') - 1);
		string output = Argument.substr(input.length() + 3, Argument.length());

		size_t strBegin = output.find_first_not_of(" \t");
		size_t strEnd = output.find_last_not_of(" \t");
		size_t strRange = strEnd - strBegin + 1;
		output = output.substr(strBegin, strRange);


		if (output.front() == '>') {
			output = output.substr(1, output.length());

			//argument se zavrsava sa >>output.txt
			if (output.front() == '>') {
				output = output.substr(1, output.length());

				ofstream outputFile;
				outputFile.open(output, std::ios::app);
				if (!outputFile) {
					ofstream outputFile(output);
				}

				stringstream stream(input);
				string word;
				int wordCount = 0;

				while (stream >> word) {
					wordCount++;
				}

				outputFile << to_string(wordCount) + "\n";


			}

			//argument se zavrsava sa >output.txt
			else {
				ofstream outputFile;
				outputFile.open(output);
				if (!outputFile) {
					ofstream outputFile(output);
				}

				stringstream stream(input);
				string word;
				int wordCount = 0;

				while (stream >> word) {
					wordCount++;
				}

				outputFile << to_string(wordCount) + "\n";
			}
		}
		else {
			cout << "Error." << endl;
		}
	}






	//ako je argument input.txt
	else if (Argument[0] != '"' && Argument.back() != '"' && !Argument.empty()) {


		ifstream file(Argument);

		if (file.is_open()) {
			int wordCount = 0;
			string line;

			while (getline(file, line)) {
				stringstream stream(line);
				string word;

				while (stream >> word) {
					wordCount++;
				}
			}
			file.close();

			cout << to_string(wordCount) + "\n";
		}
		else {
			cout << "Error! The file does not exist!\n";
		}
	}
	//ostalo
	else {
		cout << "Error! Incorrect input!\n";
	}

}








void Head::processOneCommand()
{
	Option = Option.substr(2, Option.length()-2);
	int number = stoi(Option);

	{
		if (Argument.empty()) {
			string line;
			vector <string> lines;
			while (true) {
				getline(cin, line);
				if (line.empty() && cin.eof()) {
					cin.clear();
					break;
				}
				lines.push_back(line);
			}
			int i = 1;
				for (const string& l : lines) {
					cout << l + "\n";
					i++;
					if (i > number) break;
				}
		}

		//pocinje i zavrsava se sa ""
		else if (!Argument.empty() && Argument.front() == '"' && Argument.back() == '"') {

			string content = Argument.substr(1, Argument.size() - 2);

			if (content.find('"') != string::npos) {
				cout << "Error! Incorrect character in the argument!\n";
			}
			else {
				cout << content << endl;
				}
		}

		//pocinje sa < 
		else if (Argument.front() == '<') {

			string input = Argument.substr(1, Argument.find(" "));
			string output = Argument.substr(input.length() + 1, Argument.length());


			//ako je argument <input.txt
			if (output == "") {

				ifstream inputFile(input);
				///////////////
				if (inputFile.is_open()) {
					int i = 1;
					string line;
					while (getline(inputFile, line)) {
						cout << line + "\n";
						i++;
						if (i > number) break;
					}
					inputFile.close();

				}
				else {
					cout << "Error! The file does not exist!\n";
				}

			}

			else {
				size_t strBegin = output.find_first_not_of(" \t");
				size_t strEnd = output.find_last_not_of(" \t");
				size_t strRange = strEnd - strBegin + 1;
				output = output.substr(strBegin, strRange);

				if (output.front() == '>') {
					output = output.substr(1, output.size() - 1);

					//ako je argument <input.txt >>output.txt
					if (output.front() == '>') {
						output = output.substr(1, output.size() - 1);

						ofstream outputFile;
						outputFile.open(output, std::ios::app);
						if (!outputFile) {
							ofstream outputFile(output);
						}

						ifstream inputFile(input);
						///////////////
						if (inputFile.is_open()) {
							int i = 1;
							string line;
							while (getline(inputFile, line)) {
								outputFile << line + "\n";
								i++;
								if (i > number) break;
							}
							inputFile.close();
							outputFile.close();
						}
						else {
							cout << "Error! The file does not exist!\n";
						}
					}

					//ako je argument <input.txt >output.txt
					else {

						ofstream outputFile;
						outputFile.open(output);
						if (!outputFile) {
							ofstream outputFile(output);
						}

						ifstream inputFile(input);
						///////////////
						if (inputFile.is_open()) {
							int i = 1;
							string line;
							while (getline(inputFile, line)) {
								outputFile << line + "\n";
								i++;
								if (i > number) break;
							}
							inputFile.close();
							outputFile.close();
						}
						else {
							cout << "Error! The file does not exist!\n";
						}
						

					}







				}

				else { cout << "Error." << endl; }
			}



		}


		//ako argument pocinje sa >	
		else if (Argument.front() == '>') {


			string output = Argument.substr(1, Argument.find(" "));
			string input = Argument.substr(output.length() + 1, Argument.length());


			size_t strBegin = input.find_first_not_of(" \t");
			size_t strEnd = input.find_last_not_of(" \t");
			size_t strRange = strEnd - strBegin + 1;
			input = input.substr(strBegin + 1, strRange);


			//ako je argument >>output.txt <input.txt

			if (output.front() == '>') {
				output = output.substr(1, output.size() - 1);

				ofstream outputFile;
				outputFile.open(output, std::ios::app);
				if (!outputFile) {
					ofstream outputFile(output);
				}

				ifstream inputFile(input);
				if (inputFile.is_open()) {

					int i = 1;
					string line;
					while (getline(inputFile, line)) {
						outputFile << line + "\n";
						i++;
						if (i > number) break;
					}
					inputFile.close();
					outputFile.close();
				}

				else {
					cout << "Error! The input file does not exist!" << endl;
				}
				outputFile.close();
				inputFile.close();
				//
			}

			//ako je argument >output.txt <input.txt
			else {

				ofstream outputFile;
				outputFile.open(output);
				if (!outputFile) {
					ofstream outputFile(output);
				}

				ifstream inputFile(input);
				if (inputFile.is_open()) {

					int i = 1;
					string line;
					while (getline(inputFile, line)) {
						outputFile << line + "\n";
						i++;
						if (i > number) break;
					}
					inputFile.close();
					outputFile.close();
				}
			}


		}


		//ako argument pocinje sa "" a zavrsava se sa >>output.txt ili >output.txt	
		else if (Argument.front() == '"' && Argument.back() != '"') {

			string input = Argument.substr(1, Argument.length());
			input = input.substr(0, input.find_first_of('"'));
			string output = Argument.substr(input.length() + 3, Argument.length());

			size_t strBegin = output.find_first_not_of(" \t");
			size_t strEnd = output.find_last_not_of(" \t");
			size_t strRange = strEnd - strBegin + 1;
			output = output.substr(strBegin, strRange);


			if (output.front() == '>') {
				output = output.substr(1, output.length());

				//argument se zavrsava sa >>output.txt
				if (output.front() == '>') {
					output = output.substr(1, output.length());

					ofstream outputFile;
					outputFile.open(output, std::ios::app);
					if (!outputFile) {
						ofstream outputFile(output);
					}


					outputFile << input + "\n";


				}

				//argument se zavrsava sa >output.txt
				else {
					ofstream outputFile;
					outputFile.open(output);
					if (!outputFile) {
						ofstream outputFile(output);
					}

					
					outputFile << input + "\n";
				}
			}
			else {
				cout << "Error." << endl;
			}
			}



		// ako je input.txt ne pocinje sa "" i ne zavrsava se sa "
		else if (Argument[0] != '"' && Argument.back() != '"' && !Argument.empty()) {


			ifstream file(Argument);

			if (file.is_open()) {
				int i = 1;
				string line;
				while (getline(file, line)) {
					cout << line + "\n";
					i++;
					if (i > number) break;
				}
				file.close();

			}
			else {
				cout << "Error! The file does not exist!\n";
			}
			}
			//ostalo

		else {
			cout << "Error! Incorrect input!" << endl;
		}
	}
}
