#include <Windows.h>
#include <iostream>
#include "MenuColorAndCheck.h"

using namespace std;

void SetColor(const int color) {//������� ��� ��������� ����� ������ � �������
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

bool Menu() {
	cout << "[0] - Exit the program" << endl << "[1] - Keep running the program" << endl << "Your choice: ";
	bool menu = GetBool();
	return menu;
}

template <typename T>
T GetInput() { // �������� ����� ������ �����
	T userInput;
	cin >> userInput;//���� ������������� ����������� ������
	while (cin.fail()) {//���� ���� ���� ������ �� ������������� ��������� ����
		SetColor(red);
		cout << "Try again: " << endl;
		SetColor(white);
		cin.clear();//��������� cin.fail
		cin.ignore(INT_MAX, '\n');//������������� �������� ������
		cin >> userInput;//��������� ���� ����������
	}
	cin.ignore(INT_MAX, '\n');
	return userInput;
}

bool GetBool() {
	return GetInput<bool>();
}

double GetDouble() {
	return GetInput<double>();
}