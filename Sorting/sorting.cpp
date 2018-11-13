//============================================================================
// Name        : sorting.cpp
// Author      : Robert Usey
// Assignment  : CSCE350 Project3
// Copyright   : Copyright Robert Usey 2018
// Description : Implementation large integer multiplication
//               using bruteForce and karatsuba algorithms
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

// MultAlgos CLASS HEADER TO DEFINE THE ALGORITHMS TO BE IMPLEMENTED
// + HELPER METHODS FOR VECTOR ADDITION AND SUBTRACTION
class MultAlgos {
public:
	MultAlgos();
	virtual ~MultAlgos();

	vector<int> bruteForce(const vector<int>& a, const vector<int>& b);
	vector<int> karatsuba(const vector<int>& a, const vector<int>& b);
	string print(const vector<int>& vec);

private:
	vector<int> addVec(const vector<int>& a, const vector<int>& b);
	vector<int> subVec(const vector<int>& a, const vector<int>& b);

};
//CONSTRUCTOR/DESCTRUCOR(NOT USED)
MultAlgos::MultAlgos() {
}
MultAlgos::~MultAlgos() {
}

//READ A VECTOR OF INTEGERS FROM CIN
vector<int> readVecDigits() {
	vector<int> number;
	char chr;
	int tempChr = 0;
	//READ CHARS FROM CIN
	while (cin.get(chr)) {
		//STOP AFTER NEWLINE OR STR TERMINATOR
		if (chr == '\n' || chr == '\0') {
			break;
		}
		// CONVERT CHAR TO INT
		tempChr = chr - '0';

		//DIGIT SANITATION, ADD IT TO NUMBE VEC IF IS DIGIT 0-9
		if (tempChr < 10 && tempChr >= 0) {
			number.insert(number.begin(), tempChr);
		}
	}
	return number;
}
//APPENDS TRAILING ZEROS TO THE RESPECTIVE VECTOR WITH LESS DIGITS
void equalizeNumbers(vector<int>& a, vector<int>& b) {
	int sizeDiff = 0;

	//NEED TO MAKE A. B EQUAL LENGTH BY APPENDING ZEROS RESPECTIVELY
	//TO THE SMALLER NUMBER

	//FIND DIFFERENCE IN SIZE
	sizeDiff = a.size() - b.size();

	// IF A IS BIGGER INSERT SIZEDIFF AMOUNT OF ZEROS INTO B
	if (sizeDiff > 0) {
		b.insert(b.end(), sizeDiff, 0);
	}
	// IF B IS BIGGER INSERT SIZEDIFF AMOUNT OF ZEROS INTO A
	//MUST USE ABSOLUTE VALUE BECAUSE SIZEDIFF WILL BE NEGATIVE IN THIS CASE
	else if (sizeDiff < 0) {
		a.insert(a.end(), abs(sizeDiff), 0);
	}
}

//IMPL OF BURE FORCE MULT
vector<int> MultAlgos::bruteForce(const vector<int>& a, const vector<int>& b) {

	int mult = 0;
	int digit = 0;
	int carry = 0;
	int numZeros = 0;
	int sizeA = static_cast<int>(a.size());
	int sizeB = static_cast<int>(b.size());
	vector<int> result;
	vector<int> temp;

	//OUTER LOOP ITERATE OVER A
	for (int i = 0; i < sizeA; ++i) {
		carry = 0;
		//INNER LOOP ITERATE OVER B
		for (int j = 0; j < sizeB; ++j) {
			//CLEAR THE TEMP VECTOR EACH INNER FOR ITERATION
			temp.clear();

			//INSERT TRAILING ZEROS INTOA TEMP VEC BASED ON HOW FAR INTO
			//THE ITERATION WE ARE
			//STORE IN A TEMP VECTOR
			numZeros = i + j;
			temp.insert(temp.end(), numZeros, 0);

			//MULTIPLY THE CORRESPONDING DIGITS
			//CACLULATE THE CARRY AND NUMBER OF ZEROS TO INSERT
			//INSERT THE MULTPLIED ELEMENTS MOD 10
			mult = a[i] * b[j] + carry;
			carry = mult / 10;
			digit = mult % 10;
			temp.push_back(digit);

			//ADD THE PARTIAL RESULT FOR THIS ITERATION
			result = addVec(result, temp);
		}

		// IF WE HAVE LEFTOVER CARRY
		// ADD ZEROS AND ADD FINAL PARTIAL RESULT
		if (carry != 0) {
			temp.clear();
			temp.insert(temp.end(), (i + sizeB), 0);
			temp.push_back(carry);
			result = addVec(result, temp);
		}
	}
	return result;
}

//KARATSUBA MULT IMPL
vector<int> MultAlgos::karatsuba(const vector<int>& a, const vector<int>& b) {
	vector<int> result;
	vector<int> temp;
	vector<int> msdA;
	vector<int> lsdA;
	vector<int> msdB;
	vector<int> lsdB;
	vector<int> c0;
	vector<int> c1;
	vector<int> c2;
	int middle = 0;

	if (a.size() == 1 || b.size() == 1) {
		//BASECASE MULTIPLY THE SINGLE DIGITS OF A,B USING BRUTEFORCE
		//COULD NOT FIGURE OUT TO DO A SINGLE MULT WITHOUT KNOWING WHAT POWER OF 10 WE WERE ON
		result = bruteForce(a, b);

	} else {
		middle = max(a.size(), b.size()) / 2; // floor because int

		//DIGITS LEFT OF MIDDLE ARE MOST SIGNIFICANT
		//DIGITS RIGHT OF MIDDLE ARE LEAST SIGNIFICANT
		for (int i = 0; i < a.size(); ++i) {
			if (i >= middle) {
				msdA.push_back(a[i]);
			} else {
				lsdA.push_back(a[i]);
			}
		}
		//DIGITS LEFT OF MIDDLE ARE MOST SIGNIFICANT
		//DIGITS RIGHT OF MIDDLE ARE LEAST SIGNIFICANT
		for (int j = 0; j < b.size(); ++j) {
			if (j >= middle) {
				msdB.push_back(b[j]);
			} else {
				lsdB.push_back(b[j]);
			}
		}
		//=================================
		//BEGIN DIVIDE AND CONQUER FOR MULT
		//=================================

		//RECURSE ON BOTH HALVES OF BOTH INPUTS
		c2 = karatsuba(lsdA, lsdB);
		c1 = karatsuba(msdA, msdB);
		//RECURSIVELY FIND CARRY OF ADDING LEAST/MOST SIG DIGITS OF EACH INPUT
		c0 = karatsuba(addVec(lsdA, msdA), addVec(lsdB, msdB));

		//ADD CARRY DIGITS FROM ONE AND TWO TO TEMP VECTOR
		//INSERT CORRECT ZEROS INTO C0
		temp = addVec(c2, c1);
		c0 = subVec(c0, temp);
		c0.insert(c0.begin(), middle, 0);
		//ADD PARTIAL RESULT OF MULT 1 TO RESULT
		result = addVec(c0, result);

		//ADD MOST SIGNIFICANT DIGITS TO RESULT
		c1.insert(c1.begin(), 2 * middle, 0);
		result = addVec(c1, result);

		//ADD LEAST SIGNIFICANT DIGITS TO RESULT
		result = addVec(c2, result);
	}
	return result;
}

//ADD VECTORS BY DIGIT. WILL AUTO EQUALIZE LENGTH IF NOT EQUAL
vector<int> MultAlgos::addVec(const vector<int>& a, const vector<int>& b) {
	int sum = 0;
	int carry = 0;
	int digit = 0;
	int sizeDiff = 0;
	int sizeA = static_cast<int>(a.size());
	int sizeB = static_cast<int>(b.size());
	vector<int> result;

	sizeDiff = sizeA - sizeB;

	//ADD THE DIGITS UP UNTIL THERE SIZES ARE NO LONGER EQUAL
	for (int i = 0; i < min(sizeA, sizeB); ++i) {
		sum = a[i] + b[i] + carry;
		carry = sum / 10;
		digit = sum % 10;
		result.push_back(digit);
	}

	// IF A IS BIGGER INSERT SIZEDIFF AMOUNT OF ZEROS INTO B STARTING AT THE POINT THEY ARE NOT EQUAL LENGTH
	if (sizeDiff > 0) {
		//IF A LARGER INSERT ZEROS STARTING AT END INDEX OF B (sizeB)
		for (int i = sizeB; i < sizeA; ++i) {
			sum = a[i] + carry;
			carry = sum / 10;
			digit = sum % 10;
			result.push_back(digit);
		}

	}
	// IF B IS BIGGER INSERT SIZEDIFF AMOUNT OF ZEROS INTO A STARTING AT THE POINT THEY ARE NOT EQUAL LENGTH
	else if (sizeDiff < 0) {
		//IF B LARGER INSERT ZEROS STARTING AT END INDEX OF A (sizeA)
		for (int i = sizeA; i < sizeB; ++i) {
			sum = b[i] + carry;
			carry = sum / 10;
			digit = sum % 10;
			result.push_back(digit);
		}
	}
	//HANDLE POSSIBLE CARRY OVERFLOW
	if (carry != 0) {
		result.push_back(carry);
	}
	return result;
}

//SUBTRACT VECTORS DIGIT BY DIGIT
vector<int> MultAlgos::subVec(const vector<int>& a, const vector<int>& b) {
	int difference = 0;
	int carry = 0;
	int sizeDiff = 0;
	int sizeA = static_cast<int>(a.size());
	int sizeB = static_cast<int>(b.size());
	vector<int> result;

	sizeDiff = sizeA - sizeB;

	//SUBTRACT DIGITS UNTIL THEYRE LENGTHS ARE NO LONGER EQUAL
	for (int i = 0; i < min(sizeA, sizeB); ++i) {
		difference = a[i] - b[i] - carry;
		if (difference < 0) {
			difference += 10;
			carry = 1;
		} else {
			carry = 0;
		}
		result.push_back(difference);
	}

	//A HAS MORE DIGITS
	if (sizeDiff > 0) {
		//IF A LARGER INSERT ZEROS STARTING AT END INDEX OF B (sizeB)
		for (int i = sizeB; i < sizeA; ++i) {
			difference = a[i] - carry;
			if (difference < 0) {
				difference += 10;
				carry = 1;
			} else {
				carry = 0;
			}
			result.push_back(difference);
		}
	}
	// B HAS MORE DIGITS
	// IF THE EXTRA DIGITS ARE NOT ZEROS, B>A WE CANNOT CONTINUE
	else if (sizeDiff < 0) {
		for (int i = sizeA; i < sizeB; ++i) {
			//IF WE FIND A TRAILING ZERO IN B, A,B ARE NOT EQUAL AND CANNOT BE SUBTRACTED
			//SO CLEAR RESULT AND RETURN 0
			if (b[i] != 0) {
				result.clear();
				result.push_back(0);
				return result;
			}
		}
	}
	return result;
}
//PRINTS A CALCULATE LARGE INT MULT RESULT USING REVERSE ORDER ITERATION
string MultAlgos::print(const vector<int>& vec) {
	string ret = "";
	//CREATE A REVERSE ITERATOR BECAUSE OUR RESULT IS BACKWARDS
	vector<int>::const_reverse_iterator it;
	//STARTING FROM THE END APPEND EACH DIGIT TO OUR RETURN STRING UNTIL THERE ARE NO MORE
	for (it = vec.rbegin(); it != vec.rend(); ++it) {
		ret += to_string(*it);
	}
	return ret;
}
int main(int argc, char *argv[]) {
	//READ TWO NUMBERS FROM CIN USING OUR METHOD
	vector<int> a = readVecDigits();
	vector<int> b = readVecDigits();
	//QUALIZE THE LENGTH OF BOTH VECTORS
	equalizeNumbers(a, b);
	//STACK ALLOC OF MULTALGOS CLASS.
	MultAlgos multiplier = MultAlgos();
	//OUTPUT OUR RESULTS
	cout << "Brute Force: " << multiplier.print(multiplier.bruteForce(a, b))
			<< endl;
	cout << "Karatsuba: " << multiplier.print(multiplier.karatsuba(a, b))
			<< endl;
}
