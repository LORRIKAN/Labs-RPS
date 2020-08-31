#include <iostream>
#include <Windows.h>
#include <string>
#include "VarCheckAndColorSet.h"

using namespace std;

template <typename T> // �������� ������� T
T InputCheck() { // �������� ����� ������������  
	T userInput; // �������� ���������� ��������� ���� ��� ������ ����� ������������ 
	cin >> userInput;
	while (cin.fail()) { // ���� ��������� ������ �� ������������� ����
		CoutWithColor(red, "\nTry again: ");
		cin.clear(); // ������� cin.fail()
		cin.ignore(INT_MAX, '\n'); // ������� ������
		cin >> userInput;
	}
	cin.ignore(INT_MAX, '\n');
	return userInput;
}

int GetInt() { // ���� �������������, �������� � ������� �������� int

	return InputCheck<int>();

}

bool GetBool() { // ���� �������������, �������� � ������� �������� bool

	return InputCheck<bool>();
}

void SetColor(const int& color) { // ��������� ����� � �������
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void CoutWithColor(const int& color, const string& message) { // ����� ��������� message � ������ color
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); // ��������� ����� �� color
	cout << message; // ����� ���������
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), white); // ��������� ����� �� �����
}
