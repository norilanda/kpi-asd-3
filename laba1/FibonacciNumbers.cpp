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
	}
	int k = 0;
	for (int j = 0; j <= exponent; j++)
	{
		distribution_numbers[k] = fibonacciNumbers[i - 1 - j];
		k++;
	}
	level = calculate_level(distribution_numbers);
	
	return distribution_numbers;
}
int calculate_level(vector <int> fibonacciNumbers)
{
	vector <int> temp;
	temp.resize(fibonacciNumbers.size());
	for (int i = 0; i < temp.size(); i++)
		temp[i] = (fibonacciNumbers[i]);

	int k = 0;
	while (temp.size()>1)
	{
		int index = 0;
		int smallest = find_smallest(temp, index);
		if (smallest < 0)
			break;
		for (int i = 0; i < temp.size(); i++)
			temp[i] -= smallest;
		temp[index] = smallest;
		vector <int> newTemp;
		for (int i = 0; i < temp.size(); i++)
		{
			if (temp[i] > 0)
				newTemp.push_back(temp[i]);
		}
		temp.clear();
		temp.resize(newTemp.size());
		for (int i = 0; i < newTemp.size(); i++)
			temp[i] = newTemp[i];
		k++;
	}
	return k;
}
int find_smallest(vector <int> fibonacciNumbers, int& index)
{
	int smallest = INT_MAX;
	for (int i = 0; i < fibonacciNumbers.size(); i++)
	{
		if (fibonacciNumbers[i] > 0 && fibonacciNumbers[i] < smallest)
		{
			smallest = fibonacciNumbers[i];
			index = i;
		}
	}
	return smallest;
}