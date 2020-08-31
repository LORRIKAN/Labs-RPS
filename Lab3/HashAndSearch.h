#pragma once
#include <string>

using namespace std;

struct HashedString {
	const string tenSymbols;
	const int tenSymbolsHash;
	HashedString(const string& tenSymbols, const int& tenSymbolsHash);
};

list<HashedString> InputAndHash(const int& inputWay);
void Search(const list<HashedString>& hashedText, const int& inputWay, bool& askedToSaveText);