// ������������ ������ �2.
//������ ���������� ��������.
// ����������� ������ �������� ������ ������� �� ����������� ����� �������� ���� ��������� �������.
// ������� ������ 485, ��������� ������� �������. 2019 ���
// ������� 16
//Source.cpp

#include <iostream>
#include <Windows.h>
#include "VarCheck.h" 
#include "ArrOutput.h"
#include "ArrInput.h"

using namespace std;

enum MenuItems {
	minMenuItem = 0, manual, file, random, close, maxMenuItem
};



bool Menu() { // ����� ���� � �������� �������� ������

	cout << "How to fill array: " << endl << "1. Manually" << endl << "2. From file" << endl << "3. Random" << endl <<
		"4. Exit" << endl << "Input: ";
	int menuItem; //  ����� ���� ��� ����� �������������
	bool running = true; //  ��� �������� � main, �������� �������� �� ���������
	while (true) { // ���� ������������� �������� ���� � ��� ��������
		menuItem = GetInt(); // ���� �������� ����, �������� �� int
		if (menuItem > minMenuItem && menuItem < maxMenuItem) { // �������� �� ����� �� ������� ����
			break;
		}
		else CoutWithColor(red, "Try again: ");

	}


	switch (menuItem) // ����������� ������, ���� ��������  ������������� ������ ��������� � ��������, �� ����������� ������������ ��������.
	{
	case manual:
		ManualInput();
		running = true;
		break;
	case file:
		FileInput();
		running = true;
		break;
	case random:
		RandomInput();
		running = true;
		break;
	case close:
		running = false;
		break;
	}

	return running; // ���� running = true - ��������� ������������, ���� false, �� ��������� �����������
}

int main() { // ������ ���������

	CoutWithColor(yellow, "This progtam arranges each uneven line of the matrix in ascending order of the sum of numbers of values.\nCreated by Polyushkina Tatyana, group 485\n\n");
	bool running = true; // ��� ����������� ������������ ���������
	while (running)
	{
		running = Menu();
	}


	return 0;
}