extern "C" {
	//���������� ������ �������
	double __declspec(dllexport) myf_485(double x, double a, double eps);
	//���������� ������������� �������
	double __declspec(dllexport) myf_math(double x, double a);
	//���������� ��� �������
	char __declspec(dllexport)* FName();
}