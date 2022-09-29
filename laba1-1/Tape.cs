using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba1_1
{
    internal class Tape
    {
        public string fileName;
        public int runNumber;
        public int dummyRunNumber;
        public int totalRunNumber;
        public FileStream fileObject;
        public List<int> endOfRuns;

        /* Constructors/Destructors */
        public Tape() 
        {
            TapeNumber++;
            fileName = "Tape" + TapeNumber.ToString() + ".txt";
            runNumber = 0;
            dummyRunNumber = 0;
            totalRunNumber = 0;
            fileObject = new FileStream(fileName, FileMode.OpenOrCreate);
        }
        public Tape(string filePath) { }
        /*~Tape();*/

        /* functions */
        public static int TapeNumber;
        public bool eof() { return false; }
        public bool eor() { return false; } //check the end of run
        public void destroy() { } //for deleting the fileObject
        public void Reset() { }   //set the current position at the start of the file
        public void StartRead() { }
        public void StartWrite() { }
        public void ReadANumber(ref int number) { }  //
        public void WriteANumber(ref int number) { }

        public void calculate_total_runs() { totalRunNumber = runNumber + dummyRunNumber; }
        public void AddEndOfRuns() { }    //adds to end of runs last writed position
        public void remove_run_position() { }

        /*	reading/writing with buffer	*/
        public void ReadToBuff(ref int buff, int buffSize) { }
        public void WriteFromBuff(ref int buff, int buffSize) { }

    }
}
