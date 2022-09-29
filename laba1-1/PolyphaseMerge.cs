using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Reflection.Metadata.Ecma335;
using System.Text;
using System.Threading.Tasks;

namespace laba1_1
{
    /* class for distribution all the runs between Tapes and merging them into one */
    internal class PolyphaseMerge
    {
        private int N ;    //number of Tapes
        private List<Tape> Tapes; //files
        private List<int> TapesIndexArray;    //stores indices for swapping input/output Tapes
        private List<int> ActualRunsIndexArray;   //stores indices of tapes with real runs that will be merged
        private int level;
        private int finalTapeIndex;


        /*	Constructors/Destructors */
        public PolyphaseMerge(int TapesNumber) { }
        /*~PolyphaseMerge();*/

        public void DistributeRunNumber(int runsNumber) { }   //distributes the runs between the tapes' runNumbers and dummyRunNumbers, is based on fibonacci numbers
        public void InitialDistribution() { } //reads sorted runs from file and distributes it between Tapes
        public void Polyphase() { }   //for merging the sorted runs
        public void mergeRuns() { }   //merging the real runs
        public int calculateRunNumber(string filePath, ref int numberInOneRun, int bytesInOneRun) { return 0; } //calculates total run number and how many numbers will be in each run
        public int createRuns(string filePath, int bytesInOneRun) { return 0; } //divides initial file into runs and sorts every of them
        public int pickSmallestTotalNumber(ref int tapeIndex) { return 0; }
        public void deleteTempFiles() { } //delets all temp files
        public void renameFinalFile(string fileName) { }
    }
}
