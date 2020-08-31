#include <iostream>
#include "ArrOutput.h"

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