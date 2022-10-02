using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba1_1
{
    internal class InputFromUser
    {
        public static void getInitialValues(ref int N, ref string unsortedFileName, ref string sortedFileName, ref long bytesInOneRun, ref int mode)
        {
            Console.WriteLine("Enter Tapes number (N > 2, N < 8):   ");
            N = Convert.ToInt32(Console.ReadLine());
            while (N < 3)
            {
                Console.WriteLine("Tapes number must be bigger than 2. Try again:   ");
                N = Convert.ToInt32(Console.ReadLine());
            }
            Console.WriteLine("Enter unsorted File Name: ");
            unsortedFileName = Console.ReadLine();
            Console.WriteLine("\nEnter file name for sorted file: ");
            sortedFileName = Console.ReadLine();
            Console.WriteLine("\n");

            if (new System.IO.FileInfo(unsortedFileName).Length >= 1024 * 1024)
            { 
                Console.WriteLine("How many MB will be in one run? For large files consider 300MB");
                double sizeInMB = Convert.ToDouble(Console.ReadLine());
                const int bytesInOneMB = 1024 * 1024;
                bytesInOneRun = (int)(sizeInMB * bytesInOneMB);                
            }
            else
            {
                Console.WriteLine("How many Bytes will be in one run? Be careful, number of bytes should be : 4");
                bytesInOneRun = Convert.ToInt32(Console.ReadLine());
            }
            Console.WriteLine();

            Console.WriteLine("Do you want optimized version of polyphase merge sort or polyphase merge sort without optimization? 1 - without optimization, 2 - with optimization");
            mode = Convert.ToInt32(Console.ReadLine());
            Console.WriteLine();
        }
        public static bool askIfConvertToCsv(string sortedFileName, long maxSizeInBytesToConvert)
        {
            long fileSize = new System.IO.FileInfo(sortedFileName).Length;
            if (fileSize > maxSizeInBytesToConvert)
                return false;
            Console.WriteLine("1 - to convert file to csv, 2 - to NOT convert file to csv");
            int answer = Convert.ToInt32(Console.ReadLine());
            Console.WriteLine();
            if (answer == 1)
                return true;       
            return false;
        }

        public static void displaySortInformation(string unsortedFileName, string sortedFileName, TimeSpan ts, bool isSorted)
        {
            Console.WriteLine("Unsorted size = " + new System.IO.FileInfo(unsortedFileName).Length + " bytes");
            Console.WriteLine("Sorted size   = " + new System.IO.FileInfo(sortedFileName).Length + " bytes");
            if (isSorted)
                Console.WriteLine("File is sorted");
            else
                Console.WriteLine("File is NOT sorted");

            Console.WriteLine("Elapsed Time is {0:00}:{1:00}:{2:00}.{3}", ts.Hours, ts.Minutes, ts.Seconds, ts.Milliseconds);
        }
    }
}
