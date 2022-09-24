#pragma once
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Tape 
{
private:
	string fileName;
	int runNumber;
	int dummyRunNumber;
	fstream fileObject;
	vector <int> endOfRuns;

public:
	/* Constructors/Destructors */
	Tape();
	~Tape();

	/* getters/setters */
	string getName() { return fileName; }
	int getRunNumber() { return runNumber; }
	int getDummyRunNumber() { return dummyRunNumber; }

	/* functions */
	static int TapeNumber;
	bool eof();
	void destroy();	//for deleting the fileObject
};