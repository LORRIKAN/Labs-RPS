#include <iostream>
#include <Windows.h>
#include <iomanip>
#include "VarCheckAndColorSet.h"

using namespace std;

typedef double(*Myf_485)(double x, double a, double eps); //вычисление рядной функции, получение указателя на функцию из библиотеки
typedef double(*Myf_math)(double x, double a);          //вычисление функции из math.h
typedef char* (*FName)();                          //запрос имени функции

bool Calculation() {
	bool running = true;
	HINSTANCE hGetProcIDDLL = LoadLibrary(TEXT("MathDLL.dll")); //загрузка библиотеки, получение указателя
	if (!hGetProcIDDLL) {
		cout << "Error opening dll. Press any key to exit." << endl;
		running = false;
		return running;
	}

	Myf_485 myf_485 = (Myf_485)GetProcAddress(hGetProcIDDLL, "myf_485"); //загрузка функции
	if (!myf_485) {
		cout << "Error loading function. Press any key to exit." << endl;
		running = false;
		return running;
	}

	FName Fname = (FName)GetProcAddress(hGetProcIDDLL, "FName"); //загрузка функции
	if (!Fname) {
		cout << "\nError loading function. Press any key to exit." << endl;
		running = false;
		return running;
	}

	Myf_math myf_math = (Myf_math)GetProcAddress(hGetProcIDDLL, "myf_math"); //загрузка функции
	if (!myf_math) {
		cout << "\nError loading function. Press any key to exit." << endl;
		running = false;
		return running;
	}
	double start, step, end, eps, a;
	do {
		cout << "\nInput x start. It must be between -1 and 1: ";
		start = GetDouble();
	} while (start >= 1 || start <= -1);
	do {
		cout << "\nInput x end. It must be between -1 and 1: ";
		end = GetDouble();
	} while (end < start || end >= 1 || end <= -1);
	do {
		cout << "\nInput x step. It must be between -1 and 1: ";
		step = GetDouble();
	} while (start + step <= start || step >= 1 || step <= -1);
	do {
		cout << "\nInput epsilon. It must be between 0.1 and 0.0000001: ";
		eps = GetDouble();
	} while (eps > 0.1 || eps < 10e-7);
	cout << "\nInput a parametr: ";
	a = GetDouble();
	int startInt = start * 10e7;
	int stepInt = step * 10e7;
	int endInt = end * 10e7;
	char* funcName = Fname();
	cout << setw(20) << left << "x" << setw(3) << left << "My " << setw(17) << left << funcName << setw(20) << left << funcName << setw(20) << left << "Disperency" << endl;
	SetColor(green);
	cout << fixed << setprecision(7);
	double x = start;
	double myf_485Result, myf_mathResult, disperency;
	for (int i = startInt; i <= endInt; i += stepInt, x += step) {
		myf_485Result = myf_485(x, a, eps);
		myf_mathResult = myf_math(x, a);
		disperency = abs(myf_485Result - myf_mathResult);
		if (disperency > 1) {
			cout << setw(20) << left << x << setw(20) << left << 0 << setw(20) << left << myf_mathResult << setw(20) << left << 0 << endl;
		}
		else
			cout << setw(20) << left << x << setw(20) << left << myf_485Result << setw(20) << left << myf_mathResult << setw(20) << left << disperency << endl;
	}
	SetColor(white);
	double ideal;
	do {
		cout << "\nInput x ideal. It must be between -1 and 1: ";
		ideal = GetDouble();
	} while (ideal >= 1 || ideal <= -1);
	eps = 0.1;
	cout << setw(20) << left << "\nEpsilon" << setw(3) << left << "My " << setw(17) << left << funcName << setw(20) << left << funcName << setw(20) << left << "Disperency" << endl;
	SetColor(purple);
	for (int i = 0; i < 7; ++i, eps /= 10) {
		myf_485Result = myf_485(ideal, a, eps);
		myf_mathResult = myf_math(ideal, a);
		cout << setw(20) << left << eps << setw(20) << left << myf_485Result << setw(20) << left << myf_mathResult << setw(20) << left << abs(myf_485Result - myf_mathResult) << endl;
	}
	SetColor(white);
	cout << endl;
	delete[] funcName;
	FreeLibrary(hGetProcIDDLL);
	return running;
}