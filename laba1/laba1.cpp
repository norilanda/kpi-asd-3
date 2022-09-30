#include <iostream>
#include <string>
#include <ctime>
#include "Tape.h"
#include "PolyphaseMerge.h"
#include "FileGenerating.h"
#include "FibonacciNumbers.h"

using namespace std;
int Tape::TapeNumber = 0;

int main()
{
    string smallFilePath = "files\\smallUnsortedFile.txt"; 
    string middleoutFilePath = "files\\middleUnsortedFile.txt";

    string sortedFile = "files\\sortedFile.txt";
    const int bytesInOneRun = 1024 * 1024;
    const int bytesInOneRunSmall = 1000;

    clock_t start = clock();
    PolyphaseMerge ppm(3);
    //int runNumber = ppm.createRuns(middleoutFilePath, bytesInOneRun);
    int runNumber = ppm.createRuns(smallFilePath, bytesInOneRunSmall);
    ppm.DistributeRunNumber(runNumber);
   
    cout << "\n\n Sorted:\n\n";
    ppm.InitialDistribution();

    ppm.Polyphase();
    ppm.deleteTempFiles();
    ppm.renameFinalFile(sortedFile);
    clock_t end = clock();

    //display_file(sortedFile);
    display_file_numbers_from_range(sortedFile, 1, 1000);
    remove(sortedFile.c_str());
    double time = ((double)end - start) / ((double)CLOCKS_PER_SEC);
    cout << "\nUsed time: " << time << " sec";
}
