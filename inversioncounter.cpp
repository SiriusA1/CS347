/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Conor McGullam
 * Version     : 1.0
 * Date        : 3/29/2020
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
	long count = 0;
    for(int i = 0; i < length; ++i) {
		for(int j = i+1; j < length; ++j) {
			if(array[j] < array[i]) {
				++count;
			}
		}
	}
	return count;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
	int *scratch = new int[length];
	long count = mergesort(array, scratch, 0, length-1);
	delete [] scratch;
	return count;
}

static long mergesort(int array[], int scratch[], int low, int high) {
	long count = 0;
    if(low < high) {
		int mid = low + (high - low) / 2;
		count += mergesort(array, scratch, low, mid);
		count += mergesort(array, scratch, mid+1, high);
		int L = low;
		int H = mid + 1;
		for(int k = low; k <= high; ++k) {
			if(L <= mid && (H > high || array[L] <= array[H])) {
				scratch[k] = array[L];
				++L;
			}else { 
				scratch[k] = array[H];
				count = count + (H - k);
				++H;
			}
		}
		for(int k = low; k <= high; ++k) {
			array[k] = scratch[k];
		}
	}
	return count;
}

int main(int argc, char *argv[]) {
	
    if(argc > 2) {
		cerr << "Usage: ./inversioncounter [slow]" << endl;
		return 1;
	}else {
		istringstream iss;
		bool slow = false;
		if(argc == 2) {
			string inslow;
			iss.str(argv[1]);
			iss >> inslow;
			iss.clear();
			if(inslow != "slow") {
				cerr << "Error: Unrecognized option '" << inslow << "'." << endl;
				return 1;
			}else {
				slow = true;
			}
		}

		cout << "Enter sequence of integers, each followed by a space: " << flush;

		
		int value, index = 0;
		vector<int> values;
		string str;
		str.reserve(11);
		char c;
		while (true) {
			c = getchar();
			const bool eoln = c == '\r' || c == '\n';
			if (isspace(c) || eoln) {
				if (str.length() > 0) {
					iss.str(str);
					if (iss >> value) {
						values.push_back(value);
					} else {
						cerr << "Error: Non-integer value '" << str
							<< "' received at index " << index << "." << endl;
						return 1;
					}
					iss.clear();
					++index;
				}
				if (eoln) {
					break;
				}
				str.clear();
			} else {
				str += c;
			}
		}
		if(values.size() == 0) {
			cerr << "Error: Sequence of integers not received." << endl;
			return 1;
		}
		
		if(slow) {
			cout << "Number of inversions: " << count_inversions_slow(&values[0], (int)values.size()) << endl;
		}else {
			cout << "Number of inversions: " << count_inversions_fast(&values[0], (int)values.size()) << endl;
		}

		return 0;
	}
}
