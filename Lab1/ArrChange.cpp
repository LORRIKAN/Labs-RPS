int** ArrChange(int* triangleArr, int n) { // создание и заполение исходного массива
	int** origArr = new int* [n];// выделение памяти под строки исходного массива
	for (int i = 0; i < n; ++i) { // выделение памяти под столбцы исходного массива
		origArr[i] = new int[n];
	}
	int k = 0;
	// заполнение исходной матрицы значениями из треугольной
	for (int i = 0; i < n; ++i) { // итерация по строкам массива
		for (int j = i; j < n; ++j, ++k) { // итерация по столбцам массива
			// зеркалирование матрицы
			origArr[i][j] = triangleArr[k];
			origArr[j][i] = triangleArr[k];
		}
	}
	return origArr; // возврат адреса исходной матрицы
}