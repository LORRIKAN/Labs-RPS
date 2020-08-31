#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <list>
#include <vector>
#include "FileInputOutput.h"
#include "VarCheckAndColorSet.h"
#include "HashAndSearch.h"

using namespace std;
using namespace std::filesystem;

string FilePathCheckReturnForInput() { // проверка пути для чтения из файла
	string filePath;
	bool isPathValid = false;

	while (!isPathValid) { // while isPathValid == false, проверка валидности введенного пути
		cout << "\nInput path to file with text, for example C:\\Directory\\text.txt : ";
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

string FilePathCheckReturnForOutput(const string& message) { // проверка пути для сохранения в файл
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

void OutputTextInFile(const list<HashedString>& text) {
	string path = FilePathCheckReturnForOutput("Input path to file to save text: ");
	ofstream output(path);
	for (auto textPart = text.begin(); textPart != text.end(); ++textPart) {
		output << textPart->tenSymbols;
	}
	output.close();
}

void OutputResultInFile(const vector<int>& matchedBlockNums, const string& searchedMessage) {
	string path = FilePathCheckReturnForOutput("Input path to file to save result: ");
	ofstream output(path);
	output << "You searched for: " << searchedMessage;
	if (matchedBlockNums.size()) {
		output << "\n\n" << matchedBlockNums.size() << " match(es) found.\n\nBlock(s) number(s):";
		for (int i = 0; i < matchedBlockNums.size(); ++i) {
			output << " " << matchedBlockNums[i];
		}
	}
	else
		output << "\n\nNo matches found.";
	output.close();
}