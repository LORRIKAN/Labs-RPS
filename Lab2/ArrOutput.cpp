#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <filesystem>
#include "VarCheck.h"
#include "ArrOutput.h"
#include "ArrChange.h"

using namespace std;
using namespace std::filesystem;

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

void OutputInConsoleArr(int** arr, int n, int m, int lenghtToSetw, string message, int color) {
	SetColor(color);
	cout << message;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cout << arr[i][j] << setw(lenghtToSetw);
		}
		cout << endl << left;
	}
	cout << endl << resetiosflags(ios::adjustfield);
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
void OutputArrInFile(int** arr, int n, int m) {
	ofstream file(FilePathCheckReturnForOutput("Input path to file to save original array, for example C:\\1.txt: "));

	file << n << endl << m << endl;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			file << arr[i][j] << endl;
		}
	}

}

void SaveResult(int comparesAndSwaps[sortsNumber][parametersNumber]) {
	ofstream file(FilePathCheckReturnForOutput("Input path to file to save the results of sorts working, for example C:\\1.txt: "));
	string table[5] = { "Bubble sort: ","Select sort: ", "Insert sort: ", "Shell sort:  ", "Quick sort:  " };
	file << "            Compares:   Swaps:\n";
	for (int i = 0; i < sortsNumber; ++i) {
		file << table[i];
		for (int j = 0; j < parametersNumber; ++j) {
			file << comparesAndSwaps[i][j] << setw(13);
		}
		file << endl;
	}
	file << endl;
}