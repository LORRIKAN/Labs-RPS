#pragma once
#include <string>
#include <Windows.h>
#include "ArrChange.h"
using namespace std;

enum Color { blue = 9, green, azure, red, purple, yellow, white };
void CoutWithColor(int color, string message);
void SetColor(int color);
void OutputInConsoleArr(int** arr, int n, int m, int lenghtToSetw, string message, int color);
int NumberLenght(int number);
void OutputArrInFile(int** arr, int n, int m);
void SaveResult(int comparesAndSwaps[sortsNumber][parametersNumber]);