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
	for (int i = 0; i < N; i++) { TapesIndexArray[i] = i + 1; }
	
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
	int level = 3;//!!!!!FINISH
	while (level != 0)
	{
		int currRuns = Tapes[N - 1].runNumber;
		Tapes[N].StartWrite();
	}
}

void PolyphaseMerge::DistributeRunNumber(int runNumber)
{
	int level = 1;//?
	vector <int> fibonacciNumbers = calculate_runs_distribution(N, runNumber, level);
	int perfectRunNumber = 0;
	for (int i = 0; i < fibonacciNumbers.size(); i++)
		perfectRunNumber += fibonacciNumbers[i];
	int emptyRunNumbers = perfectRunNumber - runNumber;
	for (int i = 0; i < N - 1; i++)
	{
		Tapes[i].runNumber = fibonacciNumbers[i];	//setting runs for tapes
		/*cout << Tapes[i].getRunNumber() << " ";*/
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
	/*cout << "\n";
	for (int i = 0; i < N - 1; i++)
	{
		cout << "Real: " << Tapes[i].runNumber << " Dummy: " << Tapes[i].dummyRunNumber << " Total: " << Tapes[i].runNumber + Tapes[i].dummyRunNumber << "\n";
	}*/
}
void PolyphaseMerge::InitialDistribution()
{
	Tapes[N - 1].StartRead();
	//Tapes[N - 1].fileObject.seekg(0, ios::beg);
	int currRun = 0;
	long long int firstPos = 0;
	for (int i = 0; i < Tapes[N - 1].endOfRuns.size(); i++)
		cout << Tapes[N - 1].endOfRuns[i] << " ";
	for (int i = 0; i < N - 1; i++)
	{
		cout << "rn" << Tapes[i].runNumber << "\n";
		for (int j = 0; j < Tapes[i].runNumber; j++)
		{
			long long int lastPos = Tapes[N - 1].endOfRuns[currRun];
			long long int numberOfNumbers = (lastPos - firstPos + 1)/sizeof(int);
			firstPos = lastPos;
			currRun++;
			int* buff = new int[numberOfNumbers];

			Tapes[N - 1].ReadToBuff(buff, numberOfNumbers);//doesnt read
			
			Tapes[i].WriteFromBuff(buff, numberOfNumbers);
			cout << "f" << buff[0] << " l" << buff[numberOfNumbers - 1]<<"\n";
		}
		Tapes[i].fileObject.flush();
		Tapes[i].StartRead();
		/*dispaly_file(Tapes[i].fileObject);
		cout << " end\n\n";*/
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
		Tapes[N - 1].endOfRuns.push_back(long long int(Tapes[N - 1].fileObject.tellp()) - 1);
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
	Tapes[N - 1].endOfRuns.push_back(long long int(Tapes[N - 1].fileObject.tellp()) - 1);
	Tapes[N - 1].fileObject.flush();
	cout << Tapes[N - 1].fileObject.tellp();
	//delete []buff!!!!!
	return runNumber;
}

void PolyphaseMerge::deleteTempFiles()
{
	for (int i = 0; i < N - 1; i++)
	{
		Tapes[i].destroy();
	}
}