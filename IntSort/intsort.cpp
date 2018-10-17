//============================================================================
// Name        : Sort3.cpp
// Author      : Robert Usey
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================
#include <vector>
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
using namespace std;
long comparisons = 0;

const vector<string> methods = { "selection", "qsort", "stl" };

void print(vector<int> ints) {
	for (auto i : ints) {
		cout << i << endl;
	}
	cout << "Comparisons: " << comparisons << endl;
}
int qsortCompare(const void *a, const void *b) {
	comparisons++;
	if (*(int*) a < *(int*) b)
		return -1;
	if (*(int*) a == *(int*) b)
		return 0;
	return 1;
}
bool stlSortCompare(int i, int j) {
	comparisons++;
	return i < j;
}
void selection_sort(vector<int> &ints) {
	int vecsize = ints.size();
	for (int j = 0; j < vecsize - 1; ++j) {
		int min = j;
		for (int i = j + 1; i < vecsize; ++i) {
			comparisons++;
			if (ints.at(min) > ints.at(i)) {
				min = i;
			}
		}

		if (min != j) {

			swap(ints.at(j), ints.at(min));
		}

	}
}
void determineSort(string text, vector<int>& ints) {
	if (!text.compare("selection")) {
		selection_sort(ints);
		print(ints);
	} else if (!text.compare("qsort")) {
		qsort(&(ints[0]), ints.size(), sizeof(int), qsortCompare);
		print(ints);
	} else if (!text.compare("stl")) {
		sort(ints.begin(), ints.end(), stlSortCompare);
		print(ints);
	}

}
void runAllSorts() {
	srand(time(0));
	for (int z = 0; z < 3; z++) {
		if (z == 0)
			cout << "qSort comparisons: " << endl;
		else if (z == 1)
			cout << "stl Sort comparisons: " << endl;
		else if (z == 2)
			cout << "selection Sort comparisons: " << endl;
		for (int i = 200; i < 6001; i += 200) {
			vector<int> ints;
			for (int x = 0; x < i; x++) {
				int b = (rand() % 4000) + 1;
				ints.push_back(b);
			}
			if (z == 0) {
				qsort(&(ints[0]), ints.size(), sizeof(int), qsortCompare);
				cout << comparisons << endl;
				comparisons = 0;
			} else if (z == 1) {
				sort(ints.begin(), ints.end(), stlSortCompare);
				cout << comparisons << endl;
				comparisons = 0;
			} else if (z == 2) {
				selection_sort(ints);
				cout << comparisons << endl;
				comparisons = 0;
			}
		}
	}
}
int main(int argc, char* argv[]) {
	string runAll = "-d";
	//Added ability to pass file path as arg for testing.

	if (argc > 1 && string(argv[1]) == runAll) {
		cerr << "Debug mode, running all sorts." << endl;
		runAllSorts();
		return 0;
	} else if (argc > 1) {
		ifstream exprFile(argv[1]);
		if (!exprFile.is_open()) {
			cerr << "file not found, using std::cin" << endl;
		} else {
			cin.rdbuf(exprFile.rdbuf());
		}

	} else {
		//Read everything from standard cin
		vector<int> integers;
		string method;

		cin >> method;
		if (find(methods.begin(), methods.end(), method) != methods.end()) {
			string to_use = method;
			string line;
			int str_int;
			while (cin >> line) {
				try {
					str_int = stoi(line);
					if (str_int != 0) {
						integers.push_back(str_int);
					} else {
						break;
					}
				} catch (invalid_argument& e) {
					cerr << e.what();
					break;
				}
			}
			determineSort(to_use, integers);

		} else {
			cerr << "Not a valid sort method!";
			return -1;
		}
		return EXIT_SUCCESS;
	}

}
