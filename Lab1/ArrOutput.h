#pragma once
#include <string>
using namespace std;

enum { blue = 9, green, azure, red, purple, yellow, white };
int NumberLenght(int number);
void CoutWithColor(int color, string message);
void OutputInConsoleTriangleArr(int* arr, int n, int maxNumberForSetw);
void OutputInConsoleOrigArr(int** arr, int n, int maxNumberForSetw);
void OutputInFile(int** origArr, int* triangleArr, int n, int lenghtToSetw, bool saveTriangle, bool saveOrig);
void SetColor(int color);