#include "pch.h"

using namespace std;

template <typename T>//������������� ������� ��� ������������� ������������� ���� ������
T GetInput() {
	T userInput;
	cin >> userInput;//���� ������������� ����������� ������
	while (cin.fail()) {//���� ���� ���� ������ �� ������������� ��������� ����
		cout << "Try again: " << endl;
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
		cout << "Try again: ";
		return GetUnsignedInt();
	}
	else
	return i;
}

bool GetBool(){
	return GetInput<bool>();
}