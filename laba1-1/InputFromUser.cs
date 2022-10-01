using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba1_1
{
    internal class InputFromUser
    {
        public static void getInitialValues(ref int N, ref string unsortedFileName, ref string sortedFileName, ref int bytesInOneRun)
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
            Console.WriteLine("Enter file name for sorted file: ");
            sortedFileName = Console.ReadLine();            
            Console.WriteLine("How many MB will be in one run? ");
            int sizeInMB = Convert.ToInt32(Console.ReadLine());
            const int bytesInOneMB = 1024 * 1024;
            bytesInOneRun = sizeInMB * bytesInOneMB;
        }
    }
}
