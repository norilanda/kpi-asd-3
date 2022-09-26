#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "PolyphaseMerge.h"

using namespace std;
class PolyphaseMerge;

class Tape 
{
private:
	string fileName;
	int runNumber;
	int dummyRunNumber;
	int totalRunNumber;
	fstream fileObject;
	vector <long long int> endOfRuns;

public:
	friend class PolyphaseMerge;

	/* Constructors/Destructors */
	Tape();
	Tape(string filePath);
	/*~Tape();*/

	/* functions */
	static int TapeNumber;
	bool eof();
	bool eor(); //check the end of run
	void destroy();	//for deleting the fileObject
	void Reset();	//set the current position at the start of the file
	void StartRead();
	void StartWrite();
	void ReadANumber(int& number);	//
	void WriteANumber(int& number);
	void calculate_total_runs() { totalRunNumber = runNumber + dummyRunNumber; }

	/*	reading/writing with buffer	*/
	void ReadToBuff(int* buff, int buffSize);
	void WriteFromBuff(int* buff, int buffSize);

	//void copy();	//copies current Tape 
	//void copyrun();
};