#include <iostream>
#include "ArrOutput.h"

using namespace std;

enum { comparesColumn, swapsColumn, bubbleLine = 0, selectLine, insertLine, shellLine, quickLine };
enum { bubbleSort, selectSort, insertSort, shellSort, quickSort };

struct LinkValuesAndSum {
	int value;
	int sum;
	bool listed = false;
};

void BubbleSort(int* line, int m, int& compares, int& swaps) {
	bool lineChanged = true;
	for (int i = 0; i < m && lineChanged; ++i) {
		lineChanged = false;
		for (int j = 0; j < m - i - 1; ++j) {
			++compares;
			if (line[j] > line[j + 1]) {
				int temp = line[j];
				line[j] = line[j + 1];
				line[j + 1] = temp;
				lineChanged = true;
				++swaps;
			}
		}

	}
}

void SelectSort(int* line, int m, int& compares, int& swaps) {
	int min;
	for (int i = 0; i < m - 1; ++i) {
		min = i;
		for (int j = i + 1; j < m; ++j) {
			++compares;
			if (line[j] < line[min])
				min = j;
		}
		if (i != min) {
			int temp = line[i];
			line[i] = line[min];
			line[min] = temp;
			++swaps;
		}
	}

}

void InsertSort(int* line, int m, int& compares, int& swaps) {
	for (int i = 1; i < m; ++i) {
		int x = line[i];
		int j = i;
		while (true) {
			if (j > 0) {
				++compares;
				if (x < line[j - 1]) {
					line[j] = line[j - 1];
					--j;
				}
				else break;
			}
			else break;
		}
		++swaps;
		line[j] = x;
	}
}

void ShellSort(int* line, int m, int& compares, int& swaps) {
	for (int step = m / 2; step > 0; step /= 2) {
		for (int i = step; i < m; ++i) {
				int x = line[i];
				int j = i;
				while (true) {
					if (j >= step) {
						++compares;
						if (x < line[j - step]) {
							line[j] = line[j - step];
							j -= step;
						}
						else break;
					}
					else break;
				}

				++swaps;
				line[j] = x;
			
		}
	}
}

void QuickSort(int* line, int first, int last, int& compares, int& swaps) {
	int left = first;
	int pivot = line[(first + last) / 2];
	int right = last;
	while (left < right) {
		
		while (++compares, line[left] < pivot) {
			++left;	
		}
		while (++compares, line[right] > pivot) {
			--right;
		}
		if (left <= right) {
			int temp = line[left];
			line[left] = line[right];
			line[right] = temp;
			++left;
			--right;
			++swaps;
		}

	} 
	if (first < right) QuickSort(line, first, right, compares,swaps);
	if (left < last) QuickSort(line, left, last, compares, swaps);
}

void ArrCopy(int** origArr, int** copy, int n, int m) {
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
		copy[i][j] = origArr[i][j];
}

void SumCalcAndSort(int* origLine, int* resultLine, int m, int comparesAndSwaps[sortsNumber][parametersNumber], int sortNum) {
	int* sumLine = new int[m];
	LinkValuesAndSum* arrOfLinks = new LinkValuesAndSum[m];
	for (int i = 0; i < m; ++i) {
		int value = abs(origLine[i]);
		int sum = 0;
		while (value) {
			sum += value % 10;
			value /= 10;
		}
		sumLine[i] = sum;
		arrOfLinks[i].sum = sum;
		arrOfLinks[i].value = origLine[i];
	}
	switch (sortNum)
	{

	case bubbleSort: 
		BubbleSort(sumLine, m, comparesAndSwaps[bubbleLine][comparesColumn], comparesAndSwaps[bubbleLine][swapsColumn]);
		break;
	case selectSort:
		SelectSort(sumLine, m, comparesAndSwaps[selectLine][comparesColumn], comparesAndSwaps[selectLine][swapsColumn]);
		break;
	case insertSort:
		InsertSort(sumLine, m, comparesAndSwaps[insertLine][comparesColumn], comparesAndSwaps[insertLine][swapsColumn]);
		break;
	case shellSort:
		ShellSort(sumLine, m, comparesAndSwaps[shellLine][comparesColumn], comparesAndSwaps[shellLine][swapsColumn]);
		break;
	case quickSort:
		int first = 0;
		int last = m - 1;
		QuickSort(sumLine, first, last, comparesAndSwaps[quickLine][comparesColumn], comparesAndSwaps[quickLine][swapsColumn]);
		break;
	}
		
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < m; ++j) {
			if (sumLine[i] == arrOfLinks[j].sum && !arrOfLinks[j].listed) {
				resultLine[i] = arrOfLinks[j].value;
				arrOfLinks[j].listed = true;
				break;
			}
		}
		
	}
	
	delete[] sumLine;
	delete[] arrOfLinks;
}

int** ArrChange(int** origArr, int n, int m, int comparesAndSwaps[sortsNumber][parametersNumber], int lenghtToSetw) {
	for (int i = 0; i < sortsNumber; ++i) {
		for (int j = 0; j < parametersNumber; ++j)
			comparesAndSwaps[i][j] = 0;
	}
	string table[sortsNumber] = { "Bubble sort: ", "Select sort: ", "Insert sort: ", "Shell sort:  ", "Quick sort:  " };
	int** resultArr = new int* [n];
	for (int i = 0; i < n; ++i) {
		resultArr[i] = new int[m];
	}
	for (int sortIterator = 0; sortIterator < sortsNumber; ++sortIterator) {
		ArrCopy(origArr, resultArr, n, m);
		for (int i = 0; i < n; ++i) {
			if ((i + 1) % 2) {
				SumCalcAndSort(origArr[i], resultArr[i], m, comparesAndSwaps, sortIterator);
			}
		}
		OutputInConsoleArr(resultArr, n, m, lenghtToSetw, table[sortIterator] + "\n\n", blue + sortIterator);	
	}
	return resultArr;
}