int** ArrChange(int* triangleArr, int n) { // �������� � ��������� ��������� �������
	int** origArr = new int* [n];// ��������� ������ ��� ������ ��������� �������
	for (int i = 0; i < n; ++i) { // ��������� ������ ��� ������� ��������� �������
		origArr[i] = new int[n];
	}
	int k = 0;
	// ���������� �������� ������� ���������� �� �����������
	for (int i = 0; i < n; ++i) { // �������� �� ������� �������
		for (int j = i; j < n; ++j, ++k) { // �������� �� �������� �������
			// �������������� �������
			origArr[i][j] = triangleArr[k];
			origArr[j][i] = triangleArr[k];
		}
	}
	return origArr; // ������� ������ �������� �������
}