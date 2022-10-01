﻿// See https://aka.ms/new-console-template for more information

using System.Diagnostics;
using System;
using laba1_1;

namespace laba1_1 // Note: actual namespace depends on the project name.
{
    internal class Program
    {
        static void Main(string[] args)
        {
            string smallFilePath = "C:\\Users\\ACER\\source\\repos\\kpi-asd-3\\laba1-1\\files\\smallUnsortedFile.txt";
            string middleoutFilePath = "C:\\Users\\ACER\\source\\repos\\kpi-asd-3\\laba1-1\\files\\middleUnsortedFile.txt";
            string largeFilePath = "C:\\Users\\ACER\\source\\repos\\kpi-asd-3\\laba1-1\\files\\largeUnsortedFile.txt";
            string file500MBPath = "D:\\USER_FOLDER_2\\DESKTOP\\filesASD\\largeUnsortedFile500MB.txt";

            string unsortedFile = largeFilePath;
            string sortedFile = "C:\\Users\\ACER\\source\\repos\\kpi-asd-3\\laba1-1\\files\\sortedFile.txt";
            
            const int bytesInOneRunSmall = 400;
            const int bytesInOneRunMiddle = 1024 * 1024;
            const int bytesInOneRunLarge = 1024 * 1024 * 300;
            const int bytes500MB = 1024 * 1024 * 200;
            const int sizeInMB = 100;
            long bytesInOneRun = bytesInOneRunLarge;
            
            //FileManager.generateFile(largeFilePath, sizeInMB, 'a');
            int N = 4;
            if (File.Exists(sortedFile))
                File.Delete(sortedFile);

            //InputFromUser.getInitialValues(ref N, ref unsortedFile, ref sortedFile, ref bytesInOneRun);
            Stopwatch stopwatch = new Stopwatch();
            stopwatch.Start();

            PolyphaseMerge p = new PolyphaseMerge(N, bytesInOneRun);
                        
            int runNumber = p.createRuns(unsortedFile, bytesInOneRun);
            p.DistributeRunNumber(runNumber);
            p.InitialDistribution();
            p.Polyphase();

            p.deleteTempFiles();
            p.renameFinalFile(sortedFile);

            stopwatch.Stop();
            TimeSpan ts = stopwatch.Elapsed;
            //FileManager.ConvertToCsv(sortedFile);
            bool isSorted = Testing.isSorted(sortedFile, bytesInOneRun);
            //File.Delete(sortedFile);

            Console.WriteLine("Unsorted size = " + new System.IO.FileInfo(unsortedFile).Length);
            Console.WriteLine("Sorted size   = " + new System.IO.FileInfo(sortedFile).Length);
            if (isSorted)
                Console.WriteLine("File is sorted");
            else
                Console.WriteLine("File is NOT sorted");

            Console.WriteLine("Elapsed Time is {0:00}:{1:00}:{2:00}.{3}", ts.Hours, ts.Minutes, ts.Seconds, ts.Milliseconds);

        }
    }
}

