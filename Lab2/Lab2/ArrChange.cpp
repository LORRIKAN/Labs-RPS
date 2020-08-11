#include "pch.h"
#include "InputAndCheck.h"
#include "Output.h"

using namespace std;

void ArrCopy(int *arr, int *arrCopy, int columns) {//����������� ������ ������� � ������
	for (int i = 0; i < columns; i++)
			arrCopy[i] = arr[i];
}

void BubbleSort(int *arr, int size, int &compares, int &swaps) {
	for (int j = 0; j < size - 1; j++){
		for (int i = 0; i < size - j - 1; i++) {//������� �������
			compares++;
			if (arr[i] > arr[i + 1]) {//���� i-�� ������� ������ ����������
				swaps++;
				int tmp = arr[i];
				arr[i] = arr[i + 1];//����� �������
				arr[i + 1] = tmp;
			}
		}
	}
}

void SelectingSort(int *arr, int size, int &compares, int &swaps) {
	int i, j, min, tmp;
	for (i = 0; i < size - 1; i++) {
		min = i;//����������� ������� �� ��������� i-��
		for (j = i + 1; j < size; j++) {//���������� ������� ������������ ��������
			compares++;
			if (arr[j] < arr[min])
				min = j;
		}
		++compares;
		if (i != min) {//���� ������ ������ ����������� �������
			swaps++;
			tmp = arr[i];
			arr[i] = arr[min];//����� �������
			arr[min] = tmp;
		}
	}
}

void InsertSort(int *arr, int size, int &compares, int &swaps){
	for (int i = 1; i < size; i++) {
		int j = i;
		while (j) {//���� ��������� ������� ������ �� i-��
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
			while (j >= 0) {//��������� j - �� � j + step ��-��
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
		step /= 2; //������� ���� �� ���
	}
}

void QuickSort(int *arr, int first, int last, int &compares, int &swaps)
{
	int mid;
	int left = first, right = last;
	mid = arr[(left + right) / 2]; //���������� �������� ��������
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
		if (left <= right) //������������ ���������
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

void Methods(int *arr, int size, int *comparesAndSwaps) {//���������� ������ �������� �� ���� ������� ����������
	int *arrCopy = new int[size];//�������� ������ �������
	ArrCopy(arr, arrCopy, size);//����������� ����������� � ������� ������� � ������ ��� ���������
	BubbleSort(arrCopy, size, comparesAndSwaps[0], comparesAndSwaps[1]);//��� �����, ����� ����� ����������� �������
	ArrCopy(arr, arrCopy, size);
	SelectingSort(arrCopy, size, comparesAndSwaps[2], comparesAndSwaps[3]);
	ArrCopy(arr, arrCopy, size);
	InsertSort(arrCopy, size, comparesAndSwaps[4], comparesAndSwaps[5]);
	ArrCopy(arr, arrCopy, size);
	ShellSort(arrCopy, size, comparesAndSwaps[6], comparesAndSwaps[7]);
	int first = 0, last = size - 1;
	QuickSort(arr, first, last, comparesAndSwaps[8], comparesAndSwaps[9]);//��������� �� ����� �������, � ��� ������
	delete[] arrCopy;																											//��� ��� ������������ �������� � ���������
}

void ArrChange(int **arr, int lines, int columns) {//������� ��� �������� ��������� � ���������� ������
	const string name[10] = { "Bubble Sort:", "", "Select Sort:", "", "Insert Sort:", "", "Shell  Sort:", "", "Quick  Sort:" };
	int i, j, a, *comparesAndSwaps = new int[10];//������ ��� �������� ��������� � ������������
	for (i = 0; i < 10; i++)
		comparesAndSwaps[i] = 0;
	for (i = 0; i < lines - 1; i++) {//������ �� ���� ������� ����� ���������
		a = i;
		j = 0;
		while (a < lines && j < columns) {//������� ��������� � ���������
			a++;
			j++;
		}
		int *line = new int[j];//�������� ������ ������� ����������� ���-�� ��������� � ���������
		a = i;
		j = 0;
		while (a < lines && j < columns) {//����������� ��-�� �� ��������� � ����� ������
			line[j] = arr[a][j];
			a++;
			j++;
		}
		Methods(line, j, comparesAndSwaps);//�������� ������ ������� � ��-�� ��������� �� ��� ������ ����������
		a = i;
		j = 0;
		while (a < lines && j < columns) {//��������� ��������� ������� ��-�� ��������� �� ����������
			arr[a][j] = line[j];
			a++;
			j++;
		}
		delete[] line;
	}
	for (i = 1; i < columns - 1; i++) {//������ �� ���� �������� ����� 1-�� ����������
		a = i;
		j = 0;
		while (j < lines && a < columns) {//������� ��������� � ���������
			a++;
			j++;
		}
		int *line = new int[j];//�������� ������ ������� ����������� ���-�� ��������� � ���������
		a = i;
		j = 0;
		while (j < lines && a < columns) {//����������� ��-�� �� ��������� � ����� ������
			line[j] = arr[j][a];
			a++;
			j++;
		}
		Methods(line, j, comparesAndSwaps);//�������� ������ ������� � ��-�� ��������� �� ��� ������ ����������
		a = i;
		j = 0;
		while (j < lines && a < columns) {//��������� ��������� ������� ��-�� ��������� �� ����������
			arr[j][a] = line[j];
			a++;
			j++;
		}
		delete[] line;
	}
	cout << endl << "Name:\t     " << "Compares:  " << "Swaps:" << endl;
	for (i = 0; i < 10; i += 2)//����� ������� � �������� � �� ���-��� ��������� � ������������
		cout << name[i] << setw(6) << comparesAndSwaps[i] << setw(10) << comparesAndSwaps[i + 1] << endl;
	SetColor(purple);
	cout << "Converted array:";
	OutputInConsole(arr, lines, columns);//����� ����������� ������� � �������
	SetColor(white);
	cout << endl << "Do you want to save the result into the file?" << endl
		<< "0)No" << endl
		<< "1)Yes" << endl
		<< "Your choice:";
	bool choice = GetBool();//����� �� ������������ ��������� ���������� ��������� � ����
	if (choice) {
		bool origOrResult = false;
		OutputDataInFile(arr, lines, columns, origOrResult, comparesAndSwaps);
	}
}