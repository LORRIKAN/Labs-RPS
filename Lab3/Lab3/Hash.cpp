#include "pch.h"
#include "FileCheckAndColorSet.h"

const int MAX_HASH = 999;
const int HASH_LEN = 3;

int Hash(string str) {
	size_t hash = 0;
	if (str.length() % 2)
		str += str[0];
	for (size_t i = 0; i < str.length(); i += 2)
		hash += (str[i] / str[i + 1] + str[i] % str[i + 1]);
	int len = to_string(hash).length();
	if (len > HASH_LEN)
		hash &= MAX_HASH;
	else
		hash ^= MAX_HASH;
	return hash;
}

Str::Str(const size_t strNumber, const string str) : strNumber(strNumber), str(str), hash(Hash(str)) 
{
}

void Search() {
	string path = GetFilePath(), str;
	ifstream file(path);
	multimap<int, Str> strFromDatabase;
	size_t strNumber = 0;
	while (!file.eof()) {
		getline(file, str);
		if (str == "\n" || str == " " || str == "\r")
			continue;
		strNumber++;
		Str strIn(strNumber, str);
		strFromDatabase.emplace(strIn.hash, strIn);
	}
	file.close();
	cin.ignore(INT_MAX, '\n');
	for (auto it :strFromDatabase)
		cout << it.second.strNumber << ". " << it.second.str << endl << "Hash: " << it.first << endl;
	cout << "Input data you want to find: ";
	SetColor(green);
	getline(cin, str);
	SetColor(white);
	int hash = Hash(str);
  cout << "Hash: " << hash << endl;
	SetColor(yellow);
	cout << "Found:" << endl;
	SetColor(white);
	list <Str> hashMatches;
	list <Str> completeMatches;
	auto it = strFromDatabase.find(hash);
	if (it != strFromDatabase.end()) {
		while (it->first == hash) {
			hashMatches.emplace_back(it->second);
			it++;
		}
		for (auto it : hashMatches)
			if (it.str == str) {
				completeMatches.emplace_back(it);
				cout << it.strNumber << ". ";
				SetColor(green);
				cout << str << endl;
				SetColor(white);
				cout << "Hash: " << hash << endl;
			}
	}
	size_t matchCounter = completeMatches.size();
	if (matchCounter) {
		SetColor(yellow);
		matchCounter == 1 ? cout << matchCounter << " match found!" << endl : cout << matchCounter << " matches found!" << endl;
		SetColor(white);
	}
	else {
		SetColor(purple);
		cout << "No matches found!" << endl;
		SetColor(white);
	}
	cout << "Do you want to save the result into the file?" << endl << "[0] - No" << endl << "[1] - Yes" << endl << "Your choice: ";
	bool choice = GetBool();
	if (choice)
		OutputDataInFile(completeMatches);
	strFromDatabase.clear();
	hashMatches.clear();
	completeMatches.clear();
}