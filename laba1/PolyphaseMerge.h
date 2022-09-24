#pragma once
#include "Tape.h"
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

	void Polyphase();	//
};
