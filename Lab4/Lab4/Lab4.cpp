#include <iostream>
#include <cmath>
#include <string>
#include "MenuColorAndCheck.h"
#include "Math.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "rus");
	SetColor(azure);
	cout << "������������, ��� ��������� ���������� �������� ������� sin^2(x), ����������� � ������� ������� �� ���������� cmath," 
		<< endl << "� ������ ���������������� ���� ���������." << endl;
	SetColor(white);
	bool running = true;
	while (running) {
		InputAndCalc();
		running = Menu();
	}
	system("PAUSE");
}