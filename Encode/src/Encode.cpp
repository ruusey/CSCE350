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
#include <list>
#include <cassert>
using namespace std;
//DECLARATION OF ALPHABET FOR DECODING
string alpha = "abcdefghijklmnopqrstuvwxyz";
//TEMPLATE FOR PRINTING ANYTHING ITERABLE(Vector<int> etc...)
template<typename T>
void printVector(const T& t) {
	copy(t.cbegin(), t.cend(),
			ostream_iterator<typename T::value_type>(cout, ","));
}
//RETURNS THE NUMBER OF POSSIBLE DECODINGS
int numDecodings(string str) {
	if (str[0] == '0')
		return 0;
	int n = str.size();
	//INT ARRAY TO KEEP TRACK OF OUR PERMUTATIONS
	int permutations[n + 1];
	permutations[0] = 1;
	permutations[1] = 1;
	for (int i = 2; i <= n; i++) {
		//FIND OUT IF WE CAN MAKE A DOUBLE DIGIT COMBO
		int var = (str[i - 2] - '0') * 10 + (str[i - 1] - '0');
		if (str[i - 1] == '0') {
			if (var == 10 || var == 20)
				permutations[i] = permutations[i - 2];
			else
				return 1;
		} else {
			//IF TOO LARGE ASSIGN THE PREVIOUS PERMUTATIONS
			if (var > 25)
				permutations[i] = permutations[i - 1];
			//IF WITHIN SINGLE DIGIT RANGE ASSIGN PREVIOUS PERMUTATION
			else if (var >= 0 && var <= 9)
				permutations[i] = permutations[i - 1];
			else
				permutations[i] = permutations[i - 1] + permutations[i - 2];
		}
	}
	return permutations[n];
}

//PRINT A DECODING FOR A VECTOR OF PERMUTATIONS
void printDecoding(vector<int> &vals) {
	for (unsigned int idx = 0; idx < vals.size(); ++idx)
		cout << alpha[vals.at(idx)];
	cout << endl;
}
//PRINT A DECODING FOR A STRING INT(The base input)
void printDecoding(string base) {
	for (unsigned int idx = 0; idx < base.size(); ++idx)
		cout << alpha[base[idx] - '0'];
	cout << endl;
}
void printValidCombinations(vector<char> &vec) {
	//PRINT THE NUMBER OF COMBINATIONS
	string base(vec.begin(), vec.end());
	int combinations = numDecodings(base);
	cout << combinations << endl;
	if (combinations > 30)
		return;
	//VECTOR OR PAIRS TO STORE THE INDEXES AT WHICH WE COULD HAVE CONFLICTS
	//IE 2,2,2,3 or 22,2,3
	vector<pair<int, int>> vals;
	//WE WILL ALWAYS HAVE ONE BASE ENCODING CONTAINING THE CHARACTERS READ FROM CIN

	printDecoding(base);
	//FIND ALL THE LOCATIONS WHERE WE COULD CONCAT TWO INTS TO GET A DIF DECODING
	for (unsigned int i = 0; i < vec.size() - 1; ++i) {
		string test = { vec[i], vec[i + 1] };
		int x = (stoi(test));
		if (x >= 10 && x <= 25) {
			vals.push_back(make_pair(i, x));
		}
	}
	vector<int> permutations;
	for (vector<pair<int, int> >::iterator dx = vals.begin(); dx != vals.end();
			dx++) {
		pair<int, int> result = (*dx);
		for (unsigned int idx = 0; idx < vec.size(); ++idx) {
			if ((unsigned int)result.first == idx) {
				permutations.push_back(result.second);
				idx++;
			} else {
				permutations.push_back(vec[idx] - '0');
			}
		}
		printDecoding(permutations);
		permutations.clear();

	}
	//IF THERE IS AN EDGE CASE WHERE WE HAVE TWO OR MORE2 DIGIT COMBOS
	if (vals.size() == combinations - 1)
		return;
	//MAKE SURE WE DONT HAVE ANY DUPLICATES
	vector<int> visited;
	for (unsigned int i = 0; i < vals.size(); i++) {
		visited.push_back(vals[i].second);
	}
	//ERASE THE DUPS
	visited.erase(unique(visited.begin(), visited.end()), visited.end());
	for (unsigned int i = 0; i < visited.size(); i++) {
		permutations.push_back(visited[i]);
	}
	printDecoding(permutations);

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
		cin.ignore();
	} while (cin);
}
