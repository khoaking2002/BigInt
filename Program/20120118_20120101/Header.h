#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <time.h>
using namespace std;
ifstream fi("input.txt");
ofstream fo("output.txt");
struct BigInt
{
	bool sign = 0;
	string data;
};


