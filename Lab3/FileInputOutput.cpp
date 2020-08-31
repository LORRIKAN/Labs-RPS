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

string FilePathCheckReturnForInput() { // �������� ���� ��� ������ �� �����
	string filePath;
	bool isPathValid = false;

	while (!isPathValid) { // while isPathValid == false, �������� ���������� ���������� ����
		cout << "\nInput path to file with text, for example C:\\Directory\\text.txt : ";
		cin >> filePath;
		cin.ignore(INT_MAX, '\n');

		if (!ifstream(filePath)) { // ���������� �� ����
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
		if (!file) { //�������� ������� � �����
			CoutWithColor(red, "\nAccess denied!\n");
			continue;
		}

		isPathValid = true;
	}
	return filePath;
}

string FilePathCheckReturnForOutput(const string& message) { // �������� ���� ��� ���������� � ����
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