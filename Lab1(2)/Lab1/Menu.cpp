#include "pch.h"
#include "InputAndCheck.h"
#include "ArrFilling.h"
#include "Output.h"

using namespace std;

const int maxMenuNumber = 4, minMenuNumber = 1;

enum { close = 1, fromFile, manually, random };

bool MainMenu() {//�������, ��������� �� ������������ ������� ����� ���������� �������
	bool running = true;
	cout << "How to fill the array: " << endl << "[1] - Exit the program" << endl 
			 << "[2] - From file" << endl << "[3] - Manually" << endl << "[4] - Random" << endl
			 << "Choose: ";
	int menu;
	menu = GetUnsignedInt();
	while (menu > maxMenuNumber || menu < minMenuNumber) {//����������� �� ������������� �������� ����
		SetColor(red);
		cout << "Try again: " << endl;
		SetColor(white);
		menu = GetUnsignedInt();
	}
	switch (menu) {//������� � ��������������� �������
		case fromFile: {
			FileInput();
			running = true;
			break;
		}
		case manually: {
			ManualInput();
			running = true;
			break;
		}
		case random: {
			RandomFilling();
			running = true;
			break;
		}
		case close: {
			running = false;
			break;
		}
	}
		return running;
}