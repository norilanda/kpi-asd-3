#include "FileGenerating.h"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

void generate_little_file(string fileName)
{
	ofstream outFile;
	outFile.open(fileName, ios::binary);
	int min = 0;
	int max = 10000;
	long int number = 3145728;
	vector <int> arr;
	arr.resize(number);
	for (int i=0;i< number;i++)
	{
		arr[i] = rand() % (max - min + 1) + min;
	}
	for (int i = 0; i < number; i++)
	{
		outFile.write((char*)&arr[i], sizeof(int));
	}
	outFile.close();
}

void display_file_numbers_from_range(string fileName, int startNumber, int lastNumber)
{
	startNumber++;
	lastNumber++;
	ifstream inFile;
	inFile.open(fileName, ios::binary);
	//
	inFile.seekg(startNumber * sizeof(int));
	int i = startNumber;
	int buffSize = 100;
	vector <int> buff;
	buff.resize(buffSize);
	while (!inFile.eof() && i <= lastNumber)
	{
		int j = 0;
		while (j < buffSize && i <= lastNumber)
		{
			inFile.read((char*)&buff[j], sizeof(int));
			j++;
			i++;
		}
		for (int k = 0; k < j; k++)
		{
			cout << buff[k] << " ";
		}
	}
	inFile.close();
}