using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using System.IO;
using System.Linq;
using System.Numerics;
using System.Reflection.Metadata.Ecma335;
using System.Runtime.Intrinsics;
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
        private long maxBytesInOneRun;


        public PolyphaseMerge(int TapesNumber, long maxBytesInOneRun1)   /*	Constructor */
        {
            N = TapesNumber;
            Tapes = new List<Tape>(new Tape[N]);
            for(int i=0;i<N;i++)
                Tapes[i] = new Tape();
            TapesIndexArray = new List<int>(new int[N]);
            ActualRunsIndexArray = new List<int>();
            for (int i = 0; i < N; i++) 
            { TapesIndexArray[i] = i; }
            level = 0;
            finalTapeIndex = 0;
            maxBytesInOneRun = maxBytesInOneRun1;
        }

        public void PolyphaseMergeSort(string unsortedFile, string sortedFile, int mode)
        {
            int runNumber = createRuns(unsortedFile, maxBytesInOneRun);
            DistributeRunNumber(runNumber);
            InitialDistribution();
            Polyphase(mode);

            deleteTempFiles();
            renameFinalFile(sortedFile);
        }

        public int calculateRunNumber(string filePath, ref long numberInOneRun, long bytesInOneRun)   //calculates total run number and how many numbers will be in each run
        {
            long fileSize = new System.IO.FileInfo(filePath).Length;
            int runNumber = (int)(fileSize / bytesInOneRun);
            numberInOneRun = bytesInOneRun / sizeof(int);
            maxBytesInOneRun = numberInOneRun * sizeof(int);
            return runNumber;            
        } 
        public int createRuns(string filePath, long bytesInOneRun) //divides initial file into runs and sorts every of them
        {
            long numberInOneRun = 0;
            int runNumber = calculateRunNumber(filePath, ref numberInOneRun, bytesInOneRun);

            Tape sortedRunsFile = new Tape(filePath);
            sortedRunsFile.StartRead();
            Tapes[N - 1].StartWrite();
            
            long usedBytes = 0;

            for (int i = 0; i < runNumber - 1; i++)
            {
                int[] buff = FileManager.readArrayOfInts(sortedRunsFile.binaryReader, numberInOneRun);   //reading the run as bytes
                Array.Sort(buff);
                long writtenBytes = FileManager.writeArrayOfInts(Tapes[N - 1].binaryWriter, ref buff);                
                Tapes[N - 1].AddLengthOfRuns(writtenBytes);
                usedBytes += writtenBytes;               
            }

            long fileSize = new System.IO.FileInfo(filePath).Length;
            long newBuffSize = fileSize - usedBytes;
            long newNumberInOneRun = newBuffSize / sizeof(int);
                       
            int[] lastBuff = FileManager.readArrayOfInts(sortedRunsFile.binaryReader, newNumberInOneRun);
            Array.Sort(lastBuff);
            long newWrittenBytes = FileManager.writeArrayOfInts(Tapes[N - 1].binaryWriter, ref lastBuff);
            Tapes[N - 1].AddLengthOfRuns(newWrittenBytes);

            sortedRunsFile.binaryReader.Close();
            Tapes[N - 1].binaryWriter.Close();

            return runNumber;
        } 
        public void DistributeRunNumber(int runNumber)//distributes the runs between the tapes' runNumbers and dummyRunNumbers, is based on fibonacci numbers
        {
            List<int> fibonacciNumbers = FibonacciNumbers.calculate_runs_distribution(N, runNumber, ref level);
            int perfectRunNumber = 0;
            int i;
            for (i = 0; i < fibonacciNumbers.Count(); i++)
                perfectRunNumber += fibonacciNumbers[i];
            int emptyRunNumbers = perfectRunNumber - runNumber;
            for (i = 0; i < N - 1; i++)
            {
                Tapes[i].runNumber = fibonacciNumbers[i];   //setting runs for tapes
                Tapes[i].totalRunNumber = fibonacciNumbers[i];
            }
            i = emptyRunNumbers;
            while (i > 0)   //distribute dummy runs evenly between the tapes
            {
                int j = 0;
                while (i > 0 && j < N - 1)
                {
                    if (Tapes[j].runNumber > 0)
                    {
                        Tapes[j].runNumber--;
                        Tapes[j].dummyRunNumber++;
                        i--;
                    }
                    j++;
                }
            }            
        }   
      
        public void InitialDistribution() //reads sorted runs from file and distributes it between Tapes
        {
            Tapes[N - 1].StartRead();
            int currRun = 0;
            int i;
            for (i = 0; i < N - 1; i++)
                Tapes[i].StartWrite();

            for (i = 0; i < N - 1; i++)
            {
                for (int j = 0; j < Tapes[i].runNumber; j++)
                {
                    long numberOfNumbers = Tapes[N-1].lengthOfRuns[currRun] / sizeof(int);
                    currRun++;
                    int[] buff = FileManager.readArrayOfInts(Tapes[N - 1].binaryReader, numberOfNumbers);
                    long writtenBytes = FileManager.writeArrayOfInts(Tapes[i].binaryWriter, ref buff);
                    Tapes[i].AddLengthOfRuns(writtenBytes);                                        
                }
                Tapes[i].binaryWriter.Close();
                Tapes[i].StartRead();
            }
            Tapes[N - 1].binaryReader.Close();
        }

        public void Polyphase(int mode)   //for merging the sorted runs
        {           
            while (level != 0)
            {
                finalTapeIndex = TapesIndexArray[N - 1];
                int tapeIndex = -1;
                int currRuns = pickSmallestTotalNumber(ref tapeIndex);  //total number of runs in the last tape (also the smallest number of runs)
                Tapes[TapesIndexArray[N - 1]].Reset();
                Tapes[TapesIndexArray[N - 1]].binaryReader.Close();
                Tapes[TapesIndexArray[N - 1]].StartWriteTrunc();
                while (currRuns != 0)
                {
                    for (int i = 0; i < N - 1; i++)
                    {
                        if (Tapes[TapesIndexArray[i]].dummyRunNumber > 0)
                        {
                            Tapes[TapesIndexArray[i]].dummyRunNumber--; //use dummy run for merging
                            Tapes[TapesIndexArray[i]].totalRunNumber--;
                        }
                        else if (Tapes[TapesIndexArray[i]].runNumber > 0)
                        {
                            ActualRunsIndexArray.Add(TapesIndexArray[i]);
                        }
                    }
                    if (ActualRunsIndexArray.Count() == 0)
                    {
                        Tapes[TapesIndexArray[N - 1]].dummyRunNumber++; //merge dummy runs
                        Tapes[TapesIndexArray[N - 1]].totalRunNumber++;
                        currRuns--;
                    }
                    else
                    {
                        if (mode == 1)
                            mergeRuns();    //mergeing
                        else
                            mergeRunsOptimized(maxBytesInOneRun);
                        currRuns--;
                    }
                }
                Tapes[TapesIndexArray[N - 1]].binaryWriter.Close();                
                Tapes[TapesIndexArray[N - 1]].StartRead();  //start reading recently merged Tape
                int temp = TapesIndexArray[tapeIndex];  //swapping the merged Tape and the used Tape
                TapesIndexArray[tapeIndex] = TapesIndexArray[N - 1];
                TapesIndexArray[N - 1] = temp;                
                level--;                             
            }
            for (int i = 0; i < N-1; i++)
                Tapes[i].binaryReader.Close();
            Tapes[N-1].binaryWriter.Close();
        } 

        public void mergeRuns() //merging the real runs
        {
            List<int> numbers = new List<int>(new int[ActualRunsIndexArray.Count()]);
            List<int> writtenInts = new List<int>(new int[ActualRunsIndexArray.Count()]);
            for (int i = 0; i < ActualRunsIndexArray.Count(); i++)
            { 
                numbers[i] = Tapes[ActualRunsIndexArray[i]].binaryReader.ReadInt32(); //reading a number from each tape
                writtenInts[i] = 1;
            } 
            long totalWrittenNumberOfInts = 0;
            while (ActualRunsIndexArray.Count() != 0)
            {
                int min = numbers[0];
                int minTapeIndex = 0;
                for (int i = 1; i < numbers.Count(); i++)
                {
                    if (numbers[i] < min)   //finding the smallest number
                    {
                        min = numbers[i];
                        minTapeIndex = i;
                    }
                }
                Tapes[TapesIndexArray[N - 1]].binaryWriter.Write(BitConverter.GetBytes(min));//writing this number to a source tape 
                totalWrittenNumberOfInts++;                              
                if (writtenInts[minTapeIndex] == Tapes[ActualRunsIndexArray[minTapeIndex]].lengthOfRuns[0]/sizeof(int))    //checking if the run of the tape with min number hasn't been used completely
                {                    
                    /*	deleting the tape if its run has been used*/
                    Tapes[ActualRunsIndexArray[minTapeIndex]].runNumber--;
                    Tapes[ActualRunsIndexArray[minTapeIndex]].totalRunNumber--;
                    Tapes[ActualRunsIndexArray[minTapeIndex]].remove_run_position();
                    ActualRunsIndexArray[minTapeIndex] = ActualRunsIndexArray[ActualRunsIndexArray.Count() - 1];
                    numbers[minTapeIndex] = numbers[numbers.Count() - 1];
                    ActualRunsIndexArray.RemoveAt(ActualRunsIndexArray.Count - 1);
                    numbers.RemoveAt(numbers.Count - 1);
                    writtenInts[minTapeIndex] = writtenInts[writtenInts.Count - 1];
                    writtenInts.RemoveAt(writtenInts.Count - 1);
                }
                else
                {
                    numbers[minTapeIndex] = Tapes[ActualRunsIndexArray[minTapeIndex]].binaryReader.ReadInt32();  //writing a new number
                    writtenInts[minTapeIndex]++;                   
                }
            }
            Tapes[TapesIndexArray[N - 1]].AddLengthOfRuns(totalWrittenNumberOfInts*sizeof(int));
            Tapes[TapesIndexArray[N - 1]].runNumber++;
            Tapes[TapesIndexArray[N - 1]].totalRunNumber++;            
        }
             
        public int pickSmallestTotalNumber(ref int tapeIndex) 
        {
            int smallest = Int32.MaxValue;
            for (int i = 0; i < N; i++)
            {
                if (Tapes[TapesIndexArray[i]].totalRunNumber > 0 && Tapes[TapesIndexArray[i]].totalRunNumber < smallest)
                {
                    smallest = Tapes[TapesIndexArray[i]].totalRunNumber;
                    tapeIndex = i;
                }
            }
            return smallest;
        }
        public void deleteTempFiles() //delets all temp files
        {
            for (int i = 0; i < N; i++)
            {
                Tapes[i].closeReaders();
                if (i != finalTapeIndex)
                    Tapes[i].destroy();
            }
        } 
        public void renameFinalFile(string newFileName)
        {
            Tapes[finalTapeIndex].closeReaders();
            File.Move(Tapes[finalTapeIndex].fileName, newFileName);
        }

        public void mergeRunsOptimized(long maxNumberOfBytes)
        {
            List<int[]> buffers = new List<int[]>();
            List<int> indexInBuffs = new List<int>(new int[ActualRunsIndexArray.Count()]);
            long writtenIntsToSourceFile = 0;
            int[] sourceBuff = new int[maxNumberOfBytes/sizeof(int)];
            for (int i = 0; i < ActualRunsIndexArray.Count(); i++)
            {
                long currBuffSize = Math.Min(maxNumberOfBytes, Tapes[ActualRunsIndexArray[i]].lengthOfRuns[0]);
                Tapes[ActualRunsIndexArray[i]].lengthOfRuns[0] -= currBuffSize;
                buffers.Add(FileManager.readArrayOfInts(Tapes[ActualRunsIndexArray[i]].binaryReader, currBuffSize/sizeof(int)));
                indexInBuffs[i] = 0;
            }
            long totalWrittenNumberOfInts = 0;
            while (ActualRunsIndexArray.Count() != 0)
            {
                int min = buffers[0][indexInBuffs[0]];
                int minTapeIndex = 0;
                for (int i = 1; i < buffers.Count(); i++)
                {
                    if (buffers[i][indexInBuffs[i]] < min)   //finding the smallest number
                    {
                        min = buffers[i][indexInBuffs[i]];
                        minTapeIndex = i;
                    }
                }
                sourceBuff[writtenIntsToSourceFile] = min;  //writing to source buff
                writtenIntsToSourceFile++;
                if(writtenIntsToSourceFile == sourceBuff.Length)    //flush the source buff
                {
                    FileManager.writeArrayOfInts(Tapes[TapesIndexArray[N - 1]].binaryWriter, ref sourceBuff);
                    writtenIntsToSourceFile = 0;
                }
                totalWrittenNumberOfInts++;
                indexInBuffs[minTapeIndex]++;
                if (indexInBuffs[minTapeIndex] == buffers[minTapeIndex].Length)//check if buff is not empty
                {
                    if(Tapes[ActualRunsIndexArray[minTapeIndex]].lengthOfRuns[0] == 0)  //if run has been used
                    {
                        Tapes[ActualRunsIndexArray[minTapeIndex]].runNumber--;
                        Tapes[ActualRunsIndexArray[minTapeIndex]].totalRunNumber--;
                        Tapes[ActualRunsIndexArray[minTapeIndex]].remove_run_position();
                        ActualRunsIndexArray[minTapeIndex] = ActualRunsIndexArray[ActualRunsIndexArray.Count() - 1];
                        ActualRunsIndexArray.RemoveAt(ActualRunsIndexArray.Count - 1);

                        buffers[minTapeIndex] = (int[])buffers[buffers.Count() - 1].Clone();
                        buffers.RemoveAt(buffers.Count - 1);

                        indexInBuffs[minTapeIndex] = indexInBuffs[indexInBuffs.Count - 1];
                        indexInBuffs.RemoveAt(indexInBuffs.Count - 1);                        
                    }
                    else
                    {
                        long currBuffSize = Math.Min(maxNumberOfBytes, Tapes[ActualRunsIndexArray[minTapeIndex]].lengthOfRuns[0]);
                        Tapes[ActualRunsIndexArray[minTapeIndex]].lengthOfRuns[0] -= currBuffSize;
                        buffers[minTapeIndex] = FileManager.readArrayOfInts(Tapes[ActualRunsIndexArray[minTapeIndex]].binaryReader, currBuffSize / sizeof(int));
                        indexInBuffs[minTapeIndex] = 0;
                    }
                }                
            }            
            int[] lastInts = new int[writtenIntsToSourceFile];
            Array.Copy(sourceBuff, 0, lastInts, 0, writtenIntsToSourceFile);
            FileManager.writeArrayOfInts(Tapes[TapesIndexArray[N - 1]].binaryWriter, ref lastInts);

            Tapes[TapesIndexArray[N - 1]].AddLengthOfRuns(totalWrittenNumberOfInts * sizeof(int));
            Tapes[TapesIndexArray[N - 1]].runNumber++;
            Tapes[TapesIndexArray[N - 1]].totalRunNumber++;
        }
    }
}
