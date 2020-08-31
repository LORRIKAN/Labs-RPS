#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <filesystem>
#include "VarCheck.h"

using namespace std;
using namespace std::filesystem;

enum Colors { blue = 9, green, azure, red, purple, yellow, white };

const int indent = 2;

void SetColor(int color) { // ��������� ����� � �������
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void CoutWithColor(int color, string message) { // ����� ��������� message � ������ color
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); // ��������� ����� �� color
	cout << message; // ����� ���������
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), white); // ��������� ����� �� �����
}

int NumberLenght(int number) { // ���������� ����� �����
	int lenght = 0;
	while (number != 0) {
		++lenght;
		number /= 10;
	}
	return lenght;
}

void OutputInConsoleOrigArr(int** arr, int n, int lenghtToSetw) {
	cout << "Original array:\n\n";
	SetColor(green);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cout << arr[i][j] << setw(lenghtToSetw);
		}
		cout << endl << left;
	}
	cout << endl << resetiosflags(ios::adjustfield);
	SetColor(white);
}

void OutputInConsoleTriangleArr(int* arr, int n, int lenghtToSetw) {
	cout << "\nTriangle array:\n\n";
	SetColor(azure);
	int k = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n - i; ++j, ++k) {
			cout << arr[k] << setw(lenghtToSetw); // ����� �������� � ������� ������� ��� ���������� ��������
		}
		cout << endl;
		int forTriangleOutput = lenghtToSetw * (i + 1) + 2; // ���������� ����� ������� �����
		cout << setw(forTriangleOutput);
	}
	cout << setw(0) << endl;
	SetColor(white);
}

string FilePathCheckReturnForOutput(string message) { // �������� ���� ��� ���������� � ����
	string filePath;
	bool isPathValid = false;

	while (!isPathValid) { // while isPathValid == false, �������� ���������� ���������� ����
		cout << "\n" << message;
		cin >> filePath;
		cin.ignore(INT_MAX, '\n');
		if (ifstream(filePath)) { // ���������� �� ����
			try {
				if (is_regular_file(filePath)) { //  �������� �� ����������� ����� (aux, con..) 
					SetColor(yellow);
					cout << "\nFile already exists. Do you want to overwrite it? 1 - Yes, 0 - No: ";
					bool toOverwrite = GetBool();
					SetColor(white);
					if (!toOverwrite) {
						continue;
					}
				}
			}
			catch (...) {
				CoutWithColor(red, "\nForbidden file name!\n");
				continue;
			}
		}

		ofstream file(filePath); // �������� ����� �� ��������� ����
		if (!file) { // �������� �� ������ � �������� �����
			CoutWithColor(red, "\nAccess denied!\n");
			continue;
		}
		isPathValid = true;
	}
	return filePath; // ������� ����������� ����
}

void OutputInFile(int** origArr, int* triangleArr, int n, int lenghtToSetw, bool saveTriangle, bool saveOrig) {
	if (saveTriangle) {
		ofstream file(FilePathCheckReturnForOutput("Input path to file to save triangle array, for example C:\\triangle.txt: "));

		file << n << endl;
		int k = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n - i; ++j, ++k) {
				file << triangleArr[k] << endl;
			}
		}
	}

	if (saveOrig) {
		ofstream file(FilePathCheckReturnForOutput("Input path to file to save original array, for example C:\\original.txt: "));
		file << n << endl << n << endl;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				file << origArr[i][j] << endl;
			}
		}
	}

	CoutWithColor(green, "\nSaved successfully!\n\n");

}