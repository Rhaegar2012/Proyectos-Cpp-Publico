/*
 * Utils.cpp
 *
 *  Created on: Jan 24, 2025
 *      Author: joseb
 */
#include "Utils.h"
#include <iostream>
#include <cctype>
#include <map>

using namespace std;


const int IGNORE_CHARS = 256;

char GetInputCharacter(const char* prompt, const char* error)
{
	char input;
	bool failure;

	do
	{
		failure = false;
		cout << prompt << endl;
		cin >> input;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			cout << error << endl;
			failure = true;
		}
		else
		{
			cin.ignore(IGNORE_CHARS, '\n');
			if (isalpha(input))
			{
				input = toupper(input);
			}
			else
			{
				cout << error << endl;
				failure = true;
			}

		}
	} while (failure);
	cin.clear();
	return input;
}


int GetInputInt(const char* prompt, const char* error)
{
	int intInput;
	bool failure;

	do
	{
		failure = false;
		cout << prompt << endl;
		cin >> intInput;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			cout << error << endl;
			failure = true;
		}
		else
		{
			cin.ignore(IGNORE_CHARS, '\n');

		}
	} while (failure);
	cin.clear();
	return intInput;
}

int Square(int a) 
{
	return a * a;
}




