extern "C" {
	//вычисление рядной функции
	double __declspec(dllexport) myf_485(double x, double a, double eps);
	//вычисление показательной функции
	double __declspec(dllexport) myf_math(double x, double a);
	//возвращает имя функции
	char __declspec(dllexport)* FName();
}