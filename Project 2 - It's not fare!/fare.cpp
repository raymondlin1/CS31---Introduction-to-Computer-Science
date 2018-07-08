// fare.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

const double BASE_FARE = 1.35;
const double STUDENT_FARE = 0.65;
const double ZONE_RATE = 0.55;
const double SENIOR_BASE_FARE = 0.55;
const double SENIOR_ZONE_RATE = 0.25;
const double SENIOR_ONE_ZONE = 0.45;


int getRiderAge() //get age of rider, error if input is nonsensical
{
	cout << "Age of rider: ";
	int age;
	cin >> age;
	if (age < 0)
	{
		cout << "---\nThe age must not be negative" << endl;
	}
	return age;
}

int getStudent() //get whether the rider is a student, error if input is nonsensical
{
	cout << "Student? (y/n): ";
	string student;
	cin.ignore(10000, '\n');
	getline(cin, student);
	if (student == "y")
		return 1;
	else if (student == "n")
		return 0;
	else
	{
		cout << "---\nYou must enter y or n" << endl;
		return -1;
	}
		
}

string getDestination() //get destination of rider, error if nothing is entered
{
	cout << "Destination: ";
	string destination;
	getline(cin, destination);
	if (destination.compare("") == 0)
	{
		cout << "---\nYou must enter a destination" << endl;
	}
	return destination;
}	

int getZonesCrossed() //get number of zones crossed, error if input is nonsensical
{
	cout << "Number of zone boundaries crossed: ";
	int numberZonesCrossed;
	cin >> numberZonesCrossed;
	if(numberZonesCrossed < 0) {
		cout << "---\nThe number of zone boundaries crossed must not be negative" << endl;
		return -1;
	}
	return numberZonesCrossed;
	
}

void printFare(int age, bool student, string destination, int zones) //prints the fare for the ride
{
	cout << "---" << endl;
	double fare = 0;
	if ((age < 18) || ((age < 65) && (student == true)))
	{
		if (zones < 2)
		{
			fare = STUDENT_FARE;
		}
		else
		{
			fare = BASE_FARE + zones*ZONE_RATE;
		}
	}
	else if(age >= 65)
	{
		fare = SENIOR_BASE_FARE + zones*SENIOR_ZONE_RATE;
		if (zones == 0) {
			fare = SENIOR_ONE_ZONE;
		}
		else if ((zones == 1) && (student == true)) 
		{
			fare = STUDENT_FARE;
		}
	}
	else
	{
		fare = BASE_FARE + zones*ZONE_RATE;
	}
	cout.setf(ios::fixed);
	cout.precision(2);
	cout << "The fare to " << destination << " is $" << fare << endl;
}

int main()
{
	int age = getRiderAge();
	if (age < 0)
		return -1;

	bool student = false;
	int x = getStudent();
	if (x < 0)
		return -1;
	else if (x == 1)
		student = true;

	string destination = getDestination();
	if (destination.compare("") == 0)
	{
		return -1;
	}

	int zones = getZonesCrossed();
	if (zones < 0)
	{
		return -1;
	}
		

	printFare(age, student, destination, zones);

    return 0;
}



