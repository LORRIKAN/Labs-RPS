#include "pch.h"
#include "Hash.h"

enum { blue = 9, green, azure, red, purple, yellow, white };

void SetColor(const int color) {//функция для изменения цвета текста в консоли
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int GetUint() { // Проверка ввода целого числа
	int userInput;
	cin >> userInput;//ввод пользователем необходимых данных
	while (cin.fail() || userInput < 0) {//цикл пока ввод данных не соответствует заданному типу
		SetColor(red);
		cout << "Try again: " << endl;
		SetColor(white);
		cin.clear();//обнуление cin.fail
		cin.ignore(INT_MAX, '\n');//игнорирование введённых данных
		cin >> userInput;//повторный ввод переменной
	}
	cin.ignore(INT_MAX, '\n');
	return userInput;
}

bool GetBool() { // Проверка ввода целого числа
	bool userInput;
	cin >> userInput;//ввод пользователем необходимых данных
	while (cin.fail()) {//цикл пока ввод данных не соответствует заданному типу
		SetColor(red);
		cout << "Try again: " << endl;
		SetColor(white);
		cin.clear();//обнуление cin.fail
		cin.ignore(INT_MAX, '\n');//игнорирование введённых данных
		cin >> userInput;//повторный ввод переменной
	}
	cin.ignore(INT_MAX, '\n');
	return userInput;
}

string GetFilePath() {
	setlocale(LC_ALL, "ru");
	string filePath;
	bool isPathValid = false;
	do {
	cout << "Input path to database, for example: C:\\Directory\\textfile.txt: ";
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
		myFile.close();
		isPathValid = true;
	} while (!isPathValid);
	return filePath;
}

void OutputDataInFile(const list <Str> matches) {
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
			else {//хочет ли пользователь перезаписать содержимое
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
		auto it = matches.begin();
		size_t matchCounter = matches.size();
		myFile << "You searched for: " << it->str << endl << "Hash: " << it->hash << endl
			<< "Found: " << endl;
		if (!matchCounter)
			myFile << "No matches found!";
		else {
			for (; it != matches.end(); it++)
				myFile << it->strNumber << ". " << it->str << endl << "Hash: " << it->hash << endl;

			matchCounter == 1 ? myFile << matchCounter << " match found!" << endl : myFile << matchCounter << " matches found!" << endl;
		}
		myFile.close();
		SetColor(green);
		cout << "Saved successfully!" << endl;
		SetColor(white);
		isDataSaved = true;
	} while (!isDataSaved);
}