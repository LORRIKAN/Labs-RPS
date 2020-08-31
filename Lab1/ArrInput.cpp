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

void EndingOutput(int* triangleArr, int** origArr, int n, int maxNumberForSetw) { // вывод в консоль и в файл обоих массивов
	int lenghtToSetw = NumberLenght(maxNumberForSetw) + indent; // длина отступа
	OutputInConsoleTriangleArr(triangleArr, n, lenghtToSetw); // вывод в консоль треугольной матрицы
	OutputInConsoleOrigArr(origArr, n, lenghtToSetw); // вывод в консоль исходной матрицы
	SetColor(purple);
	cout << "Do you want to save triangle array in file? 1 - Yes, 0 - No: ";
	bool saveTriangle = GetBool(); // запрос у пользователя, хочет ли он сохранить в файл оба массива
	SetColor(azure);
	cout << "\nDo you want to save original array in file? 1 - Yes, 0 - No: ";
	bool saveOrig = GetBool();
	SetColor(white);
	if (saveTriangle || saveOrig)
		OutputInFile(origArr, triangleArr, n, lenghtToSetw, saveTriangle, saveOrig);
	else
		cout << endl;
	delete[] triangleArr; // освобождение памяти, выделенной под треугольный массив
	for (int i = 0; i < n; ++i) { //  освобождение памяти, выделенной под столбцы двумерного массива
		delete[] origArr[i];
	}
	delete[] origArr; //  освобождение памяти, выделенной под строки двумерного массива

}

int InputN() { //ввод количества элементов n
	cout << "\nInput n, original array size will be n*n: ";
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

void ManualInput() { // ввод вручную
	int n; // количество элементов на ввод пользователю 
	int triangleArrSize; // размер треугольного массива по формуле (n * (n + 1)) / 2
	int maxNumberForSetw = 0; //  Максимальное число, для вычисления длины отступа
	bool userAgreed = false; // Хочет ли пользователь ввести количество элементов = triangleArrSize
	while (!userAgreed) { // пока пользователь не согласен ввести количество элементов triangleArrSize
		n = InputN(); // ввод n 
		triangleArrSize = (n * (n + 1)) / 2; // вычисление triangleArrSize
		string message = "\nYou will have to input ";
		message += to_string(triangleArrSize);
		message += " elements. Do you want to continue? 1- Yes, 0 - No: ";
		CoutWithColor(yellow, message);
		userAgreed = GetBool();
	}
	int* triangleArr = new int[triangleArrSize]; // создание одномерного треугольного массива размерностью triangleArrSize
	for (int i = 0; i < triangleArrSize; ++i) { // присваевание элементам массива введенные пользователем значения
		cout << endl << "Arr[" << i + 1 << "] = ";
		triangleArr[i] = GetInt();
		if (abs(triangleArr[i]) > maxNumberForSetw) { // поиск максимального по модулю элемента для вычисления отступа
			maxNumberForSetw = abs(triangleArr[i]);
		}
	}
	cout << endl;
	int** origArr = ArrChange(triangleArr, n); // объявление двумерного исходного массива
	EndingOutput(triangleArr, origArr, n, maxNumberForSetw); // вывод в консоль и в файл обоих массивов
}


void RandomInput() { // генерация случайных чисел для массива
	srand(static_cast<unsigned int>(time(nullptr))); // для установки начала последовательности генерируемой rand()
	int n = InputN();// ввод n 
	int triangleArrSize = (n * (n + 1)) / 2; // размер треугольного массива по формуле (n * (n + 1)) / 2
	int maxNumberForSetw = 0; //  Максимальное число, для вычисления длины отступа
	int* triangleArr = new int[triangleArrSize]; // создание одномерного треугольного массива размерностью triangleArrSize
	for (int i = 0; i < triangleArrSize; ++i) { // помещение рандомно сгенерированных чисел в массив
		triangleArr[i] = rand() % maxRandValue; // ограничение рандомного числа 
		if (abs(triangleArr[i]) > maxNumberForSetw) { // поиск максимального по модулю элемента для вычисления отступа
			maxNumberForSetw = triangleArr[i];
		}
	}
	int** origArr = ArrChange(triangleArr, n); // объявление двумерного исходного массива
	EndingOutput(triangleArr, origArr, n, maxNumberForSetw); // вывод в консоль и в файл обоих массивов
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
	int maxNumberForSetw = 0;
	int* triangleArr; // объявление указателя на треугольную матрицу
	while (!valCorrect) {
		string filePath = FilePathCheckReturnForInput();
		ifstream file(filePath);
		if (!(file >> n) || n < minArrSize) { //проверка размера массива
			CoutWithColor(red, "\nIncorrect array size.\n");
			continue;
		}
		int triangleArrSize = (n * (n + 1)) / 2; // размер треугольного массива по формуле (n * (n + 1)) / 2
		triangleArr = new int[triangleArrSize]; // создание одномерного треугольного массива размерностью triangleArrSize
		bool toContinue = false; // для перехода в начало цикла while, так как continue продолжит цикл for
		for (int i = 0; i < triangleArrSize; ++i) { // проверка элементов массива
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
		int** origArr = ArrChange(triangleArr, n); // объявление двумерного исходного массива
		EndingOutput(triangleArr, origArr, n, maxNumberForSetw); // вывод в консоль и в файл обоих массивов
	}

}