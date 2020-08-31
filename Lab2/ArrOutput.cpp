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

void SetColor(int color) { // изменение цвета в консоли
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void CoutWithColor(int color, string message) { // вывод сообщения message с цветом color
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); // изменение цвета на color
	cout << message; // вывод сообщения
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), white); // изменение цвета на белый
}

int NumberLenght(int number) { // вычисление длины числа
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
string FilePathCheckReturnForOutput(string message) { // проверка пути для сохранения в файл
	string filePath;
	bool isPathValid = false;

	while (!isPathValid) { // while isPathValid == false, проверка валидности введенного пути
		cout << "\n" << message;
		cin >> filePath;
		cin.ignore(INT_MAX, '\n');
		if (ifstream(filePath)) { // существует ли файл
			try {
				if (is_regular_file(filePath)) { //  проверка на запрещенные имена (aux, con..) 
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

		ofstream file(filePath); // создание файла по заданному пути
		if (!file) { // проверка на доступ к созданию файла
			CoutWithColor(red, "\nAccess denied!\n");
			continue;
		}
		isPathValid = true;
	}
	return filePath; // возврат корректного пути
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