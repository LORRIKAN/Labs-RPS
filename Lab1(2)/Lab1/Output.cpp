#include "pch.h"
#include "InputAndCheck.h"

using namespace std;
using namespace experimental::filesystem;

void SetColor(int color) {//������� ��� ��������� ����� ������ � �������
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void OutputArrInFile(int *arr, int size, string path) {//������� ��� ������ ���-�� �����, �������� � ������������ �������
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

void OutputResultInFile(int *arr, int size, string path) {//������� ��� ������ ���������� �������, ������� � �������� ����������
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

void OutputInConsole(int *arr, int size) {//������� ��� ������ ������� � �������
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

		if (ifstream(filePath))//�������� �� ������������� �����
			if (!is_regular_file(filePath)) {//�������� �� ����������� ����� (aux, com � �.�.)
				SetColor(red);
				cout << "Incorrect file path. Enter another one!" << endl;
				SetColor(white);
				cin.ignore(INT_MAX, '\n');
				continue;
			}
			else{//����� �� ������������ ������������ ����������
				SetColor(red);
				cout << "File already exists! Do you want to erase all data and write your array in it?" << endl;
				SetColor(white);
				cout << "[0] - No" << endl << "[1] - Yes" << endl << "Your choice:";
				bool isAnother = GetBool();
				if (!isAnother)
					continue;
			}

		ofstream myFile(filePath);

		if (!myFile) {//�������� �� ������ � ��� ������������� �����
			SetColor(red);
			cout << "Access denied! Enter another path!" << endl;
			SetColor(white);
			myFile.close();
			continue;
		}

		myFile.close();
		if (origOrResult)//������ ���� ������������� ������� ���� ����������
			OutputArrInFile(arr, size, filePath);
		else
			OutputResultInFile(arr, size, filePath);

		isDataSaved = true;
	} while (!isDataSaved);
}