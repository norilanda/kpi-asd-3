#pragma once
#include <string>
#include <fstream>

using namespace std;

void generate_little_file(string fileName);	//generates file 10MB or bigger

void generate_big_file(string fileName);	//generates file ??? GB

void display_file_numbers_from_range(string fileName, int startNumber=1, int lastNumber=0);	//displays all the numbers between startNumber and lastNumber positions

//void dispaly_file(fstream& fileObject);

void display_file(string fileName);