#include "FibonacciNumbers.h"
#include <iostream>
using std::cout;

vector<int> calculate_runs_distribution(int tapeNumbers, int runsNumber, int& level)
{
	vector<int>distribution_numbers;
	distribution_numbers.resize(tapeNumbers - 1);
	int exponent = tapeNumbers - 2;
	vector<int> fibonacciNumbers(exponent+1, 0);
	fibonacciNumbers[exponent] = 1;
	int i = exponent;
	while (fibonacciNumbers[i] < runsNumber)
	{
		int nextNumber = 0;
		for (int j = 0; j <= exponent; j++)
		{
			nextNumber += fibonacciNumbers[i - j];
		}
		fibonacciNumbers.push_back(nextNumber);
		i++;
		level++;
	}
	int k = 0;
	for (int j = 0; j <= exponent; j++)
	{
		distribution_numbers[k] = fibonacciNumbers[i - 1 - j];
		/*cout << distribution_numbers[k] << " ";*/
		k++;
	}
	return distribution_numbers;
}