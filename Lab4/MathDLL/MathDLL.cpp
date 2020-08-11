#include "MathDLL.h"
#include <cmath>
#include <string>

using namespace std;

//функция для вычисления рядной функции
double Зобнин_func(double x, double eps) {
	long double result = x * x;
	size_t n = 1;
	long double cur = result;
	long double tmp;
	do {
		tmp = cur;
		cur *= (-2 * x * x) / ((2 * n + 1)*(n + 1));
		result += cur;
		n++;
	} while (abs(cur - tmp) >= eps);
	return result;
}

// для вызова внутренней функции
double MATHDLL_API myf_485(double x, double y, double eps) {
	if (x > 17 || x < -17)
		return 0;
	return Зобнин_func(x, eps);
}

//вычисление показательной функции
double MATHDLL_API myf_math(double x, double a) {
	return pow(sin(x), a);
}

//возвращает имя функции
char MATHDLL_API *FName() {
	string str = "sin^2(x)";

	char* funcName = new char[str.length()];
	for (int i = 0; i < str.length(); ++i) {
		funcName[i] = str[i];
	}
	funcName[str.length()] = '\0';
	return funcName;
}