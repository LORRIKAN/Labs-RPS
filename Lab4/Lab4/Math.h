#pragma once
void InputAndCalc();

typedef double(*Myf_485)(double, double, double); //вычисление рядной функции
typedef double(*Myf_math)(double, double);		  //вычисление функции из math.h
typedef char* (*FName)();						  //запрос имени функции