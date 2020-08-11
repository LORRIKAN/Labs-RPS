#ifdef MATHDLL_EXPORTS 
#define MATHDLL_API __declspec(dllexport) 
#else 
#define MATHDLL_API __declspec(dllimport) 
#endif

extern "C" {
	//���������� ������ �������
	double MATHDLL_API myf_485(double x, double a, double eps);
	//���������� ������������� �������
	double MATHDLL_API myf_math(double x, double a);
	//���������� ��� �������
	char MATHDLL_API *FName();
}