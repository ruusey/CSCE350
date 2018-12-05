/**
 * Author: Robert Usey
 * Copyright Robert Usey 2018
 * CSCE350 Project 04
 */
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;
//DECLARATION OF ALPHABET FOR DECODING
string alpha = "abcdefghijklmnopqrstuvwxyz";
//TEMPLATE FOR PRINTING ANYTHING ITERABLE(Vector<int> etc...)
template<typename T>
void printVector(const T& t) {
	copy(t.cbegin(), t.cend(),ostream_iterator<typename T::value_type>(cout, ","));
}
//RETURNS THE NUMBER OF C
int numCombinations(vector<char> &vec) {
	int perm = 1;
	for (int i = 0; i < vec.size(); ++i) {
		string test = { vec[i], vec[i + 1] };
		int x = (stoi(test));
		if (x >= 10 && x <= 25)
			perm++;
		else if(test.find(vec[i])==string::npos && test.find(vec[i + 1])==string::npos)
			perm++;
	}
	return perm;
}
//PRINT A DECODING FOR A VECTOR OF PERMUTATIONS
void printDecoding(vector<int> &vals) {
	for (int idx = 0; idx < vals.size(); ++idx)
		cout << alpha[vals.at(idx)];
	cout << endl;
}
//PRINT A DECODING FOR A STRING INT(The base input)
void printDecoding(string base) {
	for (int idx = 0; idx < base.size(); ++idx)
		cout << alpha[base[idx]-'0'];
	cout << endl;
}
void printValidCombinations(vector<char> &vec) {
	//PRINT THE NUMBER OF COMBINATIONS
	int combinations = numCombinations(vec);
	cout << combinations << endl;
	if (combinations > 30) return;
	//VECTOR OR PAIRS TO STORE THE INDEXES AT WHICH WE COULD HAVE CONFLICTS
	//IE 2,2,2,3 or 22,2,3
	vector<pair<int, int>> vals;
	//WE WILL ALWAYS HAVE ONE BASE ENCODING CONTAINING THE CHARACTERS READ FROM CIN
	string base(vec.begin(), vec.end());
	//FIND ALL THE LOCATIONS WHERE WE COULD CONCAT TWO INTS TO GET A DIF DECODING
	for (int i = 0; i < vec.size() - 1; ++i) {
		string test = { vec[i], vec[i + 1] };
		int x = (stoi(test));
		if (x >= 10 && x <= 25) {
			vals.push_back(make_pair(i, x));
		}
	}
	vector<int> permutations;
	for (vector<pair<int, int> >::iterator dx = vals.begin(); dx != vals.end();dx++) {

		pair<int, int> result = (*dx);

		for (int idx = 0; idx < vec.size(); ++idx) {
			if (result.first == idx) {
				permutations.push_back(result.second);
				idx++;
			} else {
				permutations.push_back(vec[idx] - '0');
			}
		}
		printDecoding(permutations);
		permutations.clear();

	}
	if (vals.size() >= 2) {
		for (int x = 1; x < vals.size(); x++)
			permutations.push_back(vals[x].second);
	}
	if (combinations > 1) {

		printDecoding(permutations);
	} else {
		printDecoding(base);
	}
}
int main() {
	string s;
	vector<char> input;
	do {
		cin >> s;
		for (int i = 0; i < s.length(); i++) {
			int chr = s[i];
			input.push_back(chr);
		}
		printValidCombinations(input);
	} while (cin);
}
