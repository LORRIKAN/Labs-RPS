#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <vector>
#include "FileInputOutput.h"
#include "HashAndSearch.h"
#include "VarCheckAndColorSet.h"

using namespace std;

enum {fileInput = 1, manualInput};

const int minBlockSize = 10;

HashedString::HashedString(const string& tenSymbols, const int& tenSymbolsHash) : tenSymbols(tenSymbols), tenSymbolsHash(tenSymbolsHash) {}

int Hash(const char& symbol, const int& pos) {
	return symbol * pos;
}

list<HashedString> InputAndHash(const int& inputWay) {
	list<HashedString> hashedText;
	if (inputWay == fileInput) {
		string path = FilePathCheckReturnForInput();
		ifstream file(path);
		string tenSymbols = "";
		int tenSymbolsHash = 0;
		char symbol;
		int i = 0;
		while (true) {
			if (file >> symbol) {
				tenSymbols += symbol;
				tenSymbolsHash += Hash(symbol, i);
				++i;
				if (i == minBlockSize) {
					hashedText.emplace_back(tenSymbols, tenSymbolsHash);
					tenSymbols = "";
					tenSymbolsHash = 0;
					i = 0;
				}
			}
			else {
				if (i) {
					for (int j = 0; j < minBlockSize - i; ++j) {
						tenSymbols += "0";
					}
					hashedText.emplace_back(tenSymbols, tenSymbolsHash);
				}
				break;
			}
		}
	}
	else
		if (inputWay == manualInput){
			string text;
			string tenSymbols = "";
			int tenSymbolsHash = 0;
			cout << "\nInput text: ";
			getline(cin, text);
			int j = 0;
			for (int i = 0; i < text.size(); ++i) {
				tenSymbols += text[i];
				tenSymbolsHash += Hash(text[i], j);
				++j;
				if (j == minBlockSize) {
					hashedText.emplace_back(tenSymbols, tenSymbolsHash);
					tenSymbols = "";
					tenSymbolsHash = 0;
					j = 0;
				}
			}
			if (j) {
				for (int i = 0; i < minBlockSize - j; ++i) {
					tenSymbols += "0";
				}
				hashedText.emplace_back(tenSymbols, tenSymbolsHash);
			}
		}
	CoutWithColor(purple, "\nBlock");
	CoutWithColor(green, "     \tHash\n");
	for (auto textPart = hashedText.begin(); textPart != hashedText.end(); ++textPart)
		cout << textPart->tenSymbols << '\t' << textPart->tenSymbolsHash << endl;
	cout << endl;
	return hashedText;
}

void Search(const list<HashedString>& hashedText, const int& inputWay, bool& askedToSaveText) {
	string input;
	cout << "Input text you want to find: ";
	getline(cin, input);
	string copyInputToSaveInFile = input;
	int hash = 0;
	for (int i = 0; i < input.size(); ++i) {
		hash += Hash(input[i], i);
	}
	if (input.size() < minBlockSize) {
		int inputSize = input.size();
		for (int i = 0; i < minBlockSize - inputSize; ++i)
			input += "0";
	}
	cout << "\nHash: " << hash << "\n\n";
	vector<int> matchedBlockNums;
	int blockNum = 1;
	for (auto textPart = hashedText.begin(); textPart != hashedText.end(); ++textPart, ++blockNum) {
		if (hash == textPart->tenSymbolsHash && input == textPart->tenSymbols) {
			matchedBlockNums.push_back(blockNum);
			CoutWithColor(green, textPart->tenSymbols);
		}
		else
			cout << textPart->tenSymbols;
	}
	
	if (matchedBlockNums.size()) {
		SetColor(blue);
		cout << "\n\n" << matchedBlockNums.size() << " match(es) found\n";
		SetColor(white);
	}
	else
		CoutWithColor(red, "\n\nNo matches found.\n");
	if (inputWay == manualInput && !askedToSaveText) {
		SetColor(yellow);
		cout << "\nDo you want to save text you searched in? 1 - Yes, 0 - No: ";
		bool saveText = GetBool();
		SetColor(white);
		askedToSaveText = true;
		if (saveText)
			OutputTextInFile(hashedText);
	}
	SetColor(green);
	cout << "\nDo you want to save result of your search? 1 - Yes, 0 - No: ";
	bool saveResult = GetBool();
	SetColor(white);
	if (saveResult)
		OutputResultInFile(matchedBlockNums, copyInputToSaveInFile);
	SetColor(azure);
	cout << "\nDo you want to search another text in this text file? 1 - Yes, 0 - No: ";
	bool anotherSearch = GetBool();
	cout << "\n";
	SetColor(white);
	if (anotherSearch)
		Search(hashedText, inputWay, askedToSaveText);
	
}