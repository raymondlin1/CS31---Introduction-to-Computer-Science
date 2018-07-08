// array.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int split(string a[], int n, string splitter);

int main()
{
	string h[7] = { "selina", "reed", "diana", "tony", "", "logan", "peter" }; //alphabetical order: "", diana, logan, peter, reed, selina, tony
	assert(lookup(h, 7, "logan") == 5);
	assert(lookup(h, 7, "diana") == 2);
	assert(lookup(h, 2, "diana") == -1);
	assert(positionOfMax(h, 7) == 3);

	string g[4] = { "selina", "reed", "peter", "sue" };
	assert(differ(h, 4, g, 4) == 2);
	assert(appendToAll(g, 4, "?") == 4 && g[0] == "selina?" && g[3] == "sue?");
	assert(rotateLeft(g, 4, 1) == 1 && g[1] == "peter?" && g[3] == "reed?");

	string e[4] = { "diana", "tony", "", "logan" };
	assert(subsequence(h, 7, e, 4) == 2);

	string d[5] = { "reed", "reed", "reed", "tony", "tony" };
	assert(countRuns(d, 5) == 2);

	string f[3] = { "peter", "diana", "steve" };
	assert(lookupAny(h, 7, f, 3) == 2);
	assert(flip(f, 3) == 3 && f[0] == "steve" && f[2] == "peter");

	assert(split(h, 7, "") == 0);

	cerr << "All tests succeeded" << endl;
}

int appendToAll(string a[], int n, string value) {
	if (n < 0) {
		return -1;
	}

	for (int i = 0; i < n; i++) {
		a[i] += "" + value;
	}

	return n;
}

int lookup(const string a[], int n, string target) {
	if (n < 0) {
		return -1;
	}
	for (int i = 0; i < n; i++) {
		if (target == a[i]) {
			return i;
		}
	}
	return -1;
}

int positionOfMax(const string a[], int n) {
	if (n < 0) {
		return -1;
	}
	int maxPos = 0;
	for (int i = 0; i < n; i++) {
		if (a[maxPos] < a[i]) {
			maxPos = i;
		}
	}
	return maxPos;
}

int rotateLeft(string a[], int n, int pos) {
	string holder = a[pos];
	for (int i = pos; i < n - pos - 1; i++) {
		
		a[i] = a[i + 1];
	}
	a[n-1] = holder;
	return pos;
}

int countRuns(const string a[], int n) {
	if (n < 0) {
		return -1;
	}
	int runs = 1;
	for (int i = 0; i < n - 1; i++) {
		if (a[i] != a[i + 1]) {
			runs++;
		}
	}
	return runs;
}

int flip(string a[], int n) {
	if (n < 0) {
		return -1;
	}
	for (int i = 0; i < n/2; i++) {
		string temp = a[i];
		a[i] = a[n - i - 1];
		a[n - i - 1] = temp;
	}
	return n;
}

int differ(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 < 0) {
		return -1;
	}

	if (n1 < n2) {
		for (int i = 0; i < n1; i++) {
			if (a1[i] != a2[i]) {
				return i;
			}
		}
		return n1;
	}
	else {
		for (int i = 0; i < n2; i++) {
			if (a1[i] != a2[i]) {
				return i;
			}
		}
		return n2;
	}
	
}

int subsequence(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 < 0) {
		return -1;
	}

	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < n2; j++) {
			if (a1[i] == a2[j]) {
				bool contains = false;
				for (int k = 0; k < n2; k++) {
					if (a1[k + i] == a2[k]) {
						contains = true;
					}
					else {
						contains = false;
					}
				}
				if (contains) {
					return i;
				}
				else {
					return -1;
				}
			}
		}
	}
	return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 < 0) {
		return -1;
	}
	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < n2; j++) {
			if (a1[i] == a2[j]) {
				return i;
			}
		}
	}
	return -1;
}

int split(string a[], int n, string splitter) {
	if (n < 0) {
		return -1;
	}
	int counter = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] >= splitter) {
			string temp = a[i];
			for (int j = i; j < n - 1; j++) {
				a[j] = a[j + 1];
				
			}
			a[n - 1] = temp;
			i--;
			
			if (counter == n) {
				break;
			}
			
		}
		counter++;

		/*for (int i = 0; i < n; i++) {
			cout << a[i] << endl;
		}
		cout << "---" << counter << endl; */

	}	

	for (int i = 0; i < n; i++) {
		
		if (a[i] >= splitter) {
			return i;
		}
	}
	return n;
}