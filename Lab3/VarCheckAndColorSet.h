#pragma once
#include <string>

using namespace std;

enum Color { blue = 9, green, azure, red, purple, yellow, white };

int GetInt();
bool GetBool();
void CoutWithColor(const int& color, const string& message);
void SetColor(const int& color);