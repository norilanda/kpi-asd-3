#include "Tape.h"
#include "PolyphaseMerge.h"
#include "FibonacciNumbers.h"
#include <vector>
#include <iostream>	//

using namespace std;

PolyphaseMerge::PolyphaseMerge(int TapesNumber) : N(TapesNumber)
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
		Tapes[i].StartRead();
	}
	int level = 3;//!!!!!FINISH
	while (level != 0)
	{
		int currRuns = Tapes[N - 1].getRunNumber();
		Tapes[N].StartWrite();
	}
}

void PolyphaseMerge::Distribute(int runNumber)
{
	int level = 1;//?
	vector <int> fibonacciNumbers = calculate_runs_distribution(N, runNumber, level);
	int perfectRunNumber = 0;
	for (int i = 0; i < fibonacciNumbers.size(); i++)
		perfectRunNumber += fibonacciNumbers[i];
	int emptyRunNumbers = perfectRunNumber - runNumber;
	for (int i = 0; i < N - 1; i++)
	{
		Tapes[i].setRunNumber(fibonacciNumbers[i]);	//setting runs for tapes
		/*cout << Tapes[i].getRunNumber() << " ";*/
	}
	int i = emptyRunNumbers;
	while (i > 0)	//distribute dummy runs evenly between the tapes
	{
		int j = 0;
		while (i > 0 && j < N - 1)
		{
			if(Tapes[j].getRunNumber()>0)
			{
				Tapes[j].decreaseRunNumber();
				Tapes[j].increaseDummyRunNumber();
				i--;				
			}
			j++;
		}
	}
	/*cout << "\n";
	for (int i = 0; i < N - 1; i++)
	{
		cout << "Real: " << Tapes[i].getRunNumber() << " Dummy: " << Tapes[i].getDummyRunNumber() << " Total: " << Tapes[i].getRunNumber() + Tapes[i].getDummyRunNumber() << "\n";
	}*/
}
