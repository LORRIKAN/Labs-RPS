#pragma once
void InputAndCalc();

typedef double(*Myf_485)(double, double, double); //���������� ������ �������
typedef double(*Myf_math)(double, double);		  //���������� ������� �� math.h
typedef char* (*FName)();						  //������ ����� �������