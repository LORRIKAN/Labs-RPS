#include "pch.h"
#include "InputAndCheck.h"
#include "Output.h"

using namespace std;

void ArrChange(int *arr, int size) {
	int KRow, LRow;
	cout << "Input the K - th row: ";
	KRow = GetUnsignedInt();
	cout << "Input the R - th row: ";
	LRow = GetUnsignedInt();
	while (KRow == LRow || KRow == 0 || LRow == 0 || KRow > size || LRow > size) {
		SetColor(red);
		cout << "Try again!" << endl;
		SetColor(white);
		cout << "Input the K - th row: ";
		KRow = GetUnsignedInt();
		cout << "Input the R - th row: ";
		LRow = GetUnsignedInt();
	}
	KRow -= 1;
	LRow -= 1;
	int tmp = arr[LRow];
	arr[LRow] = arr[KRow];
	arr[KRow] = tmp;
	int biggestRow, lessRow;
	if (LRow > KRow) {
		biggestRow = LRow;
		lessRow = KRow;
	}
	else {
		biggestRow = KRow;
		lessRow = LRow;
	}
	for (int i = biggestRow; i < size*size; i++)
		if (i == lessRow + size) {
			lessRow += size;
			biggestRow += size;
			tmp = arr[lessRow];
			arr[lessRow] = arr[biggestRow];
			arr[biggestRow] = tmp;
		}
	//изменение цветов, вывод изменённого массива и сумм элементов начального и изменённого массивов
	SetColor(yellow);
	cout << endl << "Converted Array:" << endl;
	OutputInConsole(arr, size);
	SetColor(white);
	cout << endl << "Do you want to save the result into the file?" << endl << "[0] - No" << endl << "[1] - Yes" << endl << "Your choice: ";
	bool choice;
	choice = GetBool();//хочет ли пользователь сохранить результат в файл
	bool result = false;
	if (choice)
		OutputDataInFile(arr, size, result);//сохранение в файл
}