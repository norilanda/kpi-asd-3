#include "Tape.h"
#include <string>
#include <fstream>
#include <algorithm>

using std::string;

Tape::Tape() {
	TapeNumber++;
	fileName = "Tape" + to_string(TapeNumber) + ".txt";
	runNumber = 0;
	dummyRunNumber = 0;
	totalRunNumber = 0;
	fileObject = fstream(fileName, ios::out | ios::binary);
}
Tape::Tape(string filePath)
{
	//TapeNumber++;
	fileName = filePath;
	runNumber = 0;
	dummyRunNumber = 0;
	totalRunNumber = 0;
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
bool Tape::eor()
{
	for (int i = 0; i < endOfRuns.size(); i++)
	{
		size_t currPos = size_t(fileObject.tellg()) - 1;
		if (endOfRuns[i] == currPos)
			return true;
		if (endOfRuns[i] > currPos)
			return false;
	}
	return false;
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
	fileObject.close();
	fileObject.open(this->fileName, ios::out | ios::trunc | ios::binary);
	this->dummyRunNumber = 0;
	this->runNumber = 0;
	this->totalRunNumber = 0;
	this->endOfRuns.clear();
}

void Tape::ReadANumber(int& number)
{
	fileObject.read((char*)&number, sizeof(int));
}
void Tape::WriteANumber(int& number)
{
	fileObject.write((char*)&number, sizeof(int));
}
void Tape::AddEndOfRuns()
{
	endOfRuns.push_back(long long int(fileObject.tellp()) - 1);
}
void Tape::remove_run_position()
{
	for (int i = 1; i < endOfRuns.size(); i++)
		endOfRuns[i - 1] = endOfRuns[i];
	endOfRuns.pop_back();
}

void Tape::ReadToBuff(int* buff, int buffSize)
{
	fileObject.read((char*)buff, buffSize*sizeof(int));
}
void Tape::WriteFromBuff(int* buff, int buffSize)
{
	fileObject.write((char*)buff, buffSize * sizeof(int));
}

/*	optimization functions	*/
//void Tape::ReadToBuffOptimized(int* buff, int buffSize)
//{
//
//}

int Tape::calc_buff_size(int maxBuffSize)
{
	return min(maxBuffSize, int(endOfRuns[0] - size_t(fileObject.tellg()) + 1));
}