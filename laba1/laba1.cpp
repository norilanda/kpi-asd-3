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
    string smallFilePath = "files\\smallUnsortedFile.txt";
    string sortedRunsPath = "Tape4.txt";
    //display_file_numbers_from_range(smallFilePath, 1, 1000);
    /*generate_little_file(tempFilePath);*/
    const int bytesInOneRun = 1024 * 1024;
    const int bytesInOneRunSmall = 400;

    PolyphaseMerge ppm(4);
    int runNumber = ppm.createRuns(smallFilePath, bytesInOneRunSmall);
    ppm.DistributeRunNumber(runNumber);
    /*ppm.createRuns(outFilePath, bytesInOneRun);*/
   
    cout << "\n\n Sorted:\n\n";
    ppm.InitialDistribution();
    //display_file_numbers_from_range(sortedRunsPath, 1, 1000);
    display_file_numbers_from_range("Tape1.txt", 1, 1000);
    cout << "\n\n";
    display_file_numbers_from_range("Tape2.txt", 1, 1000);
    cout << "\n\n";
    display_file_numbers_from_range("Tape3.txt", 1, 1000);
    cout << "\n\n";
    //ppm.Polyphase();
    ppm.deleteTempFiles();
}
