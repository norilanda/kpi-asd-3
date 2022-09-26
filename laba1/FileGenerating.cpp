#include "FileGenerating.h"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

void generate_little_file(string fileName)
{
	ofstream outFile;
	outFile.open(fileName, ios::binary);
	int min = 0;
	int max = 1000;//10000
	long int number = 1000;//3145728
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
	startNumber--;
	lastNumber--;
	
	ifstream inFile;
	inFile.open(fileName, ios::binary);
	//
	if (lastNumber < 0)
	{
		inFile.seekg(0, ios::end);
		lastNumber = inFile.tellg();
		inFile.seekg(0, ios::beg);
	}
	inFile.seekg(startNumber * sizeof(int));
	int i = startNumber;
	int buffSize = 100;
	vector <int> buff;
	buff.resize(buffSize);
	const int maxNumbersInOneRow = 30;
	int numbersInOneRow = 0;
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
			if (numbersInOneRow >= maxNumbersInOneRow)
			{
				cout << "\n";
				numbersInOneRow = 0;
			}
			cout << setw(4)<<buff[k] << " ";
			numbersInOneRow++;
		}
	}
	inFile.close();
}

//void dispaly_file(fstream& fileObject)
//{
//	fileObject.seekg(0, ios::beg);
//	int buffSize = 100;
//	vector <int> buff;
//	buff.resize(buffSize);
//	const int maxNumbersInOneRow = 30;
//	int numbersInOneRow = 0;
//	while (!fileObject.eof())
//	{
//		int j = 0;
//		while (j < buffSize && !fileObject.eof())
//		{
//			fileObject.read((char*)&buff[j], sizeof(int));
//			j++;
//		}
//		for (int k = 0; k < j; k++)
//		{
//			if (numbersInOneRow >= maxNumbersInOneRow)
//			{
//				cout << "\n";
//				numbersInOneRow = 0;
//			}
//			cout << setw(4) << buff[k] << " ";
//			numbersInOneRow++;
//		}
//	}
//}