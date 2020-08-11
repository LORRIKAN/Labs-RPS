#pragma once
#include "pch.h"

void Search();

struct Str
{
 	const string str;
	const size_t strNumber;
	int hash;
	Str(const size_t strNumber, const string str);
};