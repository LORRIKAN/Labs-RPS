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
			cout << arr[k] << setw(lenghtToSetw); // вывод элемента и задание отступа для следующего элемента
		}
		cout << endl;
		int forTriangleOutput = lenghtToSetw * (i + 1) + 2; // вычисление длины отступа слева
		cout << setw(forTriangleOutput);
	}
	cout << setw(0) << endl;
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