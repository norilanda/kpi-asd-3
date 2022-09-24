#include "Tape.h"
#include "PolyphaseMerge.h"
#include <vector>

using namespace std;

PolyphaseMerge::PolyphaseMerge(int TapesNumber) : N(TapesNumber)
{
	Tapes.reserve(N);
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
