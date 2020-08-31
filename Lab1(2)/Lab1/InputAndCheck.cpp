#include "pch.h"
#include "Output.h"

enum { blue = 9, green, azure, red, purple, yellow, white };

using namespace std;

template <typename T>//������������� ������� ��� ������������� ������������� ���� ������
T GetInput() {
	T userInput;
	cin >> userInput;//���� ������������� ����������� ������
	while (cin.fail()) {//���� ���� ���� ������ �� ������������� ��������� ����
		SetColor(red);
		cout << "Try again: ";
		SetColor(white);
		cin.clear();//��������� cin.fail
		cin.ignore(INT_MAX, '\n');//������������� �������� ������
		cin >> userInput;//��������� ���� ����������
	}
	cin.ignore(INT_MAX, '\n');
	return userInput;
}
//��� ����������� ������� ���������� ���������� ��� ����� ������������� �������� ����� ������

int GetInt() {
	return GetInput<int>();
}

int GetUnsignedInt() {
	int i = GetInput<int>();
	if (i < 0) {
		SetColor(red);
		cout << "Try again: ";
		SetColor(white);
		return GetUnsignedInt();
	}
	else
	return i;
}

bool GetBool(){
	return GetInput<bool>();
}