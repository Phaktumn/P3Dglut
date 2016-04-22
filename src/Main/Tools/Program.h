#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Program
{
public:
	string* loadFile(const string& fileName) const;
	unsigned int loadProgram(const vector<string>& files);
private:

};

inline string* Program::loadFile(const string& fileName) const
{
	string* result = new string();
	ifstream file(fileName.c_str());
	if (!file) {
		cerr << "Cannot open file " << fileName << endl;
		throw exception();
	}
	string line;
	while (getline(file, line)) {
		*result += line;
		*result += '\n';
	}
	file.close();
	return result;
}
