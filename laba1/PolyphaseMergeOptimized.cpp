#include "Tape.h"
#include "PolyphaseMerge.h"
#include "FibonacciNumbers.h"
#include "FileGenerating.h"
#include <vector>
#include <iostream>	//
#include <algorithm>  

using namespace std;

void PolyphaseMerge::mergeRunsOptimized()
{
	int maxBuffSize = 400;	//max number of bytes, is :4
	int numberOfNumbersInBuff = maxBuffSize / sizeof(int);
	vector <int*> ptrToBuff(ActualRunsIndexArray.size());	//array of pointers to buffers to read from tapes
	int* outBuff;	//buff to write to source buff
	outBuff = new int[numberOfNumbersInBuff];
	int outBuffCurr = 0;
	
	vector <int> sizesOfBuffs(ActualRunsIndexArray.size());	//current size of buffs
	vector <int> currentPositions(ActualRunsIndexArray.size(), 0);	//holds current position to read from buffers

	for (int i = 0; i < ActualRunsIndexArray.size(); i++)
	{
		sizesOfBuffs[i] = Tapes[ActualRunsIndexArray[i]].calc_buff_size(maxBuffSize) / sizeof(int);
		ptrToBuff[i] = new int[sizesOfBuffs[i]];
	}
	for (int i = 0; i < ActualRunsIndexArray.size(); i++)	//reading from all the tapes to buffs
		Tapes[ActualRunsIndexArray[i]].ReadToBuff(ptrToBuff[i], sizesOfBuffs[i]);
	
	while (ActualRunsIndexArray.size() != 0)
	{
		int min = ptrToBuff[0][currentPositions[0]];
		int minTapeIndex = 0;
		for (int i = 1; i < ptrToBuff.size(); i++)
		{
			if (ptrToBuff[i][currentPositions[i]] < min)	//finding the smallest number
			{
				min = ptrToBuff[i][currentPositions[i]];
				minTapeIndex = i;
			}
		}
		outBuff[outBuffCurr] = min;	//writing to the source buff
		outBuffCurr++;
		if (outBuffCurr == maxBuffSize - 1)	//if there is no space in out buff
		{
			Tapes[TapesIndexArray[N - 1]].WriteFromBuff(outBuff, maxBuffSize);	//flush buff
			outBuffCurr = 0;
		}
		currentPositions[minTapeIndex]++;
		if (currentPositions[minTapeIndex] == sizesOfBuffs[minTapeIndex])//? sizesOfBuffs[minTapeIndex] - 1
		{
			if (Tapes[ActualRunsIndexArray[minTapeIndex]].eor())	//checking if the run of the tape with min number hasn't been used completely
			{
				Tapes[ActualRunsIndexArray[minTapeIndex]].runNumber--;
				Tapes[ActualRunsIndexArray[minTapeIndex]].totalRunNumber--;
				Tapes[ActualRunsIndexArray[minTapeIndex]].remove_run_position();

				ActualRunsIndexArray[minTapeIndex] = ActualRunsIndexArray[ActualRunsIndexArray.size() - 1];
				ActualRunsIndexArray.pop_back();
				sizesOfBuffs[minTapeIndex] = sizesOfBuffs[sizesOfBuffs.size() - 1];
				sizesOfBuffs.pop_back();
				currentPositions[minTapeIndex] = currentPositions[currentPositions.size() - 1];
				currentPositions.pop_back();
								
				delete[] ptrToBuff[minTapeIndex];
				if (minTapeIndex != ptrToBuff.size() - 1)
					ptrToBuff[minTapeIndex] = ptrToBuff[ptrToBuff.size() - 1];
				ptrToBuff.pop_back();
			}
			else //if buff is empty, read a new chunk of file
			{
				sizesOfBuffs[minTapeIndex] = Tapes[ActualRunsIndexArray[minTapeIndex]].calc_buff_size(maxBuffSize) / sizeof(int);
				delete[] ptrToBuff[minTapeIndex];
				ptrToBuff[minTapeIndex] = new int[sizesOfBuffs[minTapeIndex]];

				Tapes[ActualRunsIndexArray[minTapeIndex]].ReadToBuff(ptrToBuff[minTapeIndex], sizesOfBuffs[minTapeIndex]);
				currentPositions[minTapeIndex] = 0;
			}
		}
	}
	
	Tapes[TapesIndexArray[N - 1]].AddEndOfRuns();
	Tapes[TapesIndexArray[N - 1]].runNumber++;
	Tapes[TapesIndexArray[N - 1]].totalRunNumber++;

	//free dynamic memory!!!!!!!!
}