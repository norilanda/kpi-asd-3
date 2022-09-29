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
            string smallFilePath = "files\\smallUnsortedFile.txt";
            string middleoutFilePath = "files\\middleUnsortedFile.txt";

            string sortedFile = "files\\sortedFile.txt";
            const int bytesInOneRun = 1024 * 1024;
            const int bytesInOneRunSmall = 400;

            Stopwatch stopwatch = new Stopwatch();
            stopwatch.Start();

            int temp=0;
            FibonacciNumbers.calculate_runs_distribution(3, 10, ref temp);

            stopwatch.Stop();
            TimeSpan ts = stopwatch.Elapsed;

            Console.WriteLine("Elapsed Time is {0:00}:{1:00}:{2:00}.{3}", ts.Hours, ts.Minutes, ts.Seconds, ts.Milliseconds);

        }
    }
}

