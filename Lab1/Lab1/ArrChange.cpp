#include "pch.h"
#include "InputAndCheck.h"
#include "Output.h"

using namespace std;

void ArrChange(int **arr, int lines, int columns) {
	int sourceArrSum = 0, changedArrSum = 0, i, j;
	for (i = 0; i < lines; i++)
		for (j = 0; j < columns; j++) {
			sourceArrSum += arr[i][j];//подсчёт суммы эелементов изначального массива
			if (i == lines - 1 && j == columns - 1) {//проверка на последний элемент массива
				changedArrSum += arr[i][j];
				break;//остановка цикла, не изменение последнего элемента массива
			}
			if (j == columns - 1)//если последний столбец - вычитание первого элемента следующей строки
				arr[i][j] -= arr[i + 1][0];
			else
				arr[i][j] -= arr[i][j + 1];
			changedArrSum += arr[i][j];
		}
	//изменение цветов, вывод изменённого массива и сумм элементов начального и изменённого массивов
	SetColor(green);
	cout << endl << "Sum of elements of array you entered: " << sourceArrSum;
	SetColor(yellow);
	cout << endl << endl << "Converted Array: ";
	OutputInConsole(arr, lines, columns);
	cout << endl << "Sum of elements of converted array: " << changedArrSum;
	SetColor(white);
	cout << endl << "Do you want to save the result into the file?" << endl << "0)No" << endl << "1)Yes" << endl << "Your choice: ";
	bool choice;
	choice = GetBool();//хочет ли пользователь сохранить результат в файл
	if (choice)
		OutputResult(arr, lines, columns, sourceArrSum, changedArrSum);//сохранение в файл
	//полная очистка массива и его указателя
	for (i = 0; i < lines; i++) {
		delete[] arr[i];
		arr[i] = nullptr;
	}
	delete[] arr;
	arr = nullptr;
}