#include "pch.h"
#include "InputAndCheck.h"
#include "Output.h"
#include "ArrChange.h"

using namespace std;
using namespace experimental::filesystem;

const int minSize = 2;

void FileInput() {//заполнение массива из файла
	string filePath;
	bool isDataLoaded = false;
	int size;
	do {
		cout << "Input path to file, for example: C:\\Directory\\textfile.txt: " << endl;
		cin >> filePath;

		if (!ifstream(filePath)) {//если файла не существует
			SetColor(red);
			cout << "File does not exist! Input another path!" << endl;
			SetColor(white);
			cin.ignore(INT_MAX, '\n');
			continue;
		}

		if (!is_regular_file(filePath)) {//проверка на валидность имени (защита от aux, com и т.д.)
			SetColor(red);
			cout << "Incorrect file path. Enter another one!" << endl;
			SetColor(white);
			cin.ignore(INT_MAX, '\n');
			continue;
		}

		ifstream myFile(filePath);

		if (!myFile) {//если нет доступа к файлу
			SetColor(red);
			cout << "Access denied! Enter another path!" << endl;
			SetColor(white);
			myFile.close();
			continue;
		}
			if (!(myFile >> size) || size < minSize) {//считывание размера массива и проверка
				SetColor(red);//на валидность введённых данных
				cout << "Incorrect array size!" << endl;
				SetColor(white);
				myFile.close();
				continue;
			}

			int *arr = new int[size*size];//если все проверки пройдены успешно, создаётся одномерный массив

			bool toBreakAndContinue = false;//для выхода из двух циклов в случае ввода невалидного значения и
																			//перехода в начало программы

			for (int i = 0; i < size * size; i++)//считывание элементов массива и проверка их на валидность
					if (!(myFile >> arr[i])) {//если введено не int значение, выход из циклов и переход в начало программы
						SetColor(red);
						cout << "Invalid value type or not enough elements in file. Edit the file and try again! " << endl;
						SetColor(white);
						myFile.close();
						toBreakAndContinue = true;
						delete[] arr;
						break;
					}
			if (toBreakAndContinue)
				continue;
			
				SetColor(green);
				cout << "Loaded successfully!" << endl << endl;
				cout << "You entered:" << endl;
				OutputInConsole(arr, size);
				cout << endl;
				SetColor(white);
				isDataLoaded = true;
				myFile.close();
				ArrChange(arr, size);//выполнение задания по изменению массива
				delete[] arr;
	} while (!isDataLoaded);
}

void RandomFilling() {//случайное заполнение
	srand(static_cast <unsigned int> (time(nullptr)));//для генерации случайных чисел при каждом запуске
	int size;
	bool choice;
	cout << "Enter a size of the array: ";
	size = GetUnsignedInt();//запрос размера массива
	if (size >= minSize) {
		int *arr = new int[size*size];//создаётся двумерный массив
		for (int i = 0; i < size*size; i++)//заполнение случайными значениями
			arr[i] = rand() % 1001;
		SetColor(green);
		cout << "You entered:" << endl;
		OutputInConsole(arr, size);//вывод созданного массива в консоль
		SetColor(white);
		cout << endl << "Do you want to save the array you entred into the file?" << endl
			<< "[0] - No" << endl
			<< "[1] - Yes" << endl
			<< "Your choice:";
		choice = GetBool();//запрос от пользователя, хочет ли он сохранить полученный массив в файл
		if (choice) {
			bool orig = true;
			OutputDataInFile(arr, size, orig);
		}
		ArrChange(arr, size);//выполнение задания по изменению массива
		delete[] arr;
	}
	else {
		SetColor(red);
		cout << "Invalid lines and columns values, try again!" << endl;
		SetColor(white);
		RandomFilling();
	}
}

void ManualInput() {//ввод всех данных вручную
	int size;
	bool choice;
	cout << "Enter a size of the array: ";
	size = GetUnsignedInt();
	if (size >= minSize) {
		int *arr = new int[size*size];//создание двумерного массива
		cout << "Input it!" << endl;
		for (int i = 0, j = 0, tmp = 0, tmp1 = size; j < size*size; j++, tmp++) {
			if (j == tmp1) {
				tmp1 += size;
				i++;
				tmp = 0;
			}
			cout << "A[" << i + 1 << "]"
					 << "[" << tmp + 1 << "] = ";
			arr[j] = GetInt();//ввод значений вручную
		}
		SetColor(green);
		cout << "You entered:" << endl;
		OutputInConsole(arr, size);//вывод изначального массива в консоль
		SetColor(white);
		cout << endl << "Do you want to save array you entred into the file?" << endl
			<< "[0] - No" << endl
			<< "[1] - Yes" << endl
			<< "Your choice:";
		choice = GetBool();//запрос от пользователя, хочет ли он сохранить полученный массив в файл
		if (choice) {
			bool orig = true;
			OutputDataInFile(arr, size, orig);
		}
		ArrChange(arr, size);//выполнение задания по изменению массива и вывода сумм
		delete[] arr;
	}
	else {
		SetColor(red);
		cout << "Invalid lines and columns values, try again!" << endl;
		SetColor(white);
		ManualInput();
	}
}