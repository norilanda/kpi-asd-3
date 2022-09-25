#pragma once
#include "Tape.h"
#include <string>
#include <vector>

using namespace std;

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

	void Distribute(int runsNumber);	//distributes the runs between the series, is based on fibonacci numbers
	void Polyphase();	//for merging the sorted runs
	void createRuns(string filePath);	//divides initial file into runs and sorts every of them
	void deleteTempFiles();	//delets all temp files
};
