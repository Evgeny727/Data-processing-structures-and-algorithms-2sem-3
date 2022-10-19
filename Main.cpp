#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "HeshAndBin.h"

int main()
{
    setlocale(LC_ALL, "ru");
	testBinTask();
	testHeshTable();
	cout << endl << "Main programm\n";
	HeshTable T;
	T.createHeshTable();
	insertInTable("Data.dat", T);
	outTable(T);
	deleteRecord("Data.dat", T, 21008);
	searchRecord("Data.dat", T, 20070);
	searchRecord("Data.dat", T, 21008);
    return 0;
}