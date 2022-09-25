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
	Tape(string filePath);
	/*~Tape();*/

	/* getters/setters */
	string getName() { return fileName; }
	int getRunNumber() { return runNumber; }
	int getDummyRunNumber() { return dummyRunNumber; }

	void setRunNumber(int value) { runNumber = value; }
	void setDummyRunNumber(int value) { dummyRunNumber = value; }

	void increaseRunNumber() { runNumber++; }
	void decreaseRunNumber() { runNumber--; }
	void increaseDummyRunNumber() { dummyRunNumber++; }
	void decreaseDummyRunNumber() { dummyRunNumber--; }

	/* functions */
	static int TapeNumber;
	bool eof();
	void destroy();	//for deleting the fileObject
	void Reset();	//set the current position at the start of the file
	void StartRead();
	void StartWrite();
	//void copy();	//copies current Tape 
	//void copyrun();
	void Close();	//closes fileObject
};