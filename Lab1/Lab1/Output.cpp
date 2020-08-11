#include "pch.h"
#include "InputAndCheck.h"

using namespace std;
using namespace experimental::filesystem;

void SetColor(int color) {//������� ��� ��������� ����� ������ � �������
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void OutputArrInFile(int **arr, int lines, int columns, string path) {//������� ��� ������ ���-�� �����, �������� � ������������ ������� 
	ofstream fileOutput;
	fileOutput.open(path);
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
	SetColor(purple);
	cout << "Saved successfully! " << endl;
	SetColor(white);
}
void OutputResultInFile(int **arr, int lines, int columns, string path, int sourceArrSum, int changedArrSum) {//������� ��� ������ ���������� �������, ���� ��������� ���������� � ���������� ��������
	ofstream fileOutput;
	fileOutput.open(path);
	fileOutput << "Sum of elements of array you entered: " << endl;
	fileOutput << sourceArrSum << endl;
	fileOutput << "Converted Array: ";
	for (int i = 0; i < lines; i++) {
		fileOutput << endl;
		for (int j = 0; j < columns; j++)
			fileOutput << arr[i][j] << " ";
	}
	fileOutput << endl << "Sum of elements of converted array: " << endl;
	fileOutput << changedArrSum << endl;
	fileOutput.close();
	SetColor(purple);
	cout << "Saved successfully! " << endl;
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

void OutputOrigArr(int **arr, int lines, int columns) {//������� ��� �������� ����� � ����� � ������ ������������ �������
	bool choice;
	string path;
	cout << "Input path to file, for example: C:\\Directory\\textfile.txt: ";
	cin >> path;
	cin.ignore(INT_MAX, '\n');
		if (is_regular_file(path)) {//���� ������������ ��� ���� � ��� ���������� �����
			cout << "File already exists! Do you want to erase all data and write your array in it?" << endl << "0)No" << endl << "1)Yes" << endl << "Your choice:";
			choice = GetBool();//������������ ��������, ����� �� �� ������� ��� ������ � ����� � �������� ���� �����, ���� ������� ���� �����
			if (choice)//������ � ��� ��������� ����
				OutputArrInFile(arr, lines, columns, path);
			else//���� ���� ������
				OutputOrigArr(arr, lines, columns);
		}
		else {
			ofstream fileCheck;
			fileCheck.open(path);
			if (is_regular_file(path)) {
				fileCheck.close();
				OutputArrInFile(arr, lines, columns, path);
			}
			else {//���� ������ ����� �� ���������� � �������
				fileCheck.close();
				cout << "Incorrect file path, try again: " << endl;
				OutputOrigArr(arr, lines, columns);//����������� � ��������� �����
			}
		}
}

void OutputResult(int **arr, int lines, int columns, int sourceArrSum, int changedArrSum) {//������� ��� �������� ����� � �����, ������ ���������� �������, ���� ��������� ���������� � ���������� ��������
	string path;
	bool choice;
	cout << "Input path to file, for example: C:\\Directory\\textfile.txt: ";
	cin >> path;
	cin.ignore(INT_MAX, '\n');
	if (is_regular_file(path)) {
			cout << "File already exists! Do you want to erase all data and write your array in it?" << endl << "0)No" << endl << "1)Yes" << endl << "Your choice:";
			choice = GetBool();//������������ ��������, ����� �� �� ������� ��� ������ � ����� � �������� ���� �����, ���� ������� ���� �����
			if (choice)//������ � ��� ��������� ����
				OutputResultInFile(arr, lines, columns, path, sourceArrSum, changedArrSum);
			else//���� ���� ������
				OutputResult(arr, lines, columns, sourceArrSum, changedArrSum);
	}
	else {//���� ������ ����� �� ���������� � �������
		ofstream fileCheck;
		fileCheck.open(path);
		if (is_regular_file(path)) {
			fileCheck.close();
			OutputResultInFile(arr, lines, columns, path, sourceArrSum, changedArrSum);
		}
		else {
			fileCheck.close();
			cout << "Incorrect file path, try again: " << endl;
			OutputResult(arr, lines, columns, sourceArrSum, changedArrSum);
		}
	}
}