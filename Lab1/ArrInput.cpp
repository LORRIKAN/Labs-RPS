#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <filesystem>
#include "VarCheck.h"
#include "ArrChange.h"
#include "ArrOutput.h"

using namespace std;
using namespace std::filesystem;

const int minArrSize = 1;
const int maxRandValue = 100;
const int indent = 2;

void EndingOutput(int* triangleArr, int** origArr, int n, int maxNumberForSetw) { // ����� � ������� � � ���� ����� ��������
	int lenghtToSetw = NumberLenght(maxNumberForSetw) + indent; // ����� �������
	OutputInConsoleTriangleArr(triangleArr, n, lenghtToSetw); // ����� � ������� ����������� �������
	OutputInConsoleOrigArr(origArr, n, lenghtToSetw); // ����� � ������� �������� �������
	SetColor(purple);
	cout << "Do you want to save triangle array in file? 1 - Yes, 0 - No: ";
	bool saveTriangle = GetBool(); // ������ � ������������, ����� �� �� ��������� � ���� ��� �������
	SetColor(azure);
	cout << "\nDo you want to save original array in file? 1 - Yes, 0 - No: ";
	bool saveOrig = GetBool();
	SetColor(white);
	if (saveTriangle || saveOrig)
		OutputInFile(origArr, triangleArr, n, lenghtToSetw, saveTriangle, saveOrig);
	else
		cout << endl;
	delete[] triangleArr; // ������������ ������, ���������� ��� ����������� ������
	for (int i = 0; i < n; ++i) { //  ������������ ������, ���������� ��� ������� ���������� �������
		delete[] origArr[i];
	}
	delete[] origArr; //  ������������ ������, ���������� ��� ������ ���������� �������

}

int InputN() { //���� ���������� ��������� n
	cout << "\nInput n, original array size will be n*n: ";
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

void ManualInput() { // ���� �������
	int n; // ���������� ��������� �� ���� ������������ 
	int triangleArrSize; // ������ ������������ ������� �� ������� (n * (n + 1)) / 2
	int maxNumberForSetw = 0; //  ������������ �����, ��� ���������� ����� �������
	bool userAgreed = false; // ����� �� ������������ ������ ���������� ��������� = triangleArrSize
	while (!userAgreed) { // ���� ������������ �� �������� ������ ���������� ��������� triangleArrSize
		n = InputN(); // ���� n 
		triangleArrSize = (n * (n + 1)) / 2; // ���������� triangleArrSize
		string message = "\nYou will have to input ";
		message += to_string(triangleArrSize);
		message += " elements. Do you want to continue? 1- Yes, 0 - No: ";
		CoutWithColor(yellow, message);
		userAgreed = GetBool();
	}
	int* triangleArr = new int[triangleArrSize]; // �������� ����������� ������������ ������� ������������ triangleArrSize
	for (int i = 0; i < triangleArrSize; ++i) { // ������������ ��������� ������� ��������� ������������� ��������
		cout << endl << "Arr[" << i + 1 << "] = ";
		triangleArr[i] = GetInt();
		if (abs(triangleArr[i]) > maxNumberForSetw) { // ����� ������������� �� ������ �������� ��� ���������� �������
			maxNumberForSetw = abs(triangleArr[i]);
		}
	}
	cout << endl;
	int** origArr = ArrChange(triangleArr, n); // ���������� ���������� ��������� �������
	EndingOutput(triangleArr, origArr, n, maxNumberForSetw); // ����� � ������� � � ���� ����� ��������
}


void RandomInput() { // ��������� ��������� ����� ��� �������
	srand(static_cast<unsigned int>(time(nullptr))); // ��� ��������� ������ ������������������ ������������ rand()
	int n = InputN();// ���� n 
	int triangleArrSize = (n * (n + 1)) / 2; // ������ ������������ ������� �� ������� (n * (n + 1)) / 2
	int maxNumberForSetw = 0; //  ������������ �����, ��� ���������� ����� �������
	int* triangleArr = new int[triangleArrSize]; // �������� ����������� ������������ ������� ������������ triangleArrSize
	for (int i = 0; i < triangleArrSize; ++i) { // ��������� �������� ��������������� ����� � ������
		triangleArr[i] = rand() % maxRandValue; // ����������� ���������� ����� 
		if (abs(triangleArr[i]) > maxNumberForSetw) { // ����� ������������� �� ������ �������� ��� ���������� �������
			maxNumberForSetw = triangleArr[i];
		}
	}
	int** origArr = ArrChange(triangleArr, n); // ���������� ���������� ��������� �������
	EndingOutput(triangleArr, origArr, n, maxNumberForSetw); // ����� � ������� � � ���� ����� ��������
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
	int maxNumberForSetw = 0;
	int* triangleArr; // ���������� ��������� �� ����������� �������
	while (!valCorrect) {
		string filePath = FilePathCheckReturnForInput();
		ifstream file(filePath);
		if (!(file >> n) || n < minArrSize) { //�������� ������� �������
			CoutWithColor(red, "\nIncorrect array size.\n");
			continue;
		}
		int triangleArrSize = (n * (n + 1)) / 2; // ������ ������������ ������� �� ������� (n * (n + 1)) / 2
		triangleArr = new int[triangleArrSize]; // �������� ����������� ������������ ������� ������������ triangleArrSize
		bool toContinue = false; // ��� �������� � ������ ����� while, ��� ��� continue ��������� ���� for
		for (int i = 0; i < triangleArrSize; ++i) { // �������� ��������� �������
			if (!(file >> triangleArr[i])) {
				CoutWithColor(red, "\nIncorrect array value.\n");
				toContinue = true;
				break;
			}
			if (abs(triangleArr[i]) > maxNumberForSetw) {
				maxNumberForSetw = abs(triangleArr[i]);
			}
		}
		if (toContinue) continue;
		valCorrect = true;
		int** origArr = ArrChange(triangleArr, n); // ���������� ���������� ��������� �������
		EndingOutput(triangleArr, origArr, n, maxNumberForSetw); // ����� � ������� � � ���� ����� ��������
	}

}