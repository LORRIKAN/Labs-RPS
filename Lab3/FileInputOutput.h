#pragma once
#include <string>
#include <list>
#include <vector>
#include "HashAndSearch.h"

using namespace std;

string FilePathCheckReturnForInput();
string FilePathCheckReturnForOutput(const string& message);
void OutputTextInFile(const list<HashedString>& text);
void OutputResultInFile(const vector<int>& matchedBlockNums, const string& searchedMessage);