#include "dllmain.h"
#include <cmath>
#include <string>

using namespace std;

//функция для вычисления рядной функции
double Полюшкина_func(double x, double eps) {
	long double result = x;
	int k = 1;
	long double cur = result;
	long double tmp;
	do {
		tmp = cur;
		cur *= (x * k + x) / k;
		result += cur;
		++k;
	} while (abs(cur - tmp) >= eps);
	return result;
}

// для вызова внутренней функции
double __declspec(dllexport) myf_485(double x, double a, double eps) {
	return Полюшкина_func(x, eps);
}

//вычисление показательной функции
double __declspec(dllexport) myf_math(double x, double a) {
	return x / pow(1 - x, 2);
}

//возвращает имя функции
char __declspec(dllexport)* FName() {
	char tmp[] = "x/(1-x)^2\0";
	char* funcName = new char[11];
	for (int i = 0; i < 11; ++i)
		funcName[i] = tmp[i];
	return funcName;
}