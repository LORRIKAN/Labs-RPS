#pragma once
#include "pch.h"
#include "Hash.h"

enum { blue = 9, green, azure, red, purple, yellow, white };

void SetColor(const int color);
string GetFilePath();
int GetUint();
bool GetBool();
void OutputDataInFile(const list <Str> matches);