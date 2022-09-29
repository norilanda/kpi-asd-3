using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Reflection.Emit;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Intrinsics;

namespace laba1_1
{
    internal class FibonacciNumbers
    {
        public static List<int> calculate_runs_distribution(int tapeNumbers, int runsNumber, ref int level) 
        {
            int exponent = tapeNumbers - 2;
            List<int> fibonacciNumbers = new List<int>(new int[exponent + 1]);
            fibonacciNumbers[exponent] = 1;
            int i = exponent;

            while (fibonacciNumbers[i] < runsNumber)
            {
                int nextNumber = 0;
                for (int j = 0; j <= exponent; j++)
                {
                    nextNumber += fibonacciNumbers[i - j];
                }
                fibonacciNumbers.Add(nextNumber);
                i++;
            }

            List<int> distribution_numbers = fibonacciNumbers.GetRange(i - 1 - exponent, tapeNumbers - 1);

            level = calculate_level(distribution_numbers);
            return distribution_numbers;
        
        }

        public static int calculate_level(List<int> fibonacciNumbers) 
        {        
            List<int> temp = new List<int>(fibonacciNumbers);

            int k = 0;
            while (temp.Count() > 1)
            {
                int index = 0;
                int smallest = find_smallest(temp, ref index);
                if (smallest < 0)
                    break;
                for (int i = 0; i < temp.Count(); i++)
                    temp[i] -= smallest;
                temp[index] = smallest;

                List<int> newTemp = new List<int>();
                for (int i = 0; i < temp.Count(); i++)
                {
                    if (temp[i] > 0)
                        newTemp.Add(temp[i]);
                }
                temp.Clear();
                temp = new List<int>(newTemp);
                k++;
            }
            return k;

        }
        public static int find_smallest(List<int> fibonacciNumbers, ref int index) 
        {
            int smallest = Int32.MaxValue;
            for (int i = 0; i < fibonacciNumbers.Count(); i++)
            {
                if (fibonacciNumbers[i] > 0 && fibonacciNumbers[i] < smallest)
                {
                    smallest = fibonacciNumbers[i];
                    index = i;
                }
            }
            return smallest;
        }
    }
}
