#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <filesystem>
#include "ArrOutput.h"
#include "VarCheck.h"
#include "ArrOutput.h"
#include "ArrChange.h"

using namespace std;
using namespace std::filesystem;

const int minArrSize = 1;
const int maxRandValue = 100;
const int indent = 2;

void EndingOutput(int** origArr, int** resultArr, int n, int m, int lenghtToSetw, int comparesAndSwaps[sortsNumber][parametersNumber]) {
	string table[5] = { "Bubble sort: ","Select sort: ", "Insert sort: ", "Shell sort:  ", "Quick sort:  " };
	SetColor(azure);
	cout << "\n            Compares:   Swaps:\n";
	for (int i = 0; i < sortsNumber; ++i) {
		cout << table[i];
		for (int j = 0; j < parametersNumber; ++j) {
			cout << comparesAndSwaps[i][j] << setw(13);
		}
		cout << endl;
	}
	cout << endl;
	SetColor(purple);
	cout << "Do you want to save original array in file? 1 - Yes, 0 - No: ";
	bool saveOrig = GetBool(); // ������ � ������������, ����� �� �� ��������� � ���� �������� ������
	SetColor(white);
	if (saveOrig) {
		OutputArrInFile(origArr, n, m);
		CoutWithColor(green, "\nSaved successfully!\n\n");
	}
	else {
		cout << endl;
	}
	SetColor(blue);
	cout << "Do you want to save sorted array in file? 1 - Yes, 0 - No: ";
	bool saveSorted = GetBool();
	SetColor(white);
	if (saveSorted) {
		OutputArrInFile(resultArr, n, m);
		CoutWithColor(green, "\nSaved successfully!\n\n");
	}
	else {
		cout << endl;
	}
	SetColor(azure);
	cout << "Do you want to save result of sorting? 1 - Yes, 0 - No: ";
	bool saveResult = GetBool();
	SetColor(white);
	if (saveResult){
		SaveResult(comparesAndSwaps);
		CoutWithColor(green, "\nSaved successfully!\n\n");
	} 
	else
		cout << endl;

	

	for (int i = 0; i < n; ++i) { //  ������������ ������, ���������� ��� ������� ���������� �������
		delete[] origArr[i];
		delete[] resultArr[i];
	}
	delete[] origArr; //  ������������ ������, ���������� ��� ������ ���������� �������
	delete[] resultArr;
}


int InputN() { //���� ���������� �����
	cout << "\nInput number of lines: ";
	int n;
	while (true) { // ���� ������������� �������� n � ��� ��������
		n = GetInt();
		if (n > minArrSize) {
			break;
		}
		else
			CoutWithColor(red, "\nTry again: ");

	}
	return n;
}

int InputM() { //���� ���������� �����
	cout << "\nInput number of column: ";
	int m;
	while (true) { // ���� ������������� �������� n � ��� ��������
		m = GetInt();
		if (m > minArrSize) {
			break;
		}
		else
			CoutWithColor(red, "\nTry again: ");
	}
	return m;
}

void ManualInput() { // ���� �������
	int n; // ���������� ��������� �� ���� ������������ 
	int m;
	int ArrSize;
	int maxNumberForSetw = 0; //  ������������ �����, ��� ���������� ����� �������
	bool userAgreed = false; // ����� �� ������������ ������ ���������� ��������� 
	while (!userAgreed) { // ���� ������������ �� �������� ������ ���������� ���������  ��� ������� ArrSize
		n = InputN(); // ���� n 
		m = InputM(); //���� m
		ArrSize = (n * m); // ���������� ArrSize
		string message = "\nYou will have to input ";
		message += to_string(ArrSize);
		message += " elements. Do you want to continue? 1- Yes, 0 - No: ";
		CoutWithColor(yellow, message);
		userAgreed = GetBool();
	}
	int** origArr = new int* [n]; // �������� ����������  ������� ������������ n
	for (int i = 0; i < n; ++i) { // ��������� ������ ��� ������� ��������� �������
		origArr[i] = new int[m];
	}
	for (int i = 0; i < n; ++i) { // ������������ ��������� ������� ��������� ������������� ��������
			for (int j = 0; j < m; ++j) {
				cout << endl << "Arr[" << i + 1  << "]["<< j + 1 << "] = ";
				origArr[i][j] = GetInt();
				if (abs(origArr[i][j]) > maxNumberForSetw) {
					maxNumberForSetw = abs(origArr[i][j]);
				}
			}
		}
	int comparesAndSwaps[sortsNumber][parametersNumber];
	int lenghtToSetw = NumberLenght(maxNumberForSetw) + indent;
	OutputInConsoleArr(origArr, n, m, lenghtToSetw, "\nOriginal array:\n\n", purple);
	int** resultArr = ArrChange(origArr, n, m, comparesAndSwaps, lenghtToSetw);
	EndingOutput(origArr,resultArr, n, m, lenghtToSetw, comparesAndSwaps);
}


void RandomInput() { // ��������� ��������� ����� ��� �������
	srand(static_cast<unsigned int>(time(nullptr))); // ��� ��������� ������ ������������������ ������������ rand()
	int n = InputN();// ���� n 
	int m = InputM(); // ���� m
	int maxNumberForSetw = 0; //  ������������ �����, ��� ���������� ����� �������
	int** origArr = new int* [n]; // �������� ���������� �������
	for (int i = 0; i < n; ++i) { 
		origArr[i] = new int[m];
	}
	for (int i = 0; i < n; ++i) { // ������������ ��������� ������� ��������������� ��������
			for (int j = 0; j < m; ++j) {
				origArr[i][j] = rand() % maxRandValue;
				if (abs(origArr[i][j]) > maxNumberForSetw) {
					maxNumberForSetw = abs(origArr[i][j]);
				}
			}
	}
	int comparesAndSwaps[sortsNumber][parametersNumber];
	int lenghtToSetw = NumberLenght(maxNumberForSetw) + indent;
	OutputInConsoleArr(origArr, n, m, lenghtToSetw, "\nOriginal array:\n\n", purple);
	int** resultArr = ArrChange(origArr, n, m, comparesAndSwaps, lenghtToSetw);
	EndingOutput(origArr, resultArr, n, m, lenghtToSetw, comparesAndSwaps);
}

string FilePathCheckReturnForInput() { // �������� ���� ��� ������ �� �����
	string filePath;
	bool isPathValid = false;

	while (!isPathValid) { // while isPathValid == false, �������� ���������� ���������� ����
		cout << "\nInput path to file with array, for example C:\\Directory\\Array.txt : ";
		cin >> filePath;
		cin.ignore(INT_MAX, '\n');

		if (!ifstream(filePath)) { // ���������� �� ����
			CoutWithColor(red, "\nFile does not exist!\n");
			continue;

		}
		try {
			is_regular_file(filePath);
		}
		catch (...) {
			CoutWithColor(red, "\nForbidden file name!\n");
			continue;
		}

		ifstream file(filePath);
		if (!file) { //�������� ������� � �����
			CoutWithColor(red, "\nAccess denied!\n");
			continue;
		}

		isPathValid = true;
	}
	return filePath;
}
	
void FileInput() { //���������� ������ �� �����
	bool valCorrect = false; // �������� �� ������������ int � ������ �� ����� while, ���� ��� �������� ��������
	int n;
	int m;
	int maxNumberForSetw = 0;
	while (!valCorrect) {
		string filePath = FilePathCheckReturnForInput();
		ifstream file(filePath);
		if (!(file >> n) || n <= minArrSize || !(file >> m)|| m <= minArrSize) { //�������� ������� �������
			CoutWithColor(red, "\nIncorrect array size.\n");
			continue;
		}
		int** origArr = new int* [n]; // �������� ���������� �������
		for (int i = 0; i < n; i++) {
			origArr[i] = new int[m];
		}
		bool toContinue = false; // ��� �������� � ������ ����� while, ��� ��� continue ��������� ���� for
		bool toBreak = false;
		for (int i = 0; i < n && !toBreak; i++) { // ������������ ��������� ������� ��������������� ��������
			for (int j = 0; j < m; j++) {
				if (!(file >> origArr[i][j])) {
					CoutWithColor(red, "\nIncorrect array value.\n");
					toContinue = true;
					toBreak = true;
					break;
				}
				if (abs(origArr[i][j]) > maxNumberForSetw) {
					maxNumberForSetw = abs(origArr[i][j]);
				}
			}
		}
		if (toContinue) {
			for (int i = 0; i < n; ++i)
				delete[] origArr[i];
			delete[] origArr;
			continue;
		}
		valCorrect = true;
		int comparesAndSwaps[sortsNumber][parametersNumber];
		int lenghtToSetw = NumberLenght(maxNumberForSetw) + indent;
		OutputInConsoleArr(origArr, n, m, lenghtToSetw, "\nOriginal array:\n\n", purple);
		int** resultArr = ArrChange(origArr, n, m, comparesAndSwaps, lenghtToSetw);
		EndingOutput(origArr, resultArr, n, m, lenghtToSetw, comparesAndSwaps);
	}
}