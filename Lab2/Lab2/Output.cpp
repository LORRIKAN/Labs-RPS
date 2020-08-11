#include "pch.h"
#include "InputAndCheck.h"

using namespace std;
using namespace experimental::filesystem;

void SetColor(int color) {//������� ��� ��������� ����� ������ � �������
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void OutputArrInFile(int **arr, int lines, int columns, string path) {//������� ��� ������ ���-�� �����, �������� � ������������ ������� 
	ofstream fileOutput;
	fileOutput.open(path, ofstream::trunc);
	fileOutput << lines << endl;
	fileOutput << columns;
	for (int i = 0; i < lines; i++) {
		fileOutput << endl;
		for (int j = 0; j < columns; j++) {
			if (j == columns - 1)
				fileOutput << arr[i][j];
			else
				fileOutput << arr[i][j] << " ";
		}
	}
	fileOutput.close();
	SetColor(green);
	cout << "Saved successfully! " << endl;
	SetColor(white);
}

void OutputResultInFile(int **arr, int lines, int columns, string path, int *comparesAndSwaps) {//������� ��� ������ ���������� �������, ������� � �������� ����������
	ofstream fileOutput;
	string name[10] = { "Bubble Sort:", "", "Select Sort:", "", "Insert Sort:", "", "Shell  Sort:", "", "Quick  Sort:" };
	fileOutput.open(path, ofstream::trunc);
	fileOutput << "Name:\t     " << "Compares:  " << "Swaps:" << endl;
	for (int i = 0; i < 10; i += 2)
		fileOutput << name[i] << setw(6) << comparesAndSwaps[i] << setw(10) << comparesAndSwaps[i + 1] << endl;
	fileOutput << "Converted Array: ";
	for (int i = 0; i < lines; i++) {
		fileOutput << endl;
		for (int j = 0; j < columns; j++)
			fileOutput << arr[i][j] << " ";
	}
	fileOutput.close();
	SetColor(purple);
	cout << "Saved successfully! " << "\n\n";
	SetColor(white);
}

void OutputInConsole(int **arr, int lines, int columns) {//������� ��� ������ ������� � �������
	for (int i = 0; i < lines; i++) {
		cout << endl;
		for (int j = 0; j < columns; j++) {
			cout << "\t" << arr[i][j] << " ";
		}
	}
}

void OutputDataInFile(int **arr, int lines, int columns, bool origOrResult, int *comparesAndSwaps = 0) {
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
				cout << "0)No" << endl << "1)Yes" << endl << "Your choice:";
				bool isAnother = GetBool();
				if (!isAnother)
					continue;
			}

		ofstream myFile(filePath, ofstream::app);

		if (!myFile) {//�������� �� ������ � ��� ������������� �����
			SetColor(red);
			cout << "Access denied! Enter another path!" << endl;
			SetColor(white);
			myFile.close();
			continue;
		}

		myFile.close();
		if (origOrResult)//������ ���� ������������� ������� ���� ����������
			OutputArrInFile(arr, lines, columns, filePath);
		else
			OutputResultInFile(arr, lines, columns, filePath, comparesAndSwaps);

		isDataSaved = true;
	} while (!isDataSaved);
}