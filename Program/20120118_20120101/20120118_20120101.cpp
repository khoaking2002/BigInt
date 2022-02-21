#include "Header.h"
#include "MainFunction.h"
void main(int argc, char** argv) {
	ifstream fi(argv[1]);
	ofstream fo(argv[2]);
	while (!fi.eof())
	{
		string st, he = "", pheptoan = "", tg = "";
		BigInt s1, s2;
		getline(fi, st, '\n');
		Input(st, s1, s2, he, pheptoan, tg);
		Operation(s1, s2, he, pheptoan, tg);
	}
	fi.close();
	fo.close();
}
//1: so am
//0: so duong
