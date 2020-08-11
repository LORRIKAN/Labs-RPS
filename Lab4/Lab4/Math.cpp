#include <iostream>
#include <vector>
#include <cmath>
#include <Windows.h>
#include <iomanip>
#include "MenuColorAndCheck.h"
#include "Math.h"

using namespace std;

struct FirstTable {
	double x;
	double myFuncResult;
	double mathFuncResult;
	double discrepancy = 0;
	FirstTable(double x, double myFuncResult, double mathFuncResult) : x(x), myFuncResult(myFuncResult), 
		mathFuncResult(mathFuncResult) {
		if (static_cast<long long>(myFuncResult*10e7) != 0)
			discrepancy = sqrt(abs(pow(myFuncResult, 2) - pow(mathFuncResult, 2)));
	}
};

struct SecondTable {
	double eps;
	double myFuncResult;
	double mathFuncResult;
	double discrepancy = 0;
	SecondTable(double eps, double myFuncResult, double mathFuncResult) : eps(eps), myFuncResult(myFuncResult),
		mathFuncResult(mathFuncResult) {
		if (static_cast<long long>(myFuncResult*10e7) != 0)
			discrepancy = sqrt(abs(pow(myFuncResult, 2) - pow(mathFuncResult, 2)));
	}
};

void InputAndCalc() {
	HINSTANCE hGetProcIDDLL = LoadLibrary(TEXT("MathDLL.dll")); //загрузка библиотеки
	if (!hGetProcIDDLL) {
		cout << "Error opening dll. Press any key to exit." << endl;
		getchar();
		exit(1);
	}

	Myf_485 myf_485 = (Myf_485)GetProcAddress(hGetProcIDDLL, "myf_485"); //загрузка функции
	if (!myf_485) {
		cout << "Error loading function. Press any key to exit." << endl;
		getchar();
		exit(2);
	}

	FName Fname = (FName)GetProcAddress(hGetProcIDDLL, "FName"); //загрузка функции
	if (!Fname) {
		cout << "Error loading function. Press any key to exit." << endl;
		getchar();
		exit(2);
	}

	Myf_math myf_math = (Myf_math)GetProcAddress(hGetProcIDDLL, "myf_math"); //загрузка функции
	if (!myf_math) {
		cout << "Error loading function. Press any key to exit." << endl;
		getchar();
		exit(2);
	}

	vector<FirstTable> firstTable;
	double start, step, end, eps, ideal, a;
		cout << "Input x start: ";
		start = GetDouble();
		do {
			cout << "Input x end: ";
			end = GetDouble();
		} while (end < start);
	do {
		cout << "Input x step: ";
		step = GetDouble();
	} while (start + step <= start);
	do {
		cout << "Input epsilon: ";
		eps = GetDouble();
	} while (eps > 0.1 || eps < 10e-7);
	cout << "Input a parametr: ";
	a = GetDouble();
	double i = start;
	double k = step;
	start = static_cast<long long>(start * 10e7);
	end = static_cast<long long>(end * 10e7);
	step = static_cast<long long>(step * 10e7);

	for (long long j = start; j <= end; j += step, i += k) {
		firstTable.emplace_back(i, myf_485(i, a, eps), myf_math(i, 2));
	}

	cout << setw(20) << left << "x" << setw(3) << left << "My " << setw(17) << left << Fname() << setw(20) << left << Fname() << setw(20) << left << "disperency" << endl;
	SetColor(green);
	cout << fixed << setprecision(7);
	for (const auto it : firstTable) {
		cout << setw(20) << left << it.x << setw(20) << left << it.myFuncResult << setw(20) << left << it.mathFuncResult << setw(20) << left << it.discrepancy << endl;
	}
	SetColor(white);
	cout << endl;

	vector<SecondTable> secondTable;
	cout << "Input x ideal: ";
	ideal = GetDouble();
	eps = 0.1;
	for (int j = 0; j < 7; j++, eps /= 10)
		secondTable.emplace_back(eps, myf_485(ideal, a, eps), myf_math(ideal, 2));

	cout << setw(20) << left << "epsilon" << setw(3) << left << "My " << setw(17) << left << Fname() << setw(20) << left << Fname() << setw(20) << left << "disperency" << endl;
	SetColor(purple);
	for (const auto it : secondTable)
		cout << setw(20) << left << it.eps << setw(20) << left << it.myFuncResult << setw(20) << left << it.mathFuncResult << setw(20) << left << it.discrepancy << endl;
	SetColor(white);

	firstTable.clear();
	secondTable.clear();
	FreeLibrary(hGetProcIDDLL);
}