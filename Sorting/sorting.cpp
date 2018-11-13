//============================================================================
// Name        : Sort3.cpp
// Author      : Robert Usey
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

class Multiplier {
public:
    Multiplier();
    virtual ~Multiplier();

    vector<int> bruteForceMultiply(const vector<int>& a, const vector<int>& b);
    vector<int> karatsubaMultiply(const vector<int>& a, const vector<int>& b);
    string toString(const vector<int>& inp);

private:
    vector<int> addVectors(const vector<int>& a, const vector<int>& b);
    vector<int> subtractVectors(const vector<int>& a, const vector<int>& b);

};

Multiplier::Multiplier() {
}
Multiplier::~Multiplier() {
}


vector<int> readNumber() {
    vector<int> num;
    char c;
    int temp = 0;
    int diff = 0;

    // get big number
    // ignores any non-integer input
    while(cin.get(c)) {
        // once we reach the end of the line
        // we need to stop trying to read input
        if(c == '\n' || c == '\0') {
            break;
        }

        // converts the char into the correct int
        temp = c - '0';

        // checking to make sure the character is actually a digit
        // if so, add it to the vector
        if(temp < 10 && temp >= 0) {
            num.insert(num.begin(), temp);
        }

    }

    return num;
}

void prettifyNumbers(vector<int>& a, vector<int>& b) {
    int sizeDiff = 0;

    // Make sure the vectors are not empty.
    // If a number is empty, make it 0.
    if(a.size() == 0) {
        a.push_back(0);
    }
    if(b.size() == 0) {
        b.push_back(0);
    }

    // Ensure the numbers are of equal length
    // by adding 0s to the end of the shorter one
    // first, calculate the size sizeDifference
    sizeDiff = a.size() - b.size();

    // a is bigger, so insert the appropriate number of 0s at the end
    if(sizeDiff > 0) {
        b.insert(b.end(), sizeDiff, 0);
    }
    // b is bigger, so insert the appropriate number of 0s at the end
    // note the absolute value
    else if(sizeDiff < 0) {
        a.insert(a.end(), abs(sizeDiff), 0);
    }
}

// implements the brute force algorithm for multiplication that
// you learned in third grade. uses the partial sums method.
// O(sizeA * size B) => O(n^2)
vector<int> Multiplier::bruteForceMultiply(const vector<int>& a, const vector<int>& b) {

    int mult = 0;
    int ones = 0;
    int carry = 0;
    int numZeros = 0;
    int sizeA = static_cast<int>(a.size());
    int sizeB = static_cast<int>(b.size());
    vector<int> result;
    vector<int> temp;


    for(int i = 0; i < sizeA; ++i) { // traverse a
        carry = 0;

        for(int j = 0; j < sizeB; ++j) { // traverse b
            // erase the temp vector
            temp.clear();

            // insert the appropriate number of zeros into temp
            // one for every digit we are away from the end
            // of each number
            numZeros = i + j;
            temp.insert(temp.end(), numZeros, 0);

            // get the next digit for our partial sum
            mult = a[i] * b[j] + carry;
            carry = mult / 10;
            ones = mult % 10;
            temp.push_back(ones);

            // add the partial sum to our total so far
            result = addVectors(result, temp);
        } // inner for

        // handle overflow
        if(carry != 0) {
            temp.clear();
            temp.insert(temp.end(), (i + sizeB), 0);
            temp.push_back(carry);
            result = addVectors(result, temp);
        }
    } // outer for


    return result;
}

// implements the Karatsuba multiplication algorithm
// O(n^lg(3)) ~ O(n^1.585)
// to multiply two 2-digit numbers, the traditional algorithm requires 4 multiplications.
// this algorithm requires three multiplications, plus some addition operations.
// when applied recursively, we reduce the number of total multiplications and
// have asymptotically faster performance.
vector<int> Multiplier::karatsubaMultiply(const vector<int>& a, const vector<int>& b) {
    vector<int> result;
    vector<int> temp;
    vector<int> a0;
    vector<int> a1;
    vector<int> b0;
    vector<int> b1;
    vector<int> c0;
    vector<int> c1;
    vector<int> c2;
    int m = 0;

    if(a.size() == 1 || b.size() == 1) {
        // base case can use brute force method for single digits
        result = bruteForceMultiply(a, b);
    }
    else {
        m = max(a.size(), b.size()) / 2; // floor because int

        // copy inputs into two different vectors each
        // a = a0*10^m + a1
        // a1 = least significant digits of a = beginning of vector
        // a0 = most significant digits of a = end of vector
        for(int i = 0; i < a.size(); ++i) {
            if(i >= m) {
                a0.push_back(a[i]);
                //b0.push_back(b[i]);
            }
            else {
                a1.push_back(a[i]);
                //b1.push_back(b[i]);
            }
        }

        for(int j = 0; j < b.size(); ++ j) {
            if(j >= m) {
                b0.push_back(b[j]);
            }
            else {
                b1.push_back(b[j]);
            }
        }

        // recursive calls on each half of the input
        // notice the 3 multiplications
        c2 = karatsubaMultiply(a1, b1);
        c1 = karatsubaMultiply(a0, b0);

        c0 = karatsubaMultiply(addVectors(a1, a0), addVectors(b1, b0));

        // middle part
        // handle the carry
        // add the correct number of 0s
        temp = addVectors(c2, c1);
        c0 = subtractVectors(c0, temp);
        c0.insert(c0.begin(), m, 0);
        result = addVectors(c0, result);

        // most significant digits = c1
        // add the correct number of 0s
        c1.insert(c1.begin(), 2*m, 0);
        result = addVectors(c1, result);

        // least significant digits = c2
        result = addVectors(c2, result);
    }

    return result;
}



// adds vectors digit-by-digit
// they do not need to be the same length
vector<int> Multiplier::addVectors(const vector<int>& a, const vector<int>& b) {
    int sum = 0;
    int carry = 0;
    int ones = 0;
    int sizeDiff = 0;
    int sizeA = static_cast<int>(a.size());
    int sizeB = static_cast<int>(b.size());
    vector<int> result;

    sizeDiff = sizeA - sizeB;

    // First, add all of the digits where they both exist
    for(int i = 0; i < min(sizeA, sizeB); ++i) {
        sum = a[i] + b[i] + carry;
        carry = sum / 10;
        ones = sum % 10;
        result.push_back(ones);
    }

    // A has more digits
    if(sizeDiff > 0) {
        // first digit of A not in B is i = sizeB
        for(int i = sizeB; i < sizeA; ++i) {
            sum = a[i] + carry;
            carry = sum / 10;
            ones = sum % 10;
            result.push_back(ones);
        }

    }
    // B has more digits
    else if(sizeDiff < 0) {
        // first digit of B not in A is i = sizeA
        for(int i = sizeA; i < sizeB; ++i) {
            sum = b[i] + carry;
            carry = sum / 10;
            ones = sum % 10;
            result.push_back(ones);
        }
    }

    // regardless of which is bigger,
    // handle possible overflow from carry
    if (carry != 0) {
         result.push_back(carry);
    }

    return result;
}

// subtracts two vectors digit-by-digit
// they do not need to be the same length, but a should >= b
vector<int> Multiplier::subtractVectors(const vector<int>& a, const vector<int>& b) {
    int diff = 0;
    int carry = 0;
    int sizeDiff = 0;
    int sizeA = static_cast<int>(a.size());
    int sizeB = static_cast<int>(b.size());
    bool errorFlag = false;
    vector<int> result;

    sizeDiff = sizeA - sizeB;

    // First, add all of the digits where they both exist
    for(int i = 0; i < min(sizeA, sizeB); ++i) {
        diff = a[i] - b[i] - carry;
        if(diff < 0) {
            diff += 10;
            carry = 1;
        }
        else {
            carry = 0;
        }
        result.push_back(diff);
    }

    // A has more digits
    if(sizeDiff > 0) {
        // first digit of A not in B is i = sizeB
        for(int i = sizeB; i < sizeA; ++i) {
            diff = a[i] - carry;
            if(diff < 0) {
                diff += 10;
                carry = 1;
            }
            else {
                carry = 0;
            }
            result.push_back(diff);

        }

    }
    // B has more digits
    // All the extra digits better be 0, otherwise B > A
    else if(sizeDiff < 0) {

        // first digit of B not in A is i = sizeA
        for(int i = sizeA; i < sizeB; ++i) {
            // if we get to a digit that isn't zero,
            // B was bigger, so we flag an error
            if (b[i] != 0) {
                errorFlag = true;
                break;
            }
        }

    }

    // if we flagged an error, return 0.
    if(errorFlag) {
        result.clear();
        result.push_back(0);
    }

    return result;
}

string Multiplier::toString(const vector<int>& inp) {
    string ret = "";
    vector<int>::const_reverse_iterator it;

    for(it = inp.rbegin(); it != inp.rend(); ++it) {
        ret += to_string(*it);
    }

    return ret;
}
int main(int argc, char *argv[]) {
	vector<int> a = readNumber();
	vector<int> b = readNumber();
	prettifyNumbers(a, b);

	Multiplier multiplier = Multiplier();

	cout << "Brute Force: "
			<< multiplier.toString(multiplier.bruteForceMultiply(a, b)) << endl;
	cout << "Karatsuba: "
			<< multiplier.toString(multiplier.karatsubaMultiply(a, b)) << endl;
}
