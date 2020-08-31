#include "pch.h"
#include "InputAndCheck.h"

using namespace std;
using namespace experimental::filesystem;

void SetColor(int color) {//функция для изменения цвета текста в консоли
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void OutputArrInFile(int *arr, int size, string path) {//функция для вывода кол-ва строк, столбцов и изначального массива
	ofstream fileOutput(path);
	fileOutput << size << endl;
	for (int i = 0, tmp = size; i < size * size; i++) {
		if (i == tmp) {
			fileOutput << endl;
			tmp += size;
		}
		fileOutput << arr[i] << "\t";
	}
	fileOutput.close();
	SetColor(green);
	cout << "Saved successfully! " << endl;
	SetColor(white);
}

void OutputResultInFile(int *arr, int size, string path) {//функция для вывода изменённого массива, таблицы с методами сортировки
	ofstream fileOutput(path);
	fileOutput << "Converted Array: " << endl << "Size: " << size;
	for (int i = 0, tmp = size; i < size * size; i++) {
		if (i == tmp) {
			fileOutput << endl;
			tmp += size;
		}
		fileOutput << arr[i] << "\t";
	}
	fileOutput.close();
	SetColor(purple);
	cout << "Saved successfully! " << "\n\n";
	SetColor(white);
}

void OutputInConsole(int *arr, int size) {//функция для вывода массива в консоль
	for (int i = 0, tmp = size; i < size * size; i++) {
		if (i == tmp) {
			cout << endl;
			tmp += size;
		}
		cout << arr[i] << "\t";
	}
}

void OutputDataInFile(int *arr, int size, bool origOrResult) {
	string filePath;
	bool isDataSaved = false;
	do {
		cout << "Input path to file, for example: C:\\Directory\\textfile.txt: " << endl;
		cin >> filePath;

		if (ifstream(filePath))//проверка на существование файла
			if (!is_regular_file(filePath)) {//проверка на запрещённые имена (aux, com и т.д.)
				SetColor(red);
				cout << "Incorrect file path. Enter another one!" << endl;
				SetColor(white);
				cin.ignore(INT_MAX, '\n');
				continue;
			}
			else{//хочет ли пользователь перезаписать содержимое
				SetColor(red);
				cout << "File already exists! Do you want to erase all data and write your array in it?" << endl;
				SetColor(white);
				cout << "[0] - No" << endl << "[1] - Yes" << endl << "Your choice:";
				bool isAnother = GetBool();
				if (!isAnother)
					continue;
			}

		ofstream myFile(filePath);

		if (!myFile) {//проверка на доступ к уже существующему файлу
			SetColor(red);
			cout << "Access denied! Enter another path!" << endl;
			SetColor(white);
			myFile.close();
			continue;
		}

		myFile.close();
		if (origOrResult)//запись либо оригинального массива либо результата
			OutputArrInFile(arr, size, filePath);
		else
			OutputResultInFile(arr, size, filePath);

		isDataSaved = true;
	} while (!isDataSaved);
}