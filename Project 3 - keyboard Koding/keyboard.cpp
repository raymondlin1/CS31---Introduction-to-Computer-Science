// keyboard.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <string>
#include <cassert>
#include <cctype>
using namespace std;

char encodeNote(int octave, char noteLetter, char accidentalSign);
bool hasCorrectSyntax(string song);
int encodeSong(string song, string& instructions, int& badBeat);
bool isAccidentalSign(char character);
bool isNoteLetter(char character);

int main()
{
	//playable: return 0
	//not playable: return 2, badb set to first unplayable note
	//not a song string: return 1

	string instrs;
	int badb;
	string song;
	cin >> song;
	instrs = "xxx"; badb = -999; // so we can detect whether these get changed
	//cout << encodeSong("G/", instrs, badb) << endl;
	assert(encodeSong(song, instrs, badb) == 0 && instrs != "xxx"  &&  badb == -999);
	cerr << "All tests succeeded" << endl;
}
	
int encodeSong(string song, string& instructions, int& badBeat)
{
	bool syntax = hasCorrectSyntax(song);
	int size = song.size();
	string encodedSong = "";

	if (song == "") {
		return 0;
	}

	//if has right syntax, check if playable, else return 1
	if (syntax) {
		bool playable = false;
		int posBeat = 1;
		bool hasAtLeastOneNote = false;

		//check to see if song is playable
		for (int i = 0; i < size; i++) {
			char note = song[i];
			
			switch (note) {
			case '/':
				//if there is slash, plus a beat
				posBeat++;
				playable = true;
				if (hasAtLeastOneNote && i > 0 && song[i - 1] == '/') {
					encodedSong += " ";
				}
				
				break;
			case ' ':
				playable = true;
				
				break;
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
			case 'G':
				playable = true;
				hasAtLeastOneNote = true;
				//if char after is another note or slash, encode it
				if (isNoteLetter(song[i + 1]) || song[i + 1] == '/') {
					encodedSong += encodeNote(4, note, ' ');
					
				}
				break;
			case '#':
			case 'b':
				
				//if char after is not an octave number and char before is a note letter, encode it
				if (!isdigit(song[i + 1]) && isNoteLetter(song[i - 1])) {
					playable = true;
					encodedSong += encodeNote(4, song[i-1], note);
				}
				break;
			case '1':
				//char before must be #, which is after B
				if (i > 1 && song[i - 1] == '#' && song[i - 2] == 'B') {
					playable = true;
					encodedSong += encodeNote(1, 'B', '#');
					break;
				}
				else {
					playable = false;
					return playable;
				}
				break;
			case '2':
				
				//if char before is a note letter, encode it
				if (isNoteLetter(song[i - 1])) {
					playable = true;
					encodedSong += encodeNote(2, song[i-1], ' ');
					break;
				}

				//if char before is accidental sign and char before that is note letter, encode it
				else if (isAccidentalSign(song[i-1]) && isNoteLetter(song[i-2]) && song[i-2] != 'C') {
					playable = true;
					encodedSong += encodeNote(2, song[i - 2], song[i - 1]);
					break;
				}
				
				//if note is Cb2, unplayable
				if (song[i - 1] == 'b' && song[i - 2] == 'C') {
					playable = false;
					badBeat = posBeat;
					return 2;
				}
			case '3':
				//for all octaves, if the character before is a note or the characters before are an accidental sign and a note respectively, it is playable
				if (i > 0 && isNoteLetter(song[i - 1])) {

					playable = true;
					encodedSong += encodeNote(3, song[i - 1], ' ');
					break;
				}
				else if (i > 1 && isAccidentalSign(song[i - 1]) && isNoteLetter(song[i - 2])) {
				
					playable = true;
					encodedSong += encodeNote(3, song[i - 2], song[i - 1]);
					break;
				}
			case '4':
				if (i > 0 && isNoteLetter(song[i - 1])) {
					playable = true;
					encodedSong += encodeNote(4, song[i - 1], ' ');
					break;
				}
				else if (i > 1 && isAccidentalSign(song[i - 1]) && isNoteLetter(song[i - 2])) {
					playable = true;
					encodedSong += encodeNote(4, song[i - 2], song[i - 1]);
					break;
				}
			case '5':
				if (i > 0 && isNoteLetter(song[i - 1])) {
					playable = true;
					encodedSong += encodeNote(5, song[i - 1], ' ');
					break;
				}
				else if (i > 1 && isAccidentalSign(song[i - 1]) && isNoteLetter(song[i - 2])) {
					playable = true;
					encodedSong += encodeNote(5, song[i - 2], song[i - 1]);
					break;
				}
			case '6':
				//if char before is C, or if char before is b and before that is C, encode it
				if (i > 0 && song[i - 1] == 'C') {
					playable = true;
					encodedSong += encodeNote(6, 'C', ' ');
					break;
				}
				else if (i > 1 && (song[i - 1] == 'b' && song[i - 2] == 'C')) {
					playable = true;
					encodedSong += encodeNote(6, 'C', 'b');
					break;
				}
			default:
				//character must be unplayable
				playable = false;
				badBeat = posBeat;
				return 2;				
			}

		} //end of for

		if (playable) {
			if (hasAtLeastOneNote) {
				instructions = encodedSong;
			}			
			return 0;
		}
	
	}
	else {
		return 1;
	}
	
}

//determines if the character is an accidental sign
bool isAccidentalSign(char character) {
	if (character == 'b' || character == '#') {
		return true;
	}
	else {
		return false;
	}
}

//determines if the character is a note letter
bool isNoteLetter(char character) {
	switch (character) {
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
		return true;
	default:
		return false;
	}
}

bool hasCorrectSyntax(string song)
{
	bool returnVal = false;
	int size = song.size();

	//tests every character in song to see if they are valid; if there is an invalid combination, return false
	for (int i = 0; i < size; i++) {
		char note = song[i];

		switch (note) {
		case '/':
		case ' ':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
			//any of these characters must have correct syntax
			returnVal = true;
			break;
		case '#':
		case 'b':
			//if accidental signs are not at the beginning and the character before is a note, it has correct syntax
			if ((i>0) && isNoteLetter(song[i - 1])) {
				returnVal = true;
				break;
			}
			else {
				return false;
			}
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			//if octave is not at the beginnering and the character before is a note or an accidental sign, it has correct syntax
			if ((i > 0) && ((isNoteLetter(song[i - 1]) || isAccidentalSign(song[i - 1])))) {
				returnVal = true;
				break;
			}
		default:
			//if none of the cases above, it has incorrect syntax
			returnVal = false;
			return returnVal;
		}
	}
	//if song doesn't end with / or ' ', it has incorrect syntax
	if (song.size() > 1 && ((song[song.size() - 1] != '/') && (song[song.size() - 1] != ' '))) {
		returnVal = false;
	}
	return returnVal;
}

//*************************************
//  encodeNote
//*************************************

// Given an octave number, a note letter, and an accidental sign, return
// the character that the indicated note is encoded as if it is playable.
// Return a space character if it is not playable.
//
// First parameter:   the octave number (the integer 4 is the number of the
//                    octave that starts with middle C, for example).
// Second parameter:  an upper case note letter, 'A' through 'G'
// Third parameter:   '#', 'b', or ' ' (meaning no accidental sign)
//
// Examples:  encodeNote(4, 'A', ' ') returns 'Q'
//            encodeNote(4, 'A', '#') returns '%'
//            encodeNote(4, 'H', ' ') returns ' '

char encodeNote(int octave, char noteLetter, char accidentalSign)
{
	// This check is here solely to report a common CS 31 student error.
	if (octave > 9)
	{
		cerr << "********** encodeNote was called with first argument = "
			<< octave << endl;
	}

	// Convert Cb, C, C#/Db, D, D#/Eb, ..., B, B#
	//      to -1, 0,   1,   2,   3, ...,  11, 12

	int note;
	switch (noteLetter)
	{
	case 'C':  note = 0; break;
	case 'D':  note = 2; break;
	case 'E':  note = 4; break;
	case 'F':  note = 5; break;
	case 'G':  note = 7; break;
	case 'A':  note = 9; break;
	case 'B':  note = 11; break;
	default:   return ' ';
	}
	switch (accidentalSign)
	{
	case '#':  note++; break;
	case 'b':  note--; break;
	case ' ':  break;
	default:   return ' ';
	}

	// Convert ..., A#1, B1, C2, C#2, D2, ... to
	//         ..., -2,  -1, 0,   1,  2, ...

	int sequenceNumber = 12 * (octave - 2) + note;

	string keymap = "Z1X2CV3B4N5M,6.7/A8S9D0FG!H@JK#L$Q%WE^R&TY*U(I)OP";
	if (sequenceNumber < 0 || sequenceNumber >= keymap.size())
		return ' ';
	return keymap[sequenceNumber];
}