#include "Tape.h"
#include <string>
#include <fstream>

using std::string;

Tape::Tape() {
	TapeNumber++;
	fileName = "Tape" + to_string(TapeNumber) + ".txt";
	runNumber = 0;
	dummyRunNumber = 0;
	fileObject = fstream(fileName, ios::out | ios::binary);
}
Tape::Tape(string filePath)
{
	//TapeNumber++;
	fileName = filePath;
	runNumber = 0;
	dummyRunNumber = 0;
	fileObject = fstream(fileName, ios::in | ios::binary);	//for source file (important to save its content)
}
//Tape::~Tape()
//{
//	this->destroy();
//}

bool Tape::eof()
{
	return fileObject.eof();
}

void Tape::destroy()
{
	fileObject.close();
	remove(fileName.c_str());
}

void Tape::Reset()
{
	fileObject.seekg(0, ios::beg);
	fileObject.seekp(0, ios::beg);
}

void Tape::StartRead()
{
	fileObject.close();
	fileObject.open(this->fileName, ios::in | ios::out | ios::binary);
	this->Reset();
	///
}
void Tape::StartWrite()
{
	this->Reset();
}

void Tape::ReadANumber(int& number)
{
	fileObject.read((char*)&number, sizeof(int));
}
void Tape::ReadToBuff(int* buff, int buffSize)
{
	fileObject.read((char*)buff, buffSize*sizeof(int));
}
void Tape::WriteFromBuff(int* buff, int buffSize)
{
	fileObject.write((char*)buff, buffSize * sizeof(int));
}