#include "pch.h"
#include "InputAndCheck.h"
#include "Output.h"
#include "ArrChange.h"

using namespace std;
using namespace experimental::filesystem;

const int minSize = 2;

void FileInput() {//���������� ������� �� �����
	string filePath;
	bool isDataLoaded = false;
	int size;
	do {
		cout << "Input path to file, for example: C:\\Directory\\textfile.txt: " << endl;
		cin >> filePath;

		if (!ifstream(filePath)) {//���� ����� �� ����������
			SetColor(red);
			cout << "File does not exist! Input another path!" << endl;
			SetColor(white);
			cin.ignore(INT_MAX, '\n');
			continue;
		}

		if (!is_regular_file(filePath)) {//�������� �� ���������� ����� (������ �� aux, com � �.�.)
			SetColor(red);
			cout << "Incorrect file path. Enter another one!" << endl;
			SetColor(white);
			cin.ignore(INT_MAX, '\n');
			continue;
		}

		ifstream myFile(filePath);

		if (!myFile) {//���� ��� ������� � �����
			SetColor(red);
			cout << "Access denied! Enter another path!" << endl;
			SetColor(white);
			myFile.close();
			continue;
		}
			if (!(myFile >> size) || size < minSize) {//���������� ������� ������� � ��������
				SetColor(red);//�� ���������� �������� ������
				cout << "Incorrect array size!" << endl;
				SetColor(white);
				myFile.close();
				continue;
			}

			int *arr = new int[size*size];//���� ��� �������� �������� �������, �������� ���������� ������

			bool toBreakAndContinue = false;//��� ������ �� ���� ������ � ������ ����� ����������� �������� �
																			//�������� � ������ ���������

			for (int i = 0; i < size * size; i++)//���������� ��������� ������� � �������� �� �� ����������
					if (!(myFile >> arr[i])) {//���� ������� �� int ��������, ����� �� ������ � ������� � ������ ���������
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
				ArrChange(arr, size);//���������� ������� �� ��������� �������
				delete[] arr;
	} while (!isDataLoaded);
}

void RandomFilling() {//��������� ����������
	srand(static_cast <unsigned int> (time(nullptr)));//��� ��������� ��������� ����� ��� ������ �������
	int size;
	bool choice;
	cout << "Enter a size of the array: ";
	size = GetUnsignedInt();//������ ������� �������
	if (size >= minSize) {
		int *arr = new int[size*size];//�������� ��������� ������
		for (int i = 0; i < size*size; i++)//���������� ���������� ����������
			arr[i] = rand() % 1001;
		SetColor(green);
		cout << "You entered:" << endl;
		OutputInConsole(arr, size);//����� ���������� ������� � �������
		SetColor(white);
		cout << endl << "Do you want to save the array you entred into the file?" << endl
			<< "[0] - No" << endl
			<< "[1] - Yes" << endl
			<< "Your choice:";
		choice = GetBool();//������ �� ������������, ����� �� �� ��������� ���������� ������ � ����
		if (choice) {
			bool orig = true;
			OutputDataInFile(arr, size, orig);
		}
		ArrChange(arr, size);//���������� ������� �� ��������� �������
		delete[] arr;
	}
	else {
		SetColor(red);
		cout << "Invalid lines and columns values, try again!" << endl;
		SetColor(white);
		RandomFilling();
	}
}

void ManualInput() {//���� ���� ������ �������
	int size;
	bool choice;
	cout << "Enter a size of the array: ";
	size = GetUnsignedInt();
	if (size >= minSize) {
		int *arr = new int[size*size];//�������� ���������� �������
		cout << "Input it!" << endl;
		for (int i = 0, j = 0, tmp = 0, tmp1 = size; j < size*size; j++, tmp++) {
			if (j == tmp1) {
				tmp1 += size;
				i++;
				tmp = 0;
			}
			cout << "A[" << i + 1 << "]"
					 << "[" << tmp + 1 << "] = ";
			arr[j] = GetInt();//���� �������� �������
		}
		SetColor(green);
		cout << "You entered:" << endl;
		OutputInConsole(arr, size);//����� ������������ ������� � �������
		SetColor(white);
		cout << endl << "Do you want to save array you entred into the file?" << endl
			<< "[0] - No" << endl
			<< "[1] - Yes" << endl
			<< "Your choice:";
		choice = GetBool();//������ �� ������������, ����� �� �� ��������� ���������� ������ � ����
		if (choice) {
			bool orig = true;
			OutputDataInFile(arr, size, orig);
		}
		ArrChange(arr, size);//���������� ������� �� ��������� ������� � ������ ����
		delete[] arr;
	}
	else {
		SetColor(red);
		cout << "Invalid lines and columns values, try again!" << endl;
		SetColor(white);
		ManualInput();
	}
}