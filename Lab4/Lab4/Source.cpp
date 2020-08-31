#include <iostream>
#include "VarCheckAndColorSet.h"
#include "Calculation.h"

using namespace std;

enum MenuItems {
	minMenuItem = 0, keepRunning, close, maxMenuItem
};

bool Menu() { // ����� ���� � �������� �������� ������

	cout << "Choose option:\n" << "1. Start calculations\n" << "2. Exit the program\n" << "Input: ";
	int menuItem; //  ����� ���� ��� ����� �������������
	bool running = true; //  ��� �������� � main, �������� �������� �� ���������
	while (true) { // ���� ������������� �������� ���� � ��� ��������
		menuItem = GetInt(); // ���� �������� ����, �������� �� int
		if (menuItem > minMenuItem && menuItem < maxMenuItem) { // �������� �� ����� �� ������� ����
			break;
		}
		else CoutWithColor(red, "Try again: ");

	}
	if (menuItem == keepRunning) {
		running = Calculation();
	}
	else
		running = false;
		return running; // ���� running = true - ��������� ������������, ���� false, �� ��������� �����������
}

int main() { // ������ ���������

	CoutWithColor(yellow, "This program compares the value of the function x/(1-x)^2 calculated using the cmath library with the sum of the corresponding Maclaurin series.\nCreated by Polyushkina Tatyana, group 485\n\n");
	bool running = true; // ��� ����������� ������������ ���������
	while (running)
	{
		running = Menu();
	}


	return 0;
}