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
        public List<long> lengthOfRuns;  //in bytes
        public BinaryReader binaryReader;
        public BinaryWriter binaryWriter;
        
        /* Constructors/Destructors */
        public Tape() 
        {
            TapeNumber++;
            fileName = "Tape" + TapeNumber.ToString() + ".txt";
            runNumber = 0;
            dummyRunNumber = 0;
            totalRunNumber = 0;
            lengthOfRuns = new List<long>(); 
        }
        public Tape(string filePath) 
        {
            fileName = filePath;
            runNumber = 0;
            dummyRunNumber = 0;
            totalRunNumber = 0;
            lengthOfRuns = new List<long>();
        }

        /* functions */
        public static int TapeNumber;
        public void destroy() //for deleting the fileObject
        {            
            File.Delete(fileName);
        }

        public void closeReaders()
        {
            binaryReader.Close();
            binaryReader.Close();
        }
        public void Reset()  //set the current position at the start of the file
        {
            dummyRunNumber = 0;
            runNumber = 0;
            totalRunNumber = 0;
            lengthOfRuns.Clear();
        }  
        public void StartRead() 
        {
            fileObject = new FileStream(fileName, FileMode.Open);
            binaryReader = new BinaryReader(fileObject);
        }
        public void StartWrite() 
        {
            fileObject = new FileStream(fileName, FileMode.OpenOrCreate);
            binaryWriter = new BinaryWriter(fileObject);           
        }

        public void StartWriteTrunc()
        {
            fileObject = new FileStream(fileName, FileMode.Truncate);
            binaryWriter = new BinaryWriter(fileObject);
        }        
        public void AddLengthOfRuns(long runLenght) //adds to end of runs last writed position
        {
            lengthOfRuns.Add(runLenght);
        }    
        public void remove_run_position() 
        { 
            lengthOfRuns.RemoveAt(0);
        }
    }
}
