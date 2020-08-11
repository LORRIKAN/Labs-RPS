#include <iostream>
#include <cmath>
#include <string>
#include "MenuColorAndCheck.h"
#include "Math.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "rus");
	SetColor(azure);
	cout << "Здравствуйте, эта программа сравнивает значения функции sin^2(x), вычисленной с помощью функций из библиотеки cmath," 
		<< endl << "с суммой соответствующего ряда Маклорена." << endl;
	SetColor(white);
	bool running = true;
	while (running) {
		InputAndCalc();
		running = Menu();
	}
	system("PAUSE");
}