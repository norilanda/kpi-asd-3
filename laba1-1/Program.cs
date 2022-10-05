// See https://aka.ms/new-console-template for more information

using System.Diagnostics;
using System;
using laba1_1;

namespace laba1_1 // Note: actual namespace depends on the project name.
{
    internal class Program
    {
        static void Main(string[] args)
        {
            string unsortedFile = "";
            string sortedFile = "";            
            long bytesInOneRun = 0;
            int mode = 2;   //1 - without optimization; 2 - with optimization
            long maxSizeInBytesToConvert = 1024 * 1024 * 15;    //max file size when we can convert to csv
            int N = 3;
            InputFromUser.getInitialValues(ref N, ref unsortedFile, ref sortedFile, ref bytesInOneRun, ref mode);
            if (File.Exists(sortedFile))
                File.Delete(sortedFile);
            
            Stopwatch stopwatch = new Stopwatch();
            stopwatch.Start();

            PolyphaseMerge p = new PolyphaseMerge(N, bytesInOneRun);
                        
            p.PolyphaseMergeSort(unsortedFile, ref sortedFile, mode);

            stopwatch.Stop();
            TimeSpan ts = stopwatch.Elapsed;

            if(InputFromUser.askIfConvertToCsv(sortedFile, maxSizeInBytesToConvert))
                FileManager.ConvertToCsv(sortedFile);
            bool isSorted = Testing.isSorted(sortedFile, bytesInOneRun);
            InputFromUser.displaySortInformation(unsortedFile, sortedFile, ts, isSorted);           

        }
    }
}

