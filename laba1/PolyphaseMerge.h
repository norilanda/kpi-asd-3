#pragma once
#include "Tape.h"
#include <string>
#include <vector>

using namespace std;
class Tape;

/* class for distribution all the runs between Tapes
and merging them into one */

class PolyphaseMerge
{
private:
	const int N;	//number of Tapes
	vector <Tape> Tapes;	//files
	vector <int> TapesIndexArray;	//stores indices for swapping input/output Tapes
public:
	/*	Constructors/Destructors */
	PolyphaseMerge(int TapesNumber);
	/*~PolyphaseMerge();*/

	void DistributeRunNumber(int runsNumber);	//distributes the runs between the tapes' runNumbers and dummyRunNumbers, is based on fibonacci numbers
	void InitialDistribution();	//reads sorted runs from file and distributes it between Tapes
	void Polyphase();	//for merging the sorted runs
	long int calculateRunNumber(string filePath, long long int& numberInOneRun, int bytesInOneRun);	//calculates total run number and how many numbers will be in each run
	int createRuns(string filePath, int bytesInOneRun);	//divides initial file into runs and sorts every of them
	void deleteTempFiles();	//delets all temp files
};
