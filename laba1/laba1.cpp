#include <iostream>
#include <string>
#include "Tape.h"

using namespace std;
int Tape::TapeNumber = 0;

int main()
{
    Tape t1, t2;
    cout << t1.getName() << "\n";
    cout << t2.getName() << "\n";
}
