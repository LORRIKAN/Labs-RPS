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
	bool saveOrig = GetBool(); // запрос у пользователя, хочет ли он сохранить в файл исходный массив
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

	

	for (int i = 0; i < n; ++i) { //  освобождение памяти, выделенной под столбцы двумерного массива
		delete[] origArr[i];
		delete[] resultArr[i];
	}
	delete[] origArr; //  освобождение памяти, выделенной под строки двумерного массива
	delete[] resultArr;
}


int InputN() { //ввод количества строк
	cout << "\nInput number of lines: ";
	int n;
	while (true) { // ввод пользователем элемента n и его проверка
		n = GetInt();
		if (n > minArrSize) {
			break;
		}
		else
			CoutWithColor(red, "\nTry again: ");

	}
	return n;
}

int InputM() { //ввод количества строк
	cout << "\nInput number of column: ";
	int m;
	while (true) { // ввод пользователем элемента n и его проверка
		m = GetInt();
		if (m > minArrSize) {
			break;
		}
		else
			CoutWithColor(red, "\nTry again: ");
	}
	return m;
}

void ManualInput() { // ввод вручную
	int n; // количество элементов на ввод пользователю 
	int m;
	int ArrSize;
	int maxNumberForSetw = 0; //  Максимальное число, для вычисления длины отступа
	bool userAgreed = false; // Хочет ли пользователь ввести количество элементов 
	while (!userAgreed) { // пока пользователь не согласен ввести количество элементов  для расчёта ArrSize
		n = InputN(); // ввод n 
		m = InputM(); //ввод m
		ArrSize = (n * m); // вычисление ArrSize
		string message = "\nYou will have to input ";
		message += to_string(ArrSize);
		message += " elements. Do you want to continue? 1- Yes, 0 - No: ";
		CoutWithColor(yellow, message);
		userAgreed = GetBool();
	}
	int** origArr = new int* [n]; // создание двумерного  массива размерностью n
	for (int i = 0; i < n; ++i) { // выделение памяти под столбцы исходного массива
		origArr[i] = new int[m];
	}
	for (int i = 0; i < n; ++i) { // присваевание элементам массива введенные пользователем значения
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


void RandomInput() { // генерация случайных чисел для массива
	srand(static_cast<unsigned int>(time(nullptr))); // для установки начала последовательности генерируемой rand()
	int n = InputN();// ввод n 
	int m = InputM(); // ввод m
	int maxNumberForSetw = 0; //  Максимальное число, для вычисления длины отступа
	int** origArr = new int* [n]; // создание двумерного массива
	for (int i = 0; i < n; ++i) { 
		origArr[i] = new int[m];
	}
	for (int i = 0; i < n; ++i) { // присваевание элементам массива сгенерированные значения
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

string FilePathCheckReturnForInput() { // проверка пути для чтения из файла
	string filePath;
	bool isPathValid = false;

	while (!isPathValid) { // while isPathValid == false, проверка валидности введенного пути
		cout << "\nInput path to file with array, for example C:\\Directory\\Array.txt : ";
		cin >> filePath;
		cin.ignore(INT_MAX, '\n');

		if (!ifstream(filePath)) { // существует ли файл
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
		if (!file) { //проверка доступа к файлу
			CoutWithColor(red, "\nAccess denied!\n");
			continue;
		}

		isPathValid = true;
	}
	return filePath;
}
	
void FileInput() { //считывание данных из файла
	bool valCorrect = false; // проверка на соответствие int и выхода из цикла while, если все значения корректы
	int n;
	int m;
	int maxNumberForSetw = 0;
	while (!valCorrect) {
		string filePath = FilePathCheckReturnForInput();
		ifstream file(filePath);
		if (!(file >> n) || n <= minArrSize || !(file >> m)|| m <= minArrSize) { //проверка размера массива
			CoutWithColor(red, "\nIncorrect array size.\n");
			continue;
		}
		int** origArr = new int* [n]; // создание двумерного массива
		for (int i = 0; i < n; i++) {
			origArr[i] = new int[m];
		}
		bool toContinue = false; // для перехода в начало цикла while, так как continue продолжит цикл for
		bool toBreak = false;
		for (int i = 0; i < n && !toBreak; i++) { // присваевание элементам массива сгенерированные значения
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