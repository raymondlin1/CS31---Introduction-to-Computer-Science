// stars.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include "utilities.h"
#include <iostream>
#include <cstring>
using namespace std;

const char WORDFILENAME[] = "C:/Users/shado/OneDrive/Documents/College Stuff/CS31 Projects/Project 5 - Star Search/wordLib.txt";
const int MAXWORDS = 9000;

int runOneRound(const char words[][7], int nWords, int wordnum);

int main()
{		
	char w[MAXWORDS][MAXWORDLEN + 1];
	int n = getWords(w, MAXWORDS, WORDFILENAME);

	//check if getWords is greater than MaxWords
	if (n > MAXWORDS) {
		return -1;
	}

	//check if getWords returns a number less than 1
	if (n < 1) {
		cout << "No words were loaded, so I can't play the game." << endl;
		return -1;
	}

	//asks user how many rounds to play
	int numRounds = 0;
	cout << "How many rounds do you want to play? ";
	cin >> numRounds;

	//check if it is positive
	if (numRounds <= 0) {
		cout << "The number of rounds must be positive." << endl;
		return -1;
	}
	cin.ignore(9000, '\n');
	cout << endl;

	int i = 0;
	double total = 0.00;
	double average = 0.00;
	int maxTries = 0;
	int minTries = INT8_MAX;
	while (i < numRounds) {
		i++;
		cout << "Round " << i << endl;
		int posOfTarget = randInt(0, n - 1);
		cout << "The secret word is " << strlen(w[posOfTarget]) << " letters long." << endl;
		int tries = runOneRound(w, n, posOfTarget);

		//if error
		if (tries == -1) {
			cout << "ERROR" << endl;
			return -1;
		}

		//calculates average
		total += static_cast<double>(tries);
		average = total / i;
		cout.setf(ios::fixed);
		cout.precision(2);

		//calculates max and min tries
		if (tries > maxTries) {
			maxTries = tries;
		}
		
		if (tries < minTries) {
			minTries = tries;
		}

		//reports the number of tries
		if (tries == 1) {
			cout << "You got it in 1 try." << endl;
		}
		else {
			cout << "You got it in " << tries << " tries." << endl;
		}

		cout << "Average: " << average << ", minimum: " << minTries << ", maximum: " << maxTries << endl;

		cout << endl;
	}

	/*if (n == 2)
	{
		cout << "getWords successfully found the file and read its two words." << endl;
		cout << "You're ready to start working on Project 5." << endl;
	}
	else if (n == -1)
		cout << "The path to your file is probably incorrect" << endl;
	else
		cout << "getWords found the file, but loaded " << n
		<< " words instead of 2" << endl;*/

}	

//runs one round of the game until the user guesses the correct word
int runOneRound(const char words[][7], int nWords, int wordnum) {
	//nwords is then number of words in the array 'words'
	//wordnum is the position of the target word, in the array 'words'
	//preconditions
	if (nWords <= 0 || wordnum < 0 || wordnum >= nWords) {
		return -1;
	}
	int counter = 0; //counts the number times the user had valid guesses
	char probe[100]; //array to store the probe word cstring

	while (strcmp(words[wordnum], probe) != 0) {
		//put probe word into 'probe' cstring
		cout << "Probe word: ";
		cin.getline(probe, 100);

		//if probe word length is not between 4 and 6, return an error
		if (strlen(probe) < 4 || strlen(probe) > 6) {
			cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
		}
		else {
			//check if the probe word is in the array
			bool isInArray = false;		
			for (int i = 0; i < nWords; i++) {
				if (strcmp(probe, words[i]) == 0) {
					isInArray = true;
					break;
				}
			}

			if (!isInArray) {
				cout << "I don't know that word." << endl;
			}
			else {
				counter++;
				//loop through the cstrings and count stars and planets
				char copyOfTarget[7];
				strcpy(copyOfTarget, words[wordnum]);
				int stars = 0;
				int planets = 0;
				//loop through the chars
				for (int i = 0; i < strlen(probe); i++) {
					//count stars
					if (copyOfTarget[i] == probe[i]) {
						stars++;
						probe[i] = '+';
						copyOfTarget[i] = '-';
						//if all letters match
						if (stars == strlen(words[wordnum])) {
							return counter;
						}
					}
				}

				for (int i = 0; i < strlen(probe); i++) {
					//count planets
					char temp = probe[i];
					for (int j = 0; j < strlen(words[wordnum]); j++) {
						char temp2 = copyOfTarget[j];

						if (temp == temp2 && i != j) {
							planets++;
							copyOfTarget[j] = '-';
							break;
						}
					}

					
				}
				cout << "Stars: " << stars << ", " << "Planets: " << planets << endl;

			}
		}

	}
	return 1;
}

