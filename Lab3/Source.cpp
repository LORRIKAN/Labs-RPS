// ������������ ������ �3.
//������ ���������� ��������.
// ��� �����. ���������� ����������� �� ������, ���������� � ���� 10 ��������� (��������).
// ������� ������ 485, ��������� ������� �������. 2019 ���
// ������� 3
//Source.cpp

#include <iostream>
#include <list>
#include "VarCheckAndColorSet.h" 
#include "HashAndSearch.h"

using namespace std;

enum MenuItems {
	minMenuItem = 0, file, manually, close, maxMenuItem
};


bool Menu() { // ����� ���� � �������� �������� ������

	cout << "Choose option:\n" << "1. Input path to file with text\n" << "2. Input text manually\n" <<
		"3. Exit the program\n" << "Input: ";
	int menuItem; //  ����� ���� ��� ����� �������������
	bool running = true; //  ��� �������� � main, �������� �������� �� ���������
	while (true) { // ���� ������������� �������� ���� � ��� ��������
		menuItem = GetInt(); // ���� �������� ����, �������� �� int
		if (menuItem > minMenuItem && menuItem < maxMenuItem) { // �������� �� ����� �� ������� ����
			break;
		}
		else CoutWithColor(red, "Try again: ");

	}
	if (menuItem != close) {
		bool askedToSaveText = false;
		Search(InputAndHash(menuItem), menuItem, askedToSaveText);
	}
	else
		running = false;
	return running; // ���� running = true - ��������� ������������, ���� false, �� ��������� �����������
}

int main() { // ������ ���������

	CoutWithColor(yellow, "This program takes the text and hashes the blocks containing 10 elements (symbols).\nCreated by Polyushkina Tatyana, group 485\n\n");
	bool running = true; // ��� ����������� ������������ ���������
	while (running)
	{
		running = Menu();
	}


	return 0;
}

