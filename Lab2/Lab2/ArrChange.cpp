#include "pch.h"
#include "InputAndCheck.h"
#include "Output.h"

using namespace std;

void ArrCopy(int *arr, int *arrCopy, int columns) {//копирование одного массива в другой
	for (int i = 0; i < columns; i++)
			arrCopy[i] = arr[i];
}

void BubbleSort(int *arr, int size, int &compares, int &swaps) {
	for (int j = 0; j < size - 1; j++){
		for (int i = 0; i < size - j - 1; i++) {//перебор массива
			compares++;
			if (arr[i] > arr[i + 1]) {//если i-ый элемент больше следующего
				swaps++;
				int tmp = arr[i];
				arr[i] = arr[i + 1];//обмен местами
				arr[i + 1] = tmp;
			}
		}
	}
}

void SelectingSort(int *arr, int size, int &compares, int &swaps) {
	int i, j, min, tmp;
	for (i = 0; i < size - 1; i++) {
		min = i;//минимальный элемент по умолчанию i-ый
		for (j = i + 1; j < size; j++) {//нахождение индекса минимального элемента
			compares++;
			if (arr[j] < arr[min])
				min = j;
		}
		++compares;
		if (i != min) {//если найден другой минимальный элемент
			swaps++;
			tmp = arr[i];
			arr[i] = arr[min];//обмен местами
			arr[min] = tmp;
		}
	}
}

void InsertSort(int *arr, int size, int &compares, int &swaps){
	for (int i = 1; i < size; i++) {
		int j = i;
		while (j) {//пока находится элемент больше до i-го
			compares++;
			if (arr[j - 1] > arr[j]) {
				swaps++;
				int tmp = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = tmp;
			}
			else
				break;
			j--;
		}
	}
}

void ShellSort(int *arr, int size, int &compares, int &swaps) {
	int step = size / 2;
	while (step) {
		for (int i = 0; i < size - step; i++) {
			int j = i;
			while (j >= 0) {//сравнение j - го и j + step эл-та
				compares++;
				if (arr[j] > arr[j + step]) {
					swaps++;
					int tmp = arr[j];
					arr[j] = arr[j + step];
					arr[j + step] = tmp;
				}
				else
					break;
				j--;
			}
		}
		step /= 2; //деление шага на два
	}
}

void QuickSort(int *arr, int first, int last, int &compares, int &swaps)
{
	int mid;
	int left = first, right = last;
	mid = arr[(left + right) / 2]; //вычисление опорного элемента
	do
	{
		compares += 2;
		while (arr[left] < mid) {
			compares++;
			left++;
		}
		while (arr[right] > mid) {
			compares++;
			right--;
		}
		if (left <= right) //перестановка элементов
		{
			swaps++;
			int tmp = arr[left];
			arr[left] = arr[right];
			arr[right] = tmp;
			left++;
			right--;
		}
	} while (left < right);
	if (first < right) QuickSort(arr, first, right, compares, swaps);
	if (left < last) QuickSort(arr, left, last, compares, swaps);
}

void Methods(int *arr, int size, int *comparesAndSwaps) {//одномерный массив проходит по всем методам сортировки
	int *arrCopy = new int[size];//создание нового массива
	ArrCopy(arr, arrCopy, size);//копирование переданного в функцию массива в только что созданный
	BubbleSort(arrCopy, size, comparesAndSwaps[0], comparesAndSwaps[1]);//сам метод, после снова копирование массива
	ArrCopy(arr, arrCopy, size);
	SelectingSort(arrCopy, size, comparesAndSwaps[2], comparesAndSwaps[3]);
	ArrCopy(arr, arrCopy, size);
	InsertSort(arrCopy, size, comparesAndSwaps[4], comparesAndSwaps[5]);
	ArrCopy(arr, arrCopy, size);
	ShellSort(arrCopy, size, comparesAndSwaps[6], comparesAndSwaps[7]);
	int first = 0, last = size - 1;
	QuickSort(arr, first, last, comparesAndSwaps[8], comparesAndSwaps[9]);//передаётся не копия массива, а сам массив
	delete[] arrCopy;																											//для его последующего внесения в диагональ
}

void ArrChange(int **arr, int lines, int columns) {//функция для перевода диагонали в одномерный массив
	const string name[10] = { "Bubble Sort:", "", "Select Sort:", "", "Insert Sort:", "", "Shell  Sort:", "", "Quick  Sort:" };
	int i, j, a, *comparesAndSwaps = new int[10];//массив для подсчёта сравнений и перестановок
	for (i = 0; i < 10; i++)
		comparesAndSwaps[i] = 0;
	for (i = 0; i < lines - 1; i++) {//проход по всем строкам кроме последней
		a = i;
		j = 0;
		while (a < lines && j < columns) {//подсчёт элементов в диагонали
			a++;
			j++;
		}
		int *line = new int[j];//создание нового массива размерности кол-ва элементов в диагонали
		a = i;
		j = 0;
		while (a < lines && j < columns) {//копирование эл-ов из диагонали в новый массив
			line[j] = arr[a][j];
			a++;
			j++;
		}
		Methods(line, j, comparesAndSwaps);//передача нового массива с эл-ми диагонали во все методы сортировки
		a = i;
		j = 0;
		while (a < lines && j < columns) {//замещение исходного порядка эл-ов диагонали на полученный
			arr[a][j] = line[j];
			a++;
			j++;
		}
		delete[] line;
	}
	for (i = 1; i < columns - 1; i++) {//проход по всем столбцам кроме 1-го последнего
		a = i;
		j = 0;
		while (j < lines && a < columns) {//подсчёт элементов в диагонали
			a++;
			j++;
		}
		int *line = new int[j];//создание нового массива размерности кол-ва элементов в диагонали
		a = i;
		j = 0;
		while (j < lines && a < columns) {//копирование эл-ов из диагонали в новый массив
			line[j] = arr[j][a];
			a++;
			j++;
		}
		Methods(line, j, comparesAndSwaps);//передача нового массива с эл-ми диагонали во все методы сортировки
		a = i;
		j = 0;
		while (j < lines && a < columns) {//замещение исходного порядка эл-ов диагонали на полученный
			arr[j][a] = line[j];
			a++;
			j++;
		}
		delete[] line;
	}
	cout << endl << "Name:\t     " << "Compares:  " << "Swaps:" << endl;
	for (i = 0; i < 10; i += 2)//вывод таблицы с методами и их кол-вом сравнений и перестановок
		cout << name[i] << setw(6) << comparesAndSwaps[i] << setw(10) << comparesAndSwaps[i + 1] << endl;
	SetColor(purple);
	cout << "Converted array:";
	OutputInConsole(arr, lines, columns);//вывод полученного массива в консоль
	SetColor(white);
	cout << endl << "Do you want to save the result into the file?" << endl
		<< "0)No" << endl
		<< "1)Yes" << endl
		<< "Your choice:";
	bool choice = GetBool();//хочет ли пользователь сохранить полученный результат в файл
	if (choice) {
		bool origOrResult = false;
		OutputDataInFile(arr, lines, columns, origOrResult, comparesAndSwaps);
	}
}