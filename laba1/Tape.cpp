#include "Tape.h"
#include <string>
#include <fstream>


Tape::Tape() {
	TapeNumber++;
	fileName = "Tape" + to_string(TapeNumber) + ".txt";
	runNumber = 0;
	dummyRunNumber = 0;
	fileObject = fstream(fileName, ios::out | ios::binary);
}
Tape::~Tape()
{
	this->destroy();
}

bool Tape::eof()
{
	return fileObject.eof();
}

void Tape::destroy()
{
	fileObject.close();
	remove(fileName.c_str());
}