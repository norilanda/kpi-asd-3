#include "Tape.h"
#include "PolyphaseMerge.h"
#include "FibonacciNumbers.h"
#include "FileGenerating.h"
#include <vector>
#include <iostream>	//
#include <algorithm>  

using namespace std;

PolyphaseMerge::PolyphaseMerge(int TapesNumber) : N(TapesNumber)	//Constructor
{
	Tapes.resize(N);
	TapesIndexArray.resize(N);
	for (int i = 0; i < N; i++) { TapesIndexArray[i] = i; }
	level = 0;
	finalTapeIndex = 0;
}
//PolyphaseMerge::~PolyphaseMerge()
//{
//	for (int i = 0; i < N; i++)
//	{
//		Tapes[i].destroy();
//	}
//}

void PolyphaseMerge::Polyphase()
{
	for (int i = 0; i < N-1; i++) {
		Tapes[i].Reset();
	}
	while (level != 0)
	{			
		finalTapeIndex = TapesIndexArray[N - 1];
		int tapeIndex = -1;
		int currRuns = pickSmallestTotalNumber(tapeIndex);	//total number of runs in the last tape (also the smallest number of runs)
		Tapes[TapesIndexArray[N-1]].StartWrite();
		while (currRuns != 0)
		{
			for (int i = 0; i < N - 1; i++)
			{
				if (Tapes[TapesIndexArray[i]].dummyRunNumber > 0)
				{
					Tapes[TapesIndexArray[i]].dummyRunNumber--;	//use dummy run for merging
					Tapes[TapesIndexArray[i]].totalRunNumber--;
				}
				else if(Tapes[TapesIndexArray[i]].runNumber > 0)
				{
					ActualRunsIndexArray.push_back(TapesIndexArray[i]);
				}
			}
			if (!ActualRunsIndexArray.size())
			{
				Tapes[TapesIndexArray[N - 1]].dummyRunNumber++;	//merge dummy runs
				Tapes[TapesIndexArray[N - 1]].totalRunNumber++;
				currRuns--;
			}
			else
			{				
				mergeRuns();	//mergeing
				currRuns--;
			}			
		}
		Tapes[TapesIndexArray[N - 1]].StartRead();	//start reading recently merged Tape
		int temp = TapesIndexArray[tapeIndex];	//swapping the merged Tape and the used Tape
		TapesIndexArray[tapeIndex] = TapesIndexArray[N - 1];
		TapesIndexArray[N - 1] = temp;
		//for (int i = 0; i < N; i++)//
		//{
		//	cout << "Real: " << Tapes[i].runNumber << " Dummy: " << Tapes[i].dummyRunNumber << " Total: " << Tapes[i].totalRunNumber << "\n";
		//	for (int j = 0; j < Tapes[i].endOfRuns.size(); j++)
		//		cout << "end " << Tapes[i].endOfRuns[j] << " ";
		//	cout << "\n";
		//} cout << "\n";
		level--;
	}
	for (int i = 0; i < N; i++)
		Tapes[i].fileObject.close();
}
void PolyphaseMerge::mergeRuns()
{
	vector <int> numbers;
	numbers.resize(ActualRunsIndexArray.size());
	for (int i = 0; i < ActualRunsIndexArray.size(); i++)
		Tapes[ActualRunsIndexArray[i]].ReadANumber(numbers[i]);	//reading a number from each tape
	while (ActualRunsIndexArray.size() != 0)
	{		
		int min = numbers[0];
		int minTapeIndex = 0;
		for (int i = 1; i < numbers.size(); i++)
		{
			if (numbers[i] < min)	//finding the smallest number
			{
				min = numbers[i];
				minTapeIndex = i;
			}
		}
		Tapes[TapesIndexArray[N - 1]].WriteANumber(min);		//writing this number to a source tape
		if (Tapes[ActualRunsIndexArray[minTapeIndex]].eor())	//checking if the run of the tape with min number hasn't been used completely
		{
			/*	deleting the tape if its run has been used*/
			Tapes[ActualRunsIndexArray[minTapeIndex]].runNumber--;
			Tapes[ActualRunsIndexArray[minTapeIndex]].totalRunNumber--;
			Tapes[ActualRunsIndexArray[minTapeIndex]].remove_run_position();
			ActualRunsIndexArray[minTapeIndex] = ActualRunsIndexArray[ActualRunsIndexArray.size() - 1];
			numbers[minTapeIndex] = numbers[numbers.size() - 1];
			ActualRunsIndexArray.pop_back();
			numbers.pop_back();			
		}
		else
			Tapes[ActualRunsIndexArray[minTapeIndex]].ReadANumber(numbers[minTapeIndex]);		//writing a new number
	}
	Tapes[TapesIndexArray[N - 1]].AddEndOfRuns();
	Tapes[TapesIndexArray[N - 1]].runNumber++;
	Tapes[TapesIndexArray[N - 1]].totalRunNumber++;
}

void PolyphaseMerge::DistributeRunNumber(int runNumber)
{
	vector <int> fibonacciNumbers = calculate_runs_distribution(N, runNumber, level);
	int perfectRunNumber = 0;
	for (int i = 0; i < fibonacciNumbers.size(); i++)
		perfectRunNumber += fibonacciNumbers[i];
	int emptyRunNumbers = perfectRunNumber - runNumber;
	for (int i = 0; i < N - 1; i++)
	{
		Tapes[i].runNumber = fibonacciNumbers[i];	//setting runs for tapes
		Tapes[i].totalRunNumber = fibonacciNumbers[i];
	}
	int i = emptyRunNumbers;
	while (i > 0)	//distribute dummy runs evenly between the tapes
	{
		int j = 0;
		while (i > 0 && j < N - 1)
		{
			if(Tapes[j].runNumber>0)
			{
				Tapes[j].runNumber--;
				Tapes[j].dummyRunNumber++;
				i--;				
			}
			j++;
		}
	}
	cout << "\n";
	for (int i = 0; i < N; i++)
	{
		cout << "Real: " << Tapes[i].runNumber << " Dummy: " << Tapes[i].dummyRunNumber << " Total: " << Tapes[i].runNumber + Tapes[i].dummyRunNumber << "\n";
	}
}
void PolyphaseMerge::InitialDistribution()
{
	Tapes[N - 1].StartRead();
	int currRun = 0;
	size_t firstPos = 0;
	
	for (int i = 0; i < N - 1; i++)
	{
		for (int j = 0; j < Tapes[i].runNumber; j++)
		{
			size_t lastPos = Tapes[N - 1].endOfRuns[currRun];
			size_t numberOfNumbers = (lastPos - firstPos + 1)/sizeof(int);
			firstPos = lastPos;
			currRun++;
			int* buff = new int[numberOfNumbers];

			Tapes[N - 1].ReadToBuff(buff, numberOfNumbers);
			
			Tapes[i].WriteFromBuff(buff, numberOfNumbers);
			Tapes[i].AddEndOfRuns();
		}
		
		Tapes[i].fileObject.flush();
		Tapes[i].StartRead();
	}
}


long int PolyphaseMerge::calculateRunNumber(string filePath, long long int& numberInOneRun, int bytesInOneRun)
{
	ifstream file;
	file.open(filePath, ios::in | ios::binary);
	file.seekg(0, std::ios::end);
	long long int fileSize = file.tellg();
	file.seekg(0, std::ios::beg);
	file.close();

	long int runNumber = fileSize / bytesInOneRun;
	numberInOneRun = bytesInOneRun / sizeof(int);
	return runNumber;
}

int PolyphaseMerge::createRuns(string filePath, int bytesInOneRun)
{
	long long int numberInOneRun = 0;
	int runNumber = calculateRunNumber(filePath, numberInOneRun, bytesInOneRun);
	
	Tape sortedRunsFile = Tape(filePath);
	sortedRunsFile.Reset();

	for (int i = 0; i < runNumber - 1; i++)
	{
		int* buff = new int[numberInOneRun];
		sortedRunsFile.ReadToBuff(buff, numberInOneRun);		//reading the run
		sort(buff, buff + numberInOneRun);	//sorting the run
		Tapes[N - 1].WriteFromBuff(buff, numberInOneRun);	//write merged array
		Tapes[N - 1].AddEndOfRuns();
	}
	long long int tempPos = sortedRunsFile.fileObject.tellg();
	sortedRunsFile.fileObject.seekg(0, ios::end);
	long long int lastPos = sortedRunsFile.fileObject.tellg();
	sortedRunsFile.fileObject.seekg(tempPos);
	int newBuffSize = (lastPos - tempPos) / sizeof(int);
	int* buff = new int[newBuffSize];

	sortedRunsFile.ReadToBuff(buff, newBuffSize);
	sort(buff, buff + newBuffSize);	//sorting the run
	Tapes[N - 1].WriteFromBuff(buff, newBuffSize);
	Tapes[N - 1].fileObject.flush();
	Tapes[N - 1].AddEndOfRuns();
	
	//delete []buff!!!!!
	return runNumber;
}
int PolyphaseMerge::pickSmallestTotalNumber(int& tapeIndex)
{
	int smallest = INT_MAX;
	for (int i = 0; i < N; i++)
	{
		if (Tapes[TapesIndexArray[i]].totalRunNumber > 0 && Tapes[TapesIndexArray[i]].totalRunNumber < smallest)
		{
			smallest = Tapes[TapesIndexArray[i]].totalRunNumber;
			tapeIndex = i;
		}
	}
	return smallest;
}
void PolyphaseMerge::deleteTempFiles()
{
	for (int i = 0; i < N; i++)
	{
		if (i != finalTapeIndex)
			Tapes[i].destroy();
	}
}
void PolyphaseMerge::renameFinalFile(string fileName)
{
	rename(Tapes[finalTapeIndex].fileName.c_str(), fileName.c_str());
}