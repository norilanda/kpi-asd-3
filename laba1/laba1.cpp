#include <iostream>
#include <string>
#include "Tape.h"
#include "PolyphaseMerge.h"
#include "FileGenerating.h"
#include "FibonacciNumbers.h"

using namespace std;
int Tape::TapeNumber = 0;

int main()
{
    string outFilePath = "files\\unsortedFile.txt";
    calculate_runs_distribution(4, 40);
}
