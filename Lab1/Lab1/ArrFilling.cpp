#include "pch.h"
#include "InputAndCheck.h"
#include "Output.h"
#include "ArrChange.h"

using namespace std;
using namespace experimental::filesystem;

void FileInput() {//��������� �������� �� �����
	int lines, columns, i, j;
	string path;
	cout << "Input path to file, for example: C:\\Directory\\textfile.txt: ";
	cin >> path;
	cin.ignore(INT_MAX, '\n');
	ifstream fileArr;
	fileArr.open(path);
	if (!is_regular_file(path)) {
		cout << "Incorrect file path, try again: " << endl;
		fileArr.close();
		FileInput();
	}
	else {
		int count = -2, check;
		while (!fileArr.eof()) {
			fileArr >> check;
			count++;
			if (fileArr.fail()) {
				fileArr.close();
				cout << "Invalid value type or there is an extra space in the end of the file. Edit the file and try again!" << endl;
				FileInput();
				break;
			}
		}
		fileArr.close();
		fileArr.open(path);
		fileArr >> lines;
		fileArr >> columns;//���� ���-�� ����� � ��������, ��� ������ ��� �������� � �����
		if ((lines + columns) < 2) {
			cout << "Lines and columns values must be more than 1. Edit the file and try again!" << endl;
			fileArr.close();
			FileInput();
		}
		else{
			if (!(count == lines * columns)) {
				cout << "Not enough elements in file, edit the file and try again!" << endl;
				fileArr.close();
				FileInput();
			}
			else {
				int **arr = new int*[lines];
				for (i = 0; i < lines; i++)
					arr[i] = new int[columns];//�������� ������������� �������
				for (i = 0; i < lines; i++)
					for (j = 0; j < columns; j++)
						fileArr >> arr[i][j];//��������� �������� �� ����� � ������
				SetColor(green);
				cout << "You entered: ";
				OutputInConsole(arr, lines, columns);//����� ������������ ������� � �������
				SetColor(white);
				ArrChange(arr, lines, columns);//���������� ������� �� ��������� ������� � ������ ����
			}
		}
	}
}

void RandomFilling() {//��������� ����������
	srand(static_cast <unsigned int> (time(nullptr)));//��� ��������� ��������� ����� ��� ������ �������
	int lines = 0, columns = 0;
	bool choice;
	cout << "Enter a number of lines: ";
	lines = GetUnsignedInt();
	cout << "Enter a number of columns: ";
	columns = GetUnsignedInt();//������ ���-�� ����� � ������� �� ������������
	if ((lines + columns) > 2) {
		int **arr = new int*[lines];
		for (int i = 0; i < lines; i++)
			arr[i] = new int[columns];
		cout << "Randomizing..." << endl;
		for (int i = 0; i < lines; i++)
			for (int j = 0; j < columns; j++)
				arr[i][j] = rand() % 1001;
		SetColor(green);
		cout << "You entered: ";
		OutputInConsole(arr, lines, columns);//����� ������������ ������� � �������
		SetColor(white);
		cout << endl << "Do you want to save the array you entred into the file?" << endl
			<< "0)No" << endl
			<< "1)Yes" << endl
			<< "Your choice:";
		choice = GetBool();//������ �� ������������, ����� �� �� ��������� ���������� ������ � ����
		if (choice)
			OutputOrigArr(arr, lines, columns);
		ArrChange(arr, lines, columns);//���������� ������� �� ��������� ������� � ������ ����
	}
	else {
		cout << "Invalid lines and columns values, try again!" << endl;
		RandomFilling();
	}
}

void ManualInput() {//���� ���� ������ �������
	int lines, columns;
	bool choice;
	cout << "Enter a number of lines: ";
	lines = GetUnsignedInt();
	cout << "Enter a number of columns: ";
	columns = GetUnsignedInt();
	if ((lines + columns) > 2) {
		int **arr = new int*[lines];
		for (int i = 0; i < lines; i++)
			arr[i] = new int[columns];
		cout << "Input it!" << endl;
		for (int i = 0; i < lines; i++)
			for (int j = 0; j < columns; j++) {
				cout << "A[" << i + 1 << "]"
					<< "[" << j + 1 << "]=";
				arr[i][j] = GetInt();//���� �������� �������
			}
		SetColor(green);
		cout << "You entered: ";
		OutputInConsole(arr, lines, columns);//����� ������������ ������� � �������
		SetColor(white);
		cout << endl << "Do you want to save array you entred into the file?" << endl
			<< "0)No" << endl
			<< "1)Yes" << endl
			<< "Your choice:";
		choice = GetBool();//������ �� ������������, ����� �� �� ��������� ���������� ������ � ����
		if (choice)
			OutputOrigArr(arr, lines, columns);
		ArrChange(arr, lines, columns);//���������� ������� �� ��������� ������� � ������ ����
	}
	else {
		cout << "Invalid lines and columns values, try again!" << endl;
		ManualInput();
	}
}