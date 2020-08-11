#ifdef MATHDLL_EXPORTS 
#define MATHDLL_API __declspec(dllexport) 
#else 
#define MATHDLL_API __declspec(dllimport) 
#endif

extern "C" {
	//вычисление рядной функции
	double MATHDLL_API myf_485(double x, double a, double eps);
	//вычисление показательной функции
	double MATHDLL_API myf_math(double x, double a);
	//возвращает имя функции
	char MATHDLL_API *FName();
}