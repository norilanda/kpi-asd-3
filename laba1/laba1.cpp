#include <iostream>
#include <string>
#include "Tape.h"
#include "PolyphaseMerge.h"
#include "FileGenerating.h"

using namespace std;
int Tape::TapeNumber = 0;

int main()
{
    string outFilePath = "files\\unsortedFile.txt";
    /*generate_little_file(outFilePath);*/
    display_file_numbers_from_range(outFilePath, 0, 5);
    const int N = 3;
    PolyphaseMerge ppm(N);
}
