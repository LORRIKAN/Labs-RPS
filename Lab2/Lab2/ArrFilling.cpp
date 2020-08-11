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
	int lines, columns;
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
			if (!(myFile >> lines) || lines < minSize || !(myFile >> columns) || columns < minSize) {//считывание кол-ва строк и столбцов и проверка
				SetColor(red);//на валидность введённых данных
				cout << "Incorrect array size!" << endl;
				SetColor(white);
				myFile.close();
				continue;
			}
			int **arr = new int*[lines];//если все проверки пройдены успешно, создаётся двумерный массив
			for (int i = 0; i < lines; i++)
				arr[i] = new int[columns];

			int count = 0, i, j;
			bool toBreakAndContinue = false;//для выхода из двух циклов в случае ввода невалидного значения и
																			//перехода в начало программы

			for (i = 0; i < lines; i++)//считывание элементов массива и проверка их на валидность
				if (!toBreakAndContinue)
					for (j = 0; j < columns; j++)
						if (!toBreakAndContinue) {
							if (!(myFile >> arr[i][j])) {//если введено не int значение, выход из циклов и переход в начало программы
								SetColor(red);
								cout << "Invalid value type or not enough elements in file. Edit the file and try again! " << endl;
								SetColor(white);
								myFile.close();
								toBreakAndContinue = true;
								for (i = 0; i < lines; i++)//удаление созданного массива
									delete[] arr[i];
								delete[] arr;
							}
							count++;
						}
						else
							break;
				else
					break;

			if (toBreakAndContinue)
				continue;
			
				SetColor(green);
				cout << "Loaded successfully!" << endl << endl;
				cout << "You entered";
				OutputInConsole(arr, lines, columns);
				SetColor(white);
				isDataLoaded = true;
				myFile.close();
				ArrChange(arr, lines, columns);//выполнение задания по изменению массива
				for (int i = 0; i < lines; i++)
					delete[] arr[i];
				delete[] arr;
	} while (!isDataLoaded);
}

void RandomFilling() {//случайное заполнение
	srand(static_cast <unsigned int> (time(nullptr)));//для генерации случайных чисел при каждом запуске
	int lines, columns;
	bool choice;
	cout << "Enter a number of lines: ";
	lines = GetUnsignedInt();
	cout << "Enter a number of columns: ";
	columns = GetUnsignedInt();//запрос кол-ва строк и стобцов от пользователя
	if (lines >= minSize && columns >= minSize) {
		int **arr = new int*[lines];//создаётся двумерный массив
		for (int i = 0; i < lines; i++)
			arr[i] = new int[columns];
		cout << "Randomizing..." << endl;
		for (int i = 0; i < lines; i++)//заполнение случайными значениями
			for (int j = 0; j < columns; j++)
				arr[i][j] = rand() % 1001;
		SetColor(green);
		cout << "You entered: ";
		OutputInConsole(arr, lines, columns);//вывод созданного массива в консоль
		SetColor(white);
		cout << endl << "Do you want to save the array you entred into the file?" << endl
			<< "0)No" << endl
			<< "1)Yes" << endl
			<< "Your choice:";
		choice = GetBool();//запрос от пользователя, хочет ли он сохранить полученный массив в файл
		if (choice) {
			bool origOrResult = true;
			OutputDataInFile(arr, lines, columns, origOrResult);
		}
		ArrChange(arr, lines, columns);//выполнение задания по изменению массива
		for (int i = 0; i < lines; i++)
			delete[] arr[i];
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
	int lines, columns;
	bool choice;
	cout << "Enter a number of lines: ";
	lines = GetUnsignedInt();
	cout << "Enter a number of columns: ";
	columns = GetUnsignedInt();
	if (lines >= minSize && columns >= minSize) {
		int **arr = new int*[lines];//создание двумерного массива
		for (int i = 0; i < lines; i++)
			arr[i] = new int[columns];
		cout << "Input it!" << endl;
		for (int i = 0; i < lines; i++)
			for (int j = 0; j < columns; j++) {
				cout << "A[" << i + 1 << "]"
					<< "[" << j + 1 << "]=";
				arr[i][j] = GetInt();//ввод значений вручную
			}
		SetColor(green);
		cout << "You entered: ";
		OutputInConsole(arr, lines, columns);//вывод изначального массива в консоль
		SetColor(white);
		cout << endl << "Do you want to save array you entred into the file?" << endl
			<< "0)No" << endl
			<< "1)Yes" << endl
			<< "Your choice:";
		choice = GetBool();//запрос от пользователя, хочет ли он сохранить полученный массив в файл
		if (choice) {
			bool origOrResult = true;
			OutputDataInFile(arr, lines, columns, origOrResult);
		}
		ArrChange(arr, lines, columns);//выполнение задания по изменению массива и вывода сумм
		for (int i = 0; i < lines; i++)
			delete[] arr[i];
		delete[] arr;
	}
	else {
		SetColor(red);
		cout << "Invalid lines and columns values, try again!" << endl;
		SetColor(white);
		ManualInput();
	}
}